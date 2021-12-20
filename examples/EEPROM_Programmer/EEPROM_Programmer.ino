#include <EEP.h>

EEP EEP(39, 41, 40); 

void setup() {
   Serial.begin(9600);
   EEP.writeEEP(0xFC,0xCCCC);
   Serial.println("Byte Read: ");
   Serial.println(EEP.readEEP(0xCCCC),HEX);
}
