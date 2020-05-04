/*
 * STM32F103 GPIO and AFIO functions library header
 * Part of STM32F103 register and peripherals library
 *
 * Dpcumentation available in the provided MD file.
 *
 * (c) 2019 Dmitry Reznikov ontaelio(at)gmail.com
 *
 * Can be freely used according to the GNU GPL license.
 */

#ifndef STM32F103_GPIO_H_
#define STM32F103_GPIO_H_

#include <stdio.h>
#include <stdint.h>
#include <stm32f103_gpio_reg.h>
#include <stm32f103_gpio_lowfunc.h>
#include <stm32f103_rcc_reg.h>

//MODEX
#define INPUT		 0
#define OUTPUT		 2
#define OUTPUT_2MHZ	 2
#define OUTPUT_10MHZ 1
#define OUTPUT_50MHZ 3

//CNF in OUTPUT mode
#define PUSHPULL	 0
#define OPENDRAIN	 4

//CNF + ODR in INPUT mode)
#define FLOATING	 4
#define PULLUP		 9
#define PULLDOWN	 8

class gpio_pin
{
public:
//	gpio_pin(uint8_t pinnum, uint8_t dir, uint8_t cnfod = 4);
//	gpio_pin(uint8_t pinnum);
//	gpio_pin();
	//virtual void init() =0;
	//virtual void set() =0;
	virtual void high() =0;
	//virtual void reset() =0;
	virtual void low() =0;
	//virtual void invert() =0;
	virtual uint8_t read() =0;
	virtual void write(uint8_t val) =0;
	virtual void mode(uint8_t speed, uint8_t cnf = 4) =0;
	uint8_t pin;
	//virtual void setAll(uint32_t BSRR_value) =0;
	//virtual void resetAll(uint32_t BRR_value) =0;
	//virtual uint32_t readAll() =0;
	//operator uint8_t() {return read();}
	//gpio_pin& operator= (const uint8_t& a) {write(a); return *this;}
};

class gpioA : public gpio_pin
{
public:
	gpioA(uint8_t pinnum, uint8_t dir, uint8_t cnfod = 4);
	gpioA(uint8_t pinnum);
	gpioA();
	void init()
	{
		_RCC_(RCC_APB2ENR) |= RCC_APB2ENR_IOPAEN;
	}
	void set();
	void high();
	void reset();
	void low();
	void invert();
	uint8_t read();
	void write(uint8_t val);
	void mode(uint8_t speed, uint8_t cnf = 4);
//	uint8_t pin;

	//these functions are to avoid compiler warnings

	void setAll(uint32_t BSRR_value)
	{
		_GPIOA_(GPIOX_BSRR) = BSRR_value;
	}
	void resetAll(uint32_t BRR_value)
	{
		_GPIOA_(GPIOX_BRR) = BRR_value;
	}
	uint32_t readAll()
	{
		return(_GPIOA_(GPIOX_IDR));
	}

	operator uint8_t() {return read();}
	gpioA& operator= (const uint8_t& a) {write(a); return *this;}

	// these below are better and work; but produce warnings from the compiler
	/*
	volatile uint32_t* BRR = (uint32_t*)  (0x40010814);
	volatile uint32_t* BSRR = (uint32_t*) (0x40010810);
	volatile uint32_t* IDR = (uint32_t*)  (0x40010808);
	*/
};

class gpioB : public gpio_pin
{
public:
	gpioB(uint8_t pinnum, uint8_t dir, uint8_t cnfod = 4);
	gpioB(uint8_t pinnum);
	gpioB();
	void init()
	{
		_RCC_(RCC_APB2ENR) |= RCC_APB2ENR_IOPBEN;
	}
	void set();
	void high();
	void reset();
	void low();
	void invert();
	uint8_t read();
	void write(uint8_t val);
	void mode(uint8_t speed, uint8_t cnf = 4);
	//uint8_t pin;
	void setAll(uint32_t BSRR_value)
	{
		_GPIOB_(GPIOX_BSRR) = BSRR_value;
	}
	void resetAll(uint32_t BRR_value)
	{
		_GPIOB_(GPIOX_BSRR) = BRR_value;
	}
	uint32_t readAll()
	{
		return(_GPIOB_(GPIOX_IDR));
	}

