// EEPROM_24xx1025.h
// MICROCHIP 24AA1025/24LC1025/24FC1025 1024K I2C CMOS Serial EEPROM Library
//  for Arduino 
//  by Citriena
// 

#ifndef EEPROM_24xx1025_h
#define EEPROM_24xx1025_h
#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif
#include <Wire.h>

// Up to four devices may be connected to the same bus by using different
// Chip Select bit combinations(A0, A1) to specify diffent I2C address.
// 24xx1025 have two memory blocks of 64kbyte = 128kbyte = 1024kbit.
// In a same chip, you can select memory block by using different I2C address.
// A2 pin must be hard-wired to logical 1 state (VCC) (Microchip technology).
// Device will not operate with A2 pin left floating or held to logical 0(VSS).
//-------------------------------------------------------------------
#define EPR_ADDR0 0x50  // EEPROM address; A1=LOW, A0=LOW , block=0  B=0
//#define EPR_ADDR4 0x54  // EEPROM address; A1=LOW, A0=LOW , block=1  B=1
//-------------------------------------------------------------------
#define EPR_ADDR1 0x51  // EEPROM address; A1=LOW, A0=HIGH, block=0  B=2
//#define EPR_ADDR5 0x55  // EEPROM address; A1=LOW, A0=HIGH, block=1  B=3
//-------------------------------------------------------------------
#define EPR_ADDR2 0x52  // EEPROM address; A1=HIGH,A0=LOW , block=0  B=4
//#define EPR_ADDR6 0x56  // EEPROM address; A1=HIGH,A0=LOW , block=1  B=5
//-------------------------------------------------------------------
#define EPR_ADDR3 0x53  // EEPROM address; A1=HIGH,A0=HIGH, block=0  B=6
//#define EPR_ADDR7 0x57  // EEPROM address; A1=HIGH,A0=HIGH, block=1  B=7
//-------------------------------------------------------------------


#define EEPROM1025_WRITE_BUFF_SIZE  BUFFER_LENGTH - 2 // I2C write buffer size 32 - 2 for commands
#define EEPROM1025_READ_BUFF_SIZE   BUFFER_LENGTH     // I2C read buffer size; BUFFER_LENGTH is defined in Wire.h
#define EEPROM1025_PAGE_SIZE 0x80         // page size of the EEPRPM
#define EEPROM1025_ADDRESS_LIMIT 0xFFFF   // maximun Address of a menory block

typedef struct {
  byte block;
  unsigned int address;
} EEPROMblockAddress;

class EEPROM_24xx1025 {

public:

    EEPROM_24xx1025(byte epr_addr0);
    EEPROM_24xx1025(byte epr_addr0, byte epr_addr1);
    EEPROM_24xx1025(byte epr_addr0, byte epr_addr1, byte epr_addr2);
    EEPROM_24xx1025(byte epr_addr0, byte epr_addr1, byte epr_addr2, byte epr_addr3);

    int write(byte block, unsigned int addr, byte b[], int len);
    byte write(byte block, unsigned int addr, byte b);
    int write(long longAddr, byte b[], int len);
    byte write(long longAddr, byte b);

    int read(byte block, unsigned int addr, byte b[], int len);
    byte read(byte block, unsigned int addr);
    int read(long longAddr, byte b[], int len);
    byte read(long longAddr);

    EEPROMblockAddress incBlockAddress(byte block, unsigned int addr, unsigned int increment);
    long incLongAddress(long longAddr, unsigned int increment);
    EEPROMblockAddress long2BlockAddress(long longAddr);

    byte maxBlock;
    long maxLongAddress;          // maximum long address

    template <typename T> long readBlock(long longAddr, T& data) {
      return read(longAddr, (byte*)&data, sizeof(data));
    }

    template <typename T> long writeBlock(long longAddr, T& data) {
      return write(longAddr, (byte*)&data, sizeof(data));
    }


private:

    byte _EPR_ADDR[8];
};

#endif
