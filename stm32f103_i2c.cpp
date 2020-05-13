/*
 * STM32F103 I2C Master library source
 * Part of STM32F103 register and peripherals library
 *
 * Dpcumentation available in the provided MD file.
 *
 * (c) 2019 Dmitry Reznikov ontaelio(at)gmail.com
 *
 * Can be freely used according to the GNU GPL license.
 */


#include <stdio.h>
#include <stm32f103_gpio_reg.h>
#include <stm32f103_i2c.h>
#include <stm32f103_i2c_reg.h>
#include <stm32f103_rcc_reg.h>
//#include <stm32f103_debugLED.h>

/* ----------- I2C1 -------------------- */

i2c1::i2c1(uint8_t address, uint8_t address_bits): device_addr(address), word_addr(address_bits > 8)
{
	//if (address_bits > 8) word_addr = 1; else word_addr = 0;
}

void i2c1::startAndSendRegisterAddress(uint16_t regaddr)
{
	i2c1_start(device_addr);
	if (word_addr) i2c1_writeByte(regaddr>>8);
	i2c1_writeByte(regaddr&0xFF);
}

void i2c1::write(uint16_t addr, uint8_t stuff)
{
	startAndSendRegisterAddress(addr);
	i2c1_writeLast(stuff);
	i2c1_stop();
}

void i2c1::write16(uint16_t addr, uint16_t stuff)
{
	startAndSendRegisterAddress(addr);
	i2c1_writeByte(stuff>>8);
	i2c1_writeLast(stuff&0xFF);
	i2c1_stop();
}

void i2c1::write32(uint16_t addr, uint32_t stuff)
{
	startAndSendRegisterAddress(addr);
	i2c1_writeByte(stuff>>24);
	i2c1_writeByte(stuff>>16);
	i2c1_writeByte(stuff>>8);
	i2c1_writeLast(stuff&0xFF);
	i2c1_stop();
}

void i2c1::writeStream(uint16_t addr, uint8_t* stuff, uint8_t num)
{
	startAndSendRegisterAddress(addr);
	i2c1_writeStream(stuff, num);
	i2c1_stop();
}

uint8_t i2c1::read(uint16_t addr)
{
	uint8_t result;
	startAndSendRegisterAddress(addr);
	//i2c1_readStart(device_addr);
	result = i2c1_readOneByte(device_addr);
	//i2c1_stop();
	return(result);
}

uint16_t i2c1::read16(uint16_t addr)
{
	uint16_t result;
	startAndSendRegisterAddress(addr);
	result = i2c1_readFirstOfTwo(device_addr)<<8;
	result |= i2c1_DR();
	return result;
}

uint32_t i2c1::read32(uint16_t addr)
{
	uint32_t result;
	uint8_t arr[4];
	startAndSendRegisterAddress(addr);
	i2c1_readStreamMethod2 (device_addr, arr, 4);
	result = (arr[0]<<24) | (arr[1]<<16) | arr[2] << 8 | arr[3];
	return result;
}

void i2c1::readStream(uint16_t addr, uint8_t* arr, uint8_t num)
{
	startAndSendRegisterAddress(addr);
	if (num>3)	i2c1_readStreamMethod2(device_addr, arr, num);
	else if (num == 3)
	{
		*arr = i2c1_readFirstOfThree(device_addr);
		arr++;
		*arr = i2c1_DR();
		arr++;
		i2c1_checkRXNE();
		*arr = i2c1_DR();
	}
	else if (num == 2)
	{
		*arr = i2c1_readFirstOfTwo(device_addr);
		arr++;
		*arr = i2c1_DR();
	}
	else if (num == 1)
	{
		*arr = i2c1_readOneByte(device_addr);
	}

	/* previous version
	i2c1_readStart(device_addr);
	i2c1_readStream(arr, num);
	i2c1_stop();*/
}

uint8_t i2c1_resetBus(uint8_t altpins)
{
	uint8_t pinSDA = 7, pinSCL = 6;

	//turn GPIOB on
	_RCC_(RCC_APB2ENR) |= RCC_APB2ENR_IOPBEN;

	//setup pins and pin variables for AF
	//SDA: input floating
	//SCL: output open drain
	if (altpins == I2C1_ALT)
		{
		pinSDA = 9;
		pinSCL = 8;

		//setup SCL as high impedance
		_GPIOB_(GPIOX_BSRR) = 1<<pinSCL;
		_GPIOB_(GPIOX_CRH) &= ~(CNF9_1 | CNF8_1);
		_GPIOB_(GPIOX_CRH) |= CNF9_0 | CNF8_0;
		_GPIOB_(GPIOX_CRH) &= ~(MODE9_0 | MODE9_1 | MODE8_0);
		_GPIOB_(GPIOX_CRH) |= MODE8_1;
		}
	else
	{
		//setup SCL as high impedance
		_GPIOB_(GPIOX_BSRR) = 1<<pinSCL;
		_GPIOB_(GPIOX_CRL) &= ~(CNF7_1 | CNF6_1);
		_GPIOB_(GPIOX_CRL) |= CNF7_0 | CNF6_0;
		_GPIOB_(GPIOX_CRL) &= ~(MODE7_0 | MODE7_1 | MODE6_0);
		_GPIOB_(GPIOX_CRL) |= MODE6_1;
	}

	//check if SDA is low. If not, return 0
	if ((_GPIOB_(GPIOX_IDR)>>pinSDA) & 1) return 0;

	//produce 9 clock pulses checking SDA after each one.
	//If high, START then STOP, return 0
	for (uint8_t cycles = 0; cycles<9; cycles++)
	{
		//clock low then delay
		_GPIOB_(GPIOX_BRR) = 1<<pinSCL;
		for (volatile uint16_t a=0; a<0xFFFF; a++);
		//clock high then delay
		_GPIOB_(GPIOX_BSRR) = 1<<pinSCL;
		for (volatile uint16_t a=0; a<0xFFFF; a++);

		//check SDA
		if ((_GPIOB_(GPIOX_IDR)>>pinSDA) & 1)
		{
			//create START
			_GPIOB_(GPIOX_BRR) = 1<<pinSDA;
			for (volatile uint16_t a=0; a<0xFFFF; a++);

			//create STOP
			_GPIOB_(GPIOX_BSRR) = 1<<pinSDA;
			for (volatile uint16_t a=0; a<0xFFFF; a++);

			return 0;
		}
	}

	//if 9 clock pulses didn't help, return error
	return 1;
}

