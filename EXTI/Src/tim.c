#include "tim.h"
#define TIM2EN		(1U<<0)
#define CR1_CEN		(1U<<0)

void tim2_1hz_init(void)
{
	/*Enable clock access to tim2*/
	RCC->APB1ENR |= TIM2EN;

	/*set prescaler value*/
	TIM2->PSC = 1600 - 1;
	/*set autoreload valulre*/
	TIM2->ARR = 10000 - 1;
	/*clear counter*/
	TIM2->CNT = 0;

	/*enable timer*/
	TIM2->CR1 = CR1_CEN;
}
