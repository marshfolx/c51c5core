#include "include/uart0.h"
#include "include/timer0_1.h"

//may not accurate.
#define BAUD_RATE_9600_SET_VAL (256 - (int)(SYS_CLK_FREQ / 32 / 9600))

void uart0_beat_9k6() {
	//setup Timer1
	TR1 = 0;
	t1_set_mode(t1_timer_8_auto);

	TH1 = TL1 = BAUD_RATE_9600_SET_VAL;
	TR1 = 1;
}