void i2c1_init(uint8_t speed, uint8_t altpins)
{
	//default:
	//		SDA = PB7
	//      SCL = PB6
	//alt:
	//      SDA = PB9
	//      SCL = PB8

	//turn clocks on
	I2C1_CLOCK = 1;
	GPIOB_CLOCK = 1;
	AFIO_CLOCK = 1;

	//setup SDA and SCL pins
	if (altpins == I2C1_ALT)
	{
		//remap i2c1 pins
		_AFIO_(AFIO_MAPR) |= AFIO_MAPR_I2C1_REMAP;
		//GPIOB: output open drain, AF
		_GPIOB_(GPIOX_CRH) |= CNF9_0 | CNF9_1 | CNF8_0 | CNF8_1;
		//50 MHz
		_GPIOB_(GPIOX_CRH) |= MODE9_0 | MODE9_1 | MODE8_0 | MODE8_1;
	}
	else
	{
		//GPIOB: output open drain, AF
		_GPIOB_(GPIOX_CRL) |= CNF7_0 | CNF7_1 | CNF6_0 | CNF6_1;
		//50 MHz
		_GPIOB_(GPIOX_CRL) |= MODE7_0 | MODE7_1 | MODE6_0 | MODE6_1;
	}

	//turn i2c _mode_ on (turn off SMBus)
	_I2C1_(I2C_CR1) &= ~I2C_CR1_SMBUS;

	//freq = 36 MHz
	_I2C1_(I2C_CR2) &= ~I2C_CR2_FREQ;
	_I2C1_(I2C_CR2) |= 36;

	if (speed == I2C_FM)
	{
		//400 KHz (TPCLK = 28)
		//30 is max close to 400 kHz (4 with DUTY = 357KHz)
		//rcc = pclk1 / (i2c_speed * 3)
		//rcc with duty on = pclk1 / (i2c_speed * 25)
		_I2C1_(I2C_CCR) |= I2C_CCR_FS;
		_I2C1_(I2C_CCR) &= ~I2C_CCR_DUTY;
		_I2C1_(I2C_CCR) &= ~I2C_CCR_CCR;
		_I2C1_(I2C_CCR) |= 30;

		//TRISE = tr/tcplk1 + 1 ; only integer part. tr == 300
		_I2C1_(I2C_TRISE) &= ~I2C_TRISE_TRISE;
		_I2C1_(I2C_TRISE) |= 11;
	}
	else
	{
		//178 for 100 kHz in SM (TPCLK = 28)
		_I2C1_(I2C_CCR) &= ~I2C_CCR_FS;
		_I2C1_(I2C_CCR) &= ~I2C_CCR_DUTY;
		_I2C1_(I2C_CCR) &= ~I2C_CCR_CCR;
		_I2C1_(I2C_CCR) |= 178;

		//TRISE = tr/tcplk1 + 1 ; only integer part. tr == 1000
		_I2C1_(I2C_TRISE) &= ~I2C_TRISE_TRISE;
		_I2C1_(I2C_TRISE) |= 36;
	}

	//turn on
	_I2C1_(I2C_CR1) |= I2C_CR1_PE;
}

void i2c1_tweak(uint8_t fs_bit, uint8_t duty_bit, uint16_t ccr_val)
{
	//turn I2C1 off
	_I2C1_(I2C_CR1) &= ~I2C_CR1_PE;

	//write ccr values
	_I2C1_(I2C_CCR) &= ~I2C_CCR_FS;
	_I2C1_(I2C_CCR) &= ~I2C_CCR_DUTY;
	_I2C1_(I2C_CCR) &= ~I2C_CCR_CCR;
	_I2C1_(I2C_CCR) |= fs_bit<<15 | duty_bit<<14 | ccr_val;

	//turn I2C1 back on
	_I2C1_(I2C_CR1) |= I2C_CR1_PE;
}

void i2c1_APB1freq(uint8_t pclk1_mhz)
{
	//turn I2C1 off
	_I2C1_(I2C_CR1) &= ~I2C_CR1_PE;

	//calculate CCR val
	//check SM/FM and DUTY bits
	uint8_t sf_bit = _I2C1_(I2C_CCR) >> 15;
	uint8_t duty_bit = 1 & (_I2C1_(I2C_CCR) >> 14);
	uint8_t ccr_value = 0;
	//10 and 4 used instead of 1,000,000 and 400,000
	if (sf_bit && duty_bit) ccr_value = (uint32_t)  (pclk1_mhz * 10) / (4 * 25);
	else if (sf_bit) ccr_value = (uint32_t) (pclk1_mhz * 10) / (4 * 3);
	else ccr_value = (uint32_t) (pclk1_mhz * 10) / (1 * 2);

	//set new freq
	_I2C1_(I2C_CR2) &= ~I2C_CR2_FREQ;
	_I2C1_(I2C_CR2) |= pclk1_mhz;

	//set CCR keeping sf and duty bits
	_I2C1_(I2C_CCR) &= ~I2C_CCR_CCR;
	_I2C1_(I2C_CCR) |= ccr_value;

	//turn I2C1 back on
	_I2C1_(I2C_CR1) |= I2C_CR1_PE;
}

