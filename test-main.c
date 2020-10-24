#include "c51c5core.h"
#include "annex/lcd1602_drv.h"
#include "annex/delay.h"
#include "config.h"

#include <STDIO.H>

sbit T = P1^1;
sbit EN = LCD_1602_EN;

int main(void) {
	//EN = 0;
	delay_ms(10);

	lcd_1602_init();
	lcd_put_str("?Hello? ofpeofp", 0, 0);
	lcd_put_str("AAABBB", 0, 7);
	lcd_put_str("ccCCddDD", 1, 0);
	lcd_put_str("CCCCDDDD", 1, 0);


	while(1) {
		T = !T;
		delay_ms(50);
	}
}