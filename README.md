# EEPROM_24xx1025
 Arduino library for Microchip EEPROM 24xx1025

EEPROM_24x1025���C�u�����́AArduino��Microchip��EEPROM 24AA1025/24LC21025/24FC1025
���g�����߂̃��C�u�����ł��B������EEPROM�͓���o�X�ōő�S�̃f�o�C�X��ڑ��\
�ł����A�P���ȓǂݏ����̃R�}���h�ł͕����f�o�C�X�̈����A�y�[�W���E�̈������ʓ|�ł��B
���Ƃ�����1�o�C�g���ǂݏ������Ă��Ă͌������������EEPROM�̏������ݐ����i10�`100
����j��D�܂�������܂���B�����ŁA�����̃f�o�C�X�̓ǂݏ������ȒP�ɂ��邽�߂ɖ{
���C�u�������쐬���܂����BC++�͎g�����Ȃ��Ȃ��̂ŃR�[�f�B���O���X�}�[�g�łȂ��̂�
���e�͂��������B
�B
�{���C�u�����̓�����

�P�D�P�`�S�f�o�C�X�̐ڑ��ɑΉ�
�@�@long�A�h���X�g�p���͐ڑ����������f�o�C�X�̃��������u���b�N�ԁA�f�o�C�X�Ԗ�킸
�@�@�V�[�����X�ɓǂݏ����\�ł��i�ő�4Mbit=512Kbyte�j�B�u���b�N�ԁA�f�o�C�X�Ԃ�Arduino��
�@�@�P��R�}���h�ł͘A�����ď����ł��܂��񂪁A�{���C�u�������������ď������܂��̂�
�@�@�l���s�v�ł��B�������ő�A�h���X�ɂ͒��Ӂi�S�f�o�C�X�g�p����0x7FFFF�j�B�ǂݏ���
�@�@���ɍő�A�h���X�𒴂���ƍŏ��̃A�h���X�ɖ߂�܂��B

�Q�D�������ݎ��Ƀy�[�W���E���l���s�v
�@�@24xx1025�ł�1�y�[�W��128�o�C�g�ł��B���̂��߁A�y�[�W���E��128�i0x80�j�̔{���ł��B
�@�@�P����Arduino�̃R�}���h�Ńy�[�W���E�𒴂��ĘA�����ď������ނƁA�y�[�W�̍ŏ��ɖ�
�@�@���ď������܂�܂��B�{���C�u�����ł̓y�[�W���E�𒴂���ꍇ�A�������Ď��̃y�[�W��
�@�@�������݂܂��B

�R�D�ǂݏ�������Arduino�̃��C�u�����ɂ�����o�b�t�@�T�C�Y�������l���s�v
�@�@Arduino��Wire���C�u�����o�b�t�@��32�o�C�g�ł����A�������ݎ��̓R�}���h��2�o�C�g�g
�@�@���̂ŁA�f�[�^�Ɏg����̂�30�o�C�g�ł��B�ǂݍ��ݎ��̓f�[�^��32�o�C�g�g���܂��B
�@�@�{���C�u�����ł́A�o�b�t�@�T�C�Y�𒴂���Ńf�[�^�͕������ď������܂��B

�S�DreadBlock(), writeBlock()�ł͍\���̂̓ǂݏ������\
�@�@�\���̂Ɣz��̃L���X�g�ŏ������Ă��ǂ��ł���������Ɩʓ|�ł����A�������݂Ŕz���
�@�@�\���̂ɃL���X�g����ƃR���p�C������warning���o�܂��BreadBlock(), writeBlock()��
�@�@E24.h���Q�l�ɂ����̂ŁA������������Ă���̂������ł��Ă��܂��񂪁A�G���[�o����
�@�@�R���p�C������\���̂̓ǂݏ������\�ł��B

## EEPROM_24x1025
EEPROM_24x1025 is a Arduino library for external I2C EEPROM (Microchip 24AA1025/24LC21025/24FC1025).

## Features
 * Support up to 4 devices on the bus read and write seamlessly beyond a block as a single address space
 * Support write data across a page boundary
 * Support read and write data over Arduino data buffer size

So you can read and write data on one virtual memory space without considering any boundary.

## Usage
See sample sketches.
