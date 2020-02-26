/*
 * STM32F103 ADC functions library example
 * Part of STM32F103 register and peripherals library
 *
 * (c) 2020 Dmitry Reznikov ontaelio(at)gmail.com
 *
 * Can be freely used according to the GNU GPL license.
 *
 * Two potentiometers are connected to pins A2 and A3 (*Analog Continuous* objects).
 * When A2 goes above the `wdhigh` value, the in-built led at C13 lights up.
 * When it goes below the `wdlow` value, the led turns off. 
 * The `wdhigh` and `wdlow` values are set to mid-point initially. 
 * A3 is being constantly updated but does nothing else.
 */

#include <stm32f103_adc_func.h>
#include <stm32f103_gpio_func.h>

gpioC_pin C13(13);
analog_cont A2(1, 2), A3(2, 3);
const uint16_t wdlow = 2047;
const uint16_t wdhigh = 2048;

// interrupt routine
extern "C"
{
void ADC1_2_IRQHandler()
{
	if (adc1_WD()) //make sure it was the watchdog event
	{
		if (A2 > wdhigh)
			{
			//'remove' high threshold, restore low
			adc1_watchdogLowHigh(wdlow, 4095);
			C13.low();
			}
		else
			{
			//'remove' low threshold, restore high
			adc1_watchdogLowHigh(0, wdhigh);
			C13.high();
			}
	adc1_clearWD(); //clear the event flag to avoid permanent interrupt
	}
}
}

int main()
{
	C13.init();
	C13.mode(OUTPUT);
	C13.high(); //turn the LED off

 	A2.init(); //adc must be initialized before the watchdog setup
	A3.init();

	adc1_watchdog(2, wdlow, wdhigh); //setup watchdog on channel 2
	adc_IRQenable(); //enable ADC1_2 IRQ
	adc1_WDinterrupt(1); //enable watchdog interrupt

	A2.start(); //start continuous mode
	A3.start();

	while (1){} //nothing to do here
}