void i2c1_setFreq(uint32_t i2c_freq)
{
	//turn I2C1 off
	_I2C1_(I2C_CR1) &= ~I2C_CR1_PE;

	//get current PCLK1
	uint8_t pclk1_mhz = _I2C1_(I2C_CR2) & I2C_CR2_FREQ;

	//calculate CCR val
	//check SM/FM and DUTY bits
	uint8_t sf_bit = _I2C1_(I2C_CCR) >> 15;
	uint8_t duty_bit = 1 & (_I2C1_(I2C_CCR) >> 14);
	uint8_t ccr_value = 0;

	if (sf_bit && duty_bit) ccr_value = (uint32_t)  (pclk1_mhz * 1000000) / (i2c_freq * 25);
	else if (sf_bit) ccr_value = (uint32_t) (pclk1_mhz * 1000000) / (i2c_freq * 3);
	else ccr_value = (uint32_t) (pclk1_mhz * 1000000) / (i2c_freq * 2);

	//set CCR keeping sf and duty bits
	_I2C1_(I2C_CCR) &= ~I2C_CCR_CCR;
	_I2C1_(I2C_CCR) |= ccr_value;

	//turn I2C1 back on
	_I2C1_(I2C_CR1) |= I2C_CR1_PE;
}

uint8_t i2c1_ping(uint8_t addr) /// ADD ARLO CHECK!!!
{
	uint16_t timeout = 0xFFFF;
	uint8_t error = 0;

	//check if i2c is busy
	while (_I2C1_(I2C_SR2) & I2C_SR2_BUSY)
	{
		if (timeout-- == 0) {error = 1; break;}
	}

	if (error)
	{
		timeout = 0xFFFF;

		//try to reset i2c
		_I2C1_(I2C_CR1) |= I2C_CR1_SWRST;

		//wait a bit
		for (volatile uint32_t a=0; a<9000; a++);

		//clear sw reset bit
		_I2C1_(I2C_CR1) &= ~I2C_CR1_SWRST;

		//test again
		while (_I2C1_(I2C_SR2) & I2C_SR2_BUSY)
		{
			if (timeout-- == 0) return 1;
		}

		//reset error if ok
		error = 0;
	}

	timeout = 0xFFFF;
	//generate start
	_I2C1_(I2C_CR1) |= I2C_CR1_START;

	//check SB in SR1 (start success) or return error 1
	while (!(_I2C1_(I2C_SR1) & I2C_SR1_SB))
	{
		if (timeout-- == 0) {error = 2; break;}
	}

	if (error == 2)
		{
			//check ARLO
			if (_I2C1_(I2C_SR1) & I2C_SR1_ARLO)
			{
				timeout = 0xFFFF;

				//reset ARLO
				_I2C1_(I2C_SR1) &= ~I2C_SR1_ARLO;

				//try again and return error 4 if failed
				_I2C1_(I2C_CR1) |= I2C_CR1_START;

				while (!(_I2C1_(I2C_SR1) & I2C_SR1_SB))
					{
						if (timeout-- == 0) return 3;
					}
				error = 0;
			}
			else return 2;
		}

	//send device address
	_I2C1_(I2C_DR) = addr << 1;

	timeout = 0xFFFF;

	//make sure address is acknowledged or error 2 and break loop
	while (!(_I2C1_(I2C_SR1) & I2C_SR1_ADDR))
	{
		if (timeout-- == 0) {error = 4; break;}
	}

	//clear SR2
	(void) _I2C1_(I2C_SR2);

	//generate stop even if error == 3
	_I2C1_(I2C_CR1) |= I2C_CR1_STOP;
	return error;
}

uint8_t i2c1_scanAddr(uint8_t startAddr)
{
	while (startAddr < 0x77)
	{
		startAddr++;
		if (!i2c1_ping(startAddr)) return startAddr;
	}
	return 0;
}

// Method 2

/*
Case of a single byte to be received:
– In the ADDR event, clear the ACK bit.
– Clear ADDR
– Program the STOP/START bit.
– Read the data after the RxNE flag is set.
*/
uint8_t i2c1_readOneByte(uint8_t addr)
{
	//restart
	_I2C1_(I2C_CR1) |= I2C_CR1_START;

	//check SB is cleared and read SR1
	while (!(_I2C1_(I2C_SR1) & I2C_SR1_SB));

	//send device addr with read bit set
	_I2C1_(I2C_DR) = (addr << 1) | 1;

	//clear ACK
	_I2C1_(I2C_CR1) &= ~I2C_CR1_ACK;

	//clear ADDR
	while (!(_I2C1_(I2C_SR1) & I2C_SR1_ADDR));

	//read SR2 to continue
	(void) _I2C1_(I2C_SR2);

	//set STOP
	_I2C1_(I2C_CR1) |= I2C_CR1_STOP;

	//read data after RxNE is set
	while (!(_I2C1_(I2C_SR1) & I2C_SR1_RXNE));
	return _I2C1_(I2C_DR);
}

/*
• Case of two bytes to be received:
– Set POS and ACK
– Wait for the ADDR flag to be set
– Clear ADDR
– Clear ACK
– Wait for BTF to be set
– Program STOP
– Read DR twice
*/
uint8_t i2c1_readFirstOfTwo(uint8_t addr)
{
	//restart
	_I2C1_(I2C_CR1) |= I2C_CR1_START;

	//check SB is cleared and read SR1
	while (!(_I2C1_(I2C_SR1) & I2C_SR1_SB));

	//set POS and ACK
	_I2C1_(I2C_CR1) |= I2C_CR1_POS;
	_I2C1_(I2C_CR1) |= I2C_CR1_ACK;

	//send device address with read bit set
	_I2C1_(I2C_DR) = (addr << 1) | 1;

	//clear ADDR
	while (!(_I2C1_(I2C_SR1) & I2C_SR1_ADDR));
	(void) _I2C1_(I2C_SR2);

	//clear ACK
	_I2C1_(I2C_CR1) &= ~I2C_CR1_ACK;

	//wait for the BTF bit: first byte in DR, second in the shift register
	while (!(_I2C1_(I2C_SR1) & I2C_SR1_BTF));

	//set STOP
	_I2C1_(I2C_CR1) |= I2C_CR1_STOP;

	//read DR for the first byte, moving second one in DR
	return(_I2C1_(I2C_DR));

	//the second byte is still in the DR register!
}

