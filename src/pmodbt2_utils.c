/*******************************************************************************************
 *
 * Created by: Jonathan Tan (jona1115@iastate.edu)
 *
 * *****************************************************************************************
 *
 * @file pmodbt2_utils.c:
 *
 * MODIFICATION HISTORY:
 *
 * Ver   Who    Date	 Changes
 * ----- ------ -------- ----------------------------------------------
 * 1.00	Jonathan
 *
*******************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include "platform.h"
#include "xil_printf.h"
#include "xil_io.h"
#include "xparameters.h"
#include <unistd.h> // sleep()
//#include "PmodBT2.h"
#include "xuartps.h"
#include "xuartps_hw.h"

// Project includes
#include "utils.h"
#include "pmodbt2_utils.h"

#define x 5

int pmodBT2_init(XUartPs* Uart_PS,
				 XUartPs_Config* uart_0_config) {
	/* Auto config */
	uart_0_config = XUartPs_LookupConfig(XPAR_PS7_UART_0_DEVICE_ID);
	if (uart_0_config == NULL) {
		LOGE("Error looking up uart config!");
		return -1;
	}

	int uart_0_status = XUartPs_CfgInitialize(Uart_PS, uart_0_config, uart_0_config->BaseAddress);
	if (uart_0_status != XST_SUCCESS) {
		LOGE("Error initializing uart!");
		return -1;
	}

	uart_0_status = XUartPs_SelfTest(Uart_PS);
	if (uart_0_status != XST_SUCCESS) {
		LOGE("Error in uart self test!");
		return -1;
	}

	return 0;
}

/**
 * Parameters:
 * 	- If you dont know how long the receive buffer is, set givenReceiveBufferLen to -1, this
 *    function will free givenReceiveBuffer and malloc a new one according to how long the received
 *    response is.
 *
 * Returns:
 *  0 : All good!
 * 	-2: sent_count != SEND_BUFFER_SIZE
 */
int pmodBT2_send_and_receive(XUartPs* Uart_PS,
						 	 char* givenSendBuffer, int givenSendBufferLen,
							 char* givenReceiveBuffer, int* givenReceiveBufferLen) {
	// For some reason, when sendBuffer gets passed in its length is not right
	char tempSendBuffer[givenSendBufferLen];
	strncpy(tempSendBuffer, givenSendBuffer, givenSendBufferLen);

	/* Block sending the buffer. */
	int sent_count = 0;              /* Use tempSendBuffer instead of givenSendBuffer*/
	sent_count = XUartPs_Send(Uart_PS, &tempSendBuffer[0], givenSendBufferLen);
	if (sent_count != givenSendBufferLen) {
		LOGE("sent_count != SEND_BUFFER_SIZE!");
		return -1;
	}

	/*
	 * Wait while the UART is sending the data so that we are guaranteed
	 * to get the data the 1st time we call receive, otherwise this function
	 * may enter receive before the data has arrived
	 */
	int sendingLoopCount = 0;
	while (XUartPs_IsSending(Uart_PS)) {
		sendingLoopCount++;
		LOGD("Sending loop count: %d", sendingLoopCount);
	}

	/*
	 * Start receiving
	 */
	if (*givenReceiveBufferLen != -1) {
		// Receive buffer len known
		LOGD("Receive buffer len == %d", *givenReceiveBufferLen);

		int received_count = 0;
		while (received_count < *givenReceiveBufferLen) {
			received_count += XUartPs_Recv(Uart_PS,
										   givenReceiveBuffer,
	//									   (RECEIVE_BUFFER_SIZE - received_count)
										   1 // One byte at a time
										   );
			LOGD("Receive count: %d\tReceiving stuff...", received_count);
		}

		LOGD("Receive Buffer:");
		xil_printf(givenReceiveBuffer);
		xil_printf("\n\r");
	} else {
		// Receive buffer len unknown
		// So, we need to implement some sort of "dynamic sized" buffer
		char frameBuffer[FRAME_SIZE] = {0};
		int actualNumberOfReceivedBytes = 0;

		// The idea is if we stop receiving new characters for x times
		// Note: x is #defined above
		int history[x] = {0};
		int history_index = 0;
		int sumOfHistory = -1;

		while (1) {
			// Stop looping (probably stopped receiving new data) when:
			// 		Condition 1: The past x elements are the same
			// 		Condition 2: Make sure sumOfHistory isnt -1 ie we arent just getting started hence the history is
			//					 obviously all the same
			if ((sumOfHistory / x == history[history_index]) && (sumOfHistory != -1))
				break;

			// Start receiving
			actualNumberOfReceivedBytes += XUartPs_Recv(Uart_PS,
														frameBuffer,
													    1 // One byte at a time
													    );

			++history_index;
			if (history_index == 5) history_index = 0; // If we ran out of history index, circle back
			history[history_index] = actualNumberOfReceivedBytes;
			sumOfHistory = 0;
			for (int i = 0; i < x; ++i) sumOfHistory += history[i];
		}

		// Create actual array to return
		givenReceiveBuffer = (char*) malloc(actualNumberOfReceivedBytes * sizeof(char));
		// Make sure to change the len from -1 to the actual len
		*givenReceiveBufferLen = actualNumberOfReceivedBytes;

		// Copy from frameBuffer to givenReceiveBuffer
		strncpy(givenReceiveBuffer, frameBuffer, *givenReceiveBufferLen);

		LOGD("Receive Buffer:");
		xil_printf(givenReceiveBuffer);
		xil_printf("\n\r");
	}

	return 0;
}

