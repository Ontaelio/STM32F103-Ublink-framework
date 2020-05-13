/*
 * STM32F103 I2C Master library header
 * Part of STM32F103 register and peripherals library
 *
 * Documentation available in the provided MD file.
 *
 * (c) 2019 Dmitry Reznikov ontaelio(at)gmail.com
 *
 * Can be freely used according to the GNU GPL license.
 */

#ifndef STM32F103_I2C_H_
#define STM32F103_I2C_H_

#include <stdio.h>
#include <stdint.h>
#include <stm32f103_rcc_reg.h>
#include <stm32f103_i2c_reg.h>

//SM = 100 KHz, FM = 400 KHz, alt pins = PB9/PB8 for i2c1
#define I2C_SM 0
#define I2C_FM 1
#define I2C1_ALT 1

class i2c1
{
public:
	i2c1(uint8_t address, uint8_t address_bits = 8);
	void write(uint16_t addr, uint8_t stuff);
	void write16(uint16_t addr, uint16_t stuff);
	void write32(uint16_t addr, uint32_t stuff);
	void writeStream(uint16_t addr, uint8_t* stuff, uint8_t num);
	uint8_t read(uint16_t addr);
	uint16_t read16(uint16_t addr);
	uint32_t read32(uint16_t addr);
	void readStream(uint16_t addr, uint8_t* arr, uint8_t num);

	void DMAenable() {_I2C1_(I2C_CR2) |= I2C_CR2_DMAEN;}
	void DMAdisable() {_I2C1_(I2C_CR2) &= ~I2C_CR2_DMAEN;}
	void LASTset() {_I2C1_(I2C_CR2) |= I2C_CR2_LAST;}
	void LASTclear() {_I2C1_(I2C_CR2) &= ~I2C_CR2_LAST;}

	void DMATXenable() {_I2C1_(I2C_CR2) |= I2C_CR2_DMAEN;} //for compatibility reasons
	void DMARXenable() {_I2C1_(I2C_CR2) |= I2C_CR2_DMAEN;}
	void DMATXdisable() {_I2C1_(I2C_CR2) &= ~I2C_CR2_DMAEN;}
	void DMARXdisable() {_I2C1_(I2C_CR2) &= ~I2C_CR2_DMAEN;}

private:
	uint8_t device_addr, word_addr;
	void startAndSendRegisterAddress(uint16_t regaddr);
};

typedef i2c1 i2c1_slave;

//setup and troubleshooting
uint8_t i2c1_resetBus(uint8_t altpins = 0);
void i2c1_init(uint8_t speed, uint8_t altpins = 0);
void i2c1_tweak(uint8_t fs_bit, uint8_t duty_bit, uint16_t ccr_val);
void i2c1_APB1freq(uint8_t pclk1_mhz);
void i2c1_setFreq(uint32_t i2c_freq);
uint8_t i2c1_ping(uint8_t addr);
uint8_t i2c1_scanAddr(uint8_t startAddr = 0x07);

//Method 2
uint8_t i2c1_readOneByte(uint8_t addr);
uint8_t i2c1_readFirstOfTwo(uint8_t addr);
uint8_t i2c1_readFirstOfThree(uint8_t addr);
void i2c1_readStreamMethod2 (uint8_t addr, uint8_t* arr, uint8_t num);

inline uint8_t i2c1_DR()
{
	return(_I2C1_(I2C_DR));
}

inline void i2c1_checkRXNE()
{
	while (!(_I2C1_(I2C_SR1) & I2C_SR1_RXNE));
}

// generic and Method 1 functions
void i2c1_start(uint8_t addr);
void i2c1_writeByte(uint8_t stuff);
void i2c1_writeLast(uint8_t stuff);
void i2c1_writeStream (uint8_t* arr, uint8_t num);
void i2c1_stop();
void i2c1_readStart(uint8_t addr);
uint8_t i2c1_readByte();
uint8_t i2c1_readLast();
void i2c1_readStream(uint8_t* arr, uint8_t num);

/* ------ I2C2 ---------- */

class i2c2
{
public:
	i2c2(uint8_t address, uint8_t address_bits = 8);
	void write(uint16_t addr, uint8_t stuff);
	void write16(uint16_t addr, uint16_t stuff);
	void write32(uint16_t addr, uint32_t stuff);
	void writeStream(uint16_t addr, uint8_t* stuff, uint8_t num);
	uint8_t read(uint16_t addr);
	uint16_t read16(uint16_t addr);
	uint32_t read32(uint16_t addr);
	void readStream(uint16_t addr, uint8_t* arr, uint8_t num);

	void DMAenable() {_I2C2_(I2C_CR2) |= I2C_CR2_DMAEN;}
	void DMAdisable() {_I2C2_(I2C_CR2) &= ~I2C_CR2_DMAEN;}
	void LASTset() {_I2C2_(I2C_CR2) |= I2C_CR2_LAST;}
	void LASTclear() {_I2C2_(I2C_CR2) &= ~I2C_CR2_LAST;}

	void DMATXenable() {_I2C2_(I2C_CR2) |= I2C_CR2_DMAEN;} //for compatibility reasons
	void DMARXenable() {_I2C2_(I2C_CR2) |= I2C_CR2_DMAEN;}
	void DMATXdisable() {_I2C2_(I2C_CR2) &= ~I2C_CR2_DMAEN;}
	void DMARXdisable() {_I2C2_(I2C_CR2) &= ~I2C_CR2_DMAEN;}

private:
	uint8_t device_addr, word_addr;
	void startAndSendRegisterAddress(uint16_t regaddr);
};

typedef i2c2 i2c2_slave;

//setup and troubleshooting
uint8_t i2c2_resetBus();
void i2c2_init(uint8_t speed);
void i2c2_tweak(uint8_t fs_bit, uint8_t duty_bit, uint16_t ccr_val);
void i2c2_APB1freq(uint8_t pclk1_mhz);
void i2c2_setFreq(uint32_t i2c_freq);
uint8_t i2c2_ping(uint8_t addr);
uint8_t i2c2_scanAddr(uint8_t startAddr = 0x07);

//Method 2
uint8_t i2c2_readOneByte(uint8_t addr);
uint8_t i2c2_readFirstOfTwo(uint8_t addr);
uint8_t i2c2_readFirstOfThree(uint8_t addr);
void i2c2_readStreamMethod2 (uint8_t addr, uint8_t* arr, uint8_t num);

inline uint8_t i2c2_DR()
{
	return(_I2C2_(I2C_DR));
}

inline void i2c2_checkRXNE()
{
	while (!(_I2C2_(I2C_SR1) & I2C_SR1_RXNE));
}

// generic and Method 1 functions
void i2c2_start(uint8_t addr);
void i2c2_writeByte(uint8_t stuff);
void i2c2_writeLast(uint8_t stuff);
void i2c2_writeStream (uint8_t* arr, uint8_t num);
void i2c2_stop();
void i2c2_readStart(uint8_t addr);
uint8_t i2c2_readByte();
uint8_t i2c2_readLast();
void i2c2_readStream(uint8_t* arr, uint8_t num);

#endif /* STM32F103_I2C_H_ */
