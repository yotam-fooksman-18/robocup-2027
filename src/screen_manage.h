#pragma once
#include<Arduino.h>

struct option{
const char *name; 
   int num;
    void (*action)();   
};




void init_screen();
void display_menu(option optionsP[],int size);
void onEncoder();
void encoder_begin();
void update_screen();
void calibrate_gyro();
void change_ul_distance();
void back();
void set_ul(int num);
void ball_values();

void switch_goals();
extern int menu_number;
extern option options[4];
extern option ul_options[4];