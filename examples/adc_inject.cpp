/*
 * STM32F103 ADC functions library example
 * Part of STM32F103 register and peripherals library
 *
 * (c) 2020 Dmitry Reznikov ontaelio(at)gmail.com
 *
 * Can be freely used according to the GNU GPL license.
 *
 * Four potentiometers are connected to pins A0 .. A3.
 * Two pots are scanned constantly, two are injected and scanned on
 * external event from Timer1 every 5 seconds.
 * The output goes to a serial console (TX is on pin B6, alternative pinout used).
 */

#include <stm32f103_usart_func.h>
#include <stm32f103_adc_func.h>
#include <stm32f103_gpio_func.h>
#include <stm32f103_timers_func.h>

analog_scan twoPots; //analog scan object
uint16_t arr[2]; // array for analog scan values
timer1 tim1(36000, 10000); //will overflow once in 5 seconds
usart1 txtout; //serial output on USART1

int main()
{
	txtout.init(9600, 1); //9600 baud, alt pinout TX = B6
	txtout << "Starting...\r\n";

	tim1.init();
	tim1.master(MMS_UPDATE); //update triggers the TRGO event

	twoPots.init(arr, 3, 0,1); //regular pots are on pins A0 and A1
	twoPots.injectInit(ADC_JEXT_T1TRGO); //timer1 TRGO event
	twoPots.inject(2, 3); //injected pots are on pins A2 and A3

	twoPots.start(); //start continuous conversion
	tim1.enable(); //enable timer

	while (1)
	{
		txtout << "Regular A0: " << arr[0] << "; A1: " << arr[1] << "\r\n";
		txtout << "Injected A2: " << twoPots.injectRead(1) << "; A3: " << twoPots.injectRead(2) << "\r\n";
		delay_ms(1000);
	}
}

