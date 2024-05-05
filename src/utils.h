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
 * Ver   Who     Date	    Changes
 * ----- ------- ---------- ----------------------------------------------
 * 1.00	Jonathan 1/22/2024
 * 1.01 Jonathan 5/2/2024   Added FLASHING_SENDER and FLASHING_RECEIVER because there are 
 *                          two mains.
 *
*******************************************************************************************/


#ifndef UTILS_H
#define UTILS_H

#include "xil_printf.h"

// ##### Preprocessor and typedefs ##############################################

// Logging helper
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define LOGI(s, ...) xil_printf("[" ANSI_COLOR_BLUE "INFO" ANSI_COLOR_RESET " ] " s "\n\r", ##__VA_ARGS__)
#define LOGW(s, ...) xil_printf("[" ANSI_COLOR_YELLOW "WARNG" ANSI_COLOR_RESET "] " s "\n\r", ##__VA_ARGS__)
#define LOGE(s, ...) xil_printf("[" ANSI_COLOR_RED "ERROR" ANSI_COLOR_RESET "] " s "\n\r", ##__VA_ARGS__)
#define LOGD(s, ...) xil_printf("[" ANSI_COLOR_GREEN "DEBUG" ANSI_COLOR_RESET "] " s "\n\r", ##__VA_ARGS__)
#define LOGI_NNL(s, ...) xil_printf("[" ANSI_COLOR_BLUE "INFO" ANSI_COLOR_RESET " ] " s, ##__VA_ARGS__)		// No New Line
#define LOGW_NNL(s, ...) xil_printf("[" ANSI_COLOR_YELLOW "WARNG" ANSI_COLOR_RESET "] " s, ##__VA_ARGS__)	// No New Line
#define LOGE_NNL(s, ...) xil_printf("[" ANSI_COLOR_RED "ERROR" ANSI_COLOR_RESET "] " s, ##__VA_ARGS__)		// No New Line
#define LOGD_NNL(s, ...) xil_printf("[" ANSI_COLOR_GREEN "DEBUG" ANSI_COLOR_RESET "] " s, ##__VA_ARGS__)	// No New Line

//#define FLASHING_SENDER
#define FLASHING_RECEIVER

// ##############################################################################


// ##### Global Variable ########################################################
// ##############################################################################


// ##### Function Prototypes ####################################################
// ##############################################################################


#endif
