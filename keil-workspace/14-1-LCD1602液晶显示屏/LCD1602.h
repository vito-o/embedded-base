#ifndef __LCD1602_H__
#define __LCD1602_H__

void LCD_Init();
void LCD_WriteCommand(unsigned char command);
void LCD_ShowChar(unsigned char line, unsigned char col, unsigned char ch);
void LCD_ShowString(unsigned char line, unsigned char col, unsigned char *string);
void LCD_ShowNum(unsigned char line, unsigned char col, unsigned int num, unsigned char len);
void LCD_ShowSignNum(unsigned char line, unsigned char col, unsigned int num, unsigned char len);
void LCD_ShowHexNum(unsigned char line, unsigned char col, unsigned int num, unsigned char len);
void LCD_ShowBinNum(unsigned char line, unsigned char col, unsigned int num, unsigned char len);

#endif