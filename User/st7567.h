#ifndef ST7567_H
#define ST7567_H

#include <stdint.h>

void lcd_init(void);
void lcd_clear(void);
void lcd_test_fill(void);
void lcd_char(uint8_t x, uint8_t page, char c);
void lcd_string(uint8_t x, uint8_t page, const char *s);


void lcd_char_A(uint8_t x, uint8_t page);
void lcd_char(uint8_t x, uint8_t page, char c);
void lcd_string(uint8_t x, uint8_t page, const char *s);

#endif
