/*
 * STM32F103 ADC register definitions
 * Part of STM32F103 register and peripherals library
 *
 * Dpcumentation available in the provided MD file.
 *
 * (c) 2020 Dmitry Reznikov ontaelio(at)gmail.com
 *
 * Can be freely used according to the GNU GPL license.
 */

#ifndef STM32F103_ADC_REG_H_
#define STM32F103_ADC_REG_H_

#include <stdio.h>
#include <stdint.h>

#define _ADC1_(mem_offset) (*(volatile uint32_t *)(0x40012400 + (mem_offset)))
#define _ADC2_(mem_offset) (*(volatile uint32_t *)(0x40012800 + (mem_offset)))

//bitband atomic access addresses
//base addresses
#define BB_ADC1_BASE		*(volatile uint32_t *) 0x42248000
#define BB_ADC2_BASE		*(volatile uint32_t *) 0x42250000

//IRQs
#define BB_ADC1_CR1_EOCIE	*(volatile uint32_t *) 0x42248094
#define BB_ADC1_CR1_AWDIE	*(volatile uint32_t *) 0x42248098
#define BB_ADC1_CR1_JEOCIE	*(volatile uint32_t *) 0x4224809C
#define BB_ADC2_CR1_EOCIE	*(volatile uint32_t *) 0x42250094
#define BB_ADC2_CR1_AWDIE	*(volatile uint32_t *) 0x42250098
#define BB_ADC2_CR1_JEOCIE	*(volatile uint32_t *) 0x4225009C

//ADC registers
#define ADC_SR		0x00
#define ADC_CR1		0x04
#define ADC_CR2		0x08
#define ADC_SMPR1	0x0C
#define ADC_SMPR2	0x10
#define ADC_JPFR1	0x14
#define ADC_JPFR2	0x18
#define ADC_JPFR3	0x1C
#define ADC_JPFR4	0x20
#define ADC_HTR		0x24
#define ADC_LTR		0x28
#define ADC_SQR1	0x2C
#define ADC_SQR2	0x30
#define ADC_SQR3	0x34
#define ADC_JSQR	0x38
#define ADC_JDR1	0x3C
#define ADC_JDR2	0x40
#define ADC_JDR3	0x44
#define ADC_JDR4	0x48
#define ADC_DR		0x4C

#ifndef __STM32F10x_H ////avoid redefining if CMSIS library present

//ADC values
#define ADC_SR_AWD		(uint32_t)0x00000001
#define ADC_SR_EOC		(uint32_t)0x00000002
#define ADC_SR_JEOC		(uint32_t)0x00000004
#define ADC_SR_JSTRT	(uint32_t)0x00000008
#define ADC_SR_STRT		(uint32_t)0x00000010

#define ADC_CR1_AWDCH	(uint32_t)0x0000001F //mask
#define ADC_CR1_EOCIE	(uint32_t)0x00000020
#define ADC_CR1_AWDIE	(uint32_t)0x00000040
#define ADC_CR1_JEOCIE	(uint32_t)0x00000080
#define ADC_CR1_SCAN	(uint32_t)0x00000100
#define ADC_CR1_AWDSGL	(uint32_t)0x00000200
#define ADC_CR1_JAUTO	(uint32_t)0x00000400
#define ADC_CR1_DISCEN	(uint32_t)0x00000800
#define ADC_CR1_JDISCEN	(uint32_t)0x00001000
#define ADC_CR1_DISCNUM	(uint32_t)0x0000E000 //mask
#define ADC_CR1_DUALMOD	(uint32_t)0x000F0000 //mask
#define ADC_CR1_JAWDEN	(uint32_t)0x00400000
#define ADC_CR1_AWDEN	(uint32_t)0x00800000

#define ADC_CR2_ADON	(uint32_t)0x00000001
#define ADC_CR2_CONT	(uint32_t)0x00000002
#define ADC_CR2_CAL		(uint32_t)0x00000004
#define ADC_CR2_RSTCAL	(uint32_t)0x00000008
//reserved x4
#define ADC_CR2_DMA		(uint32_t)0x00000100
//reserved x2
#define ADC_CR2_ALIGN	(uint32_t)0x00000800
#define ADC_CR2_JEXTSEL	(uint32_t)0x00007000 //mask
#define ADC_CR2_JEXTTRIG	(uint32_t)0x00008000
//reserved
#define ADC_CR2_EXTSEL	(uint32_t)0x000E0000 //mask
#define ADC_CR2_EXTTRIG	(uint32_t)0x00100000
#define ADC_CR2_JSWSTART	(uint32_t)0x00200000
#define ADC_CR2_SWSTART	(uint32_t)0x00400000
#define ADC_CR2_TSVREFE	(uint32_t)0x00800000

#endif //CMSIS end



#endif /* STM32F103_ADC_REG_H_ */
