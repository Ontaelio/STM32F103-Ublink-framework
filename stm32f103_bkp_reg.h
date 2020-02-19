/*
 * STM32F103 BKP register definitions
 * Part of STM32F103 register and peripherals library
 *
 * Dpcumentation available in the provided MD file.
 *
 * (c) 2019 Dmitry Reznikov ontaelio(at)gmail.com
 *
 * Can be freely used according to the GNU GPL license.
 */

#ifndef STM32F103_BKP_REG_H_
#define STM32F103_BKP_REG_H_

#include <stdio.h>

#define _BKP_(mem_offset) (*(volatile uint32_t *)(0x40006C00 + (mem_offset)))

//BKP registers
#define BKP_DR1		0x04 //10x16 bits
#define BKP_DR2		0x08
#define BKP_DR3		0x0C
#define BKP_DR4		0x10
#define BKP_DR5		0x14
#define BKP_DR6		0x18
#define BKP_DR7		0x1C
#define BKP_DR8		0x20
#define BKP_DR9		0x24
#define BKP_DR10	0x28

#define BKP_RTCCR	0x2C
#define BKP_CR		0x30
#define BKP_CSR		0x34

#ifndef __STM32F10x_H //avoid redefining if CMSIS library present

//BKP values
#define BKP_RTCCR_CAL	0x007F //mask
#define BKP_RTCCR_CCO	0x0080
#define BKP_RTCCR_ASOE	0x0100
#define BKP_RTCCR_ASOS	0x0200

#define BKP_CR_TPE		0x0001
#define BKP_CR_TPAL		0x0002

#define BKP_CSR_CTE		0x0001
#define BKP_CSR_CTI		0x0002
#define BKP_CSR_TPIE	0x0004
#define BKP_CSR_TEF		0x0100
#define BKP_CSR_TIF		0x0200

#endif //CMSIS stuff

#endif /* STM32F103_BKP_REG_H_ */
