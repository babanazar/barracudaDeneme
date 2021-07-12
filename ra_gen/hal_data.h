/* generated HAL header file - do not edit */
#ifndef HAL_DATA_H_
#define HAL_DATA_H_
#include <stdint.h>
#include "bsp_api.h"
#include "common_data.h"
#include "r_gpt.h"
#include "r_timer_api.h"
#include "r_adc.h"
#include "r_adc_api.h"
#include "r_sci_uart.h"
#include "r_uart_api.h"
FSP_HEADER
/** Timer on GPT Instance. */
extern const timer_instance_t PWM_BLUE;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t PWM_BLUE_ctrl;
extern const timer_cfg_t PWM_BLUE_cfg;

#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t PWM_GREEN;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t PWM_GREEN_ctrl;
extern const timer_cfg_t PWM_GREEN_cfg;

#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t PWM_RED;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t PWM_RED_ctrl;
extern const timer_cfg_t PWM_RED_cfg;

#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif
/** ADC on ADC Instance. */
extern const adc_instance_t ANALOGPINS;

/** Access the ADC instance using these structures when calling API functions directly (::p_api is not used). */
extern adc_instance_ctrl_t ANALOGPINS_ctrl;
extern const adc_cfg_t ANALOGPINS_cfg;
extern const adc_channel_cfg_t ANALOGPINS_channel_cfg;

#ifndef NULL
void NULL(adc_callback_args_t *p_args);
#endif

#define ADC_DMAC_CHANNELS_PER_BLOCK_NULL  6
/** UART on SCI Instance. */
extern const uart_instance_t UART_L86;

/** Access the UART instance using these structures when calling API functions directly (::p_api is not used). */
extern sci_uart_instance_ctrl_t UART_L86_ctrl;
extern const uart_cfg_t UART_L86_cfg;
extern const sci_uart_extended_cfg_t UART_L86_cfg_extend;

#ifndef user_uart_callback_L86
void user_uart_callback_L86(uart_callback_args_t *p_args);
#endif
/** UART on SCI Instance. */
extern const uart_instance_t UART_SCOOTER;

/** Access the UART instance using these structures when calling API functions directly (::p_api is not used). */
extern sci_uart_instance_ctrl_t UART_SCOOTER_ctrl;
extern const uart_cfg_t UART_SCOOTER_cfg;
extern const sci_uart_extended_cfg_t UART_SCOOTER_cfg_extend;

#ifndef user_uart_callback_SCOOTER
void user_uart_callback_SCOOTER(uart_callback_args_t *p_args);
#endif
/** UART on SCI Instance. */
extern const uart_instance_t UART_BLE;

/** Access the UART instance using these structures when calling API functions directly (::p_api is not used). */
extern sci_uart_instance_ctrl_t UART_BLE_ctrl;
extern const uart_cfg_t UART_BLE_cfg;
extern const sci_uart_extended_cfg_t UART_BLE_cfg_extend;

#ifndef user_uart_callback_BLE
void user_uart_callback_BLE(uart_callback_args_t *p_args);
#endif
/** UART on SCI Instance. */
extern const uart_instance_t UART_SIMCOM;

/** Access the UART instance using these structures when calling API functions directly (::p_api is not used). */
extern sci_uart_instance_ctrl_t UART_SIMCOM_ctrl;
extern const uart_cfg_t UART_SIMCOM_cfg;
extern const sci_uart_extended_cfg_t UART_SIMCOM_cfg_extend;

#ifndef user_uart_callback_SIMCOM
void user_uart_callback_SIMCOM(uart_callback_args_t *p_args);
#endif
/** UART on SCI Instance. */
extern const uart_instance_t UART_LOCK;

/** Access the UART instance using these structures when calling API functions directly (::p_api is not used). */
extern sci_uart_instance_ctrl_t UART_LOCK_ctrl;
extern const uart_cfg_t UART_LOCK_cfg;
extern const sci_uart_extended_cfg_t UART_LOCK_cfg_extend;

#ifndef user_uart_callback_LOCK
void user_uart_callback_LOCK(uart_callback_args_t *p_args);
#endif
void hal_entry(void);
void g_hal_init(void);
FSP_FOOTER
#endif /* HAL_DATA_H_ */
