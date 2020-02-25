/*
 * STM32F103 ADC functions library example
 * Part of STM32F103 register and peripherals library
 *
 * (c) 2020 Dmitry Reznikov ontaelio(at)gmail.com
 *
 * Can be freely used according to the GNU GPL license.
 *
 * This basic example turns the Blue Pill in-built LED at pin C13 on and off
 * depending on the position of a potentiometer connected to pin A1.
 */

#include <stm32f103_adc_func.h>
#include <stm32f103_gpio_func.h>

gpioC_pin C13(13);
analog_pin A1(1);

int main()
{
	C13.init();
	C13.mode(OUTPUT);
	A1.init();

	while (1)
	{
		if (A1 < 2047) C13.high(); else C13.low();
		// same as if (A1.read() < 2047) C13.high(); else C13.low();
	}
}
