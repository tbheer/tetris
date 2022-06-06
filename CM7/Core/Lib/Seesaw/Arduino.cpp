/*
 * Arduino.c
 *
 *  Created on: Jun 3, 2022
 *      Author: Sven
 */

#include "Arduino.h"

void delay(int delay)
{
  HAL_Delay(delay);
}

void delayMicroseconds(int delay)
{
  HAL_Delay(1);
}

void yield()
{
  // If RTOS: One could implement yield();
}

uint8_t min(uint8_t a, uint8_t b)
{
  return a < b ? a : b ;
}

long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

uint16_t constrain(uint16_t x, uint16_t a, uint16_t b) {
    if(x < a) {
        return a;
    }
    else if(b < x) {
        return b;
    }
    else
        return x;
}

int digitalRead(uint8_t pin){

 return 0x01;
}
