#pragma once
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>


class Gyro{
// gyro.setExtCrystalUse(true);
private:
  Adafruit_BNO055& _bno;
int x;
int y;
int starter_x;
public:
  Gyro(Adafruit_BNO055& bno);
  int getX();
  int getY();
  int convert(int data);
  void changeX(int newx);
  bool check_ot();
};