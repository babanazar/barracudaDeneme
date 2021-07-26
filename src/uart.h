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
#define LINEFEED_ASCII            (0x10)     /* Line feed */
#define CARRIAGE_ASCII            (0x13)     /* Carriage return */
#define DATA_LENGTH               (1024u)      /* Expected Input Data length */
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
void user_uart_callback_L86(uart_callback_args_t *p_args);
void set_L86_data_received_flag(uint8_t value);
uint8_t get_L86_data_received_flag(void);
fsp_err_t send_to_ble(uint8_t *p_msg);
void set_uart_baud_rate(uart_ctrl_t * const p_api_ctrl, uint32_t baudrate);
fsp_err_t send_to_simcom(uint8_t *p_msg);


#endif /* UART_H_ */
