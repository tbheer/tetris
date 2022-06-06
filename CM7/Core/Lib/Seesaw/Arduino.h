/*
 * Arduino.h
 *
 *  Created on: Jun 3, 2022
 *      Author: Sven
 */

#ifndef SEESAW_ARDUINO_H_
#define SEESAW_ARDUINO_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

#include "Stream.h"

#include "stm32h7xx_hal.h"
#include "i2c.h"

typedef unsigned char byte;
typedef void Adafruit_SPIDevice;

#define LSBFIRST 0
#define MSBFIRST 1

#define HIGH 0x1
#define LOW  0x0

#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2

int digitalRead(uint8_t pin);
void delay(int delay);
void delayMicroseconds(int delay);
void yield();
uint8_t min(uint8_t a, uint8_t b);
long map(long x, long in_min, long in_max, long out_min, long out_max);
uint16_t constrain(uint16_t x, uint16_t a, uint16_t b);

typedef I2C_HandleTypeDef TwoWire;
//TwoWire* WireI2C = &hi2c1;

#ifdef __cplusplus
}
#endif

#endif /* SEESAW_ARDUINO_H_ */
