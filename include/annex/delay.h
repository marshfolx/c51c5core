
#ifndef CCC_DELAY_H
#define CCC_DELAY_H

#include <stdint.h>

#include "power.h"

#warning "A really not accurate delay implementation"

//used when clock cycles takes more than one us
void _delay_us_more_than_one(uint16_t u);

//used when clock cycles takes less than one us
void _delay_us_less_than_one(uint16_t u);

#ifdef SYS_CLK_MORE_THAN_ONE
	#define DELAY_US_FACTOR (SYS_CLK_PERIOD_NS / 1000.0)
	#define delay_us _delay_us_more_than_one

	#warning "_delay_us_more_than_one"
#else
	#define DELAY_US_FACTOR (1000.0 / SYS_CLK_PERIOD_NS)
	#define delay_us _delay_us_less_than_one

	#warning "_delay_us_less_than_one"
#endif


//毫秒级延时
void delay_ms(uint32_t m);


#endif