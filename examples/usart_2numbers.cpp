/*
 * STM32F103 USART library example
 * Part of STM32F103 register and peripherals library
 *
 * (c) 2020 Dmitry Reznikov ontaelio(at)gmail.com
 *
 * Can be freely used according to the GNU GPL license.
 *
 * In this example two numbers (double) are requested, then their sum is printed, 
 * and then reprinted with 10 mantissa digits instead of 2. Here, the floating point decay
 * can be seen, as the USART library prints truncated values; hence the 'long version' that
 * illustrates it. Check -100 and 0.01 as an example.
 */

#include <stm32f103_usart_func.h>

usart2 term; //USART2, TX is PA2, RX is PA3
double a, b;

int main()
{
	term.init(9600); //setup baud rate
	term << "Starting...\r\n";

	while (1)
	{
		term << "Enter two numbers: " >> a >> b <<"\r\n"
				<<"entered: "<< a << " and "<< b <<"\r\n"
				<<"The sum is: " << a + b << "\r\n";
		term << "And the long version is: ";
		term.printFloat(a+b, 10); //print the double with 10 decimals
		term << "\r\n";
	}
}

