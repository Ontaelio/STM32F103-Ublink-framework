/*
 * STM32F103 USART library example
 * Part of STM32F103 register and peripherals library
 *
 * (c) 2020 Dmitry Reznikov ontaelio(at)gmail.com
 *
 * Can be freely used according to the GNU GPL license.
 *
 * This program requests a text file from the user, copies it into an array,
 * then sends the contents of this array back.
 * Note: the size in `filesize` must be exact. The current value corresponds
 * to the size of this demo program. Also note that this example uses high baud rate
 * and the alternative pinout for USART1.
 */

#include <stm32f103_usart_func.h>

usart1 term; //USART1, alt pinout, TX is PB6, RX is PB7
uint8_t txt[4000];
char k; //a char buffer for 'press any key'
uint16_t filesize = 1085; //the size must be exact!

int main()
{
	term.init(115200, 1); //setup baud rate and alt pinout

	while(1)
	{
		term << "Send us some file!\r\n";
		term.getStream(txt, filesize);

		term << "Received. Let's see what we've got:\r\n";
		term.sendStream(txt, filesize);

		term << "\r\nPress any key... " >> k << "ok!\r\n";
	}
}