	operator uint8_t() {return (_GPIOB_(GPIOX_IDR) >> pin) & 1;} //read();}
	gpioB& operator= (const uint8_t& a) {write(a); return *this;}

	/*
	volatile uint32_t* BRR = (uint32_t*)  (0x40010C14);
	volatile uint32_t* BSRR = (uint32_t*) (0x40010C10);
	volatile uint32_t* IDR = (uint32_t*)  (0x40010C08);
	*/
};

class gpioC : public gpio_pin
{
public:
	gpioC(uint8_t pinnum, uint8_t dir, uint8_t cnfod = 4);
	gpioC(uint8_t pinnum);
	gpioC();
	void init()
	{
		_RCC_(RCC_APB2ENR) |= RCC_APB2ENR_IOPCEN;
	}
	void set();
	void high();
	void reset();
	void low();
	void invert();
	uint8_t read();
	void write(uint8_t val);
	void mode(uint8_t speed, uint8_t cnf = 4);
	//uint8_t pin;

	void setAll(uint32_t BSRR_value)
	{
		_GPIOC_(GPIOX_BSRR) = BSRR_value;
	}
	void resetAll(uint32_t BRR_value)
	{
		_GPIOC_(GPIOX_BSRR) = BRR_value;
	}
	uint32_t readAll()
	{
		return(_GPIOC_(GPIOX_IDR));
	}

	operator uint8_t() {return read();}
	gpioC& operator= (const uint8_t& a) {write(a); return *this;}

	/*
	volatile uint32_t* BRR = (uint32_t*)  (0x40011014);
	volatile uint32_t* BSRR = (uint32_t*) (0x40011010);
	volatile uint32_t* IDR = (uint32_t*)  (0x40011008);
	*/
};

class gpioD : public gpio_pin
{
public:
	gpioD(uint8_t pinnum, uint8_t dir, uint8_t cnfod = 4);
	gpioD(uint8_t pinnum);
	gpioD();
	void init()
	{
		_RCC_(RCC_APB2ENR) |= RCC_APB2ENR_IOPDEN;
	}
	void set();
	void high();
	void reset();
	void low();
	void invert();
	uint8_t read();
	void write(uint8_t val);
	void mode(uint8_t speed, uint8_t cnf = 4);
	//uint8_t pin;

	void setAll(uint32_t BSRR_value)
	{
		_GPIOD_(GPIOX_BSRR) = BSRR_value;
	}
	void resetAll(uint32_t BRR_value)
	{
		_GPIOD_(GPIOX_BSRR) = BRR_value;
	}
	uint32_t readAll()
	{
		return(_GPIOD_(GPIOX_IDR));
	}

	operator uint8_t() {return read();}
	gpioD& operator= (const uint8_t& a) {write(a); return *this;}

	/*
	volatile uint32_t* BRR = (uint32_t*)  (0x40011014);
	volatile uint32_t* BSRR = (uint32_t*) (0x40011010);
	volatile uint32_t* IDR = (uint32_t*)  (0x40011008);
	*/
};

class gpioE : public gpio_pin
{
public:
	gpioE(uint8_t pinnum, uint8_t dir, uint8_t cnfod = 4);
	gpioE(uint8_t pinnum);
	gpioE();
	void init()
	{
		_RCC_(RCC_APB2ENR) |= RCC_APB2ENR_IOPEEN;
	}
	void set();
	void high();
	void reset();
	void low();
	void invert();
	uint8_t read();
	void write(uint8_t val);
	void mode(uint8_t speed, uint8_t cnf = 4);
	//uint8_t pin;

	void setAll(uint32_t BSRR_value)
	{
		_GPIOE_(GPIOX_BSRR) = BSRR_value;
	}
	void resetAll(uint32_t BRR_value)
	{
		_GPIOE_(GPIOX_BSRR) = BRR_value;
	}
	uint32_t readAll()
	{
		return(_GPIOE_(GPIOX_IDR));
	}

	operator uint8_t() {return read();}
	gpioE& operator= (const uint8_t& a) {write(a); return *this;}

	/*
	volatile uint32_t* BRR = (uint32_t*)  (0x40011014);
	volatile uint32_t* BSRR = (uint32_t*) (0x40011010);
	volatile uint32_t* IDR = (uint32_t*)  (0x40011008);
	*/
};

