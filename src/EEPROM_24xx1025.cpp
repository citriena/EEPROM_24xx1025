#include <EEPROM_24xx1025.h>
#include <Wire.h>


EEPROM_24xx1025::EEPROM_24xx1025(uint8_t epr_addr0) {
  Wire.begin();
  _EPR_ADDR[0] = epr_addr0;
  _EPR_ADDR[1] = epr_addr0 | 0b00000100;
  maxBlock = 1;
  maxLongAddress = 0x1FFFF;
}

EEPROM_24xx1025::EEPROM_24xx1025(uint8_t epr_addr0, uint8_t epr_addr1) {
  Wire.begin();
  _EPR_ADDR[0] = epr_addr0;
  _EPR_ADDR[1] = epr_addr0 | 0b00000100;
  _EPR_ADDR[2] = epr_addr1;
  _EPR_ADDR[3] = epr_addr1 | 0b00000100;
  maxBlock = 3;
  maxLongAddress = 0x3FFFF;
}

EEPROM_24xx1025::EEPROM_24xx1025(uint8_t epr_addr0, uint8_t epr_addr1, uint8_t epr_addr2) {
  Wire.begin();
  _EPR_ADDR[0] = epr_addr0;
  _EPR_ADDR[1] = epr_addr0 | 0b00000100;
  _EPR_ADDR[2] = epr_addr1;
  _EPR_ADDR[3] = epr_addr1 | 0b00000100;
  _EPR_ADDR[4] = epr_addr2;
  _EPR_ADDR[5] = epr_addr2 | 0b00000100;
  maxBlock = 5;
  maxLongAddress = 0x5FFFF;
}


EEPROM_24xx1025::EEPROM_24xx1025(uint8_t epr_addr0, uint8_t epr_addr1, uint8_t epr_addr2, uint8_t epr_addr3) {
  Wire.begin();
  _EPR_ADDR[0] = epr_addr0;
  _EPR_ADDR[1] = epr_addr0 | 0b00000100;
  _EPR_ADDR[2] = epr_addr1;
  _EPR_ADDR[3] = epr_addr1 | 0b00000100;
  _EPR_ADDR[4] = epr_addr2;
  _EPR_ADDR[5] = epr_addr2 | 0b00000100;
  _EPR_ADDR[6] = epr_addr3;
  _EPR_ADDR[7] = epr_addr3 | 0b00000100;
  maxBlock = 7;
  maxLongAddress = 0x7FFFF;
}

////////////////////////////////////////////////////////////////////////////////


int16_t EEPROM_24xx1025::write(uint8_t blk, uint16_t addr, uint8_t b[], int16_t len) {
  int writeLen;
  int pageLeft;
  int offset = 0;
  int ct;
  EEPROMblockAddress blockAddress;

  if (blk > maxBlock) return 0;
  writeLen = len;
  blockAddress = {blk, addr};
  do {
    pageLeft = EEPROM1025_PAGE_SIZE - (blockAddress.address % EEPROM1025_PAGE_SIZE);  // can not write data crossing page boundary
    if (writeLen > pageLeft) writeLen = pageLeft;
    if (writeLen > EEPROM1025_WRITE_BUFF_SIZE) writeLen = EEPROM1025_WRITE_BUFF_SIZE;
    Wire.beginTransmission(_EPR_ADDR[blockAddress.block]);
    Wire.write(highByte(blockAddress.address));
    Wire.write(lowByte(blockAddress.address));
    Wire.write(&b[offset], writeLen);
    Wire.endTransmission();
    delay(5);
    blockAddress = incBlockAddress(blockAddress.block, blockAddress.address, writeLen);
    ct = offset + writeLen;
    offset += writeLen;
    writeLen = len - offset;
  } while (offset < len);
  return ct; // returns the number of bytes written
}


uint8_t EEPROM_24xx1025::write(uint8_t blk, uint16_t addr, uint8_t b) {
  uint8_t ans;
  if (blk > maxBlock) return 0;
  Wire.beginTransmission(_EPR_ADDR[blk]);
  Wire.write(highByte(addr));
  Wire.write(lowByte(addr));
  ans = Wire.write(b);
  Wire.endTransmission();
  delay(5);
  return ans;
}


