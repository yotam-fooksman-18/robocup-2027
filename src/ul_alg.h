#pragma once
#include<Arduino.h>
#include<connections.h>
struct sensor{
    int tx;
    int rx;

};
sensor ul_sensor[4] = {{DST0,DSR0},{DST1,DSR1},{DST2,DSR2},{DST3,DSR3}};
sensor uls0={DST0,DSR0};
sensor uls1={DST1,DSR1};
sensor uls2={DST2,DSR2};    
sensor uls3={DST3,DSR3};
int measures[4] = {0,0,0,0};
int measure_distance(sensor ul_sensor);
int send_cord(sensor uls)
