/*
 * STM32F103 GPIO and AFIO functions library
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
#include <stm32f103_gpio_func.h>

gpioA::gpioA(uint8_t pinnum, uint8_t dir, uint8_t cnfod)
{
	pin = pinnum;
	mode(dir, cnfod);
}

gpioA::gpioA(uint8_t pinnum)
{
	pin = pinnum;
}

gpioA::gpioA()
{
	static uint8_t pincount;
	pin = pincount;
	pincount++;
}

void gpioA::set()
{
	_GPIOA_(GPIOX_BSRR) = 1<<pin;
}

void gpioA::high()
{
	_GPIOA_(GPIOX_BSRR) = 1<<pin;
}

void gpioA::reset()
{
	_GPIOA_(GPIOX_BRR) = 1<<pin;
}

void gpioA::low()
{
	_GPIOA_(GPIOX_BRR) = 1<<pin;
}


void gpioA::invert()
{
	_GPIOA_(GPIOX_BSRR) = 1 << (pin + ((_GPIOA_(GPIOX_ODR)>>pin)&1)*16);
}

uint8_t gpioA::read()
{
	uint8_t val = (_GPIOA_(GPIOX_IDR) >> pin) & 1;
	return val;
}

void gpioA::write(uint8_t val)
{
	if (val) set(); else reset();
}

void gpioA::mode(uint8_t speed, uint8_t cnf)
{
	uint8_t pinpos = pin%8;
	uint8_t highlow = (pin<8) ? GPIOX_CRL:GPIOX_CRH;

	_GPIOA_(highlow) &= ~(0x0F << (pinpos*4));

	if (speed) _GPIOA_(highlow) |= (speed + cnf) << (pinpos*4);
	else
	{
		_GPIOA_(highlow) |= (cnf&0x0C) << (pinpos*4);
		_GPIOA_(GPIOX_ODR) |= (cnf&1) << pin;
	}
}



gpioB::gpioB(uint8_t pinnum, uint8_t dir, uint8_t cnfod)
{
	pin = pinnum;
	mode(dir, cnfod);
}

gpioB::gpioB(uint8_t pinnum)
{
	pin = pinnum;
}

gpioB::gpioB()
{
	static uint8_t pincount;
	pin = pincount;
	pincount++;
}


void gpioB::set()
{
	_GPIOB_(GPIOX_BSRR) = 1<<pin;
}

void gpioB::high()
{
	_GPIOB_(GPIOX_BSRR) = 1<<pin;
}

void gpioB::reset()
{
	_GPIOB_(GPIOX_BRR) = 1<<pin;
}


void gpioB::low()
{
	_GPIOB_(GPIOX_BRR) = 1<<pin;
}


void gpioB::invert()
{
	_GPIOB_(GPIOX_BSRR) = 1 << (pin + ((_GPIOB_(GPIOX_ODR)>>pin)&1)*16);
}

uint8_t gpioB::read()
{
	uint8_t val = (_GPIOB_(GPIOX_IDR) >> pin) & 1;
	return val;
}

void gpioB::write(uint8_t val)
{
	if (val) set(); else reset();
}

void gpioB::mode(uint8_t speed, uint8_t cnf)
{
	uint8_t pinpos = pin%8;
	uint8_t highlow = (pin<8) ? GPIOX_CRL:GPIOX_CRH;

	_GPIOB_(highlow) &= ~(0x0F << (pinpos*4));

	if (speed) _GPIOB_(highlow) |= (speed + cnf) << (pinpos*4);
	else
	{
		_GPIOB_(highlow) |= (cnf&0x0C) << (pinpos*4);
		_GPIOB_(GPIOX_ODR) |= (cnf&1) << pin;
	}
}



gpioC::gpioC(uint8_t pinnum, uint8_t dir, uint8_t cnfod)
{
	pin = pinnum;
	mode(dir, cnfod);
}

gpioC::gpioC(uint8_t pinnum)
{
	pin = pinnum;
}

gpioC::gpioC()
{
	static uint8_t pincount;
	pin = pincount;
	pincount++;
}

void gpioC::set()
{
	_GPIOC_(GPIOX_BSRR) = 1<<pin;
}

void gpioC::high()
{
	_GPIOC_(GPIOX_BSRR) = 1<<pin;
}

void gpioC::reset()
{
	_GPIOC_(GPIOX_BRR) = 1<<pin;
}


void gpioC::low()
{
	_GPIOC_(GPIOX_BRR) = 1<<pin;
}


void gpioC::invert()
{
	_GPIOC_(GPIOX_BSRR) = 1 << (pin + ((_GPIOC_(GPIOX_ODR)>>pin)&1)*16);
}

uint8_t gpioC::read()
{
	uint8_t val = (_GPIOC_(GPIOX_IDR) >> pin) & 1;
	return val;
}

void gpioC::write(uint8_t val)
{
	if (val) set(); else reset();
}

void gpioC::mode(uint8_t speed, uint8_t cnf)
{
	uint8_t pinpos = pin%8;
	uint8_t highlow = (pin<8) ? GPIOX_CRL:GPIOX_CRH;

	_GPIOC_(highlow) &= ~(0x0F << (pinpos*4));

	if (speed) _GPIOC_(highlow) |= (speed + cnf) << (pinpos*4);
	else
	{
		_GPIOC_(highlow) |= (cnf&0x0C) << (pinpos*4);
		_GPIOC_(GPIOX_ODR) |= (cnf&1) << pin;
	}
}


//pins:
//1 = MODEX_0
//2 = MODEX_1
//4 = CNFX_0
//8 = CNFX_1
// << (4*pinNum)

//#define PB5_INPUT {_GPIOC_(GPIOX_CRL) &= ~((1+2+8)<<20)); _GPIOC_(GPIOX_CRL) |= 4<<20;}
//#define PB5_OUTPUT_OD {_GPIOC_(GPIOX_CRL) &= ~((8+1)<<20); _GPIOC_(GPIOX_CRL) |= (2+4)<<20;}






/*
PB6_INPUT_PU //odr = 1
PB6_INPUT_PD // odr = 0
PB6_ANALOG

PB6_OUTPUT
PB6_OUTPUT_OD

PB6_OUT_PP_2
PB6_OUT_PP_10
PB6_OUT_PP_50
PB6_OUT_OD_2
PB6_OUT_OD_10
PB6_OUT_OD_50

PB6_OUT_AFPP_2
PB6_OUT_AFPP_10
PB6_OUT_AFPP_50

PB6_OUT_AFOD_2
PB6_OUT_AFOD_10
PB6_OUT_AFOD_50


*/
