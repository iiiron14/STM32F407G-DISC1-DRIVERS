#include "spi.h"
#define SPI1EN		(1U<<12)
#define GPIOAEN		(1U<<0)
#define SR_TXE		(1U<<1)
#define SR_RXNE		(1U<<0)
#define SR_BSY		(1U<<7)

void spi_gpio_init(void)
{
	RCC->AHB1ENR |= GPIOAEN;

	/*set PA5,6,7 mode to alternate function*/
	GPIOA->MODER &= ~(1U<<10);
	GPIOA->MODER |= (1U<<11);

	GPIOA->MODER &= ~(1U<<12);
	GPIOA->MODER |= (1U<<13);

	GPIOA->MODER &= ~(1U<<14);
	GPIOA->MODER |= (1U<<15);

	/*set PA9 as output pin*/
	GPIOA->MODER |= (1U<<18);
	GPIOA->MODER &= ~(1U<<19);

	/*set PA5,6,7 alternate function type to SPI1*/
	GPIOA->AFR[0] |= (1U<<20);
	GPIOA->AFR[0] &= ~(1U<<21);
	GPIOA->AFR[0] |= (1U<<22);
	GPIOA->AFR[0] &= ~(1U<<23);

	GPIOA->AFR[0] |= (1U<<24);
	GPIOA->AFR[0] &= ~(1U<<25);
	GPIOA->AFR[0] |= (1U<<26);
	GPIOA->AFR[0] &= ~(1U<<27);

	GPIOA->AFR[0] |= (1U<<28);
	GPIOA->AFR[0] &= ~(1U<<29);
	GPIOA->AFR[0] |= (1U<<30);
	GPIOA->AFR[0] &= ~(1U<<31);
}

void spi1_config(void)
{
	/*enable clock access to SPI1 module*/
	RCC->APB2ENR |= SPI1EN;

	/*set clock to fPCLK/4*/
	SPI1->CR1 |= (1U<<3);
	SPI1->CR1 &= ~(1U<<4);
	SPI1->CR1 &= ~(1U<<5);

	/*set CPOL to 1 and CPHA to 1*/
	SPI1->CR1 |= (1U<<0);
	SPI1->CR1 |= (1U<<1);

	/*enable full duplex*/
	SPI1->CR1 &= ~(1U<<10);

	/*set MSB first*/
	SPI1->CR1 &= ~(1U<<7);

	/*set mode to MASTER*/
	SPI1->CR1 |= (1U<<2);

	/*set 8 bit data mode*/
	SPI1->CR1 &= ~(1U<<11);

	/*select software slave management*/
	SPI1->CR1 |= (1U<<9);
	SPI1->CR1 |= (1U<<8);

	/*enable SPI module*/
	SPI1->CR1 |= (1U<<6);
}

void spi1_trasmit(uint8_t *data, uint32_t size)
{
	uint32_t i=0;
	uint8_t temp;
	while(i<size)
	{
		/*wait until TXE is set*/
		while(!(SPI1->SR & SR_TXE)) ;

		/*write data to the data register*/
		SPI1->DR = data[i];
		i++;
	}
	/*wait until TXE is set*/
	while(!(SPI1->SR & SR_TXE)) ;

	/*wait for busy flag to reset*/
	while(!(SPI1->SR & SR_BSY)) ;

	/*clear OVR flag*/
	temp = SPI1->DR;
	temp = SPI1->SR;
}

void spi1_receive(uint8_t *data, uint32_t size)
{
	while(size)
	{
		/*send dummy data*/
		SPI1->DR = 0;
		/*wait for RXNE flag to be set*/
		while(!(SPI1->SR & SR_RXNE)) ;
		/*read data from data register*/
		*data++ = SPI1->DR;
		size--;
	}
}

void cs_enable(void)
{
	GPIOA->ODR &= ~(1U<<9);
}

void cs_disable(void)
{
	GPIOA->ODR |= (1U<<9);
}