int pmodBT2_send_and_just_send(XUartPs* Uart_PS,
							   char* givenSendBuffer, int givenSendBufferLen) {
	// For some reason, when sendBuffer gets passed in its length is not right
	char tempSendBuffer[givenSendBufferLen];
	strncpy(tempSendBuffer, givenSendBuffer, givenSendBufferLen);

	/* Block sending the buffer. */
	int sent_count = 0;              /* Use tempSendBuffer instead of givenSendBuffer*/
//	sent_count = XUartPs_Send(Uart_PS, &tempSendBuffer[0], givenSendBufferLen);
	XUartPs_Send(Uart_PS, &tempSendBuffer[0], givenSendBufferLen);
//	if (sent_count != givenSendBufferLen) {
//		LOGE("sent_count (%d) != givenSendBufferLen (%d)!", sent_count, givenSendBufferLen);
//		return -1;
//	}

	/*
	 * Wait while the UART is sending the data so that we are guaranteed
	 * to get the data the 1st time we call receive, otherwise this function
	 * may enter receive before the data has arrived
	 */
	int sendingLoopCount = 0;
	while (XUartPs_IsSending(Uart_PS)) {
		sendingLoopCount++;
		LOGD("Sending loop count: %d", sendingLoopCount);
	}

	return 0;
}

/**
 * The idea of this function is to when it sees a start of a frame (which is "SOF" for
 * start of frame), it will start receiving characters until we got a "EOF" (end of
 * frame).
 *
 * Returns:
 * 0 : for no error
 * -1: for error
 */
int pmodBT2_receive_frame(XUartPs* Uart_PS,
						  char* givenReceiveBuffer, int* givenReceiveBufferLen) {
	// So, we need to implement some sort of "dynamic sized" buffer
	char frameBuffer[FRAME_SIZE] = {0};
	int actualNumberOfReceivedBytes = 0;

	char temp_buffer[3] = {0}; // 3 because we just need to read "SOF" and or "EOF"
	uint32_t temp_buffer_counter = 0;

	int started_receiving_frame = 0;	// Received "SOF"
	int stopped_receiving_frame = 0;	// Received "EOF"

	int waiting_for_SOF_counter = 0;

	while (1) {
		// Start receiving
		temp_buffer[0] = temp_buffer[1];
		temp_buffer[1] = temp_buffer[2];
		actualNumberOfReceivedBytes += XUartPs_Recv(Uart_PS,
													&temp_buffer[2],
												    1 // One byte at a time
												    );

		if (strncmp(temp_buffer, "SOF", 3) == 0) {
			// Pass
		} else {
			LOGD("Waiting for SOF (%d)...", waiting_for_SOF_counter++);
			continue; // Loop again and wait for SOF
		}

		// If the code is here it has received SOF
		actualNumberOfReceivedBytes += XUartPs_Recv(Uart_PS,
													frameBuffer,
													FRAME_SIZE // One byte at a time
													);

		break;
	}

	// Create actual array to return
	givenReceiveBuffer = (char*) malloc(actualNumberOfReceivedBytes * sizeof(char));
	// Make sure to change the len from -1 to the actual len
	*givenReceiveBufferLen = actualNumberOfReceivedBytes;

	// Copy from frameBuffer to givenReceiveBuffer
	strncpy(givenReceiveBuffer, frameBuffer, *givenReceiveBufferLen);

//	LOGD("Receive Buffer:");
//	xil_printf(givenReceiveBuffer);
//	xil_printf("\n\r");


	return 0;
}
