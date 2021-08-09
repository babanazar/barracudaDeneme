/*
 * File Name    : uart.c
 * Description  : Contains UART functions definition.
 *
 *  Created on  : Jul 13, 2021
 *  Author      : BABANAZAR
 */

#include "common_utils.h"
#include "uart.h"


/*
 * @addtogroup r_sci_uart
 * @{
 */

/*
 * Private function declarations
 */

/*
 * Private global variables
 */


/* Counter to update g_temp_buffer index */
static volatile uint32_t g_counter_variable = RESET_VALUE;

/* Flag to check whether data is received or not */
static volatile uint8_t g_lock_data_received_flag = false;

/* Flag for LOCK UART callback */
static volatile uint8_t g_lock_uart_event = RESET_VALUE;

/* Flag for BLE UART callback */
static volatile uint8_t g_ble_uart_event = RESET_VALUE;

/* Flag for SIM7500 UART callback */
static volatile uint8_t g_simcom_uart_event = RESET_VALUE;

/* Flag to check whether data is received or not */
static volatile uint8_t g_l86_data_received_flag = false;

/* Flag for LOCK UART callback */
static volatile uint8_t g_l86_uart_event = RESET_VALUE;

/*
 * @brief       Initialize UART.
 * @param[in]   None
 * @retval      FSP_SUCCESS Upon successful open and start of UART
 * @retval      Any other error code apart from FSP_SUCCESS upon unsuccessful open.
 */
fsp_err_t uart_initialize(uart_ctrl_t * const p_api_ctrl, uart_cfg_t const * const p_cfg)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Initialize UART channel with baud rate 115200 */
    err = R_SCI_UART_Open(p_api_ctrl, p_cfg);
    if(FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\n** R_SCI_UART_Open API failed  **\r\n");
    }
    return err;
}

/*
 * @brief       print user message to terminal
 * @param[in]   p_msg
 * @retval      FSP_SUCCESS                 Upon success
 * @retval      FSP_ERR_TRANSFER_ABORTED    Upon event failure
 * @retval      Any Other Error code apart from FSP_SUCCESS,  Unsuccessful write operation
 */
fsp_err_t uart_print(uint8_t *p_msg)
{
    fsp_err_t err = FSP_SUCCESS;
    uint8_t message_length = RESET_VALUE;
    uint32_t local_timeout = (DATA_LENGTH * UINT16_MAX);
    char *p_temp_ptr = (char *)p_msg;

    /* Calculate length of message received */
    message_length = ((uint8_t)(strlen(p_temp_ptr)));

    /* Reset callback capture variable */
    g_lock_uart_event = RESET_VALUE;

    /* Writing to terminal */
    err = R_SCI_UART_Write(&UART_LOCK_ctrl, p_msg, message_length);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\n**  R_SCI_UART_Write API Failed  **\r\n");
        return err;
    }

    /* Check for event transfer complete */
    while ((UART_EVENT_TX_COMPLETE != g_lock_uart_event) && (--local_timeout))
    {
        /* Check if any error event occurred */
        if (UART_ERROR_EVENTS == g_lock_uart_event)
        {
            APP_ERR_PRINT ("\r\n**  UART Error Event Received  **\r\n");
            return FSP_ERR_TRANSFER_ABORTED;
        }
    }
    if(RESET_VALUE == local_timeout)
    {
        err = FSP_ERR_TIMEOUT;
    }
    return err;
}


/*
 * @brief       send user command to BLE
 * @param[in]   p_msg
 * @retval      FSP_SUCCESS                 Upon success
 * @retval      FSP_ERR_TRANSFER_ABORTED    Upon event failure
 * @retval      Any Other Error code apart from FSP_SUCCESS,  Unsuccessful write operation
 */
