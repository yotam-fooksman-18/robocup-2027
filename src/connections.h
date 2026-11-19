#pragma once
#include<Arduino.h>
#define SDA0p  18
#define SCL0p  19
#define SDA1p  17
#define SCL1p  16
#define DST0 15
#define DSR0 14
#define DST1 0
#define DSR1 1
#define DST2 24  
#define DSR2 25 
#define DST3 28
#define DSR3 29 
#define REAp A12
#define REBp A13
#define CDMISO 12
#define CDMOSI 11
#define CDSCK 13
#define CDIRQ 22
#define CDCE 3
#define CDCSN 2
#define M1A 6
#define M1B 37
#define M2A 7
#define M2B 10
#define M3A 8
#define M3B 4
#define M4A 9
#define M4B 28
extern int court_width = 1200;
extern int court_length = 2000;
extern int goal_distance = 1950;
constexpr int sensors_offset_y = 60;
constexpr int sensors_offset_x = 20;
constexpr int ul_sensors_distance = 50;
constexpr int8_t table[16] = {
   0, -1,  1,  0,
   1,  0,  0, -1,
  -1,  0,  0,  1,
   0,  1, -1,  0
};
constexpr uint8_t PIN_A  = 26;
constexpr uint8_t PIN_B  = 27;
constexpr uint8_t PIN_SW = 4;
constexpr int8_t TRANSITIONS_PER_CLICK = 4;
volatile int32_t count = 0;
volatile int8_t  sub = 0;
volatile uint8_t prev = 0;

