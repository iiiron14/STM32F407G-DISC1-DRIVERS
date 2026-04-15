#ifndef IWDG_H__
#define IWDG_H__

#include <stdint.h>
#include "stm32f4xx.h"

void iwdg_init(void);
void iwdg_kick(void);

#endif // IWDG_H__
