#include "systick.h"

#define CTRL_ENABLE		(1U<<0)
#define CTRL_CLKSRC		(1U<<2)
#define CTRL_COUNTFLAG	(1U<<16)

/*By default the frequency of the MCU is 16MHz*/
#define ONE_MSEC_LOAD	16000

void systick_msec_delay(uint32_t delay)
{
	/*Load number of clock cycles per millisecond*/
	SysTick->LOAD = ONE_MSEC_LOAD - 1;

	/*Clear SysTick current value register*/
	SysTick->VAL = 0;

	/*Select internal clock source*/
	SysTick->CTRL = CTRL_CLKSRC;

	/*Enable SysTick*/
	SysTick->CTRL |= CTRL_ENABLE;

	for(volatile int i=0; i<delay; i++)
			while(!(SysTick->CTRL & CTRL_COUNTFLAG)) ;

	/*Disable SysTick*/
	SysTick->CTRL = 0;
}
