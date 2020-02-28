/*
 * STM32F103 USART library example
 * Part of STM32F103 register and peripherals library
 *
 * (c) 2020 Dmitry Reznikov ontaelio(at)gmail.com
 *
 * Can be freely used according to the GNU GPL license.
 *
 * A basic example printing 'Hello World!' every half-second and counting the lines.
 * Timers library included for the delay function.
 */

#include <stm32f103_usart_func.h>
#include <stm32f103_timers_func.h>

usart3 term; //create a USART3 object; TX on pin B10
uint16_t cnt;

int main()
{
	term.init(9600); //set baud rate
	term << "Starting...\r\n";

	while (1)
	{
		term << ++cnt <<": Hello world!\r\n";
		delay_ms(500); //wait half a second
	}
}

