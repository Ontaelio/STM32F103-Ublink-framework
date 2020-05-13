/*
 * STM32F103 GPIO and AFIO functions library
 * Part of STM32F103 register and peripherals library
 *
 * Documentation available in the provided MD file.
 *
 * (c) 2019 Dmitry Reznikov ontaelio(at)gmail.com
 *
 * Can be freely used according to the GNU GPL license.
 */

#include <stdio.h>
#include <stm32f103_gpio.h>
#include <stm32f103_gpio_reg.h>
#include <stm32f103_exti.h>

void gpio_pin::priority(uint8_t pri)
{
	switch (pin)
	{
		case 0:  irq_priority(EXTI0_IRQ, pri); break;
		case 1:  irq_priority(EXTI1_IRQ, pri); break;
		case 2:  irq_priority(EXTI2_IRQ, pri); break;
		case 3:  irq_priority(EXTI3_IRQ, pri); break;
		case 4:  irq_priority(EXTI4_IRQ, pri); break;
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:  irq_priority(EXTI9_5_IRQ, pri); break;
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15: irq_priority(EXTI15_10_IRQ, pri); break;
		default: break;
	}
}


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

void gpioA::exti(uint8_t crbits)
{
	_RCC_(RCC_APB2ENR) |= RCC_APB2ENR_AFIOEN;
	_AFIO_(AFIO_EXTICR1 + (pin/4)*4) &= ~(0xF << ((pin&3)*4));
	//_AFIO_(AFIO_EXTICR1 + (pin/4)*4) |= EXTI_GPIOA << ((pin&3)*4);
	if (crbits & EXTI_EVENT) exti_eventenable(pin); else exti_eventdisable(pin);
	if (crbits & EXTI_INTERRUPT) exti_interruptenable(pin); else exti_interruptdisable(pin);
	if (crbits & EXTI_RISING) exti_rising(pin); else exti_risingdisable(pin);
	if (crbits & EXTI_FALLING) exti_falling(pin); else exti_fallingdisable(pin);
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

void gpioB::exti(uint8_t crbits)
{
	_RCC_(RCC_APB2ENR) |= RCC_APB2ENR_AFIOEN;
	_AFIO_(AFIO_EXTICR1 + (pin/4)*4) &= ~(0xF << ((pin&3)*4));
	_AFIO_(AFIO_EXTICR1 + (pin/4)*4) |= EXTI_GPIOB << ((pin&3)*4);
	if (crbits & EXTI_EVENT) exti_eventenable(pin); else exti_eventdisable(pin);
	if (crbits & EXTI_INTERRUPT) exti_interruptenable(pin); else exti_interruptdisable(pin);
	if (crbits & EXTI_RISING) exti_rising(pin); else exti_risingdisable(pin);
	if (crbits & EXTI_FALLING) exti_falling(pin); else exti_fallingdisable(pin);
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

void gpioC::exti(uint8_t crbits)
{
	_RCC_(RCC_APB2ENR) |= RCC_APB2ENR_AFIOEN;
	_AFIO_(AFIO_EXTICR1 + (pin/4)*4) &= ~(0xF << ((pin&3)*4));
	_AFIO_(AFIO_EXTICR1 + (pin/4)*4) |= EXTI_GPIOC << ((pin&3)*4);
	if (crbits & EXTI_EVENT) exti_eventenable(pin); else exti_eventdisable(pin);
	if (crbits & EXTI_INTERRUPT) exti_interruptenable(pin); else exti_interruptdisable(pin);
	if (crbits & EXTI_RISING) exti_rising(pin); else exti_risingdisable(pin);
	if (crbits & EXTI_FALLING) exti_falling(pin); else exti_fallingdisable(pin);
}

gpioD::gpioD(uint8_t pinnum, uint8_t dir, uint8_t cnfod)
{
	pin = pinnum;
	mode(dir, cnfod);
}

gpioD::gpioD(uint8_t pinnum)
{
	pin = pinnum;
}

gpioD::gpioD()
{
	static uint8_t pincount;
	pin = pincount;
	pincount++;
}

void gpioD::set()
{
	_GPIOD_(GPIOX_BSRR) = 1<<pin;
}

void gpioD::high()
{
	_GPIOD_(GPIOX_BSRR) = 1<<pin;
}

void gpioD::reset()
{
	_GPIOD_(GPIOX_BRR) = 1<<pin;
}


void gpioD::low()
{
	_GPIOD_(GPIOX_BRR) = 1<<pin;
}


void gpioD::invert()
{
	_GPIOD_(GPIOX_BSRR) = 1 << (pin + ((_GPIOD_(GPIOX_ODR)>>pin)&1)*16);
}

uint8_t gpioD::read()
{
	uint8_t val = (_GPIOD_(GPIOX_IDR) >> pin) & 1;
	return val;
}

void gpioD::write(uint8_t val)
{
	if (val) set(); else reset();
}

void gpioD::mode(uint8_t speed, uint8_t cnf)
{
	uint8_t pinpos = pin%8;
	uint8_t highlow = (pin<8) ? GPIOX_CRL:GPIOX_CRH;

	_GPIOD_(highlow) &= ~(0x0F << (pinpos*4));

	if (speed) _GPIOD_(highlow) |= (speed + cnf) << (pinpos*4);
	else
	{
		_GPIOD_(highlow) |= (cnf&0x0C) << (pinpos*4);
		_GPIOD_(GPIOX_ODR) |= (cnf&1) << pin;
	}
}


gpioE::gpioE(uint8_t pinnum, uint8_t dir, uint8_t cnfod)
{
	pin = pinnum;
	mode(dir, cnfod);
}

gpioE::gpioE(uint8_t pinnum)
{
	pin = pinnum;
}

gpioE::gpioE()
{
	static uint8_t pincount;
	pin = pincount;
	pincount++;
}

void gpioE::set()
{
	_GPIOE_(GPIOX_BSRR) = 1<<pin;
}

void gpioE::high()
{
	_GPIOE_(GPIOX_BSRR) = 1<<pin;
}

void gpioE::reset()
{
	_GPIOE_(GPIOX_BRR) = 1<<pin;
}


void gpioE::low()
{
	_GPIOE_(GPIOX_BRR) = 1<<pin;
}


void gpioE::invert()
{
	_GPIOE_(GPIOX_BSRR) = 1 << (pin + ((_GPIOE_(GPIOX_ODR)>>pin)&1)*16);
}

uint8_t gpioE::read()
{
	uint8_t val = (_GPIOE_(GPIOX_IDR) >> pin) & 1;
	return val;
}

void gpioE::write(uint8_t val)
{
	if (val) set(); else reset();
}

void gpioE::mode(uint8_t speed, uint8_t cnf)
{
	uint8_t pinpos = pin%8;
	uint8_t highlow = (pin<8) ? GPIOX_CRL:GPIOX_CRH;

	_GPIOE_(highlow) &= ~(0x0F << (pinpos*4));

	if (speed) _GPIOE_(highlow) |= (speed + cnf) << (pinpos*4);
	else
	{
		_GPIOE_(highlow) |= (cnf&0x0C) << (pinpos*4);
		_GPIOE_(GPIOX_ODR) |= (cnf&1) << pin;
	}
}

gpioF::gpioF(uint8_t pinnum, uint8_t dir, uint8_t cnfod)
{
	pin = pinnum;
	mode(dir, cnfod);
}

gpioF::gpioF(uint8_t pinnum)
{
	pin = pinnum;
}

gpioF::gpioF()
{
	static uint8_t pincount;
	pin = pincount;
	pincount++;
}

void gpioF::set()
{
	_GPIOF_(GPIOX_BSRR) = 1<<pin;
}

void gpioF::high()
{
	_GPIOF_(GPIOX_BSRR) = 1<<pin;
}

void gpioF::reset()
{
	_GPIOF_(GPIOX_BRR) = 1<<pin;
}


void gpioF::low()
{
	_GPIOF_(GPIOX_BRR) = 1<<pin;
}


void gpioF::invert()
{
	_GPIOF_(GPIOX_BSRR) = 1 << (pin + ((_GPIOF_(GPIOX_ODR)>>pin)&1)*16);
}

uint8_t gpioF::read()
{
	uint8_t val = (_GPIOF_(GPIOX_IDR) >> pin) & 1;
	return val;
}

void gpioF::write(uint8_t val)
{
	if (val) set(); else reset();
}

void gpioF::mode(uint8_t speed, uint8_t cnf)
{
	uint8_t pinpos = pin%8;
	uint8_t highlow = (pin<8) ? GPIOX_CRL:GPIOX_CRH;

	_GPIOF_(highlow) &= ~(0x0F << (pinpos*4));

	if (speed) _GPIOF_(highlow) |= (speed + cnf) << (pinpos*4);
	else
	{
		_GPIOF_(highlow) |= (cnf&0x0C) << (pinpos*4);
		_GPIOF_(GPIOX_ODR) |= (cnf&1) << pin;
	}
}

gpioG::gpioG(uint8_t pinnum, uint8_t dir, uint8_t cnfod)
{
	pin = pinnum;
	mode(dir, cnfod);
}

gpioG::gpioG(uint8_t pinnum)
{
	pin = pinnum;
}

gpioG::gpioG()
{
	static uint8_t pincount;
	pin = pincount;
	pincount++;
}

void gpioG::set()
{
	_GPIOG_(GPIOX_BSRR) = 1<<pin;
}

void gpioG::high()
{
	_GPIOG_(GPIOX_BSRR) = 1<<pin;
}

void gpioG::reset()
{
	_GPIOG_(GPIOX_BRR) = 1<<pin;
}


void gpioG::low()
{
	_GPIOG_(GPIOX_BRR) = 1<<pin;
}


void gpioG::invert()
{
	_GPIOG_(GPIOX_BSRR) = 1 << (pin + ((_GPIOG_(GPIOX_ODR)>>pin)&1)*16);
}

uint8_t gpioG::read()
{
	uint8_t val = (_GPIOG_(GPIOX_IDR) >> pin) & 1;
	return val;
}

void gpioG::write(uint8_t val)
{
	if (val) set(); else reset();
}

void gpioG::mode(uint8_t speed, uint8_t cnf)
{
	uint8_t pinpos = pin%8;
	uint8_t highlow = (pin<8) ? GPIOX_CRL:GPIOX_CRH;

	_GPIOG_(highlow) &= ~(0x0F << (pinpos*4));

	if (speed) _GPIOG_(highlow) |= (speed + cnf) << (pinpos*4);
	else
	{
		_GPIOG_(highlow) |= (cnf&0x0C) << (pinpos*4);
		_GPIOG_(GPIOX_ODR) |= (cnf&1) << pin;
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