fsp_err_t send_to_ble(uint8_t *p_msg)
{
    fsp_err_t err = FSP_SUCCESS;
    uint8_t message_length = RESET_VALUE;
    uint32_t local_timeout = (DATA_LENGTH * UINT16_MAX);
    char *p_temp_ptr = (char *)p_msg;

    /* Calculate length of message received */
    message_length = ((uint8_t)(strlen(p_temp_ptr)));

    /* Reset callback capture variable */
    g_ble_uart_event = RESET_VALUE;

    /* Writing to terminal */
    err = R_SCI_UART_Write(&UART_BLE_ctrl, p_msg, message_length);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\n**  R_SCI_UART_Write API Failed  **\r\n");
        return err;
    }

    /* Check for event transfer complete */
    while ((UART_EVENT_TX_COMPLETE != g_ble_uart_event) && (--local_timeout))
    {
        /* Check if any error event occurred */
        if (UART_ERROR_EVENTS == g_ble_uart_event)
        {
            APP_ERR_PRINT ("\r\n**  UART Error Event Received  **\r\n");
            return FSP_ERR_TRANSFER_ABORTED;
        }
    }
    if(RESET_VALUE == local_timeout)
    {
        err = FSP_ERR_TIMEOUT;
    }
    return err;
}

/*
 * @brief   Send AT command to SIM7500
 * @param[in]
 * @retval
 */
fsp_err_t send_to_simcom(uint8_t *p_msg)
{
    fsp_err_t err = FSP_SUCCESS;
    uint8_t message_length = RESET_VALUE;
    uint32_t local_timeout = (DATA_LENGTH * UINT16_MAX);
    char *p_temp_ptr = (char *)p_msg;

    /* Calculate length of message received */
    message_length = ((uint8_t)(strlen(p_temp_ptr)));

    /* Reset callback capture variable */
    g_simcom_uart_event = RESET_VALUE;

        /* Writing to terminal */
        err = R_SCI_UART_Write(&UART_SIMCOM_ctrl, p_msg, message_length);
        if (FSP_SUCCESS != err)
        {
            APP_ERR_PRINT("\r\n**  R_SCI_UART_Write API Failed  **\r\n");
            return err;
        }

        /* Check for event transfer complete */
        while ((UART_EVENT_TX_COMPLETE != g_simcom_uart_event) && (--local_timeout))
        {
            /* Check if any error event occurred */
            if (UART_ERROR_EVENTS == g_simcom_uart_event)
            {
                APP_ERR_PRINT ("\r\n**  UART Error Event Received  **\r\n");
                return FSP_ERR_TRANSFER_ABORTED;
            }
        }
        if(RESET_VALUE == local_timeout)
        {
            err = FSP_ERR_TIMEOUT;
        }
        return err;
}

/*
 *  @brief       Deinitialize SCI UART module
 *  @param[in]   None
 *  @retval      None
 */
void deinit_uart(uart_ctrl_t * const p_api_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Close module */
    err =  R_SCI_UART_Close (p_api_ctrl);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT ("\r\n**  R_SCI_UART_Close API failed  ** \r\n");
    }
}

/*
 * @brief   Set baud rate for a uart communication
 * @
 */
void set_uart_baud_rate(uart_ctrl_t * const p_api_ctrl, uint32_t baudrate)
{
    baud_setting_t baud_setting;
    bool enable_bitrate_modulation = false;
    uint32_t error_rate_x_1000 = 500;

    fsp_err_t err = R_SCI_UART_BaudCalculate(baudrate, enable_bitrate_modulation, error_rate_x_1000, &baud_setting);

    assert(FSP_SUCCESS == err);

    err = R_SCI_UART_BaudSet(p_api_ctrl, (void *) &baud_setting);
    assert(FSP_SUCCESS == err);
}

/*
 * @brief       LOCK UART user callback
 * @param[in]   p_args
 * @retval      None
 */
void user_uart_callback_LOCK(uart_callback_args_t *p_args)
{

    /* Logged the event in global variable */
    g_lock_uart_event = (uint8_t)p_args->event;

    /* Reset g_temp buffer index if it exceeds the buffer size */
    if(DATA_LENGTH == g_counter_variable)
    {
        g_counter_variable = RESET_VALUE;
    }

    if(UART_EVENT_RX_CHAR == p_args->event)
    {
        switch (p_args->data)
        {
            /* If Enter is pressed by user, set flag to process the data */
            case CARRIAGE_ASCII:
            {
                g_counter_variable = RESET_VALUE;
                g_lock_data_received_flag = true;
                break;
            }
            /* Read all data provided by user until enter button is pressed */
            default:
            {
                g_temp_buffer[g_counter_variable++] = (uint8_t) p_args -> data;
                break;
            }
        }
    }

}

