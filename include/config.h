
#ifndef __CONFIG__H__
#define __CONFIG__H__


#include "io_x.h"


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





#endif  //!__CONFIG__H__