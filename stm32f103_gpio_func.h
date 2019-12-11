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

typedef gpioA gpioA_pin;
typedef gpioB gpioB_pin;
typedef gpioC gpioC_pin;

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
_GPIOB_(GPIOX_ODR) |= (1)<<0;
}

inline void pinB8_Input_PD()
{
_GPIOB_(GPIOX_CRH) &= ~((4+2+1)<<0);
_GPIOB_(GPIOX_CRH) |= (8)<<0;
_GPIOB_(GPIOX_ODR) &= ~(1<<0);
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
_GPIOB_(GPIOX_ODR) |= (1)<<1;
}

inline void pinB9_Input_PD()
{
_GPIOB_(GPIOX_CRH) &= ~((4+2+1)<<4);
_GPIOB_(GPIOX_CRH) |= (8)<<4;
_GPIOB_(GPIOX_ODR) &= ~(1<<1);
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
_GPIOB_(GPIOX_ODR) |= (1)<<2;
}

inline void pinB10_Input_PD()
{
_GPIOB_(GPIOX_CRH) &= ~((4+2+1)<<8);
_GPIOB_(GPIOX_CRH) |= (8)<<8;
_GPIOB_(GPIOX_ODR) &= ~(1<<2);
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
_GPIOB_(GPIOX_ODR) |= (1)<<3;
}

inline void pinB11_Input_PD()
{
_GPIOB_(GPIOX_CRH) &= ~((4+2+1)<<12);
_GPIOB_(GPIOX_CRH) |= (8)<<12;
_GPIOB_(GPIOX_ODR) &= ~(1<<3);
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
_GPIOB_(GPIOX_ODR) |= (1)<<4;
}

inline void pinB12_Input_PD()
{
_GPIOB_(GPIOX_CRH) &= ~((4+2+1)<<16);
_GPIOB_(GPIOX_CRH) |= (8)<<16;
_GPIOB_(GPIOX_ODR) &= ~(1<<4);
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
_GPIOB_(GPIOX_ODR) |= (1)<<5;
}

inline void pinB13_Input_PD()
{
_GPIOB_(GPIOX_CRH) &= ~((4+2+1)<<20);
_GPIOB_(GPIOX_CRH) |= (8)<<20;
_GPIOB_(GPIOX_ODR) &= ~(1<<5);
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
_GPIOB_(GPIOX_ODR) |= (1)<<6;
}

inline void pinB14_Input_PD()
{
_GPIOB_(GPIOX_CRH) &= ~((4+2+1)<<24);
_GPIOB_(GPIOX_CRH) |= (8)<<24;
_GPIOB_(GPIOX_ODR) &= ~(1<<6);
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
_GPIOB_(GPIOX_ODR) |= (1)<<7;
}

inline void pinB15_Input_PD()
{
_GPIOB_(GPIOX_CRH) &= ~((4+2+1)<<28);
_GPIOB_(GPIOX_CRH) |= (8)<<28;
_GPIOB_(GPIOX_ODR) &= ~(1<<7);
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
_GPIOA_(GPIOX_ODR) |= (1)<<0;
}

inline void pinA8_Input_PD()
{
_GPIOA_(GPIOX_CRH) &= ~((4+2+1)<<0);
_GPIOA_(GPIOX_CRH) |= (8)<<0;
_GPIOA_(GPIOX_ODR) &= ~(1<<0);
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
_GPIOA_(GPIOX_ODR) |= (1)<<1;
}

inline void pinA9_Input_PD()
{
_GPIOA_(GPIOX_CRH) &= ~((4+2+1)<<4);
_GPIOA_(GPIOX_CRH) |= (8)<<4;
_GPIOA_(GPIOX_ODR) &= ~(1<<1);
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
_GPIOA_(GPIOX_ODR) |= (1)<<2;
}

inline void pinA10_Input_PD()
{
_GPIOA_(GPIOX_CRH) &= ~((4+2+1)<<8);
_GPIOA_(GPIOX_CRH) |= (8)<<8;
_GPIOA_(GPIOX_ODR) &= ~(1<<2);
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
_GPIOA_(GPIOX_ODR) |= (1)<<3;
}

inline void pinA11_Input_PD()
{
_GPIOA_(GPIOX_CRH) &= ~((4+2+1)<<12);
_GPIOA_(GPIOX_CRH) |= (8)<<12;
_GPIOA_(GPIOX_ODR) &= ~(1<<3);
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
_GPIOA_(GPIOX_ODR) |= (1)<<4;
}

