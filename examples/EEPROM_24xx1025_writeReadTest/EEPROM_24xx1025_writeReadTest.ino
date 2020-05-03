#include <Wire.h>
#include <Arduino.h>
#include <EEPROM_24xx1025.h>

//EEPROM_24xx1025 eeprom1025(EPR_ADDR0,EPR_ADDR1,EPR_ADDR2,EPR_ADDR3); // maximun four devices are available
EEPROM_24xx1025 eeprom1025(EPR_ADDR0);

const int rwSize = 0x100;
const long rwAddress = 0x70; // write across page boundary (multiple of 0x80)
//const long rwAddress = 0xFFF0;  // write across block boundary (0xFFFF)
//const long rwAddress = 0x1FFF0; // read and write over maximum address results in
                                  // the data wraps around to the beginning of the address

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  EEPROMwriteTest(-1);
  EEPROMreadTest();
  EEPROMwriteTest(0xFF);
  EEPROMreadTest();
} 

void loop() {
  // put your main code here, to run repeatedly:
}


void EEPROMwriteTest(int c){
  byte wBuff[rwSize];
  int i;
  int rwByte;

  Serial.println(F("EEPROM write test start."));
  Serial.print(F("Write following data to address:"));
  Serial.print(rwAddress, HEX);
  for (i = 0; i < rwSize; i++) {
    if (c >= 0) {
      wBuff[i] = (byte)c;
    } else {
      wBuff[i] = i;
    }
    if (!(i % 0x10)) {
      Serial.println();
      Serial.print(rwAddress + i, HEX);
      Serial.print(":");
    }
    if (wBuff[i] < 0x10) Serial.print(0);
    Serial.print(wBuff[i], HEX);
    Serial.print(" ");
  }
  rwByte = eeprom1025.write(rwAddress, wBuff, rwSize);
  Serial.println();
  Serial.print("write ");
  Serial.print(rwByte, HEX);
  Serial.println(" bytes");
  Serial.println();
}


void EEPROMreadTest() {
  byte rBuff[rwSize];
  int i;
  int rwByte;

  Serial.println(F("EEPROM read test start."));
  Serial.print(F("Read data from address:"));
  Serial.print(rwAddress, HEX);
  rwByte = eeprom1025.read(rwAddress, rBuff, rwSize);
  for (i = 0; i < rwSize; i++) {
    if (!(i % 0x10)) {
      Serial.println();
      Serial.print(rwAddress + i, HEX);
      Serial.print(":");
    }
    if (rBuff[i] < 0x10) Serial.print("0");
    Serial.print(rBuff[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
  Serial.print("read ");
  Serial.print(rwByte, HEX);
  Serial.println(" bytes");
  Serial.println();
}
