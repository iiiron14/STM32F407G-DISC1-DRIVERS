#include <stdio.h>
#include "uart.h"
#include "gpio.h"
#include "gpio_exti.h"

static void exti_callback(void);

volatile uint8_t btn_pressed;

int main(void)
{
    uart_init();
    led_init();
    pa0_exti_init();

    while(1)
    {
        if(btn_pressed == 1)
        {
            exti_callback();
            // for(volatile int i=0; i<1000000; i++) ; // Debouncing
            btn_pressed = 0;
        }
    }
}

static void exti_callback(void)
{
	printf("BTN pressed...\r\n");
	led_toggle();
}

void EXTI0_IRQHandler(void)
{
    // Controlla se l'interrupt proviene dalla linea 0
    if((EXTI->PR & (1U << 0)) != 0)
    {
        // Pulisci il flag PR
        EXTI->PR |= (1U << 0);
        btn_pressed = 1;
    }
}
