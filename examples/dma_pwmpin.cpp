/*
 * STM32F103 DMA library example
 * Part of STM32F103 register and peripherals library
 *
 * (c) 2020 Dmitry Reznikov ontaelio(at)gmail.com
 *
 * Can be freely used according to the GNU GPL license.
 *
 * Blink with DMA and a PWM pin A8. Connect an LEDs cathode to PA8,
 * anode to 3.3v rail via some small resistor (like 100 Ohms or less).
 */

#include <stm32f103_gpio_func.h>
#include <stm32f103_dma_func.h>
#include <stm32f103_timers_func.h>

uint16_t da[2] = {0, 1999}; // can't use 0, 2000 in CC event mode!
tim1_pwm PA8(1, 2000);
dma test;

int main()
{
	timer1_init();
	dma1_init();
	
	PA8.init();
	PA8 = 1999;
	PA8.prescaler = 36000; // timer updates every second

	test.init(da, PA8);

	test.start(2);
	PA8.enable();
	
	while(1){} // empty cycle
}


