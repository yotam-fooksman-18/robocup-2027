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
int send_cord(){
  for (int i=0;i<4;i++){
    measures[i]=measure_distance(ul_sensors[i]);

  }
  
    
}
