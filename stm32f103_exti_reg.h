/*
 * STM32F103 EXTI register definitions
 * Part of STM32F103 register and peripherals library
 *
 * Dpcumentation available in the provided MD file.
 *
 * (c) 2019 Dmitry Reznikov ontaelio(at)gmail.com
 *
 * Can be freely used according to the GNU GPL license.
 */

#ifndef STM32F103_EXTI_REG_H_
#define STM32F103_EXTI_REG_H_

#include <stdio.h>
#include <stdint.h>

#define _EXTI_(mem_offset) (*(volatile uint32_t *)(0x40010400 + (mem_offset)))

//EXTI registers
#define EXTI_IMR	0x00
#define EXTI_EMR	0x04
#define EXTI_RTSR	0x08
#define EXTI_FTSR	0x0C
#define EXTI_SWIER	0x10
#define EXTI_PR		0x14

#endif /* STM32F103_EXTI_REG_H_ */
