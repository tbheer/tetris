#pragma once

#include "main.h"

void setUpField();
uint8_t writeState(char *text, uint16_t color);
uint8_t writeScore(uint32_t score, uint16_t color);
void setPreview(uint8_t block);
void drawPreview(uint16_t x, uint16_t y, uint16_t setFields, uint16_t color);
void drawField(uint8_t * fieldData);
uint16_t getColor(uint8_t color);
