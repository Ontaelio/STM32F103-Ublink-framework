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

#ifndef STM32F103_EXTI_H_
#define STM32F103_EXTI_H_

#include <stm32f103_exti_reg.h>
#include <stm32f103_timers_reg.h>
#include <stm32f103_rcc_reg.h>
#include <stm32f103_gpio_reg.h>
#include <stdio.h>
#include <stdint.h>

#define EXTI_EVENT		0x01
#define EXTI_INTERRUPT	0x02
#define EXTI_IRQ		0x02
#define EXTI_RISING		0x04
#define EXTI_FALLING	0x08

#define EXTI_GPIOA		0
#define EXTI_GPIOB		1
#define EXTI_GPIOC		2
#define EXTI_GPIOD		3
#define EXTI_GPIOE		4
#define EXTI_GPIOF		5
#define EXTI_GPIOG		6



inline void exti_eventenable(uint8_t channel) {_EXTI_(EXTI_EMR) |= (uint32_t)(1<<channel);}
inline void exti_eventdisable(uint8_t channel) {_EXTI_(EXTI_EMR) &= ~((uint32_t)(1<<channel));}
inline void exti_interruptenable(uint8_t channel); // sets up both STM and Cortex core interrupts
inline void exti_interruptdisable(uint8_t channel) {_EXTI_(EXTI_IMR) &= ~((uint32_t)(1<<channel));}
inline void exti_rising(uint8_t channel) {_EXTI_(EXTI_RTSR) |= (uint32_t)(1<<channel);} // rising edge
inline void exti_risingdisable(uint8_t channel) {_EXTI_(EXTI_RTSR) &= ~((uint32_t)(1<<channel));} // rising edge
inline void exti_falling(uint8_t channel) {_EXTI_(EXTI_FTSR) |= (uint32_t)(1<<channel);} // falling edge
inline void exti_fallingdisable(uint8_t channel) {_EXTI_(EXTI_FTSR) &= ~((uint32_t)(1<<channel));} // falling edge
inline void exti_interrupt(uint8_t channel)  {_EXTI_(EXTI_SWIER) |= (uint32_t)(1<<channel);} // generate interrupt
inline uint8_t exti_check(uint8_t channel)  {return ((_EXTI_(EXTI_PR)>>channel)&1);} // check pending bit
inline void exti_clear(uint8_t channel) {_EXTI_(EXTI_PR) |= (uint32_t)(1<<channel);} // clear pending bit by writing 1

class exti
{
public:
	exti(uint8_t ch_num): channel(ch_num){};

	void init(uint8_t crbits);
	void gpio(uint8_t gpio);
	void reset();
	uint8_t check() {return exti_check(channel);}
	void clear() {exti_clear(channel);}
	void interrupt() {exti_interrupt(channel);}

	uint8_t channel;
};



#endif /* STM32F103_EXTI_H_ */
