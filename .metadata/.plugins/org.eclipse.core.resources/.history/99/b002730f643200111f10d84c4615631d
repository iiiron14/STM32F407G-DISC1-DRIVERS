#include "bmp280.h"
#include <stdio.h>

BMP280_CALIB_COEFF_TypeDef coeff;
int32_t T;
uint32_t P;
uint8_t chip_id = 0;

int main(void)
{
	uart_init();

	bmp280_init();

	bmp280_read_calibration(&coeff);

	normal_mode_en();

	while(1)
	{
		bmp280_read(0xD0, &chip_id, 1);

		printf("Chip ID letto: 0x%02X (Dovrebbe essere 0x58)\r\n", chip_id);
		T = read_temp_raw();
		P = read_press_raw();

		T = compensate_T_int32(T, &coeff);
		P = compensate_P_int64(P, &coeff);

		printf("Temperature : %ld.%02ld °C\r\n", T/100, T%100);
		printf("Pressure    : %lu.%02lu hPa\r\n\n", (P/256) / 100, (P/256) % 100);

		for(volatile int i=0; i<100000; i++) ;
	}
}
