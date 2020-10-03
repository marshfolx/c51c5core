#include "delay.h"

//微秒级延时

//used when clock cycles takes more than one us
void _delay_us_more_than_one(uint16_t u) {
	u /= (int)DELAY_US_FACTOR;
	while(--u);
}

//used when clock cycles takes less than one us
void _delay_us_less_than_one(uint16_t u) {
	if(DELAY_US_FACTOR < 4) {
		/*  duration(us) = (2 + 2 * u ) * DELAY_US_FACTOR
		*/
		while(--u);
	}
	else {
		//Assume sys clock frequency is 4, 6, 8, 10, ... MHz
		uint8_t j = (int)((DELAY_US_FACTOR - 4) / 2);
		/* u == 0, loop takes 2 cycles;
		*  u == 1, j == 0, loop takes 6 cycles;
		*  u == 1, j == 1, loop takes 8 cycles;
		*  u == n, j == m, loop takes 2 + ( 4 + 2 * j) * u;
		*/
		while(--u) {
			while(--j);    //DJNZ R#
		}
	}
}


//毫秒级延时
void delay_ms(uint32_t m) {
	while(--m) {
		delay_us(1000);
	}
}