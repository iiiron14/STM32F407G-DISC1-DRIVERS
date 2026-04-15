#include "iwdg.h"

#define IWDG_START			0xCCCCU
#define IWDG_RELOAD			0xAAAAU
#define IWDG_LOAD_EN		0x5555U
#define IWDG_RELOAD_VAL		0xFFFU

#define RVU_FLAG			(1U<<1)
#define PVU_FLAG			(1U<<0)


static uint8_t _iwdg_presc_flag(void);
static uint8_t _iwdg_rld_flag(void);

void iwdg_init(void)
{
	// start the counter
	IWDG->KR = IWDG_START;
	// enable access to IWDG_PR AND IWDG_RLR
	IWDG->KR = IWDG_LOAD_EN;
	// set prescaler value to /32
	IWDG->PR |= (1U<<0);
	IWDG->PR |= (1U<<1);
	IWDG->PR &= ~(1U<<2);
	while(!_iwdg_presc_flag()) ; // not strictly necessary
	// set reload value
	IWDG->RLR = IWDG_RELOAD_VAL;
	while(!_iwdg_rld_flag()) ; // not strictly necessary
	// start to count
	IWDG->KR = IWDG_RELOAD;
}


void iwdg_kick(void)
{
	IWDG->KR = IWDG_RELOAD;
}

static uint8_t _iwdg_presc_flag(void)
{
	while(IWDG->SR & PVU_FLAG) ;
	return 1;
}

static uint8_t _iwdg_rld_flag(void)
{
	while(IWDG->SR & RVU_FLAG) ;
	return 1;
}
