/***********************************************************************************************************************
 * File Name    : uart.h
 * Description  : Contains function declaration of uart.c and Macros.
 *  Created on  : Jul 13, 2021
 *      Author  : BABANAZAR
 **********************************************************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "hal_data.h"

/* Macro definition */
#define CARRIAGE_ASCII            (0x13)     /* Carriage return */
#define DATA_LENGTH               (4u)      /* Expected Input Data length */
#define UART_ERROR_EVENTS         (UART_EVENT_BREAK_DETECT | UART_EVENT_ERR_OVERFLOW | UART_EVENT_ERR_FRAMING | \
                                    UART_EVENT_ERR_PARITY)    /* UART Error event bits mapped in registers */

/* Temporary buffer to save data from receive buffer for further processing */
static uint8_t g_temp_buffer[DATA_LENGTH] = {RESET_VALUE};

/* Function declaration */
fsp_err_t uart_initialize(uart_ctrl_t * const p_api_ctrl, uart_cfg_t const * const p_cfg);
fsp_err_t uart_print(uint8_t *p_msg);
void deinit_uart(uart_ctrl_t * const p_api_ctrl);
uint8_t get_lock_data_received_flag(void);
void set_lock_data_received_flag(uint8_t value);


#endif /* UART_H_ */
