#include<Arduino.h>
#include<connections.h>
#include<ul_alg.h>
#include<SoftwareSerial.h>
void init_ultrasonic(sensor ul_sensor){
  pinMode(ul_sensor.tx,OUTPUT);
  pinMode(ul_sensor.rx,INPUT);
}   
int measure_distance(sensor ul_sensor){
  SoftwareSerial US100(ul_sensor.rx, ul_sensor.tx);
  US100.begin(9600);
  US100.listen();

  while (US100.available() > 0) {
    US100.read();
  }

  US100.write(0x55);

  unsigned long start_time = millis();
  while (millis() - start_time < 100) {
    if (US100.available() >= 2) {
      byte high_byte = US100.read();
      byte low_byte = US100.read();
      return (high_byte << 8) | low_byte;
    }
  }

  return -1;
}
int send_cord(int oldX, int oldY){
  for (int i=0;i<4;i++){
    measures[i]=measure_distance(ul_sensors[i]);
  }
  int x,y;
if(oldX>0 && oldY>0){
  if (measures[0] == -1 || measures[1] == -1 || measures[2] == -1 || measures[3] == -1){return -1;}

  if (not(abs(oldX - ul_sensors_distance/2 -measures[1])> 30)){
    x = court_width - measures[1] - ul_sensors_distance/2;
  }else if(not(abs(oldX - ul_sensors_distance/2 -measures[3])> 30)){
    x = measures[3] + ul_sensors_distance/2;
  }else{
    x=oldX;
  }
  if(not(abs(oldY - ul_sensors_distance/2 -measures[2])> 30)){
    y = court_length - measures[2] - ul_sensors_distance/2;
  }else if(not(abs(oldY - ul_sensors_distance/2 -measures[0])> 30)){
    y = measures[0] + ul_sensors_distance/2;  
  }
else{
    y=oldY;
  }
}else{
x = court_width - measures[1] - ul_sensors_distance/2;
  y = court_length - measures[2] - ul_sensors_distance/2;
}
  x -= sensors_offset_x;
  y -= sensors_offset_y;

  return x,y;

}




  
    

