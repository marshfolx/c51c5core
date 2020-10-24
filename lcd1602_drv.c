
#include "annex/lcd1602_drv.h"
#include "INTRINS.H"

#include "config.h"


//no need to pay attention to these errors about global variable initialization.
sbit LCD_EN = LCD_1602_EN;
sbit LCD_RS = LCD_1602_RS;
sbit LCD_RW = LCD_1602_RW;
#define LCD_DP LCD_1602_DP


static uint8_t _lcd_read_cycle(void) {
	uint8_t b;
	LCD_DP = 0xff;

	//TODO: delay RS/RW setup
	LCD_EN = 1;

	//TODO: delay EN setup & read delay
	b = LCD_DP;
	LCD_EN = 0;
	return b;
}


//Assume LCD_DP port is already prepared for read.
uint8_t lcd_read_dat(void) {
	LCD_RS = 1;
	LCD_RW = 1;
	return _lcd_read_cycle();
}


uint8_t lcd_check_busy(void) {
	LCD_RS = 0;
	LCD_RW = 1;
	return _lcd_read_cycle() & 0x80;
}


#define _wait_busy() while(lcd_check_busy())


// static void _lcd_write_cycle() {
// 	//TODO: delay RS/RW setup
// 	LCD_EN = 1;

// 	//TODO: delay EN setup & data hold
// 	LCD_EN = 0;
// }

#define _lcd_write_cycle() \
do { \
	LCD_EN = 1; \
	LCD_EN = 0; \
} while(0)


void lcd_write_dat(uint8_t b) {
	LCD_RS = 1;
	LCD_RW = 0;

	LCD_DP = b;

	_lcd_write_cycle();
}


void lcd_write_cmd(uint8_t b) {
	_wait_busy();

	LCD_RS = 0;
	LCD_RW = 0;

	LCD_DP = b;
	_lcd_write_cycle();
}


void lcd_put_cursor(uint8_t l, uint8_t c) {
	if(l)
		c |= 0x40;
	c |= LCD_CMD_SET_DDRAM_ADDR;

	lcd_write_cmd(c);
}

/*
void lcd_put_char(char ch, uint8_t l, uint8_t c) {
	lcd_put_cursor(l, c);

	_wait_busy();
	lcd_write_dat(ch);
}*/

void lcd_append_char(char ch) {
	_wait_busy();
	lcd_write_dat(ch);
}


void lcd_append_str(char *s) {
	while(*s) {
		lcd_append_char(*s);
		s++;
	}
}

/*
void lcd_put_str(char *s, uint8_t l, uint8_t c) {
	lcd_put_cursor(l, c);
	lcd_append_str(s);
}*/


void lcd_1602_init() {
	LCD_EN = 0;
	lcd_write_init(lcii_line_2 | lcii_data_line_8);
	lcd_write_display(lcdd_enable_display);
	lcd_write_entry(lcee_shift_right);
	lcd_write_clr();
}

