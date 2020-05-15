#include <Wire.h>
#include <Arduino.h>
#include <EEPROM_24xx1025.h>

//EEPROM_24xx1025 eeprom1025(EPR_ADDR0,EPR_ADDR1,EPR_ADDR2,EPR_ADDR3);
EEPROM_24xx1025 eeprom1025(EPR_ADDR0);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  eraseExtEEPROM();
}

void loop() {
  // put your main code here, to run repeatedly:
}

void eraseExtEEPROM() {
  long address;
  byte fData[30];

  Serial.println(F("Erasing extEEPROM startted."));
  for (address = 0; address < 30; address ++)fData[address] = 0xFF;
  for (address = 0; address < eeprom1025.maxLongAddress; address += 16) {
    if (!(address % 0x400)) {
      Serial.println(address, HEX);
    }
    eeprom1025.write(address, fData, 30);
  }
  Serial.println(F("Erasing extEEPROM finished."));
}
