/*
 * STM32F103 RTC register definitions
 * Part of STM32F103 register and peripherals library
 *
 * Dpcumentation available in the provided MD file.
 *
 * (c) 2019 Dmitry Reznikov ontaelio(at)gmail.com
 *
 * Can be freely used according to the GNU GPL license.
 */

#ifndef STM32F103_RTC_REG_H_
#define STM32F103_RTC_REG_H_

#include <stdio.h>

#define _RTC_(mem_offset) (*(volatile uint32_t *)(0x40002800 + (mem_offset)))

//RTC registers
#define RTC_CRH		0x00
#define RTC_CRL		0x04
#define RTC_PRLH	0x08
#define RTC_PRLL	0x0C
#define RTC_DIVH	0x10
#define RTC_DIVL	0x14
#define RTC_CNTH	0x18
#define RTC_CNTL	0x1C
#define RTC_ALRH	0x20
#define RTC_ALRL	0x24

//fast access using bit-band aliases (select registers)
#define BB_RTC_CRL_SECF	*(volatile uint32_t *) 0x42050080
#define BB_RTC_CRL_ALRF	*(volatile uint32_t *) 0x42050084
#define BB_RTC_CRL_OWF	*(volatile uint32_t *) 0x42050088

#define BB_RTC_CRH_SECIE *(volatile uint32_t *) 0x42050000
#define BB_RTC_CRH_ALRIE *(volatile uint32_t *) 0x42050004
#define BB_RTC_CRH_OWIE	 *(volatile uint32_t *) 0x42050008

#ifndef __STM32F10x_H //avoid redefining if CMSIS library present

//RTC values
#define RTC_CRH_SECIE	0x0001
#define RTC_CRH_ALRIE	0x0002
#define RTC_CRH_OWIE	0x0004

#define RTC_CRL_SECF	0x0001
#define RTC_CRL_ALRF	0x0002
#define RTC_CRL_OWF		0x0004
#define RTC_CRL_RSF		0x0008
#define RTC_CRL_CNF		0x0010
#define RTC_CRL_RTOFF	0x0020

#endif //CMSIS stuff

#endif /* STM32F103_RTC_REG_H_ */