/*
When 3 bytes remain to be read:
• RxNE = 1 => Nothing (DataN-2 not read).
• DataN-1 received
• BTF = 1 because both shift and data registers are full: DataN-2 in DR and DataN-1 in
the shift register => SCL tied low: no other data will be received on the bus.
• Clear ACK bit
• Read DataN-2 in DR => This will launch the DataN reception in the shift register
• DataN received (with a NACK)
• Program START/STOP
• Read DataN-1
• RxNE = 1
• Read DataN
*/
uint8_t i2c1_readFirstOfThree(uint8_t addr)
{
	uint8_t stuff;

	//restart
	_I2C1_(I2C_CR1) |= I2C_CR1_START;

	//check SB is cleared and read SR1
	while (!(_I2C1_(I2C_SR1) & I2C_SR1_SB));

	//set ACK
	_I2C1_(I2C_CR1) |= I2C_CR1_ACK;

	//send device address with read bit set
	_I2C1_(I2C_DR) = (addr << 1) | 1;

	//clear ADDR
	while (!(_I2C1_(I2C_SR1) & I2C_SR1_ADDR));

	//read SR2 to continue
	(void) _I2C1_(I2C_SR2);

	//wait for the BTF bit: data-2 and data-1 are in
	while (!(_I2C1_(I2C_SR1) & I2C_SR1_BTF));

	//clear ACK
	_I2C1_(I2C_CR1) &= ~I2C_CR1_ACK;

	//read data-2 from DR, data-0 goes into the shift register
	stuff = _I2C1_(I2C_DR);

	//wait for data-0 to be transmitted with a NACK
	while (!(_I2C1_(I2C_SR1) & I2C_SR1_RXNE));

	//STOP
	_I2C1_(I2C_CR1) |= I2C_CR1_STOP;

	return stuff;

	//data-1 is in the DR and can be read
	//to read data-0 first wait for RXNE to get set
}

void i2c1_readStreamMethod2 (uint8_t addr, uint8_t* arr, uint8_t num)
{
	//restart
	_I2C1_(I2C_CR1) |= I2C_CR1_START;

	//check SB is cleared and read SR1
	while (!(_I2C1_(I2C_SR1) & I2C_SR1_SB));

	//set ACK
	_I2C1_(I2C_CR1) |= I2C_CR1_ACK;

	//send device address with read bit set
	_I2C1_(I2C_DR) = (addr << 1) | 1;

	//clear ADDR
	while (!(_I2C1_(I2C_SR1) & I2C_SR1_ADDR));

	//read SR2 to continue
	(void) _I2C1_(I2C_SR2);

	while(num>3)
	{
		while (!(_I2C1_(I2C_SR1) & I2C_SR1_RXNE));
		*arr = _I2C1_(I2C_DR);
		arr++;
		num--;
	}

	//wait for the BTF bit: data-2 and data-1 are in
	while (!(_I2C1_(I2C_SR1) & I2C_SR1_BTF));

	//clear ACK
	_I2C1_(I2C_CR1) &= ~I2C_CR1_ACK;

	//read data-2 from DR, data-0 goes into the shift register
	*arr = _I2C1_(I2C_DR);
	arr++; //pointer at data-1

	//wait for data-0 to be transmitted with a NACK
	while (!(_I2C1_(I2C_SR1) & I2C_SR1_RXNE));

	//STOP
	_I2C1_(I2C_CR1) |= I2C_CR1_STOP;

	*arr = _I2C1_(I2C_DR);
	arr++; //pointer at data-0

	//make sure the last byte is in DR
	while (!(_I2C1_(I2C_SR1) & I2C_SR1_RXNE));
	*arr = _I2C1_(I2C_DR);
}

// generic and Method 1 functions

void i2c1_start(uint8_t addr)
{
	//check if i2c is busy
	while (_I2C1_(I2C_SR2) & I2C_SR2_BUSY);

	//start
	_I2C1_(I2C_CR1) |= I2C_CR1_START;

	//check SB is cleared and read SR1
	while (!(_I2C1_(I2C_SR1) & I2C_SR1_SB));

	//send device address
	_I2C1_(I2C_DR) = addr << 1;

	//check ADDR is cleared then read SR2
	while (!(_I2C1_(I2C_SR1) & I2C_SR1_ADDR));
	(void) _I2C1_(I2C_SR2);
}

void i2c1_writeByte(uint8_t stuff)
{
	//send byte
	_I2C1_(I2C_DR) = stuff;

	//TxE gets set once the byte goes into the internal shift register
	while (!(_I2C1_(I2C_SR1) & I2C_SR1_TXE));
}

void i2c1_writeLast(uint8_t stuff)
{
	//send data
	_I2C1_(I2C_DR) = stuff;

	//wait for BTF (send complete) before stopping communication
	while (!(_I2C1_(I2C_SR1) & I2C_SR1_BTF));
}

void i2c1_writeStream (uint8_t* arr, uint8_t num)
{
	uint8_t counter = 0;
	while (num>1)
	{
		i2c1_writeByte (*(arr+counter));
		counter++;
		num--;
	}

	i2c1_writeLast (*(arr+counter));
}

void i2c1_stop()
{
	//stop
	_I2C1_(I2C_CR1) |= I2C_CR1_STOP;
}

void i2c1_readStart(uint8_t addr)
{
	//start
	_I2C1_(I2C_CR1) |= I2C_CR1_START;

	//check SB is cleared and read SR1
	while (!(_I2C1_(I2C_SR1) & I2C_SR1_SB));

	//send device address to read
	_I2C1_(I2C_DR) = (addr << 1) | 1;

	//check ADDR is cleared then read SR2
	while (!(_I2C1_(I2C_SR1) & I2C_SR1_ADDR));
	(void) _I2C1_(I2C_SR2);

	//acknowledge will be returned;
	_I2C1_(I2C_CR1) |= I2C_CR1_ACK;
}

