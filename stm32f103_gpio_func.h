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

#ifndef STM32F103_GPIO_FUNC_H_
#define STM32F103_GPIO_FUNC_H_

#include <stdio.h>
#include <stdint.h>
#include <stm32f103_gpio_reg.h>
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
	//virtual void write(uint8_t val) =0;
	virtual void mode(uint8_t speed, uint8_t cnf = 4) =0;
	uint8_t pin;
	//virtual void setAll(uint32_t BSRR_value) =0;
	//virtual void resetAll(uint32_t BRR_value) =0;
	//virtual uint32_t readAll() =0;
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

	operator uint8_t() {return read();}
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

inline void pinA0_Input()
{
_GPIOA_(GPIOX_CRL) &= ~((8+2+1)<<0);
_GPIOA_(GPIOX_CRL) |= (4)<<0;
}

inline void pinA0_Input_PU()
{
_GPIOA_(GPIOX_CRL) &= ~((4+2+1)<<0);
_GPIOA_(GPIOX_CRL) |= (8)<<0;
_GPIOA_(GPIOX_ODR) |= (1)<<0;
}

inline void pinA0_Input_PD()
{
_GPIOA_(GPIOX_CRL) &= ~((4+2+1)<<0);
_GPIOA_(GPIOX_CRL) |= (8)<<0;
_GPIOA_(GPIOX_ODR) &= ~(1<<0);
}

inline void pinA0_Analog()
{
_GPIOA_(GPIOX_CRL) &= ~((8+4+2+1)<<0);
}

inline void pinA0_Output()
{
_GPIOA_(GPIOX_CRL) &= ~((8+4+1)<<0);
_GPIOA_(GPIOX_CRL) |= (2)<<0;
}

inline void pinA0_Output_OD()
{
_GPIOA_(GPIOX_CRL) &= ~((8+1)<<0);
_GPIOA_(GPIOX_CRL) |= (2+4)<<0;
}

inline void pinA0_Output_PP_2()
{
_GPIOA_(GPIOX_CRL) &= ~((8+4+1)<<0);
_GPIOA_(GPIOX_CRL) |= (2)<<0;
}

inline void pinA0_Output_PP_10()
{
_GPIOA_(GPIOX_CRL) &= ~((8+4+2)<<0);
_GPIOA_(GPIOX_CRL) |= (1)<<0;
}

inline void pinA0_Output_PP_50()
{
_GPIOA_(GPIOX_CRL) &= ~((8+4)<<0);
_GPIOA_(GPIOX_CRL) |= (2+1)<<0;
}

inline void pinA0_Output_OD_2()
{
_GPIOA_(GPIOX_CRL) &= ~((8+1)<<0);
_GPIOA_(GPIOX_CRL) |= (2+4)<<0;
}

inline void pinA0_Output_OD_10()
{
_GPIOA_(GPIOX_CRL) &= ~((8+2)<<0);
_GPIOA_(GPIOX_CRL) |= (4+1)<<0;
}

inline void pinA0_Output_OD_50()
{
_GPIOA_(GPIOX_CRL) &= ~((8)<<0);
_GPIOA_(GPIOX_CRL) |= (4+2+1)<<0;
}

inline void pinA0_Output_AFPP_2()
{
_GPIOA_(GPIOX_CRL) &= ~((4+1)<<0);
_GPIOA_(GPIOX_CRL) |= (8+2)<<0;
}

inline void pinA0_Output_AFPP_10()
{
_GPIOA_(GPIOX_CRL) &= ~((4+2)<<0);
_GPIOA_(GPIOX_CRL) |= (8+1)<<0;
}

inline void pinA0_Output_AFPP_50()
{
_GPIOA_(GPIOX_CRL) &= ~((4)<<0);
_GPIOA_(GPIOX_CRL) |= (8+2+1)<<0;
}

inline void pinA0_Output_AFOD_2()
{
_GPIOA_(GPIOX_CRL) &= ~((1)<<0);
_GPIOA_(GPIOX_CRL) |= (8+2+4)<<0;
}

inline void pinA0_Output_AFOD_10()
{
_GPIOA_(GPIOX_CRL) &= ~((2)<<0);
_GPIOA_(GPIOX_CRL) |= (8+4+1)<<0;
}

inline void pinA0_Output_AFOD_50()
{
_GPIOA_(GPIOX_CRL) |= (8+4+2+1)<<0;
}

inline void pinA1_Input()
{
_GPIOA_(GPIOX_CRL) &= ~((8+2+1)<<4);
_GPIOA_(GPIOX_CRL) |= (4)<<4;
}

inline void pinA1_Input_PU()
{
_GPIOA_(GPIOX_CRL) &= ~((4+2+1)<<4);
_GPIOA_(GPIOX_CRL) |= (8)<<4;
_GPIOA_(GPIOX_ODR) |= (1)<<1;
}

inline void pinA1_Input_PD()
{
_GPIOA_(GPIOX_CRL) &= ~((4+2+1)<<4);
_GPIOA_(GPIOX_CRL) |= (8)<<4;
_GPIOA_(GPIOX_ODR) &= ~(1<<1);
}

inline void pinA1_Analog()
{
_GPIOA_(GPIOX_CRL) &= ~((8+4+2+1)<<4);
}

inline void pinA1_Output()
{
_GPIOA_(GPIOX_CRL) &= ~((8+4+1)<<4);
_GPIOA_(GPIOX_CRL) |= (2)<<4;
}

inline void pinA1_Output_OD()
{
_GPIOA_(GPIOX_CRL) &= ~((8+1)<<4);
_GPIOA_(GPIOX_CRL) |= (2+4)<<4;
}

inline void pinA1_Output_PP_2()
{
_GPIOA_(GPIOX_CRL) &= ~((8+4+1)<<4);
_GPIOA_(GPIOX_CRL) |= (2)<<4;
}

inline void pinA1_Output_PP_10()
{
_GPIOA_(GPIOX_CRL) &= ~((8+4+2)<<4);
_GPIOA_(GPIOX_CRL) |= (1)<<4;
}

inline void pinA1_Output_PP_50()
{
_GPIOA_(GPIOX_CRL) &= ~((8+4)<<4);
_GPIOA_(GPIOX_CRL) |= (2+1)<<4;
}

inline void pinA1_Output_OD_2()
{
_GPIOA_(GPIOX_CRL) &= ~((8+1)<<4);
_GPIOA_(GPIOX_CRL) |= (2+4)<<4;
}

inline void pinA1_Output_OD_10()
{
_GPIOA_(GPIOX_CRL) &= ~((8+2)<<4);
_GPIOA_(GPIOX_CRL) |= (4+1)<<4;
}

inline void pinA1_Output_OD_50()
{
_GPIOA_(GPIOX_CRL) &= ~((8)<<4);
_GPIOA_(GPIOX_CRL) |= (4+2+1)<<4;
}

inline void pinA1_Output_AFPP_2()
{
_GPIOA_(GPIOX_CRL) &= ~((4+1)<<4);
_GPIOA_(GPIOX_CRL) |= (8+2)<<4;
}

inline void pinA1_Output_AFPP_10()
{
_GPIOA_(GPIOX_CRL) &= ~((4+2)<<4);
_GPIOA_(GPIOX_CRL) |= (8+1)<<4;
}

inline void pinA1_Output_AFPP_50()
{
_GPIOA_(GPIOX_CRL) &= ~((4)<<4);
_GPIOA_(GPIOX_CRL) |= (8+2+1)<<4;
}

inline void pinA1_Output_AFOD_2()
{
_GPIOA_(GPIOX_CRL) &= ~((1)<<4);
_GPIOA_(GPIOX_CRL) |= (8+2+4)<<4;
}

inline void pinA1_Output_AFOD_10()
{
_GPIOA_(GPIOX_CRL) &= ~((2)<<4);
_GPIOA_(GPIOX_CRL) |= (8+4+1)<<4;
}

inline void pinA1_Output_AFOD_50()
{
_GPIOA_(GPIOX_CRL) |= (8+4+2+1)<<4;
}

inline void pinA2_Input()
{
_GPIOA_(GPIOX_CRL) &= ~((8+2+1)<<8);
_GPIOA_(GPIOX_CRL) |= (4)<<8;
}

inline void pinA2_Input_PU()
{
_GPIOA_(GPIOX_CRL) &= ~((4+2+1)<<8);
_GPIOA_(GPIOX_CRL) |= (8)<<8;
_GPIOA_(GPIOX_ODR) |= (1)<<2;
}

inline void pinA2_Input_PD()
{
_GPIOA_(GPIOX_CRL) &= ~((4+2+1)<<8);
_GPIOA_(GPIOX_CRL) |= (8)<<8;
_GPIOA_(GPIOX_ODR) &= ~(1<<2);
}

inline void pinA2_Analog()
{
_GPIOA_(GPIOX_CRL) &= ~((8+4+2+1)<<8);
}

inline void pinA2_Output()
{
_GPIOA_(GPIOX_CRL) &= ~((8+4+1)<<8);
_GPIOA_(GPIOX_CRL) |= (2)<<8;
}

inline void pinA2_Output_OD()
{
_GPIOA_(GPIOX_CRL) &= ~((8+1)<<8);
_GPIOA_(GPIOX_CRL) |= (2+4)<<8;
}

inline void pinA2_Output_PP_2()
{
_GPIOA_(GPIOX_CRL) &= ~((8+4+1)<<8);
_GPIOA_(GPIOX_CRL) |= (2)<<8;
}

inline void pinA2_Output_PP_10()
{
_GPIOA_(GPIOX_CRL) &= ~((8+4+2)<<8);
_GPIOA_(GPIOX_CRL) |= (1)<<8;
}

inline void pinA2_Output_PP_50()
{
_GPIOA_(GPIOX_CRL) &= ~((8+4)<<8);
_GPIOA_(GPIOX_CRL) |= (2+1)<<8;
}

inline void pinA2_Output_OD_2()
{
_GPIOA_(GPIOX_CRL) &= ~((8+1)<<8);
_GPIOA_(GPIOX_CRL) |= (2+4)<<8;
}

inline void pinA2_Output_OD_10()
{
_GPIOA_(GPIOX_CRL) &= ~((8+2)<<8);
_GPIOA_(GPIOX_CRL) |= (4+1)<<8;
}

inline void pinA2_Output_OD_50()
{
_GPIOA_(GPIOX_CRL) &= ~((8)<<8);
_GPIOA_(GPIOX_CRL) |= (4+2+1)<<8;
}

inline void pinA2_Output_AFPP_2()
{
_GPIOA_(GPIOX_CRL) &= ~((4+1)<<8);
_GPIOA_(GPIOX_CRL) |= (8+2)<<8;
}

inline void pinA2_Output_AFPP_10()
{
_GPIOA_(GPIOX_CRL) &= ~((4+2)<<8);
_GPIOA_(GPIOX_CRL) |= (8+1)<<8;
}

inline void pinA2_Output_AFPP_50()
{
_GPIOA_(GPIOX_CRL) &= ~((4)<<8);
_GPIOA_(GPIOX_CRL) |= (8+2+1)<<8;
}

inline void pinA2_Output_AFOD_2()
{
_GPIOA_(GPIOX_CRL) &= ~((1)<<8);
_GPIOA_(GPIOX_CRL) |= (8+2+4)<<8;
}

inline void pinA2_Output_AFOD_10()
{
_GPIOA_(GPIOX_CRL) &= ~((2)<<8);
_GPIOA_(GPIOX_CRL) |= (8+4+1)<<8;
}

inline void pinA2_Output_AFOD_50()
{
_GPIOA_(GPIOX_CRL) |= (8+4+2+1)<<8;
}

inline void pinA3_Input()
{
_GPIOA_(GPIOX_CRL) &= ~((8+2+1)<<12);
_GPIOA_(GPIOX_CRL) |= (4)<<12;
}

inline void pinA3_Input_PU()
{
_GPIOA_(GPIOX_CRL) &= ~((4+2+1)<<12);
_GPIOA_(GPIOX_CRL) |= (8)<<12;
_GPIOA_(GPIOX_ODR) |= (1)<<3;
}

inline void pinA3_Input_PD()
{
_GPIOA_(GPIOX_CRL) &= ~((4+2+1)<<12);
_GPIOA_(GPIOX_CRL) |= (8)<<12;
_GPIOA_(GPIOX_ODR) &= ~(1<<3);
}

inline void pinA3_Analog()
{
_GPIOA_(GPIOX_CRL) &= ~((8+4+2+1)<<12);
}

inline void pinA3_Output()
{
_GPIOA_(GPIOX_CRL) &= ~((8+4+1)<<12);
_GPIOA_(GPIOX_CRL) |= (2)<<12;
}

inline void pinA3_Output_OD()
{
_GPIOA_(GPIOX_CRL) &= ~((8+1)<<12);
_GPIOA_(GPIOX_CRL) |= (2+4)<<12;
}

inline void pinA3_Output_PP_2()
{
_GPIOA_(GPIOX_CRL) &= ~((8+4+1)<<12);
_GPIOA_(GPIOX_CRL) |= (2)<<12;
}

inline void pinA3_Output_PP_10()
{
_GPIOA_(GPIOX_CRL) &= ~((8+4+2)<<12);
_GPIOA_(GPIOX_CRL) |= (1)<<12;
}

inline void pinA3_Output_PP_50()
{
_GPIOA_(GPIOX_CRL) &= ~((8+4)<<12);
_GPIOA_(GPIOX_CRL) |= (2+1)<<12;
}

inline void pinA3_Output_OD_2()
{
_GPIOA_(GPIOX_CRL) &= ~((8+1)<<12);
_GPIOA_(GPIOX_CRL) |= (2+4)<<12;
}

inline void pinA3_Output_OD_10()
{
_GPIOA_(GPIOX_CRL) &= ~((8+2)<<12);
_GPIOA_(GPIOX_CRL) |= (4+1)<<12;
}

inline void pinA3_Output_OD_50()
{
_GPIOA_(GPIOX_CRL) &= ~((8)<<12);
_GPIOA_(GPIOX_CRL) |= (4+2+1)<<12;
}

inline void pinA3_Output_AFPP_2()
{
_GPIOA_(GPIOX_CRL) &= ~((4+1)<<12);
_GPIOA_(GPIOX_CRL) |= (8+2)<<12;
}

inline void pinA3_Output_AFPP_10()
{
_GPIOA_(GPIOX_CRL) &= ~((4+2)<<12);
_GPIOA_(GPIOX_CRL) |= (8+1)<<12;
}

inline void pinA3_Output_AFPP_50()
{
_GPIOA_(GPIOX_CRL) &= ~((4)<<12);
_GPIOA_(GPIOX_CRL) |= (8+2+1)<<12;
}

inline void pinA3_Output_AFOD_2()
{
_GPIOA_(GPIOX_CRL) &= ~((1)<<12);
_GPIOA_(GPIOX_CRL) |= (8+2+4)<<12;
}

inline void pinA3_Output_AFOD_10()
{
_GPIOA_(GPIOX_CRL) &= ~((2)<<12);
_GPIOA_(GPIOX_CRL) |= (8+4+1)<<12;
}

inline void pinA3_Output_AFOD_50()
{
_GPIOA_(GPIOX_CRL) |= (8+4+2+1)<<12;
}

inline void pinA4_Input()
{
_GPIOA_(GPIOX_CRL) &= ~((8+2+1)<<16);
_GPIOA_(GPIOX_CRL) |= (4)<<16;
}

inline void pinA4_Input_PU()
{
_GPIOA_(GPIOX_CRL) &= ~((4+2+1)<<16);
_GPIOA_(GPIOX_CRL) |= (8)<<16;
_GPIOA_(GPIOX_ODR) |= (1)<<4;
}

inline void pinA4_Input_PD()
{
_GPIOA_(GPIOX_CRL) &= ~((4+2+1)<<16);
_GPIOA_(GPIOX_CRL) |= (8)<<16;
_GPIOA_(GPIOX_ODR) &= ~(1<<4);
}

inline void pinA4_Analog()
{
_GPIOA_(GPIOX_CRL) &= ~((8+4+2+1)<<16);
}

inline void pinA4_Output()
{
_GPIOA_(GPIOX_CRL) &= ~((8+4+1)<<16);
_GPIOA_(GPIOX_CRL) |= (2)<<16;
}

inline void pinA4_Output_OD()
{
_GPIOA_(GPIOX_CRL) &= ~((8+1)<<16);
_GPIOA_(GPIOX_CRL) |= (2+4)<<16;
}

inline void pinA4_Output_PP_2()
{
_GPIOA_(GPIOX_CRL) &= ~((8+4+1)<<16);
_GPIOA_(GPIOX_CRL) |= (2)<<16;
}

inline void pinA4_Output_PP_10()
{
_GPIOA_(GPIOX_CRL) &= ~((8+4+2)<<16);
_GPIOA_(GPIOX_CRL) |= (1)<<16;
}

inline void pinA4_Output_PP_50()
{
_GPIOA_(GPIOX_CRL) &= ~((8+4)<<16);
_GPIOA_(GPIOX_CRL) |= (2+1)<<16;
}

inline void pinA4_Output_OD_2()
{
_GPIOA_(GPIOX_CRL) &= ~((8+1)<<16);
_GPIOA_(GPIOX_CRL) |= (2+4)<<16;
}

inline void pinA4_Output_OD_10()
{
_GPIOA_(GPIOX_CRL) &= ~((8+2)<<16);
_GPIOA_(GPIOX_CRL) |= (4+1)<<16;
}

inline void pinA4_Output_OD_50()
{
_GPIOA_(GPIOX_CRL) &= ~((8)<<16);
_GPIOA_(GPIOX_CRL) |= (4+2+1)<<16;
}

inline void pinA4_Output_AFPP_2()
{
_GPIOA_(GPIOX_CRL) &= ~((4+1)<<16);
_GPIOA_(GPIOX_CRL) |= (8+2)<<16;
}

inline void pinA4_Output_AFPP_10()
{
_GPIOA_(GPIOX_CRL) &= ~((4+2)<<16);
_GPIOA_(GPIOX_CRL) |= (8+1)<<16;
}

inline void pinA4_Output_AFPP_50()
{
_GPIOA_(GPIOX_CRL) &= ~((4)<<16);
_GPIOA_(GPIOX_CRL) |= (8+2+1)<<16;
}

inline void pinA4_Output_AFOD_2()
{
_GPIOA_(GPIOX_CRL) &= ~((1)<<16);
_GPIOA_(GPIOX_CRL) |= (8+2+4)<<16;
}

inline void pinA4_Output_AFOD_10()
{
_GPIOA_(GPIOX_CRL) &= ~((2)<<16);
_GPIOA_(GPIOX_CRL) |= (8+4+1)<<16;
}

inline void pinA4_Output_AFOD_50()
{
_GPIOA_(GPIOX_CRL) |= (8+4+2+1)<<16;
}

inline void pinA5_Input()
{
_GPIOA_(GPIOX_CRL) &= ~((8+2+1)<<20);
_GPIOA_(GPIOX_CRL) |= (4)<<20;
}

inline void pinA5_Input_PU()
{
_GPIOA_(GPIOX_CRL) &= ~((4+2+1)<<20);
_GPIOA_(GPIOX_CRL) |= (8)<<20;
_GPIOA_(GPIOX_ODR) |= (1)<<5;
}

inline void pinA5_Input_PD()
{
_GPIOA_(GPIOX_CRL) &= ~((4+2+1)<<20);
_GPIOA_(GPIOX_CRL) |= (8)<<20;
_GPIOA_(GPIOX_ODR) &= ~(1<<5);
}

inline void pinA5_Analog()
{
_GPIOA_(GPIOX_CRL) &= ~((8+4+2+1)<<20);
}

inline void pinA5_Output()
{
_GPIOA_(GPIOX_CRL) &= ~((8+4+1)<<20);
_GPIOA_(GPIOX_CRL) |= (2)<<20;
}

inline void pinA5_Output_OD()
{
_GPIOA_(GPIOX_CRL) &= ~((8+1)<<20);
_GPIOA_(GPIOX_CRL) |= (2+4)<<20;
}

inline void pinA5_Output_PP_2()
{
_GPIOA_(GPIOX_CRL) &= ~((8+4+1)<<20);
_GPIOA_(GPIOX_CRL) |= (2)<<20;
}

inline void pinA5_Output_PP_10()
{
_GPIOA_(GPIOX_CRL) &= ~((8+4+2)<<20);
_GPIOA_(GPIOX_CRL) |= (1)<<20;
}

inline void pinA5_Output_PP_50()
{
_GPIOA_(GPIOX_CRL) &= ~((8+4)<<20);
_GPIOA_(GPIOX_CRL) |= (2+1)<<20;
}

inline void pinA5_Output_OD_2()
{
_GPIOA_(GPIOX_CRL) &= ~((8+1)<<20);
_GPIOA_(GPIOX_CRL) |= (2+4)<<20;
}

inline void pinA5_Output_OD_10()
{
_GPIOA_(GPIOX_CRL) &= ~((8+2)<<20);
_GPIOA_(GPIOX_CRL) |= (4+1)<<20;
}

inline void pinA5_Output_OD_50()
{
_GPIOA_(GPIOX_CRL) &= ~((8)<<20);
_GPIOA_(GPIOX_CRL) |= (4+2+1)<<20;
}

inline void pinA5_Output_AFPP_2()
{
_GPIOA_(GPIOX_CRL) &= ~((4+1)<<20);
_GPIOA_(GPIOX_CRL) |= (8+2)<<20;
}

inline void pinA5_Output_AFPP_10()
{
_GPIOA_(GPIOX_CRL) &= ~((4+2)<<20);
_GPIOA_(GPIOX_CRL) |= (8+1)<<20;
}

inline void pinA5_Output_AFPP_50()
{
_GPIOA_(GPIOX_CRL) &= ~((4)<<20);
_GPIOA_(GPIOX_CRL) |= (8+2+1)<<20;
}

inline void pinA5_Output_AFOD_2()
{
_GPIOA_(GPIOX_CRL) &= ~((1)<<20);
_GPIOA_(GPIOX_CRL) |= (8+2+4)<<20;
}

inline void pinA5_Output_AFOD_10()
{
_GPIOA_(GPIOX_CRL) &= ~((2)<<20);
_GPIOA_(GPIOX_CRL) |= (8+4+1)<<20;
}

inline void pinA5_Output_AFOD_50()
{
_GPIOA_(GPIOX_CRL) |= (8+4+2+1)<<20;
}

inline void pinA6_Input()
{
_GPIOA_(GPIOX_CRL) &= ~((8+2+1)<<24);
_GPIOA_(GPIOX_CRL) |= (4)<<24;
}

inline void pinA6_Input_PU()
{
_GPIOA_(GPIOX_CRL) &= ~((4+2+1)<<24);
_GPIOA_(GPIOX_CRL) |= (8)<<24;
_GPIOA_(GPIOX_ODR) |= (1)<<6;
}

inline void pinA6_Input_PD()
{
_GPIOA_(GPIOX_CRL) &= ~((4+2+1)<<24);
_GPIOA_(GPIOX_CRL) |= (8)<<24;
_GPIOA_(GPIOX_ODR) &= ~(1<<6);
}

inline void pinA6_Analog()
{
_GPIOA_(GPIOX_CRL) &= ~((8+4+2+1)<<24);
}

inline void pinA6_Output()
{
_GPIOA_(GPIOX_CRL) &= ~((8+4+1)<<24);
_GPIOA_(GPIOX_CRL) |= (2)<<24;
}

inline void pinA6_Output_OD()
{
_GPIOA_(GPIOX_CRL) &= ~((8+1)<<24);
_GPIOA_(GPIOX_CRL) |= (2+4)<<24;
}

inline void pinA6_Output_PP_2()
{
_GPIOA_(GPIOX_CRL) &= ~((8+4+1)<<24);
_GPIOA_(GPIOX_CRL) |= (2)<<24;
}

inline void pinA6_Output_PP_10()
{
_GPIOA_(GPIOX_CRL) &= ~((8+4+2)<<24);
_GPIOA_(GPIOX_CRL) |= (1)<<24;
}

inline void pinA6_Output_PP_50()
{
_GPIOA_(GPIOX_CRL) &= ~((8+4)<<24);
_GPIOA_(GPIOX_CRL) |= (2+1)<<24;
}

inline void pinA6_Output_OD_2()
{
_GPIOA_(GPIOX_CRL) &= ~((8+1)<<24);
_GPIOA_(GPIOX_CRL) |= (2+4)<<24;
}

inline void pinA6_Output_OD_10()
{
_GPIOA_(GPIOX_CRL) &= ~((8+2)<<24);
_GPIOA_(GPIOX_CRL) |= (4+1)<<24;
}

inline void pinA6_Output_OD_50()
{
_GPIOA_(GPIOX_CRL) &= ~((8)<<24);
_GPIOA_(GPIOX_CRL) |= (4+2+1)<<24;
}

inline void pinA6_Output_AFPP_2()
{
_GPIOA_(GPIOX_CRL) &= ~((4+1)<<24);
_GPIOA_(GPIOX_CRL) |= (8+2)<<24;
}

inline void pinA6_Output_AFPP_10()
{
_GPIOA_(GPIOX_CRL) &= ~((4+2)<<24);
_GPIOA_(GPIOX_CRL) |= (8+1)<<24;
}

inline void pinA6_Output_AFPP_50()
{
_GPIOA_(GPIOX_CRL) &= ~((4)<<24);
_GPIOA_(GPIOX_CRL) |= (8+2+1)<<24;
}

inline void pinA6_Output_AFOD_2()
{
_GPIOA_(GPIOX_CRL) &= ~((1)<<24);
_GPIOA_(GPIOX_CRL) |= (8+2+4)<<24;
}

inline void pinA6_Output_AFOD_10()
{
_GPIOA_(GPIOX_CRL) &= ~((2)<<24);
_GPIOA_(GPIOX_CRL) |= (8+4+1)<<24;
}

inline void pinA6_Output_AFOD_50()
{
_GPIOA_(GPIOX_CRL) |= (8+4+2+1)<<24;
}

inline void pinA7_Input()
{
_GPIOA_(GPIOX_CRL) &= ~((8+2+1)<<28);
_GPIOA_(GPIOX_CRL) |= (4)<<28;
}

inline void pinA7_Input_PU()
{
_GPIOA_(GPIOX_CRL) &= ~((4+2+1)<<28);
_GPIOA_(GPIOX_CRL) |= (8)<<28;
_GPIOA_(GPIOX_ODR) |= (1)<<7;
}

inline void pinA7_Input_PD()
{
_GPIOA_(GPIOX_CRL) &= ~((4+2+1)<<28);
_GPIOA_(GPIOX_CRL) |= (8)<<28;
_GPIOA_(GPIOX_ODR) &= ~(1<<7);
}

inline void pinA7_Analog()
{
_GPIOA_(GPIOX_CRL) &= ~((8+4+2+1)<<28);
}

inline void pinA7_Output()
{
_GPIOA_(GPIOX_CRL) &= ~((8+4+1)<<28);
_GPIOA_(GPIOX_CRL) |= (2)<<28;
}

inline void pinA7_Output_OD()
{
_GPIOA_(GPIOX_CRL) &= ~((8+1)<<28);
_GPIOA_(GPIOX_CRL) |= (2+4)<<28;
}

inline void pinA7_Output_PP_2()
{
_GPIOA_(GPIOX_CRL) &= ~((8+4+1)<<28);
_GPIOA_(GPIOX_CRL) |= (2)<<28;
}

inline void pinA7_Output_PP_10()
{
_GPIOA_(GPIOX_CRL) &= ~((8+4+2)<<28);
_GPIOA_(GPIOX_CRL) |= (1)<<28;
}

inline void pinA7_Output_PP_50()
{
_GPIOA_(GPIOX_CRL) &= ~((8+4)<<28);
_GPIOA_(GPIOX_CRL) |= (2+1)<<28;
}

inline void pinA7_Output_OD_2()
{
_GPIOA_(GPIOX_CRL) &= ~((8+1)<<28);
_GPIOA_(GPIOX_CRL) |= (2+4)<<28;
}

inline void pinA7_Output_OD_10()
{
_GPIOA_(GPIOX_CRL) &= ~((8+2)<<28);
_GPIOA_(GPIOX_CRL) |= (4+1)<<28;
}

inline void pinA7_Output_OD_50()
{
_GPIOA_(GPIOX_CRL) &= ~((8)<<28);
_GPIOA_(GPIOX_CRL) |= (4+2+1)<<28;
}

inline void pinA7_Output_AFPP_2()
{
_GPIOA_(GPIOX_CRL) &= ~((4+1)<<28);
_GPIOA_(GPIOX_CRL) |= (8+2)<<28;
}

inline void pinA7_Output_AFPP_10()
{
_GPIOA_(GPIOX_CRL) &= ~((4+2)<<28);
_GPIOA_(GPIOX_CRL) |= (8+1)<<28;
}

inline void pinA7_Output_AFPP_50()
{
_GPIOA_(GPIOX_CRL) &= ~((4)<<28);
_GPIOA_(GPIOX_CRL) |= (8+2+1)<<28;
}

inline void pinA7_Output_AFOD_2()
{
_GPIOA_(GPIOX_CRL) &= ~((1)<<28);
_GPIOA_(GPIOX_CRL) |= (8+2+4)<<28;
}

inline void pinA7_Output_AFOD_10()
{
_GPIOA_(GPIOX_CRL) &= ~((2)<<28);
_GPIOA_(GPIOX_CRL) |= (8+4+1)<<28;
}

inline void pinA7_Output_AFOD_50()
{
_GPIOA_(GPIOX_CRL) |= (8+4+2+1)<<28;
}

inline void pinA8_Input()
{
_GPIOA_(GPIOX_CRH) &= ~((8+2+1)<<0);
_GPIOA_(GPIOX_CRH) |= (4)<<0;
}

inline void pinA8_Input_PU()
{
_GPIOA_(GPIOX_CRH) &= ~((4+2+1)<<0);
_GPIOA_(GPIOX_CRH) |= (8)<<0;
_GPIOA_(GPIOX_ODR) |= (1)<<8;
}

inline void pinA8_Input_PD()
{
_GPIOA_(GPIOX_CRH) &= ~((4+2+1)<<0);
_GPIOA_(GPIOX_CRH) |= (8)<<0;
_GPIOA_(GPIOX_ODR) &= ~(1<<8);
}

inline void pinA8_Analog()
{
_GPIOA_(GPIOX_CRH) &= ~((8+4+2+1)<<0);
}

inline void pinA8_Output()
{
_GPIOA_(GPIOX_CRH) &= ~((8+4+1)<<0);
_GPIOA_(GPIOX_CRH) |= (2)<<0;
}

inline void pinA8_Output_OD()
{
_GPIOA_(GPIOX_CRH) &= ~((8+1)<<0);
_GPIOA_(GPIOX_CRH) |= (2+4)<<0;
}

inline void pinA8_Output_PP_2()
{
_GPIOA_(GPIOX_CRH) &= ~((8+4+1)<<0);
_GPIOA_(GPIOX_CRH) |= (2)<<0;
}

inline void pinA8_Output_PP_10()
{
_GPIOA_(GPIOX_CRH) &= ~((8+4+2)<<0);
_GPIOA_(GPIOX_CRH) |= (1)<<0;
}

inline void pinA8_Output_PP_50()
{
_GPIOA_(GPIOX_CRH) &= ~((8+4)<<0);
_GPIOA_(GPIOX_CRH) |= (2+1)<<0;
}

inline void pinA8_Output_OD_2()
{
_GPIOA_(GPIOX_CRH) &= ~((8+1)<<0);
_GPIOA_(GPIOX_CRH) |= (2+4)<<0;
}

inline void pinA8_Output_OD_10()
{
_GPIOA_(GPIOX_CRH) &= ~((8+2)<<0);
_GPIOA_(GPIOX_CRH) |= (4+1)<<0;
}

inline void pinA8_Output_OD_50()
{
_GPIOA_(GPIOX_CRH) &= ~((8)<<0);
_GPIOA_(GPIOX_CRH) |= (4+2+1)<<0;
}

inline void pinA8_Output_AFPP_2()
{
_GPIOA_(GPIOX_CRH) &= ~((4+1)<<0);
_GPIOA_(GPIOX_CRH) |= (8+2)<<0;
}

inline void pinA8_Output_AFPP_10()
{
_GPIOA_(GPIOX_CRH) &= ~((4+2)<<0);
_GPIOA_(GPIOX_CRH) |= (8+1)<<0;
}

inline void pinA8_Output_AFPP_50()
{
_GPIOA_(GPIOX_CRH) &= ~((4)<<0);
_GPIOA_(GPIOX_CRH) |= (8+2+1)<<0;
}

inline void pinA8_Output_AFOD_2()
{
_GPIOA_(GPIOX_CRH) &= ~((1)<<0);
_GPIOA_(GPIOX_CRH) |= (8+2+4)<<0;
}

inline void pinA8_Output_AFOD_10()
{
_GPIOA_(GPIOX_CRH) &= ~((2)<<0);
_GPIOA_(GPIOX_CRH) |= (8+4+1)<<0;
}

inline void pinA8_Output_AFOD_50()
{
_GPIOA_(GPIOX_CRH) |= (8+4+2+1)<<0;
}

inline void pinA9_Input()
{
_GPIOA_(GPIOX_CRH) &= ~((8+2+1)<<4);
_GPIOA_(GPIOX_CRH) |= (4)<<4;
}

inline void pinA9_Input_PU()
{
_GPIOA_(GPIOX_CRH) &= ~((4+2+1)<<4);
_GPIOA_(GPIOX_CRH) |= (8)<<4;
_GPIOA_(GPIOX_ODR) |= (1)<<9;
}

inline void pinA9_Input_PD()
{
_GPIOA_(GPIOX_CRH) &= ~((4+2+1)<<4);
_GPIOA_(GPIOX_CRH) |= (8)<<4;
_GPIOA_(GPIOX_ODR) &= ~(1<<9);
}

inline void pinA9_Analog()
{
_GPIOA_(GPIOX_CRH) &= ~((8+4+2+1)<<4);
}

inline void pinA9_Output()
{
_GPIOA_(GPIOX_CRH) &= ~((8+4+1)<<4);
_GPIOA_(GPIOX_CRH) |= (2)<<4;
}

inline void pinA9_Output_OD()
{
_GPIOA_(GPIOX_CRH) &= ~((8+1)<<4);
_GPIOA_(GPIOX_CRH) |= (2+4)<<4;
}

inline void pinA9_Output_PP_2()
{
_GPIOA_(GPIOX_CRH) &= ~((8+4+1)<<4);
_GPIOA_(GPIOX_CRH) |= (2)<<4;
}

inline void pinA9_Output_PP_10()
{
_GPIOA_(GPIOX_CRH) &= ~((8+4+2)<<4);
_GPIOA_(GPIOX_CRH) |= (1)<<4;
}

inline void pinA9_Output_PP_50()
{
_GPIOA_(GPIOX_CRH) &= ~((8+4)<<4);
_GPIOA_(GPIOX_CRH) |= (2+1)<<4;
}

inline void pinA9_Output_OD_2()
{
_GPIOA_(GPIOX_CRH) &= ~((8+1)<<4);
_GPIOA_(GPIOX_CRH) |= (2+4)<<4;
}

inline void pinA9_Output_OD_10()
{
_GPIOA_(GPIOX_CRH) &= ~((8+2)<<4);
_GPIOA_(GPIOX_CRH) |= (4+1)<<4;
}

inline void pinA9_Output_OD_50()
{
_GPIOA_(GPIOX_CRH) &= ~((8)<<4);
_GPIOA_(GPIOX_CRH) |= (4+2+1)<<4;
}

inline void pinA9_Output_AFPP_2()
{
_GPIOA_(GPIOX_CRH) &= ~((4+1)<<4);
_GPIOA_(GPIOX_CRH) |= (8+2)<<4;
}

inline void pinA9_Output_AFPP_10()
{
_GPIOA_(GPIOX_CRH) &= ~((4+2)<<4);
_GPIOA_(GPIOX_CRH) |= (8+1)<<4;
}

inline void pinA9_Output_AFPP_50()
{
_GPIOA_(GPIOX_CRH) &= ~((4)<<4);
_GPIOA_(GPIOX_CRH) |= (8+2+1)<<4;
}

inline void pinA9_Output_AFOD_2()
{
_GPIOA_(GPIOX_CRH) &= ~((1)<<4);
_GPIOA_(GPIOX_CRH) |= (8+2+4)<<4;
}

inline void pinA9_Output_AFOD_10()
{
_GPIOA_(GPIOX_CRH) &= ~((2)<<4);
_GPIOA_(GPIOX_CRH) |= (8+4+1)<<4;
}

inline void pinA9_Output_AFOD_50()
{
_GPIOA_(GPIOX_CRH) |= (8+4+2+1)<<4;
}

inline void pinA10_Input()
{
_GPIOA_(GPIOX_CRH) &= ~((8+2+1)<<8);
_GPIOA_(GPIOX_CRH) |= (4)<<8;
}

inline void pinA10_Input_PU()
{
_GPIOA_(GPIOX_CRH) &= ~((4+2+1)<<8);
_GPIOA_(GPIOX_CRH) |= (8)<<8;
_GPIOA_(GPIOX_ODR) |= (1)<<10;
}

inline void pinA10_Input_PD()
{
_GPIOA_(GPIOX_CRH) &= ~((4+2+1)<<8);
_GPIOA_(GPIOX_CRH) |= (8)<<8;
_GPIOA_(GPIOX_ODR) &= ~(1<<10);
}

inline void pinA10_Analog()
{
_GPIOA_(GPIOX_CRH) &= ~((8+4+2+1)<<8);
}

inline void pinA10_Output()
{
_GPIOA_(GPIOX_CRH) &= ~((8+4+1)<<8);
_GPIOA_(GPIOX_CRH) |= (2)<<8;
}

inline void pinA10_Output_OD()
{
_GPIOA_(GPIOX_CRH) &= ~((8+1)<<8);
_GPIOA_(GPIOX_CRH) |= (2+4)<<8;
}

inline void pinA10_Output_PP_2()
{
_GPIOA_(GPIOX_CRH) &= ~((8+4+1)<<8);
_GPIOA_(GPIOX_CRH) |= (2)<<8;
}

inline void pinA10_Output_PP_10()
{
_GPIOA_(GPIOX_CRH) &= ~((8+4+2)<<8);
_GPIOA_(GPIOX_CRH) |= (1)<<8;
}

inline void pinA10_Output_PP_50()
{
_GPIOA_(GPIOX_CRH) &= ~((8+4)<<8);
_GPIOA_(GPIOX_CRH) |= (2+1)<<8;
}

inline void pinA10_Output_OD_2()
{
_GPIOA_(GPIOX_CRH) &= ~((8+1)<<8);
_GPIOA_(GPIOX_CRH) |= (2+4)<<8;
}

inline void pinA10_Output_OD_10()
{
_GPIOA_(GPIOX_CRH) &= ~((8+2)<<8);
_GPIOA_(GPIOX_CRH) |= (4+1)<<8;
}

inline void pinA10_Output_OD_50()
{
_GPIOA_(GPIOX_CRH) &= ~((8)<<8);
_GPIOA_(GPIOX_CRH) |= (4+2+1)<<8;
}

inline void pinA10_Output_AFPP_2()
{
_GPIOA_(GPIOX_CRH) &= ~((4+1)<<8);
_GPIOA_(GPIOX_CRH) |= (8+2)<<8;
}

inline void pinA10_Output_AFPP_10()
{
_GPIOA_(GPIOX_CRH) &= ~((4+2)<<8);
_GPIOA_(GPIOX_CRH) |= (8+1)<<8;
}

inline void pinA10_Output_AFPP_50()
{
_GPIOA_(GPIOX_CRH) &= ~((4)<<8);
_GPIOA_(GPIOX_CRH) |= (8+2+1)<<8;
}

inline void pinA10_Output_AFOD_2()
{
_GPIOA_(GPIOX_CRH) &= ~((1)<<8);
_GPIOA_(GPIOX_CRH) |= (8+2+4)<<8;
}

inline void pinA10_Output_AFOD_10()
{
_GPIOA_(GPIOX_CRH) &= ~((2)<<8);
_GPIOA_(GPIOX_CRH) |= (8+4+1)<<8;
}

inline void pinA10_Output_AFOD_50()
{
_GPIOA_(GPIOX_CRH) |= (8+4+2+1)<<8;
}

inline void pinA11_Input()
{
_GPIOA_(GPIOX_CRH) &= ~((8+2+1)<<12);
_GPIOA_(GPIOX_CRH) |= (4)<<12;
}

inline void pinA11_Input_PU()
{
_GPIOA_(GPIOX_CRH) &= ~((4+2+1)<<12);
_GPIOA_(GPIOX_CRH) |= (8)<<12;
_GPIOA_(GPIOX_ODR) |= (1)<<11;
}

inline void pinA11_Input_PD()
{
_GPIOA_(GPIOX_CRH) &= ~((4+2+1)<<12);
_GPIOA_(GPIOX_CRH) |= (8)<<12;
_GPIOA_(GPIOX_ODR) &= ~(1<<11);
}

inline void pinA11_Analog()
{
_GPIOA_(GPIOX_CRH) &= ~((8+4+2+1)<<12);
}

inline void pinA11_Output()
{
_GPIOA_(GPIOX_CRH) &= ~((8+4+1)<<12);
_GPIOA_(GPIOX_CRH) |= (2)<<12;
}

inline void pinA11_Output_OD()
{
_GPIOA_(GPIOX_CRH) &= ~((8+1)<<12);
_GPIOA_(GPIOX_CRH) |= (2+4)<<12;
}

inline void pinA11_Output_PP_2()
{
_GPIOA_(GPIOX_CRH) &= ~((8+4+1)<<12);
_GPIOA_(GPIOX_CRH) |= (2)<<12;
}

inline void pinA11_Output_PP_10()
{
_GPIOA_(GPIOX_CRH) &= ~((8+4+2)<<12);
_GPIOA_(GPIOX_CRH) |= (1)<<12;
}

inline void pinA11_Output_PP_50()
{
_GPIOA_(GPIOX_CRH) &= ~((8+4)<<12);
_GPIOA_(GPIOX_CRH) |= (2+1)<<12;
}

inline void pinA11_Output_OD_2()
{
_GPIOA_(GPIOX_CRH) &= ~((8+1)<<12);
_GPIOA_(GPIOX_CRH) |= (2+4)<<12;
}

inline void pinA11_Output_OD_10()
{
_GPIOA_(GPIOX_CRH) &= ~((8+2)<<12);
_GPIOA_(GPIOX_CRH) |= (4+1)<<12;
}

inline void pinA11_Output_OD_50()
{
_GPIOA_(GPIOX_CRH) &= ~((8)<<12);
_GPIOA_(GPIOX_CRH) |= (4+2+1)<<12;
}

inline void pinA11_Output_AFPP_2()
{
_GPIOA_(GPIOX_CRH) &= ~((4+1)<<12);
_GPIOA_(GPIOX_CRH) |= (8+2)<<12;
}

inline void pinA11_Output_AFPP_10()
{
_GPIOA_(GPIOX_CRH) &= ~((4+2)<<12);
_GPIOA_(GPIOX_CRH) |= (8+1)<<12;
}

inline void pinA11_Output_AFPP_50()
{
_GPIOA_(GPIOX_CRH) &= ~((4)<<12);
_GPIOA_(GPIOX_CRH) |= (8+2+1)<<12;
}

inline void pinA11_Output_AFOD_2()
{
_GPIOA_(GPIOX_CRH) &= ~((1)<<12);
_GPIOA_(GPIOX_CRH) |= (8+2+4)<<12;
}

inline void pinA11_Output_AFOD_10()
{
_GPIOA_(GPIOX_CRH) &= ~((2)<<12);
_GPIOA_(GPIOX_CRH) |= (8+4+1)<<12;
}

inline void pinA11_Output_AFOD_50()
{
_GPIOA_(GPIOX_CRH) |= (8+4+2+1)<<12;
}

inline void pinA12_Input()
{
_GPIOA_(GPIOX_CRH) &= ~((8+2+1)<<16);
_GPIOA_(GPIOX_CRH) |= (4)<<16;
}

inline void pinA12_Input_PU()
{
_GPIOA_(GPIOX_CRH) &= ~((4+2+1)<<16);
_GPIOA_(GPIOX_CRH) |= (8)<<16;
_GPIOA_(GPIOX_ODR) |= (1)<<12;
}

inline void pinA12_Input_PD()
{
_GPIOA_(GPIOX_CRH) &= ~((4+2+1)<<16);
_GPIOA_(GPIOX_CRH) |= (8)<<16;
_GPIOA_(GPIOX_ODR) &= ~(1<<12);
}

inline void pinA12_Analog()
{
_GPIOA_(GPIOX_CRH) &= ~((8+4+2+1)<<16);
}

inline void pinA12_Output()
{
_GPIOA_(GPIOX_CRH) &= ~((8+4+1)<<16);
_GPIOA_(GPIOX_CRH) |= (2)<<16;
}

inline void pinA12_Output_OD()
{
_GPIOA_(GPIOX_CRH) &= ~((8+1)<<16);
_GPIOA_(GPIOX_CRH) |= (2+4)<<16;
}

inline void pinA12_Output_PP_2()
{
_GPIOA_(GPIOX_CRH) &= ~((8+4+1)<<16);
_GPIOA_(GPIOX_CRH) |= (2)<<16;
}

inline void pinA12_Output_PP_10()
{
_GPIOA_(GPIOX_CRH) &= ~((8+4+2)<<16);
_GPIOA_(GPIOX_CRH) |= (1)<<16;
}

inline void pinA12_Output_PP_50()
{
_GPIOA_(GPIOX_CRH) &= ~((8+4)<<16);
_GPIOA_(GPIOX_CRH) |= (2+1)<<16;
}

inline void pinA12_Output_OD_2()
{
_GPIOA_(GPIOX_CRH) &= ~((8+1)<<16);
_GPIOA_(GPIOX_CRH) |= (2+4)<<16;
}

inline void pinA12_Output_OD_10()
{
_GPIOA_(GPIOX_CRH) &= ~((8+2)<<16);
_GPIOA_(GPIOX_CRH) |= (4+1)<<16;
}

inline void pinA12_Output_OD_50()
{
_GPIOA_(GPIOX_CRH) &= ~((8)<<16);
_GPIOA_(GPIOX_CRH) |= (4+2+1)<<16;
}

inline void pinA12_Output_AFPP_2()
{
_GPIOA_(GPIOX_CRH) &= ~((4+1)<<16);
_GPIOA_(GPIOX_CRH) |= (8+2)<<16;
}

inline void pinA12_Output_AFPP_10()
{
_GPIOA_(GPIOX_CRH) &= ~((4+2)<<16);
_GPIOA_(GPIOX_CRH) |= (8+1)<<16;
}

inline void pinA12_Output_AFPP_50()
{
_GPIOA_(GPIOX_CRH) &= ~((4)<<16);
_GPIOA_(GPIOX_CRH) |= (8+2+1)<<16;
}

inline void pinA12_Output_AFOD_2()
{
_GPIOA_(GPIOX_CRH) &= ~((1)<<16);
_GPIOA_(GPIOX_CRH) |= (8+2+4)<<16;
}

inline void pinA12_Output_AFOD_10()
{
_GPIOA_(GPIOX_CRH) &= ~((2)<<16);
_GPIOA_(GPIOX_CRH) |= (8+4+1)<<16;
}

inline void pinA12_Output_AFOD_50()
{
_GPIOA_(GPIOX_CRH) |= (8+4+2+1)<<16;
}

inline void pinA13_Input()
{
_GPIOA_(GPIOX_CRH) &= ~((8+2+1)<<20);
_GPIOA_(GPIOX_CRH) |= (4)<<20;
}

inline void pinA13_Input_PU()
{
_GPIOA_(GPIOX_CRH) &= ~((4+2+1)<<20);
_GPIOA_(GPIOX_CRH) |= (8)<<20;
_GPIOA_(GPIOX_ODR) |= (1)<<13;
}

inline void pinA13_Input_PD()
{
_GPIOA_(GPIOX_CRH) &= ~((4+2+1)<<20);
_GPIOA_(GPIOX_CRH) |= (8)<<20;
_GPIOA_(GPIOX_ODR) &= ~(1<<13);
}

inline void pinA13_Analog()
{
_GPIOA_(GPIOX_CRH) &= ~((8+4+2+1)<<20);
}

inline void pinA13_Output()
{
_GPIOA_(GPIOX_CRH) &= ~((8+4+1)<<20);
_GPIOA_(GPIOX_CRH) |= (2)<<20;
}

inline void pinA13_Output_OD()
{
_GPIOA_(GPIOX_CRH) &= ~((8+1)<<20);
_GPIOA_(GPIOX_CRH) |= (2+4)<<20;
}

inline void pinA13_Output_PP_2()
{
_GPIOA_(GPIOX_CRH) &= ~((8+4+1)<<20);
_GPIOA_(GPIOX_CRH) |= (2)<<20;
}

inline void pinA13_Output_PP_10()
{
_GPIOA_(GPIOX_CRH) &= ~((8+4+2)<<20);
_GPIOA_(GPIOX_CRH) |= (1)<<20;
}

inline void pinA13_Output_PP_50()
{
_GPIOA_(GPIOX_CRH) &= ~((8+4)<<20);
_GPIOA_(GPIOX_CRH) |= (2+1)<<20;
}

inline void pinA13_Output_OD_2()
{
_GPIOA_(GPIOX_CRH) &= ~((8+1)<<20);
_GPIOA_(GPIOX_CRH) |= (2+4)<<20;
}

inline void pinA13_Output_OD_10()
{
_GPIOA_(GPIOX_CRH) &= ~((8+2)<<20);
_GPIOA_(GPIOX_CRH) |= (4+1)<<20;
}

inline void pinA13_Output_OD_50()
{
_GPIOA_(GPIOX_CRH) &= ~((8)<<20);
_GPIOA_(GPIOX_CRH) |= (4+2+1)<<20;
}

inline void pinA13_Output_AFPP_2()
{
_GPIOA_(GPIOX_CRH) &= ~((4+1)<<20);
_GPIOA_(GPIOX_CRH) |= (8+2)<<20;
}

inline void pinA13_Output_AFPP_10()
{
_GPIOA_(GPIOX_CRH) &= ~((4+2)<<20);
_GPIOA_(GPIOX_CRH) |= (8+1)<<20;
}

inline void pinA13_Output_AFPP_50()
{
_GPIOA_(GPIOX_CRH) &= ~((4)<<20);
_GPIOA_(GPIOX_CRH) |= (8+2+1)<<20;
}

inline void pinA13_Output_AFOD_2()
{
_GPIOA_(GPIOX_CRH) &= ~((1)<<20);
_GPIOA_(GPIOX_CRH) |= (8+2+4)<<20;
}

inline void pinA13_Output_AFOD_10()
{
_GPIOA_(GPIOX_CRH) &= ~((2)<<20);
_GPIOA_(GPIOX_CRH) |= (8+4+1)<<20;
}

inline void pinA13_Output_AFOD_50()
{
_GPIOA_(GPIOX_CRH) |= (8+4+2+1)<<20;
}

inline void pinA14_Input()
{
_GPIOA_(GPIOX_CRH) &= ~((8+2+1)<<24);
_GPIOA_(GPIOX_CRH) |= (4)<<24;
}

inline void pinA14_Input_PU()
{
_GPIOA_(GPIOX_CRH) &= ~((4+2+1)<<24);
_GPIOA_(GPIOX_CRH) |= (8)<<24;
_GPIOA_(GPIOX_ODR) |= (1)<<14;
}

inline void pinA14_Input_PD()
{
_GPIOA_(GPIOX_CRH) &= ~((4+2+1)<<24);
_GPIOA_(GPIOX_CRH) |= (8)<<24;
_GPIOA_(GPIOX_ODR) &= ~(1<<14);
}

inline void pinA14_Analog()
{
_GPIOA_(GPIOX_CRH) &= ~((8+4+2+1)<<24);
}

inline void pinA14_Output()
{
_GPIOA_(GPIOX_CRH) &= ~((8+4+1)<<24);
_GPIOA_(GPIOX_CRH) |= (2)<<24;
}

inline void pinA14_Output_OD()
{
_GPIOA_(GPIOX_CRH) &= ~((8+1)<<24);
_GPIOA_(GPIOX_CRH) |= (2+4)<<24;
}

inline void pinA14_Output_PP_2()
{
_GPIOA_(GPIOX_CRH) &= ~((8+4+1)<<24);
_GPIOA_(GPIOX_CRH) |= (2)<<24;
}

inline void pinA14_Output_PP_10()
{
_GPIOA_(GPIOX_CRH) &= ~((8+4+2)<<24);
_GPIOA_(GPIOX_CRH) |= (1)<<24;
}

inline void pinA14_Output_PP_50()
{
_GPIOA_(GPIOX_CRH) &= ~((8+4)<<24);
_GPIOA_(GPIOX_CRH) |= (2+1)<<24;
}

inline void pinA14_Output_OD_2()
{
_GPIOA_(GPIOX_CRH) &= ~((8+1)<<24);
_GPIOA_(GPIOX_CRH) |= (2+4)<<24;
}

inline void pinA14_Output_OD_10()
{
_GPIOA_(GPIOX_CRH) &= ~((8+2)<<24);
_GPIOA_(GPIOX_CRH) |= (4+1)<<24;
}

inline void pinA14_Output_OD_50()
{
_GPIOA_(GPIOX_CRH) &= ~((8)<<24);
_GPIOA_(GPIOX_CRH) |= (4+2+1)<<24;
}

inline void pinA14_Output_AFPP_2()
{
_GPIOA_(GPIOX_CRH) &= ~((4+1)<<24);
_GPIOA_(GPIOX_CRH) |= (8+2)<<24;
}

inline void pinA14_Output_AFPP_10()
{
_GPIOA_(GPIOX_CRH) &= ~((4+2)<<24);
_GPIOA_(GPIOX_CRH) |= (8+1)<<24;
}

inline void pinA14_Output_AFPP_50()
{
_GPIOA_(GPIOX_CRH) &= ~((4)<<24);
_GPIOA_(GPIOX_CRH) |= (8+2+1)<<24;
}

inline void pinA14_Output_AFOD_2()
{
_GPIOA_(GPIOX_CRH) &= ~((1)<<24);
_GPIOA_(GPIOX_CRH) |= (8+2+4)<<24;
}

inline void pinA14_Output_AFOD_10()
{
_GPIOA_(GPIOX_CRH) &= ~((2)<<24);
_GPIOA_(GPIOX_CRH) |= (8+4+1)<<24;
}

inline void pinA14_Output_AFOD_50()
{
_GPIOA_(GPIOX_CRH) |= (8+4+2+1)<<24;
}

inline void pinA15_Input()
{
_GPIOA_(GPIOX_CRH) &= ~((8+2+1)<<28);
_GPIOA_(GPIOX_CRH) |= (4)<<28;
}

inline void pinA15_Input_PU()
{
_GPIOA_(GPIOX_CRH) &= ~((4+2+1)<<28);
_GPIOA_(GPIOX_CRH) |= (8)<<28;
_GPIOA_(GPIOX_ODR) |= (1)<<15;
}

inline void pinA15_Input_PD()
{
_GPIOA_(GPIOX_CRH) &= ~((4+2+1)<<28);
_GPIOA_(GPIOX_CRH) |= (8)<<28;
_GPIOA_(GPIOX_ODR) &= ~(1<<15);
}

inline void pinA15_Analog()
{
_GPIOA_(GPIOX_CRH) &= ~((8+4+2+1)<<28);
}

inline void pinA15_Output()
{
_GPIOA_(GPIOX_CRH) &= ~((8+4+1)<<28);
_GPIOA_(GPIOX_CRH) |= (2)<<28;
}

inline void pinA15_Output_OD()
{
_GPIOA_(GPIOX_CRH) &= ~((8+1)<<28);
_GPIOA_(GPIOX_CRH) |= (2+4)<<28;
}

inline void pinA15_Output_PP_2()
{
_GPIOA_(GPIOX_CRH) &= ~((8+4+1)<<28);
_GPIOA_(GPIOX_CRH) |= (2)<<28;
}

inline void pinA15_Output_PP_10()
{
_GPIOA_(GPIOX_CRH) &= ~((8+4+2)<<28);
_GPIOA_(GPIOX_CRH) |= (1)<<28;
}

inline void pinA15_Output_PP_50()
{
_GPIOA_(GPIOX_CRH) &= ~((8+4)<<28);
_GPIOA_(GPIOX_CRH) |= (2+1)<<28;
}

inline void pinA15_Output_OD_2()
{
_GPIOA_(GPIOX_CRH) &= ~((8+1)<<28);
_GPIOA_(GPIOX_CRH) |= (2+4)<<28;
}

inline void pinA15_Output_OD_10()
{
_GPIOA_(GPIOX_CRH) &= ~((8+2)<<28);
_GPIOA_(GPIOX_CRH) |= (4+1)<<28;
}

inline void pinA15_Output_OD_50()
{
_GPIOA_(GPIOX_CRH) &= ~((8)<<28);
_GPIOA_(GPIOX_CRH) |= (4+2+1)<<28;
}

inline void pinA15_Output_AFPP_2()
{
_GPIOA_(GPIOX_CRH) &= ~((4+1)<<28);
_GPIOA_(GPIOX_CRH) |= (8+2)<<28;
}

inline void pinA15_Output_AFPP_10()
{
_GPIOA_(GPIOX_CRH) &= ~((4+2)<<28);
_GPIOA_(GPIOX_CRH) |= (8+1)<<28;
}

inline void pinA15_Output_AFPP_50()
{
_GPIOA_(GPIOX_CRH) &= ~((4)<<28);
_GPIOA_(GPIOX_CRH) |= (8+2+1)<<28;
}

inline void pinA15_Output_AFOD_2()
{
_GPIOA_(GPIOX_CRH) &= ~((1)<<28);
_GPIOA_(GPIOX_CRH) |= (8+2+4)<<28;
}

inline void pinA15_Output_AFOD_10()
{
_GPIOA_(GPIOX_CRH) &= ~((2)<<28);
_GPIOA_(GPIOX_CRH) |= (8+4+1)<<28;
}

inline void pinA15_Output_AFOD_50()
{
_GPIOA_(GPIOX_CRH) |= (8+4+2+1)<<28;
}

inline uint8_t readPinA0()
{
return ((_GPIOA_(GPIOX_IDR)>>0) & 1);
}

inline void setPinA0()
{
_GPIOA_(GPIOX_BSRR) = (1<<0);
}

inline void resetPinA0()
{
_GPIOA_(GPIOX_BRR) = (1<<0);
}

inline uint8_t readPinA1()
{
return ((_GPIOA_(GPIOX_IDR)>>1) & 1);
}

inline void setPinA1()
{
_GPIOA_(GPIOX_BSRR) = (1<<1);
}

inline void resetPinA1()
{
_GPIOA_(GPIOX_BRR) = (1<<1);
}

inline uint8_t readPinA2()
{
return ((_GPIOA_(GPIOX_IDR)>>2) & 1);
}

inline void setPinA2()
{
_GPIOA_(GPIOX_BSRR) = (1<<2);
}

inline void resetPinA2()
{
_GPIOA_(GPIOX_BRR) = (1<<2);
}

inline uint8_t readPinA3()
{
return ((_GPIOA_(GPIOX_IDR)>>3) & 1);
}

inline void setPinA3()
{
_GPIOA_(GPIOX_BSRR) = (1<<3);
}

inline void resetPinA3()
{
_GPIOA_(GPIOX_BRR) = (1<<3);
}

inline uint8_t readPinA4()
{
return ((_GPIOA_(GPIOX_IDR)>>4) & 1);
}

inline void setPinA4()
{
_GPIOA_(GPIOX_BSRR) = (1<<4);
}

inline void resetPinA4()
{
_GPIOA_(GPIOX_BRR) = (1<<4);
}

inline uint8_t readPinA5()
{
return ((_GPIOA_(GPIOX_IDR)>>5) & 1);
}

inline void setPinA5()
{
_GPIOA_(GPIOX_BSRR) = (1<<5);
}

inline void resetPinA5()
{
_GPIOA_(GPIOX_BRR) = (1<<5);
}

inline uint8_t readPinA6()
{
return ((_GPIOA_(GPIOX_IDR)>>6) & 1);
}

inline void setPinA6()
{
_GPIOA_(GPIOX_BSRR) = (1<<6);
}

inline void resetPinA6()
{
_GPIOA_(GPIOX_BRR) = (1<<6);
}

inline uint8_t readPinA7()
{
return ((_GPIOA_(GPIOX_IDR)>>7) & 1);
}

inline void setPinA7()
{
_GPIOA_(GPIOX_BSRR) = (1<<7);
}

inline void resetPinA7()
{
_GPIOA_(GPIOX_BRR) = (1<<7);
}

inline uint8_t readPinA8()
{
return ((_GPIOA_(GPIOX_IDR)>>8) & 1);
}

inline void setPinA8()
{
_GPIOA_(GPIOX_BSRR) = (1<<8);
}

inline void resetPinA8()
{
_GPIOA_(GPIOX_BRR) = (1<<8);
}

inline uint8_t readPinA9()
{
return ((_GPIOA_(GPIOX_IDR)>>9) & 1);
}

inline void setPinA9()
{
_GPIOA_(GPIOX_BSRR) = (1<<9);
}

inline void resetPinA9()
{
_GPIOA_(GPIOX_BRR) = (1<<9);
}

inline uint8_t readPinA10()
{
return ((_GPIOA_(GPIOX_IDR)>>10) & 1);
}

inline void setPinA10()
{
_GPIOA_(GPIOX_BSRR) = (1<<10);
}

inline void resetPinA10()
{
_GPIOA_(GPIOX_BRR) = (1<<10);
}

inline uint8_t readPinA11()
{
return ((_GPIOA_(GPIOX_IDR)>>11) & 1);
}

inline void setPinA11()
{
_GPIOA_(GPIOX_BSRR) = (1<<11);
}

inline void resetPinA11()
{
_GPIOA_(GPIOX_BRR) = (1<<11);
}

inline uint8_t readPinA12()
{
return ((_GPIOA_(GPIOX_IDR)>>12) & 1);
}

inline void setPinA12()
{
_GPIOA_(GPIOX_BSRR) = (1<<12);
}

inline void resetPinA12()
{
_GPIOA_(GPIOX_BRR) = (1<<12);
}

inline uint8_t readPinA13()
{
return ((_GPIOA_(GPIOX_IDR)>>13) & 1);
}

inline void setPinA13()
{
_GPIOA_(GPIOX_BSRR) = (1<<13);
}

inline void resetPinA13()
{
_GPIOA_(GPIOX_BRR) = (1<<13);
}

inline uint8_t readPinA14()
{
return ((_GPIOA_(GPIOX_IDR)>>14) & 1);
}

inline void setPinA14()
{
_GPIOA_(GPIOX_BSRR) = (1<<14);
}

inline void resetPinA14()
{
_GPIOA_(GPIOX_BRR) = (1<<14);
}

inline uint8_t readPinA15()
{
return ((_GPIOA_(GPIOX_IDR)>>15) & 1);
}

inline void setPinA15()
{
_GPIOA_(GPIOX_BSRR) = (1<<15);
}

inline void resetPinA15()
{
_GPIOA_(GPIOX_BRR) = (1<<15);
}

inline void pinB0_Input()
{
_GPIOB_(GPIOX_CRL) &= ~((8+2+1)<<0);
_GPIOB_(GPIOX_CRL) |= (4)<<0;
}

inline void pinB0_Input_PU()
{
_GPIOB_(GPIOX_CRL) &= ~((4+2+1)<<0);
_GPIOB_(GPIOX_CRL) |= (8)<<0;
_GPIOB_(GPIOX_ODR) |= (1)<<0;
}

inline void pinB0_Input_PD()
{
_GPIOB_(GPIOX_CRL) &= ~((4+2+1)<<0);
_GPIOB_(GPIOX_CRL) |= (8)<<0;
_GPIOB_(GPIOX_ODR) &= ~(1<<0);
}

inline void pinB0_Analog()
{
_GPIOB_(GPIOX_CRL) &= ~((8+4+2+1)<<0);
}

inline void pinB0_Output()
{
_GPIOB_(GPIOX_CRL) &= ~((8+4+1)<<0);
_GPIOB_(GPIOX_CRL) |= (2)<<0;
}

inline void pinB0_Output_OD()
{
_GPIOB_(GPIOX_CRL) &= ~((8+1)<<0);
_GPIOB_(GPIOX_CRL) |= (2+4)<<0;
}

inline void pinB0_Output_PP_2()
{
_GPIOB_(GPIOX_CRL) &= ~((8+4+1)<<0);
_GPIOB_(GPIOX_CRL) |= (2)<<0;
}

inline void pinB0_Output_PP_10()
{
_GPIOB_(GPIOX_CRL) &= ~((8+4+2)<<0);
_GPIOB_(GPIOX_CRL) |= (1)<<0;
}

inline void pinB0_Output_PP_50()
{
_GPIOB_(GPIOX_CRL) &= ~((8+4)<<0);
_GPIOB_(GPIOX_CRL) |= (2+1)<<0;
}

inline void pinB0_Output_OD_2()
{
_GPIOB_(GPIOX_CRL) &= ~((8+1)<<0);
_GPIOB_(GPIOX_CRL) |= (2+4)<<0;
}

inline void pinB0_Output_OD_10()
{
_GPIOB_(GPIOX_CRL) &= ~((8+2)<<0);
_GPIOB_(GPIOX_CRL) |= (4+1)<<0;
}

inline void pinB0_Output_OD_50()
{
_GPIOB_(GPIOX_CRL) &= ~((8)<<0);
_GPIOB_(GPIOX_CRL) |= (4+2+1)<<0;
}

inline void pinB0_Output_AFPP_2()
{
_GPIOB_(GPIOX_CRL) &= ~((4+1)<<0);
_GPIOB_(GPIOX_CRL) |= (8+2)<<0;
}

inline void pinB0_Output_AFPP_10()
{
_GPIOB_(GPIOX_CRL) &= ~((4+2)<<0);
_GPIOB_(GPIOX_CRL) |= (8+1)<<0;
}

inline void pinB0_Output_AFPP_50()
{
_GPIOB_(GPIOX_CRL) &= ~((4)<<0);
_GPIOB_(GPIOX_CRL) |= (8+2+1)<<0;
}

inline void pinB0_Output_AFOD_2()
{
_GPIOB_(GPIOX_CRL) &= ~((1)<<0);
_GPIOB_(GPIOX_CRL) |= (8+2+4)<<0;
}

inline void pinB0_Output_AFOD_10()
{
_GPIOB_(GPIOX_CRL) &= ~((2)<<0);
_GPIOB_(GPIOX_CRL) |= (8+4+1)<<0;
}

inline void pinB0_Output_AFOD_50()
{
_GPIOB_(GPIOX_CRL) |= (8+4+2+1)<<0;
}

inline void pinB1_Input()
{
_GPIOB_(GPIOX_CRL) &= ~((8+2+1)<<4);
_GPIOB_(GPIOX_CRL) |= (4)<<4;
}

inline void pinB1_Input_PU()
{
_GPIOB_(GPIOX_CRL) &= ~((4+2+1)<<4);
_GPIOB_(GPIOX_CRL) |= (8)<<4;
_GPIOB_(GPIOX_ODR) |= (1)<<1;
}

inline void pinB1_Input_PD()
{
_GPIOB_(GPIOX_CRL) &= ~((4+2+1)<<4);
_GPIOB_(GPIOX_CRL) |= (8)<<4;
_GPIOB_(GPIOX_ODR) &= ~(1<<1);
}

inline void pinB1_Analog()
{
_GPIOB_(GPIOX_CRL) &= ~((8+4+2+1)<<4);
}

inline void pinB1_Output()
{
_GPIOB_(GPIOX_CRL) &= ~((8+4+1)<<4);
_GPIOB_(GPIOX_CRL) |= (2)<<4;
}

inline void pinB1_Output_OD()
{
_GPIOB_(GPIOX_CRL) &= ~((8+1)<<4);
_GPIOB_(GPIOX_CRL) |= (2+4)<<4;
}

inline void pinB1_Output_PP_2()
{
_GPIOB_(GPIOX_CRL) &= ~((8+4+1)<<4);
_GPIOB_(GPIOX_CRL) |= (2)<<4;
}

inline void pinB1_Output_PP_10()
{
_GPIOB_(GPIOX_CRL) &= ~((8+4+2)<<4);
_GPIOB_(GPIOX_CRL) |= (1)<<4;
}

inline void pinB1_Output_PP_50()
{
_GPIOB_(GPIOX_CRL) &= ~((8+4)<<4);
_GPIOB_(GPIOX_CRL) |= (2+1)<<4;
}

inline void pinB1_Output_OD_2()
{
_GPIOB_(GPIOX_CRL) &= ~((8+1)<<4);
_GPIOB_(GPIOX_CRL) |= (2+4)<<4;
}

inline void pinB1_Output_OD_10()
{
_GPIOB_(GPIOX_CRL) &= ~((8+2)<<4);
_GPIOB_(GPIOX_CRL) |= (4+1)<<4;
}

inline void pinB1_Output_OD_50()
{
_GPIOB_(GPIOX_CRL) &= ~((8)<<4);
_GPIOB_(GPIOX_CRL) |= (4+2+1)<<4;
}

inline void pinB1_Output_AFPP_2()
{
_GPIOB_(GPIOX_CRL) &= ~((4+1)<<4);
_GPIOB_(GPIOX_CRL) |= (8+2)<<4;
}

inline void pinB1_Output_AFPP_10()
{
_GPIOB_(GPIOX_CRL) &= ~((4+2)<<4);
_GPIOB_(GPIOX_CRL) |= (8+1)<<4;
}

inline void pinB1_Output_AFPP_50()
{
_GPIOB_(GPIOX_CRL) &= ~((4)<<4);
_GPIOB_(GPIOX_CRL) |= (8+2+1)<<4;
}

inline void pinB1_Output_AFOD_2()
{
_GPIOB_(GPIOX_CRL) &= ~((1)<<4);
_GPIOB_(GPIOX_CRL) |= (8+2+4)<<4;
}

inline void pinB1_Output_AFOD_10()
{
_GPIOB_(GPIOX_CRL) &= ~((2)<<4);
_GPIOB_(GPIOX_CRL) |= (8+4+1)<<4;
}

inline void pinB1_Output_AFOD_50()
{
_GPIOB_(GPIOX_CRL) |= (8+4+2+1)<<4;
}

inline void pinB2_Input()
{
_GPIOB_(GPIOX_CRL) &= ~((8+2+1)<<8);
_GPIOB_(GPIOX_CRL) |= (4)<<8;
}

inline void pinB2_Input_PU()
{
_GPIOB_(GPIOX_CRL) &= ~((4+2+1)<<8);
_GPIOB_(GPIOX_CRL) |= (8)<<8;
_GPIOB_(GPIOX_ODR) |= (1)<<2;
}

inline void pinB2_Input_PD()
{
_GPIOB_(GPIOX_CRL) &= ~((4+2+1)<<8);
_GPIOB_(GPIOX_CRL) |= (8)<<8;
_GPIOB_(GPIOX_ODR) &= ~(1<<2);
}

inline void pinB2_Analog()
{
_GPIOB_(GPIOX_CRL) &= ~((8+4+2+1)<<8);
}

inline void pinB2_Output()
{
_GPIOB_(GPIOX_CRL) &= ~((8+4+1)<<8);
_GPIOB_(GPIOX_CRL) |= (2)<<8;
}

inline void pinB2_Output_OD()
{
_GPIOB_(GPIOX_CRL) &= ~((8+1)<<8);
_GPIOB_(GPIOX_CRL) |= (2+4)<<8;
}

inline void pinB2_Output_PP_2()
{
_GPIOB_(GPIOX_CRL) &= ~((8+4+1)<<8);
_GPIOB_(GPIOX_CRL) |= (2)<<8;
}

inline void pinB2_Output_PP_10()
{
_GPIOB_(GPIOX_CRL) &= ~((8+4+2)<<8);
_GPIOB_(GPIOX_CRL) |= (1)<<8;
}

inline void pinB2_Output_PP_50()
{
_GPIOB_(GPIOX_CRL) &= ~((8+4)<<8);
_GPIOB_(GPIOX_CRL) |= (2+1)<<8;
}

inline void pinB2_Output_OD_2()
{
_GPIOB_(GPIOX_CRL) &= ~((8+1)<<8);
_GPIOB_(GPIOX_CRL) |= (2+4)<<8;
}

inline void pinB2_Output_OD_10()
{
_GPIOB_(GPIOX_CRL) &= ~((8+2)<<8);
_GPIOB_(GPIOX_CRL) |= (4+1)<<8;
}

inline void pinB2_Output_OD_50()
{
_GPIOB_(GPIOX_CRL) &= ~((8)<<8);
_GPIOB_(GPIOX_CRL) |= (4+2+1)<<8;
}

inline void pinB2_Output_AFPP_2()
{
_GPIOB_(GPIOX_CRL) &= ~((4+1)<<8);
_GPIOB_(GPIOX_CRL) |= (8+2)<<8;
}

inline void pinB2_Output_AFPP_10()
{
_GPIOB_(GPIOX_CRL) &= ~((4+2)<<8);
_GPIOB_(GPIOX_CRL) |= (8+1)<<8;
}

inline void pinB2_Output_AFPP_50()
{
_GPIOB_(GPIOX_CRL) &= ~((4)<<8);
_GPIOB_(GPIOX_CRL) |= (8+2+1)<<8;
}

inline void pinB2_Output_AFOD_2()
{
_GPIOB_(GPIOX_CRL) &= ~((1)<<8);
_GPIOB_(GPIOX_CRL) |= (8+2+4)<<8;
}

inline void pinB2_Output_AFOD_10()
{
_GPIOB_(GPIOX_CRL) &= ~((2)<<8);
_GPIOB_(GPIOX_CRL) |= (8+4+1)<<8;
}

inline void pinB2_Output_AFOD_50()
{
_GPIOB_(GPIOX_CRL) |= (8+4+2+1)<<8;
}

inline void pinB3_Input()
{
_GPIOB_(GPIOX_CRL) &= ~((8+2+1)<<12);
_GPIOB_(GPIOX_CRL) |= (4)<<12;
}

inline void pinB3_Input_PU()
{
_GPIOB_(GPIOX_CRL) &= ~((4+2+1)<<12);
_GPIOB_(GPIOX_CRL) |= (8)<<12;
_GPIOB_(GPIOX_ODR) |= (1)<<3;
}

inline void pinB3_Input_PD()
{
_GPIOB_(GPIOX_CRL) &= ~((4+2+1)<<12);
_GPIOB_(GPIOX_CRL) |= (8)<<12;
_GPIOB_(GPIOX_ODR) &= ~(1<<3);
}

inline void pinB3_Analog()
{
_GPIOB_(GPIOX_CRL) &= ~((8+4+2+1)<<12);
}

inline void pinB3_Output()
{
_GPIOB_(GPIOX_CRL) &= ~((8+4+1)<<12);
_GPIOB_(GPIOX_CRL) |= (2)<<12;
}

inline void pinB3_Output_OD()
{
_GPIOB_(GPIOX_CRL) &= ~((8+1)<<12);
_GPIOB_(GPIOX_CRL) |= (2+4)<<12;
}

inline void pinB3_Output_PP_2()
{
_GPIOB_(GPIOX_CRL) &= ~((8+4+1)<<12);
_GPIOB_(GPIOX_CRL) |= (2)<<12;
}

inline void pinB3_Output_PP_10()
{
_GPIOB_(GPIOX_CRL) &= ~((8+4+2)<<12);
_GPIOB_(GPIOX_CRL) |= (1)<<12;
}

inline void pinB3_Output_PP_50()
{
_GPIOB_(GPIOX_CRL) &= ~((8+4)<<12);
_GPIOB_(GPIOX_CRL) |= (2+1)<<12;
}

inline void pinB3_Output_OD_2()
{
_GPIOB_(GPIOX_CRL) &= ~((8+1)<<12);
_GPIOB_(GPIOX_CRL) |= (2+4)<<12;
}

inline void pinB3_Output_OD_10()
{
_GPIOB_(GPIOX_CRL) &= ~((8+2)<<12);
_GPIOB_(GPIOX_CRL) |= (4+1)<<12;
}

inline void pinB3_Output_OD_50()
{
_GPIOB_(GPIOX_CRL) &= ~((8)<<12);
_GPIOB_(GPIOX_CRL) |= (4+2+1)<<12;
}

inline void pinB3_Output_AFPP_2()
{
_GPIOB_(GPIOX_CRL) &= ~((4+1)<<12);
_GPIOB_(GPIOX_CRL) |= (8+2)<<12;
}

inline void pinB3_Output_AFPP_10()
{
_GPIOB_(GPIOX_CRL) &= ~((4+2)<<12);
_GPIOB_(GPIOX_CRL) |= (8+1)<<12;
}

inline void pinB3_Output_AFPP_50()
{
_GPIOB_(GPIOX_CRL) &= ~((4)<<12);
_GPIOB_(GPIOX_CRL) |= (8+2+1)<<12;
}

inline void pinB3_Output_AFOD_2()
{
_GPIOB_(GPIOX_CRL) &= ~((1)<<12);
_GPIOB_(GPIOX_CRL) |= (8+2+4)<<12;
}

inline void pinB3_Output_AFOD_10()
{
_GPIOB_(GPIOX_CRL) &= ~((2)<<12);
_GPIOB_(GPIOX_CRL) |= (8+4+1)<<12;
}

inline void pinB3_Output_AFOD_50()
{
_GPIOB_(GPIOX_CRL) |= (8+4+2+1)<<12;
}

inline void pinB4_Input()
{
_GPIOB_(GPIOX_CRL) &= ~((8+2+1)<<16);
_GPIOB_(GPIOX_CRL) |= (4)<<16;
}

inline void pinB4_Input_PU()
{
_GPIOB_(GPIOX_CRL) &= ~((4+2+1)<<16);
_GPIOB_(GPIOX_CRL) |= (8)<<16;
_GPIOB_(GPIOX_ODR) |= (1)<<4;
}

inline void pinB4_Input_PD()
{
_GPIOB_(GPIOX_CRL) &= ~((4+2+1)<<16);
_GPIOB_(GPIOX_CRL) |= (8)<<16;
_GPIOB_(GPIOX_ODR) &= ~(1<<4);
}

inline void pinB4_Analog()
{
_GPIOB_(GPIOX_CRL) &= ~((8+4+2+1)<<16);
}

inline void pinB4_Output()
{
_GPIOB_(GPIOX_CRL) &= ~((8+4+1)<<16);
_GPIOB_(GPIOX_CRL) |= (2)<<16;
}

inline void pinB4_Output_OD()
{
_GPIOB_(GPIOX_CRL) &= ~((8+1)<<16);
_GPIOB_(GPIOX_CRL) |= (2+4)<<16;
}

inline void pinB4_Output_PP_2()
{
_GPIOB_(GPIOX_CRL) &= ~((8+4+1)<<16);
_GPIOB_(GPIOX_CRL) |= (2)<<16;
}

inline void pinB4_Output_PP_10()
{
_GPIOB_(GPIOX_CRL) &= ~((8+4+2)<<16);
_GPIOB_(GPIOX_CRL) |= (1)<<16;
}

inline void pinB4_Output_PP_50()
{
_GPIOB_(GPIOX_CRL) &= ~((8+4)<<16);
_GPIOB_(GPIOX_CRL) |= (2+1)<<16;
}

inline void pinB4_Output_OD_2()
{
_GPIOB_(GPIOX_CRL) &= ~((8+1)<<16);
_GPIOB_(GPIOX_CRL) |= (2+4)<<16;
}

inline void pinB4_Output_OD_10()
{
_GPIOB_(GPIOX_CRL) &= ~((8+2)<<16);
_GPIOB_(GPIOX_CRL) |= (4+1)<<16;
}

inline void pinB4_Output_OD_50()
{
_GPIOB_(GPIOX_CRL) &= ~((8)<<16);
_GPIOB_(GPIOX_CRL) |= (4+2+1)<<16;
}

inline void pinB4_Output_AFPP_2()
{
_GPIOB_(GPIOX_CRL) &= ~((4+1)<<16);
_GPIOB_(GPIOX_CRL) |= (8+2)<<16;
}

inline void pinB4_Output_AFPP_10()
{
_GPIOB_(GPIOX_CRL) &= ~((4+2)<<16);
_GPIOB_(GPIOX_CRL) |= (8+1)<<16;
}

inline void pinB4_Output_AFPP_50()
{
_GPIOB_(GPIOX_CRL) &= ~((4)<<16);
_GPIOB_(GPIOX_CRL) |= (8+2+1)<<16;
}

inline void pinB4_Output_AFOD_2()
{
_GPIOB_(GPIOX_CRL) &= ~((1)<<16);
_GPIOB_(GPIOX_CRL) |= (8+2+4)<<16;
}

inline void pinB4_Output_AFOD_10()
{
_GPIOB_(GPIOX_CRL) &= ~((2)<<16);
_GPIOB_(GPIOX_CRL) |= (8+4+1)<<16;
}

inline void pinB4_Output_AFOD_50()
{
_GPIOB_(GPIOX_CRL) |= (8+4+2+1)<<16;
}

inline void pinB5_Input()
{
_GPIOB_(GPIOX_CRL) &= ~((8+2+1)<<20);
_GPIOB_(GPIOX_CRL) |= (4)<<20;
}

inline void pinB5_Input_PU()
{
_GPIOB_(GPIOX_CRL) &= ~((4+2+1)<<20);
_GPIOB_(GPIOX_CRL) |= (8)<<20;
_GPIOB_(GPIOX_ODR) |= (1)<<5;
}

inline void pinB5_Input_PD()
{
_GPIOB_(GPIOX_CRL) &= ~((4+2+1)<<20);
_GPIOB_(GPIOX_CRL) |= (8)<<20;
_GPIOB_(GPIOX_ODR) &= ~(1<<5);
}

inline void pinB5_Analog()
{
_GPIOB_(GPIOX_CRL) &= ~((8+4+2+1)<<20);
}

inline void pinB5_Output()
{
_GPIOB_(GPIOX_CRL) &= ~((8+4+1)<<20);
_GPIOB_(GPIOX_CRL) |= (2)<<20;
}

inline void pinB5_Output_OD()
{
_GPIOB_(GPIOX_CRL) &= ~((8+1)<<20);
_GPIOB_(GPIOX_CRL) |= (2+4)<<20;
}

inline void pinB5_Output_PP_2()
{
_GPIOB_(GPIOX_CRL) &= ~((8+4+1)<<20);
_GPIOB_(GPIOX_CRL) |= (2)<<20;
}

inline void pinB5_Output_PP_10()
{
_GPIOB_(GPIOX_CRL) &= ~((8+4+2)<<20);
_GPIOB_(GPIOX_CRL) |= (1)<<20;
}

inline void pinB5_Output_PP_50()
{
_GPIOB_(GPIOX_CRL) &= ~((8+4)<<20);
_GPIOB_(GPIOX_CRL) |= (2+1)<<20;
}

inline void pinB5_Output_OD_2()
{
_GPIOB_(GPIOX_CRL) &= ~((8+1)<<20);
_GPIOB_(GPIOX_CRL) |= (2+4)<<20;
}

inline void pinB5_Output_OD_10()
{
_GPIOB_(GPIOX_CRL) &= ~((8+2)<<20);
_GPIOB_(GPIOX_CRL) |= (4+1)<<20;
}

inline void pinB5_Output_OD_50()
{
_GPIOB_(GPIOX_CRL) &= ~((8)<<20);
_GPIOB_(GPIOX_CRL) |= (4+2+1)<<20;
}

inline void pinB5_Output_AFPP_2()
{
_GPIOB_(GPIOX_CRL) &= ~((4+1)<<20);
_GPIOB_(GPIOX_CRL) |= (8+2)<<20;
}

inline void pinB5_Output_AFPP_10()
{
_GPIOB_(GPIOX_CRL) &= ~((4+2)<<20);
_GPIOB_(GPIOX_CRL) |= (8+1)<<20;
}

inline void pinB5_Output_AFPP_50()
{
_GPIOB_(GPIOX_CRL) &= ~((4)<<20);
_GPIOB_(GPIOX_CRL) |= (8+2+1)<<20;
}

inline void pinB5_Output_AFOD_2()
{
_GPIOB_(GPIOX_CRL) &= ~((1)<<20);
_GPIOB_(GPIOX_CRL) |= (8+2+4)<<20;
}

inline void pinB5_Output_AFOD_10()
{
_GPIOB_(GPIOX_CRL) &= ~((2)<<20);
_GPIOB_(GPIOX_CRL) |= (8+4+1)<<20;
}

inline void pinB5_Output_AFOD_50()
{
_GPIOB_(GPIOX_CRL) |= (8+4+2+1)<<20;
}

inline void pinB6_Input()
{
_GPIOB_(GPIOX_CRL) &= ~((8+2+1)<<24);
_GPIOB_(GPIOX_CRL) |= (4)<<24;
}

inline void pinB6_Input_PU()
{
_GPIOB_(GPIOX_CRL) &= ~((4+2+1)<<24);
_GPIOB_(GPIOX_CRL) |= (8)<<24;
_GPIOB_(GPIOX_ODR) |= (1)<<6;
}

inline void pinB6_Input_PD()
{
_GPIOB_(GPIOX_CRL) &= ~((4+2+1)<<24);
_GPIOB_(GPIOX_CRL) |= (8)<<24;
_GPIOB_(GPIOX_ODR) &= ~(1<<6);
}

inline void pinB6_Analog()
{
_GPIOB_(GPIOX_CRL) &= ~((8+4+2+1)<<24);
}

inline void pinB6_Output()
{
_GPIOB_(GPIOX_CRL) &= ~((8+4+1)<<24);
_GPIOB_(GPIOX_CRL) |= (2)<<24;
}

inline void pinB6_Output_OD()
{
_GPIOB_(GPIOX_CRL) &= ~((8+1)<<24);
_GPIOB_(GPIOX_CRL) |= (2+4)<<24;
}

inline void pinB6_Output_PP_2()
{
_GPIOB_(GPIOX_CRL) &= ~((8+4+1)<<24);
_GPIOB_(GPIOX_CRL) |= (2)<<24;
}

inline void pinB6_Output_PP_10()
{
_GPIOB_(GPIOX_CRL) &= ~((8+4+2)<<24);
_GPIOB_(GPIOX_CRL) |= (1)<<24;
}

inline void pinB6_Output_PP_50()
{
_GPIOB_(GPIOX_CRL) &= ~((8+4)<<24);
_GPIOB_(GPIOX_CRL) |= (2+1)<<24;
}

inline void pinB6_Output_OD_2()
{
_GPIOB_(GPIOX_CRL) &= ~((8+1)<<24);
_GPIOB_(GPIOX_CRL) |= (2+4)<<24;
}

inline void pinB6_Output_OD_10()
{
_GPIOB_(GPIOX_CRL) &= ~((8+2)<<24);
_GPIOB_(GPIOX_CRL) |= (4+1)<<24;
}

inline void pinB6_Output_OD_50()
{
_GPIOB_(GPIOX_CRL) &= ~((8)<<24);
_GPIOB_(GPIOX_CRL) |= (4+2+1)<<24;
}

inline void pinB6_Output_AFPP_2()
{
_GPIOB_(GPIOX_CRL) &= ~((4+1)<<24);
_GPIOB_(GPIOX_CRL) |= (8+2)<<24;
}

inline void pinB6_Output_AFPP_10()
{
_GPIOB_(GPIOX_CRL) &= ~((4+2)<<24);
_GPIOB_(GPIOX_CRL) |= (8+1)<<24;
}

inline void pinB6_Output_AFPP_50()
{
_GPIOB_(GPIOX_CRL) &= ~((4)<<24);
_GPIOB_(GPIOX_CRL) |= (8+2+1)<<24;
}

inline void pinB6_Output_AFOD_2()
{
_GPIOB_(GPIOX_CRL) &= ~((1)<<24);
_GPIOB_(GPIOX_CRL) |= (8+2+4)<<24;
}

inline void pinB6_Output_AFOD_10()
{
_GPIOB_(GPIOX_CRL) &= ~((2)<<24);
_GPIOB_(GPIOX_CRL) |= (8+4+1)<<24;
}

inline void pinB6_Output_AFOD_50()
{
_GPIOB_(GPIOX_CRL) |= (8+4+2+1)<<24;
}

inline void pinB7_Input()
{
_GPIOB_(GPIOX_CRL) &= ~((8+2+1)<<28);
_GPIOB_(GPIOX_CRL) |= (4)<<28;
}

inline void pinB7_Input_PU()
{
_GPIOB_(GPIOX_CRL) &= ~((4+2+1)<<28);
_GPIOB_(GPIOX_CRL) |= (8)<<28;
_GPIOB_(GPIOX_ODR) |= (1)<<7;
}

inline void pinB7_Input_PD()
{
_GPIOB_(GPIOX_CRL) &= ~((4+2+1)<<28);
_GPIOB_(GPIOX_CRL) |= (8)<<28;
_GPIOB_(GPIOX_ODR) &= ~(1<<7);
}

inline void pinB7_Analog()
{
_GPIOB_(GPIOX_CRL) &= ~((8+4+2+1)<<28);
}

inline void pinB7_Output()
{
_GPIOB_(GPIOX_CRL) &= ~((8+4+1)<<28);
_GPIOB_(GPIOX_CRL) |= (2)<<28;
}

inline void pinB7_Output_OD()
{
_GPIOB_(GPIOX_CRL) &= ~((8+1)<<28);
_GPIOB_(GPIOX_CRL) |= (2+4)<<28;
}

inline void pinB7_Output_PP_2()
{
_GPIOB_(GPIOX_CRL) &= ~((8+4+1)<<28);
_GPIOB_(GPIOX_CRL) |= (2)<<28;
}

inline void pinB7_Output_PP_10()
{
_GPIOB_(GPIOX_CRL) &= ~((8+4+2)<<28);
_GPIOB_(GPIOX_CRL) |= (1)<<28;
}

inline void pinB7_Output_PP_50()
{
_GPIOB_(GPIOX_CRL) &= ~((8+4)<<28);
_GPIOB_(GPIOX_CRL) |= (2+1)<<28;
}

inline void pinB7_Output_OD_2()
{
_GPIOB_(GPIOX_CRL) &= ~((8+1)<<28);
_GPIOB_(GPIOX_CRL) |= (2+4)<<28;
}

inline void pinB7_Output_OD_10()
{
_GPIOB_(GPIOX_CRL) &= ~((8+2)<<28);
_GPIOB_(GPIOX_CRL) |= (4+1)<<28;
}

inline void pinB7_Output_OD_50()
{
_GPIOB_(GPIOX_CRL) &= ~((8)<<28);
_GPIOB_(GPIOX_CRL) |= (4+2+1)<<28;
}

inline void pinB7_Output_AFPP_2()
{
_GPIOB_(GPIOX_CRL) &= ~((4+1)<<28);
_GPIOB_(GPIOX_CRL) |= (8+2)<<28;
}

inline void pinB7_Output_AFPP_10()
{
_GPIOB_(GPIOX_CRL) &= ~((4+2)<<28);
_GPIOB_(GPIOX_CRL) |= (8+1)<<28;
}

inline void pinB7_Output_AFPP_50()
{
_GPIOB_(GPIOX_CRL) &= ~((4)<<28);
_GPIOB_(GPIOX_CRL) |= (8+2+1)<<28;
}

inline void pinB7_Output_AFOD_2()
{
_GPIOB_(GPIOX_CRL) &= ~((1)<<28);
_GPIOB_(GPIOX_CRL) |= (8+2+4)<<28;
}

inline void pinB7_Output_AFOD_10()
{
_GPIOB_(GPIOX_CRL) &= ~((2)<<28);
_GPIOB_(GPIOX_CRL) |= (8+4+1)<<28;
}

inline void pinB7_Output_AFOD_50()
{
_GPIOB_(GPIOX_CRL) |= (8+4+2+1)<<28;
}

inline void pinB8_Input()
{
_GPIOB_(GPIOX_CRH) &= ~((8+2+1)<<0);
_GPIOB_(GPIOX_CRH) |= (4)<<0;
}

inline void pinB8_Input_PU()
{
_GPIOB_(GPIOX_CRH) &= ~((4+2+1)<<0);
_GPIOB_(GPIOX_CRH) |= (8)<<0;
_GPIOB_(GPIOX_ODR) |= (1)<<8;
}

inline void pinB8_Input_PD()
{
_GPIOB_(GPIOX_CRH) &= ~((4+2+1)<<0);
_GPIOB_(GPIOX_CRH) |= (8)<<0;
_GPIOB_(GPIOX_ODR) &= ~(1<<8);
}

inline void pinB8_Analog()
{
_GPIOB_(GPIOX_CRH) &= ~((8+4+2+1)<<0);
}

inline void pinB8_Output()
{
_GPIOB_(GPIOX_CRH) &= ~((8+4+1)<<0);
_GPIOB_(GPIOX_CRH) |= (2)<<0;
}

inline void pinB8_Output_OD()
{
_GPIOB_(GPIOX_CRH) &= ~((8+1)<<0);
_GPIOB_(GPIOX_CRH) |= (2+4)<<0;
}

inline void pinB8_Output_PP_2()
{
_GPIOB_(GPIOX_CRH) &= ~((8+4+1)<<0);
_GPIOB_(GPIOX_CRH) |= (2)<<0;
}

inline void pinB8_Output_PP_10()
{
_GPIOB_(GPIOX_CRH) &= ~((8+4+2)<<0);
_GPIOB_(GPIOX_CRH) |= (1)<<0;
}

inline void pinB8_Output_PP_50()
{
_GPIOB_(GPIOX_CRH) &= ~((8+4)<<0);
_GPIOB_(GPIOX_CRH) |= (2+1)<<0;
}

inline void pinB8_Output_OD_2()
{
_GPIOB_(GPIOX_CRH) &= ~((8+1)<<0);
_GPIOB_(GPIOX_CRH) |= (2+4)<<0;
}

inline void pinB8_Output_OD_10()
{
_GPIOB_(GPIOX_CRH) &= ~((8+2)<<0);
_GPIOB_(GPIOX_CRH) |= (4+1)<<0;
}

inline void pinB8_Output_OD_50()
{
_GPIOB_(GPIOX_CRH) &= ~((8)<<0);
_GPIOB_(GPIOX_CRH) |= (4+2+1)<<0;
}

inline void pinB8_Output_AFPP_2()
{
_GPIOB_(GPIOX_CRH) &= ~((4+1)<<0);
_GPIOB_(GPIOX_CRH) |= (8+2)<<0;
}

inline void pinB8_Output_AFPP_10()
{
_GPIOB_(GPIOX_CRH) &= ~((4+2)<<0);
_GPIOB_(GPIOX_CRH) |= (8+1)<<0;
}

inline void pinB8_Output_AFPP_50()
{
_GPIOB_(GPIOX_CRH) &= ~((4)<<0);
_GPIOB_(GPIOX_CRH) |= (8+2+1)<<0;
}

inline void pinB8_Output_AFOD_2()
{
_GPIOB_(GPIOX_CRH) &= ~((1)<<0);
_GPIOB_(GPIOX_CRH) |= (8+2+4)<<0;
}

inline void pinB8_Output_AFOD_10()
{
_GPIOB_(GPIOX_CRH) &= ~((2)<<0);
_GPIOB_(GPIOX_CRH) |= (8+4+1)<<0;
}

inline void pinB8_Output_AFOD_50()
{
_GPIOB_(GPIOX_CRH) |= (8+4+2+1)<<0;
}

inline void pinB9_Input()
{
_GPIOB_(GPIOX_CRH) &= ~((8+2+1)<<4);
_GPIOB_(GPIOX_CRH) |= (4)<<4;
}

inline void pinB9_Input_PU()
{
_GPIOB_(GPIOX_CRH) &= ~((4+2+1)<<4);
_GPIOB_(GPIOX_CRH) |= (8)<<4;
_GPIOB_(GPIOX_ODR) |= (1)<<9;
}

inline void pinB9_Input_PD()
{
_GPIOB_(GPIOX_CRH) &= ~((4+2+1)<<4);
_GPIOB_(GPIOX_CRH) |= (8)<<4;
_GPIOB_(GPIOX_ODR) &= ~(1<<9);
}

inline void pinB9_Analog()
{
_GPIOB_(GPIOX_CRH) &= ~((8+4+2+1)<<4);
}

inline void pinB9_Output()
{
_GPIOB_(GPIOX_CRH) &= ~((8+4+1)<<4);
_GPIOB_(GPIOX_CRH) |= (2)<<4;
}

inline void pinB9_Output_OD()
{
_GPIOB_(GPIOX_CRH) &= ~((8+1)<<4);
_GPIOB_(GPIOX_CRH) |= (2+4)<<4;
}

inline void pinB9_Output_PP_2()
{
_GPIOB_(GPIOX_CRH) &= ~((8+4+1)<<4);
_GPIOB_(GPIOX_CRH) |= (2)<<4;
}

inline void pinB9_Output_PP_10()
{
_GPIOB_(GPIOX_CRH) &= ~((8+4+2)<<4);
_GPIOB_(GPIOX_CRH) |= (1)<<4;
}

inline void pinB9_Output_PP_50()
{
_GPIOB_(GPIOX_CRH) &= ~((8+4)<<4);
_GPIOB_(GPIOX_CRH) |= (2+1)<<4;
}

inline void pinB9_Output_OD_2()
{
_GPIOB_(GPIOX_CRH) &= ~((8+1)<<4);
_GPIOB_(GPIOX_CRH) |= (2+4)<<4;
}

inline void pinB9_Output_OD_10()
{
_GPIOB_(GPIOX_CRH) &= ~((8+2)<<4);
_GPIOB_(GPIOX_CRH) |= (4+1)<<4;
}

inline void pinB9_Output_OD_50()
{
_GPIOB_(GPIOX_CRH) &= ~((8)<<4);
_GPIOB_(GPIOX_CRH) |= (4+2+1)<<4;
}

inline void pinB9_Output_AFPP_2()
{
_GPIOB_(GPIOX_CRH) &= ~((4+1)<<4);
_GPIOB_(GPIOX_CRH) |= (8+2)<<4;
}

inline void pinB9_Output_AFPP_10()
{
_GPIOB_(GPIOX_CRH) &= ~((4+2)<<4);
_GPIOB_(GPIOX_CRH) |= (8+1)<<4;
}

inline void pinB9_Output_AFPP_50()
{
_GPIOB_(GPIOX_CRH) &= ~((4)<<4);
_GPIOB_(GPIOX_CRH) |= (8+2+1)<<4;
}

inline void pinB9_Output_AFOD_2()
{
_GPIOB_(GPIOX_CRH) &= ~((1)<<4);
_GPIOB_(GPIOX_CRH) |= (8+2+4)<<4;
}

inline void pinB9_Output_AFOD_10()
{
_GPIOB_(GPIOX_CRH) &= ~((2)<<4);
_GPIOB_(GPIOX_CRH) |= (8+4+1)<<4;
}

inline void pinB9_Output_AFOD_50()
{
_GPIOB_(GPIOX_CRH) |= (8+4+2+1)<<4;
}

inline void pinB10_Input()
{
_GPIOB_(GPIOX_CRH) &= ~((8+2+1)<<8);
_GPIOB_(GPIOX_CRH) |= (4)<<8;
}

inline void pinB10_Input_PU()
{
_GPIOB_(GPIOX_CRH) &= ~((4+2+1)<<8);
_GPIOB_(GPIOX_CRH) |= (8)<<8;
_GPIOB_(GPIOX_ODR) |= (1)<<10;
}

inline void pinB10_Input_PD()
{
_GPIOB_(GPIOX_CRH) &= ~((4+2+1)<<8);
_GPIOB_(GPIOX_CRH) |= (8)<<8;
_GPIOB_(GPIOX_ODR) &= ~(1<<10);
}

inline void pinB10_Analog()
{
_GPIOB_(GPIOX_CRH) &= ~((8+4+2+1)<<8);
}

inline void pinB10_Output()
{
_GPIOB_(GPIOX_CRH) &= ~((8+4+1)<<8);
_GPIOB_(GPIOX_CRH) |= (2)<<8;
}

inline void pinB10_Output_OD()
{
_GPIOB_(GPIOX_CRH) &= ~((8+1)<<8);
_GPIOB_(GPIOX_CRH) |= (2+4)<<8;
}

inline void pinB10_Output_PP_2()
{
_GPIOB_(GPIOX_CRH) &= ~((8+4+1)<<8);
_GPIOB_(GPIOX_CRH) |= (2)<<8;
}

inline void pinB10_Output_PP_10()
{
_GPIOB_(GPIOX_CRH) &= ~((8+4+2)<<8);
_GPIOB_(GPIOX_CRH) |= (1)<<8;
}

inline void pinB10_Output_PP_50()
{
_GPIOB_(GPIOX_CRH) &= ~((8+4)<<8);
_GPIOB_(GPIOX_CRH) |= (2+1)<<8;
}

inline void pinB10_Output_OD_2()
{
_GPIOB_(GPIOX_CRH) &= ~((8+1)<<8);
_GPIOB_(GPIOX_CRH) |= (2+4)<<8;
}

inline void pinB10_Output_OD_10()
{
_GPIOB_(GPIOX_CRH) &= ~((8+2)<<8);
_GPIOB_(GPIOX_CRH) |= (4+1)<<8;
}

inline void pinB10_Output_OD_50()
{
_GPIOB_(GPIOX_CRH) &= ~((8)<<8);
_GPIOB_(GPIOX_CRH) |= (4+2+1)<<8;
}

inline void pinB10_Output_AFPP_2()
{
_GPIOB_(GPIOX_CRH) &= ~((4+1)<<8);
_GPIOB_(GPIOX_CRH) |= (8+2)<<8;
}

inline void pinB10_Output_AFPP_10()
{
_GPIOB_(GPIOX_CRH) &= ~((4+2)<<8);
_GPIOB_(GPIOX_CRH) |= (8+1)<<8;
}

inline void pinB10_Output_AFPP_50()
{
_GPIOB_(GPIOX_CRH) &= ~((4)<<8);
_GPIOB_(GPIOX_CRH) |= (8+2+1)<<8;
}

inline void pinB10_Output_AFOD_2()
{
_GPIOB_(GPIOX_CRH) &= ~((1)<<8);
_GPIOB_(GPIOX_CRH) |= (8+2+4)<<8;
}

inline void pinB10_Output_AFOD_10()
{
_GPIOB_(GPIOX_CRH) &= ~((2)<<8);
_GPIOB_(GPIOX_CRH) |= (8+4+1)<<8;
}

inline void pinB10_Output_AFOD_50()
{
_GPIOB_(GPIOX_CRH) |= (8+4+2+1)<<8;
}

inline void pinB11_Input()
{
_GPIOB_(GPIOX_CRH) &= ~((8+2+1)<<12);
_GPIOB_(GPIOX_CRH) |= (4)<<12;
}

inline void pinB11_Input_PU()
{
_GPIOB_(GPIOX_CRH) &= ~((4+2+1)<<12);
_GPIOB_(GPIOX_CRH) |= (8)<<12;
_GPIOB_(GPIOX_ODR) |= (1)<<11;
}

inline void pinB11_Input_PD()
{
_GPIOB_(GPIOX_CRH) &= ~((4+2+1)<<12);
_GPIOB_(GPIOX_CRH) |= (8)<<12;
_GPIOB_(GPIOX_ODR) &= ~(1<<11);
}

inline void pinB11_Analog()
{
_GPIOB_(GPIOX_CRH) &= ~((8+4+2+1)<<12);
}

inline void pinB11_Output()
{
_GPIOB_(GPIOX_CRH) &= ~((8+4+1)<<12);
_GPIOB_(GPIOX_CRH) |= (2)<<12;
}

inline void pinB11_Output_OD()
{
_GPIOB_(GPIOX_CRH) &= ~((8+1)<<12);
_GPIOB_(GPIOX_CRH) |= (2+4)<<12;
}

inline void pinB11_Output_PP_2()
{
_GPIOB_(GPIOX_CRH) &= ~((8+4+1)<<12);
_GPIOB_(GPIOX_CRH) |= (2)<<12;
}

inline void pinB11_Output_PP_10()
{
_GPIOB_(GPIOX_CRH) &= ~((8+4+2)<<12);
_GPIOB_(GPIOX_CRH) |= (1)<<12;
}

inline void pinB11_Output_PP_50()
{
_GPIOB_(GPIOX_CRH) &= ~((8+4)<<12);
_GPIOB_(GPIOX_CRH) |= (2+1)<<12;
}

inline void pinB11_Output_OD_2()
{
_GPIOB_(GPIOX_CRH) &= ~((8+1)<<12);
_GPIOB_(GPIOX_CRH) |= (2+4)<<12;
}

inline void pinB11_Output_OD_10()
{
_GPIOB_(GPIOX_CRH) &= ~((8+2)<<12);
_GPIOB_(GPIOX_CRH) |= (4+1)<<12;
}

inline void pinB11_Output_OD_50()
{
_GPIOB_(GPIOX_CRH) &= ~((8)<<12);
_GPIOB_(GPIOX_CRH) |= (4+2+1)<<12;
}

inline void pinB11_Output_AFPP_2()
{
_GPIOB_(GPIOX_CRH) &= ~((4+1)<<12);
_GPIOB_(GPIOX_CRH) |= (8+2)<<12;
}

inline void pinB11_Output_AFPP_10()
{
_GPIOB_(GPIOX_CRH) &= ~((4+2)<<12);
_GPIOB_(GPIOX_CRH) |= (8+1)<<12;
}

inline void pinB11_Output_AFPP_50()
{
_GPIOB_(GPIOX_CRH) &= ~((4)<<12);
_GPIOB_(GPIOX_CRH) |= (8+2+1)<<12;
}

inline void pinB11_Output_AFOD_2()
{
_GPIOB_(GPIOX_CRH) &= ~((1)<<12);
_GPIOB_(GPIOX_CRH) |= (8+2+4)<<12;
}

inline void pinB11_Output_AFOD_10()
{
_GPIOB_(GPIOX_CRH) &= ~((2)<<12);
_GPIOB_(GPIOX_CRH) |= (8+4+1)<<12;
}

inline void pinB11_Output_AFOD_50()
{
_GPIOB_(GPIOX_CRH) |= (8+4+2+1)<<12;
}

inline void pinB12_Input()
{
_GPIOB_(GPIOX_CRH) &= ~((8+2+1)<<16);
_GPIOB_(GPIOX_CRH) |= (4)<<16;
}

inline void pinB12_Input_PU()
{
_GPIOB_(GPIOX_CRH) &= ~((4+2+1)<<16);
_GPIOB_(GPIOX_CRH) |= (8)<<16;
_GPIOB_(GPIOX_ODR) |= (1)<<12;
}

inline void pinB12_Input_PD()
{
_GPIOB_(GPIOX_CRH) &= ~((4+2+1)<<16);
_GPIOB_(GPIOX_CRH) |= (8)<<16;
_GPIOB_(GPIOX_ODR) &= ~(1<<12);
}

inline void pinB12_Analog()
{
_GPIOB_(GPIOX_CRH) &= ~((8+4+2+1)<<16);
}

inline void pinB12_Output()
{
_GPIOB_(GPIOX_CRH) &= ~((8+4+1)<<16);
_GPIOB_(GPIOX_CRH) |= (2)<<16;
}

inline void pinB12_Output_OD()
{
_GPIOB_(GPIOX_CRH) &= ~((8+1)<<16);
_GPIOB_(GPIOX_CRH) |= (2+4)<<16;
}

inline void pinB12_Output_PP_2()
{
_GPIOB_(GPIOX_CRH) &= ~((8+4+1)<<16);
_GPIOB_(GPIOX_CRH) |= (2)<<16;
}

inline void pinB12_Output_PP_10()
{
_GPIOB_(GPIOX_CRH) &= ~((8+4+2)<<16);
_GPIOB_(GPIOX_CRH) |= (1)<<16;
}

inline void pinB12_Output_PP_50()
{
_GPIOB_(GPIOX_CRH) &= ~((8+4)<<16);
_GPIOB_(GPIOX_CRH) |= (2+1)<<16;
}

inline void pinB12_Output_OD_2()
{
_GPIOB_(GPIOX_CRH) &= ~((8+1)<<16);
_GPIOB_(GPIOX_CRH) |= (2+4)<<16;
}

inline void pinB12_Output_OD_10()
{
_GPIOB_(GPIOX_CRH) &= ~((8+2)<<16);
_GPIOB_(GPIOX_CRH) |= (4+1)<<16;
}

inline void pinB12_Output_OD_50()
{
_GPIOB_(GPIOX_CRH) &= ~((8)<<16);
_GPIOB_(GPIOX_CRH) |= (4+2+1)<<16;
}

inline void pinB12_Output_AFPP_2()
{
_GPIOB_(GPIOX_CRH) &= ~((4+1)<<16);
_GPIOB_(GPIOX_CRH) |= (8+2)<<16;
}

inline void pinB12_Output_AFPP_10()
{
_GPIOB_(GPIOX_CRH) &= ~((4+2)<<16);
_GPIOB_(GPIOX_CRH) |= (8+1)<<16;
}

inline void pinB12_Output_AFPP_50()
{
_GPIOB_(GPIOX_CRH) &= ~((4)<<16);
_GPIOB_(GPIOX_CRH) |= (8+2+1)<<16;
}

inline void pinB12_Output_AFOD_2()
{
_GPIOB_(GPIOX_CRH) &= ~((1)<<16);
_GPIOB_(GPIOX_CRH) |= (8+2+4)<<16;
}

inline void pinB12_Output_AFOD_10()
{
_GPIOB_(GPIOX_CRH) &= ~((2)<<16);
_GPIOB_(GPIOX_CRH) |= (8+4+1)<<16;
}

inline void pinB12_Output_AFOD_50()
{
_GPIOB_(GPIOX_CRH) |= (8+4+2+1)<<16;
}

inline void pinB13_Input()
{
_GPIOB_(GPIOX_CRH) &= ~((8+2+1)<<20);
_GPIOB_(GPIOX_CRH) |= (4)<<20;
}

inline void pinB13_Input_PU()
{
_GPIOB_(GPIOX_CRH) &= ~((4+2+1)<<20);
_GPIOB_(GPIOX_CRH) |= (8)<<20;
_GPIOB_(GPIOX_ODR) |= (1)<<13;
}

inline void pinB13_Input_PD()
{
_GPIOB_(GPIOX_CRH) &= ~((4+2+1)<<20);
_GPIOB_(GPIOX_CRH) |= (8)<<20;
_GPIOB_(GPIOX_ODR) &= ~(1<<13);
}

inline void pinB13_Analog()
{
_GPIOB_(GPIOX_CRH) &= ~((8+4+2+1)<<20);
}

inline void pinB13_Output()
{
_GPIOB_(GPIOX_CRH) &= ~((8+4+1)<<20);
_GPIOB_(GPIOX_CRH) |= (2)<<20;
}

inline void pinB13_Output_OD()
{
_GPIOB_(GPIOX_CRH) &= ~((8+1)<<20);
_GPIOB_(GPIOX_CRH) |= (2+4)<<20;
}

inline void pinB13_Output_PP_2()
{
_GPIOB_(GPIOX_CRH) &= ~((8+4+1)<<20);
_GPIOB_(GPIOX_CRH) |= (2)<<20;
}

inline void pinB13_Output_PP_10()
{
_GPIOB_(GPIOX_CRH) &= ~((8+4+2)<<20);
_GPIOB_(GPIOX_CRH) |= (1)<<20;
}

inline void pinB13_Output_PP_50()
{
_GPIOB_(GPIOX_CRH) &= ~((8+4)<<20);
_GPIOB_(GPIOX_CRH) |= (2+1)<<20;
}

inline void pinB13_Output_OD_2()
{
_GPIOB_(GPIOX_CRH) &= ~((8+1)<<20);
_GPIOB_(GPIOX_CRH) |= (2+4)<<20;
}

inline void pinB13_Output_OD_10()
{
_GPIOB_(GPIOX_CRH) &= ~((8+2)<<20);
_GPIOB_(GPIOX_CRH) |= (4+1)<<20;
}

inline void pinB13_Output_OD_50()
{
_GPIOB_(GPIOX_CRH) &= ~((8)<<20);
_GPIOB_(GPIOX_CRH) |= (4+2+1)<<20;
}

inline void pinB13_Output_AFPP_2()
{
_GPIOB_(GPIOX_CRH) &= ~((4+1)<<20);
_GPIOB_(GPIOX_CRH) |= (8+2)<<20;
}

inline void pinB13_Output_AFPP_10()
{
_GPIOB_(GPIOX_CRH) &= ~((4+2)<<20);
_GPIOB_(GPIOX_CRH) |= (8+1)<<20;
}

inline void pinB13_Output_AFPP_50()
{
_GPIOB_(GPIOX_CRH) &= ~((4)<<20);
_GPIOB_(GPIOX_CRH) |= (8+2+1)<<20;
}

inline void pinB13_Output_AFOD_2()
{
_GPIOB_(GPIOX_CRH) &= ~((1)<<20);
_GPIOB_(GPIOX_CRH) |= (8+2+4)<<20;
}

inline void pinB13_Output_AFOD_10()
{
_GPIOB_(GPIOX_CRH) &= ~((2)<<20);
_GPIOB_(GPIOX_CRH) |= (8+4+1)<<20;
}

inline void pinB13_Output_AFOD_50()
{
_GPIOB_(GPIOX_CRH) |= (8+4+2+1)<<20;
}

inline void pinB14_Input()
{
_GPIOB_(GPIOX_CRH) &= ~((8+2+1)<<24);
_GPIOB_(GPIOX_CRH) |= (4)<<24;
}

inline void pinB14_Input_PU()
{
_GPIOB_(GPIOX_CRH) &= ~((4+2+1)<<24);
_GPIOB_(GPIOX_CRH) |= (8)<<24;
_GPIOB_(GPIOX_ODR) |= (1)<<14;
}

inline void pinB14_Input_PD()
{
_GPIOB_(GPIOX_CRH) &= ~((4+2+1)<<24);
_GPIOB_(GPIOX_CRH) |= (8)<<24;
_GPIOB_(GPIOX_ODR) &= ~(1<<14);
}

inline void pinB14_Analog()
{
_GPIOB_(GPIOX_CRH) &= ~((8+4+2+1)<<24);
}

inline void pinB14_Output()
{
_GPIOB_(GPIOX_CRH) &= ~((8+4+1)<<24);
_GPIOB_(GPIOX_CRH) |= (2)<<24;
}

inline void pinB14_Output_OD()
{
_GPIOB_(GPIOX_CRH) &= ~((8+1)<<24);
_GPIOB_(GPIOX_CRH) |= (2+4)<<24;
}

inline void pinB14_Output_PP_2()
{
_GPIOB_(GPIOX_CRH) &= ~((8+4+1)<<24);
_GPIOB_(GPIOX_CRH) |= (2)<<24;
}

inline void pinB14_Output_PP_10()
{
_GPIOB_(GPIOX_CRH) &= ~((8+4+2)<<24);
_GPIOB_(GPIOX_CRH) |= (1)<<24;
}

inline void pinB14_Output_PP_50()
{
_GPIOB_(GPIOX_CRH) &= ~((8+4)<<24);
_GPIOB_(GPIOX_CRH) |= (2+1)<<24;
}

inline void pinB14_Output_OD_2()
{
_GPIOB_(GPIOX_CRH) &= ~((8+1)<<24);
_GPIOB_(GPIOX_CRH) |= (2+4)<<24;
}

inline void pinB14_Output_OD_10()
{
_GPIOB_(GPIOX_CRH) &= ~((8+2)<<24);
_GPIOB_(GPIOX_CRH) |= (4+1)<<24;
}

inline void pinB14_Output_OD_50()
{
_GPIOB_(GPIOX_CRH) &= ~((8)<<24);
_GPIOB_(GPIOX_CRH) |= (4+2+1)<<24;
}

inline void pinB14_Output_AFPP_2()
{
_GPIOB_(GPIOX_CRH) &= ~((4+1)<<24);
_GPIOB_(GPIOX_CRH) |= (8+2)<<24;
}

inline void pinB14_Output_AFPP_10()
{
_GPIOB_(GPIOX_CRH) &= ~((4+2)<<24);
_GPIOB_(GPIOX_CRH) |= (8+1)<<24;
}

inline void pinB14_Output_AFPP_50()
{
_GPIOB_(GPIOX_CRH) &= ~((4)<<24);
_GPIOB_(GPIOX_CRH) |= (8+2+1)<<24;
}

inline void pinB14_Output_AFOD_2()
{
_GPIOB_(GPIOX_CRH) &= ~((1)<<24);
_GPIOB_(GPIOX_CRH) |= (8+2+4)<<24;
}

inline void pinB14_Output_AFOD_10()
{
_GPIOB_(GPIOX_CRH) &= ~((2)<<24);
_GPIOB_(GPIOX_CRH) |= (8+4+1)<<24;
}

inline void pinB14_Output_AFOD_50()
{
_GPIOB_(GPIOX_CRH) |= (8+4+2+1)<<24;
}

inline void pinB15_Input()
{
_GPIOB_(GPIOX_CRH) &= ~((8+2+1)<<28);
_GPIOB_(GPIOX_CRH) |= (4)<<28;
}

inline void pinB15_Input_PU()
{
_GPIOB_(GPIOX_CRH) &= ~((4+2+1)<<28);
_GPIOB_(GPIOX_CRH) |= (8)<<28;
_GPIOB_(GPIOX_ODR) |= (1)<<15;
}

inline void pinB15_Input_PD()
{
_GPIOB_(GPIOX_CRH) &= ~((4+2+1)<<28);
_GPIOB_(GPIOX_CRH) |= (8)<<28;
_GPIOB_(GPIOX_ODR) &= ~(1<<15);
}

inline void pinB15_Analog()
{
_GPIOB_(GPIOX_CRH) &= ~((8+4+2+1)<<28);
}

inline void pinB15_Output()
{
_GPIOB_(GPIOX_CRH) &= ~((8+4+1)<<28);
_GPIOB_(GPIOX_CRH) |= (2)<<28;
}

inline void pinB15_Output_OD()
{
_GPIOB_(GPIOX_CRH) &= ~((8+1)<<28);
_GPIOB_(GPIOX_CRH) |= (2+4)<<28;
}

inline void pinB15_Output_PP_2()
{
_GPIOB_(GPIOX_CRH) &= ~((8+4+1)<<28);
_GPIOB_(GPIOX_CRH) |= (2)<<28;
}

inline void pinB15_Output_PP_10()
{
_GPIOB_(GPIOX_CRH) &= ~((8+4+2)<<28);
_GPIOB_(GPIOX_CRH) |= (1)<<28;
}

inline void pinB15_Output_PP_50()
{
_GPIOB_(GPIOX_CRH) &= ~((8+4)<<28);
_GPIOB_(GPIOX_CRH) |= (2+1)<<28;
}

inline void pinB15_Output_OD_2()
{
_GPIOB_(GPIOX_CRH) &= ~((8+1)<<28);
_GPIOB_(GPIOX_CRH) |= (2+4)<<28;
}

inline void pinB15_Output_OD_10()
{
_GPIOB_(GPIOX_CRH) &= ~((8+2)<<28);
_GPIOB_(GPIOX_CRH) |= (4+1)<<28;
}

inline void pinB15_Output_OD_50()
{
_GPIOB_(GPIOX_CRH) &= ~((8)<<28);
_GPIOB_(GPIOX_CRH) |= (4+2+1)<<28;
}

inline void pinB15_Output_AFPP_2()
{
_GPIOB_(GPIOX_CRH) &= ~((4+1)<<28);
_GPIOB_(GPIOX_CRH) |= (8+2)<<28;
}

inline void pinB15_Output_AFPP_10()
{
_GPIOB_(GPIOX_CRH) &= ~((4+2)<<28);
_GPIOB_(GPIOX_CRH) |= (8+1)<<28;
}

inline void pinB15_Output_AFPP_50()
{
_GPIOB_(GPIOX_CRH) &= ~((4)<<28);
_GPIOB_(GPIOX_CRH) |= (8+2+1)<<28;
}

inline void pinB15_Output_AFOD_2()
{
_GPIOB_(GPIOX_CRH) &= ~((1)<<28);
_GPIOB_(GPIOX_CRH) |= (8+2+4)<<28;
}

inline void pinB15_Output_AFOD_10()
{
_GPIOB_(GPIOX_CRH) &= ~((2)<<28);
_GPIOB_(GPIOX_CRH) |= (8+4+1)<<28;
}

inline void pinB15_Output_AFOD_50()
{
_GPIOB_(GPIOX_CRH) |= (8+4+2+1)<<28;
}

inline uint8_t readPinB0()
{
return ((_GPIOB_(GPIOX_IDR)>>0) & 1);
}

inline void setPinB0()
{
_GPIOB_(GPIOX_BSRR) = (1<<0);
}

inline void resetPinB0()
{
_GPIOB_(GPIOX_BRR) = (1<<0);
}

inline uint8_t readPinB1()
{
return ((_GPIOB_(GPIOX_IDR)>>1) & 1);
}

inline void setPinB1()
{
_GPIOB_(GPIOX_BSRR) = (1<<1);
}

inline void resetPinB1()
{
_GPIOB_(GPIOX_BRR) = (1<<1);
}

inline uint8_t readPinB2()
{
return ((_GPIOB_(GPIOX_IDR)>>2) & 1);
}

inline void setPinB2()
{
_GPIOB_(GPIOX_BSRR) = (1<<2);
}

inline void resetPinB2()
{
_GPIOB_(GPIOX_BRR) = (1<<2);
}

inline uint8_t readPinB3()
{
return ((_GPIOB_(GPIOX_IDR)>>3) & 1);
}

inline void setPinB3()
{
_GPIOB_(GPIOX_BSRR) = (1<<3);
}

inline void resetPinB3()
{
_GPIOB_(GPIOX_BRR) = (1<<3);
}

inline uint8_t readPinB4()
{
return ((_GPIOB_(GPIOX_IDR)>>4) & 1);
}

inline void setPinB4()
{
_GPIOB_(GPIOX_BSRR) = (1<<4);
}

inline void resetPinB4()
{
_GPIOB_(GPIOX_BRR) = (1<<4);
}

inline uint8_t readPinB5()
{
return ((_GPIOB_(GPIOX_IDR)>>5) & 1);
}

inline void setPinB5()
{
_GPIOB_(GPIOX_BSRR) = (1<<5);
}

inline void resetPinB5()
{
_GPIOB_(GPIOX_BRR) = (1<<5);
}

inline uint8_t readPinB6()
{
return ((_GPIOB_(GPIOX_IDR)>>6) & 1);
}

inline void setPinB6()
{
_GPIOB_(GPIOX_BSRR) = (1<<6);
}

inline void resetPinB6()
{
_GPIOB_(GPIOX_BRR) = (1<<6);
}

inline uint8_t readPinB7()
{
return ((_GPIOB_(GPIOX_IDR)>>7) & 1);
}

inline void setPinB7()
{
_GPIOB_(GPIOX_BSRR) = (1<<7);
}

inline void resetPinB7()
{
_GPIOB_(GPIOX_BRR) = (1<<7);
}

inline uint8_t readPinB8()
{
return ((_GPIOB_(GPIOX_IDR)>>8) & 1);
}

inline void setPinB8()
{
_GPIOB_(GPIOX_BSRR) = (1<<8);
}

inline void resetPinB8()
{
_GPIOB_(GPIOX_BRR) = (1<<8);
}

inline uint8_t readPinB9()
{
return ((_GPIOB_(GPIOX_IDR)>>9) & 1);
}

inline void setPinB9()
{
_GPIOB_(GPIOX_BSRR) = (1<<9);
}

inline void resetPinB9()
{
_GPIOB_(GPIOX_BRR) = (1<<9);
}

inline uint8_t readPinB10()
{
return ((_GPIOB_(GPIOX_IDR)>>10) & 1);
}

inline void setPinB10()
{
_GPIOB_(GPIOX_BSRR) = (1<<10);
}

inline void resetPinB10()
{
_GPIOB_(GPIOX_BRR) = (1<<10);
}

inline uint8_t readPinB11()
{
return ((_GPIOB_(GPIOX_IDR)>>11) & 1);
}

inline void setPinB11()
{
_GPIOB_(GPIOX_BSRR) = (1<<11);
}

inline void resetPinB11()
{
_GPIOB_(GPIOX_BRR) = (1<<11);
}

inline uint8_t readPinB12()
{
return ((_GPIOB_(GPIOX_IDR)>>12) & 1);
}

inline void setPinB12()
{
_GPIOB_(GPIOX_BSRR) = (1<<12);
}

inline void resetPinB12()
{
_GPIOB_(GPIOX_BRR) = (1<<12);
}

inline uint8_t readPinB13()
{
return ((_GPIOB_(GPIOX_IDR)>>13) & 1);
}

inline void setPinB13()
{
_GPIOB_(GPIOX_BSRR) = (1<<13);
}

inline void resetPinB13()
{
_GPIOB_(GPIOX_BRR) = (1<<13);
}

inline uint8_t readPinB14()
{
return ((_GPIOB_(GPIOX_IDR)>>14) & 1);
}

inline void setPinB14()
{
_GPIOB_(GPIOX_BSRR) = (1<<14);
}

inline void resetPinB14()
{
_GPIOB_(GPIOX_BRR) = (1<<14);
}

inline uint8_t readPinB15()
{
return ((_GPIOB_(GPIOX_IDR)>>15) & 1);
}

inline void setPinB15()
{
_GPIOB_(GPIOX_BSRR) = (1<<15);
}

inline void resetPinB15()
{
_GPIOB_(GPIOX_BRR) = (1<<15);
}

inline void pinC0_Input()
{
_GPIOC_(GPIOX_CRL) &= ~((8+2+1)<<0);
_GPIOC_(GPIOX_CRL) |= (4)<<0;
}

inline void pinC0_Input_PU()
{
_GPIOC_(GPIOX_CRL) &= ~((4+2+1)<<0);
_GPIOC_(GPIOX_CRL) |= (8)<<0;
_GPIOC_(GPIOX_ODR) |= (1)<<0;
}

inline void pinC0_Input_PD()
{
_GPIOC_(GPIOX_CRL) &= ~((4+2+1)<<0);
_GPIOC_(GPIOX_CRL) |= (8)<<0;
_GPIOC_(GPIOX_ODR) &= ~(1<<0);
}

inline void pinC0_Analog()
{
_GPIOC_(GPIOX_CRL) &= ~((8+4+2+1)<<0);
}

inline void pinC0_Output()
{
_GPIOC_(GPIOX_CRL) &= ~((8+4+1)<<0);
_GPIOC_(GPIOX_CRL) |= (2)<<0;
}

inline void pinC0_Output_OD()
{
_GPIOC_(GPIOX_CRL) &= ~((8+1)<<0);
_GPIOC_(GPIOX_CRL) |= (2+4)<<0;
}

inline void pinC0_Output_PP_2()
{
_GPIOC_(GPIOX_CRL) &= ~((8+4+1)<<0);
_GPIOC_(GPIOX_CRL) |= (2)<<0;
}

inline void pinC0_Output_PP_10()
{
_GPIOC_(GPIOX_CRL) &= ~((8+4+2)<<0);
_GPIOC_(GPIOX_CRL) |= (1)<<0;
}

inline void pinC0_Output_PP_50()
{
_GPIOC_(GPIOX_CRL) &= ~((8+4)<<0);
_GPIOC_(GPIOX_CRL) |= (2+1)<<0;
}

inline void pinC0_Output_OD_2()
{
_GPIOC_(GPIOX_CRL) &= ~((8+1)<<0);
_GPIOC_(GPIOX_CRL) |= (2+4)<<0;
}

inline void pinC0_Output_OD_10()
{
_GPIOC_(GPIOX_CRL) &= ~((8+2)<<0);
_GPIOC_(GPIOX_CRL) |= (4+1)<<0;
}

inline void pinC0_Output_OD_50()
{
_GPIOC_(GPIOX_CRL) &= ~((8)<<0);
_GPIOC_(GPIOX_CRL) |= (4+2+1)<<0;
}

inline void pinC0_Output_AFPP_2()
{
_GPIOC_(GPIOX_CRL) &= ~((4+1)<<0);
_GPIOC_(GPIOX_CRL) |= (8+2)<<0;
}

inline void pinC0_Output_AFPP_10()
{
_GPIOC_(GPIOX_CRL) &= ~((4+2)<<0);
_GPIOC_(GPIOX_CRL) |= (8+1)<<0;
}

inline void pinC0_Output_AFPP_50()
{
_GPIOC_(GPIOX_CRL) &= ~((4)<<0);
_GPIOC_(GPIOX_CRL) |= (8+2+1)<<0;
}

inline void pinC0_Output_AFOD_2()
{
_GPIOC_(GPIOX_CRL) &= ~((1)<<0);
_GPIOC_(GPIOX_CRL) |= (8+2+4)<<0;
}

inline void pinC0_Output_AFOD_10()
{
_GPIOC_(GPIOX_CRL) &= ~((2)<<0);
_GPIOC_(GPIOX_CRL) |= (8+4+1)<<0;
}

inline void pinC0_Output_AFOD_50()
{
_GPIOC_(GPIOX_CRL) |= (8+4+2+1)<<0;
}

inline void pinC1_Input()
{
_GPIOC_(GPIOX_CRL) &= ~((8+2+1)<<4);
_GPIOC_(GPIOX_CRL) |= (4)<<4;
}

inline void pinC1_Input_PU()
{
_GPIOC_(GPIOX_CRL) &= ~((4+2+1)<<4);
_GPIOC_(GPIOX_CRL) |= (8)<<4;
_GPIOC_(GPIOX_ODR) |= (1)<<1;
}

inline void pinC1_Input_PD()
{
_GPIOC_(GPIOX_CRL) &= ~((4+2+1)<<4);
_GPIOC_(GPIOX_CRL) |= (8)<<4;
_GPIOC_(GPIOX_ODR) &= ~(1<<1);
}

inline void pinC1_Analog()
{
_GPIOC_(GPIOX_CRL) &= ~((8+4+2+1)<<4);
}

inline void pinC1_Output()
{
_GPIOC_(GPIOX_CRL) &= ~((8+4+1)<<4);
_GPIOC_(GPIOX_CRL) |= (2)<<4;
}

inline void pinC1_Output_OD()
{
_GPIOC_(GPIOX_CRL) &= ~((8+1)<<4);
_GPIOC_(GPIOX_CRL) |= (2+4)<<4;
}

inline void pinC1_Output_PP_2()
{
_GPIOC_(GPIOX_CRL) &= ~((8+4+1)<<4);
_GPIOC_(GPIOX_CRL) |= (2)<<4;
}

inline void pinC1_Output_PP_10()
{
_GPIOC_(GPIOX_CRL) &= ~((8+4+2)<<4);
_GPIOC_(GPIOX_CRL) |= (1)<<4;
}

inline void pinC1_Output_PP_50()
{
_GPIOC_(GPIOX_CRL) &= ~((8+4)<<4);
_GPIOC_(GPIOX_CRL) |= (2+1)<<4;
}

inline void pinC1_Output_OD_2()
{
_GPIOC_(GPIOX_CRL) &= ~((8+1)<<4);
_GPIOC_(GPIOX_CRL) |= (2+4)<<4;
}

inline void pinC1_Output_OD_10()
{
_GPIOC_(GPIOX_CRL) &= ~((8+2)<<4);
_GPIOC_(GPIOX_CRL) |= (4+1)<<4;
}

inline void pinC1_Output_OD_50()
{
_GPIOC_(GPIOX_CRL) &= ~((8)<<4);
_GPIOC_(GPIOX_CRL) |= (4+2+1)<<4;
}

inline void pinC1_Output_AFPP_2()
{
_GPIOC_(GPIOX_CRL) &= ~((4+1)<<4);
_GPIOC_(GPIOX_CRL) |= (8+2)<<4;
}

inline void pinC1_Output_AFPP_10()
{
_GPIOC_(GPIOX_CRL) &= ~((4+2)<<4);
_GPIOC_(GPIOX_CRL) |= (8+1)<<4;
}

inline void pinC1_Output_AFPP_50()
{
_GPIOC_(GPIOX_CRL) &= ~((4)<<4);
_GPIOC_(GPIOX_CRL) |= (8+2+1)<<4;
}

inline void pinC1_Output_AFOD_2()
{
_GPIOC_(GPIOX_CRL) &= ~((1)<<4);
_GPIOC_(GPIOX_CRL) |= (8+2+4)<<4;
}

inline void pinC1_Output_AFOD_10()
{
_GPIOC_(GPIOX_CRL) &= ~((2)<<4);
_GPIOC_(GPIOX_CRL) |= (8+4+1)<<4;
}

inline void pinC1_Output_AFOD_50()
{
_GPIOC_(GPIOX_CRL) |= (8+4+2+1)<<4;
}

inline void pinC2_Input()
{
_GPIOC_(GPIOX_CRL) &= ~((8+2+1)<<8);
_GPIOC_(GPIOX_CRL) |= (4)<<8;
}

inline void pinC2_Input_PU()
{
_GPIOC_(GPIOX_CRL) &= ~((4+2+1)<<8);
_GPIOC_(GPIOX_CRL) |= (8)<<8;
_GPIOC_(GPIOX_ODR) |= (1)<<2;
}

inline void pinC2_Input_PD()
{
_GPIOC_(GPIOX_CRL) &= ~((4+2+1)<<8);
_GPIOC_(GPIOX_CRL) |= (8)<<8;
_GPIOC_(GPIOX_ODR) &= ~(1<<2);
}

inline void pinC2_Analog()
{
_GPIOC_(GPIOX_CRL) &= ~((8+4+2+1)<<8);
}

inline void pinC2_Output()
{
_GPIOC_(GPIOX_CRL) &= ~((8+4+1)<<8);
_GPIOC_(GPIOX_CRL) |= (2)<<8;
}

inline void pinC2_Output_OD()
{
_GPIOC_(GPIOX_CRL) &= ~((8+1)<<8);
_GPIOC_(GPIOX_CRL) |= (2+4)<<8;
}

inline void pinC2_Output_PP_2()
{
_GPIOC_(GPIOX_CRL) &= ~((8+4+1)<<8);
_GPIOC_(GPIOX_CRL) |= (2)<<8;
}

inline void pinC2_Output_PP_10()
{
_GPIOC_(GPIOX_CRL) &= ~((8+4+2)<<8);
_GPIOC_(GPIOX_CRL) |= (1)<<8;
}

inline void pinC2_Output_PP_50()
{
_GPIOC_(GPIOX_CRL) &= ~((8+4)<<8);
_GPIOC_(GPIOX_CRL) |= (2+1)<<8;
}

inline void pinC2_Output_OD_2()
{
_GPIOC_(GPIOX_CRL) &= ~((8+1)<<8);
_GPIOC_(GPIOX_CRL) |= (2+4)<<8;
}

inline void pinC2_Output_OD_10()
{
_GPIOC_(GPIOX_CRL) &= ~((8+2)<<8);
_GPIOC_(GPIOX_CRL) |= (4+1)<<8;
}

inline void pinC2_Output_OD_50()
{
_GPIOC_(GPIOX_CRL) &= ~((8)<<8);
_GPIOC_(GPIOX_CRL) |= (4+2+1)<<8;
}

inline void pinC2_Output_AFPP_2()
{
_GPIOC_(GPIOX_CRL) &= ~((4+1)<<8);
_GPIOC_(GPIOX_CRL) |= (8+2)<<8;
}

inline void pinC2_Output_AFPP_10()
{
_GPIOC_(GPIOX_CRL) &= ~((4+2)<<8);
_GPIOC_(GPIOX_CRL) |= (8+1)<<8;
}

inline void pinC2_Output_AFPP_50()
{
_GPIOC_(GPIOX_CRL) &= ~((4)<<8);
_GPIOC_(GPIOX_CRL) |= (8+2+1)<<8;
}

inline void pinC2_Output_AFOD_2()
{
_GPIOC_(GPIOX_CRL) &= ~((1)<<8);
_GPIOC_(GPIOX_CRL) |= (8+2+4)<<8;
}

inline void pinC2_Output_AFOD_10()
{
_GPIOC_(GPIOX_CRL) &= ~((2)<<8);
_GPIOC_(GPIOX_CRL) |= (8+4+1)<<8;
}

inline void pinC2_Output_AFOD_50()
{
_GPIOC_(GPIOX_CRL) |= (8+4+2+1)<<8;
}

inline void pinC3_Input()
{
_GPIOC_(GPIOX_CRL) &= ~((8+2+1)<<12);
_GPIOC_(GPIOX_CRL) |= (4)<<12;
}

inline void pinC3_Input_PU()
{
_GPIOC_(GPIOX_CRL) &= ~((4+2+1)<<12);
_GPIOC_(GPIOX_CRL) |= (8)<<12;
_GPIOC_(GPIOX_ODR) |= (1)<<3;
}

inline void pinC3_Input_PD()
{
_GPIOC_(GPIOX_CRL) &= ~((4+2+1)<<12);
_GPIOC_(GPIOX_CRL) |= (8)<<12;
_GPIOC_(GPIOX_ODR) &= ~(1<<3);
}

inline void pinC3_Analog()
{
_GPIOC_(GPIOX_CRL) &= ~((8+4+2+1)<<12);
}

inline void pinC3_Output()
{
_GPIOC_(GPIOX_CRL) &= ~((8+4+1)<<12);
_GPIOC_(GPIOX_CRL) |= (2)<<12;
}

inline void pinC3_Output_OD()
{
_GPIOC_(GPIOX_CRL) &= ~((8+1)<<12);
_GPIOC_(GPIOX_CRL) |= (2+4)<<12;
}

inline void pinC3_Output_PP_2()
{
_GPIOC_(GPIOX_CRL) &= ~((8+4+1)<<12);
_GPIOC_(GPIOX_CRL) |= (2)<<12;
}

inline void pinC3_Output_PP_10()
{
_GPIOC_(GPIOX_CRL) &= ~((8+4+2)<<12);
_GPIOC_(GPIOX_CRL) |= (1)<<12;
}

inline void pinC3_Output_PP_50()
{
_GPIOC_(GPIOX_CRL) &= ~((8+4)<<12);
_GPIOC_(GPIOX_CRL) |= (2+1)<<12;
}

inline void pinC3_Output_OD_2()
{
_GPIOC_(GPIOX_CRL) &= ~((8+1)<<12);
_GPIOC_(GPIOX_CRL) |= (2+4)<<12;
}

inline void pinC3_Output_OD_10()
{
_GPIOC_(GPIOX_CRL) &= ~((8+2)<<12);
_GPIOC_(GPIOX_CRL) |= (4+1)<<12;
}

inline void pinC3_Output_OD_50()
{
_GPIOC_(GPIOX_CRL) &= ~((8)<<12);
_GPIOC_(GPIOX_CRL) |= (4+2+1)<<12;
}

inline void pinC3_Output_AFPP_2()
{
_GPIOC_(GPIOX_CRL) &= ~((4+1)<<12);
_GPIOC_(GPIOX_CRL) |= (8+2)<<12;
}

inline void pinC3_Output_AFPP_10()
{
_GPIOC_(GPIOX_CRL) &= ~((4+2)<<12);
_GPIOC_(GPIOX_CRL) |= (8+1)<<12;
}

inline void pinC3_Output_AFPP_50()
{
_GPIOC_(GPIOX_CRL) &= ~((4)<<12);
_GPIOC_(GPIOX_CRL) |= (8+2+1)<<12;
}

inline void pinC3_Output_AFOD_2()
{
_GPIOC_(GPIOX_CRL) &= ~((1)<<12);
_GPIOC_(GPIOX_CRL) |= (8+2+4)<<12;
}

inline void pinC3_Output_AFOD_10()
{
_GPIOC_(GPIOX_CRL) &= ~((2)<<12);
_GPIOC_(GPIOX_CRL) |= (8+4+1)<<12;
}

inline void pinC3_Output_AFOD_50()
{
_GPIOC_(GPIOX_CRL) |= (8+4+2+1)<<12;
}

inline void pinC4_Input()
{
_GPIOC_(GPIOX_CRL) &= ~((8+2+1)<<16);
_GPIOC_(GPIOX_CRL) |= (4)<<16;
}

inline void pinC4_Input_PU()
{
_GPIOC_(GPIOX_CRL) &= ~((4+2+1)<<16);
_GPIOC_(GPIOX_CRL) |= (8)<<16;
_GPIOC_(GPIOX_ODR) |= (1)<<4;
}

inline void pinC4_Input_PD()
{
_GPIOC_(GPIOX_CRL) &= ~((4+2+1)<<16);
_GPIOC_(GPIOX_CRL) |= (8)<<16;
_GPIOC_(GPIOX_ODR) &= ~(1<<4);
}

inline void pinC4_Analog()
{
_GPIOC_(GPIOX_CRL) &= ~((8+4+2+1)<<16);
}

inline void pinC4_Output()
{
_GPIOC_(GPIOX_CRL) &= ~((8+4+1)<<16);
_GPIOC_(GPIOX_CRL) |= (2)<<16;
}

inline void pinC4_Output_OD()
{
_GPIOC_(GPIOX_CRL) &= ~((8+1)<<16);
_GPIOC_(GPIOX_CRL) |= (2+4)<<16;
}

inline void pinC4_Output_PP_2()
{
_GPIOC_(GPIOX_CRL) &= ~((8+4+1)<<16);
_GPIOC_(GPIOX_CRL) |= (2)<<16;
}

inline void pinC4_Output_PP_10()
{
_GPIOC_(GPIOX_CRL) &= ~((8+4+2)<<16);
_GPIOC_(GPIOX_CRL) |= (1)<<16;
}

inline void pinC4_Output_PP_50()
{
_GPIOC_(GPIOX_CRL) &= ~((8+4)<<16);
_GPIOC_(GPIOX_CRL) |= (2+1)<<16;
}

inline void pinC4_Output_OD_2()
{
_GPIOC_(GPIOX_CRL) &= ~((8+1)<<16);
_GPIOC_(GPIOX_CRL) |= (2+4)<<16;
}

inline void pinC4_Output_OD_10()
{
_GPIOC_(GPIOX_CRL) &= ~((8+2)<<16);
_GPIOC_(GPIOX_CRL) |= (4+1)<<16;
}

inline void pinC4_Output_OD_50()
{
_GPIOC_(GPIOX_CRL) &= ~((8)<<16);
_GPIOC_(GPIOX_CRL) |= (4+2+1)<<16;
}

inline void pinC4_Output_AFPP_2()
{
_GPIOC_(GPIOX_CRL) &= ~((4+1)<<16);
_GPIOC_(GPIOX_CRL) |= (8+2)<<16;
}

inline void pinC4_Output_AFPP_10()
{
_GPIOC_(GPIOX_CRL) &= ~((4+2)<<16);
_GPIOC_(GPIOX_CRL) |= (8+1)<<16;
}

inline void pinC4_Output_AFPP_50()
{
_GPIOC_(GPIOX_CRL) &= ~((4)<<16);
_GPIOC_(GPIOX_CRL) |= (8+2+1)<<16;
}

inline void pinC4_Output_AFOD_2()
{
_GPIOC_(GPIOX_CRL) &= ~((1)<<16);
_GPIOC_(GPIOX_CRL) |= (8+2+4)<<16;
}

inline void pinC4_Output_AFOD_10()
{
_GPIOC_(GPIOX_CRL) &= ~((2)<<16);
_GPIOC_(GPIOX_CRL) |= (8+4+1)<<16;
}

inline void pinC4_Output_AFOD_50()
{
_GPIOC_(GPIOX_CRL) |= (8+4+2+1)<<16;
}

inline void pinC5_Input()
{
_GPIOC_(GPIOX_CRL) &= ~((8+2+1)<<20);
_GPIOC_(GPIOX_CRL) |= (4)<<20;
}

inline void pinC5_Input_PU()
{
_GPIOC_(GPIOX_CRL) &= ~((4+2+1)<<20);
_GPIOC_(GPIOX_CRL) |= (8)<<20;
_GPIOC_(GPIOX_ODR) |= (1)<<5;
}

inline void pinC5_Input_PD()
{
_GPIOC_(GPIOX_CRL) &= ~((4+2+1)<<20);
_GPIOC_(GPIOX_CRL) |= (8)<<20;
_GPIOC_(GPIOX_ODR) &= ~(1<<5);
}

inline void pinC5_Analog()
{
_GPIOC_(GPIOX_CRL) &= ~((8+4+2+1)<<20);
}

inline void pinC5_Output()
{
_GPIOC_(GPIOX_CRL) &= ~((8+4+1)<<20);
_GPIOC_(GPIOX_CRL) |= (2)<<20;
}

inline void pinC5_Output_OD()
{
_GPIOC_(GPIOX_CRL) &= ~((8+1)<<20);
_GPIOC_(GPIOX_CRL) |= (2+4)<<20;
}

inline void pinC5_Output_PP_2()
{
_GPIOC_(GPIOX_CRL) &= ~((8+4+1)<<20);
_GPIOC_(GPIOX_CRL) |= (2)<<20;
}

inline void pinC5_Output_PP_10()
{
_GPIOC_(GPIOX_CRL) &= ~((8+4+2)<<20);
_GPIOC_(GPIOX_CRL) |= (1)<<20;
}

inline void pinC5_Output_PP_50()
{
_GPIOC_(GPIOX_CRL) &= ~((8+4)<<20);
_GPIOC_(GPIOX_CRL) |= (2+1)<<20;
}

inline void pinC5_Output_OD_2()
{
_GPIOC_(GPIOX_CRL) &= ~((8+1)<<20);
_GPIOC_(GPIOX_CRL) |= (2+4)<<20;
}

inline void pinC5_Output_OD_10()
{
_GPIOC_(GPIOX_CRL) &= ~((8+2)<<20);
_GPIOC_(GPIOX_CRL) |= (4+1)<<20;
}

inline void pinC5_Output_OD_50()
{
_GPIOC_(GPIOX_CRL) &= ~((8)<<20);
_GPIOC_(GPIOX_CRL) |= (4+2+1)<<20;
}

inline void pinC5_Output_AFPP_2()
{
_GPIOC_(GPIOX_CRL) &= ~((4+1)<<20);
_GPIOC_(GPIOX_CRL) |= (8+2)<<20;
}

inline void pinC5_Output_AFPP_10()
{
_GPIOC_(GPIOX_CRL) &= ~((4+2)<<20);
_GPIOC_(GPIOX_CRL) |= (8+1)<<20;
}

inline void pinC5_Output_AFPP_50()
{
_GPIOC_(GPIOX_CRL) &= ~((4)<<20);
_GPIOC_(GPIOX_CRL) |= (8+2+1)<<20;
}

inline void pinC5_Output_AFOD_2()
{
_GPIOC_(GPIOX_CRL) &= ~((1)<<20);
_GPIOC_(GPIOX_CRL) |= (8+2+4)<<20;
}

inline void pinC5_Output_AFOD_10()
{
_GPIOC_(GPIOX_CRL) &= ~((2)<<20);
_GPIOC_(GPIOX_CRL) |= (8+4+1)<<20;
}

inline void pinC5_Output_AFOD_50()
{
_GPIOC_(GPIOX_CRL) |= (8+4+2+1)<<20;
}

inline void pinC6_Input()
{
_GPIOC_(GPIOX_CRL) &= ~((8+2+1)<<24);
_GPIOC_(GPIOX_CRL) |= (4)<<24;
}

inline void pinC6_Input_PU()
{
_GPIOC_(GPIOX_CRL) &= ~((4+2+1)<<24);
_GPIOC_(GPIOX_CRL) |= (8)<<24;
_GPIOC_(GPIOX_ODR) |= (1)<<6;
}

inline void pinC6_Input_PD()
{
_GPIOC_(GPIOX_CRL) &= ~((4+2+1)<<24);
_GPIOC_(GPIOX_CRL) |= (8)<<24;
_GPIOC_(GPIOX_ODR) &= ~(1<<6);
}

inline void pinC6_Analog()
{
_GPIOC_(GPIOX_CRL) &= ~((8+4+2+1)<<24);
}

inline void pinC6_Output()
{
_GPIOC_(GPIOX_CRL) &= ~((8+4+1)<<24);
_GPIOC_(GPIOX_CRL) |= (2)<<24;
}

inline void pinC6_Output_OD()
{
_GPIOC_(GPIOX_CRL) &= ~((8+1)<<24);
_GPIOC_(GPIOX_CRL) |= (2+4)<<24;
}

inline void pinC6_Output_PP_2()
{
_GPIOC_(GPIOX_CRL) &= ~((8+4+1)<<24);
_GPIOC_(GPIOX_CRL) |= (2)<<24;
}

inline void pinC6_Output_PP_10()
{
_GPIOC_(GPIOX_CRL) &= ~((8+4+2)<<24);
_GPIOC_(GPIOX_CRL) |= (1)<<24;
}

inline void pinC6_Output_PP_50()
{
_GPIOC_(GPIOX_CRL) &= ~((8+4)<<24);
_GPIOC_(GPIOX_CRL) |= (2+1)<<24;
}

inline void pinC6_Output_OD_2()
{
_GPIOC_(GPIOX_CRL) &= ~((8+1)<<24);
_GPIOC_(GPIOX_CRL) |= (2+4)<<24;
}

inline void pinC6_Output_OD_10()
{
_GPIOC_(GPIOX_CRL) &= ~((8+2)<<24);
_GPIOC_(GPIOX_CRL) |= (4+1)<<24;
}

inline void pinC6_Output_OD_50()
{
_GPIOC_(GPIOX_CRL) &= ~((8)<<24);
_GPIOC_(GPIOX_CRL) |= (4+2+1)<<24;
}

inline void pinC6_Output_AFPP_2()
{
_GPIOC_(GPIOX_CRL) &= ~((4+1)<<24);
_GPIOC_(GPIOX_CRL) |= (8+2)<<24;
}

inline void pinC6_Output_AFPP_10()
{
_GPIOC_(GPIOX_CRL) &= ~((4+2)<<24);
_GPIOC_(GPIOX_CRL) |= (8+1)<<24;
}

inline void pinC6_Output_AFPP_50()
{
_GPIOC_(GPIOX_CRL) &= ~((4)<<24);
_GPIOC_(GPIOX_CRL) |= (8+2+1)<<24;
}

inline void pinC6_Output_AFOD_2()
{
_GPIOC_(GPIOX_CRL) &= ~((1)<<24);
_GPIOC_(GPIOX_CRL) |= (8+2+4)<<24;
}

inline void pinC6_Output_AFOD_10()
{
_GPIOC_(GPIOX_CRL) &= ~((2)<<24);
_GPIOC_(GPIOX_CRL) |= (8+4+1)<<24;
}

inline void pinC6_Output_AFOD_50()
{
_GPIOC_(GPIOX_CRL) |= (8+4+2+1)<<24;
}

inline void pinC7_Input()
{
_GPIOC_(GPIOX_CRL) &= ~((8+2+1)<<28);
_GPIOC_(GPIOX_CRL) |= (4)<<28;
}

inline void pinC7_Input_PU()
{
_GPIOC_(GPIOX_CRL) &= ~((4+2+1)<<28);
_GPIOC_(GPIOX_CRL) |= (8)<<28;
_GPIOC_(GPIOX_ODR) |= (1)<<7;
}

inline void pinC7_Input_PD()
{
_GPIOC_(GPIOX_CRL) &= ~((4+2+1)<<28);
_GPIOC_(GPIOX_CRL) |= (8)<<28;
_GPIOC_(GPIOX_ODR) &= ~(1<<7);
}

inline void pinC7_Analog()
{
_GPIOC_(GPIOX_CRL) &= ~((8+4+2+1)<<28);
}

inline void pinC7_Output()
{
_GPIOC_(GPIOX_CRL) &= ~((8+4+1)<<28);
_GPIOC_(GPIOX_CRL) |= (2)<<28;
}

inline void pinC7_Output_OD()
{
_GPIOC_(GPIOX_CRL) &= ~((8+1)<<28);
_GPIOC_(GPIOX_CRL) |= (2+4)<<28;
}

inline void pinC7_Output_PP_2()
{
_GPIOC_(GPIOX_CRL) &= ~((8+4+1)<<28);
_GPIOC_(GPIOX_CRL) |= (2)<<28;
}

inline void pinC7_Output_PP_10()
{
_GPIOC_(GPIOX_CRL) &= ~((8+4+2)<<28);
_GPIOC_(GPIOX_CRL) |= (1)<<28;
}

inline void pinC7_Output_PP_50()
{
_GPIOC_(GPIOX_CRL) &= ~((8+4)<<28);
_GPIOC_(GPIOX_CRL) |= (2+1)<<28;
}

inline void pinC7_Output_OD_2()
{
_GPIOC_(GPIOX_CRL) &= ~((8+1)<<28);
_GPIOC_(GPIOX_CRL) |= (2+4)<<28;
}

inline void pinC7_Output_OD_10()
{
_GPIOC_(GPIOX_CRL) &= ~((8+2)<<28);
_GPIOC_(GPIOX_CRL) |= (4+1)<<28;
}

inline void pinC7_Output_OD_50()
{
_GPIOC_(GPIOX_CRL) &= ~((8)<<28);
_GPIOC_(GPIOX_CRL) |= (4+2+1)<<28;
}

inline void pinC7_Output_AFPP_2()
{
_GPIOC_(GPIOX_CRL) &= ~((4+1)<<28);
_GPIOC_(GPIOX_CRL) |= (8+2)<<28;
}

inline void pinC7_Output_AFPP_10()
{
_GPIOC_(GPIOX_CRL) &= ~((4+2)<<28);
_GPIOC_(GPIOX_CRL) |= (8+1)<<28;
}

inline void pinC7_Output_AFPP_50()
{
_GPIOC_(GPIOX_CRL) &= ~((4)<<28);
_GPIOC_(GPIOX_CRL) |= (8+2+1)<<28;
}

inline void pinC7_Output_AFOD_2()
{
_GPIOC_(GPIOX_CRL) &= ~((1)<<28);
_GPIOC_(GPIOX_CRL) |= (8+2+4)<<28;
}

inline void pinC7_Output_AFOD_10()
{
_GPIOC_(GPIOX_CRL) &= ~((2)<<28);
_GPIOC_(GPIOX_CRL) |= (8+4+1)<<28;
}

inline void pinC7_Output_AFOD_50()
{
_GPIOC_(GPIOX_CRL) |= (8+4+2+1)<<28;
}

inline void pinC8_Input()
{
_GPIOC_(GPIOX_CRH) &= ~((8+2+1)<<0);
_GPIOC_(GPIOX_CRH) |= (4)<<0;
}

inline void pinC8_Input_PU()
{
_GPIOC_(GPIOX_CRH) &= ~((4+2+1)<<0);
_GPIOC_(GPIOX_CRH) |= (8)<<0;
_GPIOC_(GPIOX_ODR) |= (1)<<8;
}

inline void pinC8_Input_PD()
{
_GPIOC_(GPIOX_CRH) &= ~((4+2+1)<<0);
_GPIOC_(GPIOX_CRH) |= (8)<<0;
_GPIOC_(GPIOX_ODR) &= ~(1<<8);
}

inline void pinC8_Analog()
{
_GPIOC_(GPIOX_CRH) &= ~((8+4+2+1)<<0);
}

inline void pinC8_Output()
{
_GPIOC_(GPIOX_CRH) &= ~((8+4+1)<<0);
_GPIOC_(GPIOX_CRH) |= (2)<<0;
}

inline void pinC8_Output_OD()
{
_GPIOC_(GPIOX_CRH) &= ~((8+1)<<0);
_GPIOC_(GPIOX_CRH) |= (2+4)<<0;
}

inline void pinC8_Output_PP_2()
{
_GPIOC_(GPIOX_CRH) &= ~((8+4+1)<<0);
_GPIOC_(GPIOX_CRH) |= (2)<<0;
}

inline void pinC8_Output_PP_10()
{
_GPIOC_(GPIOX_CRH) &= ~((8+4+2)<<0);
_GPIOC_(GPIOX_CRH) |= (1)<<0;
}

inline void pinC8_Output_PP_50()
{
_GPIOC_(GPIOX_CRH) &= ~((8+4)<<0);
_GPIOC_(GPIOX_CRH) |= (2+1)<<0;
}

inline void pinC8_Output_OD_2()
{
_GPIOC_(GPIOX_CRH) &= ~((8+1)<<0);
_GPIOC_(GPIOX_CRH) |= (2+4)<<0;
}

inline void pinC8_Output_OD_10()
{
_GPIOC_(GPIOX_CRH) &= ~((8+2)<<0);
_GPIOC_(GPIOX_CRH) |= (4+1)<<0;
}

inline void pinC8_Output_OD_50()
{
_GPIOC_(GPIOX_CRH) &= ~((8)<<0);
_GPIOC_(GPIOX_CRH) |= (4+2+1)<<0;
}

inline void pinC8_Output_AFPP_2()
{
_GPIOC_(GPIOX_CRH) &= ~((4+1)<<0);
_GPIOC_(GPIOX_CRH) |= (8+2)<<0;
}

inline void pinC8_Output_AFPP_10()
{
_GPIOC_(GPIOX_CRH) &= ~((4+2)<<0);
_GPIOC_(GPIOX_CRH) |= (8+1)<<0;
}

inline void pinC8_Output_AFPP_50()
{
_GPIOC_(GPIOX_CRH) &= ~((4)<<0);
_GPIOC_(GPIOX_CRH) |= (8+2+1)<<0;
}

inline void pinC8_Output_AFOD_2()
{
_GPIOC_(GPIOX_CRH) &= ~((1)<<0);
_GPIOC_(GPIOX_CRH) |= (8+2+4)<<0;
}

inline void pinC8_Output_AFOD_10()
{
_GPIOC_(GPIOX_CRH) &= ~((2)<<0);
_GPIOC_(GPIOX_CRH) |= (8+4+1)<<0;
}

inline void pinC8_Output_AFOD_50()
{
_GPIOC_(GPIOX_CRH) |= (8+4+2+1)<<0;
}

inline void pinC9_Input()
{
_GPIOC_(GPIOX_CRH) &= ~((8+2+1)<<4);
_GPIOC_(GPIOX_CRH) |= (4)<<4;
}

inline void pinC9_Input_PU()
{
_GPIOC_(GPIOX_CRH) &= ~((4+2+1)<<4);
_GPIOC_(GPIOX_CRH) |= (8)<<4;
_GPIOC_(GPIOX_ODR) |= (1)<<9;
}

inline void pinC9_Input_PD()
{
_GPIOC_(GPIOX_CRH) &= ~((4+2+1)<<4);
_GPIOC_(GPIOX_CRH) |= (8)<<4;
_GPIOC_(GPIOX_ODR) &= ~(1<<9);
}

inline void pinC9_Analog()
{
_GPIOC_(GPIOX_CRH) &= ~((8+4+2+1)<<4);
}

inline void pinC9_Output()
{
_GPIOC_(GPIOX_CRH) &= ~((8+4+1)<<4);
_GPIOC_(GPIOX_CRH) |= (2)<<4;
}

inline void pinC9_Output_OD()
{
_GPIOC_(GPIOX_CRH) &= ~((8+1)<<4);
_GPIOC_(GPIOX_CRH) |= (2+4)<<4;
}

inline void pinC9_Output_PP_2()
{
_GPIOC_(GPIOX_CRH) &= ~((8+4+1)<<4);
_GPIOC_(GPIOX_CRH) |= (2)<<4;
}

inline void pinC9_Output_PP_10()
{
_GPIOC_(GPIOX_CRH) &= ~((8+4+2)<<4);
_GPIOC_(GPIOX_CRH) |= (1)<<4;
}

inline void pinC9_Output_PP_50()
{
_GPIOC_(GPIOX_CRH) &= ~((8+4)<<4);
_GPIOC_(GPIOX_CRH) |= (2+1)<<4;
}

inline void pinC9_Output_OD_2()
{
_GPIOC_(GPIOX_CRH) &= ~((8+1)<<4);
_GPIOC_(GPIOX_CRH) |= (2+4)<<4;
}

inline void pinC9_Output_OD_10()
{
_GPIOC_(GPIOX_CRH) &= ~((8+2)<<4);
_GPIOC_(GPIOX_CRH) |= (4+1)<<4;
}

inline void pinC9_Output_OD_50()
{
_GPIOC_(GPIOX_CRH) &= ~((8)<<4);
_GPIOC_(GPIOX_CRH) |= (4+2+1)<<4;
}

inline void pinC9_Output_AFPP_2()
{
_GPIOC_(GPIOX_CRH) &= ~((4+1)<<4);
_GPIOC_(GPIOX_CRH) |= (8+2)<<4;
}

inline void pinC9_Output_AFPP_10()
{
_GPIOC_(GPIOX_CRH) &= ~((4+2)<<4);
_GPIOC_(GPIOX_CRH) |= (8+1)<<4;
}

inline void pinC9_Output_AFPP_50()
{
_GPIOC_(GPIOX_CRH) &= ~((4)<<4);
_GPIOC_(GPIOX_CRH) |= (8+2+1)<<4;
}

inline void pinC9_Output_AFOD_2()
{
_GPIOC_(GPIOX_CRH) &= ~((1)<<4);
_GPIOC_(GPIOX_CRH) |= (8+2+4)<<4;
}

inline void pinC9_Output_AFOD_10()
{
_GPIOC_(GPIOX_CRH) &= ~((2)<<4);
_GPIOC_(GPIOX_CRH) |= (8+4+1)<<4;
}

inline void pinC9_Output_AFOD_50()
{
_GPIOC_(GPIOX_CRH) |= (8+4+2+1)<<4;
}

inline void pinC10_Input()
{
_GPIOC_(GPIOX_CRH) &= ~((8+2+1)<<8);
_GPIOC_(GPIOX_CRH) |= (4)<<8;
}

inline void pinC10_Input_PU()
{
_GPIOC_(GPIOX_CRH) &= ~((4+2+1)<<8);
_GPIOC_(GPIOX_CRH) |= (8)<<8;
_GPIOC_(GPIOX_ODR) |= (1)<<10;
}

inline void pinC10_Input_PD()
{
_GPIOC_(GPIOX_CRH) &= ~((4+2+1)<<8);
_GPIOC_(GPIOX_CRH) |= (8)<<8;
_GPIOC_(GPIOX_ODR) &= ~(1<<10);
}

inline void pinC10_Analog()
{
_GPIOC_(GPIOX_CRH) &= ~((8+4+2+1)<<8);
}

inline void pinC10_Output()
{
_GPIOC_(GPIOX_CRH) &= ~((8+4+1)<<8);
_GPIOC_(GPIOX_CRH) |= (2)<<8;
}

inline void pinC10_Output_OD()
{
_GPIOC_(GPIOX_CRH) &= ~((8+1)<<8);
_GPIOC_(GPIOX_CRH) |= (2+4)<<8;
}

inline void pinC10_Output_PP_2()
{
_GPIOC_(GPIOX_CRH) &= ~((8+4+1)<<8);
_GPIOC_(GPIOX_CRH) |= (2)<<8;
}

inline void pinC10_Output_PP_10()
{
_GPIOC_(GPIOX_CRH) &= ~((8+4+2)<<8);
_GPIOC_(GPIOX_CRH) |= (1)<<8;
}

inline void pinC10_Output_PP_50()
{
_GPIOC_(GPIOX_CRH) &= ~((8+4)<<8);
_GPIOC_(GPIOX_CRH) |= (2+1)<<8;
}

inline void pinC10_Output_OD_2()
{
_GPIOC_(GPIOX_CRH) &= ~((8+1)<<8);
_GPIOC_(GPIOX_CRH) |= (2+4)<<8;
}

inline void pinC10_Output_OD_10()
{
_GPIOC_(GPIOX_CRH) &= ~((8+2)<<8);
_GPIOC_(GPIOX_CRH) |= (4+1)<<8;
}

inline void pinC10_Output_OD_50()
{
_GPIOC_(GPIOX_CRH) &= ~((8)<<8);
_GPIOC_(GPIOX_CRH) |= (4+2+1)<<8;
}

inline void pinC10_Output_AFPP_2()
{
_GPIOC_(GPIOX_CRH) &= ~((4+1)<<8);
_GPIOC_(GPIOX_CRH) |= (8+2)<<8;
}

inline void pinC10_Output_AFPP_10()
{
_GPIOC_(GPIOX_CRH) &= ~((4+2)<<8);
_GPIOC_(GPIOX_CRH) |= (8+1)<<8;
}

inline void pinC10_Output_AFPP_50()
{
_GPIOC_(GPIOX_CRH) &= ~((4)<<8);
_GPIOC_(GPIOX_CRH) |= (8+2+1)<<8;
}

inline void pinC10_Output_AFOD_2()
{
_GPIOC_(GPIOX_CRH) &= ~((1)<<8);
_GPIOC_(GPIOX_CRH) |= (8+2+4)<<8;
}

inline void pinC10_Output_AFOD_10()
{
_GPIOC_(GPIOX_CRH) &= ~((2)<<8);
_GPIOC_(GPIOX_CRH) |= (8+4+1)<<8;
}

inline void pinC10_Output_AFOD_50()
{
_GPIOC_(GPIOX_CRH) |= (8+4+2+1)<<8;
}

inline void pinC11_Input()
{
_GPIOC_(GPIOX_CRH) &= ~((8+2+1)<<12);
_GPIOC_(GPIOX_CRH) |= (4)<<12;
}

inline void pinC11_Input_PU()
{
_GPIOC_(GPIOX_CRH) &= ~((4+2+1)<<12);
_GPIOC_(GPIOX_CRH) |= (8)<<12;
_GPIOC_(GPIOX_ODR) |= (1)<<11;
}

inline void pinC11_Input_PD()
{
_GPIOC_(GPIOX_CRH) &= ~((4+2+1)<<12);
_GPIOC_(GPIOX_CRH) |= (8)<<12;
_GPIOC_(GPIOX_ODR) &= ~(1<<11);
}

inline void pinC11_Analog()
{
_GPIOC_(GPIOX_CRH) &= ~((8+4+2+1)<<12);
}

inline void pinC11_Output()
{
_GPIOC_(GPIOX_CRH) &= ~((8+4+1)<<12);
_GPIOC_(GPIOX_CRH) |= (2)<<12;
}

inline void pinC11_Output_OD()
{
_GPIOC_(GPIOX_CRH) &= ~((8+1)<<12);
_GPIOC_(GPIOX_CRH) |= (2+4)<<12;
}

inline void pinC11_Output_PP_2()
{
_GPIOC_(GPIOX_CRH) &= ~((8+4+1)<<12);
_GPIOC_(GPIOX_CRH) |= (2)<<12;
}

inline void pinC11_Output_PP_10()
{
_GPIOC_(GPIOX_CRH) &= ~((8+4+2)<<12);
_GPIOC_(GPIOX_CRH) |= (1)<<12;
}

inline void pinC11_Output_PP_50()
{
_GPIOC_(GPIOX_CRH) &= ~((8+4)<<12);
_GPIOC_(GPIOX_CRH) |= (2+1)<<12;
}

inline void pinC11_Output_OD_2()
{
_GPIOC_(GPIOX_CRH) &= ~((8+1)<<12);
_GPIOC_(GPIOX_CRH) |= (2+4)<<12;
}

inline void pinC11_Output_OD_10()
{
_GPIOC_(GPIOX_CRH) &= ~((8+2)<<12);
_GPIOC_(GPIOX_CRH) |= (4+1)<<12;
}

inline void pinC11_Output_OD_50()
{
_GPIOC_(GPIOX_CRH) &= ~((8)<<12);
_GPIOC_(GPIOX_CRH) |= (4+2+1)<<12;
}

inline void pinC11_Output_AFPP_2()
{
_GPIOC_(GPIOX_CRH) &= ~((4+1)<<12);
_GPIOC_(GPIOX_CRH) |= (8+2)<<12;
}

inline void pinC11_Output_AFPP_10()
{
_GPIOC_(GPIOX_CRH) &= ~((4+2)<<12);
_GPIOC_(GPIOX_CRH) |= (8+1)<<12;
}

inline void pinC11_Output_AFPP_50()
{
_GPIOC_(GPIOX_CRH) &= ~((4)<<12);
_GPIOC_(GPIOX_CRH) |= (8+2+1)<<12;
}

inline void pinC11_Output_AFOD_2()
{
_GPIOC_(GPIOX_CRH) &= ~((1)<<12);
_GPIOC_(GPIOX_CRH) |= (8+2+4)<<12;
}

inline void pinC11_Output_AFOD_10()
{
_GPIOC_(GPIOX_CRH) &= ~((2)<<12);
_GPIOC_(GPIOX_CRH) |= (8+4+1)<<12;
}

inline void pinC11_Output_AFOD_50()
{
_GPIOC_(GPIOX_CRH) |= (8+4+2+1)<<12;
}

inline void pinC12_Input()
{
_GPIOC_(GPIOX_CRH) &= ~((8+2+1)<<16);
_GPIOC_(GPIOX_CRH) |= (4)<<16;
}

inline void pinC12_Input_PU()
{
_GPIOC_(GPIOX_CRH) &= ~((4+2+1)<<16);
_GPIOC_(GPIOX_CRH) |= (8)<<16;
_GPIOC_(GPIOX_ODR) |= (1)<<12;
}

inline void pinC12_Input_PD()
{
_GPIOC_(GPIOX_CRH) &= ~((4+2+1)<<16);
_GPIOC_(GPIOX_CRH) |= (8)<<16;
_GPIOC_(GPIOX_ODR) &= ~(1<<12);
}

inline void pinC12_Analog()
{
_GPIOC_(GPIOX_CRH) &= ~((8+4+2+1)<<16);
}

inline void pinC12_Output()
{
_GPIOC_(GPIOX_CRH) &= ~((8+4+1)<<16);
_GPIOC_(GPIOX_CRH) |= (2)<<16;
}

inline void pinC12_Output_OD()
{
_GPIOC_(GPIOX_CRH) &= ~((8+1)<<16);
_GPIOC_(GPIOX_CRH) |= (2+4)<<16;
}

inline void pinC12_Output_PP_2()
{
_GPIOC_(GPIOX_CRH) &= ~((8+4+1)<<16);
_GPIOC_(GPIOX_CRH) |= (2)<<16;
}

inline void pinC12_Output_PP_10()
{
_GPIOC_(GPIOX_CRH) &= ~((8+4+2)<<16);
_GPIOC_(GPIOX_CRH) |= (1)<<16;
}

inline void pinC12_Output_PP_50()
{
_GPIOC_(GPIOX_CRH) &= ~((8+4)<<16);
_GPIOC_(GPIOX_CRH) |= (2+1)<<16;
}

inline void pinC12_Output_OD_2()
{
_GPIOC_(GPIOX_CRH) &= ~((8+1)<<16);
_GPIOC_(GPIOX_CRH) |= (2+4)<<16;
}

inline void pinC12_Output_OD_10()
{
_GPIOC_(GPIOX_CRH) &= ~((8+2)<<16);
_GPIOC_(GPIOX_CRH) |= (4+1)<<16;
}

inline void pinC12_Output_OD_50()
{
_GPIOC_(GPIOX_CRH) &= ~((8)<<16);
_GPIOC_(GPIOX_CRH) |= (4+2+1)<<16;
}

inline void pinC12_Output_AFPP_2()
{
_GPIOC_(GPIOX_CRH) &= ~((4+1)<<16);
_GPIOC_(GPIOX_CRH) |= (8+2)<<16;
}

inline void pinC12_Output_AFPP_10()
{
_GPIOC_(GPIOX_CRH) &= ~((4+2)<<16);
_GPIOC_(GPIOX_CRH) |= (8+1)<<16;
}

inline void pinC12_Output_AFPP_50()
{
_GPIOC_(GPIOX_CRH) &= ~((4)<<16);
_GPIOC_(GPIOX_CRH) |= (8+2+1)<<16;
}

inline void pinC12_Output_AFOD_2()
{
_GPIOC_(GPIOX_CRH) &= ~((1)<<16);
_GPIOC_(GPIOX_CRH) |= (8+2+4)<<16;
}

inline void pinC12_Output_AFOD_10()
{
_GPIOC_(GPIOX_CRH) &= ~((2)<<16);
_GPIOC_(GPIOX_CRH) |= (8+4+1)<<16;
}

inline void pinC12_Output_AFOD_50()
{
_GPIOC_(GPIOX_CRH) |= (8+4+2+1)<<16;
}

inline void pinC13_Input()
{
_GPIOC_(GPIOX_CRH) &= ~((8+2+1)<<20);
_GPIOC_(GPIOX_CRH) |= (4)<<20;
}

inline void pinC13_Input_PU()
{
_GPIOC_(GPIOX_CRH) &= ~((4+2+1)<<20);
_GPIOC_(GPIOX_CRH) |= (8)<<20;
_GPIOC_(GPIOX_ODR) |= (1)<<13;
}

inline void pinC13_Input_PD()
{
_GPIOC_(GPIOX_CRH) &= ~((4+2+1)<<20);
_GPIOC_(GPIOX_CRH) |= (8)<<20;
_GPIOC_(GPIOX_ODR) &= ~(1<<13);
}

inline void pinC13_Analog()
{
_GPIOC_(GPIOX_CRH) &= ~((8+4+2+1)<<20);
}

inline void pinC13_Output()
{
_GPIOC_(GPIOX_CRH) &= ~((8+4+1)<<20);
_GPIOC_(GPIOX_CRH) |= (2)<<20;
}

inline void pinC13_Output_OD()
{
_GPIOC_(GPIOX_CRH) &= ~((8+1)<<20);
_GPIOC_(GPIOX_CRH) |= (2+4)<<20;
}

inline void pinC13_Output_PP_2()
{
_GPIOC_(GPIOX_CRH) &= ~((8+4+1)<<20);
_GPIOC_(GPIOX_CRH) |= (2)<<20;
}

inline void pinC13_Output_PP_10()
{
_GPIOC_(GPIOX_CRH) &= ~((8+4+2)<<20);
_GPIOC_(GPIOX_CRH) |= (1)<<20;
}

inline void pinC13_Output_PP_50()
{
_GPIOC_(GPIOX_CRH) &= ~((8+4)<<20);
_GPIOC_(GPIOX_CRH) |= (2+1)<<20;
}

inline void pinC13_Output_OD_2()
{
_GPIOC_(GPIOX_CRH) &= ~((8+1)<<20);
_GPIOC_(GPIOX_CRH) |= (2+4)<<20;
}

inline void pinC13_Output_OD_10()
{
_GPIOC_(GPIOX_CRH) &= ~((8+2)<<20);
_GPIOC_(GPIOX_CRH) |= (4+1)<<20;
}

inline void pinC13_Output_OD_50()
{
_GPIOC_(GPIOX_CRH) &= ~((8)<<20);
_GPIOC_(GPIOX_CRH) |= (4+2+1)<<20;
}

inline void pinC13_Output_AFPP_2()
{
_GPIOC_(GPIOX_CRH) &= ~((4+1)<<20);
_GPIOC_(GPIOX_CRH) |= (8+2)<<20;
}

inline void pinC13_Output_AFPP_10()
{
_GPIOC_(GPIOX_CRH) &= ~((4+2)<<20);
_GPIOC_(GPIOX_CRH) |= (8+1)<<20;
}

inline void pinC13_Output_AFPP_50()
{
_GPIOC_(GPIOX_CRH) &= ~((4)<<20);
_GPIOC_(GPIOX_CRH) |= (8+2+1)<<20;
}

inline void pinC13_Output_AFOD_2()
{
_GPIOC_(GPIOX_CRH) &= ~((1)<<20);
_GPIOC_(GPIOX_CRH) |= (8+2+4)<<20;
}

inline void pinC13_Output_AFOD_10()
{
_GPIOC_(GPIOX_CRH) &= ~((2)<<20);
_GPIOC_(GPIOX_CRH) |= (8+4+1)<<20;
}

inline void pinC13_Output_AFOD_50()
{
_GPIOC_(GPIOX_CRH) |= (8+4+2+1)<<20;
}

inline void pinC14_Input()
{
_GPIOC_(GPIOX_CRH) &= ~((8+2+1)<<24);
_GPIOC_(GPIOX_CRH) |= (4)<<24;
}

inline void pinC14_Input_PU()
{
_GPIOC_(GPIOX_CRH) &= ~((4+2+1)<<24);
_GPIOC_(GPIOX_CRH) |= (8)<<24;
_GPIOC_(GPIOX_ODR) |= (1)<<14;
}

inline void pinC14_Input_PD()
{
_GPIOC_(GPIOX_CRH) &= ~((4+2+1)<<24);
_GPIOC_(GPIOX_CRH) |= (8)<<24;
_GPIOC_(GPIOX_ODR) &= ~(1<<14);
}

inline void pinC14_Analog()
{
_GPIOC_(GPIOX_CRH) &= ~((8+4+2+1)<<24);
}

inline void pinC14_Output()
{
_GPIOC_(GPIOX_CRH) &= ~((8+4+1)<<24);
_GPIOC_(GPIOX_CRH) |= (2)<<24;
}

inline void pinC14_Output_OD()
{
_GPIOC_(GPIOX_CRH) &= ~((8+1)<<24);
_GPIOC_(GPIOX_CRH) |= (2+4)<<24;
}

inline void pinC14_Output_PP_2()
{
_GPIOC_(GPIOX_CRH) &= ~((8+4+1)<<24);
_GPIOC_(GPIOX_CRH) |= (2)<<24;
}

inline void pinC14_Output_PP_10()
{
_GPIOC_(GPIOX_CRH) &= ~((8+4+2)<<24);
_GPIOC_(GPIOX_CRH) |= (1)<<24;
}

inline void pinC14_Output_PP_50()
{
_GPIOC_(GPIOX_CRH) &= ~((8+4)<<24);
_GPIOC_(GPIOX_CRH) |= (2+1)<<24;
}

inline void pinC14_Output_OD_2()
{
_GPIOC_(GPIOX_CRH) &= ~((8+1)<<24);
_GPIOC_(GPIOX_CRH) |= (2+4)<<24;
}

inline void pinC14_Output_OD_10()
{
_GPIOC_(GPIOX_CRH) &= ~((8+2)<<24);
_GPIOC_(GPIOX_CRH) |= (4+1)<<24;
}

inline void pinC14_Output_OD_50()
{
_GPIOC_(GPIOX_CRH) &= ~((8)<<24);
_GPIOC_(GPIOX_CRH) |= (4+2+1)<<24;
}

inline void pinC14_Output_AFPP_2()
{
_GPIOC_(GPIOX_CRH) &= ~((4+1)<<24);
_GPIOC_(GPIOX_CRH) |= (8+2)<<24;
}

inline void pinC14_Output_AFPP_10()
{
_GPIOC_(GPIOX_CRH) &= ~((4+2)<<24);
_GPIOC_(GPIOX_CRH) |= (8+1)<<24;
}

inline void pinC14_Output_AFPP_50()
{
_GPIOC_(GPIOX_CRH) &= ~((4)<<24);
_GPIOC_(GPIOX_CRH) |= (8+2+1)<<24;
}

inline void pinC14_Output_AFOD_2()
{
_GPIOC_(GPIOX_CRH) &= ~((1)<<24);
_GPIOC_(GPIOX_CRH) |= (8+2+4)<<24;
}

inline void pinC14_Output_AFOD_10()
{
_GPIOC_(GPIOX_CRH) &= ~((2)<<24);
_GPIOC_(GPIOX_CRH) |= (8+4+1)<<24;
}

inline void pinC14_Output_AFOD_50()
{
_GPIOC_(GPIOX_CRH) |= (8+4+2+1)<<24;
}

inline void pinC15_Input()
{
_GPIOC_(GPIOX_CRH) &= ~((8+2+1)<<28);
_GPIOC_(GPIOX_CRH) |= (4)<<28;
}

inline void pinC15_Input_PU()
{
_GPIOC_(GPIOX_CRH) &= ~((4+2+1)<<28);
_GPIOC_(GPIOX_CRH) |= (8)<<28;
_GPIOC_(GPIOX_ODR) |= (1)<<15;
}

inline void pinC15_Input_PD()
{
_GPIOC_(GPIOX_CRH) &= ~((4+2+1)<<28);
_GPIOC_(GPIOX_CRH) |= (8)<<28;
_GPIOC_(GPIOX_ODR) &= ~(1<<15);
}

inline void pinC15_Analog()
{
_GPIOC_(GPIOX_CRH) &= ~((8+4+2+1)<<28);
}

inline void pinC15_Output()
{
_GPIOC_(GPIOX_CRH) &= ~((8+4+1)<<28);
_GPIOC_(GPIOX_CRH) |= (2)<<28;
}

inline void pinC15_Output_OD()
{
_GPIOC_(GPIOX_CRH) &= ~((8+1)<<28);
_GPIOC_(GPIOX_CRH) |= (2+4)<<28;
}

inline void pinC15_Output_PP_2()
{
_GPIOC_(GPIOX_CRH) &= ~((8+4+1)<<28);
_GPIOC_(GPIOX_CRH) |= (2)<<28;
}

inline void pinC15_Output_PP_10()
{
_GPIOC_(GPIOX_CRH) &= ~((8+4+2)<<28);
_GPIOC_(GPIOX_CRH) |= (1)<<28;
}

inline void pinC15_Output_PP_50()
{
_GPIOC_(GPIOX_CRH) &= ~((8+4)<<28);
_GPIOC_(GPIOX_CRH) |= (2+1)<<28;
}

inline void pinC15_Output_OD_2()
{
_GPIOC_(GPIOX_CRH) &= ~((8+1)<<28);
_GPIOC_(GPIOX_CRH) |= (2+4)<<28;
}

inline void pinC15_Output_OD_10()
{
_GPIOC_(GPIOX_CRH) &= ~((8+2)<<28);
_GPIOC_(GPIOX_CRH) |= (4+1)<<28;
}

inline void pinC15_Output_OD_50()
{
_GPIOC_(GPIOX_CRH) &= ~((8)<<28);
_GPIOC_(GPIOX_CRH) |= (4+2+1)<<28;
}

inline void pinC15_Output_AFPP_2()
{
_GPIOC_(GPIOX_CRH) &= ~((4+1)<<28);
_GPIOC_(GPIOX_CRH) |= (8+2)<<28;
}

inline void pinC15_Output_AFPP_10()
{
_GPIOC_(GPIOX_CRH) &= ~((4+2)<<28);
_GPIOC_(GPIOX_CRH) |= (8+1)<<28;
}

inline void pinC15_Output_AFPP_50()
{
_GPIOC_(GPIOX_CRH) &= ~((4)<<28);
_GPIOC_(GPIOX_CRH) |= (8+2+1)<<28;
}

inline void pinC15_Output_AFOD_2()
{
_GPIOC_(GPIOX_CRH) &= ~((1)<<28);
_GPIOC_(GPIOX_CRH) |= (8+2+4)<<28;
}

inline void pinC15_Output_AFOD_10()
{
_GPIOC_(GPIOX_CRH) &= ~((2)<<28);
_GPIOC_(GPIOX_CRH) |= (8+4+1)<<28;
}

inline void pinC15_Output_AFOD_50()
{
_GPIOC_(GPIOX_CRH) |= (8+4+2+1)<<28;
}

inline uint8_t readPinC0()
{
return ((_GPIOC_(GPIOX_IDR)>>0) & 1);
}

inline void setPinC0()
{
_GPIOC_(GPIOX_BSRR) = (1<<0);
}

inline void resetPinC0()
{
_GPIOC_(GPIOX_BRR) = (1<<0);
}

inline uint8_t readPinC1()
{
return ((_GPIOC_(GPIOX_IDR)>>1) & 1);
}

inline void setPinC1()
{
_GPIOC_(GPIOX_BSRR) = (1<<1);
}

inline void resetPinC1()
{
_GPIOC_(GPIOX_BRR) = (1<<1);
}

inline uint8_t readPinC2()
{
return ((_GPIOC_(GPIOX_IDR)>>2) & 1);
}

inline void setPinC2()
{
_GPIOC_(GPIOX_BSRR) = (1<<2);
}

inline void resetPinC2()
{
_GPIOC_(GPIOX_BRR) = (1<<2);
}

inline uint8_t readPinC3()
{
return ((_GPIOC_(GPIOX_IDR)>>3) & 1);
}

inline void setPinC3()
{
_GPIOC_(GPIOX_BSRR) = (1<<3);
}

inline void resetPinC3()
{
_GPIOC_(GPIOX_BRR) = (1<<3);
}

inline uint8_t readPinC4()
{
return ((_GPIOC_(GPIOX_IDR)>>4) & 1);
}

inline void setPinC4()
{
_GPIOC_(GPIOX_BSRR) = (1<<4);
}

inline void resetPinC4()
{
_GPIOC_(GPIOX_BRR) = (1<<4);
}

inline uint8_t readPinC5()
{
return ((_GPIOC_(GPIOX_IDR)>>5) & 1);
}

inline void setPinC5()
{
_GPIOC_(GPIOX_BSRR) = (1<<5);
}

inline void resetPinC5()
{
_GPIOC_(GPIOX_BRR) = (1<<5);
}

inline uint8_t readPinC6()
{
return ((_GPIOC_(GPIOX_IDR)>>6) & 1);
}

inline void setPinC6()
{
_GPIOC_(GPIOX_BSRR) = (1<<6);
}

inline void resetPinC6()
{
_GPIOC_(GPIOX_BRR) = (1<<6);
}

inline uint8_t readPinC7()
{
return ((_GPIOC_(GPIOX_IDR)>>7) & 1);
}

inline void setPinC7()
{
_GPIOC_(GPIOX_BSRR) = (1<<7);
}

inline void resetPinC7()
{
_GPIOC_(GPIOX_BRR) = (1<<7);
}

inline uint8_t readPinC8()
{
return ((_GPIOC_(GPIOX_IDR)>>8) & 1);
}

inline void setPinC8()
{
_GPIOC_(GPIOX_BSRR) = (1<<8);
}

inline void resetPinC8()
{
_GPIOC_(GPIOX_BRR) = (1<<8);
}

inline uint8_t readPinC9()
{
return ((_GPIOC_(GPIOX_IDR)>>9) & 1);
}

inline void setPinC9()
{
_GPIOC_(GPIOX_BSRR) = (1<<9);
}

inline void resetPinC9()
{
_GPIOC_(GPIOX_BRR) = (1<<9);
}

inline uint8_t readPinC10()
{
return ((_GPIOC_(GPIOX_IDR)>>10) & 1);
}

inline void setPinC10()
{
_GPIOC_(GPIOX_BSRR) = (1<<10);
}

inline void resetPinC10()
{
_GPIOC_(GPIOX_BRR) = (1<<10);
}

inline uint8_t readPinC11()
{
return ((_GPIOC_(GPIOX_IDR)>>11) & 1);
}

inline void setPinC11()
{
_GPIOC_(GPIOX_BSRR) = (1<<11);
}

inline void resetPinC11()
{
_GPIOC_(GPIOX_BRR) = (1<<11);
}

inline uint8_t readPinC12()
{
return ((_GPIOC_(GPIOX_IDR)>>12) & 1);
}

inline void setPinC12()
{
_GPIOC_(GPIOX_BSRR) = (1<<12);
}

inline void resetPinC12()
{
_GPIOC_(GPIOX_BRR) = (1<<12);
}

inline uint8_t readPinC13()
{
return ((_GPIOC_(GPIOX_IDR)>>13) & 1);
}

inline void setPinC13()
{
_GPIOC_(GPIOX_BSRR) = (1<<13);
}

inline void resetPinC13()
{
_GPIOC_(GPIOX_BRR) = (1<<13);
}

inline uint8_t readPinC14()
{
return ((_GPIOC_(GPIOX_IDR)>>14) & 1);
}

inline void setPinC14()
{
_GPIOC_(GPIOX_BSRR) = (1<<14);
}

inline void resetPinC14()
{
_GPIOC_(GPIOX_BRR) = (1<<14);
}

inline uint8_t readPinC15()
{
return ((_GPIOC_(GPIOX_IDR)>>15) & 1);
}

inline void setPinC15()
{
_GPIOC_(GPIOX_BSRR) = (1<<15);
}

inline void resetPinC15()
{
_GPIOC_(GPIOX_BRR) = (1<<15);
}

inline void pinD0_Input()
{
_GPIOD_(GPIOX_CRL) &= ~((8+2+1)<<0);
_GPIOD_(GPIOX_CRL) |= (4)<<0;
}

inline void pinD0_Input_PU()
{
_GPIOD_(GPIOX_CRL) &= ~((4+2+1)<<0);
_GPIOD_(GPIOX_CRL) |= (8)<<0;
_GPIOD_(GPIOX_ODR) |= (1)<<0;
}

inline void pinD0_Input_PD()
{
_GPIOD_(GPIOX_CRL) &= ~((4+2+1)<<0);
_GPIOD_(GPIOX_CRL) |= (8)<<0;
_GPIOD_(GPIOX_ODR) &= ~(1<<0);
}

inline void pinD0_Analog()
{
_GPIOD_(GPIOX_CRL) &= ~((8+4+2+1)<<0);
}

inline void pinD0_Output()
{
_GPIOD_(GPIOX_CRL) &= ~((8+4+1)<<0);
_GPIOD_(GPIOX_CRL) |= (2)<<0;
}

inline void pinD0_Output_OD()
{
_GPIOD_(GPIOX_CRL) &= ~((8+1)<<0);
_GPIOD_(GPIOX_CRL) |= (2+4)<<0;
}

inline void pinD0_Output_PP_2()
{
_GPIOD_(GPIOX_CRL) &= ~((8+4+1)<<0);
_GPIOD_(GPIOX_CRL) |= (2)<<0;
}

inline void pinD0_Output_PP_10()
{
_GPIOD_(GPIOX_CRL) &= ~((8+4+2)<<0);
_GPIOD_(GPIOX_CRL) |= (1)<<0;
}

inline void pinD0_Output_PP_50()
{
_GPIOD_(GPIOX_CRL) &= ~((8+4)<<0);
_GPIOD_(GPIOX_CRL) |= (2+1)<<0;
}

inline void pinD0_Output_OD_2()
{
_GPIOD_(GPIOX_CRL) &= ~((8+1)<<0);
_GPIOD_(GPIOX_CRL) |= (2+4)<<0;
}

inline void pinD0_Output_OD_10()
{
_GPIOD_(GPIOX_CRL) &= ~((8+2)<<0);
_GPIOD_(GPIOX_CRL) |= (4+1)<<0;
}

inline void pinD0_Output_OD_50()
{
_GPIOD_(GPIOX_CRL) &= ~((8)<<0);
_GPIOD_(GPIOX_CRL) |= (4+2+1)<<0;
}

inline void pinD0_Output_AFPP_2()
{
_GPIOD_(GPIOX_CRL) &= ~((4+1)<<0);
_GPIOD_(GPIOX_CRL) |= (8+2)<<0;
}

inline void pinD0_Output_AFPP_10()
{
_GPIOD_(GPIOX_CRL) &= ~((4+2)<<0);
_GPIOD_(GPIOX_CRL) |= (8+1)<<0;
}

inline void pinD0_Output_AFPP_50()
{
_GPIOD_(GPIOX_CRL) &= ~((4)<<0);
_GPIOD_(GPIOX_CRL) |= (8+2+1)<<0;
}

inline void pinD0_Output_AFOD_2()
{
_GPIOD_(GPIOX_CRL) &= ~((1)<<0);
_GPIOD_(GPIOX_CRL) |= (8+2+4)<<0;
}

inline void pinD0_Output_AFOD_10()
{
_GPIOD_(GPIOX_CRL) &= ~((2)<<0);
_GPIOD_(GPIOX_CRL) |= (8+4+1)<<0;
}

inline void pinD0_Output_AFOD_50()
{
_GPIOD_(GPIOX_CRL) |= (8+4+2+1)<<0;
}

inline void pinD1_Input()
{
_GPIOD_(GPIOX_CRL) &= ~((8+2+1)<<4);
_GPIOD_(GPIOX_CRL) |= (4)<<4;
}

inline void pinD1_Input_PU()
{
_GPIOD_(GPIOX_CRL) &= ~((4+2+1)<<4);
_GPIOD_(GPIOX_CRL) |= (8)<<4;
_GPIOD_(GPIOX_ODR) |= (1)<<1;
}

inline void pinD1_Input_PD()
{
_GPIOD_(GPIOX_CRL) &= ~((4+2+1)<<4);
_GPIOD_(GPIOX_CRL) |= (8)<<4;
_GPIOD_(GPIOX_ODR) &= ~(1<<1);
}

inline void pinD1_Analog()
{
_GPIOD_(GPIOX_CRL) &= ~((8+4+2+1)<<4);
}

inline void pinD1_Output()
{
_GPIOD_(GPIOX_CRL) &= ~((8+4+1)<<4);
_GPIOD_(GPIOX_CRL) |= (2)<<4;
}

inline void pinD1_Output_OD()
{
_GPIOD_(GPIOX_CRL) &= ~((8+1)<<4);
_GPIOD_(GPIOX_CRL) |= (2+4)<<4;
}

inline void pinD1_Output_PP_2()
{
_GPIOD_(GPIOX_CRL) &= ~((8+4+1)<<4);
_GPIOD_(GPIOX_CRL) |= (2)<<4;
}

inline void pinD1_Output_PP_10()
{
_GPIOD_(GPIOX_CRL) &= ~((8+4+2)<<4);
_GPIOD_(GPIOX_CRL) |= (1)<<4;
}

inline void pinD1_Output_PP_50()
{
_GPIOD_(GPIOX_CRL) &= ~((8+4)<<4);
_GPIOD_(GPIOX_CRL) |= (2+1)<<4;
}

inline void pinD1_Output_OD_2()
{
_GPIOD_(GPIOX_CRL) &= ~((8+1)<<4);
_GPIOD_(GPIOX_CRL) |= (2+4)<<4;
}

inline void pinD1_Output_OD_10()
{
_GPIOD_(GPIOX_CRL) &= ~((8+2)<<4);
_GPIOD_(GPIOX_CRL) |= (4+1)<<4;
}

inline void pinD1_Output_OD_50()
{
_GPIOD_(GPIOX_CRL) &= ~((8)<<4);
_GPIOD_(GPIOX_CRL) |= (4+2+1)<<4;
}

inline void pinD1_Output_AFPP_2()
{
_GPIOD_(GPIOX_CRL) &= ~((4+1)<<4);
_GPIOD_(GPIOX_CRL) |= (8+2)<<4;
}

inline void pinD1_Output_AFPP_10()
{
_GPIOD_(GPIOX_CRL) &= ~((4+2)<<4);
_GPIOD_(GPIOX_CRL) |= (8+1)<<4;
}

inline void pinD1_Output_AFPP_50()
{
_GPIOD_(GPIOX_CRL) &= ~((4)<<4);
_GPIOD_(GPIOX_CRL) |= (8+2+1)<<4;
}

inline void pinD1_Output_AFOD_2()
{
_GPIOD_(GPIOX_CRL) &= ~((1)<<4);
_GPIOD_(GPIOX_CRL) |= (8+2+4)<<4;
}

inline void pinD1_Output_AFOD_10()
{
_GPIOD_(GPIOX_CRL) &= ~((2)<<4);
_GPIOD_(GPIOX_CRL) |= (8+4+1)<<4;
}

inline void pinD1_Output_AFOD_50()
{
_GPIOD_(GPIOX_CRL) |= (8+4+2+1)<<4;
}

inline void pinD2_Input()
{
_GPIOD_(GPIOX_CRL) &= ~((8+2+1)<<8);
_GPIOD_(GPIOX_CRL) |= (4)<<8;
}

inline void pinD2_Input_PU()
{
_GPIOD_(GPIOX_CRL) &= ~((4+2+1)<<8);
_GPIOD_(GPIOX_CRL) |= (8)<<8;
_GPIOD_(GPIOX_ODR) |= (1)<<2;
}

inline void pinD2_Input_PD()
{
_GPIOD_(GPIOX_CRL) &= ~((4+2+1)<<8);
_GPIOD_(GPIOX_CRL) |= (8)<<8;
_GPIOD_(GPIOX_ODR) &= ~(1<<2);
}

inline void pinD2_Analog()
{
_GPIOD_(GPIOX_CRL) &= ~((8+4+2+1)<<8);
}

inline void pinD2_Output()
{
_GPIOD_(GPIOX_CRL) &= ~((8+4+1)<<8);
_GPIOD_(GPIOX_CRL) |= (2)<<8;
}

inline void pinD2_Output_OD()
{
_GPIOD_(GPIOX_CRL) &= ~((8+1)<<8);
_GPIOD_(GPIOX_CRL) |= (2+4)<<8;
}

inline void pinD2_Output_PP_2()
{
_GPIOD_(GPIOX_CRL) &= ~((8+4+1)<<8);
_GPIOD_(GPIOX_CRL) |= (2)<<8;
}

inline void pinD2_Output_PP_10()
{
_GPIOD_(GPIOX_CRL) &= ~((8+4+2)<<8);
_GPIOD_(GPIOX_CRL) |= (1)<<8;
}

inline void pinD2_Output_PP_50()
{
_GPIOD_(GPIOX_CRL) &= ~((8+4)<<8);
_GPIOD_(GPIOX_CRL) |= (2+1)<<8;
}

inline void pinD2_Output_OD_2()
{
_GPIOD_(GPIOX_CRL) &= ~((8+1)<<8);
_GPIOD_(GPIOX_CRL) |= (2+4)<<8;
}

inline void pinD2_Output_OD_10()
{
_GPIOD_(GPIOX_CRL) &= ~((8+2)<<8);
_GPIOD_(GPIOX_CRL) |= (4+1)<<8;
}

inline void pinD2_Output_OD_50()
{
_GPIOD_(GPIOX_CRL) &= ~((8)<<8);
_GPIOD_(GPIOX_CRL) |= (4+2+1)<<8;
}

inline void pinD2_Output_AFPP_2()
{
_GPIOD_(GPIOX_CRL) &= ~((4+1)<<8);
_GPIOD_(GPIOX_CRL) |= (8+2)<<8;
}

inline void pinD2_Output_AFPP_10()
{
_GPIOD_(GPIOX_CRL) &= ~((4+2)<<8);
_GPIOD_(GPIOX_CRL) |= (8+1)<<8;
}

inline void pinD2_Output_AFPP_50()
{
_GPIOD_(GPIOX_CRL) &= ~((4)<<8);
_GPIOD_(GPIOX_CRL) |= (8+2+1)<<8;
}

inline void pinD2_Output_AFOD_2()
{
_GPIOD_(GPIOX_CRL) &= ~((1)<<8);
_GPIOD_(GPIOX_CRL) |= (8+2+4)<<8;
}

inline void pinD2_Output_AFOD_10()
{
_GPIOD_(GPIOX_CRL) &= ~((2)<<8);
_GPIOD_(GPIOX_CRL) |= (8+4+1)<<8;
}

inline void pinD2_Output_AFOD_50()
{
_GPIOD_(GPIOX_CRL) |= (8+4+2+1)<<8;
}

inline void pinD3_Input()
{
_GPIOD_(GPIOX_CRL) &= ~((8+2+1)<<12);
_GPIOD_(GPIOX_CRL) |= (4)<<12;
}

inline void pinD3_Input_PU()
{
_GPIOD_(GPIOX_CRL) &= ~((4+2+1)<<12);
_GPIOD_(GPIOX_CRL) |= (8)<<12;
_GPIOD_(GPIOX_ODR) |= (1)<<3;
}

inline void pinD3_Input_PD()
{
_GPIOD_(GPIOX_CRL) &= ~((4+2+1)<<12);
_GPIOD_(GPIOX_CRL) |= (8)<<12;
_GPIOD_(GPIOX_ODR) &= ~(1<<3);
}

inline void pinD3_Analog()
{
_GPIOD_(GPIOX_CRL) &= ~((8+4+2+1)<<12);
}

inline void pinD3_Output()
{
_GPIOD_(GPIOX_CRL) &= ~((8+4+1)<<12);
_GPIOD_(GPIOX_CRL) |= (2)<<12;
}

inline void pinD3_Output_OD()
{
_GPIOD_(GPIOX_CRL) &= ~((8+1)<<12);
_GPIOD_(GPIOX_CRL) |= (2+4)<<12;
}

inline void pinD3_Output_PP_2()
{
_GPIOD_(GPIOX_CRL) &= ~((8+4+1)<<12);
_GPIOD_(GPIOX_CRL) |= (2)<<12;
}

inline void pinD3_Output_PP_10()
{
_GPIOD_(GPIOX_CRL) &= ~((8+4+2)<<12);
_GPIOD_(GPIOX_CRL) |= (1)<<12;
}

inline void pinD3_Output_PP_50()
{
_GPIOD_(GPIOX_CRL) &= ~((8+4)<<12);
_GPIOD_(GPIOX_CRL) |= (2+1)<<12;
}

inline void pinD3_Output_OD_2()
{
_GPIOD_(GPIOX_CRL) &= ~((8+1)<<12);
_GPIOD_(GPIOX_CRL) |= (2+4)<<12;
}

inline void pinD3_Output_OD_10()
{
_GPIOD_(GPIOX_CRL) &= ~((8+2)<<12);
_GPIOD_(GPIOX_CRL) |= (4+1)<<12;
}

inline void pinD3_Output_OD_50()
{
_GPIOD_(GPIOX_CRL) &= ~((8)<<12);
_GPIOD_(GPIOX_CRL) |= (4+2+1)<<12;
}

inline void pinD3_Output_AFPP_2()
{
_GPIOD_(GPIOX_CRL) &= ~((4+1)<<12);
_GPIOD_(GPIOX_CRL) |= (8+2)<<12;
}

inline void pinD3_Output_AFPP_10()
{
_GPIOD_(GPIOX_CRL) &= ~((4+2)<<12);
_GPIOD_(GPIOX_CRL) |= (8+1)<<12;
}

inline void pinD3_Output_AFPP_50()
{
_GPIOD_(GPIOX_CRL) &= ~((4)<<12);
_GPIOD_(GPIOX_CRL) |= (8+2+1)<<12;
}

inline void pinD3_Output_AFOD_2()
{
_GPIOD_(GPIOX_CRL) &= ~((1)<<12);
_GPIOD_(GPIOX_CRL) |= (8+2+4)<<12;
}

inline void pinD3_Output_AFOD_10()
{
_GPIOD_(GPIOX_CRL) &= ~((2)<<12);
_GPIOD_(GPIOX_CRL) |= (8+4+1)<<12;
}

inline void pinD3_Output_AFOD_50()
{
_GPIOD_(GPIOX_CRL) |= (8+4+2+1)<<12;
}

inline void pinD4_Input()
{
_GPIOD_(GPIOX_CRL) &= ~((8+2+1)<<16);
_GPIOD_(GPIOX_CRL) |= (4)<<16;
}

inline void pinD4_Input_PU()
{
_GPIOD_(GPIOX_CRL) &= ~((4+2+1)<<16);
_GPIOD_(GPIOX_CRL) |= (8)<<16;
_GPIOD_(GPIOX_ODR) |= (1)<<4;
}

inline void pinD4_Input_PD()
{
_GPIOD_(GPIOX_CRL) &= ~((4+2+1)<<16);
_GPIOD_(GPIOX_CRL) |= (8)<<16;
_GPIOD_(GPIOX_ODR) &= ~(1<<4);
}

inline void pinD4_Analog()
{
_GPIOD_(GPIOX_CRL) &= ~((8+4+2+1)<<16);
}

inline void pinD4_Output()
{
_GPIOD_(GPIOX_CRL) &= ~((8+4+1)<<16);
_GPIOD_(GPIOX_CRL) |= (2)<<16;
}

inline void pinD4_Output_OD()
{
_GPIOD_(GPIOX_CRL) &= ~((8+1)<<16);
_GPIOD_(GPIOX_CRL) |= (2+4)<<16;
}

inline void pinD4_Output_PP_2()
{
_GPIOD_(GPIOX_CRL) &= ~((8+4+1)<<16);
_GPIOD_(GPIOX_CRL) |= (2)<<16;
}

inline void pinD4_Output_PP_10()
{
_GPIOD_(GPIOX_CRL) &= ~((8+4+2)<<16);
_GPIOD_(GPIOX_CRL) |= (1)<<16;
}

inline void pinD4_Output_PP_50()
{
_GPIOD_(GPIOX_CRL) &= ~((8+4)<<16);
_GPIOD_(GPIOX_CRL) |= (2+1)<<16;
}

inline void pinD4_Output_OD_2()
{
_GPIOD_(GPIOX_CRL) &= ~((8+1)<<16);
_GPIOD_(GPIOX_CRL) |= (2+4)<<16;
}

inline void pinD4_Output_OD_10()
{
_GPIOD_(GPIOX_CRL) &= ~((8+2)<<16);
_GPIOD_(GPIOX_CRL) |= (4+1)<<16;
}

inline void pinD4_Output_OD_50()
{
_GPIOD_(GPIOX_CRL) &= ~((8)<<16);
_GPIOD_(GPIOX_CRL) |= (4+2+1)<<16;
}

inline void pinD4_Output_AFPP_2()
{
_GPIOD_(GPIOX_CRL) &= ~((4+1)<<16);
_GPIOD_(GPIOX_CRL) |= (8+2)<<16;
}

inline void pinD4_Output_AFPP_10()
{
_GPIOD_(GPIOX_CRL) &= ~((4+2)<<16);
_GPIOD_(GPIOX_CRL) |= (8+1)<<16;
}

inline void pinD4_Output_AFPP_50()
{
_GPIOD_(GPIOX_CRL) &= ~((4)<<16);
_GPIOD_(GPIOX_CRL) |= (8+2+1)<<16;
}

inline void pinD4_Output_AFOD_2()
{
_GPIOD_(GPIOX_CRL) &= ~((1)<<16);
_GPIOD_(GPIOX_CRL) |= (8+2+4)<<16;
}

inline void pinD4_Output_AFOD_10()
{
_GPIOD_(GPIOX_CRL) &= ~((2)<<16);
_GPIOD_(GPIOX_CRL) |= (8+4+1)<<16;
}

inline void pinD4_Output_AFOD_50()
{
_GPIOD_(GPIOX_CRL) |= (8+4+2+1)<<16;
}

inline void pinD5_Input()
{
_GPIOD_(GPIOX_CRL) &= ~((8+2+1)<<20);
_GPIOD_(GPIOX_CRL) |= (4)<<20;
}

inline void pinD5_Input_PU()
{
_GPIOD_(GPIOX_CRL) &= ~((4+2+1)<<20);
_GPIOD_(GPIOX_CRL) |= (8)<<20;
_GPIOD_(GPIOX_ODR) |= (1)<<5;
}

inline void pinD5_Input_PD()
{
_GPIOD_(GPIOX_CRL) &= ~((4+2+1)<<20);
_GPIOD_(GPIOX_CRL) |= (8)<<20;
_GPIOD_(GPIOX_ODR) &= ~(1<<5);
}

inline void pinD5_Analog()
{
_GPIOD_(GPIOX_CRL) &= ~((8+4+2+1)<<20);
}

inline void pinD5_Output()
{
_GPIOD_(GPIOX_CRL) &= ~((8+4+1)<<20);
_GPIOD_(GPIOX_CRL) |= (2)<<20;
}

inline void pinD5_Output_OD()
{
_GPIOD_(GPIOX_CRL) &= ~((8+1)<<20);
_GPIOD_(GPIOX_CRL) |= (2+4)<<20;
}

inline void pinD5_Output_PP_2()
{
_GPIOD_(GPIOX_CRL) &= ~((8+4+1)<<20);
_GPIOD_(GPIOX_CRL) |= (2)<<20;
}

inline void pinD5_Output_PP_10()
{
_GPIOD_(GPIOX_CRL) &= ~((8+4+2)<<20);
_GPIOD_(GPIOX_CRL) |= (1)<<20;
}

inline void pinD5_Output_PP_50()
{
_GPIOD_(GPIOX_CRL) &= ~((8+4)<<20);
_GPIOD_(GPIOX_CRL) |= (2+1)<<20;
}

inline void pinD5_Output_OD_2()
{
_GPIOD_(GPIOX_CRL) &= ~((8+1)<<20);
_GPIOD_(GPIOX_CRL) |= (2+4)<<20;
}

inline void pinD5_Output_OD_10()
{
_GPIOD_(GPIOX_CRL) &= ~((8+2)<<20);
_GPIOD_(GPIOX_CRL) |= (4+1)<<20;
}

inline void pinD5_Output_OD_50()
{
_GPIOD_(GPIOX_CRL) &= ~((8)<<20);
_GPIOD_(GPIOX_CRL) |= (4+2+1)<<20;
}

inline void pinD5_Output_AFPP_2()
{
_GPIOD_(GPIOX_CRL) &= ~((4+1)<<20);
_GPIOD_(GPIOX_CRL) |= (8+2)<<20;
}

inline void pinD5_Output_AFPP_10()
{
_GPIOD_(GPIOX_CRL) &= ~((4+2)<<20);
_GPIOD_(GPIOX_CRL) |= (8+1)<<20;
}

inline void pinD5_Output_AFPP_50()
{
_GPIOD_(GPIOX_CRL) &= ~((4)<<20);
_GPIOD_(GPIOX_CRL) |= (8+2+1)<<20;
}

inline void pinD5_Output_AFOD_2()
{
_GPIOD_(GPIOX_CRL) &= ~((1)<<20);
_GPIOD_(GPIOX_CRL) |= (8+2+4)<<20;
}

inline void pinD5_Output_AFOD_10()
{
_GPIOD_(GPIOX_CRL) &= ~((2)<<20);
_GPIOD_(GPIOX_CRL) |= (8+4+1)<<20;
}

inline void pinD5_Output_AFOD_50()
{
_GPIOD_(GPIOX_CRL) |= (8+4+2+1)<<20;
}

inline void pinD6_Input()
{
_GPIOD_(GPIOX_CRL) &= ~((8+2+1)<<24);
_GPIOD_(GPIOX_CRL) |= (4)<<24;
}

inline void pinD6_Input_PU()
{
_GPIOD_(GPIOX_CRL) &= ~((4+2+1)<<24);
_GPIOD_(GPIOX_CRL) |= (8)<<24;
_GPIOD_(GPIOX_ODR) |= (1)<<6;
}

inline void pinD6_Input_PD()
{
_GPIOD_(GPIOX_CRL) &= ~((4+2+1)<<24);
_GPIOD_(GPIOX_CRL) |= (8)<<24;
_GPIOD_(GPIOX_ODR) &= ~(1<<6);
}

inline void pinD6_Analog()
{
_GPIOD_(GPIOX_CRL) &= ~((8+4+2+1)<<24);
}

inline void pinD6_Output()
{
_GPIOD_(GPIOX_CRL) &= ~((8+4+1)<<24);
_GPIOD_(GPIOX_CRL) |= (2)<<24;
}

inline void pinD6_Output_OD()
{
_GPIOD_(GPIOX_CRL) &= ~((8+1)<<24);
_GPIOD_(GPIOX_CRL) |= (2+4)<<24;
}

inline void pinD6_Output_PP_2()
{
_GPIOD_(GPIOX_CRL) &= ~((8+4+1)<<24);
_GPIOD_(GPIOX_CRL) |= (2)<<24;
}

inline void pinD6_Output_PP_10()
{
_GPIOD_(GPIOX_CRL) &= ~((8+4+2)<<24);
_GPIOD_(GPIOX_CRL) |= (1)<<24;
}

inline void pinD6_Output_PP_50()
{
_GPIOD_(GPIOX_CRL) &= ~((8+4)<<24);
_GPIOD_(GPIOX_CRL) |= (2+1)<<24;
}

inline void pinD6_Output_OD_2()
{
_GPIOD_(GPIOX_CRL) &= ~((8+1)<<24);
_GPIOD_(GPIOX_CRL) |= (2+4)<<24;
}

inline void pinD6_Output_OD_10()
{
_GPIOD_(GPIOX_CRL) &= ~((8+2)<<24);
_GPIOD_(GPIOX_CRL) |= (4+1)<<24;
}

inline void pinD6_Output_OD_50()
{
_GPIOD_(GPIOX_CRL) &= ~((8)<<24);
_GPIOD_(GPIOX_CRL) |= (4+2+1)<<24;
}

inline void pinD6_Output_AFPP_2()
{
_GPIOD_(GPIOX_CRL) &= ~((4+1)<<24);
_GPIOD_(GPIOX_CRL) |= (8+2)<<24;
}

inline void pinD6_Output_AFPP_10()
{
_GPIOD_(GPIOX_CRL) &= ~((4+2)<<24);
_GPIOD_(GPIOX_CRL) |= (8+1)<<24;
}

inline void pinD6_Output_AFPP_50()
{
_GPIOD_(GPIOX_CRL) &= ~((4)<<24);
_GPIOD_(GPIOX_CRL) |= (8+2+1)<<24;
}

inline void pinD6_Output_AFOD_2()
{
_GPIOD_(GPIOX_CRL) &= ~((1)<<24);
_GPIOD_(GPIOX_CRL) |= (8+2+4)<<24;
}

inline void pinD6_Output_AFOD_10()
{
_GPIOD_(GPIOX_CRL) &= ~((2)<<24);
_GPIOD_(GPIOX_CRL) |= (8+4+1)<<24;
}

inline void pinD6_Output_AFOD_50()
{
_GPIOD_(GPIOX_CRL) |= (8+4+2+1)<<24;
}

inline void pinD7_Input()
{
_GPIOD_(GPIOX_CRL) &= ~((8+2+1)<<28);
_GPIOD_(GPIOX_CRL) |= (4)<<28;
}

inline void pinD7_Input_PU()
{
_GPIOD_(GPIOX_CRL) &= ~((4+2+1)<<28);
_GPIOD_(GPIOX_CRL) |= (8)<<28;
_GPIOD_(GPIOX_ODR) |= (1)<<7;
}

inline void pinD7_Input_PD()
{
_GPIOD_(GPIOX_CRL) &= ~((4+2+1)<<28);
_GPIOD_(GPIOX_CRL) |= (8)<<28;
_GPIOD_(GPIOX_ODR) &= ~(1<<7);
}

inline void pinD7_Analog()
{
_GPIOD_(GPIOX_CRL) &= ~((8+4+2+1)<<28);
}

inline void pinD7_Output()
{
_GPIOD_(GPIOX_CRL) &= ~((8+4+1)<<28);
_GPIOD_(GPIOX_CRL) |= (2)<<28;
}

inline void pinD7_Output_OD()
{
_GPIOD_(GPIOX_CRL) &= ~((8+1)<<28);
_GPIOD_(GPIOX_CRL) |= (2+4)<<28;
}

inline void pinD7_Output_PP_2()
{
_GPIOD_(GPIOX_CRL) &= ~((8+4+1)<<28);
_GPIOD_(GPIOX_CRL) |= (2)<<28;
}

inline void pinD7_Output_PP_10()
{
_GPIOD_(GPIOX_CRL) &= ~((8+4+2)<<28);
_GPIOD_(GPIOX_CRL) |= (1)<<28;
}

inline void pinD7_Output_PP_50()
{
_GPIOD_(GPIOX_CRL) &= ~((8+4)<<28);
_GPIOD_(GPIOX_CRL) |= (2+1)<<28;
}

inline void pinD7_Output_OD_2()
{
_GPIOD_(GPIOX_CRL) &= ~((8+1)<<28);
_GPIOD_(GPIOX_CRL) |= (2+4)<<28;
}

inline void pinD7_Output_OD_10()
{
_GPIOD_(GPIOX_CRL) &= ~((8+2)<<28);
_GPIOD_(GPIOX_CRL) |= (4+1)<<28;
}

inline void pinD7_Output_OD_50()
{
_GPIOD_(GPIOX_CRL) &= ~((8)<<28);
_GPIOD_(GPIOX_CRL) |= (4+2+1)<<28;
}

inline void pinD7_Output_AFPP_2()
{
_GPIOD_(GPIOX_CRL) &= ~((4+1)<<28);
_GPIOD_(GPIOX_CRL) |= (8+2)<<28;
}

inline void pinD7_Output_AFPP_10()
{
_GPIOD_(GPIOX_CRL) &= ~((4+2)<<28);
_GPIOD_(GPIOX_CRL) |= (8+1)<<28;
}

inline void pinD7_Output_AFPP_50()
{
_GPIOD_(GPIOX_CRL) &= ~((4)<<28);
_GPIOD_(GPIOX_CRL) |= (8+2+1)<<28;
}

inline void pinD7_Output_AFOD_2()
{
_GPIOD_(GPIOX_CRL) &= ~((1)<<28);
_GPIOD_(GPIOX_CRL) |= (8+2+4)<<28;
}

inline void pinD7_Output_AFOD_10()
{
_GPIOD_(GPIOX_CRL) &= ~((2)<<28);
_GPIOD_(GPIOX_CRL) |= (8+4+1)<<28;
}

inline void pinD7_Output_AFOD_50()
{
_GPIOD_(GPIOX_CRL) |= (8+4+2+1)<<28;
}

inline void pinD8_Input()
{
_GPIOD_(GPIOX_CRH) &= ~((8+2+1)<<0);
_GPIOD_(GPIOX_CRH) |= (4)<<0;
}

inline void pinD8_Input_PU()
{
_GPIOD_(GPIOX_CRH) &= ~((4+2+1)<<0);
_GPIOD_(GPIOX_CRH) |= (8)<<0;
_GPIOD_(GPIOX_ODR) |= (1)<<8;
}

inline void pinD8_Input_PD()
{
_GPIOD_(GPIOX_CRH) &= ~((4+2+1)<<0);
_GPIOD_(GPIOX_CRH) |= (8)<<0;
_GPIOD_(GPIOX_ODR) &= ~(1<<8);
}

inline void pinD8_Analog()
{
_GPIOD_(GPIOX_CRH) &= ~((8+4+2+1)<<0);
}

inline void pinD8_Output()
{
_GPIOD_(GPIOX_CRH) &= ~((8+4+1)<<0);
_GPIOD_(GPIOX_CRH) |= (2)<<0;
}

inline void pinD8_Output_OD()
{
_GPIOD_(GPIOX_CRH) &= ~((8+1)<<0);
_GPIOD_(GPIOX_CRH) |= (2+4)<<0;
}

inline void pinD8_Output_PP_2()
{
_GPIOD_(GPIOX_CRH) &= ~((8+4+1)<<0);
_GPIOD_(GPIOX_CRH) |= (2)<<0;
}

inline void pinD8_Output_PP_10()
{
_GPIOD_(GPIOX_CRH) &= ~((8+4+2)<<0);
_GPIOD_(GPIOX_CRH) |= (1)<<0;
}

inline void pinD8_Output_PP_50()
{
_GPIOD_(GPIOX_CRH) &= ~((8+4)<<0);
_GPIOD_(GPIOX_CRH) |= (2+1)<<0;
}

inline void pinD8_Output_OD_2()
{
_GPIOD_(GPIOX_CRH) &= ~((8+1)<<0);
_GPIOD_(GPIOX_CRH) |= (2+4)<<0;
}

inline void pinD8_Output_OD_10()
{
_GPIOD_(GPIOX_CRH) &= ~((8+2)<<0);
_GPIOD_(GPIOX_CRH) |= (4+1)<<0;
}

inline void pinD8_Output_OD_50()
{
_GPIOD_(GPIOX_CRH) &= ~((8)<<0);
_GPIOD_(GPIOX_CRH) |= (4+2+1)<<0;
}

inline void pinD8_Output_AFPP_2()
{
_GPIOD_(GPIOX_CRH) &= ~((4+1)<<0);
_GPIOD_(GPIOX_CRH) |= (8+2)<<0;
}

inline void pinD8_Output_AFPP_10()
{
_GPIOD_(GPIOX_CRH) &= ~((4+2)<<0);
_GPIOD_(GPIOX_CRH) |= (8+1)<<0;
}

inline void pinD8_Output_AFPP_50()
{
_GPIOD_(GPIOX_CRH) &= ~((4)<<0);
_GPIOD_(GPIOX_CRH) |= (8+2+1)<<0;
}

inline void pinD8_Output_AFOD_2()
{
_GPIOD_(GPIOX_CRH) &= ~((1)<<0);
_GPIOD_(GPIOX_CRH) |= (8+2+4)<<0;
}

inline void pinD8_Output_AFOD_10()
{
_GPIOD_(GPIOX_CRH) &= ~((2)<<0);
_GPIOD_(GPIOX_CRH) |= (8+4+1)<<0;
}

inline void pinD8_Output_AFOD_50()
{
_GPIOD_(GPIOX_CRH) |= (8+4+2+1)<<0;
}

inline void pinD9_Input()
{
_GPIOD_(GPIOX_CRH) &= ~((8+2+1)<<4);
_GPIOD_(GPIOX_CRH) |= (4)<<4;
}

inline void pinD9_Input_PU()
{
_GPIOD_(GPIOX_CRH) &= ~((4+2+1)<<4);
_GPIOD_(GPIOX_CRH) |= (8)<<4;
_GPIOD_(GPIOX_ODR) |= (1)<<9;
}

inline void pinD9_Input_PD()
{
_GPIOD_(GPIOX_CRH) &= ~((4+2+1)<<4);
_GPIOD_(GPIOX_CRH) |= (8)<<4;
_GPIOD_(GPIOX_ODR) &= ~(1<<9);
}

inline void pinD9_Analog()
{
_GPIOD_(GPIOX_CRH) &= ~((8+4+2+1)<<4);
}

inline void pinD9_Output()
{
_GPIOD_(GPIOX_CRH) &= ~((8+4+1)<<4);
_GPIOD_(GPIOX_CRH) |= (2)<<4;
}

inline void pinD9_Output_OD()
{
_GPIOD_(GPIOX_CRH) &= ~((8+1)<<4);
_GPIOD_(GPIOX_CRH) |= (2+4)<<4;
}

inline void pinD9_Output_PP_2()
{
_GPIOD_(GPIOX_CRH) &= ~((8+4+1)<<4);
_GPIOD_(GPIOX_CRH) |= (2)<<4;
}

inline void pinD9_Output_PP_10()
{
_GPIOD_(GPIOX_CRH) &= ~((8+4+2)<<4);
_GPIOD_(GPIOX_CRH) |= (1)<<4;
}

inline void pinD9_Output_PP_50()
{
_GPIOD_(GPIOX_CRH) &= ~((8+4)<<4);
_GPIOD_(GPIOX_CRH) |= (2+1)<<4;
}

inline void pinD9_Output_OD_2()
{
_GPIOD_(GPIOX_CRH) &= ~((8+1)<<4);
_GPIOD_(GPIOX_CRH) |= (2+4)<<4;
}

inline void pinD9_Output_OD_10()
{
_GPIOD_(GPIOX_CRH) &= ~((8+2)<<4);
_GPIOD_(GPIOX_CRH) |= (4+1)<<4;
}

inline void pinD9_Output_OD_50()
{
_GPIOD_(GPIOX_CRH) &= ~((8)<<4);
_GPIOD_(GPIOX_CRH) |= (4+2+1)<<4;
}

inline void pinD9_Output_AFPP_2()
{
_GPIOD_(GPIOX_CRH) &= ~((4+1)<<4);
_GPIOD_(GPIOX_CRH) |= (8+2)<<4;
}

inline void pinD9_Output_AFPP_10()
{
_GPIOD_(GPIOX_CRH) &= ~((4+2)<<4);
_GPIOD_(GPIOX_CRH) |= (8+1)<<4;
}

inline void pinD9_Output_AFPP_50()
{
_GPIOD_(GPIOX_CRH) &= ~((4)<<4);
_GPIOD_(GPIOX_CRH) |= (8+2+1)<<4;
}

inline void pinD9_Output_AFOD_2()
{
_GPIOD_(GPIOX_CRH) &= ~((1)<<4);
_GPIOD_(GPIOX_CRH) |= (8+2+4)<<4;
}

inline void pinD9_Output_AFOD_10()
{
_GPIOD_(GPIOX_CRH) &= ~((2)<<4);
_GPIOD_(GPIOX_CRH) |= (8+4+1)<<4;
}

inline void pinD9_Output_AFOD_50()
{
_GPIOD_(GPIOX_CRH) |= (8+4+2+1)<<4;
}

inline void pinD10_Input()
{
_GPIOD_(GPIOX_CRH) &= ~((8+2+1)<<8);
_GPIOD_(GPIOX_CRH) |= (4)<<8;
}

inline void pinD10_Input_PU()
{
_GPIOD_(GPIOX_CRH) &= ~((4+2+1)<<8);
_GPIOD_(GPIOX_CRH) |= (8)<<8;
_GPIOD_(GPIOX_ODR) |= (1)<<10;
}

inline void pinD10_Input_PD()
{
_GPIOD_(GPIOX_CRH) &= ~((4+2+1)<<8);
_GPIOD_(GPIOX_CRH) |= (8)<<8;
_GPIOD_(GPIOX_ODR) &= ~(1<<10);
}

inline void pinD10_Analog()
{
_GPIOD_(GPIOX_CRH) &= ~((8+4+2+1)<<8);
}

inline void pinD10_Output()
{
_GPIOD_(GPIOX_CRH) &= ~((8+4+1)<<8);
_GPIOD_(GPIOX_CRH) |= (2)<<8;
}

inline void pinD10_Output_OD()
{
_GPIOD_(GPIOX_CRH) &= ~((8+1)<<8);
_GPIOD_(GPIOX_CRH) |= (2+4)<<8;
}

inline void pinD10_Output_PP_2()
{
_GPIOD_(GPIOX_CRH) &= ~((8+4+1)<<8);
_GPIOD_(GPIOX_CRH) |= (2)<<8;
}

inline void pinD10_Output_PP_10()
{
_GPIOD_(GPIOX_CRH) &= ~((8+4+2)<<8);
_GPIOD_(GPIOX_CRH) |= (1)<<8;
}

inline void pinD10_Output_PP_50()
{
_GPIOD_(GPIOX_CRH) &= ~((8+4)<<8);
_GPIOD_(GPIOX_CRH) |= (2+1)<<8;
}

inline void pinD10_Output_OD_2()
{
_GPIOD_(GPIOX_CRH) &= ~((8+1)<<8);
_GPIOD_(GPIOX_CRH) |= (2+4)<<8;
}

inline void pinD10_Output_OD_10()
{
_GPIOD_(GPIOX_CRH) &= ~((8+2)<<8);
_GPIOD_(GPIOX_CRH) |= (4+1)<<8;
}

inline void pinD10_Output_OD_50()
{
_GPIOD_(GPIOX_CRH) &= ~((8)<<8);
_GPIOD_(GPIOX_CRH) |= (4+2+1)<<8;
}

inline void pinD10_Output_AFPP_2()
{
_GPIOD_(GPIOX_CRH) &= ~((4+1)<<8);
_GPIOD_(GPIOX_CRH) |= (8+2)<<8;
}

inline void pinD10_Output_AFPP_10()
{
_GPIOD_(GPIOX_CRH) &= ~((4+2)<<8);
_GPIOD_(GPIOX_CRH) |= (8+1)<<8;
}

inline void pinD10_Output_AFPP_50()
{
_GPIOD_(GPIOX_CRH) &= ~((4)<<8);
_GPIOD_(GPIOX_CRH) |= (8+2+1)<<8;
}

inline void pinD10_Output_AFOD_2()
{
_GPIOD_(GPIOX_CRH) &= ~((1)<<8);
_GPIOD_(GPIOX_CRH) |= (8+2+4)<<8;
}

inline void pinD10_Output_AFOD_10()
{
_GPIOD_(GPIOX_CRH) &= ~((2)<<8);
_GPIOD_(GPIOX_CRH) |= (8+4+1)<<8;
}

inline void pinD10_Output_AFOD_50()
{
_GPIOD_(GPIOX_CRH) |= (8+4+2+1)<<8;
}

inline void pinD11_Input()
{
_GPIOD_(GPIOX_CRH) &= ~((8+2+1)<<12);
_GPIOD_(GPIOX_CRH) |= (4)<<12;
}

inline void pinD11_Input_PU()
{
_GPIOD_(GPIOX_CRH) &= ~((4+2+1)<<12);
_GPIOD_(GPIOX_CRH) |= (8)<<12;
_GPIOD_(GPIOX_ODR) |= (1)<<11;
}

inline void pinD11_Input_PD()
{
_GPIOD_(GPIOX_CRH) &= ~((4+2+1)<<12);
_GPIOD_(GPIOX_CRH) |= (8)<<12;
_GPIOD_(GPIOX_ODR) &= ~(1<<11);
}

inline void pinD11_Analog()
{
_GPIOD_(GPIOX_CRH) &= ~((8+4+2+1)<<12);
}

inline void pinD11_Output()
{
_GPIOD_(GPIOX_CRH) &= ~((8+4+1)<<12);
_GPIOD_(GPIOX_CRH) |= (2)<<12;
}

inline void pinD11_Output_OD()
{
_GPIOD_(GPIOX_CRH) &= ~((8+1)<<12);
_GPIOD_(GPIOX_CRH) |= (2+4)<<12;
}

inline void pinD11_Output_PP_2()
{
_GPIOD_(GPIOX_CRH) &= ~((8+4+1)<<12);
_GPIOD_(GPIOX_CRH) |= (2)<<12;
}

inline void pinD11_Output_PP_10()
{
_GPIOD_(GPIOX_CRH) &= ~((8+4+2)<<12);
_GPIOD_(GPIOX_CRH) |= (1)<<12;
}

inline void pinD11_Output_PP_50()
{
_GPIOD_(GPIOX_CRH) &= ~((8+4)<<12);
_GPIOD_(GPIOX_CRH) |= (2+1)<<12;
}

inline void pinD11_Output_OD_2()
{
_GPIOD_(GPIOX_CRH) &= ~((8+1)<<12);
_GPIOD_(GPIOX_CRH) |= (2+4)<<12;
}

inline void pinD11_Output_OD_10()
{
_GPIOD_(GPIOX_CRH) &= ~((8+2)<<12);
_GPIOD_(GPIOX_CRH) |= (4+1)<<12;
}

inline void pinD11_Output_OD_50()
{
_GPIOD_(GPIOX_CRH) &= ~((8)<<12);
_GPIOD_(GPIOX_CRH) |= (4+2+1)<<12;
}

inline void pinD11_Output_AFPP_2()
{
_GPIOD_(GPIOX_CRH) &= ~((4+1)<<12);
_GPIOD_(GPIOX_CRH) |= (8+2)<<12;
}

inline void pinD11_Output_AFPP_10()
{
_GPIOD_(GPIOX_CRH) &= ~((4+2)<<12);
_GPIOD_(GPIOX_CRH) |= (8+1)<<12;
}

inline void pinD11_Output_AFPP_50()
{
_GPIOD_(GPIOX_CRH) &= ~((4)<<12);
_GPIOD_(GPIOX_CRH) |= (8+2+1)<<12;
}

inline void pinD11_Output_AFOD_2()
{
_GPIOD_(GPIOX_CRH) &= ~((1)<<12);
_GPIOD_(GPIOX_CRH) |= (8+2+4)<<12;
}

inline void pinD11_Output_AFOD_10()
{
_GPIOD_(GPIOX_CRH) &= ~((2)<<12);
_GPIOD_(GPIOX_CRH) |= (8+4+1)<<12;
}

inline void pinD11_Output_AFOD_50()
{
_GPIOD_(GPIOX_CRH) |= (8+4+2+1)<<12;
}

inline void pinD12_Input()
{
_GPIOD_(GPIOX_CRH) &= ~((8+2+1)<<16);
_GPIOD_(GPIOX_CRH) |= (4)<<16;
}

inline void pinD12_Input_PU()
{
_GPIOD_(GPIOX_CRH) &= ~((4+2+1)<<16);
_GPIOD_(GPIOX_CRH) |= (8)<<16;
_GPIOD_(GPIOX_ODR) |= (1)<<12;
}

inline void pinD12_Input_PD()
{
_GPIOD_(GPIOX_CRH) &= ~((4+2+1)<<16);
_GPIOD_(GPIOX_CRH) |= (8)<<16;
_GPIOD_(GPIOX_ODR) &= ~(1<<12);
}

inline void pinD12_Analog()
{
_GPIOD_(GPIOX_CRH) &= ~((8+4+2+1)<<16);
}

inline void pinD12_Output()
{
_GPIOD_(GPIOX_CRH) &= ~((8+4+1)<<16);
_GPIOD_(GPIOX_CRH) |= (2)<<16;
}

inline void pinD12_Output_OD()
{
_GPIOD_(GPIOX_CRH) &= ~((8+1)<<16);
_GPIOD_(GPIOX_CRH) |= (2+4)<<16;
}

inline void pinD12_Output_PP_2()
{
_GPIOD_(GPIOX_CRH) &= ~((8+4+1)<<16);
_GPIOD_(GPIOX_CRH) |= (2)<<16;
}

inline void pinD12_Output_PP_10()
{
_GPIOD_(GPIOX_CRH) &= ~((8+4+2)<<16);
_GPIOD_(GPIOX_CRH) |= (1)<<16;
}

inline void pinD12_Output_PP_50()
{
_GPIOD_(GPIOX_CRH) &= ~((8+4)<<16);
_GPIOD_(GPIOX_CRH) |= (2+1)<<16;
}

inline void pinD12_Output_OD_2()
{
_GPIOD_(GPIOX_CRH) &= ~((8+1)<<16);
_GPIOD_(GPIOX_CRH) |= (2+4)<<16;
}

inline void pinD12_Output_OD_10()
{
_GPIOD_(GPIOX_CRH) &= ~((8+2)<<16);
_GPIOD_(GPIOX_CRH) |= (4+1)<<16;
}

inline void pinD12_Output_OD_50()
{
_GPIOD_(GPIOX_CRH) &= ~((8)<<16);
_GPIOD_(GPIOX_CRH) |= (4+2+1)<<16;
}

inline void pinD12_Output_AFPP_2()
{
_GPIOD_(GPIOX_CRH) &= ~((4+1)<<16);
_GPIOD_(GPIOX_CRH) |= (8+2)<<16;
}

inline void pinD12_Output_AFPP_10()
{
_GPIOD_(GPIOX_CRH) &= ~((4+2)<<16);
_GPIOD_(GPIOX_CRH) |= (8+1)<<16;
}

inline void pinD12_Output_AFPP_50()
{
_GPIOD_(GPIOX_CRH) &= ~((4)<<16);
_GPIOD_(GPIOX_CRH) |= (8+2+1)<<16;
}

inline void pinD12_Output_AFOD_2()
{
_GPIOD_(GPIOX_CRH) &= ~((1)<<16);
_GPIOD_(GPIOX_CRH) |= (8+2+4)<<16;
}

inline void pinD12_Output_AFOD_10()
{
_GPIOD_(GPIOX_CRH) &= ~((2)<<16);
_GPIOD_(GPIOX_CRH) |= (8+4+1)<<16;
}

inline void pinD12_Output_AFOD_50()
{
_GPIOD_(GPIOX_CRH) |= (8+4+2+1)<<16;
}

inline void pinD13_Input()
{
_GPIOD_(GPIOX_CRH) &= ~((8+2+1)<<20);
_GPIOD_(GPIOX_CRH) |= (4)<<20;
}

inline void pinD13_Input_PU()
{
_GPIOD_(GPIOX_CRH) &= ~((4+2+1)<<20);
_GPIOD_(GPIOX_CRH) |= (8)<<20;
_GPIOD_(GPIOX_ODR) |= (1)<<13;
}

inline void pinD13_Input_PD()
{
_GPIOD_(GPIOX_CRH) &= ~((4+2+1)<<20);
_GPIOD_(GPIOX_CRH) |= (8)<<20;
_GPIOD_(GPIOX_ODR) &= ~(1<<13);
}

inline void pinD13_Analog()
{
_GPIOD_(GPIOX_CRH) &= ~((8+4+2+1)<<20);
}

inline void pinD13_Output()
{
_GPIOD_(GPIOX_CRH) &= ~((8+4+1)<<20);
_GPIOD_(GPIOX_CRH) |= (2)<<20;
}

inline void pinD13_Output_OD()
{
_GPIOD_(GPIOX_CRH) &= ~((8+1)<<20);
_GPIOD_(GPIOX_CRH) |= (2+4)<<20;
}

inline void pinD13_Output_PP_2()
{
_GPIOD_(GPIOX_CRH) &= ~((8+4+1)<<20);
_GPIOD_(GPIOX_CRH) |= (2)<<20;
}

inline void pinD13_Output_PP_10()
{
_GPIOD_(GPIOX_CRH) &= ~((8+4+2)<<20);
_GPIOD_(GPIOX_CRH) |= (1)<<20;
}

inline void pinD13_Output_PP_50()
{
_GPIOD_(GPIOX_CRH) &= ~((8+4)<<20);
_GPIOD_(GPIOX_CRH) |= (2+1)<<20;
}

inline void pinD13_Output_OD_2()
{
_GPIOD_(GPIOX_CRH) &= ~((8+1)<<20);
_GPIOD_(GPIOX_CRH) |= (2+4)<<20;
}

inline void pinD13_Output_OD_10()
{
_GPIOD_(GPIOX_CRH) &= ~((8+2)<<20);
_GPIOD_(GPIOX_CRH) |= (4+1)<<20;
}

inline void pinD13_Output_OD_50()
{
_GPIOD_(GPIOX_CRH) &= ~((8)<<20);
_GPIOD_(GPIOX_CRH) |= (4+2+1)<<20;
}

inline void pinD13_Output_AFPP_2()
{
_GPIOD_(GPIOX_CRH) &= ~((4+1)<<20);
_GPIOD_(GPIOX_CRH) |= (8+2)<<20;
}

inline void pinD13_Output_AFPP_10()
{
_GPIOD_(GPIOX_CRH) &= ~((4+2)<<20);
_GPIOD_(GPIOX_CRH) |= (8+1)<<20;
}

inline void pinD13_Output_AFPP_50()
{
_GPIOD_(GPIOX_CRH) &= ~((4)<<20);
_GPIOD_(GPIOX_CRH) |= (8+2+1)<<20;
}

inline void pinD13_Output_AFOD_2()
{
_GPIOD_(GPIOX_CRH) &= ~((1)<<20);
_GPIOD_(GPIOX_CRH) |= (8+2+4)<<20;
}

inline void pinD13_Output_AFOD_10()
{
_GPIOD_(GPIOX_CRH) &= ~((2)<<20);
_GPIOD_(GPIOX_CRH) |= (8+4+1)<<20;
}

inline void pinD13_Output_AFOD_50()
{
_GPIOD_(GPIOX_CRH) |= (8+4+2+1)<<20;
}

inline void pinD14_Input()
{
_GPIOD_(GPIOX_CRH) &= ~((8+2+1)<<24);
_GPIOD_(GPIOX_CRH) |= (4)<<24;
}

inline void pinD14_Input_PU()
{
_GPIOD_(GPIOX_CRH) &= ~((4+2+1)<<24);
_GPIOD_(GPIOX_CRH) |= (8)<<24;
_GPIOD_(GPIOX_ODR) |= (1)<<14;
}

inline void pinD14_Input_PD()
{
_GPIOD_(GPIOX_CRH) &= ~((4+2+1)<<24);
_GPIOD_(GPIOX_CRH) |= (8)<<24;
_GPIOD_(GPIOX_ODR) &= ~(1<<14);
}

inline void pinD14_Analog()
{
_GPIOD_(GPIOX_CRH) &= ~((8+4+2+1)<<24);
}

inline void pinD14_Output()
{
_GPIOD_(GPIOX_CRH) &= ~((8+4+1)<<24);
_GPIOD_(GPIOX_CRH) |= (2)<<24;
}

inline void pinD14_Output_OD()
{
_GPIOD_(GPIOX_CRH) &= ~((8+1)<<24);
_GPIOD_(GPIOX_CRH) |= (2+4)<<24;
}

inline void pinD14_Output_PP_2()
{
_GPIOD_(GPIOX_CRH) &= ~((8+4+1)<<24);
_GPIOD_(GPIOX_CRH) |= (2)<<24;
}

inline void pinD14_Output_PP_10()
{
_GPIOD_(GPIOX_CRH) &= ~((8+4+2)<<24);
_GPIOD_(GPIOX_CRH) |= (1)<<24;
}

inline void pinD14_Output_PP_50()
{
_GPIOD_(GPIOX_CRH) &= ~((8+4)<<24);
_GPIOD_(GPIOX_CRH) |= (2+1)<<24;
}

inline void pinD14_Output_OD_2()
{
_GPIOD_(GPIOX_CRH) &= ~((8+1)<<24);
_GPIOD_(GPIOX_CRH) |= (2+4)<<24;
}

inline void pinD14_Output_OD_10()
{
_GPIOD_(GPIOX_CRH) &= ~((8+2)<<24);
_GPIOD_(GPIOX_CRH) |= (4+1)<<24;
}

inline void pinD14_Output_OD_50()
{
_GPIOD_(GPIOX_CRH) &= ~((8)<<24);
_GPIOD_(GPIOX_CRH) |= (4+2+1)<<24;
}

inline void pinD14_Output_AFPP_2()
{
_GPIOD_(GPIOX_CRH) &= ~((4+1)<<24);
_GPIOD_(GPIOX_CRH) |= (8+2)<<24;
}

inline void pinD14_Output_AFPP_10()
{
_GPIOD_(GPIOX_CRH) &= ~((4+2)<<24);
_GPIOD_(GPIOX_CRH) |= (8+1)<<24;
}

inline void pinD14_Output_AFPP_50()
{
_GPIOD_(GPIOX_CRH) &= ~((4)<<24);
_GPIOD_(GPIOX_CRH) |= (8+2+1)<<24;
}

inline void pinD14_Output_AFOD_2()
{
_GPIOD_(GPIOX_CRH) &= ~((1)<<24);
_GPIOD_(GPIOX_CRH) |= (8+2+4)<<24;
}

inline void pinD14_Output_AFOD_10()
{
_GPIOD_(GPIOX_CRH) &= ~((2)<<24);
_GPIOD_(GPIOX_CRH) |= (8+4+1)<<24;
}

inline void pinD14_Output_AFOD_50()
{
_GPIOD_(GPIOX_CRH) |= (8+4+2+1)<<24;
}

inline void pinD15_Input()
{
_GPIOD_(GPIOX_CRH) &= ~((8+2+1)<<28);
_GPIOD_(GPIOX_CRH) |= (4)<<28;
}

inline void pinD15_Input_PU()
{
_GPIOD_(GPIOX_CRH) &= ~((4+2+1)<<28);
_GPIOD_(GPIOX_CRH) |= (8)<<28;
_GPIOD_(GPIOX_ODR) |= (1)<<15;
}

inline void pinD15_Input_PD()
{
_GPIOD_(GPIOX_CRH) &= ~((4+2+1)<<28);
_GPIOD_(GPIOX_CRH) |= (8)<<28;
_GPIOD_(GPIOX_ODR) &= ~(1<<15);
}

inline void pinD15_Analog()
{
_GPIOD_(GPIOX_CRH) &= ~((8+4+2+1)<<28);
}

inline void pinD15_Output()
{
_GPIOD_(GPIOX_CRH) &= ~((8+4+1)<<28);
_GPIOD_(GPIOX_CRH) |= (2)<<28;
}

inline void pinD15_Output_OD()
{
_GPIOD_(GPIOX_CRH) &= ~((8+1)<<28);
_GPIOD_(GPIOX_CRH) |= (2+4)<<28;
}

inline void pinD15_Output_PP_2()
{
_GPIOD_(GPIOX_CRH) &= ~((8+4+1)<<28);
_GPIOD_(GPIOX_CRH) |= (2)<<28;
}

inline void pinD15_Output_PP_10()
{
_GPIOD_(GPIOX_CRH) &= ~((8+4+2)<<28);
_GPIOD_(GPIOX_CRH) |= (1)<<28;
}

inline void pinD15_Output_PP_50()
{
_GPIOD_(GPIOX_CRH) &= ~((8+4)<<28);
_GPIOD_(GPIOX_CRH) |= (2+1)<<28;
}

inline void pinD15_Output_OD_2()
{
_GPIOD_(GPIOX_CRH) &= ~((8+1)<<28);
_GPIOD_(GPIOX_CRH) |= (2+4)<<28;
}

inline void pinD15_Output_OD_10()
{
_GPIOD_(GPIOX_CRH) &= ~((8+2)<<28);
_GPIOD_(GPIOX_CRH) |= (4+1)<<28;
}

inline void pinD15_Output_OD_50()
{
_GPIOD_(GPIOX_CRH) &= ~((8)<<28);
_GPIOD_(GPIOX_CRH) |= (4+2+1)<<28;
}

inline void pinD15_Output_AFPP_2()
{
_GPIOD_(GPIOX_CRH) &= ~((4+1)<<28);
_GPIOD_(GPIOX_CRH) |= (8+2)<<28;
}

inline void pinD15_Output_AFPP_10()
{
_GPIOD_(GPIOX_CRH) &= ~((4+2)<<28);
_GPIOD_(GPIOX_CRH) |= (8+1)<<28;
}

inline void pinD15_Output_AFPP_50()
{
_GPIOD_(GPIOX_CRH) &= ~((4)<<28);
_GPIOD_(GPIOX_CRH) |= (8+2+1)<<28;
}

inline void pinD15_Output_AFOD_2()
{
_GPIOD_(GPIOX_CRH) &= ~((1)<<28);
_GPIOD_(GPIOX_CRH) |= (8+2+4)<<28;
}

inline void pinD15_Output_AFOD_10()
{
_GPIOD_(GPIOX_CRH) &= ~((2)<<28);
_GPIOD_(GPIOX_CRH) |= (8+4+1)<<28;
}

inline void pinD15_Output_AFOD_50()
{
_GPIOD_(GPIOX_CRH) |= (8+4+2+1)<<28;
}

inline uint8_t readPinD0()
{
return ((_GPIOD_(GPIOX_IDR)>>0) & 1);
}

inline void setPinD0()
{
_GPIOD_(GPIOX_BSRR) = (1<<0);
}

inline void resetPinD0()
{
_GPIOD_(GPIOX_BRR) = (1<<0);
}

inline uint8_t readPinD1()
{
return ((_GPIOD_(GPIOX_IDR)>>1) & 1);
}

inline void setPinD1()
{
_GPIOD_(GPIOX_BSRR) = (1<<1);
}

inline void resetPinD1()
{
_GPIOD_(GPIOX_BRR) = (1<<1);
}

inline uint8_t readPinD2()
{
return ((_GPIOD_(GPIOX_IDR)>>2) & 1);
}

inline void setPinD2()
{
_GPIOD_(GPIOX_BSRR) = (1<<2);
}

inline void resetPinD2()
{
_GPIOD_(GPIOX_BRR) = (1<<2);
}

inline uint8_t readPinD3()
{
return ((_GPIOD_(GPIOX_IDR)>>3) & 1);
}

inline void setPinD3()
{
_GPIOD_(GPIOX_BSRR) = (1<<3);
}

inline void resetPinD3()
{
_GPIOD_(GPIOX_BRR) = (1<<3);
}

inline uint8_t readPinD4()
{
return ((_GPIOD_(GPIOX_IDR)>>4) & 1);
}

inline void setPinD4()
{
_GPIOD_(GPIOX_BSRR) = (1<<4);
}

inline void resetPinD4()
{
_GPIOD_(GPIOX_BRR) = (1<<4);
}

inline uint8_t readPinD5()
{
return ((_GPIOD_(GPIOX_IDR)>>5) & 1);
}

inline void setPinD5()
{
_GPIOD_(GPIOX_BSRR) = (1<<5);
}

inline void resetPinD5()
{
_GPIOD_(GPIOX_BRR) = (1<<5);
}

inline uint8_t readPinD6()
{
return ((_GPIOD_(GPIOX_IDR)>>6) & 1);
}

inline void setPinD6()
{
_GPIOD_(GPIOX_BSRR) = (1<<6);
}

inline void resetPinD6()
{
_GPIOD_(GPIOX_BRR) = (1<<6);
}

inline uint8_t readPinD7()
{
return ((_GPIOD_(GPIOX_IDR)>>7) & 1);
}

inline void setPinD7()
{
_GPIOD_(GPIOX_BSRR) = (1<<7);
}

inline void resetPinD7()
{
_GPIOD_(GPIOX_BRR) = (1<<7);
}

inline uint8_t readPinD8()
{
return ((_GPIOD_(GPIOX_IDR)>>8) & 1);
}

inline void setPinD8()
{
_GPIOD_(GPIOX_BSRR) = (1<<8);
}

inline void resetPinD8()
{
_GPIOD_(GPIOX_BRR) = (1<<8);
}

inline uint8_t readPinD9()
{
return ((_GPIOD_(GPIOX_IDR)>>9) & 1);
}

inline void setPinD9()
{
_GPIOD_(GPIOX_BSRR) = (1<<9);
}

inline void resetPinD9()
{
_GPIOD_(GPIOX_BRR) = (1<<9);
}

inline uint8_t readPinD10()
{
return ((_GPIOD_(GPIOX_IDR)>>10) & 1);
}

inline void setPinD10()
{
_GPIOD_(GPIOX_BSRR) = (1<<10);
}

inline void resetPinD10()
{
_GPIOD_(GPIOX_BRR) = (1<<10);
}

inline uint8_t readPinD11()
{
return ((_GPIOD_(GPIOX_IDR)>>11) & 1);
}

inline void setPinD11()
{
_GPIOD_(GPIOX_BSRR) = (1<<11);
}

inline void resetPinD11()
{
_GPIOD_(GPIOX_BRR) = (1<<11);
}

inline uint8_t readPinD12()
{
return ((_GPIOD_(GPIOX_IDR)>>12) & 1);
}

inline void setPinD12()
{
_GPIOD_(GPIOX_BSRR) = (1<<12);
}

inline void resetPinD12()
{
_GPIOD_(GPIOX_BRR) = (1<<12);
}

inline uint8_t readPinD13()
{
return ((_GPIOD_(GPIOX_IDR)>>13) & 1);
}

inline void setPinD13()
{
_GPIOD_(GPIOX_BSRR) = (1<<13);
}

inline void resetPinD13()
{
_GPIOD_(GPIOX_BRR) = (1<<13);
}

inline uint8_t readPinD14()
{
return ((_GPIOD_(GPIOX_IDR)>>14) & 1);
}

inline void setPinD14()
{
_GPIOD_(GPIOX_BSRR) = (1<<14);
}

inline void resetPinD14()
{
_GPIOD_(GPIOX_BRR) = (1<<14);
}

inline uint8_t readPinD15()
{
return ((_GPIOD_(GPIOX_IDR)>>15) & 1);
}

inline void setPinD15()
{
_GPIOD_(GPIOX_BSRR) = (1<<15);
}

inline void resetPinD15()
{
_GPIOD_(GPIOX_BRR) = (1<<15);
}

inline void pinE0_Input()
{
_GPIOE_(GPIOX_CRL) &= ~((8+2+1)<<0);
_GPIOE_(GPIOX_CRL) |= (4)<<0;
}

inline void pinE0_Input_PU()
{
_GPIOE_(GPIOX_CRL) &= ~((4+2+1)<<0);
_GPIOE_(GPIOX_CRL) |= (8)<<0;
_GPIOE_(GPIOX_ODR) |= (1)<<0;
}

inline void pinE0_Input_PD()
{
_GPIOE_(GPIOX_CRL) &= ~((4+2+1)<<0);
_GPIOE_(GPIOX_CRL) |= (8)<<0;
_GPIOE_(GPIOX_ODR) &= ~(1<<0);
}

inline void pinE0_Analog()
{
_GPIOE_(GPIOX_CRL) &= ~((8+4+2+1)<<0);
}

inline void pinE0_Output()
{
_GPIOE_(GPIOX_CRL) &= ~((8+4+1)<<0);
_GPIOE_(GPIOX_CRL) |= (2)<<0;
}

inline void pinE0_Output_OD()
{
_GPIOE_(GPIOX_CRL) &= ~((8+1)<<0);
_GPIOE_(GPIOX_CRL) |= (2+4)<<0;
}

inline void pinE0_Output_PP_2()
{
_GPIOE_(GPIOX_CRL) &= ~((8+4+1)<<0);
_GPIOE_(GPIOX_CRL) |= (2)<<0;
}

inline void pinE0_Output_PP_10()
{
_GPIOE_(GPIOX_CRL) &= ~((8+4+2)<<0);
_GPIOE_(GPIOX_CRL) |= (1)<<0;
}

inline void pinE0_Output_PP_50()
{
_GPIOE_(GPIOX_CRL) &= ~((8+4)<<0);
_GPIOE_(GPIOX_CRL) |= (2+1)<<0;
}

inline void pinE0_Output_OD_2()
{
_GPIOE_(GPIOX_CRL) &= ~((8+1)<<0);
_GPIOE_(GPIOX_CRL) |= (2+4)<<0;
}

inline void pinE0_Output_OD_10()
{
_GPIOE_(GPIOX_CRL) &= ~((8+2)<<0);
_GPIOE_(GPIOX_CRL) |= (4+1)<<0;
}

inline void pinE0_Output_OD_50()
{
_GPIOE_(GPIOX_CRL) &= ~((8)<<0);
_GPIOE_(GPIOX_CRL) |= (4+2+1)<<0;
}

inline void pinE0_Output_AFPP_2()
{
_GPIOE_(GPIOX_CRL) &= ~((4+1)<<0);
_GPIOE_(GPIOX_CRL) |= (8+2)<<0;
}

inline void pinE0_Output_AFPP_10()
{
_GPIOE_(GPIOX_CRL) &= ~((4+2)<<0);
_GPIOE_(GPIOX_CRL) |= (8+1)<<0;
}

inline void pinE0_Output_AFPP_50()
{
_GPIOE_(GPIOX_CRL) &= ~((4)<<0);
_GPIOE_(GPIOX_CRL) |= (8+2+1)<<0;
}

inline void pinE0_Output_AFOD_2()
{
_GPIOE_(GPIOX_CRL) &= ~((1)<<0);
_GPIOE_(GPIOX_CRL) |= (8+2+4)<<0;
}

inline void pinE0_Output_AFOD_10()
{
_GPIOE_(GPIOX_CRL) &= ~((2)<<0);
_GPIOE_(GPIOX_CRL) |= (8+4+1)<<0;
}

inline void pinE0_Output_AFOD_50()
{
_GPIOE_(GPIOX_CRL) |= (8+4+2+1)<<0;
}

inline void pinE1_Input()
{
_GPIOE_(GPIOX_CRL) &= ~((8+2+1)<<4);
_GPIOE_(GPIOX_CRL) |= (4)<<4;
}

inline void pinE1_Input_PU()
{
_GPIOE_(GPIOX_CRL) &= ~((4+2+1)<<4);
_GPIOE_(GPIOX_CRL) |= (8)<<4;
_GPIOE_(GPIOX_ODR) |= (1)<<1;
}

inline void pinE1_Input_PD()
{
_GPIOE_(GPIOX_CRL) &= ~((4+2+1)<<4);
_GPIOE_(GPIOX_CRL) |= (8)<<4;
_GPIOE_(GPIOX_ODR) &= ~(1<<1);
}

inline void pinE1_Analog()
{
_GPIOE_(GPIOX_CRL) &= ~((8+4+2+1)<<4);
}

inline void pinE1_Output()
{
_GPIOE_(GPIOX_CRL) &= ~((8+4+1)<<4);
_GPIOE_(GPIOX_CRL) |= (2)<<4;
}

inline void pinE1_Output_OD()
{
_GPIOE_(GPIOX_CRL) &= ~((8+1)<<4);
_GPIOE_(GPIOX_CRL) |= (2+4)<<4;
}

inline void pinE1_Output_PP_2()
{
_GPIOE_(GPIOX_CRL) &= ~((8+4+1)<<4);
_GPIOE_(GPIOX_CRL) |= (2)<<4;
}

inline void pinE1_Output_PP_10()
{
_GPIOE_(GPIOX_CRL) &= ~((8+4+2)<<4);
_GPIOE_(GPIOX_CRL) |= (1)<<4;
}

inline void pinE1_Output_PP_50()
{
_GPIOE_(GPIOX_CRL) &= ~((8+4)<<4);
_GPIOE_(GPIOX_CRL) |= (2+1)<<4;
}

inline void pinE1_Output_OD_2()
{
_GPIOE_(GPIOX_CRL) &= ~((8+1)<<4);
_GPIOE_(GPIOX_CRL) |= (2+4)<<4;
}

inline void pinE1_Output_OD_10()
{
_GPIOE_(GPIOX_CRL) &= ~((8+2)<<4);
_GPIOE_(GPIOX_CRL) |= (4+1)<<4;
}

inline void pinE1_Output_OD_50()
{
_GPIOE_(GPIOX_CRL) &= ~((8)<<4);
_GPIOE_(GPIOX_CRL) |= (4+2+1)<<4;
}

inline void pinE1_Output_AFPP_2()
{
_GPIOE_(GPIOX_CRL) &= ~((4+1)<<4);
_GPIOE_(GPIOX_CRL) |= (8+2)<<4;
}

inline void pinE1_Output_AFPP_10()
{
_GPIOE_(GPIOX_CRL) &= ~((4+2)<<4);
_GPIOE_(GPIOX_CRL) |= (8+1)<<4;
}

inline void pinE1_Output_AFPP_50()
{
_GPIOE_(GPIOX_CRL) &= ~((4)<<4);
_GPIOE_(GPIOX_CRL) |= (8+2+1)<<4;
}

inline void pinE1_Output_AFOD_2()
{
_GPIOE_(GPIOX_CRL) &= ~((1)<<4);
_GPIOE_(GPIOX_CRL) |= (8+2+4)<<4;
}

inline void pinE1_Output_AFOD_10()
{
_GPIOE_(GPIOX_CRL) &= ~((2)<<4);
_GPIOE_(GPIOX_CRL) |= (8+4+1)<<4;
}

inline void pinE1_Output_AFOD_50()
{
_GPIOE_(GPIOX_CRL) |= (8+4+2+1)<<4;
}

inline void pinE2_Input()
{
_GPIOE_(GPIOX_CRL) &= ~((8+2+1)<<8);
_GPIOE_(GPIOX_CRL) |= (4)<<8;
}

inline void pinE2_Input_PU()
{
_GPIOE_(GPIOX_CRL) &= ~((4+2+1)<<8);
_GPIOE_(GPIOX_CRL) |= (8)<<8;
_GPIOE_(GPIOX_ODR) |= (1)<<2;
}

inline void pinE2_Input_PD()
{
_GPIOE_(GPIOX_CRL) &= ~((4+2+1)<<8);
_GPIOE_(GPIOX_CRL) |= (8)<<8;
_GPIOE_(GPIOX_ODR) &= ~(1<<2);
}

inline void pinE2_Analog()
{
_GPIOE_(GPIOX_CRL) &= ~((8+4+2+1)<<8);
}

inline void pinE2_Output()
{
_GPIOE_(GPIOX_CRL) &= ~((8+4+1)<<8);
_GPIOE_(GPIOX_CRL) |= (2)<<8;
}

inline void pinE2_Output_OD()
{
_GPIOE_(GPIOX_CRL) &= ~((8+1)<<8);
_GPIOE_(GPIOX_CRL) |= (2+4)<<8;
}

inline void pinE2_Output_PP_2()
{
_GPIOE_(GPIOX_CRL) &= ~((8+4+1)<<8);
_GPIOE_(GPIOX_CRL) |= (2)<<8;
}

inline void pinE2_Output_PP_10()
{
_GPIOE_(GPIOX_CRL) &= ~((8+4+2)<<8);
_GPIOE_(GPIOX_CRL) |= (1)<<8;
}

inline void pinE2_Output_PP_50()
{
_GPIOE_(GPIOX_CRL) &= ~((8+4)<<8);
_GPIOE_(GPIOX_CRL) |= (2+1)<<8;
}

inline void pinE2_Output_OD_2()
{
_GPIOE_(GPIOX_CRL) &= ~((8+1)<<8);
_GPIOE_(GPIOX_CRL) |= (2+4)<<8;
}

inline void pinE2_Output_OD_10()
{
_GPIOE_(GPIOX_CRL) &= ~((8+2)<<8);
_GPIOE_(GPIOX_CRL) |= (4+1)<<8;
}

inline void pinE2_Output_OD_50()
{
_GPIOE_(GPIOX_CRL) &= ~((8)<<8);
_GPIOE_(GPIOX_CRL) |= (4+2+1)<<8;
}

inline void pinE2_Output_AFPP_2()
{
_GPIOE_(GPIOX_CRL) &= ~((4+1)<<8);
_GPIOE_(GPIOX_CRL) |= (8+2)<<8;
}

inline void pinE2_Output_AFPP_10()
{
_GPIOE_(GPIOX_CRL) &= ~((4+2)<<8);
_GPIOE_(GPIOX_CRL) |= (8+1)<<8;
}

inline void pinE2_Output_AFPP_50()
{
_GPIOE_(GPIOX_CRL) &= ~((4)<<8);
_GPIOE_(GPIOX_CRL) |= (8+2+1)<<8;
}

inline void pinE2_Output_AFOD_2()
{
_GPIOE_(GPIOX_CRL) &= ~((1)<<8);
_GPIOE_(GPIOX_CRL) |= (8+2+4)<<8;
}

inline void pinE2_Output_AFOD_10()
{
_GPIOE_(GPIOX_CRL) &= ~((2)<<8);
_GPIOE_(GPIOX_CRL) |= (8+4+1)<<8;
}

inline void pinE2_Output_AFOD_50()
{
_GPIOE_(GPIOX_CRL) |= (8+4+2+1)<<8;
}

inline void pinE3_Input()
{
_GPIOE_(GPIOX_CRL) &= ~((8+2+1)<<12);
_GPIOE_(GPIOX_CRL) |= (4)<<12;
}

inline void pinE3_Input_PU()
{
_GPIOE_(GPIOX_CRL) &= ~((4+2+1)<<12);
_GPIOE_(GPIOX_CRL) |= (8)<<12;
_GPIOE_(GPIOX_ODR) |= (1)<<3;
}

inline void pinE3_Input_PD()
{
_GPIOE_(GPIOX_CRL) &= ~((4+2+1)<<12);
_GPIOE_(GPIOX_CRL) |= (8)<<12;
_GPIOE_(GPIOX_ODR) &= ~(1<<3);
}

inline void pinE3_Analog()
{
_GPIOE_(GPIOX_CRL) &= ~((8+4+2+1)<<12);
}

inline void pinE3_Output()
{
_GPIOE_(GPIOX_CRL) &= ~((8+4+1)<<12);
_GPIOE_(GPIOX_CRL) |= (2)<<12;
}

inline void pinE3_Output_OD()
{
_GPIOE_(GPIOX_CRL) &= ~((8+1)<<12);
_GPIOE_(GPIOX_CRL) |= (2+4)<<12;
}

inline void pinE3_Output_PP_2()
{
_GPIOE_(GPIOX_CRL) &= ~((8+4+1)<<12);
_GPIOE_(GPIOX_CRL) |= (2)<<12;
}

inline void pinE3_Output_PP_10()
{
_GPIOE_(GPIOX_CRL) &= ~((8+4+2)<<12);
_GPIOE_(GPIOX_CRL) |= (1)<<12;
}

inline void pinE3_Output_PP_50()
{
_GPIOE_(GPIOX_CRL) &= ~((8+4)<<12);
_GPIOE_(GPIOX_CRL) |= (2+1)<<12;
}

inline void pinE3_Output_OD_2()
{
_GPIOE_(GPIOX_CRL) &= ~((8+1)<<12);
_GPIOE_(GPIOX_CRL) |= (2+4)<<12;
}

inline void pinE3_Output_OD_10()
{
_GPIOE_(GPIOX_CRL) &= ~((8+2)<<12);
_GPIOE_(GPIOX_CRL) |= (4+1)<<12;
}

inline void pinE3_Output_OD_50()
{
_GPIOE_(GPIOX_CRL) &= ~((8)<<12);
_GPIOE_(GPIOX_CRL) |= (4+2+1)<<12;
}

inline void pinE3_Output_AFPP_2()
{
_GPIOE_(GPIOX_CRL) &= ~((4+1)<<12);
_GPIOE_(GPIOX_CRL) |= (8+2)<<12;
}

inline void pinE3_Output_AFPP_10()
{
_GPIOE_(GPIOX_CRL) &= ~((4+2)<<12);
_GPIOE_(GPIOX_CRL) |= (8+1)<<12;
}

inline void pinE3_Output_AFPP_50()
{
_GPIOE_(GPIOX_CRL) &= ~((4)<<12);
_GPIOE_(GPIOX_CRL) |= (8+2+1)<<12;
}

inline void pinE3_Output_AFOD_2()
{
_GPIOE_(GPIOX_CRL) &= ~((1)<<12);
_GPIOE_(GPIOX_CRL) |= (8+2+4)<<12;
}

inline void pinE3_Output_AFOD_10()
{
_GPIOE_(GPIOX_CRL) &= ~((2)<<12);
_GPIOE_(GPIOX_CRL) |= (8+4+1)<<12;
}

inline void pinE3_Output_AFOD_50()
{
_GPIOE_(GPIOX_CRL) |= (8+4+2+1)<<12;
}

inline void pinE4_Input()
{
_GPIOE_(GPIOX_CRL) &= ~((8+2+1)<<16);
_GPIOE_(GPIOX_CRL) |= (4)<<16;
}

inline void pinE4_Input_PU()
{
_GPIOE_(GPIOX_CRL) &= ~((4+2+1)<<16);
_GPIOE_(GPIOX_CRL) |= (8)<<16;
_GPIOE_(GPIOX_ODR) |= (1)<<4;
}

inline void pinE4_Input_PD()
{
_GPIOE_(GPIOX_CRL) &= ~((4+2+1)<<16);
_GPIOE_(GPIOX_CRL) |= (8)<<16;
_GPIOE_(GPIOX_ODR) &= ~(1<<4);
}

inline void pinE4_Analog()
{
_GPIOE_(GPIOX_CRL) &= ~((8+4+2+1)<<16);
}

inline void pinE4_Output()
{
_GPIOE_(GPIOX_CRL) &= ~((8+4+1)<<16);
_GPIOE_(GPIOX_CRL) |= (2)<<16;
}

inline void pinE4_Output_OD()
{
_GPIOE_(GPIOX_CRL) &= ~((8+1)<<16);
_GPIOE_(GPIOX_CRL) |= (2+4)<<16;
}

inline void pinE4_Output_PP_2()
{
_GPIOE_(GPIOX_CRL) &= ~((8+4+1)<<16);
_GPIOE_(GPIOX_CRL) |= (2)<<16;
}

inline void pinE4_Output_PP_10()
{
_GPIOE_(GPIOX_CRL) &= ~((8+4+2)<<16);
_GPIOE_(GPIOX_CRL) |= (1)<<16;
}

inline void pinE4_Output_PP_50()
{
_GPIOE_(GPIOX_CRL) &= ~((8+4)<<16);
_GPIOE_(GPIOX_CRL) |= (2+1)<<16;
}

inline void pinE4_Output_OD_2()
{
_GPIOE_(GPIOX_CRL) &= ~((8+1)<<16);
_GPIOE_(GPIOX_CRL) |= (2+4)<<16;
}

inline void pinE4_Output_OD_10()
{
_GPIOE_(GPIOX_CRL) &= ~((8+2)<<16);
_GPIOE_(GPIOX_CRL) |= (4+1)<<16;
}

inline void pinE4_Output_OD_50()
{
_GPIOE_(GPIOX_CRL) &= ~((8)<<16);
_GPIOE_(GPIOX_CRL) |= (4+2+1)<<16;
}

inline void pinE4_Output_AFPP_2()
{
_GPIOE_(GPIOX_CRL) &= ~((4+1)<<16);
_GPIOE_(GPIOX_CRL) |= (8+2)<<16;
}

inline void pinE4_Output_AFPP_10()
{
_GPIOE_(GPIOX_CRL) &= ~((4+2)<<16);
_GPIOE_(GPIOX_CRL) |= (8+1)<<16;
}

inline void pinE4_Output_AFPP_50()
{
_GPIOE_(GPIOX_CRL) &= ~((4)<<16);
_GPIOE_(GPIOX_CRL) |= (8+2+1)<<16;
}

inline void pinE4_Output_AFOD_2()
{
_GPIOE_(GPIOX_CRL) &= ~((1)<<16);
_GPIOE_(GPIOX_CRL) |= (8+2+4)<<16;
}

inline void pinE4_Output_AFOD_10()
{
_GPIOE_(GPIOX_CRL) &= ~((2)<<16);
_GPIOE_(GPIOX_CRL) |= (8+4+1)<<16;
}

inline void pinE4_Output_AFOD_50()
{
_GPIOE_(GPIOX_CRL) |= (8+4+2+1)<<16;
}

inline void pinE5_Input()
{
_GPIOE_(GPIOX_CRL) &= ~((8+2+1)<<20);
_GPIOE_(GPIOX_CRL) |= (4)<<20;
}

inline void pinE5_Input_PU()
{
_GPIOE_(GPIOX_CRL) &= ~((4+2+1)<<20);
_GPIOE_(GPIOX_CRL) |= (8)<<20;
_GPIOE_(GPIOX_ODR) |= (1)<<5;
}

inline void pinE5_Input_PD()
{
_GPIOE_(GPIOX_CRL) &= ~((4+2+1)<<20);
_GPIOE_(GPIOX_CRL) |= (8)<<20;
_GPIOE_(GPIOX_ODR) &= ~(1<<5);
}

inline void pinE5_Analog()
{
_GPIOE_(GPIOX_CRL) &= ~((8+4+2+1)<<20);
}

inline void pinE5_Output()
{
_GPIOE_(GPIOX_CRL) &= ~((8+4+1)<<20);
_GPIOE_(GPIOX_CRL) |= (2)<<20;
}

inline void pinE5_Output_OD()
{
_GPIOE_(GPIOX_CRL) &= ~((8+1)<<20);
_GPIOE_(GPIOX_CRL) |= (2+4)<<20;
}

inline void pinE5_Output_PP_2()
{
_GPIOE_(GPIOX_CRL) &= ~((8+4+1)<<20);
_GPIOE_(GPIOX_CRL) |= (2)<<20;
}

inline void pinE5_Output_PP_10()
{
_GPIOE_(GPIOX_CRL) &= ~((8+4+2)<<20);
_GPIOE_(GPIOX_CRL) |= (1)<<20;
}

inline void pinE5_Output_PP_50()
{
_GPIOE_(GPIOX_CRL) &= ~((8+4)<<20);
_GPIOE_(GPIOX_CRL) |= (2+1)<<20;
}

inline void pinE5_Output_OD_2()
{
_GPIOE_(GPIOX_CRL) &= ~((8+1)<<20);
_GPIOE_(GPIOX_CRL) |= (2+4)<<20;
}

inline void pinE5_Output_OD_10()
{
_GPIOE_(GPIOX_CRL) &= ~((8+2)<<20);
_GPIOE_(GPIOX_CRL) |= (4+1)<<20;
}

inline void pinE5_Output_OD_50()
{
_GPIOE_(GPIOX_CRL) &= ~((8)<<20);
_GPIOE_(GPIOX_CRL) |= (4+2+1)<<20;
}

inline void pinE5_Output_AFPP_2()
{
_GPIOE_(GPIOX_CRL) &= ~((4+1)<<20);
_GPIOE_(GPIOX_CRL) |= (8+2)<<20;
}

inline void pinE5_Output_AFPP_10()
{
_GPIOE_(GPIOX_CRL) &= ~((4+2)<<20);
_GPIOE_(GPIOX_CRL) |= (8+1)<<20;
}

inline void pinE5_Output_AFPP_50()
{
_GPIOE_(GPIOX_CRL) &= ~((4)<<20);
_GPIOE_(GPIOX_CRL) |= (8+2+1)<<20;
}

inline void pinE5_Output_AFOD_2()
{
_GPIOE_(GPIOX_CRL) &= ~((1)<<20);
_GPIOE_(GPIOX_CRL) |= (8+2+4)<<20;
}

inline void pinE5_Output_AFOD_10()
{
_GPIOE_(GPIOX_CRL) &= ~((2)<<20);
_GPIOE_(GPIOX_CRL) |= (8+4+1)<<20;
}

inline void pinE5_Output_AFOD_50()
{
_GPIOE_(GPIOX_CRL) |= (8+4+2+1)<<20;
}

inline void pinE6_Input()
{
_GPIOE_(GPIOX_CRL) &= ~((8+2+1)<<24);
_GPIOE_(GPIOX_CRL) |= (4)<<24;
}

inline void pinE6_Input_PU()
{
_GPIOE_(GPIOX_CRL) &= ~((4+2+1)<<24);
_GPIOE_(GPIOX_CRL) |= (8)<<24;
_GPIOE_(GPIOX_ODR) |= (1)<<6;
}

inline void pinE6_Input_PD()
{
_GPIOE_(GPIOX_CRL) &= ~((4+2+1)<<24);
_GPIOE_(GPIOX_CRL) |= (8)<<24;
_GPIOE_(GPIOX_ODR) &= ~(1<<6);
}

inline void pinE6_Analog()
{
_GPIOE_(GPIOX_CRL) &= ~((8+4+2+1)<<24);
}

inline void pinE6_Output()
{
_GPIOE_(GPIOX_CRL) &= ~((8+4+1)<<24);
_GPIOE_(GPIOX_CRL) |= (2)<<24;
}

inline void pinE6_Output_OD()
{
_GPIOE_(GPIOX_CRL) &= ~((8+1)<<24);
_GPIOE_(GPIOX_CRL) |= (2+4)<<24;
}

inline void pinE6_Output_PP_2()
{
_GPIOE_(GPIOX_CRL) &= ~((8+4+1)<<24);
_GPIOE_(GPIOX_CRL) |= (2)<<24;
}

inline void pinE6_Output_PP_10()
{
_GPIOE_(GPIOX_CRL) &= ~((8+4+2)<<24);
_GPIOE_(GPIOX_CRL) |= (1)<<24;
}

inline void pinE6_Output_PP_50()
{
_GPIOE_(GPIOX_CRL) &= ~((8+4)<<24);
_GPIOE_(GPIOX_CRL) |= (2+1)<<24;
}

inline void pinE6_Output_OD_2()
{
_GPIOE_(GPIOX_CRL) &= ~((8+1)<<24);
_GPIOE_(GPIOX_CRL) |= (2+4)<<24;
}

inline void pinE6_Output_OD_10()
{
_GPIOE_(GPIOX_CRL) &= ~((8+2)<<24);
_GPIOE_(GPIOX_CRL) |= (4+1)<<24;
}

inline void pinE6_Output_OD_50()
{
_GPIOE_(GPIOX_CRL) &= ~((8)<<24);
_GPIOE_(GPIOX_CRL) |= (4+2+1)<<24;
}

inline void pinE6_Output_AFPP_2()
{
_GPIOE_(GPIOX_CRL) &= ~((4+1)<<24);
_GPIOE_(GPIOX_CRL) |= (8+2)<<24;
}

inline void pinE6_Output_AFPP_10()
{
_GPIOE_(GPIOX_CRL) &= ~((4+2)<<24);
_GPIOE_(GPIOX_CRL) |= (8+1)<<24;
}

inline void pinE6_Output_AFPP_50()
{
_GPIOE_(GPIOX_CRL) &= ~((4)<<24);
_GPIOE_(GPIOX_CRL) |= (8+2+1)<<24;
}

inline void pinE6_Output_AFOD_2()
{
_GPIOE_(GPIOX_CRL) &= ~((1)<<24);
_GPIOE_(GPIOX_CRL) |= (8+2+4)<<24;
}

inline void pinE6_Output_AFOD_10()
{
_GPIOE_(GPIOX_CRL) &= ~((2)<<24);
_GPIOE_(GPIOX_CRL) |= (8+4+1)<<24;
}

inline void pinE6_Output_AFOD_50()
{
_GPIOE_(GPIOX_CRL) |= (8+4+2+1)<<24;
}

inline void pinE7_Input()
{
_GPIOE_(GPIOX_CRL) &= ~((8+2+1)<<28);
_GPIOE_(GPIOX_CRL) |= (4)<<28;
}

inline void pinE7_Input_PU()
{
_GPIOE_(GPIOX_CRL) &= ~((4+2+1)<<28);
_GPIOE_(GPIOX_CRL) |= (8)<<28;
_GPIOE_(GPIOX_ODR) |= (1)<<7;
}

inline void pinE7_Input_PD()
{
_GPIOE_(GPIOX_CRL) &= ~((4+2+1)<<28);
_GPIOE_(GPIOX_CRL) |= (8)<<28;
_GPIOE_(GPIOX_ODR) &= ~(1<<7);
}

inline void pinE7_Analog()
{
_GPIOE_(GPIOX_CRL) &= ~((8+4+2+1)<<28);
}

inline void pinE7_Output()
{
_GPIOE_(GPIOX_CRL) &= ~((8+4+1)<<28);
_GPIOE_(GPIOX_CRL) |= (2)<<28;
}

inline void pinE7_Output_OD()
{
_GPIOE_(GPIOX_CRL) &= ~((8+1)<<28);
_GPIOE_(GPIOX_CRL) |= (2+4)<<28;
}

inline void pinE7_Output_PP_2()
{
_GPIOE_(GPIOX_CRL) &= ~((8+4+1)<<28);
_GPIOE_(GPIOX_CRL) |= (2)<<28;
}

inline void pinE7_Output_PP_10()
{
_GPIOE_(GPIOX_CRL) &= ~((8+4+2)<<28);
_GPIOE_(GPIOX_CRL) |= (1)<<28;
}

inline void pinE7_Output_PP_50()
{
_GPIOE_(GPIOX_CRL) &= ~((8+4)<<28);
_GPIOE_(GPIOX_CRL) |= (2+1)<<28;
}

inline void pinE7_Output_OD_2()
{
_GPIOE_(GPIOX_CRL) &= ~((8+1)<<28);
_GPIOE_(GPIOX_CRL) |= (2+4)<<28;
}

inline void pinE7_Output_OD_10()
{
_GPIOE_(GPIOX_CRL) &= ~((8+2)<<28);
_GPIOE_(GPIOX_CRL) |= (4+1)<<28;
}

inline void pinE7_Output_OD_50()
{
_GPIOE_(GPIOX_CRL) &= ~((8)<<28);
_GPIOE_(GPIOX_CRL) |= (4+2+1)<<28;
}

inline void pinE7_Output_AFPP_2()
{
_GPIOE_(GPIOX_CRL) &= ~((4+1)<<28);
_GPIOE_(GPIOX_CRL) |= (8+2)<<28;
}

inline void pinE7_Output_AFPP_10()
{
_GPIOE_(GPIOX_CRL) &= ~((4+2)<<28);
_GPIOE_(GPIOX_CRL) |= (8+1)<<28;
}

inline void pinE7_Output_AFPP_50()
{
_GPIOE_(GPIOX_CRL) &= ~((4)<<28);
_GPIOE_(GPIOX_CRL) |= (8+2+1)<<28;
}

inline void pinE7_Output_AFOD_2()
{
_GPIOE_(GPIOX_CRL) &= ~((1)<<28);
_GPIOE_(GPIOX_CRL) |= (8+2+4)<<28;
}

inline void pinE7_Output_AFOD_10()
{
_GPIOE_(GPIOX_CRL) &= ~((2)<<28);
_GPIOE_(GPIOX_CRL) |= (8+4+1)<<28;
}

inline void pinE7_Output_AFOD_50()
{
_GPIOE_(GPIOX_CRL) |= (8+4+2+1)<<28;
}

inline void pinE8_Input()
{
_GPIOE_(GPIOX_CRH) &= ~((8+2+1)<<0);
_GPIOE_(GPIOX_CRH) |= (4)<<0;
}

inline void pinE8_Input_PU()
{
_GPIOE_(GPIOX_CRH) &= ~((4+2+1)<<0);
_GPIOE_(GPIOX_CRH) |= (8)<<0;
_GPIOE_(GPIOX_ODR) |= (1)<<8;
}

inline void pinE8_Input_PD()
{
_GPIOE_(GPIOX_CRH) &= ~((4+2+1)<<0);
_GPIOE_(GPIOX_CRH) |= (8)<<0;
_GPIOE_(GPIOX_ODR) &= ~(1<<8);
}

inline void pinE8_Analog()
{
_GPIOE_(GPIOX_CRH) &= ~((8+4+2+1)<<0);
}

inline void pinE8_Output()
{
_GPIOE_(GPIOX_CRH) &= ~((8+4+1)<<0);
_GPIOE_(GPIOX_CRH) |= (2)<<0;
}

inline void pinE8_Output_OD()
{
_GPIOE_(GPIOX_CRH) &= ~((8+1)<<0);
_GPIOE_(GPIOX_CRH) |= (2+4)<<0;
}

inline void pinE8_Output_PP_2()
{
_GPIOE_(GPIOX_CRH) &= ~((8+4+1)<<0);
_GPIOE_(GPIOX_CRH) |= (2)<<0;
}

inline void pinE8_Output_PP_10()
{
_GPIOE_(GPIOX_CRH) &= ~((8+4+2)<<0);
_GPIOE_(GPIOX_CRH) |= (1)<<0;
}

inline void pinE8_Output_PP_50()
{
_GPIOE_(GPIOX_CRH) &= ~((8+4)<<0);
_GPIOE_(GPIOX_CRH) |= (2+1)<<0;
}

inline void pinE8_Output_OD_2()
{
_GPIOE_(GPIOX_CRH) &= ~((8+1)<<0);
_GPIOE_(GPIOX_CRH) |= (2+4)<<0;
}

inline void pinE8_Output_OD_10()
{
_GPIOE_(GPIOX_CRH) &= ~((8+2)<<0);
_GPIOE_(GPIOX_CRH) |= (4+1)<<0;
}

inline void pinE8_Output_OD_50()
{
_GPIOE_(GPIOX_CRH) &= ~((8)<<0);
_GPIOE_(GPIOX_CRH) |= (4+2+1)<<0;
}

inline void pinE8_Output_AFPP_2()
{
_GPIOE_(GPIOX_CRH) &= ~((4+1)<<0);
_GPIOE_(GPIOX_CRH) |= (8+2)<<0;
}

inline void pinE8_Output_AFPP_10()
{
_GPIOE_(GPIOX_CRH) &= ~((4+2)<<0);
_GPIOE_(GPIOX_CRH) |= (8+1)<<0;
}

inline void pinE8_Output_AFPP_50()
{
_GPIOE_(GPIOX_CRH) &= ~((4)<<0);
_GPIOE_(GPIOX_CRH) |= (8+2+1)<<0;
}

inline void pinE8_Output_AFOD_2()
{
_GPIOE_(GPIOX_CRH) &= ~((1)<<0);
_GPIOE_(GPIOX_CRH) |= (8+2+4)<<0;
}

inline void pinE8_Output_AFOD_10()
{
_GPIOE_(GPIOX_CRH) &= ~((2)<<0);
_GPIOE_(GPIOX_CRH) |= (8+4+1)<<0;
}

inline void pinE8_Output_AFOD_50()
{
_GPIOE_(GPIOX_CRH) |= (8+4+2+1)<<0;
}

inline void pinE9_Input()
{
_GPIOE_(GPIOX_CRH) &= ~((8+2+1)<<4);
_GPIOE_(GPIOX_CRH) |= (4)<<4;
}

inline void pinE9_Input_PU()
{
_GPIOE_(GPIOX_CRH) &= ~((4+2+1)<<4);
_GPIOE_(GPIOX_CRH) |= (8)<<4;
_GPIOE_(GPIOX_ODR) |= (1)<<9;
}

inline void pinE9_Input_PD()
{
_GPIOE_(GPIOX_CRH) &= ~((4+2+1)<<4);
_GPIOE_(GPIOX_CRH) |= (8)<<4;
_GPIOE_(GPIOX_ODR) &= ~(1<<9);
}

inline void pinE9_Analog()
{
_GPIOE_(GPIOX_CRH) &= ~((8+4+2+1)<<4);
}

inline void pinE9_Output()
{
_GPIOE_(GPIOX_CRH) &= ~((8+4+1)<<4);
_GPIOE_(GPIOX_CRH) |= (2)<<4;
}

inline void pinE9_Output_OD()
{
_GPIOE_(GPIOX_CRH) &= ~((8+1)<<4);
_GPIOE_(GPIOX_CRH) |= (2+4)<<4;
}

inline void pinE9_Output_PP_2()
{
_GPIOE_(GPIOX_CRH) &= ~((8+4+1)<<4);
_GPIOE_(GPIOX_CRH) |= (2)<<4;
}

inline void pinE9_Output_PP_10()
{
_GPIOE_(GPIOX_CRH) &= ~((8+4+2)<<4);
_GPIOE_(GPIOX_CRH) |= (1)<<4;
}

inline void pinE9_Output_PP_50()
{
_GPIOE_(GPIOX_CRH) &= ~((8+4)<<4);
_GPIOE_(GPIOX_CRH) |= (2+1)<<4;
}

inline void pinE9_Output_OD_2()
{
_GPIOE_(GPIOX_CRH) &= ~((8+1)<<4);
_GPIOE_(GPIOX_CRH) |= (2+4)<<4;
}

inline void pinE9_Output_OD_10()
{
_GPIOE_(GPIOX_CRH) &= ~((8+2)<<4);
_GPIOE_(GPIOX_CRH) |= (4+1)<<4;
}

inline void pinE9_Output_OD_50()
{
_GPIOE_(GPIOX_CRH) &= ~((8)<<4);
_GPIOE_(GPIOX_CRH) |= (4+2+1)<<4;
}

inline void pinE9_Output_AFPP_2()
{
_GPIOE_(GPIOX_CRH) &= ~((4+1)<<4);
_GPIOE_(GPIOX_CRH) |= (8+2)<<4;
}

inline void pinE9_Output_AFPP_10()
{
_GPIOE_(GPIOX_CRH) &= ~((4+2)<<4);
_GPIOE_(GPIOX_CRH) |= (8+1)<<4;
}

inline void pinE9_Output_AFPP_50()
{
_GPIOE_(GPIOX_CRH) &= ~((4)<<4);
_GPIOE_(GPIOX_CRH) |= (8+2+1)<<4;
}

inline void pinE9_Output_AFOD_2()
{
_GPIOE_(GPIOX_CRH) &= ~((1)<<4);
_GPIOE_(GPIOX_CRH) |= (8+2+4)<<4;
}

inline void pinE9_Output_AFOD_10()
{
_GPIOE_(GPIOX_CRH) &= ~((2)<<4);
_GPIOE_(GPIOX_CRH) |= (8+4+1)<<4;
}

inline void pinE9_Output_AFOD_50()
{
_GPIOE_(GPIOX_CRH) |= (8+4+2+1)<<4;
}

inline void pinE10_Input()
{
_GPIOE_(GPIOX_CRH) &= ~((8+2+1)<<8);
_GPIOE_(GPIOX_CRH) |= (4)<<8;
}

inline void pinE10_Input_PU()
{
_GPIOE_(GPIOX_CRH) &= ~((4+2+1)<<8);
_GPIOE_(GPIOX_CRH) |= (8)<<8;
_GPIOE_(GPIOX_ODR) |= (1)<<10;
}

inline void pinE10_Input_PD()
{
_GPIOE_(GPIOX_CRH) &= ~((4+2+1)<<8);
_GPIOE_(GPIOX_CRH) |= (8)<<8;
_GPIOE_(GPIOX_ODR) &= ~(1<<10);
}

inline void pinE10_Analog()
{
_GPIOE_(GPIOX_CRH) &= ~((8+4+2+1)<<8);
}

inline void pinE10_Output()
{
_GPIOE_(GPIOX_CRH) &= ~((8+4+1)<<8);
_GPIOE_(GPIOX_CRH) |= (2)<<8;
}

inline void pinE10_Output_OD()
{
_GPIOE_(GPIOX_CRH) &= ~((8+1)<<8);
_GPIOE_(GPIOX_CRH) |= (2+4)<<8;
}

inline void pinE10_Output_PP_2()
{
_GPIOE_(GPIOX_CRH) &= ~((8+4+1)<<8);
_GPIOE_(GPIOX_CRH) |= (2)<<8;
}

inline void pinE10_Output_PP_10()
{
_GPIOE_(GPIOX_CRH) &= ~((8+4+2)<<8);
_GPIOE_(GPIOX_CRH) |= (1)<<8;
}

inline void pinE10_Output_PP_50()
{
_GPIOE_(GPIOX_CRH) &= ~((8+4)<<8);
_GPIOE_(GPIOX_CRH) |= (2+1)<<8;
}

inline void pinE10_Output_OD_2()
{
_GPIOE_(GPIOX_CRH) &= ~((8+1)<<8);
_GPIOE_(GPIOX_CRH) |= (2+4)<<8;
}

inline void pinE10_Output_OD_10()
{
_GPIOE_(GPIOX_CRH) &= ~((8+2)<<8);
_GPIOE_(GPIOX_CRH) |= (4+1)<<8;
}

inline void pinE10_Output_OD_50()
{
_GPIOE_(GPIOX_CRH) &= ~((8)<<8);
_GPIOE_(GPIOX_CRH) |= (4+2+1)<<8;
}

inline void pinE10_Output_AFPP_2()
{
_GPIOE_(GPIOX_CRH) &= ~((4+1)<<8);
_GPIOE_(GPIOX_CRH) |= (8+2)<<8;
}

inline void pinE10_Output_AFPP_10()
{
_GPIOE_(GPIOX_CRH) &= ~((4+2)<<8);
_GPIOE_(GPIOX_CRH) |= (8+1)<<8;
}

inline void pinE10_Output_AFPP_50()
{
_GPIOE_(GPIOX_CRH) &= ~((4)<<8);
_GPIOE_(GPIOX_CRH) |= (8+2+1)<<8;
}

inline void pinE10_Output_AFOD_2()
{
_GPIOE_(GPIOX_CRH) &= ~((1)<<8);
_GPIOE_(GPIOX_CRH) |= (8+2+4)<<8;
}

inline void pinE10_Output_AFOD_10()
{
_GPIOE_(GPIOX_CRH) &= ~((2)<<8);
_GPIOE_(GPIOX_CRH) |= (8+4+1)<<8;
}

inline void pinE10_Output_AFOD_50()
{
_GPIOE_(GPIOX_CRH) |= (8+4+2+1)<<8;
}

inline void pinE11_Input()
{
_GPIOE_(GPIOX_CRH) &= ~((8+2+1)<<12);
_GPIOE_(GPIOX_CRH) |= (4)<<12;
}

inline void pinE11_Input_PU()
{
_GPIOE_(GPIOX_CRH) &= ~((4+2+1)<<12);
_GPIOE_(GPIOX_CRH) |= (8)<<12;
_GPIOE_(GPIOX_ODR) |= (1)<<11;
}

inline void pinE11_Input_PD()
{
_GPIOE_(GPIOX_CRH) &= ~((4+2+1)<<12);
_GPIOE_(GPIOX_CRH) |= (8)<<12;
_GPIOE_(GPIOX_ODR) &= ~(1<<11);
}

inline void pinE11_Analog()
{
_GPIOE_(GPIOX_CRH) &= ~((8+4+2+1)<<12);
}

inline void pinE11_Output()
{
_GPIOE_(GPIOX_CRH) &= ~((8+4+1)<<12);
_GPIOE_(GPIOX_CRH) |= (2)<<12;
}

inline void pinE11_Output_OD()
{
_GPIOE_(GPIOX_CRH) &= ~((8+1)<<12);
_GPIOE_(GPIOX_CRH) |= (2+4)<<12;
}

inline void pinE11_Output_PP_2()
{
_GPIOE_(GPIOX_CRH) &= ~((8+4+1)<<12);
_GPIOE_(GPIOX_CRH) |= (2)<<12;
}

inline void pinE11_Output_PP_10()
{
_GPIOE_(GPIOX_CRH) &= ~((8+4+2)<<12);
_GPIOE_(GPIOX_CRH) |= (1)<<12;
}

inline void pinE11_Output_PP_50()
{
_GPIOE_(GPIOX_CRH) &= ~((8+4)<<12);
_GPIOE_(GPIOX_CRH) |= (2+1)<<12;
}

inline void pinE11_Output_OD_2()
{
_GPIOE_(GPIOX_CRH) &= ~((8+1)<<12);
_GPIOE_(GPIOX_CRH) |= (2+4)<<12;
}

inline void pinE11_Output_OD_10()
{
_GPIOE_(GPIOX_CRH) &= ~((8+2)<<12);
_GPIOE_(GPIOX_CRH) |= (4+1)<<12;
}

inline void pinE11_Output_OD_50()
{
_GPIOE_(GPIOX_CRH) &= ~((8)<<12);
_GPIOE_(GPIOX_CRH) |= (4+2+1)<<12;
}

inline void pinE11_Output_AFPP_2()
{
_GPIOE_(GPIOX_CRH) &= ~((4+1)<<12);
_GPIOE_(GPIOX_CRH) |= (8+2)<<12;
}

inline void pinE11_Output_AFPP_10()
{
_GPIOE_(GPIOX_CRH) &= ~((4+2)<<12);
_GPIOE_(GPIOX_CRH) |= (8+1)<<12;
}

inline void pinE11_Output_AFPP_50()
{
_GPIOE_(GPIOX_CRH) &= ~((4)<<12);
_GPIOE_(GPIOX_CRH) |= (8+2+1)<<12;
}

inline void pinE11_Output_AFOD_2()
{
_GPIOE_(GPIOX_CRH) &= ~((1)<<12);
_GPIOE_(GPIOX_CRH) |= (8+2+4)<<12;
}

inline void pinE11_Output_AFOD_10()
{
_GPIOE_(GPIOX_CRH) &= ~((2)<<12);
_GPIOE_(GPIOX_CRH) |= (8+4+1)<<12;
}

inline void pinE11_Output_AFOD_50()
{
_GPIOE_(GPIOX_CRH) |= (8+4+2+1)<<12;
}

inline void pinE12_Input()
{
_GPIOE_(GPIOX_CRH) &= ~((8+2+1)<<16);
_GPIOE_(GPIOX_CRH) |= (4)<<16;
}

inline void pinE12_Input_PU()
{
_GPIOE_(GPIOX_CRH) &= ~((4+2+1)<<16);
_GPIOE_(GPIOX_CRH) |= (8)<<16;
_GPIOE_(GPIOX_ODR) |= (1)<<12;
}

inline void pinE12_Input_PD()
{
_GPIOE_(GPIOX_CRH) &= ~((4+2+1)<<16);
_GPIOE_(GPIOX_CRH) |= (8)<<16;
_GPIOE_(GPIOX_ODR) &= ~(1<<12);
}

inline void pinE12_Analog()
{
_GPIOE_(GPIOX_CRH) &= ~((8+4+2+1)<<16);
}

inline void pinE12_Output()
{
_GPIOE_(GPIOX_CRH) &= ~((8+4+1)<<16);
_GPIOE_(GPIOX_CRH) |= (2)<<16;
}

inline void pinE12_Output_OD()
{
_GPIOE_(GPIOX_CRH) &= ~((8+1)<<16);
_GPIOE_(GPIOX_CRH) |= (2+4)<<16;
}

inline void pinE12_Output_PP_2()
{
_GPIOE_(GPIOX_CRH) &= ~((8+4+1)<<16);
_GPIOE_(GPIOX_CRH) |= (2)<<16;
}

inline void pinE12_Output_PP_10()
{
_GPIOE_(GPIOX_CRH) &= ~((8+4+2)<<16);
_GPIOE_(GPIOX_CRH) |= (1)<<16;
}

inline void pinE12_Output_PP_50()
{
_GPIOE_(GPIOX_CRH) &= ~((8+4)<<16);
_GPIOE_(GPIOX_CRH) |= (2+1)<<16;
}

inline void pinE12_Output_OD_2()
{
_GPIOE_(GPIOX_CRH) &= ~((8+1)<<16);
_GPIOE_(GPIOX_CRH) |= (2+4)<<16;
}

inline void pinE12_Output_OD_10()
{
_GPIOE_(GPIOX_CRH) &= ~((8+2)<<16);
_GPIOE_(GPIOX_CRH) |= (4+1)<<16;
}

inline void pinE12_Output_OD_50()
{
_GPIOE_(GPIOX_CRH) &= ~((8)<<16);
_GPIOE_(GPIOX_CRH) |= (4+2+1)<<16;
}

inline void pinE12_Output_AFPP_2()
{
_GPIOE_(GPIOX_CRH) &= ~((4+1)<<16);
_GPIOE_(GPIOX_CRH) |= (8+2)<<16;
}

inline void pinE12_Output_AFPP_10()
{
_GPIOE_(GPIOX_CRH) &= ~((4+2)<<16);
_GPIOE_(GPIOX_CRH) |= (8+1)<<16;
}

inline void pinE12_Output_AFPP_50()
{
_GPIOE_(GPIOX_CRH) &= ~((4)<<16);
_GPIOE_(GPIOX_CRH) |= (8+2+1)<<16;
}

inline void pinE12_Output_AFOD_2()
{
_GPIOE_(GPIOX_CRH) &= ~((1)<<16);
_GPIOE_(GPIOX_CRH) |= (8+2+4)<<16;
}

inline void pinE12_Output_AFOD_10()
{
_GPIOE_(GPIOX_CRH) &= ~((2)<<16);
_GPIOE_(GPIOX_CRH) |= (8+4+1)<<16;
}

inline void pinE12_Output_AFOD_50()
{
_GPIOE_(GPIOX_CRH) |= (8+4+2+1)<<16;
}

inline void pinE13_Input()
{
_GPIOE_(GPIOX_CRH) &= ~((8+2+1)<<20);
_GPIOE_(GPIOX_CRH) |= (4)<<20;
}

inline void pinE13_Input_PU()
{
_GPIOE_(GPIOX_CRH) &= ~((4+2+1)<<20);
_GPIOE_(GPIOX_CRH) |= (8)<<20;
_GPIOE_(GPIOX_ODR) |= (1)<<13;
}

inline void pinE13_Input_PD()
{
_GPIOE_(GPIOX_CRH) &= ~((4+2+1)<<20);
_GPIOE_(GPIOX_CRH) |= (8)<<20;
_GPIOE_(GPIOX_ODR) &= ~(1<<13);
}

inline void pinE13_Analog()
{
_GPIOE_(GPIOX_CRH) &= ~((8+4+2+1)<<20);
}

inline void pinE13_Output()
{
_GPIOE_(GPIOX_CRH) &= ~((8+4+1)<<20);
_GPIOE_(GPIOX_CRH) |= (2)<<20;
}

inline void pinE13_Output_OD()
{
_GPIOE_(GPIOX_CRH) &= ~((8+1)<<20);
_GPIOE_(GPIOX_CRH) |= (2+4)<<20;
}

inline void pinE13_Output_PP_2()
{
_GPIOE_(GPIOX_CRH) &= ~((8+4+1)<<20);
_GPIOE_(GPIOX_CRH) |= (2)<<20;
}

inline void pinE13_Output_PP_10()
{
_GPIOE_(GPIOX_CRH) &= ~((8+4+2)<<20);
_GPIOE_(GPIOX_CRH) |= (1)<<20;
}

inline void pinE13_Output_PP_50()
{
_GPIOE_(GPIOX_CRH) &= ~((8+4)<<20);
_GPIOE_(GPIOX_CRH) |= (2+1)<<20;
}

inline void pinE13_Output_OD_2()
{
_GPIOE_(GPIOX_CRH) &= ~((8+1)<<20);
_GPIOE_(GPIOX_CRH) |= (2+4)<<20;
}

inline void pinE13_Output_OD_10()
{
_GPIOE_(GPIOX_CRH) &= ~((8+2)<<20);
_GPIOE_(GPIOX_CRH) |= (4+1)<<20;
}

inline void pinE13_Output_OD_50()
{
_GPIOE_(GPIOX_CRH) &= ~((8)<<20);
_GPIOE_(GPIOX_CRH) |= (4+2+1)<<20;
}

inline void pinE13_Output_AFPP_2()
{
_GPIOE_(GPIOX_CRH) &= ~((4+1)<<20);
_GPIOE_(GPIOX_CRH) |= (8+2)<<20;
}

inline void pinE13_Output_AFPP_10()
{
_GPIOE_(GPIOX_CRH) &= ~((4+2)<<20);
_GPIOE_(GPIOX_CRH) |= (8+1)<<20;
}

inline void pinE13_Output_AFPP_50()
{
_GPIOE_(GPIOX_CRH) &= ~((4)<<20);
_GPIOE_(GPIOX_CRH) |= (8+2+1)<<20;
}

inline void pinE13_Output_AFOD_2()
{
_GPIOE_(GPIOX_CRH) &= ~((1)<<20);
_GPIOE_(GPIOX_CRH) |= (8+2+4)<<20;
}

inline void pinE13_Output_AFOD_10()
{
_GPIOE_(GPIOX_CRH) &= ~((2)<<20);
_GPIOE_(GPIOX_CRH) |= (8+4+1)<<20;
}

inline void pinE13_Output_AFOD_50()
{
_GPIOE_(GPIOX_CRH) |= (8+4+2+1)<<20;
}

inline void pinE14_Input()
{
_GPIOE_(GPIOX_CRH) &= ~((8+2+1)<<24);
_GPIOE_(GPIOX_CRH) |= (4)<<24;
}

inline void pinE14_Input_PU()
{
_GPIOE_(GPIOX_CRH) &= ~((4+2+1)<<24);
_GPIOE_(GPIOX_CRH) |= (8)<<24;
_GPIOE_(GPIOX_ODR) |= (1)<<14;
}

inline void pinE14_Input_PD()
{
_GPIOE_(GPIOX_CRH) &= ~((4+2+1)<<24);
_GPIOE_(GPIOX_CRH) |= (8)<<24;
_GPIOE_(GPIOX_ODR) &= ~(1<<14);
}

inline void pinE14_Analog()
{
_GPIOE_(GPIOX_CRH) &= ~((8+4+2+1)<<24);
}

inline void pinE14_Output()
{
_GPIOE_(GPIOX_CRH) &= ~((8+4+1)<<24);
_GPIOE_(GPIOX_CRH) |= (2)<<24;
}

inline void pinE14_Output_OD()
{
_GPIOE_(GPIOX_CRH) &= ~((8+1)<<24);
_GPIOE_(GPIOX_CRH) |= (2+4)<<24;
}

inline void pinE14_Output_PP_2()
{
_GPIOE_(GPIOX_CRH) &= ~((8+4+1)<<24);
_GPIOE_(GPIOX_CRH) |= (2)<<24;
}

inline void pinE14_Output_PP_10()
{
_GPIOE_(GPIOX_CRH) &= ~((8+4+2)<<24);
_GPIOE_(GPIOX_CRH) |= (1)<<24;
}

inline void pinE14_Output_PP_50()
{
_GPIOE_(GPIOX_CRH) &= ~((8+4)<<24);
_GPIOE_(GPIOX_CRH) |= (2+1)<<24;
}

inline void pinE14_Output_OD_2()
{
_GPIOE_(GPIOX_CRH) &= ~((8+1)<<24);
_GPIOE_(GPIOX_CRH) |= (2+4)<<24;
}

inline void pinE14_Output_OD_10()
{
_GPIOE_(GPIOX_CRH) &= ~((8+2)<<24);
_GPIOE_(GPIOX_CRH) |= (4+1)<<24;
}

inline void pinE14_Output_OD_50()
{
_GPIOE_(GPIOX_CRH) &= ~((8)<<24);
_GPIOE_(GPIOX_CRH) |= (4+2+1)<<24;
}

inline void pinE14_Output_AFPP_2()
{
_GPIOE_(GPIOX_CRH) &= ~((4+1)<<24);
_GPIOE_(GPIOX_CRH) |= (8+2)<<24;
}

inline void pinE14_Output_AFPP_10()
{
_GPIOE_(GPIOX_CRH) &= ~((4+2)<<24);
_GPIOE_(GPIOX_CRH) |= (8+1)<<24;
}

inline void pinE14_Output_AFPP_50()
{
_GPIOE_(GPIOX_CRH) &= ~((4)<<24);
_GPIOE_(GPIOX_CRH) |= (8+2+1)<<24;
}

inline void pinE14_Output_AFOD_2()
{
_GPIOE_(GPIOX_CRH) &= ~((1)<<24);
_GPIOE_(GPIOX_CRH) |= (8+2+4)<<24;
}

inline void pinE14_Output_AFOD_10()
{
_GPIOE_(GPIOX_CRH) &= ~((2)<<24);
_GPIOE_(GPIOX_CRH) |= (8+4+1)<<24;
}

inline void pinE14_Output_AFOD_50()
{
_GPIOE_(GPIOX_CRH) |= (8+4+2+1)<<24;
}

inline void pinE15_Input()
{
_GPIOE_(GPIOX_CRH) &= ~((8+2+1)<<28);
_GPIOE_(GPIOX_CRH) |= (4)<<28;
}

inline void pinE15_Input_PU()
{
_GPIOE_(GPIOX_CRH) &= ~((4+2+1)<<28);
_GPIOE_(GPIOX_CRH) |= (8)<<28;
_GPIOE_(GPIOX_ODR) |= (1)<<15;
}

inline void pinE15_Input_PD()
{
_GPIOE_(GPIOX_CRH) &= ~((4+2+1)<<28);
_GPIOE_(GPIOX_CRH) |= (8)<<28;
_GPIOE_(GPIOX_ODR) &= ~(1<<15);
}

inline void pinE15_Analog()
{
_GPIOE_(GPIOX_CRH) &= ~((8+4+2+1)<<28);
}

inline void pinE15_Output()
{
_GPIOE_(GPIOX_CRH) &= ~((8+4+1)<<28);
_GPIOE_(GPIOX_CRH) |= (2)<<28;
}

inline void pinE15_Output_OD()
{
_GPIOE_(GPIOX_CRH) &= ~((8+1)<<28);
_GPIOE_(GPIOX_CRH) |= (2+4)<<28;
}

inline void pinE15_Output_PP_2()
{
_GPIOE_(GPIOX_CRH) &= ~((8+4+1)<<28);
_GPIOE_(GPIOX_CRH) |= (2)<<28;
}

inline void pinE15_Output_PP_10()
{
_GPIOE_(GPIOX_CRH) &= ~((8+4+2)<<28);
_GPIOE_(GPIOX_CRH) |= (1)<<28;
}

inline void pinE15_Output_PP_50()
{
_GPIOE_(GPIOX_CRH) &= ~((8+4)<<28);
_GPIOE_(GPIOX_CRH) |= (2+1)<<28;
}

inline void pinE15_Output_OD_2()
{
_GPIOE_(GPIOX_CRH) &= ~((8+1)<<28);
_GPIOE_(GPIOX_CRH) |= (2+4)<<28;
}

inline void pinE15_Output_OD_10()
{
_GPIOE_(GPIOX_CRH) &= ~((8+2)<<28);
_GPIOE_(GPIOX_CRH) |= (4+1)<<28;
}

inline void pinE15_Output_OD_50()
{
_GPIOE_(GPIOX_CRH) &= ~((8)<<28);
_GPIOE_(GPIOX_CRH) |= (4+2+1)<<28;
}

inline void pinE15_Output_AFPP_2()
{
_GPIOE_(GPIOX_CRH) &= ~((4+1)<<28);
_GPIOE_(GPIOX_CRH) |= (8+2)<<28;
}

inline void pinE15_Output_AFPP_10()
{
_GPIOE_(GPIOX_CRH) &= ~((4+2)<<28);
_GPIOE_(GPIOX_CRH) |= (8+1)<<28;
}

inline void pinE15_Output_AFPP_50()
{
_GPIOE_(GPIOX_CRH) &= ~((4)<<28);
_GPIOE_(GPIOX_CRH) |= (8+2+1)<<28;
}

inline void pinE15_Output_AFOD_2()
{
_GPIOE_(GPIOX_CRH) &= ~((1)<<28);
_GPIOE_(GPIOX_CRH) |= (8+2+4)<<28;
}

inline void pinE15_Output_AFOD_10()
{
_GPIOE_(GPIOX_CRH) &= ~((2)<<28);
_GPIOE_(GPIOX_CRH) |= (8+4+1)<<28;
}

inline void pinE15_Output_AFOD_50()
{
_GPIOE_(GPIOX_CRH) |= (8+4+2+1)<<28;
}

inline uint8_t readPinE0()
{
return ((_GPIOE_(GPIOX_IDR)>>0) & 1);
}

inline void setPinE0()
{
_GPIOE_(GPIOX_BSRR) = (1<<0);
}

inline void resetPinE0()
{
_GPIOE_(GPIOX_BRR) = (1<<0);
}

inline uint8_t readPinE1()
{
return ((_GPIOE_(GPIOX_IDR)>>1) & 1);
}

inline void setPinE1()
{
_GPIOE_(GPIOX_BSRR) = (1<<1);
}

inline void resetPinE1()
{
_GPIOE_(GPIOX_BRR) = (1<<1);
}

inline uint8_t readPinE2()
{
return ((_GPIOE_(GPIOX_IDR)>>2) & 1);
}

inline void setPinE2()
{
_GPIOE_(GPIOX_BSRR) = (1<<2);
}

inline void resetPinE2()
{
_GPIOE_(GPIOX_BRR) = (1<<2);
}

inline uint8_t readPinE3()
{
return ((_GPIOE_(GPIOX_IDR)>>3) & 1);
}

inline void setPinE3()
{
_GPIOE_(GPIOX_BSRR) = (1<<3);
}

inline void resetPinE3()
{
_GPIOE_(GPIOX_BRR) = (1<<3);
}

inline uint8_t readPinE4()
{
return ((_GPIOE_(GPIOX_IDR)>>4) & 1);
}

inline void setPinE4()
{
_GPIOE_(GPIOX_BSRR) = (1<<4);
}

inline void resetPinE4()
{
_GPIOE_(GPIOX_BRR) = (1<<4);
}

inline uint8_t readPinE5()
{
return ((_GPIOE_(GPIOX_IDR)>>5) & 1);
}

inline void setPinE5()
{
_GPIOE_(GPIOX_BSRR) = (1<<5);
}

inline void resetPinE5()
{
_GPIOE_(GPIOX_BRR) = (1<<5);
}

inline uint8_t readPinE6()
{
return ((_GPIOE_(GPIOX_IDR)>>6) & 1);
}

inline void setPinE6()
{
_GPIOE_(GPIOX_BSRR) = (1<<6);
}

inline void resetPinE6()
{
_GPIOE_(GPIOX_BRR) = (1<<6);
}

inline uint8_t readPinE7()
{
return ((_GPIOE_(GPIOX_IDR)>>7) & 1);
}

inline void setPinE7()
{
_GPIOE_(GPIOX_BSRR) = (1<<7);
}

inline void resetPinE7()
{
_GPIOE_(GPIOX_BRR) = (1<<7);
}

inline uint8_t readPinE8()
{
return ((_GPIOE_(GPIOX_IDR)>>8) & 1);
}

inline void setPinE8()
{
_GPIOE_(GPIOX_BSRR) = (1<<8);
}

inline void resetPinE8()
{
_GPIOE_(GPIOX_BRR) = (1<<8);
}

inline uint8_t readPinE9()
{
return ((_GPIOE_(GPIOX_IDR)>>9) & 1);
}

inline void setPinE9()
{
_GPIOE_(GPIOX_BSRR) = (1<<9);
}

inline void resetPinE9()
{
_GPIOE_(GPIOX_BRR) = (1<<9);
}

inline uint8_t readPinE10()
{
return ((_GPIOE_(GPIOX_IDR)>>10) & 1);
}

inline void setPinE10()
{
_GPIOE_(GPIOX_BSRR) = (1<<10);
}

inline void resetPinE10()
{
_GPIOE_(GPIOX_BRR) = (1<<10);
}

inline uint8_t readPinE11()
{
return ((_GPIOE_(GPIOX_IDR)>>11) & 1);
}

inline void setPinE11()
{
_GPIOE_(GPIOX_BSRR) = (1<<11);
}

inline void resetPinE11()
{
_GPIOE_(GPIOX_BRR) = (1<<11);
}

inline uint8_t readPinE12()
{
return ((_GPIOE_(GPIOX_IDR)>>12) & 1);
}

inline void setPinE12()
{
_GPIOE_(GPIOX_BSRR) = (1<<12);
}

inline void resetPinE12()
{
_GPIOE_(GPIOX_BRR) = (1<<12);
}

inline uint8_t readPinE13()
{
return ((_GPIOE_(GPIOX_IDR)>>13) & 1);
}

inline void setPinE13()
{
_GPIOE_(GPIOX_BSRR) = (1<<13);
}

inline void resetPinE13()
{
_GPIOE_(GPIOX_BRR) = (1<<13);
}

inline uint8_t readPinE14()
{
return ((_GPIOE_(GPIOX_IDR)>>14) & 1);
}

inline void setPinE14()
{
_GPIOE_(GPIOX_BSRR) = (1<<14);
}

inline void resetPinE14()
{
_GPIOE_(GPIOX_BRR) = (1<<14);
}

inline uint8_t readPinE15()
{
return ((_GPIOE_(GPIOX_IDR)>>15) & 1);
}

inline void setPinE15()
{
_GPIOE_(GPIOX_BSRR) = (1<<15);
}

inline void resetPinE15()
{
_GPIOE_(GPIOX_BRR) = (1<<15);
}

inline void pinF0_Input()
{
_GPIOF_(GPIOX_CRL) &= ~((8+2+1)<<0);
_GPIOF_(GPIOX_CRL) |= (4)<<0;
}

inline void pinF0_Input_PU()
{
_GPIOF_(GPIOX_CRL) &= ~((4+2+1)<<0);
_GPIOF_(GPIOX_CRL) |= (8)<<0;
_GPIOF_(GPIOX_ODR) |= (1)<<0;
}

inline void pinF0_Input_PD()
{
_GPIOF_(GPIOX_CRL) &= ~((4+2+1)<<0);
_GPIOF_(GPIOX_CRL) |= (8)<<0;
_GPIOF_(GPIOX_ODR) &= ~(1<<0);
}

inline void pinF0_Analog()
{
_GPIOF_(GPIOX_CRL) &= ~((8+4+2+1)<<0);
}

inline void pinF0_Output()
{
_GPIOF_(GPIOX_CRL) &= ~((8+4+1)<<0);
_GPIOF_(GPIOX_CRL) |= (2)<<0;
}

inline void pinF0_Output_OD()
{
_GPIOF_(GPIOX_CRL) &= ~((8+1)<<0);
_GPIOF_(GPIOX_CRL) |= (2+4)<<0;
}

inline void pinF0_Output_PP_2()
{
_GPIOF_(GPIOX_CRL) &= ~((8+4+1)<<0);
_GPIOF_(GPIOX_CRL) |= (2)<<0;
}

inline void pinF0_Output_PP_10()
{
_GPIOF_(GPIOX_CRL) &= ~((8+4+2)<<0);
_GPIOF_(GPIOX_CRL) |= (1)<<0;
}

inline void pinF0_Output_PP_50()
{
_GPIOF_(GPIOX_CRL) &= ~((8+4)<<0);
_GPIOF_(GPIOX_CRL) |= (2+1)<<0;
}

inline void pinF0_Output_OD_2()
{
_GPIOF_(GPIOX_CRL) &= ~((8+1)<<0);
_GPIOF_(GPIOX_CRL) |= (2+4)<<0;
}

inline void pinF0_Output_OD_10()
{
_GPIOF_(GPIOX_CRL) &= ~((8+2)<<0);
_GPIOF_(GPIOX_CRL) |= (4+1)<<0;
}

inline void pinF0_Output_OD_50()
{
_GPIOF_(GPIOX_CRL) &= ~((8)<<0);
_GPIOF_(GPIOX_CRL) |= (4+2+1)<<0;
}

inline void pinF0_Output_AFPP_2()
{
_GPIOF_(GPIOX_CRL) &= ~((4+1)<<0);
_GPIOF_(GPIOX_CRL) |= (8+2)<<0;
}

inline void pinF0_Output_AFPP_10()
{
_GPIOF_(GPIOX_CRL) &= ~((4+2)<<0);
_GPIOF_(GPIOX_CRL) |= (8+1)<<0;
}

inline void pinF0_Output_AFPP_50()
{
_GPIOF_(GPIOX_CRL) &= ~((4)<<0);
_GPIOF_(GPIOX_CRL) |= (8+2+1)<<0;
}

inline void pinF0_Output_AFOD_2()
{
_GPIOF_(GPIOX_CRL) &= ~((1)<<0);
_GPIOF_(GPIOX_CRL) |= (8+2+4)<<0;
}

inline void pinF0_Output_AFOD_10()
{
_GPIOF_(GPIOX_CRL) &= ~((2)<<0);
_GPIOF_(GPIOX_CRL) |= (8+4+1)<<0;
}

inline void pinF0_Output_AFOD_50()
{
_GPIOF_(GPIOX_CRL) |= (8+4+2+1)<<0;
}

inline void pinF1_Input()
{
_GPIOF_(GPIOX_CRL) &= ~((8+2+1)<<4);
_GPIOF_(GPIOX_CRL) |= (4)<<4;
}

inline void pinF1_Input_PU()
{
_GPIOF_(GPIOX_CRL) &= ~((4+2+1)<<4);
_GPIOF_(GPIOX_CRL) |= (8)<<4;
_GPIOF_(GPIOX_ODR) |= (1)<<1;
}

inline void pinF1_Input_PD()
{
_GPIOF_(GPIOX_CRL) &= ~((4+2+1)<<4);
_GPIOF_(GPIOX_CRL) |= (8)<<4;
_GPIOF_(GPIOX_ODR) &= ~(1<<1);
}

inline void pinF1_Analog()
{
_GPIOF_(GPIOX_CRL) &= ~((8+4+2+1)<<4);
}

inline void pinF1_Output()
{
_GPIOF_(GPIOX_CRL) &= ~((8+4+1)<<4);
_GPIOF_(GPIOX_CRL) |= (2)<<4;
}

inline void pinF1_Output_OD()
{
_GPIOF_(GPIOX_CRL) &= ~((8+1)<<4);
_GPIOF_(GPIOX_CRL) |= (2+4)<<4;
}

inline void pinF1_Output_PP_2()
{
_GPIOF_(GPIOX_CRL) &= ~((8+4+1)<<4);
_GPIOF_(GPIOX_CRL) |= (2)<<4;
}

inline void pinF1_Output_PP_10()
{
_GPIOF_(GPIOX_CRL) &= ~((8+4+2)<<4);
_GPIOF_(GPIOX_CRL) |= (1)<<4;
}

inline void pinF1_Output_PP_50()
{
_GPIOF_(GPIOX_CRL) &= ~((8+4)<<4);
_GPIOF_(GPIOX_CRL) |= (2+1)<<4;
}

inline void pinF1_Output_OD_2()
{
_GPIOF_(GPIOX_CRL) &= ~((8+1)<<4);
_GPIOF_(GPIOX_CRL) |= (2+4)<<4;
}

inline void pinF1_Output_OD_10()
{
_GPIOF_(GPIOX_CRL) &= ~((8+2)<<4);
_GPIOF_(GPIOX_CRL) |= (4+1)<<4;
}

inline void pinF1_Output_OD_50()
{
_GPIOF_(GPIOX_CRL) &= ~((8)<<4);
_GPIOF_(GPIOX_CRL) |= (4+2+1)<<4;
}

inline void pinF1_Output_AFPP_2()
{
_GPIOF_(GPIOX_CRL) &= ~((4+1)<<4);
_GPIOF_(GPIOX_CRL) |= (8+2)<<4;
}

inline void pinF1_Output_AFPP_10()
{
_GPIOF_(GPIOX_CRL) &= ~((4+2)<<4);
_GPIOF_(GPIOX_CRL) |= (8+1)<<4;
}

inline void pinF1_Output_AFPP_50()
{
_GPIOF_(GPIOX_CRL) &= ~((4)<<4);
_GPIOF_(GPIOX_CRL) |= (8+2+1)<<4;
}

inline void pinF1_Output_AFOD_2()
{
_GPIOF_(GPIOX_CRL) &= ~((1)<<4);
_GPIOF_(GPIOX_CRL) |= (8+2+4)<<4;
}

inline void pinF1_Output_AFOD_10()
{
_GPIOF_(GPIOX_CRL) &= ~((2)<<4);
_GPIOF_(GPIOX_CRL) |= (8+4+1)<<4;
}

inline void pinF1_Output_AFOD_50()
{
_GPIOF_(GPIOX_CRL) |= (8+4+2+1)<<4;
}

inline void pinF2_Input()
{
_GPIOF_(GPIOX_CRL) &= ~((8+2+1)<<8);
_GPIOF_(GPIOX_CRL) |= (4)<<8;
}

inline void pinF2_Input_PU()
{
_GPIOF_(GPIOX_CRL) &= ~((4+2+1)<<8);
_GPIOF_(GPIOX_CRL) |= (8)<<8;
_GPIOF_(GPIOX_ODR) |= (1)<<2;
}

inline void pinF2_Input_PD()
{
_GPIOF_(GPIOX_CRL) &= ~((4+2+1)<<8);
_GPIOF_(GPIOX_CRL) |= (8)<<8;
_GPIOF_(GPIOX_ODR) &= ~(1<<2);
}

inline void pinF2_Analog()
{
_GPIOF_(GPIOX_CRL) &= ~((8+4+2+1)<<8);
}

inline void pinF2_Output()
{
_GPIOF_(GPIOX_CRL) &= ~((8+4+1)<<8);
_GPIOF_(GPIOX_CRL) |= (2)<<8;
}

inline void pinF2_Output_OD()
{
_GPIOF_(GPIOX_CRL) &= ~((8+1)<<8);
_GPIOF_(GPIOX_CRL) |= (2+4)<<8;
}

inline void pinF2_Output_PP_2()
{
_GPIOF_(GPIOX_CRL) &= ~((8+4+1)<<8);
_GPIOF_(GPIOX_CRL) |= (2)<<8;
}

inline void pinF2_Output_PP_10()
{
_GPIOF_(GPIOX_CRL) &= ~((8+4+2)<<8);
_GPIOF_(GPIOX_CRL) |= (1)<<8;
}

inline void pinF2_Output_PP_50()
{
_GPIOF_(GPIOX_CRL) &= ~((8+4)<<8);
_GPIOF_(GPIOX_CRL) |= (2+1)<<8;
}

inline void pinF2_Output_OD_2()
{
_GPIOF_(GPIOX_CRL) &= ~((8+1)<<8);
_GPIOF_(GPIOX_CRL) |= (2+4)<<8;
}

inline void pinF2_Output_OD_10()
{
_GPIOF_(GPIOX_CRL) &= ~((8+2)<<8);
_GPIOF_(GPIOX_CRL) |= (4+1)<<8;
}

inline void pinF2_Output_OD_50()
{
_GPIOF_(GPIOX_CRL) &= ~((8)<<8);
_GPIOF_(GPIOX_CRL) |= (4+2+1)<<8;
}

inline void pinF2_Output_AFPP_2()
{
_GPIOF_(GPIOX_CRL) &= ~((4+1)<<8);
_GPIOF_(GPIOX_CRL) |= (8+2)<<8;
}

inline void pinF2_Output_AFPP_10()
{
_GPIOF_(GPIOX_CRL) &= ~((4+2)<<8);
_GPIOF_(GPIOX_CRL) |= (8+1)<<8;
}

inline void pinF2_Output_AFPP_50()
{
_GPIOF_(GPIOX_CRL) &= ~((4)<<8);
_GPIOF_(GPIOX_CRL) |= (8+2+1)<<8;
}

inline void pinF2_Output_AFOD_2()
{
_GPIOF_(GPIOX_CRL) &= ~((1)<<8);
_GPIOF_(GPIOX_CRL) |= (8+2+4)<<8;
}

inline void pinF2_Output_AFOD_10()
{
_GPIOF_(GPIOX_CRL) &= ~((2)<<8);
_GPIOF_(GPIOX_CRL) |= (8+4+1)<<8;
}

inline void pinF2_Output_AFOD_50()
{
_GPIOF_(GPIOX_CRL) |= (8+4+2+1)<<8;
}

inline void pinF3_Input()
{
_GPIOF_(GPIOX_CRL) &= ~((8+2+1)<<12);
_GPIOF_(GPIOX_CRL) |= (4)<<12;
}

inline void pinF3_Input_PU()
{
_GPIOF_(GPIOX_CRL) &= ~((4+2+1)<<12);
_GPIOF_(GPIOX_CRL) |= (8)<<12;
_GPIOF_(GPIOX_ODR) |= (1)<<3;
}

inline void pinF3_Input_PD()
{
_GPIOF_(GPIOX_CRL) &= ~((4+2+1)<<12);
_GPIOF_(GPIOX_CRL) |= (8)<<12;
_GPIOF_(GPIOX_ODR) &= ~(1<<3);
}

inline void pinF3_Analog()
{
_GPIOF_(GPIOX_CRL) &= ~((8+4+2+1)<<12);
}

inline void pinF3_Output()
{
_GPIOF_(GPIOX_CRL) &= ~((8+4+1)<<12);
_GPIOF_(GPIOX_CRL) |= (2)<<12;
}

inline void pinF3_Output_OD()
{
_GPIOF_(GPIOX_CRL) &= ~((8+1)<<12);
_GPIOF_(GPIOX_CRL) |= (2+4)<<12;
}

inline void pinF3_Output_PP_2()
{
_GPIOF_(GPIOX_CRL) &= ~((8+4+1)<<12);
_GPIOF_(GPIOX_CRL) |= (2)<<12;
}

inline void pinF3_Output_PP_10()
{
_GPIOF_(GPIOX_CRL) &= ~((8+4+2)<<12);
_GPIOF_(GPIOX_CRL) |= (1)<<12;
}

inline void pinF3_Output_PP_50()
{
_GPIOF_(GPIOX_CRL) &= ~((8+4)<<12);
_GPIOF_(GPIOX_CRL) |= (2+1)<<12;
}

inline void pinF3_Output_OD_2()
{
_GPIOF_(GPIOX_CRL) &= ~((8+1)<<12);
_GPIOF_(GPIOX_CRL) |= (2+4)<<12;
}

inline void pinF3_Output_OD_10()
{
_GPIOF_(GPIOX_CRL) &= ~((8+2)<<12);
_GPIOF_(GPIOX_CRL) |= (4+1)<<12;
}

inline void pinF3_Output_OD_50()
{
_GPIOF_(GPIOX_CRL) &= ~((8)<<12);
_GPIOF_(GPIOX_CRL) |= (4+2+1)<<12;
}

inline void pinF3_Output_AFPP_2()
{
_GPIOF_(GPIOX_CRL) &= ~((4+1)<<12);
_GPIOF_(GPIOX_CRL) |= (8+2)<<12;
}

inline void pinF3_Output_AFPP_10()
{
_GPIOF_(GPIOX_CRL) &= ~((4+2)<<12);
_GPIOF_(GPIOX_CRL) |= (8+1)<<12;
}

inline void pinF3_Output_AFPP_50()
{
_GPIOF_(GPIOX_CRL) &= ~((4)<<12);
_GPIOF_(GPIOX_CRL) |= (8+2+1)<<12;
}

inline void pinF3_Output_AFOD_2()
{
_GPIOF_(GPIOX_CRL) &= ~((1)<<12);
_GPIOF_(GPIOX_CRL) |= (8+2+4)<<12;
}

inline void pinF3_Output_AFOD_10()
{
_GPIOF_(GPIOX_CRL) &= ~((2)<<12);
_GPIOF_(GPIOX_CRL) |= (8+4+1)<<12;
}

inline void pinF3_Output_AFOD_50()
{
_GPIOF_(GPIOX_CRL) |= (8+4+2+1)<<12;
}

inline void pinF4_Input()
{
_GPIOF_(GPIOX_CRL) &= ~((8+2+1)<<16);
_GPIOF_(GPIOX_CRL) |= (4)<<16;
}

inline void pinF4_Input_PU()
{
_GPIOF_(GPIOX_CRL) &= ~((4+2+1)<<16);
_GPIOF_(GPIOX_CRL) |= (8)<<16;
_GPIOF_(GPIOX_ODR) |= (1)<<4;
}

inline void pinF4_Input_PD()
{
_GPIOF_(GPIOX_CRL) &= ~((4+2+1)<<16);
_GPIOF_(GPIOX_CRL) |= (8)<<16;
_GPIOF_(GPIOX_ODR) &= ~(1<<4);
}

inline void pinF4_Analog()
{
_GPIOF_(GPIOX_CRL) &= ~((8+4+2+1)<<16);
}

inline void pinF4_Output()
{
_GPIOF_(GPIOX_CRL) &= ~((8+4+1)<<16);
_GPIOF_(GPIOX_CRL) |= (2)<<16;
}

inline void pinF4_Output_OD()
{
_GPIOF_(GPIOX_CRL) &= ~((8+1)<<16);
_GPIOF_(GPIOX_CRL) |= (2+4)<<16;
}

inline void pinF4_Output_PP_2()
{
_GPIOF_(GPIOX_CRL) &= ~((8+4+1)<<16);
_GPIOF_(GPIOX_CRL) |= (2)<<16;
}

inline void pinF4_Output_PP_10()
{
_GPIOF_(GPIOX_CRL) &= ~((8+4+2)<<16);
_GPIOF_(GPIOX_CRL) |= (1)<<16;
}

inline void pinF4_Output_PP_50()
{
_GPIOF_(GPIOX_CRL) &= ~((8+4)<<16);
_GPIOF_(GPIOX_CRL) |= (2+1)<<16;
}

inline void pinF4_Output_OD_2()
{
_GPIOF_(GPIOX_CRL) &= ~((8+1)<<16);
_GPIOF_(GPIOX_CRL) |= (2+4)<<16;
}

inline void pinF4_Output_OD_10()
{
_GPIOF_(GPIOX_CRL) &= ~((8+2)<<16);
_GPIOF_(GPIOX_CRL) |= (4+1)<<16;
}

inline void pinF4_Output_OD_50()
{
_GPIOF_(GPIOX_CRL) &= ~((8)<<16);
_GPIOF_(GPIOX_CRL) |= (4+2+1)<<16;
}

inline void pinF4_Output_AFPP_2()
{
_GPIOF_(GPIOX_CRL) &= ~((4+1)<<16);
_GPIOF_(GPIOX_CRL) |= (8+2)<<16;
}

inline void pinF4_Output_AFPP_10()
{
_GPIOF_(GPIOX_CRL) &= ~((4+2)<<16);
_GPIOF_(GPIOX_CRL) |= (8+1)<<16;
}

inline void pinF4_Output_AFPP_50()
{
_GPIOF_(GPIOX_CRL) &= ~((4)<<16);
_GPIOF_(GPIOX_CRL) |= (8+2+1)<<16;
}

inline void pinF4_Output_AFOD_2()
{
_GPIOF_(GPIOX_CRL) &= ~((1)<<16);
_GPIOF_(GPIOX_CRL) |= (8+2+4)<<16;
}

inline void pinF4_Output_AFOD_10()
{
_GPIOF_(GPIOX_CRL) &= ~((2)<<16);
_GPIOF_(GPIOX_CRL) |= (8+4+1)<<16;
}

inline void pinF4_Output_AFOD_50()
{
_GPIOF_(GPIOX_CRL) |= (8+4+2+1)<<16;
}

inline void pinF5_Input()
{
_GPIOF_(GPIOX_CRL) &= ~((8+2+1)<<20);
_GPIOF_(GPIOX_CRL) |= (4)<<20;
}

inline void pinF5_Input_PU()
{
_GPIOF_(GPIOX_CRL) &= ~((4+2+1)<<20);
_GPIOF_(GPIOX_CRL) |= (8)<<20;
_GPIOF_(GPIOX_ODR) |= (1)<<5;
}

inline void pinF5_Input_PD()
{
_GPIOF_(GPIOX_CRL) &= ~((4+2+1)<<20);
_GPIOF_(GPIOX_CRL) |= (8)<<20;
_GPIOF_(GPIOX_ODR) &= ~(1<<5);
}

inline void pinF5_Analog()
{
_GPIOF_(GPIOX_CRL) &= ~((8+4+2+1)<<20);
}

inline void pinF5_Output()
{
_GPIOF_(GPIOX_CRL) &= ~((8+4+1)<<20);
_GPIOF_(GPIOX_CRL) |= (2)<<20;
}

inline void pinF5_Output_OD()
{
_GPIOF_(GPIOX_CRL) &= ~((8+1)<<20);
_GPIOF_(GPIOX_CRL) |= (2+4)<<20;
}

inline void pinF5_Output_PP_2()
{
_GPIOF_(GPIOX_CRL) &= ~((8+4+1)<<20);
_GPIOF_(GPIOX_CRL) |= (2)<<20;
}

inline void pinF5_Output_PP_10()
{
_GPIOF_(GPIOX_CRL) &= ~((8+4+2)<<20);
_GPIOF_(GPIOX_CRL) |= (1)<<20;
}

inline void pinF5_Output_PP_50()
{
_GPIOF_(GPIOX_CRL) &= ~((8+4)<<20);
_GPIOF_(GPIOX_CRL) |= (2+1)<<20;
}

inline void pinF5_Output_OD_2()
{
_GPIOF_(GPIOX_CRL) &= ~((8+1)<<20);
_GPIOF_(GPIOX_CRL) |= (2+4)<<20;
}

inline void pinF5_Output_OD_10()
{
_GPIOF_(GPIOX_CRL) &= ~((8+2)<<20);
_GPIOF_(GPIOX_CRL) |= (4+1)<<20;
}

inline void pinF5_Output_OD_50()
{
_GPIOF_(GPIOX_CRL) &= ~((8)<<20);
_GPIOF_(GPIOX_CRL) |= (4+2+1)<<20;
}

inline void pinF5_Output_AFPP_2()
{
_GPIOF_(GPIOX_CRL) &= ~((4+1)<<20);
_GPIOF_(GPIOX_CRL) |= (8+2)<<20;
}

inline void pinF5_Output_AFPP_10()
{
_GPIOF_(GPIOX_CRL) &= ~((4+2)<<20);
_GPIOF_(GPIOX_CRL) |= (8+1)<<20;
}

inline void pinF5_Output_AFPP_50()
{
_GPIOF_(GPIOX_CRL) &= ~((4)<<20);
_GPIOF_(GPIOX_CRL) |= (8+2+1)<<20;
}

inline void pinF5_Output_AFOD_2()
{
_GPIOF_(GPIOX_CRL) &= ~((1)<<20);
_GPIOF_(GPIOX_CRL) |= (8+2+4)<<20;
}

inline void pinF5_Output_AFOD_10()
{
_GPIOF_(GPIOX_CRL) &= ~((2)<<20);
_GPIOF_(GPIOX_CRL) |= (8+4+1)<<20;
}

inline void pinF5_Output_AFOD_50()
{
_GPIOF_(GPIOX_CRL) |= (8+4+2+1)<<20;
}

inline void pinF6_Input()
{
_GPIOF_(GPIOX_CRL) &= ~((8+2+1)<<24);
_GPIOF_(GPIOX_CRL) |= (4)<<24;
}

inline void pinF6_Input_PU()
{
_GPIOF_(GPIOX_CRL) &= ~((4+2+1)<<24);
_GPIOF_(GPIOX_CRL) |= (8)<<24;
_GPIOF_(GPIOX_ODR) |= (1)<<6;
}

inline void pinF6_Input_PD()
{
_GPIOF_(GPIOX_CRL) &= ~((4+2+1)<<24);
_GPIOF_(GPIOX_CRL) |= (8)<<24;
_GPIOF_(GPIOX_ODR) &= ~(1<<6);
}

inline void pinF6_Analog()
{
_GPIOF_(GPIOX_CRL) &= ~((8+4+2+1)<<24);
}

inline void pinF6_Output()
{
_GPIOF_(GPIOX_CRL) &= ~((8+4+1)<<24);
_GPIOF_(GPIOX_CRL) |= (2)<<24;
}

inline void pinF6_Output_OD()
{
_GPIOF_(GPIOX_CRL) &= ~((8+1)<<24);
_GPIOF_(GPIOX_CRL) |= (2+4)<<24;
}

inline void pinF6_Output_PP_2()
{
_GPIOF_(GPIOX_CRL) &= ~((8+4+1)<<24);
_GPIOF_(GPIOX_CRL) |= (2)<<24;
}

inline void pinF6_Output_PP_10()
{
_GPIOF_(GPIOX_CRL) &= ~((8+4+2)<<24);
_GPIOF_(GPIOX_CRL) |= (1)<<24;
}

inline void pinF6_Output_PP_50()
{
_GPIOF_(GPIOX_CRL) &= ~((8+4)<<24);
_GPIOF_(GPIOX_CRL) |= (2+1)<<24;
}

inline void pinF6_Output_OD_2()
{
_GPIOF_(GPIOX_CRL) &= ~((8+1)<<24);
_GPIOF_(GPIOX_CRL) |= (2+4)<<24;
}

inline void pinF6_Output_OD_10()
{
_GPIOF_(GPIOX_CRL) &= ~((8+2)<<24);
_GPIOF_(GPIOX_CRL) |= (4+1)<<24;
}

inline void pinF6_Output_OD_50()
{
_GPIOF_(GPIOX_CRL) &= ~((8)<<24);
_GPIOF_(GPIOX_CRL) |= (4+2+1)<<24;
}

inline void pinF6_Output_AFPP_2()
{
_GPIOF_(GPIOX_CRL) &= ~((4+1)<<24);
_GPIOF_(GPIOX_CRL) |= (8+2)<<24;
}

inline void pinF6_Output_AFPP_10()
{
_GPIOF_(GPIOX_CRL) &= ~((4+2)<<24);
_GPIOF_(GPIOX_CRL) |= (8+1)<<24;
}

inline void pinF6_Output_AFPP_50()
{
_GPIOF_(GPIOX_CRL) &= ~((4)<<24);
_GPIOF_(GPIOX_CRL) |= (8+2+1)<<24;
}

inline void pinF6_Output_AFOD_2()
{
_GPIOF_(GPIOX_CRL) &= ~((1)<<24);
_GPIOF_(GPIOX_CRL) |= (8+2+4)<<24;
}

inline void pinF6_Output_AFOD_10()
{
_GPIOF_(GPIOX_CRL) &= ~((2)<<24);
_GPIOF_(GPIOX_CRL) |= (8+4+1)<<24;
}

inline void pinF6_Output_AFOD_50()
{
_GPIOF_(GPIOX_CRL) |= (8+4+2+1)<<24;
}

inline void pinF7_Input()
{
_GPIOF_(GPIOX_CRL) &= ~((8+2+1)<<28);
_GPIOF_(GPIOX_CRL) |= (4)<<28;
}

inline void pinF7_Input_PU()
{
_GPIOF_(GPIOX_CRL) &= ~((4+2+1)<<28);
_GPIOF_(GPIOX_CRL) |= (8)<<28;
_GPIOF_(GPIOX_ODR) |= (1)<<7;
}

inline void pinF7_Input_PD()
{
_GPIOF_(GPIOX_CRL) &= ~((4+2+1)<<28);
_GPIOF_(GPIOX_CRL) |= (8)<<28;
_GPIOF_(GPIOX_ODR) &= ~(1<<7);
}

inline void pinF7_Analog()
{
_GPIOF_(GPIOX_CRL) &= ~((8+4+2+1)<<28);
}

inline void pinF7_Output()
{
_GPIOF_(GPIOX_CRL) &= ~((8+4+1)<<28);
_GPIOF_(GPIOX_CRL) |= (2)<<28;
}

inline void pinF7_Output_OD()
{
_GPIOF_(GPIOX_CRL) &= ~((8+1)<<28);
_GPIOF_(GPIOX_CRL) |= (2+4)<<28;
}

inline void pinF7_Output_PP_2()
{
_GPIOF_(GPIOX_CRL) &= ~((8+4+1)<<28);
_GPIOF_(GPIOX_CRL) |= (2)<<28;
}

inline void pinF7_Output_PP_10()
{
_GPIOF_(GPIOX_CRL) &= ~((8+4+2)<<28);
_GPIOF_(GPIOX_CRL) |= (1)<<28;
}

inline void pinF7_Output_PP_50()
{
_GPIOF_(GPIOX_CRL) &= ~((8+4)<<28);
_GPIOF_(GPIOX_CRL) |= (2+1)<<28;
}

inline void pinF7_Output_OD_2()
{
_GPIOF_(GPIOX_CRL) &= ~((8+1)<<28);
_GPIOF_(GPIOX_CRL) |= (2+4)<<28;
}

inline void pinF7_Output_OD_10()
{
_GPIOF_(GPIOX_CRL) &= ~((8+2)<<28);
_GPIOF_(GPIOX_CRL) |= (4+1)<<28;
}

inline void pinF7_Output_OD_50()
{
_GPIOF_(GPIOX_CRL) &= ~((8)<<28);
_GPIOF_(GPIOX_CRL) |= (4+2+1)<<28;
}

inline void pinF7_Output_AFPP_2()
{
_GPIOF_(GPIOX_CRL) &= ~((4+1)<<28);
_GPIOF_(GPIOX_CRL) |= (8+2)<<28;
}

inline void pinF7_Output_AFPP_10()
{
_GPIOF_(GPIOX_CRL) &= ~((4+2)<<28);
_GPIOF_(GPIOX_CRL) |= (8+1)<<28;
}

inline void pinF7_Output_AFPP_50()
{
_GPIOF_(GPIOX_CRL) &= ~((4)<<28);
_GPIOF_(GPIOX_CRL) |= (8+2+1)<<28;
}

inline void pinF7_Output_AFOD_2()
{
_GPIOF_(GPIOX_CRL) &= ~((1)<<28);
_GPIOF_(GPIOX_CRL) |= (8+2+4)<<28;
}

inline void pinF7_Output_AFOD_10()
{
_GPIOF_(GPIOX_CRL) &= ~((2)<<28);
_GPIOF_(GPIOX_CRL) |= (8+4+1)<<28;
}

inline void pinF7_Output_AFOD_50()
{
_GPIOF_(GPIOX_CRL) |= (8+4+2+1)<<28;
}

inline void pinF8_Input()
{
_GPIOF_(GPIOX_CRH) &= ~((8+2+1)<<0);
_GPIOF_(GPIOX_CRH) |= (4)<<0;
}

inline void pinF8_Input_PU()
{
_GPIOF_(GPIOX_CRH) &= ~((4+2+1)<<0);
_GPIOF_(GPIOX_CRH) |= (8)<<0;
_GPIOF_(GPIOX_ODR) |= (1)<<8;
}

inline void pinF8_Input_PD()
{
_GPIOF_(GPIOX_CRH) &= ~((4+2+1)<<0);
_GPIOF_(GPIOX_CRH) |= (8)<<0;
_GPIOF_(GPIOX_ODR) &= ~(1<<8);
}

inline void pinF8_Analog()
{
_GPIOF_(GPIOX_CRH) &= ~((8+4+2+1)<<0);
}

inline void pinF8_Output()
{
_GPIOF_(GPIOX_CRH) &= ~((8+4+1)<<0);
_GPIOF_(GPIOX_CRH) |= (2)<<0;
}

inline void pinF8_Output_OD()
{
_GPIOF_(GPIOX_CRH) &= ~((8+1)<<0);
_GPIOF_(GPIOX_CRH) |= (2+4)<<0;
}

inline void pinF8_Output_PP_2()
{
_GPIOF_(GPIOX_CRH) &= ~((8+4+1)<<0);
_GPIOF_(GPIOX_CRH) |= (2)<<0;
}

inline void pinF8_Output_PP_10()
{
_GPIOF_(GPIOX_CRH) &= ~((8+4+2)<<0);
_GPIOF_(GPIOX_CRH) |= (1)<<0;
}

inline void pinF8_Output_PP_50()
{
_GPIOF_(GPIOX_CRH) &= ~((8+4)<<0);
_GPIOF_(GPIOX_CRH) |= (2+1)<<0;
}

inline void pinF8_Output_OD_2()
{
_GPIOF_(GPIOX_CRH) &= ~((8+1)<<0);
_GPIOF_(GPIOX_CRH) |= (2+4)<<0;
}

inline void pinF8_Output_OD_10()
{
_GPIOF_(GPIOX_CRH) &= ~((8+2)<<0);
_GPIOF_(GPIOX_CRH) |= (4+1)<<0;
}

inline void pinF8_Output_OD_50()
{
_GPIOF_(GPIOX_CRH) &= ~((8)<<0);
_GPIOF_(GPIOX_CRH) |= (4+2+1)<<0;
}

inline void pinF8_Output_AFPP_2()
{
_GPIOF_(GPIOX_CRH) &= ~((4+1)<<0);
_GPIOF_(GPIOX_CRH) |= (8+2)<<0;
}

inline void pinF8_Output_AFPP_10()
{
_GPIOF_(GPIOX_CRH) &= ~((4+2)<<0);
_GPIOF_(GPIOX_CRH) |= (8+1)<<0;
}

inline void pinF8_Output_AFPP_50()
{
_GPIOF_(GPIOX_CRH) &= ~((4)<<0);
_GPIOF_(GPIOX_CRH) |= (8+2+1)<<0;
}

inline void pinF8_Output_AFOD_2()
{
_GPIOF_(GPIOX_CRH) &= ~((1)<<0);
_GPIOF_(GPIOX_CRH) |= (8+2+4)<<0;
}

inline void pinF8_Output_AFOD_10()
{
_GPIOF_(GPIOX_CRH) &= ~((2)<<0);
_GPIOF_(GPIOX_CRH) |= (8+4+1)<<0;
}

inline void pinF8_Output_AFOD_50()
{
_GPIOF_(GPIOX_CRH) |= (8+4+2+1)<<0;
}

inline void pinF9_Input()
{
_GPIOF_(GPIOX_CRH) &= ~((8+2+1)<<4);
_GPIOF_(GPIOX_CRH) |= (4)<<4;
}

inline void pinF9_Input_PU()
{
_GPIOF_(GPIOX_CRH) &= ~((4+2+1)<<4);
_GPIOF_(GPIOX_CRH) |= (8)<<4;
_GPIOF_(GPIOX_ODR) |= (1)<<9;
}

inline void pinF9_Input_PD()
{
_GPIOF_(GPIOX_CRH) &= ~((4+2+1)<<4);
_GPIOF_(GPIOX_CRH) |= (8)<<4;
_GPIOF_(GPIOX_ODR) &= ~(1<<9);
}

inline void pinF9_Analog()
{
_GPIOF_(GPIOX_CRH) &= ~((8+4+2+1)<<4);
}

inline void pinF9_Output()
{
_GPIOF_(GPIOX_CRH) &= ~((8+4+1)<<4);
_GPIOF_(GPIOX_CRH) |= (2)<<4;
}

inline void pinF9_Output_OD()
{
_GPIOF_(GPIOX_CRH) &= ~((8+1)<<4);
_GPIOF_(GPIOX_CRH) |= (2+4)<<4;
}

inline void pinF9_Output_PP_2()
{
_GPIOF_(GPIOX_CRH) &= ~((8+4+1)<<4);
_GPIOF_(GPIOX_CRH) |= (2)<<4;
}

inline void pinF9_Output_PP_10()
{
_GPIOF_(GPIOX_CRH) &= ~((8+4+2)<<4);
_GPIOF_(GPIOX_CRH) |= (1)<<4;
}

inline void pinF9_Output_PP_50()
{
_GPIOF_(GPIOX_CRH) &= ~((8+4)<<4);
_GPIOF_(GPIOX_CRH) |= (2+1)<<4;
}

inline void pinF9_Output_OD_2()
{
_GPIOF_(GPIOX_CRH) &= ~((8+1)<<4);
_GPIOF_(GPIOX_CRH) |= (2+4)<<4;
}

inline void pinF9_Output_OD_10()
{
_GPIOF_(GPIOX_CRH) &= ~((8+2)<<4);
_GPIOF_(GPIOX_CRH) |= (4+1)<<4;
}

inline void pinF9_Output_OD_50()
{
_GPIOF_(GPIOX_CRH) &= ~((8)<<4);
_GPIOF_(GPIOX_CRH) |= (4+2+1)<<4;
}

inline void pinF9_Output_AFPP_2()
{
_GPIOF_(GPIOX_CRH) &= ~((4+1)<<4);
_GPIOF_(GPIOX_CRH) |= (8+2)<<4;
}

inline void pinF9_Output_AFPP_10()
{
_GPIOF_(GPIOX_CRH) &= ~((4+2)<<4);
_GPIOF_(GPIOX_CRH) |= (8+1)<<4;
}

inline void pinF9_Output_AFPP_50()
{
_GPIOF_(GPIOX_CRH) &= ~((4)<<4);
_GPIOF_(GPIOX_CRH) |= (8+2+1)<<4;
}

inline void pinF9_Output_AFOD_2()
{
_GPIOF_(GPIOX_CRH) &= ~((1)<<4);
_GPIOF_(GPIOX_CRH) |= (8+2+4)<<4;
}

inline void pinF9_Output_AFOD_10()
{
_GPIOF_(GPIOX_CRH) &= ~((2)<<4);
_GPIOF_(GPIOX_CRH) |= (8+4+1)<<4;
}

inline void pinF9_Output_AFOD_50()
{
_GPIOF_(GPIOX_CRH) |= (8+4+2+1)<<4;
}

inline void pinF10_Input()
{
_GPIOF_(GPIOX_CRH) &= ~((8+2+1)<<8);
_GPIOF_(GPIOX_CRH) |= (4)<<8;
}

inline void pinF10_Input_PU()
{
_GPIOF_(GPIOX_CRH) &= ~((4+2+1)<<8);
_GPIOF_(GPIOX_CRH) |= (8)<<8;
_GPIOF_(GPIOX_ODR) |= (1)<<10;
}

inline void pinF10_Input_PD()
{
_GPIOF_(GPIOX_CRH) &= ~((4+2+1)<<8);
_GPIOF_(GPIOX_CRH) |= (8)<<8;
_GPIOF_(GPIOX_ODR) &= ~(1<<10);
}

inline void pinF10_Analog()
{
_GPIOF_(GPIOX_CRH) &= ~((8+4+2+1)<<8);
}

inline void pinF10_Output()
{
_GPIOF_(GPIOX_CRH) &= ~((8+4+1)<<8);
_GPIOF_(GPIOX_CRH) |= (2)<<8;
}

inline void pinF10_Output_OD()
{
_GPIOF_(GPIOX_CRH) &= ~((8+1)<<8);
_GPIOF_(GPIOX_CRH) |= (2+4)<<8;
}

inline void pinF10_Output_PP_2()
{
_GPIOF_(GPIOX_CRH) &= ~((8+4+1)<<8);
_GPIOF_(GPIOX_CRH) |= (2)<<8;
}

inline void pinF10_Output_PP_10()
{
_GPIOF_(GPIOX_CRH) &= ~((8+4+2)<<8);
_GPIOF_(GPIOX_CRH) |= (1)<<8;
}

inline void pinF10_Output_PP_50()
{
_GPIOF_(GPIOX_CRH) &= ~((8+4)<<8);
_GPIOF_(GPIOX_CRH) |= (2+1)<<8;
}

inline void pinF10_Output_OD_2()
{
_GPIOF_(GPIOX_CRH) &= ~((8+1)<<8);
_GPIOF_(GPIOX_CRH) |= (2+4)<<8;
}

inline void pinF10_Output_OD_10()
{
_GPIOF_(GPIOX_CRH) &= ~((8+2)<<8);
_GPIOF_(GPIOX_CRH) |= (4+1)<<8;
}

inline void pinF10_Output_OD_50()
{
_GPIOF_(GPIOX_CRH) &= ~((8)<<8);
_GPIOF_(GPIOX_CRH) |= (4+2+1)<<8;
}

inline void pinF10_Output_AFPP_2()
{
_GPIOF_(GPIOX_CRH) &= ~((4+1)<<8);
_GPIOF_(GPIOX_CRH) |= (8+2)<<8;
}

inline void pinF10_Output_AFPP_10()
{
_GPIOF_(GPIOX_CRH) &= ~((4+2)<<8);
_GPIOF_(GPIOX_CRH) |= (8+1)<<8;
}

inline void pinF10_Output_AFPP_50()
{
_GPIOF_(GPIOX_CRH) &= ~((4)<<8);
_GPIOF_(GPIOX_CRH) |= (8+2+1)<<8;
}

inline void pinF10_Output_AFOD_2()
{
_GPIOF_(GPIOX_CRH) &= ~((1)<<8);
_GPIOF_(GPIOX_CRH) |= (8+2+4)<<8;
}

inline void pinF10_Output_AFOD_10()
{
_GPIOF_(GPIOX_CRH) &= ~((2)<<8);
_GPIOF_(GPIOX_CRH) |= (8+4+1)<<8;
}

inline void pinF10_Output_AFOD_50()
{
_GPIOF_(GPIOX_CRH) |= (8+4+2+1)<<8;
}

inline void pinF11_Input()
{
_GPIOF_(GPIOX_CRH) &= ~((8+2+1)<<12);
_GPIOF_(GPIOX_CRH) |= (4)<<12;
}

inline void pinF11_Input_PU()
{
_GPIOF_(GPIOX_CRH) &= ~((4+2+1)<<12);
_GPIOF_(GPIOX_CRH) |= (8)<<12;
_GPIOF_(GPIOX_ODR) |= (1)<<11;
}

inline void pinF11_Input_PD()
{
_GPIOF_(GPIOX_CRH) &= ~((4+2+1)<<12);
_GPIOF_(GPIOX_CRH) |= (8)<<12;
_GPIOF_(GPIOX_ODR) &= ~(1<<11);
}

inline void pinF11_Analog()
{
_GPIOF_(GPIOX_CRH) &= ~((8+4+2+1)<<12);
}

inline void pinF11_Output()
{
_GPIOF_(GPIOX_CRH) &= ~((8+4+1)<<12);
_GPIOF_(GPIOX_CRH) |= (2)<<12;
}

inline void pinF11_Output_OD()
{
_GPIOF_(GPIOX_CRH) &= ~((8+1)<<12);
_GPIOF_(GPIOX_CRH) |= (2+4)<<12;
}

inline void pinF11_Output_PP_2()
{
_GPIOF_(GPIOX_CRH) &= ~((8+4+1)<<12);
_GPIOF_(GPIOX_CRH) |= (2)<<12;
}

inline void pinF11_Output_PP_10()
{
_GPIOF_(GPIOX_CRH) &= ~((8+4+2)<<12);
_GPIOF_(GPIOX_CRH) |= (1)<<12;
}

inline void pinF11_Output_PP_50()
{
_GPIOF_(GPIOX_CRH) &= ~((8+4)<<12);
_GPIOF_(GPIOX_CRH) |= (2+1)<<12;
}

inline void pinF11_Output_OD_2()
{
_GPIOF_(GPIOX_CRH) &= ~((8+1)<<12);
_GPIOF_(GPIOX_CRH) |= (2+4)<<12;
}

inline void pinF11_Output_OD_10()
{
_GPIOF_(GPIOX_CRH) &= ~((8+2)<<12);
_GPIOF_(GPIOX_CRH) |= (4+1)<<12;
}

inline void pinF11_Output_OD_50()
{
_GPIOF_(GPIOX_CRH) &= ~((8)<<12);
_GPIOF_(GPIOX_CRH) |= (4+2+1)<<12;
}

inline void pinF11_Output_AFPP_2()
{
_GPIOF_(GPIOX_CRH) &= ~((4+1)<<12);
_GPIOF_(GPIOX_CRH) |= (8+2)<<12;
}

inline void pinF11_Output_AFPP_10()
{
_GPIOF_(GPIOX_CRH) &= ~((4+2)<<12);
_GPIOF_(GPIOX_CRH) |= (8+1)<<12;
}

inline void pinF11_Output_AFPP_50()
{
_GPIOF_(GPIOX_CRH) &= ~((4)<<12);
_GPIOF_(GPIOX_CRH) |= (8+2+1)<<12;
}

inline void pinF11_Output_AFOD_2()
{
_GPIOF_(GPIOX_CRH) &= ~((1)<<12);
_GPIOF_(GPIOX_CRH) |= (8+2+4)<<12;
}

inline void pinF11_Output_AFOD_10()
{
_GPIOF_(GPIOX_CRH) &= ~((2)<<12);
_GPIOF_(GPIOX_CRH) |= (8+4+1)<<12;
}

inline void pinF11_Output_AFOD_50()
{
_GPIOF_(GPIOX_CRH) |= (8+4+2+1)<<12;
}

inline void pinF12_Input()
{
_GPIOF_(GPIOX_CRH) &= ~((8+2+1)<<16);
_GPIOF_(GPIOX_CRH) |= (4)<<16;
}

inline void pinF12_Input_PU()
{
_GPIOF_(GPIOX_CRH) &= ~((4+2+1)<<16);
_GPIOF_(GPIOX_CRH) |= (8)<<16;
_GPIOF_(GPIOX_ODR) |= (1)<<12;
}

inline void pinF12_Input_PD()
{
_GPIOF_(GPIOX_CRH) &= ~((4+2+1)<<16);
_GPIOF_(GPIOX_CRH) |= (8)<<16;
_GPIOF_(GPIOX_ODR) &= ~(1<<12);
}

inline void pinF12_Analog()
{
_GPIOF_(GPIOX_CRH) &= ~((8+4+2+1)<<16);
}

inline void pinF12_Output()
{
_GPIOF_(GPIOX_CRH) &= ~((8+4+1)<<16);
_GPIOF_(GPIOX_CRH) |= (2)<<16;
}

inline void pinF12_Output_OD()
{
_GPIOF_(GPIOX_CRH) &= ~((8+1)<<16);
_GPIOF_(GPIOX_CRH) |= (2+4)<<16;
}

inline void pinF12_Output_PP_2()
{
_GPIOF_(GPIOX_CRH) &= ~((8+4+1)<<16);
_GPIOF_(GPIOX_CRH) |= (2)<<16;
}

inline void pinF12_Output_PP_10()
{
_GPIOF_(GPIOX_CRH) &= ~((8+4+2)<<16);
_GPIOF_(GPIOX_CRH) |= (1)<<16;
}

inline void pinF12_Output_PP_50()
{
_GPIOF_(GPIOX_CRH) &= ~((8+4)<<16);
_GPIOF_(GPIOX_CRH) |= (2+1)<<16;
}

inline void pinF12_Output_OD_2()
{
_GPIOF_(GPIOX_CRH) &= ~((8+1)<<16);
_GPIOF_(GPIOX_CRH) |= (2+4)<<16;
}

inline void pinF12_Output_OD_10()
{
_GPIOF_(GPIOX_CRH) &= ~((8+2)<<16);
_GPIOF_(GPIOX_CRH) |= (4+1)<<16;
}

inline void pinF12_Output_OD_50()
{
_GPIOF_(GPIOX_CRH) &= ~((8)<<16);
_GPIOF_(GPIOX_CRH) |= (4+2+1)<<16;
}

inline void pinF12_Output_AFPP_2()
{
_GPIOF_(GPIOX_CRH) &= ~((4+1)<<16);
_GPIOF_(GPIOX_CRH) |= (8+2)<<16;
}

inline void pinF12_Output_AFPP_10()
{
_GPIOF_(GPIOX_CRH) &= ~((4+2)<<16);
_GPIOF_(GPIOX_CRH) |= (8+1)<<16;
}

inline void pinF12_Output_AFPP_50()
{
_GPIOF_(GPIOX_CRH) &= ~((4)<<16);
_GPIOF_(GPIOX_CRH) |= (8+2+1)<<16;
}

inline void pinF12_Output_AFOD_2()
{
_GPIOF_(GPIOX_CRH) &= ~((1)<<16);
_GPIOF_(GPIOX_CRH) |= (8+2+4)<<16;
}

inline void pinF12_Output_AFOD_10()
{
_GPIOF_(GPIOX_CRH) &= ~((2)<<16);
_GPIOF_(GPIOX_CRH) |= (8+4+1)<<16;
}

inline void pinF12_Output_AFOD_50()
{
_GPIOF_(GPIOX_CRH) |= (8+4+2+1)<<16;
}

inline void pinF13_Input()
{
_GPIOF_(GPIOX_CRH) &= ~((8+2+1)<<20);
_GPIOF_(GPIOX_CRH) |= (4)<<20;
}

inline void pinF13_Input_PU()
{
_GPIOF_(GPIOX_CRH) &= ~((4+2+1)<<20);
_GPIOF_(GPIOX_CRH) |= (8)<<20;
_GPIOF_(GPIOX_ODR) |= (1)<<13;
}

inline void pinF13_Input_PD()
{
_GPIOF_(GPIOX_CRH) &= ~((4+2+1)<<20);
_GPIOF_(GPIOX_CRH) |= (8)<<20;
_GPIOF_(GPIOX_ODR) &= ~(1<<13);
}

inline void pinF13_Analog()
{
_GPIOF_(GPIOX_CRH) &= ~((8+4+2+1)<<20);
}

inline void pinF13_Output()
{
_GPIOF_(GPIOX_CRH) &= ~((8+4+1)<<20);
_GPIOF_(GPIOX_CRH) |= (2)<<20;
}

inline void pinF13_Output_OD()
{
_GPIOF_(GPIOX_CRH) &= ~((8+1)<<20);
_GPIOF_(GPIOX_CRH) |= (2+4)<<20;
}

inline void pinF13_Output_PP_2()
{
_GPIOF_(GPIOX_CRH) &= ~((8+4+1)<<20);
_GPIOF_(GPIOX_CRH) |= (2)<<20;
}

inline void pinF13_Output_PP_10()
{
_GPIOF_(GPIOX_CRH) &= ~((8+4+2)<<20);
_GPIOF_(GPIOX_CRH) |= (1)<<20;
}

inline void pinF13_Output_PP_50()
{
_GPIOF_(GPIOX_CRH) &= ~((8+4)<<20);
_GPIOF_(GPIOX_CRH) |= (2+1)<<20;
}

inline void pinF13_Output_OD_2()
{
_GPIOF_(GPIOX_CRH) &= ~((8+1)<<20);
_GPIOF_(GPIOX_CRH) |= (2+4)<<20;
}

inline void pinF13_Output_OD_10()
{
_GPIOF_(GPIOX_CRH) &= ~((8+2)<<20);
_GPIOF_(GPIOX_CRH) |= (4+1)<<20;
}

inline void pinF13_Output_OD_50()
{
_GPIOF_(GPIOX_CRH) &= ~((8)<<20);
_GPIOF_(GPIOX_CRH) |= (4+2+1)<<20;
}

inline void pinF13_Output_AFPP_2()
{
_GPIOF_(GPIOX_CRH) &= ~((4+1)<<20);
_GPIOF_(GPIOX_CRH) |= (8+2)<<20;
}

inline void pinF13_Output_AFPP_10()
{
_GPIOF_(GPIOX_CRH) &= ~((4+2)<<20);
_GPIOF_(GPIOX_CRH) |= (8+1)<<20;
}

inline void pinF13_Output_AFPP_50()
{
_GPIOF_(GPIOX_CRH) &= ~((4)<<20);
_GPIOF_(GPIOX_CRH) |= (8+2+1)<<20;
}

inline void pinF13_Output_AFOD_2()
{
_GPIOF_(GPIOX_CRH) &= ~((1)<<20);
_GPIOF_(GPIOX_CRH) |= (8+2+4)<<20;
}

inline void pinF13_Output_AFOD_10()
{
_GPIOF_(GPIOX_CRH) &= ~((2)<<20);
_GPIOF_(GPIOX_CRH) |= (8+4+1)<<20;
}

inline void pinF13_Output_AFOD_50()
{
_GPIOF_(GPIOX_CRH) |= (8+4+2+1)<<20;
}

inline void pinF14_Input()
{
_GPIOF_(GPIOX_CRH) &= ~((8+2+1)<<24);
_GPIOF_(GPIOX_CRH) |= (4)<<24;
}

inline void pinF14_Input_PU()
{
_GPIOF_(GPIOX_CRH) &= ~((4+2+1)<<24);
_GPIOF_(GPIOX_CRH) |= (8)<<24;
_GPIOF_(GPIOX_ODR) |= (1)<<14;
}

inline void pinF14_Input_PD()
{
_GPIOF_(GPIOX_CRH) &= ~((4+2+1)<<24);
_GPIOF_(GPIOX_CRH) |= (8)<<24;
_GPIOF_(GPIOX_ODR) &= ~(1<<14);
}

inline void pinF14_Analog()
{
_GPIOF_(GPIOX_CRH) &= ~((8+4+2+1)<<24);
}

inline void pinF14_Output()
{
_GPIOF_(GPIOX_CRH) &= ~((8+4+1)<<24);
_GPIOF_(GPIOX_CRH) |= (2)<<24;
}

inline void pinF14_Output_OD()
{
_GPIOF_(GPIOX_CRH) &= ~((8+1)<<24);
_GPIOF_(GPIOX_CRH) |= (2+4)<<24;
}

inline void pinF14_Output_PP_2()
{
_GPIOF_(GPIOX_CRH) &= ~((8+4+1)<<24);
_GPIOF_(GPIOX_CRH) |= (2)<<24;
}

inline void pinF14_Output_PP_10()
{
_GPIOF_(GPIOX_CRH) &= ~((8+4+2)<<24);
_GPIOF_(GPIOX_CRH) |= (1)<<24;
}

inline void pinF14_Output_PP_50()
{
_GPIOF_(GPIOX_CRH) &= ~((8+4)<<24);
_GPIOF_(GPIOX_CRH) |= (2+1)<<24;
}

inline void pinF14_Output_OD_2()
{
_GPIOF_(GPIOX_CRH) &= ~((8+1)<<24);
_GPIOF_(GPIOX_CRH) |= (2+4)<<24;
}

inline void pinF14_Output_OD_10()
{
_GPIOF_(GPIOX_CRH) &= ~((8+2)<<24);
_GPIOF_(GPIOX_CRH) |= (4+1)<<24;
}

inline void pinF14_Output_OD_50()
{
_GPIOF_(GPIOX_CRH) &= ~((8)<<24);
_GPIOF_(GPIOX_CRH) |= (4+2+1)<<24;
}

inline void pinF14_Output_AFPP_2()
{
_GPIOF_(GPIOX_CRH) &= ~((4+1)<<24);
_GPIOF_(GPIOX_CRH) |= (8+2)<<24;
}

inline void pinF14_Output_AFPP_10()
{
_GPIOF_(GPIOX_CRH) &= ~((4+2)<<24);
_GPIOF_(GPIOX_CRH) |= (8+1)<<24;
}

inline void pinF14_Output_AFPP_50()
{
_GPIOF_(GPIOX_CRH) &= ~((4)<<24);
_GPIOF_(GPIOX_CRH) |= (8+2+1)<<24;
}

inline void pinF14_Output_AFOD_2()
{
_GPIOF_(GPIOX_CRH) &= ~((1)<<24);
_GPIOF_(GPIOX_CRH) |= (8+2+4)<<24;
}

inline void pinF14_Output_AFOD_10()
{
_GPIOF_(GPIOX_CRH) &= ~((2)<<24);
_GPIOF_(GPIOX_CRH) |= (8+4+1)<<24;
}

inline void pinF14_Output_AFOD_50()
{
_GPIOF_(GPIOX_CRH) |= (8+4+2+1)<<24;
}

inline void pinF15_Input()
{
_GPIOF_(GPIOX_CRH) &= ~((8+2+1)<<28);
_GPIOF_(GPIOX_CRH) |= (4)<<28;
}

inline void pinF15_Input_PU()
{
_GPIOF_(GPIOX_CRH) &= ~((4+2+1)<<28);
_GPIOF_(GPIOX_CRH) |= (8)<<28;
_GPIOF_(GPIOX_ODR) |= (1)<<15;
}

inline void pinF15_Input_PD()
{
_GPIOF_(GPIOX_CRH) &= ~((4+2+1)<<28);
_GPIOF_(GPIOX_CRH) |= (8)<<28;
_GPIOF_(GPIOX_ODR) &= ~(1<<15);
}

inline void pinF15_Analog()
{
_GPIOF_(GPIOX_CRH) &= ~((8+4+2+1)<<28);
}

inline void pinF15_Output()
{
_GPIOF_(GPIOX_CRH) &= ~((8+4+1)<<28);
_GPIOF_(GPIOX_CRH) |= (2)<<28;
}

inline void pinF15_Output_OD()
{
_GPIOF_(GPIOX_CRH) &= ~((8+1)<<28);
_GPIOF_(GPIOX_CRH) |= (2+4)<<28;
}

inline void pinF15_Output_PP_2()
{
_GPIOF_(GPIOX_CRH) &= ~((8+4+1)<<28);
_GPIOF_(GPIOX_CRH) |= (2)<<28;
}

inline void pinF15_Output_PP_10()
{
_GPIOF_(GPIOX_CRH) &= ~((8+4+2)<<28);
_GPIOF_(GPIOX_CRH) |= (1)<<28;
}

inline void pinF15_Output_PP_50()
{
_GPIOF_(GPIOX_CRH) &= ~((8+4)<<28);
_GPIOF_(GPIOX_CRH) |= (2+1)<<28;
}

inline void pinF15_Output_OD_2()
{
_GPIOF_(GPIOX_CRH) &= ~((8+1)<<28);
_GPIOF_(GPIOX_CRH) |= (2+4)<<28;
}

inline void pinF15_Output_OD_10()
{
_GPIOF_(GPIOX_CRH) &= ~((8+2)<<28);
_GPIOF_(GPIOX_CRH) |= (4+1)<<28;
}

inline void pinF15_Output_OD_50()
{
_GPIOF_(GPIOX_CRH) &= ~((8)<<28);
_GPIOF_(GPIOX_CRH) |= (4+2+1)<<28;
}

inline void pinF15_Output_AFPP_2()
{
_GPIOF_(GPIOX_CRH) &= ~((4+1)<<28);
_GPIOF_(GPIOX_CRH) |= (8+2)<<28;
}

inline void pinF15_Output_AFPP_10()
{
_GPIOF_(GPIOX_CRH) &= ~((4+2)<<28);
_GPIOF_(GPIOX_CRH) |= (8+1)<<28;
}

inline void pinF15_Output_AFPP_50()
{
_GPIOF_(GPIOX_CRH) &= ~((4)<<28);
_GPIOF_(GPIOX_CRH) |= (8+2+1)<<28;
}

inline void pinF15_Output_AFOD_2()
{
_GPIOF_(GPIOX_CRH) &= ~((1)<<28);
_GPIOF_(GPIOX_CRH) |= (8+2+4)<<28;
}

inline void pinF15_Output_AFOD_10()
{
_GPIOF_(GPIOX_CRH) &= ~((2)<<28);
_GPIOF_(GPIOX_CRH) |= (8+4+1)<<28;
}

inline void pinF15_Output_AFOD_50()
{
_GPIOF_(GPIOX_CRH) |= (8+4+2+1)<<28;
}

inline uint8_t readPinF0()
{
return ((_GPIOF_(GPIOX_IDR)>>0) & 1);
}

inline void setPinF0()
{
_GPIOF_(GPIOX_BSRR) = (1<<0);
}

inline void resetPinF0()
{
_GPIOF_(GPIOX_BRR) = (1<<0);
}

inline uint8_t readPinF1()
{
return ((_GPIOF_(GPIOX_IDR)>>1) & 1);
}

inline void setPinF1()
{
_GPIOF_(GPIOX_BSRR) = (1<<1);
}

inline void resetPinF1()
{
_GPIOF_(GPIOX_BRR) = (1<<1);
}

inline uint8_t readPinF2()
{
return ((_GPIOF_(GPIOX_IDR)>>2) & 1);
}

inline void setPinF2()
{
_GPIOF_(GPIOX_BSRR) = (1<<2);
}

inline void resetPinF2()
{
_GPIOF_(GPIOX_BRR) = (1<<2);
}

inline uint8_t readPinF3()
{
return ((_GPIOF_(GPIOX_IDR)>>3) & 1);
}

inline void setPinF3()
{
_GPIOF_(GPIOX_BSRR) = (1<<3);
}

inline void resetPinF3()
{
_GPIOF_(GPIOX_BRR) = (1<<3);
}

inline uint8_t readPinF4()
{
return ((_GPIOF_(GPIOX_IDR)>>4) & 1);
}

inline void setPinF4()
{
_GPIOF_(GPIOX_BSRR) = (1<<4);
}

inline void resetPinF4()
{
_GPIOF_(GPIOX_BRR) = (1<<4);
}

inline uint8_t readPinF5()
{
return ((_GPIOF_(GPIOX_IDR)>>5) & 1);
}

inline void setPinF5()
{
_GPIOF_(GPIOX_BSRR) = (1<<5);
}

inline void resetPinF5()
{
_GPIOF_(GPIOX_BRR) = (1<<5);
}

inline uint8_t readPinF6()
{
return ((_GPIOF_(GPIOX_IDR)>>6) & 1);
}

inline void setPinF6()
{
_GPIOF_(GPIOX_BSRR) = (1<<6);
}

inline void resetPinF6()
{
_GPIOF_(GPIOX_BRR) = (1<<6);
}

inline uint8_t readPinF7()
{
return ((_GPIOF_(GPIOX_IDR)>>7) & 1);
}

inline void setPinF7()
{
_GPIOF_(GPIOX_BSRR) = (1<<7);
}

inline void resetPinF7()
{
_GPIOF_(GPIOX_BRR) = (1<<7);
}

inline uint8_t readPinF8()
{
return ((_GPIOF_(GPIOX_IDR)>>8) & 1);
}

inline void setPinF8()
{
_GPIOF_(GPIOX_BSRR) = (1<<8);
}

inline void resetPinF8()
{
_GPIOF_(GPIOX_BRR) = (1<<8);
}

inline uint8_t readPinF9()
{
return ((_GPIOF_(GPIOX_IDR)>>9) & 1);
}

inline void setPinF9()
{
_GPIOF_(GPIOX_BSRR) = (1<<9);
}

inline void resetPinF9()
{
_GPIOF_(GPIOX_BRR) = (1<<9);
}

inline uint8_t readPinF10()
{
return ((_GPIOF_(GPIOX_IDR)>>10) & 1);
}

inline void setPinF10()
{
_GPIOF_(GPIOX_BSRR) = (1<<10);
}

inline void resetPinF10()
{
_GPIOF_(GPIOX_BRR) = (1<<10);
}

inline uint8_t readPinF11()
{
return ((_GPIOF_(GPIOX_IDR)>>11) & 1);
}

inline void setPinF11()
{
_GPIOF_(GPIOX_BSRR) = (1<<11);
}

inline void resetPinF11()
{
_GPIOF_(GPIOX_BRR) = (1<<11);
}

inline uint8_t readPinF12()
{
return ((_GPIOF_(GPIOX_IDR)>>12) & 1);
}

inline void setPinF12()
{
_GPIOF_(GPIOX_BSRR) = (1<<12);
}

inline void resetPinF12()
{
_GPIOF_(GPIOX_BRR) = (1<<12);
}

inline uint8_t readPinF13()
{
return ((_GPIOF_(GPIOX_IDR)>>13) & 1);
}

inline void setPinF13()
{
_GPIOF_(GPIOX_BSRR) = (1<<13);
}

inline void resetPinF13()
{
_GPIOF_(GPIOX_BRR) = (1<<13);
}

inline uint8_t readPinF14()
{
return ((_GPIOF_(GPIOX_IDR)>>14) & 1);
}

inline void setPinF14()
{
_GPIOF_(GPIOX_BSRR) = (1<<14);
}

inline void resetPinF14()
{
_GPIOF_(GPIOX_BRR) = (1<<14);
}

inline uint8_t readPinF15()
{
return ((_GPIOF_(GPIOX_IDR)>>15) & 1);
}

inline void setPinF15()
{
_GPIOF_(GPIOX_BSRR) = (1<<15);
}

inline void resetPinF15()
{
_GPIOF_(GPIOX_BRR) = (1<<15);
}

inline void pinG0_Input()
{
_GPIOG_(GPIOX_CRL) &= ~((8+2+1)<<0);
_GPIOG_(GPIOX_CRL) |= (4)<<0;
}

inline void pinG0_Input_PU()
{
_GPIOG_(GPIOX_CRL) &= ~((4+2+1)<<0);
_GPIOG_(GPIOX_CRL) |= (8)<<0;
_GPIOG_(GPIOX_ODR) |= (1)<<0;
}

inline void pinG0_Input_PD()
{
_GPIOG_(GPIOX_CRL) &= ~((4+2+1)<<0);
_GPIOG_(GPIOX_CRL) |= (8)<<0;
_GPIOG_(GPIOX_ODR) &= ~(1<<0);
}

inline void pinG0_Analog()
{
_GPIOG_(GPIOX_CRL) &= ~((8+4+2+1)<<0);
}

inline void pinG0_Output()
{
_GPIOG_(GPIOX_CRL) &= ~((8+4+1)<<0);
_GPIOG_(GPIOX_CRL) |= (2)<<0;
}

inline void pinG0_Output_OD()
{
_GPIOG_(GPIOX_CRL) &= ~((8+1)<<0);
_GPIOG_(GPIOX_CRL) |= (2+4)<<0;
}

inline void pinG0_Output_PP_2()
{
_GPIOG_(GPIOX_CRL) &= ~((8+4+1)<<0);
_GPIOG_(GPIOX_CRL) |= (2)<<0;
}

inline void pinG0_Output_PP_10()
{
_GPIOG_(GPIOX_CRL) &= ~((8+4+2)<<0);
_GPIOG_(GPIOX_CRL) |= (1)<<0;
}

inline void pinG0_Output_PP_50()
{
_GPIOG_(GPIOX_CRL) &= ~((8+4)<<0);
_GPIOG_(GPIOX_CRL) |= (2+1)<<0;
}

inline void pinG0_Output_OD_2()
{
_GPIOG_(GPIOX_CRL) &= ~((8+1)<<0);
_GPIOG_(GPIOX_CRL) |= (2+4)<<0;
}

inline void pinG0_Output_OD_10()
{
_GPIOG_(GPIOX_CRL) &= ~((8+2)<<0);
_GPIOG_(GPIOX_CRL) |= (4+1)<<0;
}

inline void pinG0_Output_OD_50()
{
_GPIOG_(GPIOX_CRL) &= ~((8)<<0);
_GPIOG_(GPIOX_CRL) |= (4+2+1)<<0;
}

inline void pinG0_Output_AFPP_2()
{
_GPIOG_(GPIOX_CRL) &= ~((4+1)<<0);
_GPIOG_(GPIOX_CRL) |= (8+2)<<0;
}

inline void pinG0_Output_AFPP_10()
{
_GPIOG_(GPIOX_CRL) &= ~((4+2)<<0);
_GPIOG_(GPIOX_CRL) |= (8+1)<<0;
}

inline void pinG0_Output_AFPP_50()
{
_GPIOG_(GPIOX_CRL) &= ~((4)<<0);
_GPIOG_(GPIOX_CRL) |= (8+2+1)<<0;
}

inline void pinG0_Output_AFOD_2()
{
_GPIOG_(GPIOX_CRL) &= ~((1)<<0);
_GPIOG_(GPIOX_CRL) |= (8+2+4)<<0;
}

inline void pinG0_Output_AFOD_10()
{
_GPIOG_(GPIOX_CRL) &= ~((2)<<0);
_GPIOG_(GPIOX_CRL) |= (8+4+1)<<0;
}

inline void pinG0_Output_AFOD_50()
{
_GPIOG_(GPIOX_CRL) |= (8+4+2+1)<<0;
}

inline void pinG1_Input()
{
_GPIOG_(GPIOX_CRL) &= ~((8+2+1)<<4);
_GPIOG_(GPIOX_CRL) |= (4)<<4;
}

inline void pinG1_Input_PU()
{
_GPIOG_(GPIOX_CRL) &= ~((4+2+1)<<4);
_GPIOG_(GPIOX_CRL) |= (8)<<4;
_GPIOG_(GPIOX_ODR) |= (1)<<1;
}

inline void pinG1_Input_PD()
{
_GPIOG_(GPIOX_CRL) &= ~((4+2+1)<<4);
_GPIOG_(GPIOX_CRL) |= (8)<<4;
_GPIOG_(GPIOX_ODR) &= ~(1<<1);
}

inline void pinG1_Analog()
{
_GPIOG_(GPIOX_CRL) &= ~((8+4+2+1)<<4);
}

inline void pinG1_Output()
{
_GPIOG_(GPIOX_CRL) &= ~((8+4+1)<<4);
_GPIOG_(GPIOX_CRL) |= (2)<<4;
}

inline void pinG1_Output_OD()
{
_GPIOG_(GPIOX_CRL) &= ~((8+1)<<4);
_GPIOG_(GPIOX_CRL) |= (2+4)<<4;
}

inline void pinG1_Output_PP_2()
{
_GPIOG_(GPIOX_CRL) &= ~((8+4+1)<<4);
_GPIOG_(GPIOX_CRL) |= (2)<<4;
}

inline void pinG1_Output_PP_10()
{
_GPIOG_(GPIOX_CRL) &= ~((8+4+2)<<4);
_GPIOG_(GPIOX_CRL) |= (1)<<4;
}

inline void pinG1_Output_PP_50()
{
_GPIOG_(GPIOX_CRL) &= ~((8+4)<<4);
_GPIOG_(GPIOX_CRL) |= (2+1)<<4;
}

inline void pinG1_Output_OD_2()
{
_GPIOG_(GPIOX_CRL) &= ~((8+1)<<4);
_GPIOG_(GPIOX_CRL) |= (2+4)<<4;
}

inline void pinG1_Output_OD_10()
{
_GPIOG_(GPIOX_CRL) &= ~((8+2)<<4);
_GPIOG_(GPIOX_CRL) |= (4+1)<<4;
}

inline void pinG1_Output_OD_50()
{
_GPIOG_(GPIOX_CRL) &= ~((8)<<4);
_GPIOG_(GPIOX_CRL) |= (4+2+1)<<4;
}

inline void pinG1_Output_AFPP_2()
{
_GPIOG_(GPIOX_CRL) &= ~((4+1)<<4);
_GPIOG_(GPIOX_CRL) |= (8+2)<<4;
}

inline void pinG1_Output_AFPP_10()
{
_GPIOG_(GPIOX_CRL) &= ~((4+2)<<4);
_GPIOG_(GPIOX_CRL) |= (8+1)<<4;
}

inline void pinG1_Output_AFPP_50()
{
_GPIOG_(GPIOX_CRL) &= ~((4)<<4);
_GPIOG_(GPIOX_CRL) |= (8+2+1)<<4;
}

inline void pinG1_Output_AFOD_2()
{
_GPIOG_(GPIOX_CRL) &= ~((1)<<4);
_GPIOG_(GPIOX_CRL) |= (8+2+4)<<4;
}

inline void pinG1_Output_AFOD_10()
{
_GPIOG_(GPIOX_CRL) &= ~((2)<<4);
_GPIOG_(GPIOX_CRL) |= (8+4+1)<<4;
}

inline void pinG1_Output_AFOD_50()
{
_GPIOG_(GPIOX_CRL) |= (8+4+2+1)<<4;
}

inline void pinG2_Input()
{
_GPIOG_(GPIOX_CRL) &= ~((8+2+1)<<8);
_GPIOG_(GPIOX_CRL) |= (4)<<8;
}

inline void pinG2_Input_PU()
{
_GPIOG_(GPIOX_CRL) &= ~((4+2+1)<<8);
_GPIOG_(GPIOX_CRL) |= (8)<<8;
_GPIOG_(GPIOX_ODR) |= (1)<<2;
}

inline void pinG2_Input_PD()
{
_GPIOG_(GPIOX_CRL) &= ~((4+2+1)<<8);
_GPIOG_(GPIOX_CRL) |= (8)<<8;
_GPIOG_(GPIOX_ODR) &= ~(1<<2);
}

inline void pinG2_Analog()
{
_GPIOG_(GPIOX_CRL) &= ~((8+4+2+1)<<8);
}

inline void pinG2_Output()
{
_GPIOG_(GPIOX_CRL) &= ~((8+4+1)<<8);
_GPIOG_(GPIOX_CRL) |= (2)<<8;
}

inline void pinG2_Output_OD()
{
_GPIOG_(GPIOX_CRL) &= ~((8+1)<<8);
_GPIOG_(GPIOX_CRL) |= (2+4)<<8;
}

inline void pinG2_Output_PP_2()
{
_GPIOG_(GPIOX_CRL) &= ~((8+4+1)<<8);
_GPIOG_(GPIOX_CRL) |= (2)<<8;
}

inline void pinG2_Output_PP_10()
{
_GPIOG_(GPIOX_CRL) &= ~((8+4+2)<<8);
_GPIOG_(GPIOX_CRL) |= (1)<<8;
}

inline void pinG2_Output_PP_50()
{
_GPIOG_(GPIOX_CRL) &= ~((8+4)<<8);
_GPIOG_(GPIOX_CRL) |= (2+1)<<8;
}

inline void pinG2_Output_OD_2()
{
_GPIOG_(GPIOX_CRL) &= ~((8+1)<<8);
_GPIOG_(GPIOX_CRL) |= (2+4)<<8;
}

inline void pinG2_Output_OD_10()
{
_GPIOG_(GPIOX_CRL) &= ~((8+2)<<8);
_GPIOG_(GPIOX_CRL) |= (4+1)<<8;
}

inline void pinG2_Output_OD_50()
{
_GPIOG_(GPIOX_CRL) &= ~((8)<<8);
_GPIOG_(GPIOX_CRL) |= (4+2+1)<<8;
}

inline void pinG2_Output_AFPP_2()
{
_GPIOG_(GPIOX_CRL) &= ~((4+1)<<8);
_GPIOG_(GPIOX_CRL) |= (8+2)<<8;
}

inline void pinG2_Output_AFPP_10()
{
_GPIOG_(GPIOX_CRL) &= ~((4+2)<<8);
_GPIOG_(GPIOX_CRL) |= (8+1)<<8;
}

inline void pinG2_Output_AFPP_50()
{
_GPIOG_(GPIOX_CRL) &= ~((4)<<8);
_GPIOG_(GPIOX_CRL) |= (8+2+1)<<8;
}

inline void pinG2_Output_AFOD_2()
{
_GPIOG_(GPIOX_CRL) &= ~((1)<<8);
_GPIOG_(GPIOX_CRL) |= (8+2+4)<<8;
}

inline void pinG2_Output_AFOD_10()
{
_GPIOG_(GPIOX_CRL) &= ~((2)<<8);
_GPIOG_(GPIOX_CRL) |= (8+4+1)<<8;
}

inline void pinG2_Output_AFOD_50()
{
_GPIOG_(GPIOX_CRL) |= (8+4+2+1)<<8;
}

inline void pinG3_Input()
{
_GPIOG_(GPIOX_CRL) &= ~((8+2+1)<<12);
_GPIOG_(GPIOX_CRL) |= (4)<<12;
}

inline void pinG3_Input_PU()
{
_GPIOG_(GPIOX_CRL) &= ~((4+2+1)<<12);
_GPIOG_(GPIOX_CRL) |= (8)<<12;
_GPIOG_(GPIOX_ODR) |= (1)<<3;
}

inline void pinG3_Input_PD()
{
_GPIOG_(GPIOX_CRL) &= ~((4+2+1)<<12);
_GPIOG_(GPIOX_CRL) |= (8)<<12;
_GPIOG_(GPIOX_ODR) &= ~(1<<3);
}

inline void pinG3_Analog()
{
_GPIOG_(GPIOX_CRL) &= ~((8+4+2+1)<<12);
}

inline void pinG3_Output()
{
_GPIOG_(GPIOX_CRL) &= ~((8+4+1)<<12);
_GPIOG_(GPIOX_CRL) |= (2)<<12;
}

inline void pinG3_Output_OD()
{
_GPIOG_(GPIOX_CRL) &= ~((8+1)<<12);
_GPIOG_(GPIOX_CRL) |= (2+4)<<12;
}

inline void pinG3_Output_PP_2()
{
_GPIOG_(GPIOX_CRL) &= ~((8+4+1)<<12);
_GPIOG_(GPIOX_CRL) |= (2)<<12;
}

inline void pinG3_Output_PP_10()
{
_GPIOG_(GPIOX_CRL) &= ~((8+4+2)<<12);
_GPIOG_(GPIOX_CRL) |= (1)<<12;
}

inline void pinG3_Output_PP_50()
{
_GPIOG_(GPIOX_CRL) &= ~((8+4)<<12);
_GPIOG_(GPIOX_CRL) |= (2+1)<<12;
}

inline void pinG3_Output_OD_2()
{
_GPIOG_(GPIOX_CRL) &= ~((8+1)<<12);
_GPIOG_(GPIOX_CRL) |= (2+4)<<12;
}

inline void pinG3_Output_OD_10()
{
_GPIOG_(GPIOX_CRL) &= ~((8+2)<<12);
_GPIOG_(GPIOX_CRL) |= (4+1)<<12;
}

inline void pinG3_Output_OD_50()
{
_GPIOG_(GPIOX_CRL) &= ~((8)<<12);
_GPIOG_(GPIOX_CRL) |= (4+2+1)<<12;
}

inline void pinG3_Output_AFPP_2()
{
_GPIOG_(GPIOX_CRL) &= ~((4+1)<<12);
_GPIOG_(GPIOX_CRL) |= (8+2)<<12;
}

inline void pinG3_Output_AFPP_10()
{
_GPIOG_(GPIOX_CRL) &= ~((4+2)<<12);
_GPIOG_(GPIOX_CRL) |= (8+1)<<12;
}

inline void pinG3_Output_AFPP_50()
{
_GPIOG_(GPIOX_CRL) &= ~((4)<<12);
_GPIOG_(GPIOX_CRL) |= (8+2+1)<<12;
}

inline void pinG3_Output_AFOD_2()
{
_GPIOG_(GPIOX_CRL) &= ~((1)<<12);
_GPIOG_(GPIOX_CRL) |= (8+2+4)<<12;
}

inline void pinG3_Output_AFOD_10()
{
_GPIOG_(GPIOX_CRL) &= ~((2)<<12);
_GPIOG_(GPIOX_CRL) |= (8+4+1)<<12;
}

inline void pinG3_Output_AFOD_50()
{
_GPIOG_(GPIOX_CRL) |= (8+4+2+1)<<12;
}

inline void pinG4_Input()
{
_GPIOG_(GPIOX_CRL) &= ~((8+2+1)<<16);
_GPIOG_(GPIOX_CRL) |= (4)<<16;
}

inline void pinG4_Input_PU()
{
_GPIOG_(GPIOX_CRL) &= ~((4+2+1)<<16);
_GPIOG_(GPIOX_CRL) |= (8)<<16;
_GPIOG_(GPIOX_ODR) |= (1)<<4;
}

inline void pinG4_Input_PD()
{
_GPIOG_(GPIOX_CRL) &= ~((4+2+1)<<16);
_GPIOG_(GPIOX_CRL) |= (8)<<16;
_GPIOG_(GPIOX_ODR) &= ~(1<<4);
}

inline void pinG4_Analog()
{
_GPIOG_(GPIOX_CRL) &= ~((8+4+2+1)<<16);
}

inline void pinG4_Output()
{
_GPIOG_(GPIOX_CRL) &= ~((8+4+1)<<16);
_GPIOG_(GPIOX_CRL) |= (2)<<16;
}

inline void pinG4_Output_OD()
{
_GPIOG_(GPIOX_CRL) &= ~((8+1)<<16);
_GPIOG_(GPIOX_CRL) |= (2+4)<<16;
}

inline void pinG4_Output_PP_2()
{
_GPIOG_(GPIOX_CRL) &= ~((8+4+1)<<16);
_GPIOG_(GPIOX_CRL) |= (2)<<16;
}

inline void pinG4_Output_PP_10()
{
_GPIOG_(GPIOX_CRL) &= ~((8+4+2)<<16);
_GPIOG_(GPIOX_CRL) |= (1)<<16;
}

inline void pinG4_Output_PP_50()
{
_GPIOG_(GPIOX_CRL) &= ~((8+4)<<16);
_GPIOG_(GPIOX_CRL) |= (2+1)<<16;
}

inline void pinG4_Output_OD_2()
{
_GPIOG_(GPIOX_CRL) &= ~((8+1)<<16);
_GPIOG_(GPIOX_CRL) |= (2+4)<<16;
}

inline void pinG4_Output_OD_10()
{
_GPIOG_(GPIOX_CRL) &= ~((8+2)<<16);
_GPIOG_(GPIOX_CRL) |= (4+1)<<16;
}

inline void pinG4_Output_OD_50()
{
_GPIOG_(GPIOX_CRL) &= ~((8)<<16);
_GPIOG_(GPIOX_CRL) |= (4+2+1)<<16;
}

inline void pinG4_Output_AFPP_2()
{
_GPIOG_(GPIOX_CRL) &= ~((4+1)<<16);
_GPIOG_(GPIOX_CRL) |= (8+2)<<16;
}

inline void pinG4_Output_AFPP_10()
{
_GPIOG_(GPIOX_CRL) &= ~((4+2)<<16);
_GPIOG_(GPIOX_CRL) |= (8+1)<<16;
}

inline void pinG4_Output_AFPP_50()
{
_GPIOG_(GPIOX_CRL) &= ~((4)<<16);
_GPIOG_(GPIOX_CRL) |= (8+2+1)<<16;
}

inline void pinG4_Output_AFOD_2()
{
_GPIOG_(GPIOX_CRL) &= ~((1)<<16);
_GPIOG_(GPIOX_CRL) |= (8+2+4)<<16;
}

inline void pinG4_Output_AFOD_10()
{
_GPIOG_(GPIOX_CRL) &= ~((2)<<16);
_GPIOG_(GPIOX_CRL) |= (8+4+1)<<16;
}

inline void pinG4_Output_AFOD_50()
{
_GPIOG_(GPIOX_CRL) |= (8+4+2+1)<<16;
}

inline void pinG5_Input()
{
_GPIOG_(GPIOX_CRL) &= ~((8+2+1)<<20);
_GPIOG_(GPIOX_CRL) |= (4)<<20;
}

inline void pinG5_Input_PU()
{
_GPIOG_(GPIOX_CRL) &= ~((4+2+1)<<20);
_GPIOG_(GPIOX_CRL) |= (8)<<20;
_GPIOG_(GPIOX_ODR) |= (1)<<5;
}

inline void pinG5_Input_PD()
{
_GPIOG_(GPIOX_CRL) &= ~((4+2+1)<<20);
_GPIOG_(GPIOX_CRL) |= (8)<<20;
_GPIOG_(GPIOX_ODR) &= ~(1<<5);
}

inline void pinG5_Analog()
{
_GPIOG_(GPIOX_CRL) &= ~((8+4+2+1)<<20);
}

inline void pinG5_Output()
{
_GPIOG_(GPIOX_CRL) &= ~((8+4+1)<<20);
_GPIOG_(GPIOX_CRL) |= (2)<<20;
}

inline void pinG5_Output_OD()
{
_GPIOG_(GPIOX_CRL) &= ~((8+1)<<20);
_GPIOG_(GPIOX_CRL) |= (2+4)<<20;
}

inline void pinG5_Output_PP_2()
{
_GPIOG_(GPIOX_CRL) &= ~((8+4+1)<<20);
_GPIOG_(GPIOX_CRL) |= (2)<<20;
}

inline void pinG5_Output_PP_10()
{
_GPIOG_(GPIOX_CRL) &= ~((8+4+2)<<20);
_GPIOG_(GPIOX_CRL) |= (1)<<20;
}

inline void pinG5_Output_PP_50()
{
_GPIOG_(GPIOX_CRL) &= ~((8+4)<<20);
_GPIOG_(GPIOX_CRL) |= (2+1)<<20;
}

inline void pinG5_Output_OD_2()
{
_GPIOG_(GPIOX_CRL) &= ~((8+1)<<20);
_GPIOG_(GPIOX_CRL) |= (2+4)<<20;
}

inline void pinG5_Output_OD_10()
{
_GPIOG_(GPIOX_CRL) &= ~((8+2)<<20);
_GPIOG_(GPIOX_CRL) |= (4+1)<<20;
}

inline void pinG5_Output_OD_50()
{
_GPIOG_(GPIOX_CRL) &= ~((8)<<20);
_GPIOG_(GPIOX_CRL) |= (4+2+1)<<20;
}

inline void pinG5_Output_AFPP_2()
{
_GPIOG_(GPIOX_CRL) &= ~((4+1)<<20);
_GPIOG_(GPIOX_CRL) |= (8+2)<<20;
}

inline void pinG5_Output_AFPP_10()
{
_GPIOG_(GPIOX_CRL) &= ~((4+2)<<20);
_GPIOG_(GPIOX_CRL) |= (8+1)<<20;
}

inline void pinG5_Output_AFPP_50()
{
_GPIOG_(GPIOX_CRL) &= ~((4)<<20);
_GPIOG_(GPIOX_CRL) |= (8+2+1)<<20;
}

inline void pinG5_Output_AFOD_2()
{
_GPIOG_(GPIOX_CRL) &= ~((1)<<20);
_GPIOG_(GPIOX_CRL) |= (8+2+4)<<20;
}

inline void pinG5_Output_AFOD_10()
{
_GPIOG_(GPIOX_CRL) &= ~((2)<<20);
_GPIOG_(GPIOX_CRL) |= (8+4+1)<<20;
}

inline void pinG5_Output_AFOD_50()
{
_GPIOG_(GPIOX_CRL) |= (8+4+2+1)<<20;
}

inline void pinG6_Input()
{
_GPIOG_(GPIOX_CRL) &= ~((8+2+1)<<24);
_GPIOG_(GPIOX_CRL) |= (4)<<24;
}

inline void pinG6_Input_PU()
{
_GPIOG_(GPIOX_CRL) &= ~((4+2+1)<<24);
_GPIOG_(GPIOX_CRL) |= (8)<<24;
_GPIOG_(GPIOX_ODR) |= (1)<<6;
}

inline void pinG6_Input_PD()
{
_GPIOG_(GPIOX_CRL) &= ~((4+2+1)<<24);
_GPIOG_(GPIOX_CRL) |= (8)<<24;
_GPIOG_(GPIOX_ODR) &= ~(1<<6);
}

inline void pinG6_Analog()
{
_GPIOG_(GPIOX_CRL) &= ~((8+4+2+1)<<24);
}

inline void pinG6_Output()
{
_GPIOG_(GPIOX_CRL) &= ~((8+4+1)<<24);
_GPIOG_(GPIOX_CRL) |= (2)<<24;
}

inline void pinG6_Output_OD()
{
_GPIOG_(GPIOX_CRL) &= ~((8+1)<<24);
_GPIOG_(GPIOX_CRL) |= (2+4)<<24;
}

inline void pinG6_Output_PP_2()
{
_GPIOG_(GPIOX_CRL) &= ~((8+4+1)<<24);
_GPIOG_(GPIOX_CRL) |= (2)<<24;
}

inline void pinG6_Output_PP_10()
{
_GPIOG_(GPIOX_CRL) &= ~((8+4+2)<<24);
_GPIOG_(GPIOX_CRL) |= (1)<<24;
}

inline void pinG6_Output_PP_50()
{
_GPIOG_(GPIOX_CRL) &= ~((8+4)<<24);
_GPIOG_(GPIOX_CRL) |= (2+1)<<24;
}

inline void pinG6_Output_OD_2()
{
_GPIOG_(GPIOX_CRL) &= ~((8+1)<<24);
_GPIOG_(GPIOX_CRL) |= (2+4)<<24;
}

inline void pinG6_Output_OD_10()
{
_GPIOG_(GPIOX_CRL) &= ~((8+2)<<24);
_GPIOG_(GPIOX_CRL) |= (4+1)<<24;
}

inline void pinG6_Output_OD_50()
{
_GPIOG_(GPIOX_CRL) &= ~((8)<<24);
_GPIOG_(GPIOX_CRL) |= (4+2+1)<<24;
}

inline void pinG6_Output_AFPP_2()
{
_GPIOG_(GPIOX_CRL) &= ~((4+1)<<24);
_GPIOG_(GPIOX_CRL) |= (8+2)<<24;
}

inline void pinG6_Output_AFPP_10()
{
_GPIOG_(GPIOX_CRL) &= ~((4+2)<<24);
_GPIOG_(GPIOX_CRL) |= (8+1)<<24;
}

inline void pinG6_Output_AFPP_50()
{
_GPIOG_(GPIOX_CRL) &= ~((4)<<24);
_GPIOG_(GPIOX_CRL) |= (8+2+1)<<24;
}

inline void pinG6_Output_AFOD_2()
{
_GPIOG_(GPIOX_CRL) &= ~((1)<<24);
_GPIOG_(GPIOX_CRL) |= (8+2+4)<<24;
}

inline void pinG6_Output_AFOD_10()
{
_GPIOG_(GPIOX_CRL) &= ~((2)<<24);
_GPIOG_(GPIOX_CRL) |= (8+4+1)<<24;
}

inline void pinG6_Output_AFOD_50()
{
_GPIOG_(GPIOX_CRL) |= (8+4+2+1)<<24;
}

inline void pinG7_Input()
{
_GPIOG_(GPIOX_CRL) &= ~((8+2+1)<<28);
_GPIOG_(GPIOX_CRL) |= (4)<<28;
}

inline void pinG7_Input_PU()
{
_GPIOG_(GPIOX_CRL) &= ~((4+2+1)<<28);
_GPIOG_(GPIOX_CRL) |= (8)<<28;
_GPIOG_(GPIOX_ODR) |= (1)<<7;
}

inline void pinG7_Input_PD()
{
_GPIOG_(GPIOX_CRL) &= ~((4+2+1)<<28);
_GPIOG_(GPIOX_CRL) |= (8)<<28;
_GPIOG_(GPIOX_ODR) &= ~(1<<7);
}

inline void pinG7_Analog()
{
_GPIOG_(GPIOX_CRL) &= ~((8+4+2+1)<<28);
}

inline void pinG7_Output()
{
_GPIOG_(GPIOX_CRL) &= ~((8+4+1)<<28);
_GPIOG_(GPIOX_CRL) |= (2)<<28;
}

inline void pinG7_Output_OD()
{
_GPIOG_(GPIOX_CRL) &= ~((8+1)<<28);
_GPIOG_(GPIOX_CRL) |= (2+4)<<28;
}

inline void pinG7_Output_PP_2()
{
_GPIOG_(GPIOX_CRL) &= ~((8+4+1)<<28);
_GPIOG_(GPIOX_CRL) |= (2)<<28;
}

inline void pinG7_Output_PP_10()
{
_GPIOG_(GPIOX_CRL) &= ~((8+4+2)<<28);
_GPIOG_(GPIOX_CRL) |= (1)<<28;
}

inline void pinG7_Output_PP_50()
{
_GPIOG_(GPIOX_CRL) &= ~((8+4)<<28);
_GPIOG_(GPIOX_CRL) |= (2+1)<<28;
}

inline void pinG7_Output_OD_2()
{
_GPIOG_(GPIOX_CRL) &= ~((8+1)<<28);
_GPIOG_(GPIOX_CRL) |= (2+4)<<28;
}

inline void pinG7_Output_OD_10()
{
_GPIOG_(GPIOX_CRL) &= ~((8+2)<<28);
_GPIOG_(GPIOX_CRL) |= (4+1)<<28;
}

inline void pinG7_Output_OD_50()
{
_GPIOG_(GPIOX_CRL) &= ~((8)<<28);
_GPIOG_(GPIOX_CRL) |= (4+2+1)<<28;
}

inline void pinG7_Output_AFPP_2()
{
_GPIOG_(GPIOX_CRL) &= ~((4+1)<<28);
_GPIOG_(GPIOX_CRL) |= (8+2)<<28;
}

inline void pinG7_Output_AFPP_10()
{
_GPIOG_(GPIOX_CRL) &= ~((4+2)<<28);
_GPIOG_(GPIOX_CRL) |= (8+1)<<28;
}

inline void pinG7_Output_AFPP_50()
{
_GPIOG_(GPIOX_CRL) &= ~((4)<<28);
_GPIOG_(GPIOX_CRL) |= (8+2+1)<<28;
}

inline void pinG7_Output_AFOD_2()
{
_GPIOG_(GPIOX_CRL) &= ~((1)<<28);
_GPIOG_(GPIOX_CRL) |= (8+2+4)<<28;
}

inline void pinG7_Output_AFOD_10()
{
_GPIOG_(GPIOX_CRL) &= ~((2)<<28);
_GPIOG_(GPIOX_CRL) |= (8+4+1)<<28;
}

inline void pinG7_Output_AFOD_50()
{
_GPIOG_(GPIOX_CRL) |= (8+4+2+1)<<28;
}

inline void pinG8_Input()
{
_GPIOG_(GPIOX_CRH) &= ~((8+2+1)<<0);
_GPIOG_(GPIOX_CRH) |= (4)<<0;
}

inline void pinG8_Input_PU()
{
_GPIOG_(GPIOX_CRH) &= ~((4+2+1)<<0);
_GPIOG_(GPIOX_CRH) |= (8)<<0;
_GPIOG_(GPIOX_ODR) |= (1)<<8;
}

inline void pinG8_Input_PD()
{
_GPIOG_(GPIOX_CRH) &= ~((4+2+1)<<0);
_GPIOG_(GPIOX_CRH) |= (8)<<0;
_GPIOG_(GPIOX_ODR) &= ~(1<<8);
}

inline void pinG8_Analog()
{
_GPIOG_(GPIOX_CRH) &= ~((8+4+2+1)<<0);
}

inline void pinG8_Output()
{
_GPIOG_(GPIOX_CRH) &= ~((8+4+1)<<0);
_GPIOG_(GPIOX_CRH) |= (2)<<0;
}

inline void pinG8_Output_OD()
{
_GPIOG_(GPIOX_CRH) &= ~((8+1)<<0);
_GPIOG_(GPIOX_CRH) |= (2+4)<<0;
}

inline void pinG8_Output_PP_2()
{
_GPIOG_(GPIOX_CRH) &= ~((8+4+1)<<0);
_GPIOG_(GPIOX_CRH) |= (2)<<0;
}

inline void pinG8_Output_PP_10()
{
_GPIOG_(GPIOX_CRH) &= ~((8+4+2)<<0);
_GPIOG_(GPIOX_CRH) |= (1)<<0;
}

inline void pinG8_Output_PP_50()
{
_GPIOG_(GPIOX_CRH) &= ~((8+4)<<0);
_GPIOG_(GPIOX_CRH) |= (2+1)<<0;
}

inline void pinG8_Output_OD_2()
{
_GPIOG_(GPIOX_CRH) &= ~((8+1)<<0);
_GPIOG_(GPIOX_CRH) |= (2+4)<<0;
}

inline void pinG8_Output_OD_10()
{
_GPIOG_(GPIOX_CRH) &= ~((8+2)<<0);
_GPIOG_(GPIOX_CRH) |= (4+1)<<0;
}

inline void pinG8_Output_OD_50()
{
_GPIOG_(GPIOX_CRH) &= ~((8)<<0);
_GPIOG_(GPIOX_CRH) |= (4+2+1)<<0;
}

inline void pinG8_Output_AFPP_2()
{
_GPIOG_(GPIOX_CRH) &= ~((4+1)<<0);
_GPIOG_(GPIOX_CRH) |= (8+2)<<0;
}

inline void pinG8_Output_AFPP_10()
{
_GPIOG_(GPIOX_CRH) &= ~((4+2)<<0);
_GPIOG_(GPIOX_CRH) |= (8+1)<<0;
}

inline void pinG8_Output_AFPP_50()
{
_GPIOG_(GPIOX_CRH) &= ~((4)<<0);
_GPIOG_(GPIOX_CRH) |= (8+2+1)<<0;
}

inline void pinG8_Output_AFOD_2()
{
_GPIOG_(GPIOX_CRH) &= ~((1)<<0);
_GPIOG_(GPIOX_CRH) |= (8+2+4)<<0;
}

inline void pinG8_Output_AFOD_10()
{
_GPIOG_(GPIOX_CRH) &= ~((2)<<0);
_GPIOG_(GPIOX_CRH) |= (8+4+1)<<0;
}

inline void pinG8_Output_AFOD_50()
{
_GPIOG_(GPIOX_CRH) |= (8+4+2+1)<<0;
}

inline void pinG9_Input()
{
_GPIOG_(GPIOX_CRH) &= ~((8+2+1)<<4);
_GPIOG_(GPIOX_CRH) |= (4)<<4;
}

inline void pinG9_Input_PU()
{
_GPIOG_(GPIOX_CRH) &= ~((4+2+1)<<4);
_GPIOG_(GPIOX_CRH) |= (8)<<4;
_GPIOG_(GPIOX_ODR) |= (1)<<9;
}

inline void pinG9_Input_PD()
{
_GPIOG_(GPIOX_CRH) &= ~((4+2+1)<<4);
_GPIOG_(GPIOX_CRH) |= (8)<<4;
_GPIOG_(GPIOX_ODR) &= ~(1<<9);
}

inline void pinG9_Analog()
{
_GPIOG_(GPIOX_CRH) &= ~((8+4+2+1)<<4);
}

inline void pinG9_Output()
{
_GPIOG_(GPIOX_CRH) &= ~((8+4+1)<<4);
_GPIOG_(GPIOX_CRH) |= (2)<<4;
}

inline void pinG9_Output_OD()
{
_GPIOG_(GPIOX_CRH) &= ~((8+1)<<4);
_GPIOG_(GPIOX_CRH) |= (2+4)<<4;
}

inline void pinG9_Output_PP_2()
{
_GPIOG_(GPIOX_CRH) &= ~((8+4+1)<<4);
_GPIOG_(GPIOX_CRH) |= (2)<<4;
}

inline void pinG9_Output_PP_10()
{
_GPIOG_(GPIOX_CRH) &= ~((8+4+2)<<4);
_GPIOG_(GPIOX_CRH) |= (1)<<4;
}

inline void pinG9_Output_PP_50()
{
_GPIOG_(GPIOX_CRH) &= ~((8+4)<<4);
_GPIOG_(GPIOX_CRH) |= (2+1)<<4;
}

inline void pinG9_Output_OD_2()
{
_GPIOG_(GPIOX_CRH) &= ~((8+1)<<4);
_GPIOG_(GPIOX_CRH) |= (2+4)<<4;
}

inline void pinG9_Output_OD_10()
{
_GPIOG_(GPIOX_CRH) &= ~((8+2)<<4);
_GPIOG_(GPIOX_CRH) |= (4+1)<<4;
}

inline void pinG9_Output_OD_50()
{
_GPIOG_(GPIOX_CRH) &= ~((8)<<4);
_GPIOG_(GPIOX_CRH) |= (4+2+1)<<4;
}

inline void pinG9_Output_AFPP_2()
{
_GPIOG_(GPIOX_CRH) &= ~((4+1)<<4);
_GPIOG_(GPIOX_CRH) |= (8+2)<<4;
}

inline void pinG9_Output_AFPP_10()
{
_GPIOG_(GPIOX_CRH) &= ~((4+2)<<4);
_GPIOG_(GPIOX_CRH) |= (8+1)<<4;
}

inline void pinG9_Output_AFPP_50()
{
_GPIOG_(GPIOX_CRH) &= ~((4)<<4);
_GPIOG_(GPIOX_CRH) |= (8+2+1)<<4;
}

inline void pinG9_Output_AFOD_2()
{
_GPIOG_(GPIOX_CRH) &= ~((1)<<4);
_GPIOG_(GPIOX_CRH) |= (8+2+4)<<4;
}

inline void pinG9_Output_AFOD_10()
{
_GPIOG_(GPIOX_CRH) &= ~((2)<<4);
_GPIOG_(GPIOX_CRH) |= (8+4+1)<<4;
}

inline void pinG9_Output_AFOD_50()
{
_GPIOG_(GPIOX_CRH) |= (8+4+2+1)<<4;
}

inline void pinG10_Input()
{
_GPIOG_(GPIOX_CRH) &= ~((8+2+1)<<8);
_GPIOG_(GPIOX_CRH) |= (4)<<8;
}

inline void pinG10_Input_PU()
{
_GPIOG_(GPIOX_CRH) &= ~((4+2+1)<<8);
_GPIOG_(GPIOX_CRH) |= (8)<<8;
_GPIOG_(GPIOX_ODR) |= (1)<<10;
}

inline void pinG10_Input_PD()
{
_GPIOG_(GPIOX_CRH) &= ~((4+2+1)<<8);
_GPIOG_(GPIOX_CRH) |= (8)<<8;
_GPIOG_(GPIOX_ODR) &= ~(1<<10);
}

inline void pinG10_Analog()
{
_GPIOG_(GPIOX_CRH) &= ~((8+4+2+1)<<8);
}

inline void pinG10_Output()
{
_GPIOG_(GPIOX_CRH) &= ~((8+4+1)<<8);
_GPIOG_(GPIOX_CRH) |= (2)<<8;
}

inline void pinG10_Output_OD()
{
_GPIOG_(GPIOX_CRH) &= ~((8+1)<<8);
_GPIOG_(GPIOX_CRH) |= (2+4)<<8;
}

inline void pinG10_Output_PP_2()
{
_GPIOG_(GPIOX_CRH) &= ~((8+4+1)<<8);
_GPIOG_(GPIOX_CRH) |= (2)<<8;
}

inline void pinG10_Output_PP_10()
{
_GPIOG_(GPIOX_CRH) &= ~((8+4+2)<<8);
_GPIOG_(GPIOX_CRH) |= (1)<<8;
}

inline void pinG10_Output_PP_50()
{
_GPIOG_(GPIOX_CRH) &= ~((8+4)<<8);
_GPIOG_(GPIOX_CRH) |= (2+1)<<8;
}

inline void pinG10_Output_OD_2()
{
_GPIOG_(GPIOX_CRH) &= ~((8+1)<<8);
_GPIOG_(GPIOX_CRH) |= (2+4)<<8;
}

inline void pinG10_Output_OD_10()
{
_GPIOG_(GPIOX_CRH) &= ~((8+2)<<8);
_GPIOG_(GPIOX_CRH) |= (4+1)<<8;
}

inline void pinG10_Output_OD_50()
{
_GPIOG_(GPIOX_CRH) &= ~((8)<<8);
_GPIOG_(GPIOX_CRH) |= (4+2+1)<<8;
}

inline void pinG10_Output_AFPP_2()
{
_GPIOG_(GPIOX_CRH) &= ~((4+1)<<8);
_GPIOG_(GPIOX_CRH) |= (8+2)<<8;
}

inline void pinG10_Output_AFPP_10()
{
_GPIOG_(GPIOX_CRH) &= ~((4+2)<<8);
_GPIOG_(GPIOX_CRH) |= (8+1)<<8;
}

inline void pinG10_Output_AFPP_50()
{
_GPIOG_(GPIOX_CRH) &= ~((4)<<8);
_GPIOG_(GPIOX_CRH) |= (8+2+1)<<8;
}

inline void pinG10_Output_AFOD_2()
{
_GPIOG_(GPIOX_CRH) &= ~((1)<<8);
_GPIOG_(GPIOX_CRH) |= (8+2+4)<<8;
}

inline void pinG10_Output_AFOD_10()
{
_GPIOG_(GPIOX_CRH) &= ~((2)<<8);
_GPIOG_(GPIOX_CRH) |= (8+4+1)<<8;
}

inline void pinG10_Output_AFOD_50()
{
_GPIOG_(GPIOX_CRH) |= (8+4+2+1)<<8;
}

inline void pinG11_Input()
{
_GPIOG_(GPIOX_CRH) &= ~((8+2+1)<<12);
_GPIOG_(GPIOX_CRH) |= (4)<<12;
}

inline void pinG11_Input_PU()
{
_GPIOG_(GPIOX_CRH) &= ~((4+2+1)<<12);
_GPIOG_(GPIOX_CRH) |= (8)<<12;
_GPIOG_(GPIOX_ODR) |= (1)<<11;
}

inline void pinG11_Input_PD()
{
_GPIOG_(GPIOX_CRH) &= ~((4+2+1)<<12);
_GPIOG_(GPIOX_CRH) |= (8)<<12;
_GPIOG_(GPIOX_ODR) &= ~(1<<11);
}

inline void pinG11_Analog()
{
_GPIOG_(GPIOX_CRH) &= ~((8+4+2+1)<<12);
}

inline void pinG11_Output()
{
_GPIOG_(GPIOX_CRH) &= ~((8+4+1)<<12);
_GPIOG_(GPIOX_CRH) |= (2)<<12;
}

inline void pinG11_Output_OD()
{
_GPIOG_(GPIOX_CRH) &= ~((8+1)<<12);
_GPIOG_(GPIOX_CRH) |= (2+4)<<12;
}

inline void pinG11_Output_PP_2()
{
_GPIOG_(GPIOX_CRH) &= ~((8+4+1)<<12);
_GPIOG_(GPIOX_CRH) |= (2)<<12;
}

inline void pinG11_Output_PP_10()
{
_GPIOG_(GPIOX_CRH) &= ~((8+4+2)<<12);
_GPIOG_(GPIOX_CRH) |= (1)<<12;
}

inline void pinG11_Output_PP_50()
{
_GPIOG_(GPIOX_CRH) &= ~((8+4)<<12);
_GPIOG_(GPIOX_CRH) |= (2+1)<<12;
}

inline void pinG11_Output_OD_2()
{
_GPIOG_(GPIOX_CRH) &= ~((8+1)<<12);
_GPIOG_(GPIOX_CRH) |= (2+4)<<12;
}

inline void pinG11_Output_OD_10()
{
_GPIOG_(GPIOX_CRH) &= ~((8+2)<<12);
_GPIOG_(GPIOX_CRH) |= (4+1)<<12;
}

inline void pinG11_Output_OD_50()
{
_GPIOG_(GPIOX_CRH) &= ~((8)<<12);
_GPIOG_(GPIOX_CRH) |= (4+2+1)<<12;
}

inline void pinG11_Output_AFPP_2()
{
_GPIOG_(GPIOX_CRH) &= ~((4+1)<<12);
_GPIOG_(GPIOX_CRH) |= (8+2)<<12;
}

inline void pinG11_Output_AFPP_10()
{
_GPIOG_(GPIOX_CRH) &= ~((4+2)<<12);
_GPIOG_(GPIOX_CRH) |= (8+1)<<12;
}

inline void pinG11_Output_AFPP_50()
{
_GPIOG_(GPIOX_CRH) &= ~((4)<<12);
_GPIOG_(GPIOX_CRH) |= (8+2+1)<<12;
}

inline void pinG11_Output_AFOD_2()
{
_GPIOG_(GPIOX_CRH) &= ~((1)<<12);
_GPIOG_(GPIOX_CRH) |= (8+2+4)<<12;
}

inline void pinG11_Output_AFOD_10()
{
_GPIOG_(GPIOX_CRH) &= ~((2)<<12);
_GPIOG_(GPIOX_CRH) |= (8+4+1)<<12;
}

inline void pinG11_Output_AFOD_50()
{
_GPIOG_(GPIOX_CRH) |= (8+4+2+1)<<12;
}

inline void pinG12_Input()
{
_GPIOG_(GPIOX_CRH) &= ~((8+2+1)<<16);
_GPIOG_(GPIOX_CRH) |= (4)<<16;
}

inline void pinG12_Input_PU()
{
_GPIOG_(GPIOX_CRH) &= ~((4+2+1)<<16);
_GPIOG_(GPIOX_CRH) |= (8)<<16;
_GPIOG_(GPIOX_ODR) |= (1)<<12;
}

inline void pinG12_Input_PD()
{
_GPIOG_(GPIOX_CRH) &= ~((4+2+1)<<16);
_GPIOG_(GPIOX_CRH) |= (8)<<16;
_GPIOG_(GPIOX_ODR) &= ~(1<<12);
}

inline void pinG12_Analog()
{
_GPIOG_(GPIOX_CRH) &= ~((8+4+2+1)<<16);
}

inline void pinG12_Output()
{
_GPIOG_(GPIOX_CRH) &= ~((8+4+1)<<16);
_GPIOG_(GPIOX_CRH) |= (2)<<16;
}

inline void pinG12_Output_OD()
{
_GPIOG_(GPIOX_CRH) &= ~((8+1)<<16);
_GPIOG_(GPIOX_CRH) |= (2+4)<<16;
}

inline void pinG12_Output_PP_2()
{
_GPIOG_(GPIOX_CRH) &= ~((8+4+1)<<16);
_GPIOG_(GPIOX_CRH) |= (2)<<16;
}

inline void pinG12_Output_PP_10()
{
_GPIOG_(GPIOX_CRH) &= ~((8+4+2)<<16);
_GPIOG_(GPIOX_CRH) |= (1)<<16;
}

inline void pinG12_Output_PP_50()
{
_GPIOG_(GPIOX_CRH) &= ~((8+4)<<16);
_GPIOG_(GPIOX_CRH) |= (2+1)<<16;
}

inline void pinG12_Output_OD_2()
{
_GPIOG_(GPIOX_CRH) &= ~((8+1)<<16);
_GPIOG_(GPIOX_CRH) |= (2+4)<<16;
}

inline void pinG12_Output_OD_10()
{
_GPIOG_(GPIOX_CRH) &= ~((8+2)<<16);
_GPIOG_(GPIOX_CRH) |= (4+1)<<16;
}

inline void pinG12_Output_OD_50()
{
_GPIOG_(GPIOX_CRH) &= ~((8)<<16);
_GPIOG_(GPIOX_CRH) |= (4+2+1)<<16;
}

inline void pinG12_Output_AFPP_2()
{
_GPIOG_(GPIOX_CRH) &= ~((4+1)<<16);
_GPIOG_(GPIOX_CRH) |= (8+2)<<16;
}

inline void pinG12_Output_AFPP_10()
{
_GPIOG_(GPIOX_CRH) &= ~((4+2)<<16);
_GPIOG_(GPIOX_CRH) |= (8+1)<<16;
}

inline void pinG12_Output_AFPP_50()
{
_GPIOG_(GPIOX_CRH) &= ~((4)<<16);
_GPIOG_(GPIOX_CRH) |= (8+2+1)<<16;
}

inline void pinG12_Output_AFOD_2()
{
_GPIOG_(GPIOX_CRH) &= ~((1)<<16);
_GPIOG_(GPIOX_CRH) |= (8+2+4)<<16;
}

inline void pinG12_Output_AFOD_10()
{
_GPIOG_(GPIOX_CRH) &= ~((2)<<16);
_GPIOG_(GPIOX_CRH) |= (8+4+1)<<16;
}

inline void pinG12_Output_AFOD_50()
{
_GPIOG_(GPIOX_CRH) |= (8+4+2+1)<<16;
}

inline void pinG13_Input()
{
_GPIOG_(GPIOX_CRH) &= ~((8+2+1)<<20);
_GPIOG_(GPIOX_CRH) |= (4)<<20;
}

inline void pinG13_Input_PU()
{
_GPIOG_(GPIOX_CRH) &= ~((4+2+1)<<20);
_GPIOG_(GPIOX_CRH) |= (8)<<20;
_GPIOG_(GPIOX_ODR) |= (1)<<13;
}

inline void pinG13_Input_PD()
{
_GPIOG_(GPIOX_CRH) &= ~((4+2+1)<<20);
_GPIOG_(GPIOX_CRH) |= (8)<<20;
_GPIOG_(GPIOX_ODR) &= ~(1<<13);
}

inline void pinG13_Analog()
{
_GPIOG_(GPIOX_CRH) &= ~((8+4+2+1)<<20);
}

inline void pinG13_Output()
{
_GPIOG_(GPIOX_CRH) &= ~((8+4+1)<<20);
_GPIOG_(GPIOX_CRH) |= (2)<<20;
}

inline void pinG13_Output_OD()
{
_GPIOG_(GPIOX_CRH) &= ~((8+1)<<20);
_GPIOG_(GPIOX_CRH) |= (2+4)<<20;
}

inline void pinG13_Output_PP_2()
{
_GPIOG_(GPIOX_CRH) &= ~((8+4+1)<<20);
_GPIOG_(GPIOX_CRH) |= (2)<<20;
}

inline void pinG13_Output_PP_10()
{
_GPIOG_(GPIOX_CRH) &= ~((8+4+2)<<20);
_GPIOG_(GPIOX_CRH) |= (1)<<20;
}

inline void pinG13_Output_PP_50()
{
_GPIOG_(GPIOX_CRH) &= ~((8+4)<<20);
_GPIOG_(GPIOX_CRH) |= (2+1)<<20;
}

inline void pinG13_Output_OD_2()
{
_GPIOG_(GPIOX_CRH) &= ~((8+1)<<20);
_GPIOG_(GPIOX_CRH) |= (2+4)<<20;
}

inline void pinG13_Output_OD_10()
{
_GPIOG_(GPIOX_CRH) &= ~((8+2)<<20);
_GPIOG_(GPIOX_CRH) |= (4+1)<<20;
}

inline void pinG13_Output_OD_50()
{
_GPIOG_(GPIOX_CRH) &= ~((8)<<20);
_GPIOG_(GPIOX_CRH) |= (4+2+1)<<20;
}

inline void pinG13_Output_AFPP_2()
{
_GPIOG_(GPIOX_CRH) &= ~((4+1)<<20);
_GPIOG_(GPIOX_CRH) |= (8+2)<<20;
}

inline void pinG13_Output_AFPP_10()
{
_GPIOG_(GPIOX_CRH) &= ~((4+2)<<20);
_GPIOG_(GPIOX_CRH) |= (8+1)<<20;
}

inline void pinG13_Output_AFPP_50()
{
_GPIOG_(GPIOX_CRH) &= ~((4)<<20);
_GPIOG_(GPIOX_CRH) |= (8+2+1)<<20;
}

inline void pinG13_Output_AFOD_2()
{
_GPIOG_(GPIOX_CRH) &= ~((1)<<20);
_GPIOG_(GPIOX_CRH) |= (8+2+4)<<20;
}

inline void pinG13_Output_AFOD_10()
{
_GPIOG_(GPIOX_CRH) &= ~((2)<<20);
_GPIOG_(GPIOX_CRH) |= (8+4+1)<<20;
}

inline void pinG13_Output_AFOD_50()
{
_GPIOG_(GPIOX_CRH) |= (8+4+2+1)<<20;
}

inline void pinG14_Input()
{
_GPIOG_(GPIOX_CRH) &= ~((8+2+1)<<24);
_GPIOG_(GPIOX_CRH) |= (4)<<24;
}

inline void pinG14_Input_PU()
{
_GPIOG_(GPIOX_CRH) &= ~((4+2+1)<<24);
_GPIOG_(GPIOX_CRH) |= (8)<<24;
_GPIOG_(GPIOX_ODR) |= (1)<<14;
}

inline void pinG14_Input_PD()
{
_GPIOG_(GPIOX_CRH) &= ~((4+2+1)<<24);
_GPIOG_(GPIOX_CRH) |= (8)<<24;
_GPIOG_(GPIOX_ODR) &= ~(1<<14);
}

inline void pinG14_Analog()
{
_GPIOG_(GPIOX_CRH) &= ~((8+4+2+1)<<24);
}

inline void pinG14_Output()
{
_GPIOG_(GPIOX_CRH) &= ~((8+4+1)<<24);
_GPIOG_(GPIOX_CRH) |= (2)<<24;
}

inline void pinG14_Output_OD()
{
_GPIOG_(GPIOX_CRH) &= ~((8+1)<<24);
_GPIOG_(GPIOX_CRH) |= (2+4)<<24;
}

inline void pinG14_Output_PP_2()
{
_GPIOG_(GPIOX_CRH) &= ~((8+4+1)<<24);
_GPIOG_(GPIOX_CRH) |= (2)<<24;
}

inline void pinG14_Output_PP_10()
{
_GPIOG_(GPIOX_CRH) &= ~((8+4+2)<<24);
_GPIOG_(GPIOX_CRH) |= (1)<<24;
}

inline void pinG14_Output_PP_50()
{
_GPIOG_(GPIOX_CRH) &= ~((8+4)<<24);
_GPIOG_(GPIOX_CRH) |= (2+1)<<24;
}

inline void pinG14_Output_OD_2()
{
_GPIOG_(GPIOX_CRH) &= ~((8+1)<<24);
_GPIOG_(GPIOX_CRH) |= (2+4)<<24;
}

inline void pinG14_Output_OD_10()
{
_GPIOG_(GPIOX_CRH) &= ~((8+2)<<24);
_GPIOG_(GPIOX_CRH) |= (4+1)<<24;
}

inline void pinG14_Output_OD_50()
{
_GPIOG_(GPIOX_CRH) &= ~((8)<<24);
_GPIOG_(GPIOX_CRH) |= (4+2+1)<<24;
}

inline void pinG14_Output_AFPP_2()
{
_GPIOG_(GPIOX_CRH) &= ~((4+1)<<24);
_GPIOG_(GPIOX_CRH) |= (8+2)<<24;
}

inline void pinG14_Output_AFPP_10()
{
_GPIOG_(GPIOX_CRH) &= ~((4+2)<<24);
_GPIOG_(GPIOX_CRH) |= (8+1)<<24;
}

inline void pinG14_Output_AFPP_50()
{
_GPIOG_(GPIOX_CRH) &= ~((4)<<24);
_GPIOG_(GPIOX_CRH) |= (8+2+1)<<24;
}

inline void pinG14_Output_AFOD_2()
{
_GPIOG_(GPIOX_CRH) &= ~((1)<<24);
_GPIOG_(GPIOX_CRH) |= (8+2+4)<<24;
}

inline void pinG14_Output_AFOD_10()
{
_GPIOG_(GPIOX_CRH) &= ~((2)<<24);
_GPIOG_(GPIOX_CRH) |= (8+4+1)<<24;
}

inline void pinG14_Output_AFOD_50()
{
_GPIOG_(GPIOX_CRH) |= (8+4+2+1)<<24;
}

inline void pinG15_Input()
{
_GPIOG_(GPIOX_CRH) &= ~((8+2+1)<<28);
_GPIOG_(GPIOX_CRH) |= (4)<<28;
}

inline void pinG15_Input_PU()
{
_GPIOG_(GPIOX_CRH) &= ~((4+2+1)<<28);
_GPIOG_(GPIOX_CRH) |= (8)<<28;
_GPIOG_(GPIOX_ODR) |= (1)<<15;
}

inline void pinG15_Input_PD()
{
_GPIOG_(GPIOX_CRH) &= ~((4+2+1)<<28);
_GPIOG_(GPIOX_CRH) |= (8)<<28;
_GPIOG_(GPIOX_ODR) &= ~(1<<15);
}

inline void pinG15_Analog()
{
_GPIOG_(GPIOX_CRH) &= ~((8+4+2+1)<<28);
}

inline void pinG15_Output()
{
_GPIOG_(GPIOX_CRH) &= ~((8+4+1)<<28);
_GPIOG_(GPIOX_CRH) |= (2)<<28;
}

inline void pinG15_Output_OD()
{
_GPIOG_(GPIOX_CRH) &= ~((8+1)<<28);
_GPIOG_(GPIOX_CRH) |= (2+4)<<28;
}

inline void pinG15_Output_PP_2()
{
_GPIOG_(GPIOX_CRH) &= ~((8+4+1)<<28);
_GPIOG_(GPIOX_CRH) |= (2)<<28;
}

inline void pinG15_Output_PP_10()
{
_GPIOG_(GPIOX_CRH) &= ~((8+4+2)<<28);
_GPIOG_(GPIOX_CRH) |= (1)<<28;
}

inline void pinG15_Output_PP_50()
{
_GPIOG_(GPIOX_CRH) &= ~((8+4)<<28);
_GPIOG_(GPIOX_CRH) |= (2+1)<<28;
}

inline void pinG15_Output_OD_2()
{
_GPIOG_(GPIOX_CRH) &= ~((8+1)<<28);
_GPIOG_(GPIOX_CRH) |= (2+4)<<28;
}

inline void pinG15_Output_OD_10()
{
_GPIOG_(GPIOX_CRH) &= ~((8+2)<<28);
_GPIOG_(GPIOX_CRH) |= (4+1)<<28;
}

inline void pinG15_Output_OD_50()
{
_GPIOG_(GPIOX_CRH) &= ~((8)<<28);
_GPIOG_(GPIOX_CRH) |= (4+2+1)<<28;
}

inline void pinG15_Output_AFPP_2()
{
_GPIOG_(GPIOX_CRH) &= ~((4+1)<<28);
_GPIOG_(GPIOX_CRH) |= (8+2)<<28;
}

inline void pinG15_Output_AFPP_10()
{
_GPIOG_(GPIOX_CRH) &= ~((4+2)<<28);
_GPIOG_(GPIOX_CRH) |= (8+1)<<28;
}

inline void pinG15_Output_AFPP_50()
{
_GPIOG_(GPIOX_CRH) &= ~((4)<<28);
_GPIOG_(GPIOX_CRH) |= (8+2+1)<<28;
}

inline void pinG15_Output_AFOD_2()
{
_GPIOG_(GPIOX_CRH) &= ~((1)<<28);
_GPIOG_(GPIOX_CRH) |= (8+2+4)<<28;
}

inline void pinG15_Output_AFOD_10()
{
_GPIOG_(GPIOX_CRH) &= ~((2)<<28);
_GPIOG_(GPIOX_CRH) |= (8+4+1)<<28;
}

inline void pinG15_Output_AFOD_50()
{
_GPIOG_(GPIOX_CRH) |= (8+4+2+1)<<28;
}

inline uint8_t readPinG0()
{
return ((_GPIOG_(GPIOX_IDR)>>0) & 1);
}

inline void setPinG0()
{
_GPIOG_(GPIOX_BSRR) = (1<<0);
}

inline void resetPinG0()
{
_GPIOG_(GPIOX_BRR) = (1<<0);
}

inline uint8_t readPinG1()
{
return ((_GPIOG_(GPIOX_IDR)>>1) & 1);
}

inline void setPinG1()
{
_GPIOG_(GPIOX_BSRR) = (1<<1);
}

inline void resetPinG1()
{
_GPIOG_(GPIOX_BRR) = (1<<1);
}

inline uint8_t readPinG2()
{
return ((_GPIOG_(GPIOX_IDR)>>2) & 1);
}

inline void setPinG2()
{
_GPIOG_(GPIOX_BSRR) = (1<<2);
}

inline void resetPinG2()
{
_GPIOG_(GPIOX_BRR) = (1<<2);
}

inline uint8_t readPinG3()
{
return ((_GPIOG_(GPIOX_IDR)>>3) & 1);
}

inline void setPinG3()
{
_GPIOG_(GPIOX_BSRR) = (1<<3);
}

inline void resetPinG3()
{
_GPIOG_(GPIOX_BRR) = (1<<3);
}

inline uint8_t readPinG4()
{
return ((_GPIOG_(GPIOX_IDR)>>4) & 1);
}

inline void setPinG4()
{
_GPIOG_(GPIOX_BSRR) = (1<<4);
}

inline void resetPinG4()
{
_GPIOG_(GPIOX_BRR) = (1<<4);
}

inline uint8_t readPinG5()
{
return ((_GPIOG_(GPIOX_IDR)>>5) & 1);
}

inline void setPinG5()
{
_GPIOG_(GPIOX_BSRR) = (1<<5);
}

inline void resetPinG5()
{
_GPIOG_(GPIOX_BRR) = (1<<5);
}

inline uint8_t readPinG6()
{
return ((_GPIOG_(GPIOX_IDR)>>6) & 1);
}

inline void setPinG6()
{
_GPIOG_(GPIOX_BSRR) = (1<<6);
}

inline void resetPinG6()
{
_GPIOG_(GPIOX_BRR) = (1<<6);
}

inline uint8_t readPinG7()
{
return ((_GPIOG_(GPIOX_IDR)>>7) & 1);
}

inline void setPinG7()
{
_GPIOG_(GPIOX_BSRR) = (1<<7);
}

inline void resetPinG7()
{
_GPIOG_(GPIOX_BRR) = (1<<7);
}

inline uint8_t readPinG8()
{
return ((_GPIOG_(GPIOX_IDR)>>8) & 1);
}

inline void setPinG8()
{
_GPIOG_(GPIOX_BSRR) = (1<<8);
}

inline void resetPinG8()
{
_GPIOG_(GPIOX_BRR) = (1<<8);
}

inline uint8_t readPinG9()
{
return ((_GPIOG_(GPIOX_IDR)>>9) & 1);
}

inline void setPinG9()
{
_GPIOG_(GPIOX_BSRR) = (1<<9);
}

inline void resetPinG9()
{
_GPIOG_(GPIOX_BRR) = (1<<9);
}

inline uint8_t readPinG10()
{
return ((_GPIOG_(GPIOX_IDR)>>10) & 1);
}

inline void setPinG10()
{
_GPIOG_(GPIOX_BSRR) = (1<<10);
}

inline void resetPinG10()
{
_GPIOG_(GPIOX_BRR) = (1<<10);
}

inline uint8_t readPinG11()
{
return ((_GPIOG_(GPIOX_IDR)>>11) & 1);
}

inline void setPinG11()
{
_GPIOG_(GPIOX_BSRR) = (1<<11);
}

inline void resetPinG11()
{
_GPIOG_(GPIOX_BRR) = (1<<11);
}

inline uint8_t readPinG12()
{
return ((_GPIOG_(GPIOX_IDR)>>12) & 1);
}

inline void setPinG12()
{
_GPIOG_(GPIOX_BSRR) = (1<<12);
}

inline void resetPinG12()
{
_GPIOG_(GPIOX_BRR) = (1<<12);
}

inline uint8_t readPinG13()
{
return ((_GPIOG_(GPIOX_IDR)>>13) & 1);
}

inline void setPinG13()
{
_GPIOG_(GPIOX_BSRR) = (1<<13);
}

inline void resetPinG13()
{
_GPIOG_(GPIOX_BRR) = (1<<13);
}

inline uint8_t readPinG14()
{
return ((_GPIOG_(GPIOX_IDR)>>14) & 1);
}

inline void setPinG14()
{
_GPIOG_(GPIOX_BSRR) = (1<<14);
}

inline void resetPinG14()
{
_GPIOG_(GPIOX_BRR) = (1<<14);
}

inline uint8_t readPinG15()
{
return ((_GPIOG_(GPIOX_IDR)>>15) & 1);
}

inline void setPinG15()
{
_GPIOG_(GPIOX_BSRR) = (1<<15);
}

inline void resetPinG15()
{
_GPIOG_(GPIOX_BRR) = (1<<15);
}



#endif /* STM32F103_GPIO_FUNC_H_ */
