#include "dma_adc.h"

#define GPIOAEN					(1U<<0)

#define DMA2EN					(1U<<22)
#define DMA1_SCR_EN				(1U<<0)
#define DMA_SCR_MINC			(1U<<10)
#define DMA_SCR_PINC			(1U<<9)
#define DMA_SCR_CIRC			(1U<<8)
#define DMA_SCR_TCIE			(1U<<4)
#define DMA_SCR_TEIE			(1U<<2)
#define DMA_SFCR_DMDIS			(1U<<2)

#define ADC1EN		(1U<<8)
#define CR1_SCAN	(1U<<8)
#define CR2_DMA		(1U<<8)
#define CR2_DDS		(1U<<9)
#define CR2_ADCON	(1U<<0)
#define CR2_CONT	(1U<<1)
#define CR2_SWSTART	(1U<<30)


uint16_t adc_raw_data[NUM_CHAN];



void dma1_init(void)
{
	/******GPIO config******/
	RCC->AHB1ENR |= GPIOAEN;

	// set PA0, PA1 to analog mode
	GPIOA->MODER |= (1U<<0);
	GPIOA->MODER |= (1U<<1);

	GPIOA->MODER |= (1U<<2);
	GPIOA->MODER |= (1U<<3);

	/******ADC config******/
	RCC->APB2ENR |= ADC1EN;

	// set sequence length
	ADC1->SQR1 |= (1U<<20);
	ADC1->SQR1 &= ~(1U<<21);
	ADC1->SQR1 &= ~(1U<<22);
	ADC1->SQR1 &= ~(1U<<23);

	// set sequence
	ADC1->SQR3 = (0U<<0) | (1U<<5);

	// enable scan mode
	ADC1->CR1 = CR1_SCAN;

	// select use of DMA
	ADC1->CR2 |= CR2_CONT | CR2_DMA | CR2_DDS;
}
