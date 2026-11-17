#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>
#include "connections.h"
#include"screen_manage.h"
#include"Gyro.h"
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

void update_screen(int size){
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

