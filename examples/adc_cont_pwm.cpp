/*
 * STM32F103 ADC functions library example
 * Part of STM32F103 register and peripherals library
 *
 * (c) 2020 Dmitry Reznikov ontaelio(at)gmail.com
 *
 * Can be freely used according to the GNU GPL license.
 *
 * In this example, the brightness of the Blue Pill in-built LED (C13)
 * is controlled by two potentiometers connected to pins A3 and A4
 * by using software PWM control.
 * Note that (A3+A4) is the same as (A3.read() + A4.read()).
 * The timers library is needed for the delay to work.
 */

#include <stm32f103_adc_func.h>
#include <stm32f103_gpio_func.h>
#include <stm32f103_timers_func.h>

gpioC_pin C13(13);
analog_cont A3(1, 3);
analog_cont A4(2, 4);

int main()
{
	C13.init();
	C13.mode(OUTPUT_50MHZ);
	A3.init(); // initialize objects
	A4.init();
	A3.start(); // start continuous conversion
	A4.start();

	while (1)
	{
		C13.low(); //turn the LED on
		delay_us((A3+A4)/2); //delay according to the readings
		C13.high(); //turn the LED off
		delay_us(4095 - (A3+A4)/2); //delay according to the readings
	}
}