uint8_t i2c1_readByte()
{

	while (!(_I2C1_(I2C_SR1) & I2C_SR1_RXNE));
	return _I2C1_(I2C_DR);
}

uint8_t i2c1_readLast()
{
	uint8_t stuff;

	//don't send acknowledge
	_I2C1_(I2C_CR1) &= ~I2C_CR1_ACK;

	//read
	while (!(_I2C1_(I2C_SR1) & I2C_SR1_RXNE));
	stuff = _I2C1_(I2C_DR);

	return(stuff);
}

void i2c1_readStream(uint8_t* arr, uint8_t num)
{

	while (num>1)
	{
		*arr = i2c1_readByte();
		arr++;
		num--;
	}

	*arr = i2c1_readLast();
}


/* ----------- I2C2 -------------------- */

i2c2::i2c2(uint8_t address, uint8_t address_bits): device_addr(address), word_addr(address_bits > 8)
{
	//if (address_bits > 8) word_addr = 1; else word_addr = 0;
}

void i2c2::startAndSendRegisterAddress(uint16_t regaddr)
{
	i2c2_start(device_addr);
	if (word_addr) i2c2_writeByte(regaddr>>8);
	i2c2_writeByte(regaddr&0xFF);
}

void i2c2::write(uint16_t addr, uint8_t stuff)
{
	startAndSendRegisterAddress(addr);
	i2c2_writeLast(stuff);
	i2c2_stop();
}

void i2c2::write16(uint16_t addr, uint16_t stuff)
{
	startAndSendRegisterAddress(addr);
	i2c2_writeByte(stuff>>8);
	i2c2_writeLast(stuff&0xFF);
	i2c2_stop();
}

void i2c2::write32(uint16_t addr, uint32_t stuff)
{
	startAndSendRegisterAddress(addr);
	i2c2_writeByte(stuff>>24);
	i2c2_writeByte(stuff>>16);
	i2c2_writeByte(stuff>>8);
	i2c2_writeLast(stuff&0xFF);
	i2c2_stop();
}

void i2c2::writeStream(uint16_t addr, uint8_t* stuff, uint8_t num)
{
	startAndSendRegisterAddress(addr);
	i2c2_writeStream(stuff, num);
	i2c2_stop();
}

uint8_t i2c2::read(uint16_t addr)
{
	uint8_t result;
	startAndSendRegisterAddress(addr);
	//i2c2_readStart(device_addr);
	result = i2c2_readOneByte(device_addr);
	//i2c2_stop();
	return(result);
}

uint16_t i2c2::read16(uint16_t addr)
{
	uint16_t result;
	startAndSendRegisterAddress(addr);
	result = i2c2_readFirstOfTwo(device_addr)<<8;
	result |= i2c2_DR();
	return result;
}

uint32_t i2c2::read32(uint16_t addr)
{
	uint32_t result;
	uint8_t arr[4];
	startAndSendRegisterAddress(addr);
	i2c2_readStreamMethod2 (device_addr, arr, 4);
	result = (arr[0]<<24) | (arr[1]<<16) | arr[2] << 8 | arr[3];
	return result;
}

void i2c2::readStream(uint16_t addr, uint8_t* arr, uint8_t num)
{
	startAndSendRegisterAddress(addr);
	if (num>3)	i2c2_readStreamMethod2(device_addr, arr, num);
	else if (num == 3)
	{
		*arr = i2c2_readFirstOfThree(device_addr);
		arr++;
		*arr = i2c2_DR();
		arr++;
		i2c2_checkRXNE();
		*arr = i2c2_DR();
	}
	else if (num == 2)
	{
		*arr = i2c2_readFirstOfTwo(device_addr);
		arr++;
		*arr = i2c2_DR();
	}
	else if (num == 1)
	{
		*arr = i2c2_readOneByte(device_addr);
	}

	/* previous version
	i2c2_readStart(device_addr);
	i2c2_readStream(arr, num);
	i2c2_stop();*/
}

uint8_t i2c2_resetBus()
{
	uint8_t pinSDA = 11, pinSCL = 10;

	//turn GPIOB on
	_RCC_(RCC_APB2ENR) |= RCC_APB2ENR_IOPBEN;

	//setup pins and pin variables for AF
	//SDA: input floating
	//SCL: output open drain
	//setup SCL as high impedance
	_GPIOB_(GPIOX_BSRR) = 1<<pinSCL;
	_GPIOB_(GPIOX_CRH) &= ~(CNF11_1 | CNF10_1);
	_GPIOB_(GPIOX_CRH) |= CNF11_0 | CNF10_0;
	_GPIOB_(GPIOX_CRH) &= ~(MODE11_0 | MODE11_1 | MODE10_0);
	_GPIOB_(GPIOX_CRH) |= MODE10_1;

	//check if SDA is low. If not, return 0
	if ((_GPIOB_(GPIOX_IDR)>>pinSDA) & 1) return 0;

	//produce 9 clock pulses checking SDA after each one.
	//If high, START then STOP, return 0
	for (uint8_t cycles = 0; cycles<9; cycles++)
	{
		//clock low then delay
		_GPIOB_(GPIOX_BRR) = 1<<pinSCL;
		for (volatile uint16_t a=0; a<0xFFFF; a++);
		//clock high then delay
		_GPIOB_(GPIOX_BSRR) = 1<<pinSCL;
		for (volatile uint16_t a=0; a<0xFFFF; a++);

		//check SDA
		if ((_GPIOB_(GPIOX_IDR)>>pinSDA) & 1)
		{
			//create START
			_GPIOB_(GPIOX_BRR) = 1<<pinSDA;
			for (volatile uint16_t a=0; a<0xFFFF; a++);

			//create STOP
			_GPIOB_(GPIOX_BSRR) = 1<<pinSDA;
			for (volatile uint16_t a=0; a<0xFFFF; a++);

			return 0;
		}
	}

	//if 9 clock pulses didn't help, return error
	return 1;
}

