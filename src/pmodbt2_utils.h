/*******************************************************************************************
 *
 * Created by: Jonathan Tan (jona1115@iastate.edu)
 *
 * *****************************************************************************************
 *
 * @file pmodbt2_utils.h:
 *
 * MODIFICATION HISTORY:
 *
 * Ver   Who    Date	 Changes
 * ----- ------ -------- ----------------------------------------------
 * 1.00	Jonathan
 *
*******************************************************************************************/


#ifndef PMODBT2_UTILS_H
#define PMODBT2_UTILS_H

//#define FRAME_SIZE 106*60+1 // 106*60 + Null Byte
#define FRAME_SIZE 10

int pmodBT2_init(XUartPs* Uart_PS,
				 XUartPs_Config* uart_0_config);

int pmodBT2_send_and_receive(XUartPs* Uart_PS,
						 	 char* givenSendBuffer, int givenSendBufferLen,
							 char* givenReceiveBuffer, int* givenReceiveBufferLen);

int pmodBT2_send_and_just_send(XUartPs* Uart_PS,
							   char* givenSendBuffer, int givenSendBufferLen);

int pmodBT2_receive_frame(XUartPs* Uart_PS,
						  char* givenReceiveBuffer, int* givenReceiveBufferLen);

#endif
