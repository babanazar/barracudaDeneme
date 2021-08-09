/*
 * spi.h
 *
 *  Created on: Jul 26, 2021
 *      Author: BABANAZAR
 */

#ifndef SPI_H_
#define SPI_H_

#include "hal_data.h"

/* SPI buffer length */
#define BUFF_LEN 32

/* Max wait count for time-out operation */
#define MAX_COUNT 0xFFFFFF

/* MACRO for null character */
#define NULL_CHAR   '\0'

fsp_err_t spi_init (spi_ctrl_t * p_api_ctrl, spi_cfg_t const * const p_cfg);
fsp_err_t spi_write_and_read(void);

fsp_err_t write_to_EEPROM(uint8_t address);

fsp_err_t read_from_EEPROM(uint8_t address);

#endif /* SPI_H_ */
