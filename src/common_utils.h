/*
 * common_utils.h
 *
 *  Created on: Jul 13, 2021
 *      Author: BABANAZAR
 */

#ifndef COMMON_UTILS_H_
#define COMMON_UTILS_H_

/* generic headers */
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

/* SEGGER RTT and error related headers */
#include "SEGGER_RTT/SEGGER_RTT.h"


#define LVL_ERR      (1u)       /* error conditions   */

#define RESET_VALUE             (0x00)

#define SEGGER_INDEX            (0)

#define APP_PRINT(fn_, ...)     SEGGER_RTT_printf (SEGGER_INDEX, "[DEBUG] In Function: %s(), %s", __FUNCTION__, (fn_), ##__VA_ARGS__);

#define APP_ERR_PRINT(fn_, ...)  if(LVL_ERR)\
        SEGGER_RTT_printf (SEGGER_INDEX, "[ERR] In Function: %s(), %s",__FUNCTION__,(fn_),##__VA_ARGS__);

#endif /* COMMON_UTILS_H_ */
