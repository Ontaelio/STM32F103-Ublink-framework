/*
 * STM32F103 I2C register definitions
 * Part of STM32F103 register and peripherals library
 *
 * Dpcumentation available in the provided MD file.
 *
 * (c) 2019 Dmitry Reznikov ontaelio(at)gmail.com
 *
 * Can be freely used according to the GNU GPL license.
 */

#include <stdio.h>
#include <stdint.h>

#ifndef STM32F103_I2C_REG_H_
#define STM32F103_I2C_REG_H_

#define _I2C1_(mem_offset) (*(volatile uint32_t *)(0x40005400 + (mem_offset)))
#define _I2C2_(mem_offset) (*(volatile uint32_t *)(0x40005800 + (mem_offset)))

#define I2C_CR1 0x00
#define I2C_CR2 0x04
#define I2C_OAR1 0x08
#define I2C_OAR2 0x0C
#define I2C_DR 0x10
#define I2C_SR1 0x14
#define I2C_SR2 0x18
#define I2C_CCR 0x1C
#define I2C_TRISE 0x20

//bits and masks different from CMSIS
//OAR1
#define I2C_OAR1_ADD_7    0x00FE //mask for a 7-bit address
#define I2C_OAR1_ADD_10   0x03FF //mask for a 10-bit address

#define I2C_SR2_PECBYTE 0xFF00 //mask for upper 8 bits

#ifndef __STM32F10x_H ////avoid redefining if CMSIS library present

//CR1
#define I2C_CR1_PE      0x0001
#define I2C_CR1_SMBUS   0x0002
//reserved      0x0004
#define I2C_CR1_SMBTYPE 0x0008
#define I2C_CR1_ENARP   0x0010
#define I2C_CR1_ENPEC   0x0020
#define I2C_CR1_ENGC    0x0040
#define I2C_CR1_NOSTRETCH 0x0080
#define I2C_CR1_START   0x0100
#define I2C_CR1_STOP    0x0200
#define I2C_CR1_ACK     0x0400
#define I2C_CR1_POS     0x0800
#define I2C_CR1_PEC     0x1000
#define I2C_CR1_ALERT   0x2000
//reserved      0x4000
#define I2C_CR1_SWRST   0x8000

//CR2
#define I2C_CR2_FREQ    0x003F //mask for bits 5:0
//reserved		0x0040
//reserved		0x0080
#define I2C_CR2_ITERREN 0x0100
#define I2C_CR2_ITEVTEN 0x0200
#define I2C_CR2_ITBUFEN 0x0400
#define I2C_CR2_DMAEN   0x0800
#define I2C_CR2_LAST    0x1000
//reserved      0x2000
//reserved      0x4000
//reserved		0x8000

#define I2C_OAR1_ADDMODE  0x8000

//OAR2
#define I2C_OAR2_ENDUAL  0x0001
//ADD2 == ADD7 from OAR1
//the rest is reserved

//SR1
#define I2C_SR1_SB      0x0001
#define I2C_SR1_ADDR    0x0002
#define I2C_SR1_BTF     0x0004
#define I2C_SR1_ADD10   0x0008
#define I2C_SR1_STOPF   0x0010
//reserved      0x0020
#define I2C_SR1_RXNE    0x0040
#define I2C_SR1_TXE     0x0080
#define I2C_SR1_BERR    0x0100
#define I2C_SR1_ARLO    0x0200
#define I2C_SR1_AF      0x0400
#define I2C_SR1_OVR     0x0800
#define I2C_SR1_PECERR  0x1000
//reserved      0x2000
#define I2C_SR1_TIMEOUT 0x4000
#define I2C_SR1_SMBALERT 0x8000

//SR2
#define I2C_SR2_MSL     0x0001
#define I2C_SR2_BUSY    0x0002
#define I2C_SR2_TRA     0x0004
//reserved      0x0008
#define I2C_SR2_GENCALL 0x0010
#define I2C_SR2_SMBDEFAULT 0x0020
#define I2C_SR2_SMBHOST 0x0040
#define I2C_SR2_DUALF   0x0080

//CCR
#define I2C_CCR_CCR     0x0FFF
#define I2C_CCR_DUTY	0x4000
#define I2C_CCR_FS      0x8000

//TRISE
#define I2C_TRISE_TRISE		0x003F

#endif //CMSIS lib

#endif /* STM32F103_I2C_REG_H_ */
