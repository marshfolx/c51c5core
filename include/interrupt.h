
#ifndef CCC_INTERRUPT_H
#define CCC_INTERRUPT_H

#include "io_x.h"


#define interrupt_enable \
do {                     \
	EA = 1;              \
} while(0)


#define interrupt_shut \
do {                   \
	EA = 0;            \
} while(0)


//FROM: SDCC - mcs51/8051.h - GPLv2
/* Interrupt numbers: address = (number * 8) + 3 */
#define IE0_VECTOR      0       /* 0x03 external interrupt 0 */
#define TF0_VECTOR      1       /* 0x0b timer 0 */
#define IE1_VECTOR      2       /* 0x13 external interrupt 1 */
#define TF1_VECTOR      3       /* 0x1b timer 1 */
#define SI0_VECTOR      4       /* 0x23 serial port 0 */


//iv == interrupt vector
#define iv_int0   IE0_VECTOR
#define iv_int1   IE1_VECTOR
#define iv_t0     IT0_VECTOR
#define iv_t1     IT1_VECTOR
#define iv_uart0  SI0_VECTOR


#endif