/*
 * STM32F103 EXTI library source file
 * Part of STM32F103 register and peripherals library
 *
 * Dpcumentation available in the provided MD file.
 *
 * (c) 2019-2020 Dmitry Reznikov ontaelio(at)gmail.com
 *
 * Can be freely used according to the GNU GPL license.
 */

#include <stm32f103_exti.h>



void exti_interruptenable(uint8_t channel)
{
	_EXTI_(EXTI_IMR) |= (uint32_t)(1<<channel);
	switch (channel)
	{
		case 0:  IRQ_0TO31_SER |= IRQ_BITMASK_EXTI0; break;
		case 1:  IRQ_0TO31_SER |= IRQ_BITMASK_EXTI1; break;
		case 2:  IRQ_0TO31_SER |= IRQ_BITMASK_EXTI2; break;
		case 3:  IRQ_0TO31_SER |= IRQ_BITMASK_EXTI3; break;
		case 4:  IRQ_0TO31_SER |= IRQ_BITMASK_EXTI4; break;
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:  IRQ_0TO31_SER |= IRQ_BITMASK_EXTI9_5; break;
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15: IRQ_32TO63_SER |= IRQ_BITMASK_EXTI15_10; break;
		case 16:  IRQ_0TO31_SER |= IRQ_BITMASK_PVD; break;
		case 17:  IRQ_32TO63_SER |= IRQ_BITMASK_RTCAlarm; break;
		case 18:  IRQ_32TO63_SER |= IRQ_BITMASK_USBWakeup; break;
		default: break;
	}
}

void exti::reset()
{
	exti_eventdisable(channel);
	exti_interruptdisable(channel);
	exti_risingdisable(channel);
	exti_fallingdisable(channel);
}

void exti::init(uint8_t crbits)
{
	if (crbits & EXTI_EVENT) exti_eventenable(channel); else exti_eventdisable(channel);
	if (crbits & EXTI_INTERRUPT) exti_interruptenable(channel); else exti_interruptdisable(channel);
	if (crbits & EXTI_RISING) exti_rising(channel); else exti_risingdisable(channel);
	if (crbits & EXTI_FALLING) exti_falling(channel); else exti_fallingdisable(channel);
}

void exti::gpio(uint8_t gpio)
{
	_RCC_(RCC_APB2ENR) |= RCC_APB2ENR_AFIOEN;
	_AFIO_(AFIO_EXTICR1 + (channel/4)*4) &= ~(0xF << ((channel&3)*4));
	_AFIO_(AFIO_EXTICR1 + (channel/4)*4) |= gpio << ((channel&3)*4);
}
