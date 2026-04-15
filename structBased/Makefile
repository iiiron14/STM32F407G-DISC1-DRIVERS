FILENAME =structBased
CC = arm-none-eabi-gcc
CFLAGS = -c -mcpu=cortex-m4 -mthumb -std=gnu11
LDFLAGS = -nostdlib -T stm32_ls.ld -Wl,-Map=$(FILENAME).map

final : $(FILENAME).elf

main.o : main.c
	$(CC) $(CFLAGS) $^ -o $@

stm32f407_startup.o : stm32f407_startup.c
	$(CC) $(CFLAGS) $^ -o $@

$(FILENAME).elf : main.o stm32f407_startup.o
	$(CC) $(LDFLAGS) $^ -o $@

load :
	openocd -f board/stm32f4discovery.cfg
clean:
	del	-f *.o *.elf *.map