void i2c2_init(uint8_t speed)
{
	//		SDA = PB11
	//      SCL = PB10

	//turn clocks on
	I2C2_CLOCK = 1;
	GPIOB_CLOCK = 1;
	AFIO_CLOCK = 1;

	//setup SDA and SCL pins
	//GPIOB: output open drain, AF
	_GPIOB_(GPIOX_CRH) |= CNF11_0 | CNF11_1 | CNF10_0 | CNF10_1;
	//50 MHz
	_GPIOB_(GPIOX_CRH) |= MODE11_0 | MODE11_1 | MODE10_0 | MODE10_1;


	//turn i2c _mode_ on (turn off SMBus)
	_I2C2_(I2C_CR1) &= ~I2C_CR1_SMBUS;

	//freq = 36 MHz
	_I2C2_(I2C_CR2) &= ~I2C_CR2_FREQ;
	_I2C2_(I2C_CR2) |= 36;

	if (speed == I2C_FM)
	{
		//400 KHz (TPCLK = 28)
		//30 is max close to 400 kHz (4 with DUTY = 357KHz)
		//rcc = pclk1 / (i2c_speed * 3)
		//rcc with duty on = pclk1 / (i2c_speed * 25)
		_I2C2_(I2C_CCR) |= I2C_CCR_FS;
		_I2C2_(I2C_CCR) &= ~I2C_CCR_DUTY;
		_I2C2_(I2C_CCR) &= ~I2C_CCR_CCR;
		_I2C2_(I2C_CCR) |= 30;

		//TRISE = tr/tcplk1 + 1 ; only integer part. tr == 300
		_I2C2_(I2C_TRISE) &= ~I2C_TRISE_TRISE;
		_I2C2_(I2C_TRISE) |= 11;
	}
	else
	{
		//178 for 100 kHz in SM (TPCLK = 28)
		_I2C2_(I2C_CCR) &= ~I2C_CCR_FS;
		_I2C2_(I2C_CCR) &= ~I2C_CCR_DUTY;
		_I2C2_(I2C_CCR) &= ~I2C_CCR_CCR;
		_I2C2_(I2C_CCR) |= 178;

		//TRISE = tr/tcplk1 + 1 ; only integer part. tr == 1000
		_I2C2_(I2C_TRISE) &= ~I2C_TRISE_TRISE;
		_I2C2_(I2C_TRISE) |= 36;
	}

	//turn on
	_I2C2_(I2C_CR1) |= I2C_CR1_PE;
}

void i2c2_tweak(uint8_t fs_bit, uint8_t duty_bit, uint16_t ccr_val)
{
	//turn I2C2 off
	_I2C2_(I2C_CR1) &= ~I2C_CR1_PE;

	//write ccr values
	_I2C2_(I2C_CCR) &= ~I2C_CCR_FS;
	_I2C2_(I2C_CCR) &= ~I2C_CCR_DUTY;
	_I2C2_(I2C_CCR) &= ~I2C_CCR_CCR;
	_I2C2_(I2C_CCR) |= fs_bit<<15 | duty_bit<<14 | ccr_val;

	//turn I2C2 back on
	_I2C2_(I2C_CR1) |= I2C_CR1_PE;
}

void i2c2_APB1freq(uint8_t pclk1_mhz)
{
	//turn I2C2 off
	_I2C2_(I2C_CR1) &= ~I2C_CR1_PE;

	//calculate CCR val
	//check SM/FM and DUTY bits
	uint8_t sf_bit = _I2C2_(I2C_CCR) >> 15;
	uint8_t duty_bit = 1 & (_I2C2_(I2C_CCR) >> 14);
	uint8_t ccr_value = 0;
	//10 and 4 used instead of 1,000,000 and 400,000
	if (sf_bit && duty_bit) ccr_value = (uint32_t)  (pclk1_mhz * 10) / (4 * 25);
	else if (sf_bit) ccr_value = (uint32_t) (pclk1_mhz * 10) / (4 * 3);
	else ccr_value = (uint32_t) (pclk1_mhz * 10) / (1 * 2);

	//set new freq
	_I2C2_(I2C_CR2) &= ~I2C_CR2_FREQ;
	_I2C2_(I2C_CR2) |= pclk1_mhz;

	//set CCR keeping sf and duty bits
	_I2C2_(I2C_CCR) &= ~I2C_CCR_CCR;
	_I2C2_(I2C_CCR) |= ccr_value;

	//turn I2C2 back on
	_I2C2_(I2C_CR1) |= I2C_CR1_PE;
}

void i2c2_setFreq(uint32_t i2c_freq)
{
	//turn I2C2 off
	_I2C2_(I2C_CR1) &= ~I2C_CR1_PE;

	//get current PCLK1
	uint8_t pclk1_mhz = _I2C2_(I2C_CR2) & I2C_CR2_FREQ;

	//calculate CCR val
	//check SM/FM and DUTY bits
	uint8_t sf_bit = _I2C2_(I2C_CCR) >> 15;
	uint8_t duty_bit = 1 & (_I2C2_(I2C_CCR) >> 14);
	uint8_t ccr_value = 0;

	if (sf_bit && duty_bit) ccr_value = (uint32_t)  (pclk1_mhz * 1000000) / (i2c_freq * 25);
	else if (sf_bit) ccr_value = (uint32_t) (pclk1_mhz * 1000000) / (i2c_freq * 3);
	else ccr_value = (uint32_t) (pclk1_mhz * 1000000) / (i2c_freq * 2);

	//set CCR keeping sf and duty bits
	_I2C2_(I2C_CCR) &= ~I2C_CCR_CCR;
	_I2C2_(I2C_CCR) |= ccr_value;

	//turn I2C2 back on
	_I2C2_(I2C_CR1) |= I2C_CR1_PE;
}

