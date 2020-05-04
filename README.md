# EEPROM_24xx1025
 Arduino library for Microchip EEPROM 24xx1025

EEPROM_24x1025ライブラリは、ArduinoでMicrochipのEEPROM 24AA1025/24LC21025/24FC1025
を使うためのライブラリです。これらのEEPROMは同一バスで最大４個のデバイスを接続可能
ですが、単純な読み書きのコマンドでは複数デバイスの扱い、ページ境界の扱いが面倒です。
かといって1バイトずつ読み書きしていては効率が悪い上にEEPROMの書き込み制限（10～100
万回）上好ましくありません。そこで、これらのデバイスの読み書きを簡単にするために本
ライブラリを作成しました。C++は使いこなせないのでコーディングがスマートでないのは
ご容赦ください。
。
本ライブラリの特徴は

１．１～４デバイスの接続に対応
　　longアドレス使用時は接続した複数デバイスのメモリをブロック間、デバイス間問わず
　　シームレスに読み書き可能です（最大4Mbit=512Kbyte）。ブロック間、デバイス間はArduinoの
　　単一コマンドでは連続して処理できませんが、本ライブラリが分割して処理しますので
　　考慮不要です。ただし最大アドレスには注意（４デバイス使用時は0x7FFFF）。読み書き
　　時に最大アドレスを超えると最初のアドレスに戻ります。

２．書き込み時にページ境界を考慮不要
　　24xx1025では1ページは128バイトです。このため、ページ境界は128（0x80）の倍数です。
　　単純にArduinoのコマンドでページ境界を超えて連続して書き込むと、ページの最初に戻
　　って書き込まれます。本ライブラリではページ境界を超える場合、分割して次のページに
　　書き込みます。

３．読み書き時にArduinoのライブラリにおけるバッファサイズ制限を考慮不要
　　ArduinoのWireライブラリバッファは32バイトですが、書き込み時はコマンドで2バイト使
　　うので、データに使えるのは30バイトです。読み込み時はデータで32バイト使えます。
　　本ライブラリでは、バッファサイズを超えるでデータは分割して処理します。

４．readBlock(), writeBlock()では構造体の読み書きが可能
　　構造体と配列のキャストで処理しても良いですがちょっと面倒ですし、書き込みで配列を
　　構造体にキャストするとコンパイル時にwarningが出ます。readBlock(), writeBlock()は
　　E24.hを参考にしたので、正直何をやっているのか理解できていませんが、エラー出ずに
　　コンパイルされ構造体の読み書きが可能です。

## EEPROM_24x1025
EEPROM_24x1025 is a Arduino library for external I2C EEPROM (Microchip 24AA1025/24LC21025/24FC1025).

## Features
 * Support up to 4 devices on the bus read and write seamlessly beyond a block as a single address space
 * Support write data across a page boundary
 * Support read and write data over Arduino data buffer size

So you can read and write data on one virtual memory space without considering any boundary.

## Usage
See sample sketches.
