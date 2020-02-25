/*
 * STM32F103 ADC functions library example
 * Part of STM32F103 register and peripherals library
 *
 * (c) 2020 Dmitry Reznikov ontaelio(at)gmail.com
 *
 * Can be freely used according to the GNU GPL license.
 *
 * Four potentiometers are connected to pins A0 .. A3.
 * If the sum of the readings on pins A2 and A3 is more than the sum of the readings
 * on pins A0 and A1, the in-built Blue Pill LED (C13) lights up and is dark otherwise.
 */

#include <stm32f103_adc_func.h>
#include <stm32f103_gpio_func.h>

gpioC_pin C13(13);
analog_scan fourPots;
uint16_t arr[4]; //an array to hold the conversion results

int main()
{
	C13.init();
	C13.mode(OUTPUT);
	fourPots.init(arr, 4, 0,1,2,3); //pots are on pins A0, A1, A2 and A3
	fourPots.start(); //start continuous conversion

	while (1)
	{
		if ((arr[0] + arr[1]) > (arr[2] + arr[3])) C13.high(); else C13.low();
	}
}

