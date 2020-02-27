/*
 * STM32F103 USART register definitions
 * Part of STM32F103 register and peripherals library
 *
 * Dpcumentation available in the provided MD file.
 *
 * (c) 2019 Dmitry Reznikov ontaelio(at)gmail.com
 *
 * Can be freely used according to the GNU GPL license.
 */

#ifndef STM32F103_USART_REG_H_
#define STM32F103_USART_REG_H_

#include <stdio.h>

//base addresses
#define _USART1_(mem_offset) (*(volatile uint32_t *)(0x40013800 + (mem_offset)))
#define _USART2_(mem_offset) (*(volatile uint32_t *)(0x40004400 + (mem_offset)))
#define _USART3_(mem_offset) (*(volatile uint32_t *)(0x40004800 + (mem_offset)))
#define _UART4_(mem_offset) (*(volatile uint32_t *)(0x40004C00 + (mem_offset)))
#define _UART5_(mem_offset) (*(volatile uint32_t *)(0x40005000 + (mem_offset)))

//Bit-band aliases (atomic access to select registers)
#define BB_USART1_CR1_M     *(volatile uint32_t *) 0x422701B0
#define BB_USART2_CR1_M     *(volatile uint32_t *) 0x420881B0
#define BB_USART3_CR1_M     *(volatile uint32_t *) 0x420901B0


//register offsets
#define USART_SR	0x00
#define USART_DR	0x04
#define USART_BRR	0x08
#define USART_CR1	0x0C
#define USART_CR2	0x10
#define USART_CR3	0x14
#define USART_GTPR	0x18

#ifndef __STM32F10x_H //avoid redefining

//register bits
#define USART_SR_PE			0x0001
#define USART_SR_FE			0x0002
#define USART_SR_NE			0x0004
#define USART_SR_ORE		0x0008
#define USART_SR_IDLE		0x0010
#define USART_SR_RXNE		0x0020
#define USART_SR_TC			0x0040
#define USART_SR_TXE		0x0080
#define USART_SR_LBD		0x0100
#define USART_SR_CTS		0x0200
//the rest reserved

#define USART_CR1_SBK		0x0001
#define USART_CR1_RWU		0x0002
#define USART_CR1_RE		0x0004
#define USART_CR1_TE		0x0008
#define USART_CR1_IDLEIE	0x0010
#define USART_CR1_RXNEIE	0x0020
#define USART_CR1_TCIE		0x0040
#define USART_CR1_TXEIE		0x0080
#define USART_CR1_PEIE		0x0100
#define USART_CR1_PS		0x0200
#define USART_CR1_PCE		0x0400
#define USART_CR1_WAKE		0x0800
#define USART_CR1_M			0x1000
#define USART_CR1_UE		0x2000
//the rest reserved

#define USART_CR2_ADD		0x000F
//reserved
#define USART_CR2_LBDL		0x0020
#define USART_CR2_LBDIE		0x0040
//reserved
#define USART_CR2_LBCL		0x0100
#define USART_CR2_CPHA		0x0200
#define USART_CR2_CPOL		0x0400
#define USART_CR2_CLKEN		0x0800
#define USART_CR2_STOP		0x3000
#define USART_CR2_LINEN		0x4000
//reserved

#define USART_CR3_EIE		0x0001
#define USART_CR3_IREN		0x0002
#define USART_CR3_IRLP		0x0004
#define USART_CR3_HDSEL		0x0008
#define USART_CR3_NACK		0x0010
#define USART_CR3_SCEN		0x0020
#define USART_CR3_DMAR		0x0040
#define USART_CR3_DMAT		0x0080
#define USART_CR3_RTSE		0x0100
#define USART_CR3_CTSE		0x0200
#define USART_CR3_CTSIE		0x0400
//the rest reserved

#define USART_GTPR_PSC		0x00FF //mask
#define USART_GTPR_GT		0xFF00 //mask

#endif //CMSIS stuff

#endif /* STM32F103_USART_REG_H_ */
