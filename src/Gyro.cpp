#include"Gyro.h"
#include"main.cpp"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

// Gyro(Adafruit_BNO055& bno) : _bno(bno) {}
int getX(){
    sensors_event_t event; 
 gyro.getEvent(&event);
 int x = event.orientation.x;

  return x;
}
int getY(){
    sensors_event_t event; 
 gyro.getEvent(&event);
 int  y = event.orientation.y;
  Serial.println(y);
  return y;
}
int convert(int data){
  if (data> 180) data-=360;
  return data;
}
void changeX(int newx){
  starter_x = newx;
}
bool check_ot(){
  int nx = getX();
 if (abs(nx - starter_x) < 10){
  return true;
 }else{
  return false;
 }
}


