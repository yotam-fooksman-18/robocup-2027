#pragma once
#include<Arduino.h>

struct option{
    char name[20];
    int num;
    void (action)();   
};




void init_screen();
void display_menu(option optionsP[]);
void onEncoder();
void encoder_begin();
void update_screen();
void calibrate_gyro();
option options[4] = {{'calibrate gyro', 1 ,'calibrate_gyro'},{'switch goals', 2 ,'switch_goals'},{'ball values', 3, 'ball_values'},{'D', 4 ,'something'}};
