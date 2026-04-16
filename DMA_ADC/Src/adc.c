#include "adc.h"

#define GPIOAEN		(1U<<0)
#define ADC1EN		(1U<<8)
#define ADC_CH1		(1U<<0)
#define ADC_SEQ_LEN1	0x00
#define CR2_ADCON	(1U<<0)
#define CR2_CONT	(1U<<1)
#define CR2_SWSTART	(1U<<30)
#define SR_EOC		(1U<<1)

void pa1_adc_init(void)
{
	/*configure ADC GPIO pin*/
	/*enable clock access to GPIOA*/
	RCC->AHB1ENR |= GPIOAEN;

	/*set PA1 to analog mode*/
	GPIOA->MODER |= (1U<<2);
	GPIOA->MODER |= (1U<<3);

	/*configure adc module*/
	/*enable clock access to adc*/
	RCC->APB2ENR |= ADC1EN;

	/*set conversione sequence start*/
	ADC1->SQR3 = ADC_CH1;

	/*set conversione sequence length*/
	ADC1->SQR1 = ADC_SEQ_LEN1;		// stiamo settando tutto il registro a zero, in realtà sarebbero i bit 23...20

	/*enable adc module*/
	ADC1->CR2 |= CR2_ADCON;
}

void start_conversion(void)
{
	/*enable continous conversion*/
	ADC1->CR2 |= CR2_CONT;

	/*start adc conversion*/
	ADC1->CR2 |= CR2_SWSTART;
}

uint32_t adc_read(void)
{
	/*wait for conversion to be complete*/
	while(!(ADC1->SR & SR_EOC)) ;

	/*read converted value*/
	return (ADC1->DR);
}












