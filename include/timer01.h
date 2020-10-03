
#ifndef CCC_TIMER01_H
#define CCC_TIMER01_H

#include "io_x.h"
#include "reg_x.h"

enum _t0_mode {
	t0_timer_13 = 0x00,           //13位定时器
	t0_timer_16 = 0x01,           //16位定时器
	t0_timer_8_auto = 0x02,       //8位自动重装定时器
	t0_timer_8_special = 0x03,    //两个8位定时器

	t0_counter_13 = 0x04,         //13位计数器
	t0_counter_16,                //16位计数器
	t0_counter_8_auto,            //8位自动重装计数器
	t0_counter_8_special,         //两个8位计数器
};
typedef enum _t0_mode t0_mode;

enum _t1_mode {
	t1_timer_13 = 0x00,
	t1_timer_16 = 0x10,
	t1_timer_8_auto = 0x20,
	t1_timer_halt = 0x30,

	t1_counter_13 = 0x40,
	t1_counter_16 = 0x50,
	t1_counter_8_auto = 0x60,
	t1_counter_halt = 0x70,
};
typedef enum _t1_mode t1_mode;

//these three functions can not be replaced by macro,
//otherwise the intellisense to enum arguments wont work.

//set mode, meanwhile clear gate control.
static inline void t0_set_mode(t0_mode m) {
	TMOD &= ~(T0_CT | T0_M1 | T0_M0 | T0_GATE);
	TMOD |= (uint8_t)(m);
}

//set mode, meanwhile clear gate control.
static inline void t1_set_mode(t1_mode m) {
	TMOD &= ~(T1_CT | T1_M1 | T1_M0 | T1_GATE);
	TMOD |= (uint8_t)(m);
}

//set mode for both t0/ t1, meanwhile clear gate control.
static inline void t01_set_tmod(t0_mode m0, t1_mode m1) {
	TMOD = (uint8_t)m0 | (uint8_t)m1;
}


//refer to data sheet to see what the gate control actually is.
#define t0_enable_gate_control() \
do { \
	TMOD |= T0_GATE; \
} while(0)


#define t0_disable_gate_control() \
do { \
	TMOD &= ~T0_GATE; \
} while(0)


#define t1_enable_gate_control() \
do { \
	TMOD |= T1_GATE; \
} while(0)


#define t1_disable_gate_control() \
do { \
	TMOD &= ~T1_GATE; \
} while(0)


#define t0_enable_interrupt() \
do { \
	ET0 = 1; \
} while(0)


#define t0_disable_interrupt() \
do { \
	ET0 = 0; \
} while(0)


#define t1_enable_interrupt() \
do { \
	ET1 = 1; \
} while(0)


#define t1_disable_interrupt() \
do { \
	ET1 = 0; \
} while(0)


#define t0_start() \
do { \
	TR0 = 1; \
} while(0)


//unless timer mode is set on timer_8_auto, when timer count exceeds TOP, TRn is cleared by hardware.
#define t0_stop() \
do { \
	TR0 = 0; \
} while(0)


#define t1_start() \
do { \
	TR1 = 1; \
} while(0)


#define t1_stop() \
do { \
	TR1 = 0; \
} while(0)


// 'init_16'  should be constexpr
#define t0_set_val16(init_16) \
do { \
	TL0 = (uint8_t)(init_16 & 0x00ff); \
	TH0 = (uint8_t)(init_16 >> 8); \
} while(0)


// 'init_16' should be constexpr
#define t1_set_val16(init_16) \
do { \
	TL1 = (uint8_t)(init_16 & 0x00ff); \
	TH1 = (uint8_t)(init_16 >> 8); \
} while(0)


#endif