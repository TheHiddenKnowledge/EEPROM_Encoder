//A0-A3 is PD0-PD3, D0-D3 is PD4-PD7, OE is PB0, CE/WE is PB1  
#include <EEP.h>
EEP EEP(2); 
void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);
   EEP.writeEEP(0xFC,0xCCCC);
   Serial.println("Byte Read: ");
   Serial.println(EEP.readEEP(0xCCCC),HEX);
}
