/*
 * STM32F103 EXTI library header file
 * Part of STM32F103 register and peripherals library
 *
 * Dpcumentation available in the provided MD file.
 *
 * (c) 2019-2020 Dmitry Reznikov ontaelio(at)gmail.com
 *
 * Can be freely used according to the GNU GPL license.
 */

#ifndef STM32F103_EXTI_FUNC_H_
#define STM32F103_EXTI_FUNC_H_

#include <stm32f103_exti_reg.h>
#include <stm32f103_timers_func.h>

#define EXTI_EVENT		0x01
#define EXTI_INTERRUPT	0x02
#define EXTI_IRQ		0x02
#define EXTI_RISING		0x04
#define EXTI_FALLING	0x08


void exti_eventenable(uint8_t channel) {_EXTI_(EXTI_EMR) |= (uint32_t)(1<<channel);}
void exti_eventdisable(uint8_t channel) {_EXTI_(EXTI_EMR) &= ~((uint32_t)(1<<channel));}
void exti_interruptenable(uint8_t channel); // sets up both STM and Cortex core interrupts
void exti_interruptdisable(uint8_t channel) {_EXTI_(EXTI_IMR) &= ~((uint32_t)(1<<channel));}
void exti_rising(uint8_t channel) {_EXTI_(EXTI_RTSR) |= (uint32_t)(1<<channel);} // rising edge
void exti_risingdisable(uint8_t channel) {_EXTI_(EXTI_RTSR) &= ~((uint32_t)(1<<channel));} // rising edge
void exti_falling(uint8_t channel) {_EXTI_(EXTI_FTSR) |= (uint32_t)(1<<channel);} // falling edge
void exti_fallingdisable(uint8_t channel) {_EXTI_(EXTI_FTSR) &= ~((uint32_t)(1<<channel));} // falling edge
void exti_interrupt(uint8_t channel)  {_EXTI_(EXTI_SWIER) |= (uint32_t)(1<<channel);} // generate interrupt
uint8_t exti_check(uint8_t channel)  {return ((_EXTI_(EXTI_PR)>>channel)&1);} // check pending bit
void exti_clear(uint8_t channel) {_EXTI_(EXTI_PR) &= ~((uint32_t)(1<<channel));} // clear pending bit

class exti
{
	exti(uint8_t ch_num): channel(ch_num){};

	void init(uint8_t crbits);
	void reset();
	uint8_t check() {return exti_check(channel);}
	uint8_t clear() {exti_clear(channel);}
	void interrupt() {exti_interrupt(channel);}

	uint8_t channel;
};



#endif /* STM32F103_EXTI_FUNC_H_ */
