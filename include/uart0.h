#ifndef __CCC_UART0__H__
#define __CCC_UART0__H__

//#include "8051inc_error_hide.h"
#include "io_x.h"
#include "power.h"

enum _uart0_mode {
	fixed_8_bit = 0x00,    //fixed baud rate = F_sys / 12
	fixed_9_bit = 0x80,    //fixed baud rate = Fsys / 128 or Fsys / 32 (speed doubled)
	variable_8_bit = 0x40, //variable baud rate = F_ovf_T1 
	variable_9_bit = 0xc0, //variable baud rate = F_ovf_T1
};
typedef enum _uart0_mode uart0_mode;


static inline void uart0_set_mode(uart0_mode m) {
	SCON &= 0x3f;
	SCON |= m;  //when m is fixed_8_bit (0), this line is waste.
}


//start UART at variable baud rate mode.
//Start Timer1 at 8bit auto reload mode and set baud rate at 9600.
//the default implementation in uart0.c assumes that the clock frequency of timer1 equals to F_sys, no other prescaler.
extern void uart0_beat_9k6();


#define uart0_enable_multi() \
do { \
	SM2 = 1; \
} while(0)


#define uart0_disable_multi() \
do { \
	SM2 = 0 \
} while(0)


#define uart0_enable_rx() \
do { \
	REN = 1; \
} while(0)


#define uart0_disable_rx() \
do { \
	REN = 0; \
} while(0)


#define uart0_enable_interrupt() \
do { \
	ES = 1; \
} while(0)


#define uart0_disable_interrupt() \
do { \
	ES = 0; \
} while(0)


#endif  //!__UART0__H__