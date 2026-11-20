#pragma once
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>


extern Adafruit_BNO055 gyro;
extern int x;
extern int y;
extern int starster_x;


 extern int getX();
  extern int getY();
  extern int convert(int data);
  extern void changeX(int newx);
 extern  bool check_ot();
