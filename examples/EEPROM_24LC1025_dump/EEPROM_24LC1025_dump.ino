#include <Wire.h>         // http://arduino.cc/en/Reference/Wire (included with Arduino IDE)
#include <Arduino.h>
#include <EEPROM_24xx1025.h>

EEPROM_24xx1025 eeprom1025(EPR_ADDR0);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dumpExtEEPROM();
}

int i = 0;

void loop() {
  // put your main code here, to run repeatedly:
}


void dumpExtEEPROM() {
  long address;
  byte rData[16];

  Serial.println(F("extEEPROM dump start."));
  for (address = 0; address < eeprom1025.maxLongAddress(); address += 16) {
    eeprom1025.read(address,rData,16);
    Serial.print(address, HEX);
    Serial.print(':');
    for (int i = 0; i < 16; i++) {
      Serial.print(rData[i],HEX);
      Serial.print(' ');
    }
    Serial.println();
  }
  Serial.println(F("extEEPROM dump finished."));
}
