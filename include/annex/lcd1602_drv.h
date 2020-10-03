#ifndef  __CCC_LCD1602_DRV_H__
#define __CCC_LCD1602_DRV_H__


#include "io_x.h"
#include "macrobin.h"


#define LCD_DP P0   //八位IO端口
sbit LCD_RS = P3^5;
sbit LCD_RW = P3^6;
sbit LCD_EN = P3^4;

//all command is enable if specified, disable otherwise.
//which means send a command without a part will disable it,
//not just keep it.


//0b001xxx00
#define LCD_CMD_INIT (B0010_0000)

enum _lcd_cmd_init {
	lci_data_line_8 = B0001_0000,    //use 8 lines to tansfer data if set, 4 otherwise.
	lci_line_count  = B0000_1000,    //display 2 lines if set, 1 otherwise.
	lci_char_5x10   = B0000_0100,    //use 5x10 size character if set, 5x8 otherwise.
	                               //note that 5x10 can only be used in 1 line mode.
};
typedef enum _lcd_cmd_init lcd_cmd_init;

//0b0000_1xxx
#define LCD_CMD_DISPLAY (B0000_1000)

enum _lcd_cmd_display {
	lcd_enable_display = B0000_0100,
	lcd_show_cursor    = B0000_0010,
	lcd_cursor_blink   = B0000_0001,
};
typedef enum _lcd_cmd_display lcd_cmd_display;


//0b0000_01xx
#define LCD_CMD_AFTER_ENTER (B0000_0100)

enum _lcd_cmd_after_enter {        //what will happen when a new character come in.
	lcae_cursor_direction = B0000_0010,    //cursor will shift right if set, left otherwise.
	lcae_shift_screen     = B0000_0001,     //shift screen instead of cursor.
};
typedef enum _lcd_cmd_after_enter lcd_cmd_after_enter;


//0b0001xx00
#define LCD_CMD_SHIFT (B0001_0000)

enum _lcd_cmd_shift {
	lcs_shift_screen = B0000_1000,    //shift screen if set, cursor otherwise.
	lcs_to_right     = B0000_0100,    //shift right if set, left otherwise.
};
typedef enum _lcd_cmd_shift lcd_cmd_shift;


#define LCD_CMD_CLR (0x01)
#define LCD_CMD_CR  (0x02)

//0b01xxxxxx
#define LCD_CMD_SET_CGRAM_ADDR (0x70)

//0b1xxxxxxx
#define LCD_CMD_SET_DDRAM_ADDR (0x80)


//read without addr set will check busy flag.



#endif  //__CCC_LCD1602_DRV_H__