class gpioF : public gpio_pin
{
public:
	gpioF(uint8_t pinnum, uint8_t dir, uint8_t cnfod = 4);
	gpioF(uint8_t pinnum);
	gpioF();
	void init()
	{
		_RCC_(RCC_APB2ENR) |= RCC_APB2ENR_IOPFEN;
	}
	void set();
	void high();
	void reset();
	void low();
	void invert();
	uint8_t read();
	void write(uint8_t val);
	void mode(uint8_t speed, uint8_t cnf = 4);
	//uint8_t pin;

	void setAll(uint32_t BSRR_value)
	{
		_GPIOF_(GPIOX_BSRR) = BSRR_value;
	}
	void resetAll(uint32_t BRR_value)
	{
		_GPIOF_(GPIOX_BSRR) = BRR_value;
	}
	uint32_t readAll()
	{
		return(_GPIOF_(GPIOX_IDR));
	}

	operator uint8_t() {return read();}
	gpioF& operator= (const uint8_t& a) {write(a); return *this;}

	/*
	volatile uint32_t* BRR = (uint32_t*)  (0x40011014);
	volatile uint32_t* BSRR = (uint32_t*) (0x40011010);
	volatile uint32_t* IDR = (uint32_t*)  (0x40011008);
	*/
};

class gpioG : public gpio_pin
{
public:
	gpioG(uint8_t pinnum, uint8_t dir, uint8_t cnfod = 4);
	gpioG(uint8_t pinnum);
	gpioG();
	void init()
	{
		_RCC_(RCC_APB2ENR) |= RCC_APB2ENR_IOPGEN;
	}
	void set();
	void high();
	void reset();
	void low();
	void invert();
	uint8_t read();
	void write(uint8_t val);
	void mode(uint8_t speed, uint8_t cnf = 4);
	//uint8_t pin;

	void setAll(uint32_t BSRR_value)
	{
		_GPIOG_(GPIOX_BSRR) = BSRR_value;
	}
	void resetAll(uint32_t BRR_value)
	{
		_GPIOG_(GPIOX_BSRR) = BRR_value;
	}
	uint32_t readAll()
	{
		return(_GPIOG_(GPIOX_IDR));
	}

	operator uint8_t() {return read();}
	gpioG& operator= (const uint8_t& a) {write(a); return *this;}

	/*
	volatile uint32_t* BRR = (uint32_t*)  (0x40011014);
	volatile uint32_t* BSRR = (uint32_t*) (0x40011010);
	volatile uint32_t* IDR = (uint32_t*)  (0x40011008);
	*/
};

typedef gpioA gpioA_pin;
typedef gpioB gpioB_pin;
typedef gpioC gpioC_pin;
typedef gpioD gpioD_pin;
typedef gpioE gpioE_pin;
typedef gpioF gpioF_pin;
typedef gpioG gpioG_pin;

inline void gpioA_init()
{
	_RCC_(RCC_APB2ENR) |= RCC_APB2ENR_IOPAEN;
}

inline void gpioB_init()
{
	_RCC_(RCC_APB2ENR) |= RCC_APB2ENR_IOPBEN;
}

inline void gpioC_init()
{
	_RCC_(RCC_APB2ENR) |= RCC_APB2ENR_IOPCEN;
}

inline void gpioD_init()
{
	_RCC_(RCC_APB2ENR) |= RCC_APB2ENR_IOPDEN;
}

inline void gpioE_init()
{
	_RCC_(RCC_APB2ENR) |= RCC_APB2ENR_IOPEEN;
}

inline void gpioF_init()
{
	_RCC_(RCC_APB2ENR) |= RCC_APB2ENR_IOPFEN;
}

inline void gpioG_init()
{
	_RCC_(RCC_APB2ENR) |= RCC_APB2ENR_IOPGEN;
}

inline void afio_init()
{
	_RCC_(RCC_APB2ENR) |= RCC_APB2ENR_AFIOEN;
}

inline void jtag_release()
{
	_AFIO_(AFIO_MAPR) |= 1<<25;
}


#endif /* STM32F103_GPIO_H_ */
