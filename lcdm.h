#ifndef _LCDM_H
#define _LCDM_H

#define LCD_MODE_BLINK 0x01
#define LCD_MODE_CURSOR 0x02
#define LCD_MODE_ON 0x04

void LCD_Init(void);
void LCD_PutChar(unsigned char c);
void LCD_SetCursor(unsigned char pos);
void LCD_DisplayOn(unsigned char mode);

#endif