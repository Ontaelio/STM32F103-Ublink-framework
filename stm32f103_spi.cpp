/*
 * STM32F103 SPI functions library
 * Part of STM32F103 register and peripherals library
 *
 * Documentation available in the provided MD file.
 *
 * (c) 2019 Dmitry Reznikov ontaelio(at)gmail.com
 *
 * Can be freely used according to the GNU GPL license.
 */



#include <stm32f103_rcc_reg.h>
#include <stm32f103_gpio_reg.h>
#include <stm32f103_spi_reg.h>
#include <stdio.h>
#include <stdint.h>
#include <stm32f103_gpio.h>
#include <stm32f103_spi.h>


void spi1_slave::init(uint16_t conf)
{
	cr1_config = conf;// | SPI_CR1_DFF;
	ss_pin->high();
	ss_pin->mode(OUTPUT, PUSHPULL);
	cr1_config &= ~SPI_CR1_SPE; //disable SPI in config
	cr1_config |= SPI_CR1_MSTR; //set master in config
	_SPI1_(SPI_CR1) &= ~SPI_CR1_SPE; //disable SPI
	_SPI1_(SPI_CR1) = cr1_config; //set new CR1 values
	//_BBSPI1_ (BB_SPI_CR1 + BB_SPI_CR1_SPE) = 1;
	_SPI1_(SPI_CR1) |= SPI_CR1_SPE; //enable SPI
}

void spi1_slave::enable()
{
	_SPI1_(SPI_CR1) &= ~SPI_CR1_SPE; //disable SPI
	_SPI1_(SPI_CR1) = cr1_config; //set new CR1 values
	//_BBSPI1_ (BB_SPI_CR1 + BB_SPI_CR1_SPE) = 1;
	_SPI1_(SPI_CR1) |= SPI_CR1_SPE; //enable SPI
}

void spi1_slave::write(uint16_t dat)
{
	ss_low();
    _SPI1_(SPI_DR) = dat; //send a byte or two
    while (!(_SPI1_(SPI_SR) & SPI_SR_TXE)); //wait until it's sent
    while (_SPI1_(SPI_SR) & SPI_SR_BSY); //wait until BSY is cleared
    ss_high();
}

void spi1_slave::writeStream(void* stuff, uint16_t num)
{
	uint16_t k = 0;
	ss_low();
	if (cr1_config & SPI_CR1_DFF)
	{
		uint16_t* arr = (uint16_t*)stuff;
		do
		{
			spi1_writeData(*(arr + k));
			k++;
		}
		while (k<num);
	}
	else
	{
		uint8_t* arr = (uint8_t*)stuff;
		do
		{
			spi1_writeData(*(arr + k));
			k++;
		}
		while (k<num);
	}
	while (_SPI1_(SPI_SR) & SPI_SR_BSY); //wait until BSY is cleared
	ss_high();
}

uint16_t spi1_slave::read()
{
	uint8_t dat;
	ss_low();
	while (!(_SPI1_(SPI_SR) & SPI_SR_RXNE)); //wait until data is received
	ss_high();
	dat = _SPI1_(SPI_DR); //read a byte or two
	return dat;
}

void spi1_slave::readStream(void* stuff, uint16_t num)
{
	uint16_t k = 0;
	if (cr1_config & SPI_CR1_DFF)
	{
		uint16_t* arr = (uint16_t*)stuff;
		ss_low();
		do
		{
			*(arr + k) = spi1_readData();
			k++;
		}
		while (k<num);
		ss_high();
	}
	else
	{
		uint8_t* arr = (uint8_t*)stuff;
		ss_low();
		do
		{
			*(arr + k) = spi1_readData();
			k++;
		}
		while (k<num);
		ss_high();
	}
}

uint16_t spi1_slave::transfer(uint16_t dat_out)
{
	uint16_t dat_in;
	ss_low();
	spi1_writeData(dat_out);
	dat_in = spi1_readData();
	ss_high();
	return dat_in;
}

void spi1_slave::transferStream(void* arr_out, void* arr_in, uint16_t num)
{
	uint16_t k = 0;
	--num;

	if (cr1_config & SPI_CR1_DFF)
	{
		uint16_t* aout = (uint16_t*)arr_out;
		uint16_t* ain = (uint16_t*)arr_in;
		ss_low();
		_SPI1_(SPI_DR) = *aout; //put first data in DR
		do
		{
			*(ain + k) = spi1_transferData(*(aout + k +1));
			//spi1_writeData(*(aout + k));
			//*(ain + k) = spi1_readData();
			++k;
		}
		while (k<num);
		*(ain + num) = spi1_readData(); //get last data from DR
	}
	else
	{
		uint8_t* aout = (uint8_t*)arr_out;
		uint8_t* ain = (uint8_t*)arr_in;
		ss_low();
		_SPI1_(SPI_DR) = *aout;
		do
		{
			*(ain + k) = spi1_transferData(*(aout + k +1));
			//spi1_writeData(*(aout + k));
			//*(ain + k) = spi1_readData();
			++k;
		}
		while (k<num);
		*(ain + num) = spi1_readData();
	}
	while (!(_SPI1_(SPI_SR) & SPI_SR_TXE));
	while (_SPI1_(SPI_SR) & SPI_SR_BSY); //wait until BSY is cleared
	ss_high();
}

