/*
 * STM32F103 PWR register definitions
 * Part of STM32F103 register and peripherals library
 *
 * Dpcumentation available in the provided MD file.
 *
 * (c) 2019 Dmitry Reznikov ontaelio(at)gmail.com
 *
 * Can be freely used according to the GNU GPL license.
 */

#ifndef STM32F103_PWR_REG_H_
#define STM32F103_PWR_REG_H_

#include <stdio.h>
#include <stdint.h>

#define _PWR_(mem_offset) (*(volatile uint32_t *)(0x40007000 + (mem_offset)))

//PWR registers
#define PWR_CR		0x00
#define PWR_CSR		0x04

//ARM registers
#define SYSTEM_CONTROL_REGISTER *(volatile uint32_t *) 0xE000ED10

//ARM values
#define SLEEPONEXIT	0x00000002
#define DEEPSLEEP	0x00000004
#define SEVONPEND	0x00000010

#ifndef __STM32F10x_H //avoid redefining if CMSIS library present

//PWR values
#define PWR_CR_LPDS		0x0001
#define PWR_CR_PDDS		0x0002
#define PWR_CR_CWUF		0x0004
#define PWR_CR_CSBF		0x0008
#define PWR_CR_PVDE		0x0010
#define PWR_CR_PLS		0x00E0 //map
#define PWR_CR_DBP		0x0100

#define PWR_CSR_WUF		0x0001
#define PWR_CSR_SBF		0x0002
#define PWR_CSR_PVDO	0x0004
#define PWR_CSR_EWUP	0x0100

#endif //CMSIS stuff

#endif /* STM32F103_PWR_REG_H_ */
