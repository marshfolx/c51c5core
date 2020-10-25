
#ifndef __CCC_CONFIG__H__
#define __CCC_CONFIG__H__


#include "io_x.h"

#ifdef __CCC_CONFIG_EXTEND__
	/* if __CCC_CONFIG_EXTEND__ defined, this config file will try to include another config.h file outside this repo folder,
	*  thus all the configurations can be replaced without directly modifing this file.
	*  __CCC_CONFIG_EXTEND__ should be set as compiler predefined flag to affect all compile module.
	*  The replacing config.h should use other flag as include guard rather than this __CCC_CONFIG__H__.
	*/

	#include "../../include/config.h"

#else


/*! \file
*  In this file placed the system configurations.
*/


/*! \def
*  F_CPU should be defined like these:
*  #define F_CPU (3000000)     //3 Mhz
*  #define F_CPU (6000000)     //6 Mhz
*  #define F_CPU (11059200)    //11.0592 Mhz
*  #define F_CPU (12000000)    //12 Mhz
*  #define F_CPU (16000000)    //16 Mhz
*  #define F_CPU (24000000)    //24 Mhz
*
*  F_CPU is the frequency of clock source driving cpu,
*  the clock source may be prescaled from F_OSC which is the frequency of oscillator.
*
*  The traditional 8051 cpu has a 12-divided frequency from F_CPU called 'machine cycle',
*  which is defined as F_SYS or SYS_CLK_FREQ in power.h.
*  However modern 8051 variation is faster a lot which has the F_SYS equal with F_CPU.
*  F_SYS can be configured by SYS_CLK_DIV_12 macro, through which whether the system is 12-divided is defined.
*/
#define F_CPU (11059200)


// define if the system clock is 12 divided from F_CPU, 0 for false, 1 for true.
#define SYS_CLK_DIV_12 (1)


// annex/lcd_1602_drv
//LCD 1602 端口定义
#define LCD_1602_DP P0   //8-bit data port
#define LCD_1602_RS (P3^5)
#define LCD_1602_RW (P3^6)
#define LCD_1602_EN (P3^4)


#endif

#endif  //!__CCC_CONFIG__H__