void spi1_slave::seqTransfer(uint8_t* arr_out, uint16_t num_out, uint8_t* arr_in, uint16_t num_in)
{
	uint8_t* aout = arr_out;
	uint8_t* ain = arr_in;
	uint16_t k = 0;
	--num_in; --num_out;
	ss_low();
	_SPI1_(SPI_DR) = *aout; //put first data in DR
	do
	{
		spi1_transferData(*(aout + k +1));
		++k;
	}
	while (k<num_out);
	spi1_transferData(0);
	k = 0;
	do
	{
		*(ain + k) = spi1_transferData(0);
		++k;
	}
	while (k<num_in);
	if (num_in) *(ain + num_in) = spi1_readData(); //get last data from DR

	while (!(_SPI1_(SPI_SR) & SPI_SR_TXE));
	while (_SPI1_(SPI_SR) & SPI_SR_BSY); //wait until BSY is cleared
	ss_high();
}

void spi2_slave::init(uint16_t conf)
{
	cr1_config = conf;// | SPI_CR1_DFF;
	ss_pin->high();
	ss_pin->mode(OUTPUT, PUSHPULL);
	cr1_config &= ~SPI_CR1_SPE; //disable SPI in config
	cr1_config |= SPI_CR1_MSTR; //set master in config
	_SPI2_(SPI_CR1) &= ~SPI_CR1_SPE; //disable SPI
	_SPI2_(SPI_CR1) = cr1_config; //set new CR1 values
	//_BBSPI2_ (BB_SPI_CR1 + BB_SPI_CR1_SPE) = 1;
	_SPI2_(SPI_CR1) |= SPI_CR1_SPE; //enable SPI
}

void spi2_slave::enable()
{
	_SPI2_(SPI_CR1) &= ~SPI_CR1_SPE; //disable SPI
	_SPI2_(SPI_CR1) = cr1_config; //set new CR1 values
	//_BBSPI2_ (BB_SPI_CR1 + BB_SPI_CR1_SPE) = 1;
	_SPI2_(SPI_CR1) |= SPI_CR1_SPE; //enable SPI
}

void spi2_slave::write(uint16_t dat)
{
	ss_low();
    _SPI2_(SPI_DR) = dat; //send a byte or two
    while (!(_SPI2_(SPI_SR) & SPI_SR_TXE)); //wait until it's sent
    while (_SPI2_(SPI_SR) & SPI_SR_BSY); //wait until BSY is cleared
    ss_high();
}

void spi2_slave::writeStream(void* stuff, uint16_t num)
{
	uint16_t k = 0;
	ss_low();
	if (cr1_config & SPI_CR1_DFF)
	{
		uint16_t* arr = (uint16_t*)stuff;
		do
		{
			spi2_writeData(*(arr + k));
			k++;
		}
		while (k<num);
	}
	else
	{
		uint8_t* arr = (uint8_t*)stuff;
		do
		{
			spi2_writeData(*(arr + k));
			k++;
		}
		while (k<num);
	}
	while (_SPI2_(SPI_SR) & SPI_SR_BSY); //wait until BSY is cleared
	ss_high();
}

uint16_t spi2_slave::read()
{
	uint8_t dat;
	ss_low();
	while (!(_SPI2_(SPI_SR) & SPI_SR_RXNE)); //wait until data is received
	ss_high();
	dat = _SPI2_(SPI_DR); //read a byte or two
	return dat;
}

void spi2_slave::readStream(void* stuff, uint16_t num)
{
	uint16_t k = 0;
	if (cr1_config & SPI_CR1_DFF)
	{
		uint16_t* arr = (uint16_t*)stuff;
		ss_low();
		do
		{
			*(arr + k) = spi2_readData();
			k++;
		}
		while (k<num);
		ss_high();
	}
	else
	{
		uint8_t* arr = (uint8_t*)stuff;
		ss_low();
		do
		{
			*(arr + k) = spi2_readData();
			k++;
		}
		while (k<num);
		ss_high();
	}
}

uint16_t spi2_slave::transfer(uint16_t dat_out)
{
	uint16_t dat_in;
	ss_low();
	spi2_writeData(dat_out);
	dat_in = spi2_readData();
	ss_high();
	return dat_in;
}

