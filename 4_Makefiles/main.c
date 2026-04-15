// 1: base address for peripherals
#define PERIPH_BASE				(0x40000000UL)
// 2: offset for AHB1 peripheral bus
#define AHB1PERIPH_OFFSET		(0x00020000UL)
// 3: base address for AHB1 peripherals
#define AHB1PERIPH_BASE			(PERIPH_BASE + AHB1PERIPH_OFFSET)
// 4: offset for GPIOD
#define GPIOD_OFFSET			(0x0C00UL)
// 5: base address for GPIOD
#define GPIOD_BASE				(AHB1PERIPH_BASE + GPIOD_OFFSET)
// 6: offset for RCC
#define RCC_OFFSET				(0x3800UL)
// 7: base address for RCC
#define RCC_BASE				(AHB1PERIPH_BASE + RCC_OFFSET)
// 8: offset for AHB1EN register
#define AHB1EN_R_OFFSET			(0x30UL)
// 9: address of AHB1EN register
#define RCC_AHB1EN_R			(*(volatile unsigned int *)(RCC_BASE + AHB1EN_R_OFFSET))
// 10: offset for mode register
#define MODE_R_OFFSET			(0x00UL)
// 11: address of GPIOD mode register
#define GPIOD_MODE_R			(*(volatile unsigned int *)(GPIOD_BASE + MODE_R_OFFSET))
// 12: offset for bit set/reset register
#define BSR_R_OFFSET			(0x18UL)
// 13: address of GPIOD bit set/reset register
#define GPIOD_BSR_R				(*(volatile unsigned int *)(GPIOD_BASE + BSR_R_OFFSET))
// 14: bit mask for enabling GPIOD
#define GPIODEN					(1U<<3)
// 15: bit mask for GPIOD pin 12
#define BS_PIN12				(1U<<12)
#define BR_PIN12				(1U<<28)

#define BS_PIN13				(1U<<13)
#define BR_PIN13				(1U<<29)

#define BS_PIN14				(1U<<14)
#define BR_PIN14				(1U<<30)

#define BS_PIN15				(1U<<15)
#define BR_PIN15				(1U<<31)
// 16: alias for PIN12 representing LED pin
#define LED_G_PIN_ON				BS_PIN12
#define LED_G_PIN_OFF				BR_PIN12

#define LED_O_PIN_ON				BS_PIN13
#define LED_O_PIN_OFF				BR_PIN13

#define LED_R_PIN_ON				BS_PIN14
#define LED_R_PIN_OFF				BR_PIN14

#define LED_B_PIN_ON				BS_PIN15
#define LED_B_PIN_OFF				BR_PIN15

// 17: start of main
int main(void)
{
	// 18: enable clock access to GPIOD
	RCC_AHB1EN_R |= GPIODEN;

	GPIOD_MODE_R |= (1U<<24);	// 19: set bit 24 to 1
	GPIOD_MODE_R &= ~(1U<<25);  // 20: set bit 25 to 0

	GPIOD_MODE_R |= (1U<<26);	// 19: set bit 24 to 1
	GPIOD_MODE_R &= ~(1U<<27);  // 20: set bit 25 to 0

	GPIOD_MODE_R |= (1U<<28);	// 19: set bit 24 to 1
	GPIOD_MODE_R &= ~(1U<<29);  // 20: set bit 25 to 0

	GPIOD_MODE_R |= (1U<<30);	// 19: set bit 24 to 1
	GPIOD_MODE_R &= ~(1U<<31);  // 20: set bit 25 to 0

	// 21: start of infinite loop
	while(1)
	{
		// line 22: set PD12 ON (LED_PIN_ON)
		GPIOD_BSR_R = LED_B_PIN_ON;
		GPIOD_BSR_R = LED_G_PIN_ON;
		GPIOD_BSR_R = LED_R_PIN_ON;
		GPIOD_BSR_R = LED_O_PIN_ON;
		
		for(int i=0; i < 100000; i++) ;
		
		GPIOD_BSR_R = LED_B_PIN_OFF;
		GPIOD_BSR_R = LED_G_PIN_OFF;
		GPIOD_BSR_R = LED_R_PIN_OFF;
		GPIOD_BSR_R = LED_O_PIN_OFF;
		
		for(int i=0; i < 100000; i++) ;
	}
	return 0;
}


