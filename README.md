# EEPROM_24xx1025

EEPROM_24xx1025 is an Arduino library for external I2C EEPROM (Microchip 24AA1025/24LC21025/24FC1025).

## Features
* Support up to 4 devices on the bus read and write seamlessly beyond a block as a single address space
* Support write data across a page boundary
* Support read and write data over Arduino data buffer size
* Support Structured block read and write

So you can read and write data on one virtual memory space without considering any boundary.

## Usage
### Constructor
```
EEPROM_24xx1025 eeprom1025(EPR_ADDR0, EPR_ADDR1, EPR_ADDR2, EPR_ADDR3)；
EEPROM_24xx1025(uint8_t epr_addr0, uint8_t epr_addr1, uint8_t epr_addr2, uint8_t epr_addr3);

```
Set I2C bus address(es) of EEPROM device(s). Up to four devices may be connected to the same bus. The addresses listed below can be used in any order.

* EPR_ADDR0: 0x50
* EPR_ADDR1: 0x51
* EPR_ADDR2: 0x52
* EPR_ADDR3: 0x53

### Addressing
EEPROM_24xx1025 can access connected multiple EEPROMs by addressing 0\-0x7FFFF (longAddr).

### Functions
```
uint8_t write(int32_t longAddr, uint8_t b);
```
Write single byte to EEPROM.
```
int16_t write(int32_t longAddr, uint8_t b[], int16_t len);
```
Write multiple bytes to EEPROM.
```
uint8_t read(int32_t longAddr);
```
Read single byte from EEPROM.
```
int16_t read(int32_t longAddr, uint8_t b[], int16_t len);
```
Read multiple bytes from EEPROM.

```
int32_t maxLongAddress();
```
Returns maximum longAddr value.
```
int16_t writeBlock(int32_t longAddr, typedef data);
```
Write structured block to EEPROM.
```
int16_t readBlock(int32_t longAddr, typdef data);
```
Read structured block from EEPROM.

## Releases

### 1.0.0 - Mar  4, 2019

### 1.0.1 - May 23, 2020
* renamed some functions constants and variables

### 1.1.0 - June 09, 2020
* change public variables private
* add public functions to access private variables
