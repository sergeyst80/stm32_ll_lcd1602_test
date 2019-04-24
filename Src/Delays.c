#include "Delays.h"

void Delay_us_ms(enum DelayType us_ms, uint32_t delay)
{
	uint32_t count = 0;
	
	switch (us_ms)
	{
		case USEC: 
			LL_TIM_SetPrescaler(DELAY_TIM, SystemCoreClock/1000000 - 1);
		break;
		case MSEC:
			LL_TIM_SetPrescaler(DELAY_TIM, SystemCoreClock/1000 - 1);
		break;
	}
	LL_TIM_SetAutoReload(DELAY_TIM, 1000);
	LL_TIM_SetCounter(DELAY_TIM, 0);
	LL_TIM_EnableCounter(DELAY_TIM);
	while(count + LL_TIM_GetCounter(DELAY_TIM) < delay)
	{
		if (LL_TIM_IsActiveFlag_UPDATE(DELAY_TIM))
		{
				count +=1000;
				LL_TIM_ClearFlag_UPDATE(DELAY_TIM);
		}
			
	}
	LL_TIM_DisableCounter(TIM3);
}

