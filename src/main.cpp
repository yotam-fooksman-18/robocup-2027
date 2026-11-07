#include<Arduino.h>
#include <Servo.h>
#include<Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include "motor.h"
#include "mcp.h"
#include "Gyro.h"
#include "mcp.h"
Adafruit_BNO055 igyro = Adafruit_BNO055(55, 0x28, &Wire1);
Gyro gyro(igyro);
 Motor mFR(49,50,0);
 Motor mFL(51,52,0);
  Motor mBR(53,54,0);
   Motor mBL(55,56,0);


void setup(){
  Serial.begin(115200);
    Wire1.setSDA(17);
  Wire1.setSCL(16);
  Wire1.begin();
  mcp.begin();
    if (!igyro.begin()) Serial.println(F("Gyro missing!"));
   for (int i =49;i<57:i++){
    pinMode(i,OUTPUT);
   }

}
void loop(){

}