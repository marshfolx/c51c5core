
#ifndef CCC_POWER_H
#define CCC_POWER_H


/* system clock and power management.
*/

//#include "8051inc_error_hide.h"
#include "io_x.h"
#include "reg_x.h"

#include "config.h"

#ifndef F_CPU    //in Hz
	#warning "F_CPU should be defined."
    #define F_CPU (12000000)
#endif


#ifndef SYS_CLK_DIV_12
	#warning "SYS_CLK_DIV_12 should be defined either (0) -> false (default) or (1) -> true"
#endif

//if the CPU clock is 12 divided from cpu clock source (traditional 8051 style).
#if SYS_CLK_DIV_12 == 0    
	#define EXTRA_SYS_CLK_DIV (1)
#else
	#define EXTRA_SYS_CLK_DIV (12)
#endif


#define SYS_CLK_FREQ (F_CPU / EXTRA_SYS_CLK_DIV)  //in Hz
#define F_SYS SYS_CLK_FREQ

#define SYS_CLK_PERIOD_US (1E6 / SYS_CLK_FREQ)    //in microsecond (us)
#define SYS_CLK_PERIOD_NS (1E9 / SYS_CLK_FREQ)    //in nanosecond  (ns)


#if (SYS_CLK_DIV_12 == 0)
	#if (F_CPU < 1000000)  //< 1Mhz
		#define SYS_CLK_MORE_THAN_ONE    //a clock cycle takes more than 1us
	#else
		#define SYS_CLK_LESS_THAN_ONE    //a clock cycle takes less than 1us
	#endif
#else
	#if (F_CPU < 12000000)  //< 12Mhz
		#define SYS_CLK_MORE_THAN_ONE    //a clock cycle takes more than 1us
	#else
		#define SYS_CLK_LESS_THAN_ONE    //a clock cycle takes less than 1us
	#endif
#endif


#define enable_double_uart0_speed() \
do { \
	PCON |= SOMD; \
} while(0)


#define disable_double_uart0_speed() \
do { \
	PCON &= ~SMOD; \
} while(0)


#define power_down() \
do { \
	PCON |= PD; \
} while(0)


#define power_idle() \
do { \
	PCON |= IDL; \
} while(0)


#endif
