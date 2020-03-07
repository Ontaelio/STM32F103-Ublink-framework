/*
 * STM32F103 DMA library example
 * Part of STM32F103 register and peripherals library
 *
 * (c) 2020 Dmitry Reznikov ontaelio(at)gmail.com
 *
 * Can be freely used according to the GNU GPL license.
 *
 * Blink the built-in Blue Pill LED using DMA-to-GPIO timed transfers.
 * This example writes into BSRR register, setting and resetting individual bits.
 * Pins are not being overwritten here and can be used normally along with this.
 */

#include <stm32f103_gpio_func.h>
#include <stm32f103_dma_func.h>
#include <stm32f103_timers_func.h>

uint32_t da[2] = {0x00002000, 0x20000000}; // first value sets bit 13, second resets it
timer3 tmr(36000, 1000); // half-second timer clock cycle
dma test (DMA_TIM3_UP); // update event
gpioC portC;

int main()
{
	timer3_init();
	dma1_init();
	gpioC_init();
	pinC13_Output(); // built-in LED
	pinC14_Analog(); // these are connected to the external crystal
	pinC15_Analog(); // better turn off clocking for them

	tmr.DMAUPenable();
	tmr.enable();

	test.init(da, portC);
	test.start(2);

	while(0){}
}

