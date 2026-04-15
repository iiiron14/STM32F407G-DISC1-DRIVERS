#include <stdio.h>
#include "uart.h"

int main(void)
{
	uart_init();
	while(1)
	{
		printf("Sono una scheda parlante \r\n");
		for(volatile int i=0; i<5000000; i++) ;
	}
}
