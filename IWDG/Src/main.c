#include "iwdg.h"
#include "uart.h"
#include "gpio.h"
#include "gpio_exti.h"
#include <stdio.h>

#define LINE0					(1U<<0)


static void check_reset_source(void);
static void exti_callback(void);

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
	if((RCC->CSR & RCC_CSR_IWDGRSTF) == RCC_CSR_IWDGRSTF)
	{
		// clear IWDG reset flag
		RCC->CSR = RCC_CSR_RMVF;

		led_on();
		printf("Reset was caused by IWDG \r\n");

		while(g_btn_press != 1) ;

		g_btn_press = 0;
	}
}

static void exti_callback(void)
{
	g_btn_press = 1;
}

void EXTI0_IRQHandler(void)
{
	if((EXTI->PR & LINE0) != 0)
	{
		// clear flag
		EXTI->PR |= LINE0;
		exti_callback();
	}
}
















