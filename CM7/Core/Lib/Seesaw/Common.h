/*
 * Commons.h
 *
 *  Created on: Jun 3, 2022
 *      Author: Sven
 */

#ifndef SEESAW_COMMON_H_
#define SEESAW_COMMON_H_

#include "stm32h7xx_hal.h"

uint32_t millis()
{
  return HAL_GetTick();
}

#endif /* SEESAW_COMMON_H_ */
