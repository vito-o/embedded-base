#ifndef __INT_EEPROM_H__
#define __INT_EEPROM_H__

/**
 * @brief 向EEPROM指定位置写入多个字节
 *
 * @param addr 起始地址
 * @param bytes 要写入的字节
 * @param len 要写入的字节个数
 * @return bit 0:写入成功 1:写入失败
 */
unsigned char Int_EEPROM_WriteBytes(unsigned char addr, unsigned char *bytes, unsigned char len);


unsigned char Int_EEPROM_ReadBytes(unsigned char addr, unsigned char *bytes, unsigned char len);

#endif