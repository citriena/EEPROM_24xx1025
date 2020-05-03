#include <EEPROM_24xx1025.h>
#include <Wire.h>


EEPROM_24xx1025::EEPROM_24xx1025(byte epr_addr0) {
  Wire.begin();
  _EPR_ADDR[0] = epr_addr0;
  _EPR_ADDR[1] = epr_addr0 | 0b00000100;
  maxBlock = 1;
  maxLongAddress = 0x1FFFF;
}

EEPROM_24xx1025::EEPROM_24xx1025(byte epr_addr0, byte epr_addr1) {
  Wire.begin();
  _EPR_ADDR[0] = epr_addr0;
  _EPR_ADDR[1] = epr_addr0 | 0b00000100;
  _EPR_ADDR[2] = epr_addr1;
  _EPR_ADDR[3] = epr_addr1 | 0b00000100;
  maxBlock = 3;
  maxLongAddress = 0x3FFFF;
}

EEPROM_24xx1025::EEPROM_24xx1025(byte epr_addr0, byte epr_addr1, byte epr_addr2) {
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


EEPROM_24xx1025::EEPROM_24xx1025(byte epr_addr0, byte epr_addr1, byte epr_addr2, byte epr_addr3) {
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


int EEPROM_24xx1025::write(byte blk, unsigned int addr, byte b[], int len) {
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


byte EEPROM_24xx1025::write(byte blk, unsigned int addr, byte b) {
  byte ans;
  if (blk > maxBlock) return 0;
  Wire.beginTransmission(_EPR_ADDR[blk]);
  Wire.write(highByte(addr));
  Wire.write(lowByte(addr));
  ans = Wire.write(b);
  Wire.endTransmission();
  delay(5);
  return ans;
}


int EEPROM_24xx1025::write(long longAddr, byte b[], int len) {
  EEPROMblockAddress blockAddress = long2BlockAddress(longAddr);
  return write(blockAddress.block, blockAddress.address, b, len);
}


byte EEPROM_24xx1025::write(long longAddr, byte b) {
  if (longAddr > maxLongAddress) return 0;
  EEPROMblockAddress blockAddress = long2BlockAddress(longAddr);
  return write(blockAddress.block, blockAddress.address, b);
} // returns the number of bytes written

////////////////////////////////////////////////////////////////////////////////


int EEPROM_24xx1025::read(byte blk, unsigned int addr, byte b[], int len) {
  int i;
  int readLen;
  int offset = 0;
  int ct = 0;
  long romLen;
  EEPROMblockAddress blockAddress;

  if (blk > maxBlock) return 0;
  blockAddress = {blk, addr};
  readLen = len;
  do {
    romLen = (long)EEPROM1025_ADDRESS_LIMIT - (long)blockAddress.address + 1;
    if (readLen > romLen) readLen = romLen;
    if (readLen > EEPROM1025_READ_BUFF_SIZE) readLen = EEPROM1025_READ_BUFF_SIZE;
    Wire.beginTransmission(_EPR_ADDR[blockAddress.block]);
    Wire.write(highByte(blockAddress.address));
    Wire.write(lowByte(blockAddress.address));
    Wire.endTransmission();
    Wire.requestFrom((int)_EPR_ADDR[blockAddress.block], readLen);
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


byte EEPROM_24xx1025::read(byte blk, unsigned int addr) {
  if (blk > maxBlock) return 0xFF;
  Wire.beginTransmission(_EPR_ADDR[blk]);
  Wire.write(highByte(addr));
  Wire.write(lowByte(addr));
  Wire.endTransmission();
  Wire.requestFrom(_EPR_ADDR[blk], (byte)1);
  return Wire.read();
}


int EEPROM_24xx1025::read(long longAddr, byte b[], int len) {
  EEPROMblockAddress blockAddress = long2BlockAddress(longAddr);
  return read(blockAddress.block, blockAddress.address, b, len);
}


byte EEPROM_24xx1025::read(long longAddr) {
  EEPROMblockAddress blockAddress = long2BlockAddress(longAddr);
   return read(blockAddress.block, blockAddress.address);
}  // returns the number of bytes read

////////////////////////////////////////////////////////////////////////////////


EEPROMblockAddress EEPROM_24xx1025::incBlockAddress(byte blk, unsigned int addr, unsigned int increment) {
	addr += increment;
	if (addr < increment) {  // when wrap around happened
		blk++;
		if (blk > maxBlock) blk = 0;
	}
	return {blk, addr};
}

long EEPROM_24xx1025::incLongAddress(long longAddr, unsigned int increment) {
	longAddr += increment;
	if (longAddr > maxLongAddress) longAddr = (longAddr - maxLongAddress - 1);
	return longAddr;
}


EEPROMblockAddress EEPROM_24xx1025::long2BlockAddress(long longAddr) {
   byte blk = (byte)(longAddr >> 16);
   unsigned int addr = (unsigned int)(longAddr & 0x0000FFFF);
   return {blk, addr};
}
