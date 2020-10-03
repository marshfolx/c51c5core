
#ifndef C51C5CORE_H
#define C51C5CORE_H


/*
	C51 C5 Core == A library wraps almost all registers' operations of 8051 core.
*/


/* Assume any 8051/8052 compatible device at least meets following requirements (registers & hardware spec):
*  1. Timer0/1      : TCON, TMOD, TL0, TH0, TL1, TH1;
*  2. Power Control : PCON;
*  3. UART0         : SBUF, SCON;
*  4. Interrupt     : IE, IP;
*  5. IO            : INT0, INT1;
*
*  6. ROM space        : enough to waste;
*  7. RAM space        : 256 byte idata at least;
*  8. System frequency : fast enough for inefficient code;
*  
*  and is compatible with <REG51.h>
*/


#include "io_x.h"    //including sfr definitions

#include "macrobin.h"

#include "power.h"

#include "uart0.h"

#include "interrupt.h"

#include "timer01.h"

#include "uart0.h"

#endif