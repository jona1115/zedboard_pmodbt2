/*******************************************************************************************
 *
 * Created by: Jonathan Tan (jona1115@iastate.edu)
 *
 * *****************************************************************************************
 *
 * @file receiver.c:
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

#ifdef VIVADO_BLOCK_DESIGN_1
#define PMOD1_IN XPAR_AXI_GPIO_0_BASEADDR
#define PMOD1_OUT XPAR_AXI_GPIO_1_BASEADDR
#define PMOD2_IN XPAR_AXI_GPIO_3_BASEADDR
#define PMOD2_OUT XPAR_AXI_GPIO_2_BASEADDR
#endif

#define BTN_C_PRESSED(a) ((a) & 1)
#define BTN_U_PRESSED(a) ((a) & 16)
#define BTN_D_PRESSED(a) ((a) & 2)
#define BTN_L_PRESSED(a) ((a) & 4)
#define BTN_R_PRESSED(a) ((a) & 8)

//#define VIVADO_BLOCK_DESIGN_1
//#define VIVADO_BLOCK_DESIGN_2
#define VIVADO_BLOCK_DESIGN_3

#ifdef FLASHING_RECEIVER
int main()
{
    init_platform();

    LOGI("Start of PmodBT2 receive program.");

    // Setting up UART
    int ret = 0;
    XUartPs Uart_PS;
    XUartPs_Config *uart_0_config = (XUartPs_Config*) malloc(sizeof(XUartPs_Config));
    unsigned int sent_count = 0;
    unsigned int received_count = 0;
    int SEND_BUFFER_SIZE = FRAME_SIZE + 3;	// Ignore why this is capitalized they used to be constants
    int RECEIVE_BUFFER_SIZE = FRAME_SIZE;		// Ignore why this is capitalized they used to be constants

    uint8_t sendBuffer[SEND_BUFFER_SIZE];		/* Buffer for Transmitting Data */
    uint8_t receiveBuffer[RECEIVE_BUFFER_SIZE];	/* Buffer for Receiving Data */

    ret = pmodBT2_init(&Uart_PS, uart_0_config);

    // Sit here and wait for a frame to come in
    LOGD("Waiting for frame...");

    int received_frame_len = -1;
    pmodBT2_receive_frame(&Uart_PS, receiveBuffer, &received_frame_len);

    xil_printf(receiveBuffer);

	// If this prints, we jumped through all hoops above.
	LOGI("Done receiving!!");

// Bad bad coding practice... Only for testing purposes only.
_cleanup:
	// Clean up and exit.
    cleanup_platform();
    return 0;
}
#endif
