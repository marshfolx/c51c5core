
#include "include/timer01.h"
#include "power.h"
#include "uart0.h"

//may not accurate.
#define BAUD_RATE_9600_SET_VAL (256 - (int)(F_SYS / 32 / 9600))

void uart0_start_9k6() {
	TR1 = 0;
	uart0_set_mode(uart0_variable_8_bit);
	t1_set_mode(t1_timer_8_auto);
	TH1 = TL1 = BAUD_RATE_9600_SET_VAL;
	TR1 = 1;

	RI = TI = 1;    //without this printf won't work.
}