#pragma once
#include<Arduino.h>

struct option{
    char name[20];
    int num;
    void (*action)();   
};
option options[4] = {{'calibrate gyro',1},{'switch goals',2},{'ball values',3},{'D',4}};
void init_screen();
void display_menu(option *optionsP);