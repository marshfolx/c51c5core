#ifndef __CCC_IO_X__H__
#define __CCC_IO_X__H__


//#include "8051inc_error_hide.h"
#include <REG51.H>
#include "stdint.h"


#define int0_set_trigger_low_level() \
do { \
	IT0 = 0; \
} while (0)


#define int0_set_trigger_falling_edge() \
do { \
	IT0 = 1; \
} while(0)


#define enable_int0() \
do { \
	ET0 = 1; \
} while(0)


#define disable_int0() \
do { \
	ET0 = 0; \
} while(0)


#define int1_set_trigger_low_level() \
do { \
	IT1 = 0; \
} while(0)


#define int1_set_tirgger_falling_edge() \
do { \
	IT1 = 1; \
} while(0)


#define enable_int1() \
do { \
	ET1 = 1; \
} while(0)	


#define disable_int1() \
do { \
	ET1 = 0; \
} while(0)


#define high_half(b) (b >> 4)


#define low_half(b) (b & 0x0f)


#define bit_flip(b, pos) (b ^ (1 << pos))


//assume true == (0x01), false == (0x00), if bool is bit, just use ~ of ! instead.
#define bool_flip(b) (b ^ 1)



#endif  //!__IO_X__H__