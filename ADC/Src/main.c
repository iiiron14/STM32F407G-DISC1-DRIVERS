#include <stdio.h>
#include "adc.h"
#include "uart.h"

int sensor_value;
uint32_t millivolts;

int main(void)
{
	uart_init();

	pa1_adc_init();

	start_conversion();

	while(1)
	{
		sensor_value = adc_read();

		millivolts = (sensor_value * 3000) / 4095;

		printf("Sensor value: %lu.%03lu V\r\n", millivolts / 1000, millivolts % 1000);
		for(volatile int i=0; i<100000; i++) ;
	}
}
