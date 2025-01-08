/*
 * EXT_INT.c
 *
 *  Created on: ???/???/????
 *      Author: dell
 */

#include "BIT_MATH.h"
#include "REG.h"

void EXT_INT_0_INIT(void)
{
	SET_BIT(SREG,7);        /*_TO_ENABLE_THE_GLOBAL_INT_*/
	SET_BIT(GICR,6);        /*_TO_ENABLE_INT_0_*/
	CLR_BIT(MCUCR,0);       /* to make interrupt with FALLING edge*/
	SET_BIT(MCUCR,1);       /*                //                  */
}
