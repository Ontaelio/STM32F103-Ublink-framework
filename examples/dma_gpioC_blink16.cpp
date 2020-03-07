/*
 * STM32F103 DMA library example
 * Part of STM32F103 register and peripherals library
 *
 * (c) 2020 Dmitry Reznikov ontaelio(at)gmail.com
 *
 * Can be freely used according to the GNU GPL license.
 *
 * Blink the built-in Blue Pill LED using DMA-to-GPIO timed transfers.
 * This example writes directly into the output data register, overwriting
 * all 16 outputs.
 */

#include <stm32f103_gpio_func.h>
#include <stm32f103_dma_func.h>
#include <stm32f103_timers_func.h>

uint16_t da[2] = {0x2000, 0};
timer1 tmr(36000, 2000); // 1-second timer clock cycle
dma test (DMA_TIM1_UP); // update event
gpioC portC;

int main()
{
	timer1_init();
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

