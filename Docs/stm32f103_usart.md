# USART library

The USART library consists of a partially abstract class `usart` and it's inherited classes `usart1`, `usart2` and `usart3`. These classes provide all the needed member functions to control USART communications. Unlike other libraries here, there are no non-member functions in this library.

Contents:
* [Quick start guide](#quick-start)
* [USART pinout](#usart-pinout)
* [Higher level class functions](#higher-level-class-functions)
* [Read, print and formatted print functions](#read-print-and-formatted-print-functions)
* [Interrupts and errors](#interrupts-and-errors)
* [usart_mem class](#usart_mem-class)
* [Setup member functions](#setup-member-functions)
* [Defined values and compiler directives](#defined-values-and-compiler-directives)
* [Code examples](#examples)


## Quick start

The USART library is built around two use-cases:

a) sending and receiving text information to/from a PC via a serial terminal;
b) sending and receiving chunks of data via USART (mainly PC again).

To do these tasks a class object must be declared and initialized, then simple operators and functions do their job.

There are three classes: `usart1`, `usart2` and `usart3`, all use a default constructor. Initialization is done with a standard `init(uint16_t baud)` member function that sets up the USART speed to `baud`. For USART1 an optional parameter is added to `init` that allows the use of the alternative pinout: `init(baud, 1)`. `init` enables USART, GPIO and AFIO clocks and configures the needed pins according to their USART role.

Sending and receiving text information is done with `<<` and `>>` operators, like with the standard streams. Streams are not realized in this library, however, thus both `<<` and `>>` can be used in the same line, e.g.
```cpp
term << "Enter a number: " >> num;
```
where `term` is a `usartX` object and `num` is an int/float variable where the user-entered value will be stored.

As we're not dealing with streams, any data is immediately sent or read after a `<<` or `>>` operator is encountered.

`<<` and `>>` can convert to text, send and receive all the standard variable types except `bool`, as well as C-style strings. For code please check the [examples section](#examples) below.

Sending and receiving chunks of data is done with `sendStream()` and `getStream()` member functions. These functions accept an array of bytes as their first argument and the number of bytes to transfer as the second. Check the [data stream example](#usart-data-stream) below.

## USART pinout

USART | TX | RX | remap TX | remap RX
--|--|--|--|--
USART1 | PA9 | PA10 | PB6 | PB7
USART2 | PA2 | PA3 |  | 
USART3 | PB10 | PB11 | 

*Note: for full pinout please check pages 180-181 of the RM0008 STM32F103 reference manual.*

## Higher level class functions

Constructor:

* **usart1**, **usart2**, **usart3**

Create an object of `usart` type. A default constructor is used, no arguments needed.

* void **init (uint32_t baud, uint_fast8_t remap = 0)**

Initializes a `usart` object and enables USART interface at the speed of `baud`. Optional `remap` value (USART1 only) remaps the TX and RX pins if non-zero.

* void **initTX (uint32_t baud, uint_fast8_t remap = 0)**

Initializes USART in TX (output) mode only, leaving RX pin free for general GPIO use.

* void **initRX (uint32_t baud, uint_fast8_t remap = 0)**

Initializes USART in RX (input) mode only, leaving TX pin free for general GPIO use.

* void **sendByte (uint8_t dat)**

Sends a single byte via USART.

* uint8_t **getByte ()**

Returns a single byte received from USART. Note that this function will wait for the byte, stopping the program.

* overloaded operators **<<** and **>>**

Receive and send data over USART. Any numbers are converted to/from text with these operators. The following data types are accepted:
```
char, char* (C-type string),
int, int8_t, int16_t, int32_t, int64_t,
unsigned, uint8_t, uint16_t, uint32_t, uint64_t,
float, double, long double.
```

Floating numbers are printed **truncated** to 2 numbers after the decimal point. This may show the floating decay. If you need the correct output, use `math.h` rounding functions and formatted print functions (see below).

* void **sendStream (uint8_t\* dat, uint32_t size)**

Sends a stream of `size` bytes from an array `dat` via USART.

* void **getStream (uint8_t\* dat, uint16_t size)**

Receives a stream of `size` bytes from USART into an array `dat`. This function ends only after the full `size` of bytes was transferred.

* void **sendStreamDMA (uint8_t\* dat, uint32_t size)**

Initiates a sending of `size` number of bytes from an array `dat` using DMA. DMA here has high priority. Note that this function doesn't wait for the transfer to complete.

*Note: DMA must be initialized with the `dma1_init()` function prior to use.*

* void **getStreamDMA (uint8_t\* dat, uint32_t size)**

Initiates a receiving of `size` number of bytes from an array `dat` using DMA. DMA here has high priority. Note that this function doesn't wait for the transfer to complete.

*Note: check the transfer complete flag in the DMA_ISR register (`dma1_transfercomplete()` function) to know that the data was transferred. More on this in the DMA library manual.*

* void **startTX (uint8_t\* dat, uint16_t size, uint16_t pri = 0x1000)**

Initiates a circular DMA transfer of the array `dat` into the USART channel. That is, the `size` amount of bytes will be constantly sent over and over again until the DMA channel is disabled with `stopTX()`. Optional `pri` argument sets the DMA priority level. The following values are defined for priority levels: `DMA_PLLOW`, `DMA_PLMEDIUM` (default), `DMA_PLHIGH` and `DMA_PLVHIGH`.

*Note: if the constant dumping of data is used for ADC (`analog_scan` object), there's no need to change the priority as the ADC uses the DMA channel 1 and stays higher in the list even when set to the same priority level (as it is by default).*

* void **stopTX()**

Stops the circular transfer and disables the corresponding DMA channel.

* void **startRX (uint8_t\* dat, uint16_t size, uint16_t pri = 0x1000)**

Initiates a circular DMA read from the USART channel into the array `dat`. Once `size` number of bytes is received, writing restarts at the beginning of the array (circular buffer).

* void **stopRX()**

Stops the circular read and disables the corresponding DMA channel.

* void **dump()**

Dumps the last received byte if present. Useful prior to any kind of 'press any key' request, as some terminal programs may send unwanted stuff (like new lines) from time to time; these bytes sit in the incoming register and are considered 'newly received' when polled.

## Read, print and formatted print functions

Most of the following functions are used by the overloaded `<<` and `>>` operators. You may use the functions instead of the operators if you wish.

* void **printString(const char\* str)**

Outputs a C-style string `str`. Usual phrases in double quotes like "Hello world!" are printed with this function.

* void **printCPPString(std::string s)**

Prints a C++ string (`string.h` standard library). Note that `<<` operator doesn't support such strings, but can print them if you use their `c_str` pointer (e.g. `term << some_string.c_str`).

* void **printUInt(uint32_t a)**
* void **printInt(int32_t a)**
* void **printUInt64(uint64_t a)**
* void **printInt64(int64_t a)**
* void **printFloat(long double a, uint_fast8_t s = 2)**

Convert the number of the corresponding data type (`unsigned int`, `int` or `double`) into text and send the text over the USART. Functions dealing with 64-bit integers use a buffer to order the symbols, while 32-bit values are ordered using stack (with inline assembly).

* void **printHex(unsigned val)**

Prints the provided number in hex in 0x123... format. Leading zeroes omitted.

* void **fprintUInt(uint32_t a, uint_fast8_t s)**

Formatted print for the unsigned int types. Adds '0's at the beginning to make the total number of characters equal to `s`.

* char **getChar()**
* uint64_t **getUInt()**
* int64_t **getInt()**
* long double **getFloat()**

Receive text data from the USART and convert it into the corresponding data type if needed.

* void **getString(char\* arr)**

Receive a string of characters and convert it into a C-style string (character array). Any ASCII code below space (like line feed or carriage return) will signal the end of the string. Note that `arr` must be big enough to accomodate all the input characters + 1.

## Interrupts and errors

There's only one IRQ per USART channel in the Cortex M3 architecture, but STM provides multiple cases for this interrupt to trigger.

* void **IRQenable(uint16_t irqs)**
* void **IRQdisable()**

Enable/disable IRQ. `irqs` argument contains the interrupts that are being ebabled. You can use either the 'macro' or the 'register bit' (also a macro). While these bits are from different registers, they can be used together in a single function argument using '|' (OR operator); the function will place them accordingly. 

macro | register bit | description
---|---|---
USART_TX_EMPTY | USART_CR1_TXEIE | TX empty
USART_TRANSFER_COMPLETE | USART_CR1_TCIE | Transfer complete
USART_RX_NOT_EMPTY | USART_CR1_RXNEIE | RX not empty
USART_IDLE_LINE | USART_CR1_IDLEIE | Line is idle
USART_PARITY_ERROR | USART_CR1_PEIE | Parity error
USART_CLEAR_TO_SEND | USART_CR3_CTSIE | CTS interrupt
USART_DMAR_ERROR | USART_CR3_EIE | Overrun, noise or framing error (DMAR=1)

*LIN interrupts not implemented.*

* void **clearCTS()**

Clears the CTS interrupt flag.

* int16_t **checkError()**
* uint16_t **checkIdle()**

Check the error/idle status. `checkError()` returns any of the following error values or possibly a sum of them; `checkIdle()` returns only Idle status:

macro | value | description
--|--|--
USART_SR_ORE | 8 | Overrun error
USART_SR_NE | 4 | Noise error
USART_SR_FE | 2 | Framing error
USART_SR_PE | 1 | Parity error
USART_SR_IDLE | 16 | Line idle

_Note: use `readDR()**` after getting an error code to clear the error/idle bit in SR. Use `getByte()**` to clear the Parity Error bit, as it waits for RXNE before reading DR._

* uint16_t **readDR()**

Reads DR register to clear any error bits and/or to dump the RX contents.

## usart_mem class

The `usart_mem` class can be used to store the output text 'stream' in a byte array in RAM. An object of the `usart_mem` class supports most of the `print` and `get` member functions and overloaded operators of a 'normal' `usart` class (except the C++ string ones). It can be used to convert numbers to text, for example.

The constructor takes one argument - the size of the array in bytes, e.g. **usart_mem** foo(256);

The **init(uint8_t\* dat)** function binds the `usart_mem` object to an array `dat`. Note that while this array holds text, it must be of `byte` aka `uint8_t` type.

The array is used as a circular buffer, once its end is reached, new output will start overwriting bytes from the beginning. `usart_mem` can store ASCII control characters (like `\r` and `\n`) to allow text formatting. A special `\e` (escape, 27) character can be used to mark the end of text and return the 'carriage' to the start of the array (new data will overwrite the existing one).

## Setup member functions

* void **RXenable()**
* void **RXdisable()**

Enable/disable RX. If RX is disabled, the corresponding pin is free for other uses.

* void **TXenable()**
* void **TXdisable()**

Enable/disable TX. If TX is disabled, the corresponding pin is free for other uses.

* void **CLKenable(uint8_t cpol = 0, uint8_t cpha = 0, uint8_t lbcl = 0)**
* void **CLKdisable()**

Enavle/disable CK (clock) pin. Default values set this pin up as *low when idle*, *first transition is the first data edge* and *clock pulse of the last data is not output*. This can be changed by providing optional `cpol`, `cpha` and `lbcl` arguments respectfully (set them to 1 to change).

* void **RTSenable()**
* void **RTSdisable()**
* void **CTSenable()**
* void **CTSdisable()**

Enable/disable hardware flow control (RTS and CTS pins).

* void **HDenable()**
* void **HDdisable()**

Enable/disable Half-duplex mode.

* void **DMARXenable()**
* void **DMARXdisable()**
* void **DMATXenable()**
* void **DMATXdisable()**

Enable/disable DMA mode for reception and transmission. Higher-level DMA functions above use these, so there's no need to enable TX to `startTX()`, for example.

* void **parityEnable(uint8_t ps)**
* void **parityDisable()**

Enable/disable parity control. The `ps` value sets the parity: `0 == even; 1 == odd`. Note that parity control requires 9-bit word length to work correctly.

* void **wordLength(uint8_t M)**

Sets the word length: 8 data bits (`M == 0`, default) or 9 data bits (`M == 1`).

* void **sendBreak()**

Sends a break character.

* void **stopBits(uint8_t stp)**

Program the stop bits. `stp` values are:
`stp` | stop bits
--|--
0 | 1 Stop bit
1 | 0.5 Stop bit
2 | 2 Stop bits
3 | 1.5 Stop bit


## Defined values and compiler directives

`stm32f103_usart_func.h` file contains a number of `#defines` at the start that may be changed according to the current project setup.

`#define APB2SPEED 72000000`
`#define APB1SPEED 36000000`

Define the APB1 and APB2 speeds. If you changed the system clock frequency, change these values accordingly.

`#define USE_BUFFER_FOR_INTS`

When converting 32-bit and smaller integer values to text, the library uses inline assembler and the stack to order the characters. This *may* lead to problems in interrupt-rich environment. If needed, uncomment this macro to enable the 'classic' integer-to-text conversion using a buffer array.

`#define NAN_INFINITY_ENABLED`

Uncomment this macro to enable the correct output for IEEE 754 `NaN` (not a number) and infinite floating numbers. Disabled by default to reduce the code size. If disabled, &infin; won't be formatted (i.e. it won't truncate to 2 decimal digits).

## Examples

Example programs suppose you use some terminal software on the connected computer (I'm using [CoolTerm](https://freeware.the-meiers.org/). Also, unless you can somehow connect directly to the COM port, a USART-USB converter is needed (in my case it's a CP210x module).

### USART Hello World

A basic example printing 'Hello World!' every half-second and counting the lines. Timers library included for the delay function.

```cpp
#include <stm32f103_usart_func.h>
#include <stm32f103_timers_func.h>

usart3 term; //create a USART3 object; TX pin B10
uint16_t cnt;

int main()
{
	term.init(9600) //set baud rate
	term << "Starting...\r\n";

	while (1)
	{
		term << ++cnt <<": Hello world!\r\n";
		delay_ms(500) //wait half a second
	}
}

```

### USART Two numbers sum

In this example two numbers (doubles) are requested, then their sum is printed, and then reprinted with 10 mantissa digits instead of 2. Here, the floating point decay can be seen, as the USART library prints truncated values; hence the 'long version' that illustrates it. Check -100 and 0.01 as an example.

```cpp
#include <stm32f103_usart_func.h>

usart2 term; //USART2, TX is PA2, RX is PA3
double a, b;

int main()
{
	term.init(9600) //setup baud rate
	term << "Starting...\r\n";

	while (1)
	{
		term << "Enter two numbers: " >> a >> b <<"\r\n"
				<<"entered: "<< a << " and "<< b <<"\r\n"
				<<"The sum is: " << a + b << "\r\n";
		term << "And the long version is: ";
		term.printFloat(a+b, 10) //print the double with 10 decimals
		term << "\r\n";
	}
}
```

### USART Data stream

This program requests a text file from the user, copies it into an array, then sends the contents of this array back. Note: the size in `filesize` must be exact. The current value corresponds to the size of this demo program. Also note that this example uses high baud rate and the alternative pinout for USART1.

```cpp
#include <stm32f103_usart_func.h>

usart1 term; //USART1, alt pinout, TX is PB6, RX is PB7
uint8_t txt[4000];
char k; //a char buffer for 'press any key'
uint16_t filesize = 1085; //the size must be exact!

int main()
{
	term.init(115200, 1) //setup baud rate and alt pinout

	while(1)
	{
		term << "Send us some file!\r\n";
		term.getStream(txt, filesize)

		term << "Received. Let's see what we've got:\r\n";
		term.sendStream(txt, filesize)

		term << "\r\nPress any key... " >> k << "ok!\r\n";
	}
}
```



