#ifndef __CCC_UART0__H__
#define __CCC_UART0__H__

//#include "8051inc_error_hide.h"
#include "io_x.h"


#ifdef __cplusplus
extern "C" {
#endif


//REN is set by default.
enum _uart0_mode {
	uart0_fixed_8_bit = 0x10,    //fixed baud rate = F_sys / 12
	uart0_fixed_9_bit = 0x90,    //fixed baud rate = Fsys / 128 or Fsys / 32 (speed doubled)
	uart0_variable_8_bit = 0x50, //variable baud rate = F_ovf_T1 
	uart0_variable_9_bit = 0xd0, //variable baud rate = F_ovf_T1
};
typedef enum _uart0_mode uart0_mode;


#ifdef  __VSCODE_C51__
	extern void uart0_set_mode(uart0_mode m);
#else
	#define uart0_set_mode(m) \
	do { \
		SCON &= 0x3f; \
		SCON |= m;  /*when m is fixed_8_bit (0), this line is waste.*/ \
	} while(0)
#endif  //__VSCODE_C51__


//Start UART at variable baud rate mode.
//Start Timer1 at 8-bit auto reload mode and set baud rate at 9600 or 9k6.
//The default implementation in uart0.c assumes that the clock frequency of timer1 equals to F_SYS.
//The init value of Timer1 is calculated as (256 - F_CPU / 12 / 32 / 9600).
//SMOD bit in PCON can double this frequency to 19200 or 19k2.
extern void uart0_start_9k6();


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


#ifdef __cplusplus
}
#endif

#endif  //!__UART0__H__