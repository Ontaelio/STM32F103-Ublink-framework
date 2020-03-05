/*
 * STM32F103 SPI functions library header
 * Part of STM32F103 register and peripherals library
 *
 * Documentation available in the provided MD file.
 *
 * (c) 2019 Dmitry Reznikov ontaelio(at)gmail.com
 *
 * Can be freely used according to the GNU GPL license.
 */

#ifndef STM32F103_SPI_FUNC_H_
#define STM32F103_SPI_FUNC_H_

#include <stm32f103_rcc_reg.h>
#include <stm32f103_spi_reg.h>
#include <stm32f103_gpio_reg.h>
#include <stm32f103_gpio_func.h>
#include <stdio.h>
#include <stdint.h>

#define BIDI_INPUT  	0x8000
#define BIDI_OUTPUT 	0xC000
#define FULL_DUPLEX		0x0000
#define DATAFRAME_8		0x0000
#define DATAFRAME_16	0x0800
#define SOFT_SS			0x0300
#define LSB_FIRST		0x0080
#define MSB_FIRST		0x0000
#define CPHASE_FIRST	0x0000
#define CPHASE_SECOND	0x0001
#define CLKIDLE_LOW		0x0000
#define CLKIDLE_HIGH	0x0002
#define CLK_LOWRISE		0x0000
#define CLK_HIGHFALL	0x0002
#define CLK_LOWFALL		0x0001
#define CLK_HIGHRISE	0x0003


void spi1_initMaster(uint16_t bitmode, uint16_t prescaler, uint16_t bidimode = 0, uint8_t sc = 1, uint8_t af = 0);
void spi1_init(uint8_t af = 0);

void spi2_initMaster(uint16_t bitmode, uint16_t prescaler, uint16_t bidimode = 0, uint8_t sc = 1);
void spi2_init();

/************** abstract class *****************/
class spi_slave
{
public:
	spi_slave(gpio_pin* gpin): ss_pin(gpin){}
	void ss_low()
	{
		ss_pin->low();
	}
	void ss_high()
	{
		ss_pin->high();
	}

	virtual void init(uint16_t conf) = 0;// = default_config) = 0;
	virtual void enable() = 0;
	virtual void disable()= 0;
	virtual void write(uint16_t dat) =0;
	virtual void writeData(uint16_t dat) =0;
	virtual void writeStream(void* stuff, uint16_t num) =0;
	virtual uint16_t read() =0;
	virtual uint16_t readData() =0;
	virtual void readStream(void* stuff, uint16_t num) =0;
	virtual uint16_t transfer(uint16_t dat_out) =0;
	virtual void transferStream(void* arr_out, void* arr_in, uint16_t num) =0;
	virtual void seqTransfer(uint8_t* arr_out, uint16_t num_out, uint8_t* arr_in, uint16_t num_in) =0;

protected:
	gpio_pin* ss_pin;
	uint16_t cr1_config;
};

/************ SPI1 *****************/

class spi1_slave : public spi_slave
{
public:
	spi1_slave(gpio_pin* gpin): spi_slave(gpin){}
	void init(uint16_t conf = default_config);
	void enable();
	void disable()
	{
		_SPI1_(SPI_CR1) &= ~SPI_CR1_SPE;
	}
	void write(uint16_t dat);
	void writeStream(void* stuff, uint16_t num);
	void writeData(uint16_t dat)
	{
	    _SPI1_(SPI_DR) = dat; //send a byte or two
	    while (!(_SPI1_(SPI_SR) & SPI_SR_TXE)); //wait until it's sent
	}
	uint16_t read();
	void readStream(void* stuff, uint16_t num);
	uint16_t readData()
	{
		while (!(_SPI1_(SPI_SR) & SPI_SR_RXNE)); //wait until data is received
		return _SPI1_(SPI_DR);
	}
	uint16_t transfer(uint16_t dat_out);
	void transferStream(void* arr_out, void* arr_in, uint16_t num);

	void seqTransfer(uint8_t* arr_out, uint16_t num_out, uint8_t* arr_in, uint16_t num_in);