uint8_t i2c2_ping(uint8_t addr) /// ADD ARLO CHECK!!!
{
	uint16_t timeout = 0xFFFF;
	uint8_t error = 0;

	//check if i2c is busy
	while (_I2C2_(I2C_SR2) & I2C_SR2_BUSY)
	{
		if (timeout-- == 0) {error = 1; break;}
	}

	if (error)
	{
		timeout = 0xFFFF;

		//try to reset i2c
		_I2C2_(I2C_CR1) |= I2C_CR1_SWRST;

		//wait a bit
		for (volatile uint32_t a=0; a<9000; a++);

		//clear sw reset bit
		_I2C2_(I2C_CR1) &= ~I2C_CR1_SWRST;

		//test again
		while (_I2C2_(I2C_SR2) & I2C_SR2_BUSY)
		{
			if (timeout-- == 0) return 1;
		}

		//reset error if ok
		error = 0;
	}

	timeout = 0xFFFF;
	//generate start
	_I2C2_(I2C_CR1) |= I2C_CR1_START;

	//check SB in SR1 (start success) or return error 1
	while (!(_I2C2_(I2C_SR1) & I2C_SR1_SB))
	{
		if (timeout-- == 0) {error = 2; break;}
	}

	if (error == 2)
		{
			//check ARLO
			if (_I2C2_(I2C_SR1) & I2C_SR1_ARLO)
			{
				timeout = 0xFFFF;

				//reset ARLO
				_I2C2_(I2C_SR1) &= ~I2C_SR1_ARLO;

				//try again and return error 4 if failed
				_I2C2_(I2C_CR1) |= I2C_CR1_START;

				while (!(_I2C2_(I2C_SR1) & I2C_SR1_SB))
					{
						if (timeout-- == 0) return 3;
					}
				error = 0;
			}
			else return 2;
		}

	//send device address
	_I2C2_(I2C_DR) = addr << 1;

	timeout = 0xFFFF;

	//make sure address is acknowledged or error 2 and break loop
	while (!(_I2C2_(I2C_SR1) & I2C_SR1_ADDR))
	{
		if (timeout-- == 0) {error = 4; break;}
	}

	//clear SR2
	(void) _I2C2_(I2C_SR2);

	//generate stop even if error == 3
	_I2C2_(I2C_CR1) |= I2C_CR1_STOP;
	return error;
}

uint8_t i2c2_scanAddr(uint8_t startAddr)
{
	while (startAddr < 0x77)
	{
		startAddr++;
		if (!i2c2_ping(startAddr)) return startAddr;
	}
	return 0;
}

// Method 2

/*
Case of a single byte to be received:
– In the ADDR event, clear the ACK bit.
– Clear ADDR
– Program the STOP/START bit.
– Read the data after the RxNE flag is set.
*/
uint8_t i2c2_readOneByte(uint8_t addr)
{
	//restart
	_I2C2_(I2C_CR1) |= I2C_CR1_START;

	//check SB is cleared and read SR1
	while (!(_I2C2_(I2C_SR1) & I2C_SR1_SB));

	//send device addr with read bit set
	_I2C2_(I2C_DR) = (addr << 1) | 1;

	//clear ACK
	_I2C2_(I2C_CR1) &= ~I2C_CR1_ACK;

	//clear ADDR
	while (!(_I2C2_(I2C_SR1) & I2C_SR1_ADDR));

	//read SR2 to continue
	(void) _I2C2_(I2C_SR2);

	//set STOP
	_I2C2_(I2C_CR1) |= I2C_CR1_STOP;

	//read data after RxNE is set
	while (!(_I2C2_(I2C_SR1) & I2C_SR1_RXNE));
	return _I2C2_(I2C_DR);
}

/*
• Case of two bytes to be received:
– Set POS and ACK
– Wait for the ADDR flag to be set
– Clear ADDR
– Clear ACK
– Wait for BTF to be set
– Program STOP
– Read DR twice
*/
uint8_t i2c2_readFirstOfTwo(uint8_t addr)
{
	//restart
	_I2C2_(I2C_CR1) |= I2C_CR1_START;

	//check SB is cleared and read SR1
	while (!(_I2C2_(I2C_SR1) & I2C_SR1_SB));

	//set POS and ACK
	_I2C2_(I2C_CR1) |= I2C_CR1_POS;
	_I2C2_(I2C_CR1) |= I2C_CR1_ACK;

	//send device address with read bit set
	_I2C2_(I2C_DR) = (addr << 1) | 1;

	//clear ADDR
	while (!(_I2C2_(I2C_SR1) & I2C_SR1_ADDR));
	(void) _I2C2_(I2C_SR2);

	//clear ACK
	_I2C2_(I2C_CR1) &= ~I2C_CR1_ACK;

	//wait for the BTF bit: first byte in DR, second in the shift register
	while (!(_I2C2_(I2C_SR1) & I2C_SR1_BTF));

	//set STOP
	_I2C2_(I2C_CR1) |= I2C_CR1_STOP;

	//read DR for the first byte, moving second one in DR
	return(_I2C2_(I2C_DR));

	//the second byte is still in the DR register!
}

