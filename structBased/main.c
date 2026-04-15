// 0: Include standard integer types header for fixed-width integer types
#include <stdint.h>

// 1: GPIO_TypeDef structure definition
typedef struct
{
	volatile uint32_t MODER;		/*offset: 0x00	*/
	volatile uint32_t OTYPER;		/*offset: 0x04	*/
	volatile uint32_t OSPEEDR;		/*offset: 0x08	*/
	volatile uint32_t PUPDR;		/*offset: 0x0C	*/
	volatile uint32_t IDR;			/*offset: 0x10	*/
	volatile uint32_t ODR;			/*offset: 0x14	*/
	volatile uint32_t BSRR;			/*offset: 0x18	*/
	volatile uint32_t LCKR;			/*offset: 0x1C	*/
	volatile uint32_t AFRL;			/*offset: 0x20	*/
	volatile uint32_t AFRH;			/*offset: 0x24	*/
} GPIO_TypeDef;

// 2: RCC_TypeDef structure definition
typedef struct
{
	volatile uint32_t PLACEHOLDER[12];	/*12 x 4B = 0x30-1	*/
	volatile uint32_t AHB1ENR;			/*offset: 0x30		*/
} RCC_TypeDef;

// 3: Base address definition
#define GPIOD_BASE		0x40020C00
#define RCC_BASE		0x40023800

// 4: Peripheral pointer definitions
#define RCC 	((RCC_TypeDef*) RCC_BASE)
#define GPIOD 	((GPIO_TypeDef*) GPIOD_BASE)

// 5: bit mask for enabling GPIOD (bit 3)
#define GPIODEN		(1U<<3);
// 6: bit mask for GPIOD pin12
#define PIN12	(1U<<12);
// 7: alias for representing LED pin
#define LED_PIN		PIN12

// 8: start of main function
int main(void)
{
	// 9: enable clock access to gpiod
	RCC->AHB1ENR |= GPIODEN;
	
	GPIOD->MODER |= (1U<<24);
	GPIOD->MODER &= ~(1U<<25);
	
	while(1)
	{
		GPIOD->ODR ^= LED_PIN;
		for(volatile int i=0; i<100000; i++) ;
	}
	return 0;
}
