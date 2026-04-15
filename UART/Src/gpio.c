#include <gpio.h>

#define GPIODEN		(1U<<3)
#define GPIOAEN		(1U<<0)

#define LED_BS12	(1U<<12)
#define LED_BR12	(1U<<28)

#define LED_PIN		(1U<<12)
#define BTN_PIN		(1U<<0)

void led_init(void)
{
	/*Enable clock access to GPIOD*/
	RCC->AHB1ENR |= GPIODEN;
	GPIOD->MODER |= (1U<<24);
	GPIOD->MODER &= ~(1U<<25);
}

void button_init(void)
{
	/*enable clock access to GPIOA*/
	RCC->AHB1ENR |= GPIOAEN;
	GPIOA->MODER &= ~(1U<<0);
	GPIOA->MODER &= ~(1U<<1);
}

void led_on(void)
{
	/*set PA12 on*/
	GPIOD->BSRR |= LED_BS12;
}

void led_off(void)
{
	/*set PA12 off*/
	GPIOD->BSRR |= LED_BR12;
}

void led_toggle(void)
{
	/*toggle PD12*/
	GPIOD->ODR ^= LED_PIN;
}

bool get_btn_state(void)
{
	/*note: BTN is active high*/
	/*check if BTN is pressed*/
	if(GPIOA->IDR & BTN_PIN){
		return true;
	}
	else{
		return false;
	}
}