/*
When 3 bytes remain to be read:
• RxNE = 1 => Nothing (DataN-2 not read).
• DataN-1 received
• BTF = 1 because both shift and data registers are full: DataN-2 in DR and DataN-1 in
the shift register => SCL tied low: no other data will be received on the bus.
• Clear ACK bit
• Read DataN-2 in DR => This will launch the DataN reception in the shift register
• DataN received (with a NACK)
• Program START/STOP
• Read DataN-1
• RxNE = 1
• Read DataN
*/
uint8_t i2c2_readFirstOfThree(uint8_t addr)
{
	uint8_t stuff;

	//restart
	_I2C2_(I2C_CR1) |= I2C_CR1_START;

	//check SB is cleared and read SR1
	while (!(_I2C2_(I2C_SR1) & I2C_SR1_SB));

	//set ACK
	_I2C2_(I2C_CR1) |= I2C_CR1_ACK;

	//send device address with read bit set
	_I2C2_(I2C_DR) = (addr << 1) | 1;

	//clear ADDR
	while (!(_I2C2_(I2C_SR1) & I2C_SR1_ADDR));

	//read SR2 to continue
	(void) _I2C2_(I2C_SR2);

	//wait for the BTF bit: data-2 and data-1 are in
	while (!(_I2C2_(I2C_SR1) & I2C_SR1_BTF));

	//clear ACK
	_I2C2_(I2C_CR1) &= ~I2C_CR1_ACK;

	//read data-2 from DR, data-0 goes into the shift register
	stuff = _I2C2_(I2C_DR);

	//wait for data-0 to be transmitted with a NACK
	while (!(_I2C2_(I2C_SR1) & I2C_SR1_RXNE));

	//STOP
	_I2C2_(I2C_CR1) |= I2C_CR1_STOP;

	return stuff;

	//data-1 is in the DR and can be read
	//to read data-0 first wait for RXNE to get set
}

void i2c2_readStreamMethod2 (uint8_t addr, uint8_t* arr, uint8_t num)
{
	//restart
	_I2C2_(I2C_CR1) |= I2C_CR1_START;

	//check SB is cleared and read SR1
	while (!(_I2C2_(I2C_SR1) & I2C_SR1_SB));

	//set ACK
	_I2C2_(I2C_CR1) |= I2C_CR1_ACK;

	//send device address with read bit set
	_I2C2_(I2C_DR) = (addr << 1) | 1;

	//clear ADDR
	while (!(_I2C2_(I2C_SR1) & I2C_SR1_ADDR));

	//read SR2 to continue
	(void) _I2C2_(I2C_SR2);

	while(num>3)
	{
		while (!(_I2C2_(I2C_SR1) & I2C_SR1_RXNE));
		*arr = _I2C2_(I2C_DR);
		arr++;
		num--;
	}

	//wait for the BTF bit: data-2 and data-1 are in
	while (!(_I2C2_(I2C_SR1) & I2C_SR1_BTF));

	//clear ACK
	_I2C2_(I2C_CR1) &= ~I2C_CR1_ACK;

	//read data-2 from DR, data-0 goes into the shift register
	*arr = _I2C2_(I2C_DR);
	arr++; //pointer at data-1

	//wait for data-0 to be transmitted with a NACK
	while (!(_I2C2_(I2C_SR1) & I2C_SR1_RXNE));

	//STOP
	_I2C2_(I2C_CR1) |= I2C_CR1_STOP;

	*arr = _I2C2_(I2C_DR);
	arr++; //pointer at data-0

	//make sure the last byte is in DR
	while (!(_I2C2_(I2C_SR1) & I2C_SR1_RXNE));
	*arr = _I2C2_(I2C_DR);
}

// generic and Method 1 functions

void i2c2_start(uint8_t addr)
{
	//check if i2c is busy
	while (_I2C2_(I2C_SR2) & I2C_SR2_BUSY);

	//start
	_I2C2_(I2C_CR1) |= I2C_CR1_START;

	//check SB is cleared and read SR1
	while (!(_I2C2_(I2C_SR1) & I2C_SR1_SB));

	//send device address
	_I2C2_(I2C_DR) = addr << 1;

	//check ADDR is cleared then read SR2
	while (!(_I2C2_(I2C_SR1) & I2C_SR1_ADDR));
	(void) _I2C2_(I2C_SR2);
}

void i2c2_writeByte(uint8_t stuff)
{
	//send byte
	_I2C2_(I2C_DR) = stuff;

	//TxE gets set once the byte goes into the internal shift register
	while (!(_I2C2_(I2C_SR1) & I2C_SR1_TXE));
}

void i2c2_writeLast(uint8_t stuff)
{
	//send data
	_I2C2_(I2C_DR) = stuff;

	//wait for BTF (send complete) before stopping communication
	while (!(_I2C2_(I2C_SR1) & I2C_SR1_BTF));
}

void i2c2_writeStream (uint8_t* arr, uint8_t num)
{
	uint8_t counter = 0;
	while (num>1)
	{
		i2c2_writeByte (*(arr+counter));
		counter++;
		num--;
	}

	i2c2_writeLast (*(arr+counter));
}

void i2c2_stop()
{
	//stop
	_I2C2_(I2C_CR1) |= I2C_CR1_STOP;
}

void i2c2_readStart(uint8_t addr)
{
	//start
	_I2C2_(I2C_CR1) |= I2C_CR1_START;

	//check SB is cleared and read SR1
	while (!(_I2C2_(I2C_SR1) & I2C_SR1_SB));

	//send device address to read
	_I2C2_(I2C_DR) = (addr << 1) | 1;

	//check ADDR is cleared then read SR2
	while (!(_I2C2_(I2C_SR1) & I2C_SR1_ADDR));
	(void) _I2C2_(I2C_SR2);

	//acknowledge will be returned;
	_I2C2_(I2C_CR1) |= I2C_CR1_ACK;
}

uint8_t i2c2_readByte()
{

	while (!(_I2C2_(I2C_SR1) & I2C_SR1_RXNE));
	return _I2C2_(I2C_DR);
}

uint8_t i2c2_readLast()
{
	uint8_t stuff;

	//don't send acknowledge
	_I2C2_(I2C_CR1) &= ~I2C_CR1_ACK;

	//read
	while (!(_I2C2_(I2C_SR1) & I2C_SR1_RXNE));
	stuff = _I2C2_(I2C_DR);

	return(stuff);
}

void i2c2_readStream(uint8_t* arr, uint8_t num)
{

	while (num>1)
	{
		*arr = i2c2_readByte();
		arr++;
		num--;
	}

	*arr = i2c2_readLast();
}
