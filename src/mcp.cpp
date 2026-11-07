#include <Wire.h>

#define MCP_ADDR 0x20

// Register addresses (IOCON.BANK = 0, the default)
#define IODIRA 0x00
#define IODIRB 0x01
#define GPPUB  0x0D
#define GPIOA  0x12
#define GPIOB  0x13

void mcpWrite(uint8_t reg, uint8_t val) {
  Wire.beginTransmission(MCP_ADDR);
  Wire.write(reg);
  Wire.write(val);
  Wire.endTransmission();
}

uint8_t mcpRead(uint8_t reg) {
  Wire.beginTransmission(MCP_ADDR);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom((uint8_t)MCP_ADDR, (uint8_t)1);
  return Wire.read();
}

void setup() {
  Wire.begin();
  Wire.setClock(400000);

  mcpWrite(IODIRA, 0x00);  // port A: all outputs
  mcpWrite(IODIRB, 0xFF);  // port B: all inputs
  mcpWrite(GPPUB, 0xFF);   // port B: internal pull-ups on
}
void mcpBegin() {
  Wire.begin();
  Wire.setClock(400000);

  // Safe default: everything input until you set modes
  Wire.beginTransmission(MCP_ADDR);
  Wire.write(IODIRA);
  Wire.write(0xFF);   // IODIRA
  Wire.write(0xFF);   // IODIRB (address auto-increments in the default mode)
  Wire.endTransmission();
}
void loop() {
  mcpWrite(GPIOA, 0xFF);   // all A pins high
  delay(500);
  mcpWrite(GPIOA, 0x00);   // all A pins low
  delay(500);

  uint8_t b = mcpRead(GPIOB);  // bit n = pin Bn (0 = pressed if wired to GND)
}