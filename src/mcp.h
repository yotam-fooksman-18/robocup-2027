#pragma once
#include <Arduino.h>

void mcpBegin();
void mcpPinMode(uint8_t pin, uint8_t mode);   // pin 0-15, INPUT / OUTPUT / INPUT_PULLUP
void mcpDigitalWrite(uint8_t pin, bool val);
bool mcpDigitalRead(uint8_t pin);