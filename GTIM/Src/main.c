#include "gpio.h"
#include "tim.h"

int main(void)
{
	/*Initialize led*/
	led_init();
	/*Initialize timer*/
	tim2_1hz_init();
	while(1)
	{
		led_toggle();
		/*wait for uif*/
		while(!(TIM2->SR & SR_UIF)) ;
		/*Clear uif*/
		TIM2->SR &= ~SR_UIF;
	}
}
