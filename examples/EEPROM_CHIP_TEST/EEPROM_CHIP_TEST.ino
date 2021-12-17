#include <TinyI2CMaster.h>
byte sent = 125; 
byte address = 10;
byte writeEEPROM(byte value, byte address) {
  TinyI2C.start(0x50, 0);
  TinyI2C.write(address);
  TinyI2C.write(value);
  TinyI2C.stop();
  
}
byte readEEPROM(byte address) {
  byte value;
  TinyI2C.start(0x50, 0);
  TinyI2C.write(address);
  TinyI2C.restart(0x50, 1);
  value = TinyI2C.read();
  TinyI2C.stop();
  return value;
}
void setup() {
  // put your setup code here, to run once:
  pinMode(1, OUTPUT);
  TinyI2C.init();
  writeEEPROM(sent, address);
}

void loop() {
  // put your main code here, to run repeatedly:
  byte rec = 125;
  analogWrite(1, rec);
  delay(100);
}