	void DMATXenable() {_SPI1_(SPI_CR2) |= SPI_CR2_RXDMAEN;}
	void DMARXenable() {_SPI1_(SPI_CR2) |= SPI_CR2_TXDMAEN;}
	void DMATXdisable() {_SPI1_(SPI_CR2) &= ~SPI_CR2_RXDMAEN;}
	void DMARXdisable() {_SPI1_(SPI_CR2) &= ~SPI_CR2_TXDMAEN;}

private:
	uint16_t static const default_config = 0x0300;

};

/************ SPI2 *****************/

class spi2_slave : public spi_slave
{
public:
	spi2_slave(gpio_pin* gpin): spi_slave(gpin){}
	void init(uint16_t conf = default_config);
	void enable();
	void disable()
	{
		_SPI2_(SPI_CR1) &= ~SPI_CR1_SPE;
	}
	void write(uint16_t dat);
	void writeStream(void* stuff, uint16_t num);
	void writeData(uint16_t dat)
	{
	    _SPI2_(SPI_DR) = dat; //send a byte or two
	    while (!(_SPI2_(SPI_SR) & SPI_SR_TXE)); //wait until it's sent
	}
	uint16_t read();
	void readStream(void* stuff, uint16_t num);
	uint16_t readData()
	{
		while (!(_SPI2_(SPI_SR) & SPI_SR_RXNE)); //wait until data is received
		return _SPI2_(SPI_DR);
	}
	uint16_t transfer(uint16_t dat_out);
	void transferStream(void* arr_out, void* arr_in, uint16_t num);

	void seqTransfer(uint8_t* arr_out, uint16_t num_out, uint8_t* arr_in, uint16_t num_in);

	void DMATXenable() {_SPI2_(SPI_CR2) |= SPI_CR2_RXDMAEN;}
	void DMARXenable() {_SPI2_(SPI_CR2) |= SPI_CR2_TXDMAEN;}
	void DMATXdisable() {_SPI2_(SPI_CR2) &= ~SPI_CR2_RXDMAEN;}
	void DMARXdisable() {_SPI2_(SPI_CR2) &= ~SPI_CR2_TXDMAEN;}


private:
	uint16_t static const default_config = 0x0300;

};


/************ LOWER LEVEL *******************/

inline void spi1_writeData(uint16_t dat)
{
	//continuous transmission, ss should be low already
    _SPI1_(SPI_DR) = dat; //send a byte or two
    while (!(_SPI1_(SPI_SR) & SPI_SR_TXE)); //wait until it's sent
    //don't wait until BSY is cleared
    //don't change ss state
}

inline void spi1_transferStart(uint16_t dat)
{
	_SPI1_(SPI_DR) = dat;
}

uint16_t spi1_transferData(uint16_t dat_out);

inline uint16_t spi1_transferEnd()
{
	return _SPI1_(SPI_DR);
}

inline uint16_t spi1_readData()
{
	while (!(_SPI1_(SPI_SR) & SPI_SR_RXNE)); //wait until data is received
	return _SPI1_(SPI_DR);
}

uint16_t spi1_writeReadData(uint16_t dat_out);


inline void spi2_writeData(uint16_t dat)
{
	//continuous transmission, ss should be low already
    _SPI2_(SPI_DR) = dat; //send a byte or two
    while (!(_SPI2_(SPI_SR) & SPI_SR_TXE)); //wait until it's sent
    //don't wait until BSY is cleared
    //don't change ss state
}

inline void spi2_transferStart(uint16_t dat)
{
	_SPI2_(SPI_DR) = dat;
}

uint16_t spi2_transferData(uint16_t dat_out);

inline uint16_t spi2_transferEnd()
{
	return _SPI2_(SPI_DR);
}

inline uint16_t spi2_readData()
{
	while (!(_SPI2_(SPI_SR) & SPI_SR_RXNE)); //wait until data is received
	return _SPI2_(SPI_DR);
}

uint16_t spi2_writeReadData(uint16_t dat_out);

#endif /* STM32F103_SPI_FUNC_H_ */
