/*
 * stm32f103_debugLED.h
 *
 *  Created on: 3 но€б. 2019 г.
 *      Author: Ontaelio
 */

#ifndef STM32F103_DEBUGLED_H_
#define STM32F103_DEBUGLED_H_

#include <stm32f103_gpio_reg.h>


inline void setDebugLED()
{
	_RCC_(RCC_APB2ENR) |= RCC_APB2ENR_IOPCEN; //gpioC_init();
	_GPIOC_(GPIOX_CRH) &= ~((8+1)<<20);
	_GPIOC_(GPIOX_CRH) |= (2+4)<<20;
	_GPIOC_(GPIOX_BSRR) = 1<<13;
}


inline void debugLED()
{
	_RCC_(RCC_APB2ENR) |= RCC_APB2ENR_IOPCEN; //gpioC_init();
	_GPIOC_(GPIOX_CRH) &= ~((8+1)<<20);
	_GPIOC_(GPIOX_CRH) |= (2+4)<<20;
	_GPIOC_(GPIOX_BRR) = 1<<13;
}

inline void debugLEDoff()
{
	_GPIOC_(GPIOX_BSRR) = 1<<13;
}


#endif /* STM32F103_DEBUGLED_H_ */
