#include "gpio.h"
#include "systick.h"

int main(void)
{
	/*Initialize led*/
	led_init();

	while(1)
	{
		/*Delay for 500ms*/
		systick_msec_delay(1000);
		/*Toggle the led*/
		led_toggle();
	}
}
