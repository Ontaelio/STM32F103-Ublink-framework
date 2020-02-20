/*
 * STM32F103 ADC functions header file
 * Part of STM32F103 register and peripherals library
 *
 * Dpcumentation available in the provided MD file.
 *
 * (c) 2019-2020 Dmitry Reznikov ontaelio(at)gmail.com
 *
 * Can be freely used according to the GNU GPL license.
 */
#ifndef STM32F103_ADC_FUNC_H_
#define STM32F103_ADC_FUNC_H_

#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <stm32f103_adc_reg.h>
#include <stm32f103_rcc_reg.h>
#include <stm32f103_gpio_reg.h>
#include <stm32f103_gpio_func.h>
#include <stm32f103_timers_func.h>
#include <stm32f103_dma_func.h>

class analog_pin
{
public:
	analog_pin(uint_fast8_t cha) : cnum (cha) {}
	void init(uint8_t cycles = 0);
	uint16_t read();

protected:
	uint_fast8_t cnum;
};

class analog_cont
{
public:
	analog_cont(uint_fast8_t adg, uint_fast8_t cha) :
			cnum (cha), adc ((volatile uint32_t *)(0x40012400 + 0x0000400 * (adg - 1))) {}
	void init(uint8_t cycles = 0);
	void start();
	void stop() {*(adc + ADC_CR2/4) &= ~ADC_CR2_ADON;}
	uint16_t read() {return *(adc + 19);}
	operator uint16_t() {return *(adc + 19);}

protected:
	uint_fast8_t cnum;
	volatile uint32_t* adc;
};

class analog_scan
{
public:
	//analog_scan();
	void init(uint16_t* targ, uint_fast8_t num, ...); // DMA1 channel 1
	void start() {_ADC1_(ADC_CR2) |= ADC_CR2_CONT;	_ADC1_(ADC_CR2) |= ADC_CR2_ADON;}
	void stop() {_ADC1_(ADC_CR2) &= ~ADC_CR2_CONT;}
	void read() {_ADC1_(ADC_CR2) |= ADC_CR2_ADON;} //convert once
	void speed(uint_fast8_t cha, uint8_t cycles);
	void priority(uint8_t pri) {_DMA1_(DMA_CCR1) &= ~DMA_CCR_PL; _DMA1_(DMA_CCR1) |= (pri << 12);}

	void external(uint8_t regtrig);
	void externalStart() {_ADC1_(ADC_CR2) |= ADC_CR2_CONT; _ADC1_(ADC_CR2) |= ADC_CR2_SWSTART;}
	void externalRead() { _ADC1_(ADC_CR2) |= ADC_CR2_SWSTART;}

	void injectInit(uint8_t jtrigger = 7);
	void inject(uint8_t cha1);
	void inject(uint8_t cha1, uint8_t cha2);
	void inject(uint8_t cha1, uint8_t cha2, uint8_t cha3);
	void inject(uint8_t cha1, uint8_t cha2, uint8_t cha3, uint8_t cha4);
	void injectStart(uint_fast8_t dowait = 1);
	void injectClear() {_ADC1_(ADC_SR) &= ~ADC_SR_JEOC;}
	uint16_t injectRead(uint_fast8_t jcha);

private:
	void injectWaitForResult();
};

//single injected channel object
class analog_inject
{
	analog_inject(uint_fast8_t dadcma, uint_fast8_t cha) :
			cnum (cha), adc ((volatile uint32_t *)(0x40012400 + 0x0000400 * (dadcma - 1))) {}
	void init(uint8_t jtrigger = 7, uint8_t cycles = 0);
	void inject();
	uint16_t read(uint8_t jch) {return *(adc + ADC_JSQR/4 + jch);} //JSQR is right before JDR1
	void autoInject(uint8_t b = 1);

protected:
	uint_fast8_t cnum;
	volatile uint32_t* adc;
};


void adc1_init();
void adc2_init();

void adc1_injectSetup(uint_fast8_t jtrigger);



#endif /* STM32F103_ADC_FUNC_H_ */