void spi2_slave::transferStream(void* arr_out, void* arr_in, uint16_t num)
{
	uint16_t k = 0;
	--num;

	if (cr1_config & SPI_CR1_DFF)
	{
		uint16_t* aout = (uint16_t*)arr_out;
		uint16_t* ain = (uint16_t*)arr_in;
		ss_low();
		_SPI2_(SPI_DR) = *aout; //put first data in DR
		do
		{
			*(ain + k) = spi2_transferData(*(aout + k +1));
			//spi2_writeData(*(aout + k));
			//*(ain + k) = spi2_readData();
			++k;
		}
		while (k<num);
		*(ain + num) = spi2_readData(); //get last data from DR
	}
	else
	{
		uint8_t* aout = (uint8_t*)arr_out;
		uint8_t* ain = (uint8_t*)arr_in;
		ss_low();
		_SPI2_(SPI_DR) = *aout;
		do
		{
			*(ain + k) = spi2_transferData(*(aout + k +1));
			//spi2_writeData(*(aout + k));
			//*(ain + k) = spi2_readData();
			++k;
		}
		while (k<num);
		*(ain + num) = spi2_readData();
	}
	while (!(_SPI2_(SPI_SR) & SPI_SR_TXE));
	while (_SPI2_(SPI_SR) & SPI_SR_BSY); //wait until BSY is cleared
	ss_high();
}

void spi2_slave::seqTransfer(uint8_t* arr_out, uint16_t num_out, uint8_t* arr_in, uint16_t num_in)
{
	uint8_t* aout = arr_out;
	uint8_t* ain = arr_in;
	uint16_t k = 0;
	--num_in; --num_out;
	ss_low();
	_SPI2_(SPI_DR) = *aout; //put first data in DR
	do
	{
		spi2_transferData(*(aout + k +1));
		++k;
	}
	while (k<num_out);
	spi2_transferData(0);
	k = 0;
	do
	{
		*(ain + k) = spi2_transferData(0);
		++k;
	}
	while (k<num_in);
	if (num_in) *(ain + num_in) = spi2_readData(); //get last data from DR

	while (!(_SPI2_(SPI_SR) & SPI_SR_TXE));
	while (_SPI2_(SPI_SR) & SPI_SR_BSY); //wait until BSY is cleared
	ss_high();
}

void spi1_init(uint8_t af)
{
	/**** GPIO setup ****/
	if (af) //alternate mapping:
	{
		//NOTE: PB pins are used by JTAG by default!
		//      JTAG must be disabled to use them in SPI mode
		//		Alt pin mapping must also be done outside of this function (AFIOMAPR)

		//turn on clocks for GPIOA and B, as well as AFIO
		_RCC_(RCC_APB2ENR) |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_AFIOEN;
		/*setup pins:
	  	  MOSI	B5 alt push pull
	  	  MISO	B4 alt push pull
	  	  SCK	B3 alt push pull
		  SS	A15 norm push pull
		*/
		_GPIOB_(GPIOX_CRL) &= ~(CNF5_0 | CNF3_0 |CNF4_0); //clear the bit set by default
		_GPIOB_(GPIOX_CRL) |= CNF5_1 | CNF3_1 | CNF4_1; //alt functions
		_GPIOB_(GPIOX_CRL) |= MODE5_1 | MODE5_0 | MODE3_1 | MODE3_0 | MODE4_1 | MODE4_0; //output 50 MHz
		_GPIOA_(GPIOX_CRH) &= ~(CNF15_0 | CNF15_1); //clear CNF
		_GPIOA_(GPIOX_CRH) &= ~MODE15_0;
		_GPIOA_(GPIOX_CRH) |= MODE15_1; //output 2 MHz
	}
	else //default pins
		{
		//turn on clocks for GPIOA and AFIO
		_RCC_(RCC_APB2ENR) |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN;
		/*setup pins:
	  	  MOSI	A7 alt push pull
		  MISO	A6 alt push pull
		  SCK	A5 alt push pull
		  SS	A4 norm push pull
		*/
		_GPIOA_(GPIOX_CRL) &= ~(CNF7_0 | CNF6_0 | CNF5_0 | CNF4_0); //clear the bit set by default
		_GPIOA_(GPIOX_CRL) &= ~CNF4_1; //just in case it's set
		_GPIOA_(GPIOX_CRL) |= CNF7_1 | CNF6_1 | CNF5_1; //alt functions
		_GPIOA_(GPIOX_CRL) |= MODE7_1 | MODE7_0 | MODE6_1 | MODE6_0 | MODE5_1 | MODE5_0 | MODE4_1; //output 50 MHz
	}

	//enable spi1 clock
	_RCC_(RCC_APB2ENR) |= RCC_APB2ENR_SPI1EN;
}

