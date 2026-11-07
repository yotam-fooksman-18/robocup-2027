#include"Gyro.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

Gyro::Gyro(Adafruit_BNO055& bno) : _bno(bno) {}
int Gyro::getX(){
    sensors_event_t event; 
 _bno.getEvent(&event);
 int x = event.orientation.x;

  return x;
}
int Gyro::getY(){
    sensors_event_t event; 
 _bno.getEvent(&event);
 int  y = event.orientation.y;
  Serial.println(y);
  return y;
}
int Gyro::convert(int data){
  if (data> 180) data-=360;
  return data;
}
void Gyro::changeX(int newx){
  starter_x = newx;
}
bool Gyro::check_ot(){
  int nx = getX();
 if (abs(nx - starter_x) < 10){
  return true;
 }else{
  return false;
 }
}


