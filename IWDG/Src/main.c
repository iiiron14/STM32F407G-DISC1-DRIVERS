#include "iwdg.h"
#include "uart.h"
#include "gpio.h"
#include "gpio_exti.h"
#include <stdio.h>

static void check_reset_source(void);
uint8_t g_btn_press;
int main(void)
{
	uart_init();
	led_init();
	pa0_exti_init();
	check_reset_source();
	iwdg_init();

	while(1)
	{
		if(g_btn_press != 1)
		{
			iwdg_kick();
			led_toggle();
			for(volatile int i=0;i<90000; i++) ; // delay
		}
	}
}

static void check_reset_source(void)
{
}


















