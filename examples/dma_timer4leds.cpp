/*
 * STM32F103 DMA library example
 * Part of STM32F103 register and peripherals library
 *
 * (c) 2020 Dmitry Reznikov ontaelio(at)gmail.com
 *
 * Can be freely used according to the GNU GPL license.
 *
 * Blink four LEDs with DMA. Connect four LEDs to PA8, PA8, PA10 and PA11
 * (cathode to pin, anode to 3.3v rail via some small resistor (like 100 Ohms or less).
 */

#include <stm32f103_gpio_func.h>
#include <stm32f103_dma_func.h>
#include <stm32f103_timers_func.h>

uint16_t da[16] = {2000, 0, 0, 0,
				  0, 2000, 0, 0,
				  0, 0, 2000, 0,
				  0, 0, 0, 2000};

timer1 tmr(36000, 2000); // 1 second timer cycle
dma test;

int main()
{
	timer1_init();
	dma1_init();
	gpioA_init();

	tmr.pwmSetup(0, 0); // setup PWM and four channels
	tmr.pwmChannel(1, 1, 1); // polarity: low when active
	tmr.pwmChannel(2, 1, 1); // to avoid parasitic blinks
	tmr.pwmChannel(3, 1, 1);
	tmr.pwmChannel(4, 1, 1);
	tmr.enable();

	test.init(da, tmr); // default number of channels = 4
	test.start(16); // 4 values will be sent in one burst, 4 bursts for full cycle

	while(0){} // empty cycle
}


