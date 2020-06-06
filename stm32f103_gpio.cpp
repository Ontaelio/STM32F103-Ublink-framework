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

void gpioA::init(gpio_config conf)
{
	gpioA_init();
	_GPIOA_(GPIOX_CRL) = conf.crl;
	_GPIOA_(GPIOX_CRH) = conf.crh;
	_GPIOA_(GPIOX_ODR) = conf.odr;
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

void gpioA::disablePins(uint16_t pins)
{
	uint32_t crl = 0;
	uint32_t crh = 0;
	uint8_t cnt = 0;
	while(pins)
	{
		crl |= (0xF * (pins&1)) << cnt;
		crh |= (0xF * ((pins>>8)&1)) << cnt;
		pins >>= 1;
		cnt+=4;
	}
	_GPIOA_(GPIOX_CRL) &= ~crl;
	_GPIOA_(GPIOX_CRH) &= ~crh;
}

gpio_config gpioA::saveConfig()
{
	gpio_config res;
	res.crl = _GPIOA_(GPIOX_CRL);
	res.crh = _GPIOA_(GPIOX_CRH);
	res.odr = _GPIOA_(GPIOX_ODR);
	return res;
}

void gpioA::setConfig(gpio_config conf)
{
	_GPIOA_(GPIOX_CRL) = conf.crl;
	_GPIOA_(GPIOX_CRH) = conf.crh;
	_GPIOA_(GPIOX_ODR) = conf.odr;
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

void gpioB::init(gpio_config conf)
{
	gpioB_init();
	_GPIOB_(GPIOX_CRL) = conf.crl;
	_GPIOB_(GPIOX_CRH) = conf.crh;
	_GPIOB_(GPIOX_ODR) = conf.odr;
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

void gpioB::disablePins(uint16_t pins)
{
	uint32_t crl = 0;
	uint32_t crh = 0;
	uint8_t cnt = 0;
	while(pins)
	{
		crl |= (0xF * (pins&1)) << cnt;
		crh |= (0xF * ((pins>>8)&1)) << cnt;
		pins >>= 1;
		cnt+=4;
	}
	_GPIOB_(GPIOX_CRL) &= ~crl;
	_GPIOB_(GPIOX_CRH) &= ~crh;
}

gpio_config gpioB::saveConfig()
{
	gpio_config res;
	res.crl = _GPIOB_(GPIOX_CRL);
	res.crh = _GPIOB_(GPIOX_CRH);
	res.odr = _GPIOB_(GPIOX_ODR);
	return res;
}

void gpioB::setConfig(gpio_config conf)
{
	_GPIOB_(GPIOX_CRL) = conf.crl;
	_GPIOB_(GPIOX_CRH) = conf.crh;
	_GPIOB_(GPIOX_ODR) = conf.odr;
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

void gpioC::init(gpio_config conf)
{
	gpioC_init();
	_GPIOC_(GPIOX_CRL) = conf.crl;
	_GPIOC_(GPIOX_CRH) = conf.crh;
	_GPIOC_(GPIOX_ODR) = conf.odr;
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

void gpioC::disablePins(uint16_t pins)
{
	uint32_t crl = 0;
	uint32_t crh = 0;
	uint8_t cnt = 0;
	while(pins)
	{
		crl |= (0xF * (pins&1)) << cnt;
		crh |= (0xF * ((pins>>8)&1)) << cnt;
		pins >>= 1;
		cnt+=4;
	}
	_GPIOC_(GPIOX_CRL) &= ~crl;
	_GPIOC_(GPIOX_CRH) &= ~crh;
}

gpio_config gpioC::saveConfig()
{
	gpio_config res;
	res.crl = _GPIOC_(GPIOX_CRL);
	res.crh = _GPIOC_(GPIOX_CRH);
	res.odr = _GPIOC_(GPIOX_ODR);
	return res;
}

void gpioC::setConfig(gpio_config conf)
{
	_GPIOC_(GPIOX_CRL) = conf.crl;
	_GPIOC_(GPIOX_CRH) = conf.crh;
	_GPIOC_(GPIOX_ODR) = conf.odr;
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

void gpioD::init(gpio_config conf)
{
	gpioD_init();
	_GPIOD_(GPIOX_CRL) = conf.crl;
	_GPIOD_(GPIOX_CRH) = conf.crh;
	_GPIOD_(GPIOX_ODR) = conf.odr;
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

void gpioD::disablePins(uint16_t pins)
{
	uint32_t crl = 0;
	uint32_t crh = 0;
	uint8_t cnt = 0;
	while(pins)
	{
		crl |= (0xF * (pins&1)) << cnt;
		crh |= (0xF * ((pins>>8)&1)) << cnt;
		pins >>= 1;
		cnt+=4;
	}
	_GPIOD_(GPIOX_CRL) &= ~crl;
	_GPIOD_(GPIOX_CRH) &= ~crh;
}

gpio_config gpioD::saveConfig()
{
	gpio_config res;
	res.crl = _GPIOD_(GPIOX_CRL);
	res.crh = _GPIOD_(GPIOX_CRH);
	res.odr = _GPIOD_(GPIOX_ODR);
	return res;
}

void gpioD::setConfig(gpio_config conf)
{
	_GPIOD_(GPIOX_CRL) = conf.crl;
	_GPIOD_(GPIOX_CRH) = conf.crh;
	_GPIOD_(GPIOX_ODR) = conf.odr;
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

void gpioE::init(gpio_config conf)
{
	gpioE_init();
	_GPIOE_(GPIOX_CRL) = conf.crl;
	_GPIOE_(GPIOX_CRH) = conf.crh;
	_GPIOE_(GPIOX_ODR) = conf.odr;
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

void gpioE::disablePins(uint16_t pins)
{
	uint32_t crl = 0;
	uint32_t crh = 0;
	uint8_t cnt = 0;
	while(pins)
	{
		crl |= (0xF * (pins&1)) << cnt;
		crh |= (0xF * ((pins>>8)&1)) << cnt;
		pins >>= 1;
		cnt+=4;
	}
	_GPIOE_(GPIOX_CRL) &= ~crl;
	_GPIOE_(GPIOX_CRH) &= ~crh;
}

gpio_config gpioE::saveConfig()
{
	gpio_config res;
	res.crl = _GPIOE_(GPIOX_CRL);
	res.crh = _GPIOE_(GPIOX_CRH);
	res.odr = _GPIOE_(GPIOX_ODR);
	return res;
}

void gpioE::setConfig(gpio_config conf)
{
	_GPIOE_(GPIOX_CRL) = conf.crl;
	_GPIOE_(GPIOX_CRH) = conf.crh;
	_GPIOE_(GPIOX_ODR) = conf.odr;
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

void gpioF::init(gpio_config conf)
{
	gpioF_init();
	_GPIOF_(GPIOX_CRL) = conf.crl;
	_GPIOF_(GPIOX_CRH) = conf.crh;
	_GPIOF_(GPIOX_ODR) = conf.odr;
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

void gpioF::disablePins(uint16_t pins)
{
	uint32_t crl = 0;
	uint32_t crh = 0;
	uint8_t cnt = 0;
	while(pins)
	{
		crl |= (0xF * (pins&1)) << cnt;
		crh |= (0xF * ((pins>>8)&1)) << cnt;
		pins >>= 1;
		cnt+=4;
	}
	_GPIOF_(GPIOX_CRL) &= ~crl;
	_GPIOF_(GPIOX_CRH) &= ~crh;
}

gpio_config gpioF::saveConfig()
{
	gpio_config res;
	res.crl = _GPIOF_(GPIOX_CRL);
	res.crh = _GPIOF_(GPIOX_CRH);
	res.odr = _GPIOF_(GPIOX_ODR);
	return res;
}

void gpioF::setConfig(gpio_config conf)
{
	_GPIOF_(GPIOX_CRL) = conf.crl;
	_GPIOF_(GPIOX_CRH) = conf.crh;
	_GPIOF_(GPIOX_ODR) = conf.odr;
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

void gpioG::init(gpio_config conf)
{
	gpioG_init();
	_GPIOG_(GPIOX_CRL) = conf.crl;
	_GPIOG_(GPIOX_CRH) = conf.crh;
	_GPIOG_(GPIOX_ODR) = conf.odr;
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

void gpioG::disablePins(uint16_t pins)
{
	uint32_t crl = 0;
	uint32_t crh = 0;
	uint8_t cnt = 0;
	while(pins)
	{
		crl |= (0xF * (pins&1)) << cnt;
		crh |= (0xF * ((pins>>8)&1)) << cnt;
		pins >>= 1;
		cnt+=4;
	}
	_GPIOG_(GPIOX_CRL) &= ~crl;
	_GPIOG_(GPIOX_CRH) &= ~crh;
}

gpio_config gpioG::saveConfig()
{
	gpio_config res;
	res.crl = _GPIOG_(GPIOX_CRL);
	res.crh = _GPIOG_(GPIOX_CRH);
	res.odr = _GPIOG_(GPIOX_ODR);
	return res;
}

void gpioG::setConfig(gpio_config conf)
{
	_GPIOG_(GPIOX_CRL) = conf.crl;
	_GPIOG_(GPIOX_CRH) = conf.crh;
	_GPIOG_(GPIOX_ODR) = conf.odr;
}