/*
 * @brief       SIMCOM UART user callback
 * @param[in]   p_args
 * @retval      None
 * */
void user_uart_callback_SIMCOM(uart_callback_args_t *p_args)
{
        /* Logged the event in global variable */
        g_simcom_uart_event = (uint8_t)p_args->event;

        /* Reset g_temp buffer index if it exceeds the buffer size */
        if(DATA_LENGTH == g_counter_variable)
        {
            g_counter_variable = RESET_VALUE;
        }

        if(UART_EVENT_RX_CHAR == p_args->event)
        {
            g_temp_buffer[g_counter_variable++] = (uint8_t) p_args -> data;
        }
        else if(UART_EVENT_RX_COMPLETE == p_args->event)
        {
            g_counter_variable = RESET_VALUE;
            g_lock_data_received_flag = true;
        }
}

/*
 * @brief       Get lock data received flag
 * @param[in]   None
 * @retval      Lock data received flag
 */
uint8_t get_lock_data_received_flag(void)
{
    return g_lock_data_received_flag;
}

/*
 * @brief       Set lock data received flag
 * @param[in]   value: to set as lock data received flag
 * @retval      None
 */
void set_lock_data_received_flag(uint8_t value)
{
    g_lock_data_received_flag = value;
}

/*
 * @brief       Get L86 data received flag
 * @param[in]   None
 * @retval      L86 data received flag
 */
uint8_t get_L86_data_received_flag(void)
{
    return g_l86_data_received_flag;
}


/*
 * @brief       Set L86 data received flag
 * @param[in]   value: to set as L86 data received flag
 * @retval      None
 */
void set_L86_data_received_flag(uint8_t value)
{
    g_l86_data_received_flag = value;
}

/*
 * @brief       L86 UART user callback
 * @param[in]   p_args
 * @retval      None
 */
void user_uart_callback_L86(uart_callback_args_t *p_args)
{
    /* Logged the event in global variable */
    g_l86_uart_event = (uint8_t)p_args->event;

    /* Reset g_temp buffer index if it exceeds the buffer size */
    if(DATA_LENGTH == g_counter_variable)
    {
        g_counter_variable = RESET_VALUE;
    }

    if(UART_EVENT_RX_CHAR == p_args->event)
    {
        switch (p_args->data)
        {
            case '\n':
            {
                g_counter_variable = RESET_VALUE;
                g_l86_data_received_flag = true;
                break;
            }
            default:
            {
                g_temp_buffer[g_counter_variable++] = (uint8_t) p_args -> data;
                break;
            }
        }
    }

}

/*
 * @brief       BLE UART user callback
 * @param[in]   p_args
 * @retval      None
 */
void user_uart_callback_BLE(uart_callback_args_t *p_args){
    /* Logged the event in global variable */
   g_l86_uart_event = (uint8_t)p_args->event;

   /* Reset g_temp buffer index if it exceeds the buffer size */
   if(DATA_LENGTH == g_counter_variable)
   {
       g_counter_variable = RESET_VALUE;
   }

   if(UART_EVENT_RX_COMPLETE == p_args->event)
   {
       g_lock_data_received_flag = true;
   }

   if(UART_EVENT_RX_CHAR == p_args->event)
   {
       switch (p_args->data)
       {
           /* If Enter is pressed by user, set flag to process the data */
           case CARRIAGE_ASCII:
           {
               g_counter_variable = RESET_VALUE;
               g_lock_data_received_flag = true;
               break;
           }
           /* Read all data provided by user until enter button is pressed */
           default:
           {
               g_temp_buffer[g_counter_variable++] = (uint8_t) p_args -> data;
               break;
           }
       }
   }
}

/*******************************************************************************************************************//**
 * @} (end addtogroup r_sci_uart_ep)
 **********************************************************************************************************************/
