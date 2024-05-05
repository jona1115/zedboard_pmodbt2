///******************************************************************************
//*
//* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
//*
//* Permission is hereby granted, free of charge, to any person obtaining a copy
//* of this software and associated documentation files (the "Software"), to deal
//* in the Software without restriction, including without limitation the rights
//* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//* copies of the Software, and to permit persons to whom the Software is
//* furnished to do so, subject to the following conditions:
//*
//* The above copyright notice and this permission notice shall be included in
//* all copies or substantial portions of the Software.
//*
//* Use of the Software is limited solely to applications:
//* (a) running on a Xilinx device, or
//* (b) that interact with a Xilinx device through a bus or interconnect.
//*
//* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
//* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
//* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
//* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//* SOFTWARE.
//*
//* Except as contained in this notice, the name of the Xilinx shall not be used
//* in advertising or otherwise to promote the sale, use or other dealings in
//* this Software without prior written authorization from Xilinx.
//*
//******************************************************************************/
//
///*
// * helloworld.c: simple test application
// *
// * This application configures UART 16550 to baud rate 9600.
// * PS7 UART (Zynq) is not initialized by this application, since
// * bootrom/bsp configures it to baud rate 115200
// *
// * ------------------------------------------------
// * | UART TYPE   BAUD RATE                        |
// * ------------------------------------------------
// *   uartns550   9600
// *   uartlite    Configurable only in HW design
// *   ps7_uart    115200 (configured by bootrom/bsp)
// */
//
//#include <stdio.h>
//#include <stdlib.h>
//#include "platform.h"
//#include "xil_printf.h"
//#include "xil_io.h"
//#include "xparameters.h"
//#include <unistd.h> // sleep()
////#include "PmodBT2.h"
//#include "xuartps.h"
//#include "xuartps_hw.h"
//
//// Project includes
//#include "utils.h"
//#include "pmodbt2_utils.h"
//
//
//void uint16_to_binary(uint16_t num, char *str) {
//    if (str == NULL) {
//        return; // Check for NULL pointer
//    }
//
//    // We need 16 characters + 3 dots + 1 for the null terminator
//    str[19] = '\0'; // Null-terminate the string
//
//    int pos = 18; // Start from the end of the string
//    for (int i = 0; i < 16; i++) {
//        str[pos--] = (num & 1) ? '1' : '0'; // Set each char to '0' or '1'
//        num >>= 1; // Shift the number to the right
//
//        // Insert a dot every four bits, but not after the last group
//        if (i % 4 == 3 && i != 15) {
//            str[pos--] = '.';
//        }
//    }
//}
//
//#ifdef VIVADO_BLOCK_DESIGN_1
//#define PMOD1_IN XPAR_AXI_GPIO_0_BASEADDR
//#define PMOD1_OUT XPAR_AXI_GPIO_1_BASEADDR
//#define PMOD2_IN XPAR_AXI_GPIO_3_BASEADDR
//#define PMOD2_OUT XPAR_AXI_GPIO_2_BASEADDR
//#endif
//
////#define VIVADO_BLOCK_DESIGN_1
////#define VIVADO_BLOCK_DESIGN_2
//#define VIVADO_BLOCK_DESIGN_3
//
//int main()
//{
//    init_platform();
//
//    LOGI("Start of PmodBT2 test program.");
//
////    print("Hello World\n\r");
////    print("Successfully ran Hello World application");
//
//#ifdef VIVADO_BLOCK_DESIGN_1
//    char binaryStr1[20];
//    char binaryStr2[20];
//
//    uint16_t pmod1 = Xil_In16(PMOD1_IN);
//    uint16_t pmod2 = Xil_In16(PMOD2_IN);
//
//    // Reset both pmod
//	Xil_Out16(PMOD1_OUT, 0x10);
//	Xil_Out16(PMOD2_OUT, 0x10);
//
//    int count = 0;
//    while (1) {
//    	uint16_to_binary(pmod1, binaryStr1);
//    	uint16_to_binary(pmod2, binaryStr2);
//
//    	xil_printf("[LOG  ] (%d) PMOD1 values: 0b%s\n\r", count, binaryStr1);
//    	xil_printf("[LOG  ] (%d) PMOD2 values: 0b%s\n\r", count, binaryStr2);
//    	xil_printf("\n\r");
//    	sleep(1);
//
//    	pmod1 = Xil_In16(PMOD1_IN);
//    	pmod2 = Xil_In16(PMOD2_IN);
//
//    	// Put a 1 at pmod1 TX (bit 2)
//    	Xil_Out16(PMOD1_OUT, 0b100);
//    	// Put a 1 at pmod1 RTS (bit 0)
//    	Xil_Out16(PMOD1_OUT, 0b1);
//
//    	++count;
//    }
//#elif defined(VIVADO_BLOCK_DESIGN_2)
//
//#elif defined(VIVADO_BLOCK_DESIGN_3)
//    int ret;
//
//    // Setting up UART
//    XUartPs Uart_PS;
//    XUartPs_Config *uart_0_config = (XUartPs_Config*) malloc(sizeof(XUartPs_Config));
//    unsigned int sent_count = 0;
//    unsigned int received_count = 0;
//    int SEND_BUFFER_SIZE = 3 * 1/*000*/;	// Ignore why this is capitalized they used to be constants
//    int RECEIVE_BUFFER_SIZE = 3 * 1;		// Ignore why this is capitalized they used to be constants
//
//    uint8_t sendBuffer[SEND_BUFFER_SIZE];		/* Buffer for Transmitting Data */
//    uint8_t receiveBuffer[RECEIVE_BUFFER_SIZE];	/* Buffer for Receiving Data */
//
////	/* Auto config */
////	uart_0_config = XUartPs_LookupConfig(XPAR_PS7_UART_0_DEVICE_ID);
////	if (uart_0_config == NULL) {
////		LOGE("Error looking up uart config!");
////		return -1;
////	}
////
////	uart_0_status = XUartPs_CfgInitialize(&Uart_PS, uart_0_config, uart_0_config->BaseAddress);
////	if (uart_0_status != XST_SUCCESS) {
////		LOGE("Error initializing uart!");
////		return -1;
////	}
////
////	uart_0_status = XUartPs_SelfTest(&Uart_PS);
////	if (uart_0_status != XST_SUCCESS) {
////		LOGE("Error in uart self test!");
////		return -1;
////	}
//
//    ret = pmodBT2_init(&Uart_PS, uart_0_config);
//
//	LOGD("Hello :)");
//
//	/* Normal mode. Is this what we want? */
////	XUartPs_SetOperMode(&Uart_PS, XUARTPS_OPER_MODE_NORMAL);
//
////	/*
////	 * Initialize the send buffer bytes with a pattern and zero out
////	 * the receive buffer.
////	 */
////	for (int i = 0; i < TEST_BUFFER_SIZE; i++) {
//////		sendBuffer[i] = '0' + i;
////		sendBuffer[i] = 0xA;
////		receiveBuffer[i] = 0;
////	}
//
////_retry_send_$$$:
//	/*
//	 * Start PMOD to command mode by sending "$$$"
//	 *
//	 * Read: http://ww1.microchip.com/downloads/en/DeviceDoc/bluetooth_cr_UG-v1.0r.pdf
//	 */
//	sendBuffer[0] = '$';
//	sendBuffer[1] = '$';
//	sendBuffer[2] = '$';
////	sendBuffer[3] = '\0';
//
////	/* Block sending the buffer. */
////	sent_count = XUartPs_Send(&Uart_PS, sendBuffer, SEND_BUFFER_SIZE);
////	if (sent_count != SEND_BUFFER_SIZE) {
////		LOGE("sent_count != SEND_BUFFER_SIZE!");
////		goto _cleanup;
////	}
//
////	/*
////	 * Wait while the UART is sending the data so that we are guaranteed
////	 * to get the data the 1st time we call receive, otherwise this function
////	 * may enter receive before the data has arrived
////	 */
////	int loopCount = 0;
////	while (XUartPs_IsSending(&Uart_PS)) {
////		loopCount++;
////		LOGD("Loop count: %d", loopCount);
////	}
//
////	uint8_t temp = XUartPs_RecvByte(uart_0_config->BaseAddress);
////	uint8_t temp2 = XUartPs_RecvByte(uart_0_config->BaseAddress);
////	uint8_t temp3 = XUartPs_RecvByte(uart_0_config->BaseAddress);
//
////	const int MAX_RECEIVE_LOOP_COUNT = 100;
////	int receive_loop_count = 0;
////	received_count = 0;
////	while (received_count < RECEIVE_BUFFER_SIZE) {
////		received_count += XUartPs_Recv(&Uart_PS,
////									   &receiveBuffer[received_count],
//////									   (RECEIVE_BUFFER_SIZE - received_count)
////									   1 // One byte at a time
////									   );
////		LOGD("Receive count: %d\tReceiving stuff...", received_count);
////
////		++receive_loop_count;
////		if (receive_loop_count >= MAX_RECEIVE_LOOP_COUNT) {
////			LOGE("MAX_RECEIVE_LOOP_COUNT reached. Retrying to resend $$$.");
////			goto _retry_send_$$$;
////		}
////	}
////
////	// Null-lize the last byte
//////	receiveBuffer[] = 0;
////
////	LOGD("Receive Buffer:");
////	xil_printf(receiveBuffer);
////	xil_printf("\n\r");
//
//	int receiveBufferLen = RECEIVE_BUFFER_SIZE;
//	ret = pmodBT2_send(&Uart_PS, sendBuffer, SEND_BUFFER_SIZE, receiveBuffer, &receiveBufferLen);
//	if (ret < 0) {
//		LOGE("An error occurred when sending, error code: %d", ret);
//		goto _cleanup;
//	}
//
//	if (strncmp(receiveBuffer, "CMD\0", 4)) {
//		LOGI("CPU is connected to PmodBT2!");
//	} else {
//		LOGE("CPU failed to connect to PmodBT2!");
//		goto _cleanup;
//	}
//
//	char sendBuffer2[1] = "D";
//	int sendBuffer2Len = 1;
//	char *receiveBuffer2;
//	int receiveBuffer2Len = -1;
//
//	ret = pmodBT2_send(&Uart_PS, sendBuffer2, sendBuffer2Len, receiveBuffer2, &receiveBuffer2Len);
//	if (ret < 0) {
//		LOGE("An error occurred when sending, error code: %d", ret);
//		goto _cleanup;
//	}
//
//	LOGD("Received:");
//	xil_printf("%s", receiveBuffer2);
//
//	// If this prints, we jumped through all hoops above.
//	LOGI("End of program!");
//
//#endif
//
//// Bad bad coding practice... Only for testing purposes only.
//_cleanup:
//	// Clean up and exit.
//    cleanup_platform();
//    return 0;
//}
