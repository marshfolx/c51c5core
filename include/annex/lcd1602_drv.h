#ifndef  __CCC_LCD1602_DRV_H__
#define __CCC_LCD1602_DRV_H__


#include "io_x.h"
#include "macrobin.h"
#include "config.h"


#ifdef __cplusplus
extern "C" {
#endif


/*! \file
*  \par
*  according to a datasheet to lcd1602 module,
*  before the rise edge of LCD_EN, RS/RW should be held at least 0.1us,
*  then the high level on LCD_EN shall be held at least 0.3us,
*  and another rise edge shall be delayed for at least 0.5us.
*  when read, the output on data line appears with a delay at range of [0.06 ~ 0.19]us
*  when write, the data line should be held at least 0.06us after EN setup.

*  \par
*  系统时钟频率 F_CPU 或F_SYS > 1MHz 时，单周期指令执行时间小于1us，
*  驱动lcd1602 信号可能需要额外的延时, 否则可能导致不稳定。
*  不考虑IO 切换延时的情况下，如果统一给信号操作延时大约0.3us ~ 1us，
*  则        F_SYS < 3MHz  不需要延时;
*    3MHz < F_SYS < 10MHz 延时3个周期;
*   10MHz < F_SYS < 20MHz 延时6个周期;
*   20MHz < F_SYS < 30MHz 延时9个周期;
*   30MHz < F_SYS < 40MHz 延时12个周期;
*   40MHz < F_SYS < 50MHz 延时15个周期;
*  依此类推。
*
*  这个延时将被插入到:  lcd_read_dat   / lcd_read_dat4
*                    lcd_write_dat / lcd_write_dat4
*                    lcd_write_cmd / lcd_write_cmd4
*                    lcd_read_cmd  / lcd_read_cmd4
*  
*  底层使用这些函数的函数也将受到影响。
*  
*  \note !Not implemented yet.
*  TODO:
*  
*  \par
*  all commands enable something if specified, disable otherwise.
*  which means send a command without a part will disable it, not just keep it.
*/

//0b001xxx00
#define LCD_CMD_INIT (B0010_0000)

enum _lcd_cmd_init {
	lcii_data_line_8 = B0001_0000,    //use 8 lines to tansfer data if set, 4 otherwise.
	lcii_line_2      = B0000_1000,    //display 2 lines if set, 1 otherwise.
	lcii_char_5x10   = B0000_0100,    //use 5x10 size character if set, 5x8 otherwise.
	                                 //note that 5x10 can only be used in 1 line mode.
};
typedef enum _lcd_cmd_init lcd_cmd_init;

//0b0000_1xxx
#define LCD_CMD_DISPLAY (B0000_1000)

enum _lcd_cmd_display {
	lcdd_enable_display = B0000_0100,
	lcdd_show_cursor    = B0000_0010,
	lcdd_cursor_blink   = B0000_0001,
};
typedef enum _lcd_cmd_display lcd_cmd_display;


//0b0000_01xx
#define LCD_CMD_ENTRY (B0000_0100)

enum _lcd_cmd_entry {        //what will happen when a new character come in.
	lcee_shift_right  = B0000_0010,    //cursor will shift right if set, left otherwise.
	lcee_shift_screen = B0000_0001,    //shift screen instead of cursor.
};
typedef enum _lcd_cmd_entry lcd_cmd_entry;


//0b0001xx00
#define LCD_CMD_SHIFT (B0001_0000)

enum _lcd_cmd_shift {
	lcss_shift_screen = B0000_1000,    //shift screen if set, cursor otherwise.
	lcss_to_right     = B0000_0100,    //shift right if set, left otherwise.
};
typedef enum _lcd_cmd_shift lcd_cmd_shift;


#define LCD_CMD_CLR (0x01)    //! screen clear.
#define LCD_CMD_CR  (0x02)    //! carriage return.

//0b01xxxxxx
#define LCD_CMD_SET_CGRAM_ADDR (0x70)

//0b1xxxxxxx
#define LCD_CMD_SET_DDRAM_ADDR (0x80)


/*!
*  \note config LCD_DP in input mode or set all pins high (open-drain) before read.
*/
uint8_t lcd_read_dat(void);


void lcd_write_dat(uint8_t b);


void lcd_write_cmd(uint8_t b);


/*! check if lcd1602 is busy
*  \note config LCD_DP in input mode or set all pins high (open-drain) before read.
*  \note may not work, always idle.
*  \return return zero if idle, non-zero if busy.
*/
uint8_t lcd_check_busy(void);


/*! write init cmd with specified options.
*  \param b  could be like (lcii_line_2 | lcii_data_line_8)
*/
#define lcd_write_init(b) \
do { \
	lcd_write_cmd(LCD_CMD_INIT | (b)); \
} while(0)

/*! write display cmd with specified options.
*  \param b  could be like (lcdd_enable_display | lcdd_show_cursor | lcdd_cursor_blink)
*/
#define lcd_write_display(b) \
do { \
	lcd_write_cmd(LCD_CMD_DISPLAY | (b)); \
} while(0)


/*! write entry cmd with specified options.
*  \param b  could be like (lcee_shift_right | lcee_shift_screen)
*/
#define lcd_write_entry(b) \
do { \
	lcd_write_cmd(LCD_CMD_ENTRY | (b)); \
} while(0)


/*! write SHIFT cmd with specified options.
*  \param b  could be like (lcss_shift_screen | lcss_to_right)
*/
#define lcd_write_shift(b) \
do { \
	lcd_write_cmd(LCD_CMD_SHIFT | (b)); \
} while(0)


#define lcd_write_clr() \
do { \
	lcd_write_cmd(LCD_CMD_CLR); \
} while(0)


#define lcd_write_cr() \
do { \
	lcd_write_cmd(LCD_CMD_CR); \
} while(0)


/*! init it as 16 02, 8 data lines.
*/

void lcd_1602_init();

/*! put cursor on the specified location.
*  \param l  line num, 0 or 1.
*  \param c  column, [0, 15] or [0, 39]
*/
void lcd_put_cursor(uint8_t l, uint8_t c);


/*! put a character to the current cursor position.
*  \param ch character, encoded by ascii.
*/
void lcd_append_char(char ch);

/*! put a string to the current cursor position.
*  \param s  zero-terminated string.
*  \note the ENTRY option controls the display direction of string.
*/
void lcd_append_str(char *s);


/*! put a character on the specified location.
*  \param ch character, encoded by ascii.
*  \param l  line num, 0 or 1.
*  \param c  column, [0, 15] or [0, 39]
*/
#define lcd_put_char(ch, l, c) \
do { \
	lcd_put_cursor(l, c); \
	lcd_append_char(ch); \
} while(0)

//void lcd_put_char(char ch, uint8_t l, uint8_t c);


/*! put a string on the specified location.
*  \param s  zero-terminated string.
*  \param l  line num, 0 or 1.
*  \param c  column, [0, 15] or [0, 39]
*  \note the ENTRY option controls the display direction of string.
*/
#define lcd_put_str(s, l, c) \
do { \
	lcd_put_cursor(l, c); \
	lcd_append_str(s); \
} while(0)

//void lcd_put_str(char *s, uint8_t l, uint8_t c);


#ifdef __cplusplus
}
#endif

#endif  //__CCC_LCD1602_DRV_H__