#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>
#include "connections.h"
#include "ul_alg.h"
#include"screen_manage.h"
#include"Gyro.h"
int menu_number = 1;
option options[4] = {
  {"calibrate gyro",     1, calibrate_gyro},
  {"switch goals",       2, switch_goals},
  {"ball values",        3, ball_values},
  {"Change ul distance", 4, change_ul_distance}
};

option ul_options[4] = {
  {"set width",     1, []{ set_ul(0); }},
  {"set length",    2, []{ set_ul(1); }},
  {"set goal dist", 3, []{ set_ul(2); }},
  {"back",          4, back}
};
 U8G2_SSD1327_WS_128X128_1_HW_I2C display(U8G2_R0, U8X8_PIN_NONE);
void init_screen() {
 


  // 1) I2C scan: prints the address of anything connected
  for (uint8_t a = 1; a < 127; a++) {
    Wire.beginTransmission(a);
    if (Wire.endTransmission() == 0) {
      Serial.print(F("Found I2C device at 0x"));
      Serial.println(a, HEX);
    }
  }

  // 2) Init the screen and draw a border + text
  display.begin();
  // display.setI2CAddress(0x7A);   // use this if the scan found 0x3D

  display.firstPage();
  do {
    display.setFont(u8g2_font_6x12_tr);
    display.drawFrame(0, 0, 128, 128);   // border shows if the whole area is visible
    display.drawStr(10, 20, "Hello Yotam!");
  } while (display.nextPage());
}
void display_menu(option optionsP[],int size){
display.clearBuffer();
for(int i = 0; i < size; i++){
    display.setCursor(0, 0); 
    display.drawStr(0, 12*i, optionsP[i].name);
}

}
void onEncoder() {   // runs on every A/B change
  prev = ((prev << 2) | (digitalRead(PIN_A) << 1) | digitalRead(PIN_B)) & 0x0F;
  sub += table[prev];

  if (sub >= TRANSITIONS_PER_CLICK)       { count++; sub = 0; }
  else if (sub <= -TRANSITIONS_PER_CLICK) { count--; sub = 0; }
}
void encoder_begin(){
    pinMode(PIN_A, INPUT_PULLUP);
  pinMode(PIN_B, INPUT_PULLUP);
  pinMode(PIN_SW, INPUT_PULLUP);

  prev = (digitalRead(PIN_A) << 1) | digitalRead(PIN_B);
  attachInterrupt(digitalPinToInterrupt(PIN_A), onEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_B), onEncoder, CHANGE);
}

void update_screen(){
  int size;
  option *options;
  switch(menu_number){
    case 1:
      options = options;
      size = 4;
      break;
    case 2:
      options = ul_options;
      size = 3;
      break;
  }
  display_menu(options,size);
  static int32_t lastCount = 0;
  static bool lastPressed = false;

  noInterrupts();
  int32_t c = count;
  interrupts();

  bool pressed = (digitalRead(PIN_SW) == LOW);

  if (c != lastCount) {
    Serial.print(F("Count: "));
    Serial.println(c);
    lastCount = c;
  }
  if (pressed != lastPressed) {
    Serial.println(pressed ? F("Button pressed") : F("Button released"));
    lastPressed = pressed;
    delay(20);   // crude debounce
  }
  int selectedOption = c % size;
  display.drawDisc(108,selectedOption , 20);       
  if (pressed) {
    options[selectedOption].action();
  }
}
void calibrate_gyro(){
  Serial.println("Calibrating gyro...");
  changeX(getX());
}

void change_ul_distance(){
 menu_number = 2;
 update_screen();
}
void set_ul(int num){

  switch(num){
    case 0:
      Serial.println("Setting width");
     court_width = change_dimentions(0);
      break;
    case 1:
      Serial.println("Setting length");
      court_length = change_dimentions(1);
      break;
    case 2:
      Serial.println("Setting goal distance");
      goal_distance = measures[1];
      break;
  }

}