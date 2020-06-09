# EEPROM_24xx1025

EEPROM_24xx1025 is an Arduino library for external I2C EEPROM (Microchip 24AA1025/24LC21025/24FC1025).

## Features
* Support up to 4 devices on the bus read and write seamlessly beyond a block as a single address space
* Support write data across a page boundary
* Support read and write data over Arduino data buffer size
* Support Structured block read and write

So you can read and write data on one virtual memory space without considering any boundary.

## Usage
See sample sketches.

## Releases

### 1.0.0 - Mar  4, 2019

### 1.0.1 - May 23, 2020
* renamed some functions constants and variables

### 1.1.0 - June 09, 2020
* change public variables private
* add public functions to access private variables

## 概要
EEPROM_24xx1025ライブラリは、ArduinoでMicrochipのEEPROM 24AA1025/24LC21025/24FC1025を使うためのライブラリです。これらのEEPROMは同一バスで最大４個のデバイスを接続可能ですが、単純な読み書きのコマンドでは複数デバイスの扱い、ページ境界の扱いが面倒です。かといって1バイトずつ読み書きしていては効率が悪い上にEEPROMの書き込み制限（10～100万回）上好ましくありません。そこで、これらのデバイスの読み書きを簡単にするために本ライブラリを作成しました。

## 特徴

### １．１～４デバイスの接続に対応
longアドレス使用時は接続した複数デバイスのメモリをブロック間、デバイス間問わずシームレスに読み書き可能です（最大4Mbit=512Kbyte）。ブロック間、デバイス間はArduinoの単一コマンドでは連続して処理できませんが、本ライブラリが分割して処理しますので考慮不要です。ただし最大アドレスには注意が必要です（４デバイス使用時は0x7FFFF）。読み書き時に最大アドレスを超えると最初のアドレスに戻ります。

### ２．書き込み時にページ境界を考慮不要
24xx1025では1ページは128バイトです。このため、ページ境界は128（0x80）の倍数です。単純にArduinoのコマンドでページ境界を超えて連続して書き込むと、ページの最初に戻って書き込まれます。本ライブラリではページ境界を超える場合、分割して次のページに書き込みます。

### ３．読み書き時にArduinoのライブラリにおけるバッファサイズ制限を考慮不要
ArduinoのWireライブラリバッファは32バイトですが、書き込み時はコマンドで2バイト使うので、データに使えるのは30バイトです。読み込み時はデータで32バイト使えます。本ライブラリでは、バッファサイズを超えるデータは分割して処理します。

### ４．readBlock(), writeBlock()では構造体の読み書きが可能
構造体と配列のキャストで処理しても良いですがちょっと面倒ですし、書き込みで配列を構造体にキャストするとコンパイル時にwarningが出ます。readBlock(), writeBlock()を使えばコンパイル時にwarningを出すことなく、かつ簡単に構造体の読み書きができます。E24.hを参考にしました。

## 使い方

### コンストラクタ
```
EEPROM_24xx1025 eeprom1025(EPR_ADDR0, EPR_ADDR1, EPR_ADDR2, EPR_ADDR3)；
```

使用するEEPROMのI2Cアドレスを指定します。最大4つ指定できます。順序は自由です。指定した順にブロック番号（0\-7）、連続メモリアドレス(0\-0x7FFFF)が割り振られます。I2Cアドレスは以下の通りです。

* EPR_ADDR0: 0x50
* EPR_ADDR1: 0x51
* EPR_ADDR2: 0x52
* EPR_ADDR3: 0x53

### メモリアドレス指定
24AA1025/24LC21025/24FC1025は１ブロック0\-0xFFFF (0x10000byte) が基本的なメモリ空間で、１つのチップに２つのブロックがあります。各ブロックのアクセスはI2Cアドレスで区別します。

EEPROM_24xx1025は、デバイスを指定した順に各ブロックにつけたブロック番号（0-7）とそのブロックのメモリアドレスを元にしたアクセスと、全てのメモリを連続したメモリ空間 (すなわち、最大0\-0x7FFFF)としたアクセスの２つの方法が使えます。ここでは後者の方法を説明します。
```
uint8_t write(int32_t longAddr, uint8_t b);
```
指定したアドレス(longAddr)に1バイト(b)を書き込みます。実際に書き込みしたバイト数を返します。
```
int16_t write(int32_t longAddr, uint8_t b[], int16_t len);
```
指定したアドレス(longAddr)に配列bからlenバイトを書き込みます。実際に書き込みしたバイト数を返します。
```
uint8_t read(int32_t longAddr);
```
指定したアドレス(longAddr)から1バイト読み込みます。
読み込んだデータを返します。
```
int16_t read(int32_t longAddr, uint8_t b[], int16_t len);
```
指定したアドレス(longAddr)から配列bにlenバイトを読み込みます。実際に読み込んだバイト数を返します。
```
int32_t maxLongAddress();
```
指定したデバイス全てのメモリを連続したメモリ空間とした場合の最大アドレスを返します。デバイスを４つ指定した場合は0x7FFFFを返します。
```
int16_t writeBlock(int32_t longAddr, typedef data);
```
指定したアドレス(longAddr)に構造体typedef dataからデータを書き込みます。
```
int16_t readBlock(int32_t longAddr, typdef data);
```
指定したアドレス(longAddr)から構造体typedef dataにデータを読み込みます。