void spi1_initMaster(uint16_t bitmode, uint16_t prescaler, uint16_t bidimode, uint8_t sc, uint8_t af)
{
	spi1_init(af);
	//clear CR1 and set bidi or unidi mode
	_SPI1_(SPI_CR1) = bidimode;

	//set bitmode 8 or 16
	_SPI1_ (SPI_CR1) |= bitmode;

	//set prescaler
	_SPI1_ (SPI_CR1) |= prescaler;// 3 bits

	//software control of SS
	if (sc) _SPI1_ (SPI_CR1) |= SPI_CR1_SSM | SPI_CR1_SSI; //enable software control of SS, SS high

	//default values used here:
	//CPOL == 0 : SCK will be low when idle
	//CPHA == 0 : rising edge with CPOL = 0; first clock transition
	//LSB_FIRST == 0 : MSB first

	//set SPI master
	_SPI1_ (SPI_CR1) |= SPI_CR1_MSTR; //SPI master
	//enable SPI
	_SPI1_ (SPI_CR1) |= SPI_CR1_SPE; //enable SPI
	//_BBSPI_ (BB_SPI_CR1 + BB_SPI_CR1_SPE) = 1;
}

uint16_t spi1_transferData(uint16_t dat_out)
{
	while (!(_SPI1_(SPI_SR) & SPI_SR_TXE)); //wait for TXE set (data from DR buffered)
	_SPI1_(SPI_DR) = dat_out; //write a byte or a word into the DR register
	while (!(_SPI1_(SPI_SR) & SPI_SR_RXNE)); //wait for RXNE to get set
	return _SPI1_(SPI_DR);//return contents of DR
}

uint16_t spi1_writeReadData(uint16_t dat_out)
{
	spi1_writeData(dat_out);
	return spi1_readData();
}

void spi2_init()
{
	/**** GPIO setup ****/

	//turn on clocks for GPIOB and AFIO
	_RCC_(RCC_APB2ENR) |= RCC_APB2ENR_IOPBEN | RCC_APB2ENR_AFIOEN;
	/*setup pins:
	  MOSI	B15 alt push pull
	  MISO	B14 alt push pull
	  SCK	B13 alt push pull
	  SS	B12 norm push pull
	*/
	_GPIOB_(GPIOX_CRH) &= ~(CNF15_0 | CNF14_0 | CNF13_0 | CNF12_0); //clear the bit set by default
	_GPIOB_(GPIOX_CRH) &= ~CNF12_1; //just in case it's set
	_GPIOB_(GPIOX_CRH) |= CNF15_1 | CNF14_1 | CNF13_1; //alt functions
	_GPIOB_(GPIOX_CRH) |= MODE15_1 | MODE15_0 | MODE14_1 | MODE14_0 | MODE13_1 | MODE13_0 | MODE12_1; //output 50 MHz


	//enable spi2 clock; note that SPI2 is in APB1 domain, the slower one
	_RCC_(RCC_APB1ENR) |= RCC_APB1ENR_SPI2EN;
}

void spi2_initMaster(uint16_t bitmode, uint16_t prescaler, uint16_t bidimode, uint8_t sc)
{
	spi2_init();
	//clear CR1 and set bidi or unidi mode
	_SPI2_(SPI_CR1) = bidimode;

	//set bitmode 8 or 16
	_SPI2_ (SPI_CR1) |= bitmode;

	//set prescaler
	_SPI2_ (SPI_CR1) |= prescaler; //3 bits

	//software control of SS
	if (sc) _SPI2_ (SPI_CR1) |= SPI_CR1_SSM | SPI_CR1_SSI; //enable software control of SS, SS high

	//default values used here:
	//CPOL == 0 : SCK will be low when idle
	//CPHA == 0 : rising edge with CPOL = 0; first clock transition
	//LSB_FIRST == 0 : MSB first

	//set SPI master
	_SPI2_ (SPI_CR1) |= SPI_CR1_MSTR; //SPI master
	//enable SPI
	_SPI2_ (SPI_CR1) |= SPI_CR1_SPE; //enable SPI
	//_BBSPI2_ (BB_SPI_CR1 + BB_SPI_CR1_SPE) = 1;
}

uint16_t spi2_transferData(uint16_t dat_out)
{
	while (!(_SPI2_(SPI_SR) & SPI_SR_TXE)); //wait for TXE set (data from DR buffered)
	_SPI2_(SPI_DR) = dat_out; //write a byte or a word into the DR register
	while (!(_SPI2_(SPI_SR) & SPI_SR_RXNE)); //wait for RXNE to get set
	return _SPI2_(SPI_DR);//return contents of DR
}

uint16_t spi2_writeReadData(uint16_t dat_out)
{
	spi2_writeData(dat_out);
	return spi2_readData();
}
