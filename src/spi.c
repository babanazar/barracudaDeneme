/*
 * spi.c
 *
 *  Created on: Jul 26, 2021
 *      Author: BABANAZAR
 */

#include "common_utils.h"
#include "spi.h"

/* Wait counter for wait operation monitoring */
static volatile uint32_t g_wait_count = MAX_COUNT;

/* Event flags for master and slave */
static volatile spi_event_t g_spi_event_flag;    // Master Transfer Event completion flag

/* SPI module buffers for Master and Slave */
static uint32_t g_master_tx_buff[BUFF_LEN];   // Master Transmit Buffer
static uint32_t g_master_rx_buff[BUFF_LEN];   // Master Receive Buffer
static uint32_t g_slave_tx_buff[BUFF_LEN];    // Slave Transmit Buffer
static uint32_t g_slave_rx_buff[BUFF_LEN];    // Slave Receive Buffer

uint8_t start = 0x0A;

uint8_t opcode_read = 0x80;
uint8_t opcode_write = 0x40;


fsp_err_t spi_init (spi_ctrl_t * p_api_ctrl, spi_cfg_t const * const p_cfg)
{
    fsp_err_t err = FSP_SUCCESS;     // Error status

    /* Open/Initialize SPI module */
    err = R_SCI_SPI_Open(p_api_ctrl, p_cfg);

    /* Handle Error */
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\n SCI_SPI open failed");
        APP_ERR_TRAP(err);
    }

    return err;
}

/*******************************************************************************************************************//**
 * @brief This function demos both R_SPI_Write() and R_SPI_Read() individually.
 * @param[IN]   None
 * @retval      FSP_SUCCESS                  Upon successful SPI Write and SPI Read
 * @retval      Any Other Error code apart from FSP_SUCCES  Unsuccessful Write and Read
 **********************************************************************************************************************/
fsp_err_t spi_write_and_read(void)
{
    fsp_err_t err = FSP_SUCCESS;     // Error status

    uint32_t num_bytes = RESET_VALUE;  // Number of bytes read by SEGGER real-time-terminal

    /* Cleaning buffers */
    memset(&g_master_tx_buff[0], NULL_CHAR, BUFF_LEN);
    memset(&g_master_rx_buff[0], NULL_CHAR, BUFF_LEN);
    memset(&g_slave_rx_buff[0], NULL_CHAR, BUFF_LEN);

    num_bytes = 4;

    /* Slave receive data from Master */
    err = R_SPI_Read(&g_spi0_ctrl, g_slave_rx_buff, num_bytes, SPI_BIT_WIDTH_16_BITS);
    /* Error handle */
    if(err != FSP_SUCCESS)
    {
        APP_ERR_PRINT("\r\nSlave R_SPI_Read() failed");
        return err;
    }

    /* Master send data to Slave */
    err = R_SPI_Write(&g_spi0_ctrl, 0x1100017, num_bytes, SPI_BIT_WIDTH_16_BITS);
    /* Error handle */
    if(FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\nMaster R_SPI_Write() failed");
        return err;
    }

    return err;
}


fsp_err_t write_to_EEPROM(uint8_t address)
{
    fsp_err_t err;

    uint32_t msg = 0x17;

    R_IOPORT_PinWrite(&g_ioport_ctrl, EEPROM_CS, BSP_IO_LEVEL_HIGH);

//    R_BSP_SoftwareDelay(5, BSP_DELAY_UNITS_MICROSECONDS);

    err = R_SPI_Write(&g_spi0_ctrl, &start, 1, SPI_BIT_WIDTH_16_BITS);

//    uint16_t writing = opcode_write | address;
//    err = R_SPI_Write(&g_spi0_ctrl, &writing, 2, SPI_BIT_WIDTH_16_BITS);

    /* Master send data to Slave */
//    err = R_SPI_Write(&g_spi0_ctrl, &msg, 1, SPI_BIT_WIDTH_16_BITS);
    /* Error handle */
    if(FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\nMaster R_SPI_Write() failed");
        return err;
    }
    R_IOPORT_PinWrite(&g_ioport_ctrl, EEPROM_CS, BSP_IO_LEVEL_LOW);
    return err;
}


fsp_err_t read_from_EEPROM(uint8_t address)
{
    fsp_err_t err;

    uint32_t read_value = 0x00;

    R_IOPORT_PinWrite(&g_ioport_ctrl, EEPROM_CS, BSP_IO_LEVEL_HIGH);

    /* Master send data to Slave */
    err = R_SPI_Write(&g_spi0_ctrl, &start, 4, SPI_BIT_WIDTH_16_BITS);

    uint16_t reading = opcode_read | address;

    err = R_SPI_Write(&g_spi0_ctrl, &reading, 2, SPI_BIT_WIDTH_16_BITS);

    /* Read from SPI */
    err = R_SPI_Read(&g_spi0_ctrl, &read_value, 4, SPI_BIT_WIDTH_16_BITS);

    R_IOPORT_PinWrite(&g_ioport_ctrl, EEPROM_CS, BSP_IO_LEVEL_LOW);

    /* Error handle */
    if(FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\nMaster R_SPI_Write() failed");
        return err;
    }
    return err;
}


void spi_callback(spi_callback_args_t *p_args)
{
    if (SPI_EVENT_TRANSFER_COMPLETE == p_args->event)
    {
        g_spi_event_flag = SPI_EVENT_TRANSFER_COMPLETE;
    }
    else
    {
        g_spi_event_flag = SPI_EVENT_TRANSFER_ABORTED;
    }
}