int16_t EEPROM_24xx1025::write(int32_t longAddr, uint8_t b[], int16_t len) {
  EEPROMblockAddress blockAddress = long2BlockAddress(longAddr);
  return write(blockAddress.block, blockAddress.address, b, len);
}


uint8_t EEPROM_24xx1025::write(int32_t longAddr, uint8_t b) {
  if (longAddr > maxLongAddress) return 0;
  EEPROMblockAddress blockAddress = long2BlockAddress(longAddr);
  return write(blockAddress.block, blockAddress.address, b);
} // returns the number of bytes written

////////////////////////////////////////////////////////////////////////////////


int16_t EEPROM_24xx1025::read(uint8_t blk, uint16_t addr, uint8_t b[], int16_t len) {
  int16_t i;
  int16_t readLen;
  int16_t offset = 0;
  int16_t ct = 0;
  int32_t romLen;
  EEPROMblockAddress blockAddress;

  if (blk > maxBlock) return 0;
  blockAddress = {blk, addr};
  readLen = len;
  do {
    romLen = (int32_t)EEPROM1025_ADDRESS_LIMIT - (int32_t)blockAddress.address + 1;
    if (readLen > romLen) readLen = romLen;
    if (readLen > EEPROM1025_READ_BUFF_SIZE) readLen = EEPROM1025_READ_BUFF_SIZE;
    Wire.beginTransmission(_EPR_ADDR[blockAddress.block]);
    Wire.write(highByte(blockAddress.address));
    Wire.write(lowByte(blockAddress.address));
    Wire.endTransmission();
    Wire.requestFrom((int16_t)_EPR_ADDR[blockAddress.block], readLen);
    for (i = 0; i < readLen; i++) {
      if (Wire.available()) {
        b[offset + i] = Wire.read();
        ct++;
      } else {
        return ct;
      }
    }
    blockAddress = incBlockAddress(blockAddress.block, blockAddress.address, readLen);
    offset += readLen;
    readLen = len - offset;
  } while (offset < len);
  return ct; // returns the number of bytes read
}


uint8_t EEPROM_24xx1025::read(uint8_t blk, uint16_t addr) {
  if (blk > maxBlock) return 0xFF;
  Wire.beginTransmission(_EPR_ADDR[blk]);
  Wire.write(highByte(addr));
  Wire.write(lowByte(addr));
  Wire.endTransmission();
  Wire.requestFrom(_EPR_ADDR[blk], (uint8_t)1);
  return Wire.read();
}


int16_t EEPROM_24xx1025::read(int32_t longAddr, uint8_t b[], int16_t len) {
  EEPROMblockAddress blockAddress = long2BlockAddress(longAddr);
  return read(blockAddress.block, blockAddress.address, b, len);
}


uint8_t EEPROM_24xx1025::read(int32_t longAddr) {
  EEPROMblockAddress blockAddress = long2BlockAddress(longAddr);
   return read(blockAddress.block, blockAddress.address);
}  // returns the number of bytes read

////////////////////////////////////////////////////////////////////////////////


EEPROMblockAddress EEPROM_24xx1025::incBlockAddress(uint8_t blk, uint16_t addr, uint16_t increment) {
	addr += increment;
	if (addr < increment) {  // when wrap around happened
		blk++;
		if (blk > maxBlock) blk = 0;
	}
	return {blk, addr};
}

int32_t EEPROM_24xx1025::incLongAddress(int32_t longAddr, uint16_t increment) {
	longAddr += increment;
	if (longAddr > maxLongAddress) longAddr = (longAddr - maxLongAddress - 1);
	return longAddr;
}


EEPROMblockAddress EEPROM_24xx1025::long2BlockAddress(int32_t longAddr) {
   uint8_t blk = (uint8_t)(longAddr >> 16);
   uint16_t addr = (uint16_t)(longAddr & 0x0000FFFF);
   return {blk, addr};
}
