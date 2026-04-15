#include "gpio_exti.h"

#define GPIOCEN (1U<<2)
#define SYSCFGEN	(1U<<14)

void pa0_exti_init(void)
{
    __disable_irq();

    // 1. Abilita Clock per GPIOA e SYSCFG
    RCC->AHB1ENR |= (1U << 0);  // GPIOAEN
    RCC->APB2ENR |= (1U << 14); // SYSCFGEN

    // 2. PA0 come Input (00 nei bit 0-1)
    GPIOA->MODER &= ~(3U << 0);

    // 3. Mappa la linea 0 su PORT A
    // EXTICR[0] gestisce le linee 0, 1, 2, 3.
    // I bit [3:0] a 0000 selezionano il PORT A per la linea 0.
    SYSCFG->EXTICR[0] &= ~(0xFU << 0);

    // 4. Configura EXTI Linea 0
    EXTI->IMR  |= (1U << 0);    // Unmask linea 0
    EXTI->RTSR |= (1U << 0);    // Trigger su SALITA (Attivo Alto)
    EXTI->FTSR &= ~(1U << 0);   // No discesa

    // 5. Configura NVIC per EXTI0
    EXTI->PR = (1U << 0);       // Pulisci flag
    NVIC_EnableIRQ(EXTI0_IRQn); // <--- ATTENZIONE: EXTI0_IRQn, non 15_10!

    __enable_irq();
}