inline void pinA12_Input_PD()
{
_GPIOA_(GPIOX_CRH) &= ~((4+2+1)<<16);
_GPIOA_(GPIOX_CRH) |= (8)<<16;
_GPIOA_(GPIOX_ODR) &= ~(1<<4);
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
_GPIOA_(GPIOX_ODR) |= (1)<<5;
}

inline void pinA13_Input_PD()
{
_GPIOA_(GPIOX_CRH) &= ~((4+2+1)<<20);
_GPIOA_(GPIOX_CRH) |= (8)<<20;
_GPIOA_(GPIOX_ODR) &= ~(1<<5);
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
_GPIOA_(GPIOX_ODR) |= (1)<<6;
}

inline void pinA14_Input_PD()
{
_GPIOA_(GPIOX_CRH) &= ~((4+2+1)<<24);
_GPIOA_(GPIOX_CRH) |= (8)<<24;
_GPIOA_(GPIOX_ODR) &= ~(1<<6);
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
_GPIOA_(GPIOX_ODR) |= (1)<<7;
}

inline void pinA15_Input_PD()
{
_GPIOA_(GPIOX_CRH) &= ~((4+2+1)<<28);
_GPIOA_(GPIOX_CRH) |= (8)<<28;
_GPIOA_(GPIOX_ODR) &= ~(1<<7);
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
_GPIOC_(GPIOX_ODR) |= (1)<<0;
}

inline void pinC8_Input_PD()
{
_GPIOC_(GPIOX_CRH) &= ~((4+2+1)<<0);
_GPIOC_(GPIOX_CRH) |= (8)<<0;
_GPIOC_(GPIOX_ODR) &= ~(1<<0);
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
_GPIOC_(GPIOX_ODR) |= (1)<<1;
}

inline void pinC9_Input_PD()
{
_GPIOC_(GPIOX_CRH) &= ~((4+2+1)<<4);
_GPIOC_(GPIOX_CRH) |= (8)<<4;
_GPIOC_(GPIOX_ODR) &= ~(1<<1);
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
_GPIOC_(GPIOX_ODR) |= (1)<<2;
}

inline void pinC10_Input_PD()
{
_GPIOC_(GPIOX_CRH) &= ~((4+2+1)<<8);
_GPIOC_(GPIOX_CRH) |= (8)<<8;
_GPIOC_(GPIOX_ODR) &= ~(1<<2);
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
_GPIOC_(GPIOX_ODR) |= (1)<<3;
}

inline void pinC11_Input_PD()
{
_GPIOC_(GPIOX_CRH) &= ~((4+2+1)<<12);
_GPIOC_(GPIOX_CRH) |= (8)<<12;
_GPIOC_(GPIOX_ODR) &= ~(1<<3);
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
_GPIOC_(GPIOX_ODR) |= (1)<<4;
}

inline void pinC12_Input_PD()
{
_GPIOC_(GPIOX_CRH) &= ~((4+2+1)<<16);
_GPIOC_(GPIOX_CRH) |= (8)<<16;
_GPIOC_(GPIOX_ODR) &= ~(1<<4);
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
_GPIOC_(GPIOX_ODR) |= (1)<<5;
}

inline void pinC13_Input_PD()
{
_GPIOC_(GPIOX_CRH) &= ~((4+2+1)<<20);
_GPIOC_(GPIOX_CRH) |= (8)<<20;
_GPIOC_(GPIOX_ODR) &= ~(1<<5);
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
_GPIOC_(GPIOX_ODR) |= (1)<<6;
}

inline void pinC14_Input_PD()
{
_GPIOC_(GPIOX_CRH) &= ~((4+2+1)<<24);
_GPIOC_(GPIOX_CRH) |= (8)<<24;
_GPIOC_(GPIOX_ODR) &= ~(1<<6);
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
_GPIOC_(GPIOX_ODR) |= (1)<<7;
}

inline void pinC15_Input_PD()
{
_GPIOC_(GPIOX_CRH) &= ~((4+2+1)<<28);
_GPIOC_(GPIOX_CRH) |= (8)<<28;
_GPIOC_(GPIOX_ODR) &= ~(1<<7);
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



#endif /* STM32F103_GPIO_FUNC_H_ */
