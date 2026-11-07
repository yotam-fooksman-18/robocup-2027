#include"Motor.h"
#include <Arduino.h>
Motor::Motor(const int IN1p,const int IN2p, int offs) : IN1pin(IN1p),IN2pin(IN1p),offset(offs){};
void Motor::move(int in1,bool in2){
if(in1!= 0 && in2!=0){
    Serial.println("Error - motor double HIGH");
    return;
}
analogWrite(IN1pin,in1);
analogWrite(IN2pin,in2);
}
void Motor::move_int(int speed){
if (speed>0){
    move(speed,0);
}else{
        move(0,speed);
}
}