/*
 * STM32F103 SPI register definitions
 * Part of STM32F103 register and peripherals library
 *
 * Dpcumentation available in the provided MD file.
 *
 * (c) 2019 Dmitry Reznikov ontaelio(at)gmail.com
 *
 * Can be freely used according to the GNU GPL license.
 */

#ifndef STM32F103_SPI_REG_H_
#define STM32F103_SPI_REG_H_

#include <stdio.h>
#include <stdint.h>

#define _SPI1_(mem_offset) (*(volatile uint32_t *)(0x40013000 + (mem_offset)))
#define _SPI2_(mem_offset) (*(volatile uint32_t *)(0x40003800 + (mem_offset)))
#define _SPI3_(mem_offset) (*(volatile uint32_t *)(0x40003C00 + (mem_offset)))

#define _BBSPI1_(mem_offset) (*(volatile uint32_t *)(0x42260000 + (mem_offset)))
#define _BBSPI2_(mem_offset) (*(volatile uint32_t *)(0x42070000 + (mem_offset)))
#define BB_SPI_CR1  0x0000
#define BB_SPI_CR1_SPE 0x18

#define SPI_CR1		0x00
#define SPI_CR2		0x04
#define SPI_SR 		0x08
#define SPI_DR		0x0C
#define SPI_CRCPR	0x10
#define SPI_RXCRCR	0x14
#define SPI_TXCRCR	0x18
#define SPI_I2SCFGR	0x1C
#define SPI_I2SPR	0x20

//Baud Rate aka Prescaler values
#define SPIBR2		0x0000
#define SPIBR4		0x0008
#define SPIBR8		0x0010
#define SPIBR16		0x0018
#define SPIBR32		0x0020
#define SPIBR64		0x0028
#define SPIBR128	0x0030
#define SPIBR256	0x0038

#ifndef __STM32F10x_H ////avoid redefining if CMSIS library present

//CR1
#define SPI_CR1_CPHA        0x0001
#define SPI_CR1_CPOL        0x0002
#define SPI_CR1_MSTR        0x0004
#define SPI_CR1_BR			0x0038 //mask
#define SPI_CR1_SPE         0x0040
#define SPI_CR1_LSBFIRST    0x0080
#define SPI_CR1_SSI         0x0100
#define SPI_CR1_SSM         0x0200
#define SPI_CR1_RXONLY      0x0400
#define SPI_CR1_DFF         0x0800
#define SPI_CR1_CRCNEXT     0x1000
#define SPI_CR1_CRCEN       0x2000
#define SPI_CR1_BIDIOE      0x4000
#define SPI_CR1_BIDIMODE    0x8000

//CR2
#define SPI_CR2_RXDMAEN		0x0001
#define SPI_CR2_TXDMAEN		0x0002
#define SPI_CR2_SSOE		0x0004
//reserved 0x0008
//reserved 0x0010
#define SPI_CR2_ERRIE		0x0020
#define SPI_CR2_RXNEIE		0x0040
#define SPI_CR2_TXEIE		0x0080
//the rest reserved

//SR
#define SPI_SR_RXNE			0x0001
#define SPI_SR_TXE			0x0002
#define SPI_SR_CHSIDE		0x0004
#define SPI_SR_UDR			0x0008
#define SPI_SR_CRCERR		0x0010
#define SPI_SR_MODF			0x0020
#define SPI_SR_OVR			0x0040
#define SPI_SR_BSY			0x0080
//the rest reserved

//I2SCFGR
#define SPI_I2SCFGR_CHLEN	0x0001
#define SPI_I2SCFGR_DATLEN  0x0006 //mask, 2 bits
#define SPI_I2SCFGR_CKPOL	0x0008
#define SPI_I2SCFGR_I2SSTD	0x0030 //mask, 2 bits
//reserved 0x0040
#define SPI_I2SCFGR_PCMSYNC	0x0080
#define SPI_I2SCFGR_I2SCFG	0x0300 //mask, 2 bits
#define SPI_I2SCFGR_I2SE	0x0400
#define SPI_I2SCFGR_I2SMOD	0x0800
//the rest reserved

//I2SPR
#define SPI_I2SPR_I2SDIV	0x00FF //mask, bits 7..0
#define SPI_I2SPR_ODD		0x0100
#define SPI_I2SPR_MCKOE		0x0200
//the rest reserved

#endif //CMSIS stuff

#endif /* STM32F103_SPI_REG_H_ */
