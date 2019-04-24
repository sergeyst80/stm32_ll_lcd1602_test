#ifndef __DELAYS_H
#define __DELAYS_H

#ifdef __cplusplus
 extern "C" {
#endif
/*****************************************************************************/

#include "main.h"	 

#define DELAY_TIM TIM3

enum DelayType
{
	USEC,
	MSEC
};	 
	 
void Delay_us_ms(enum DelayType, uint32_t);

/*****************************************************************************/
#ifdef __cplusplus
}
#endif

#endif /* __DELAYS_H */
