# ADC (Analog to digital) library

The ADC library provides basic and extended functions to run the analog-to-digital conversion. Three classes deal with single, continuous and scan modes of operation.

[Analog Pin Class](#analog-pin-class)
[Analog Continuous Class](#analog-continuous-class)
[Analog Scan Class](#analog-scan-class)
[External triggers on regular channels](#external-triggers-on-regular-channels)
[Injected channels](#injected-channels)
[Non-member initialization](#non-member-adc-functions)
[Analog watchdog](#analog-watchdog)
[Interrupts and events](#interrupts-and-events)
[Examples](#examples)

## Classes and their member functions

### Analog Pin Class

This is the most basic class of the ADC library. It provides simple 'Arduino-style' functions to read ADC-compatible pins manually, one by one. Each class object represents a single pin to be read. This class utilizes ADC2, as this peripheral is not DMA-empowered, thus *Analog Pins* can be used at the same time as *Analog Continuous* (on ADC1) and *Analog Scan* objects.

Constructor:
* **analog_pin (uint8_t cha)**

Initializes an object and binds it to the ADC channel `cha`. There are 10 external ADC channels on the STM32F103 (Blue Pill) on pins A0 .. A7, B0 and B1 (channels 0..9 respectfully). Other channels (10..17) are either used on bigger chip packages, or connect internal peripherals (internal temperature sensor == channel 16, and reference voltage == channel 17; must be enabled before use).

* void **init ([uint8_t cycles = 0])**

Initializes and calibrates ADC2 using `adc2_init()` (see below). Optional `cycles` argument sets the sample time (conversion speed):

`cycles` value | actual ADC sample cycles
--|--
0 | 1.5 cycles
1 | 7.5 cycles
2 | 13.5 cycles
3 | 28.5 cycles
4 | 41.5 cycles
5 | 55.5 cycles
6 | 71.5 cycles
7 | 239.5 cycles

Default `cycles` value is 0.

* uint16_t **read ()**

Starts a single conversion, waits for the End of Conversion (EOC) flag to set, then returns the conversion result.

* **overloaded type conversion**

 *Analog Pin* class is overloaded into `uint16_t` type and can be used as a right-hand operand as any normal `uint16_t` unsigned integer, e.g. `uint16_t res = analog_pin_object;`. Check the code [example](#analog-pin-adc-blink) below.

###Analog Continuous Class

Up to two pins (ADC1 _and_ ADC2) can be set up as *Analog Continuous* objects providing real-time continuous conversions on selected channels. Additional channels can be used in injected mode. The continuous mode uses its ADC peripheral fully, so no other `analog` object can be set up on the same ADC.

Constructor:

* **analog_cont (uint8_t adc, uint8_t cha)**

Initializes an object and binds it to the ADC #`adc` and the channel `cha`. `adc` can be 1 or 2 and represents ADC1 or ADC2 respectfully.

* void **init (uint8_t cycles = 0)**

Initializes and calibrates the bound ADC using `adcX_init()`. Optional `cycles` argument sets the sample time (see the table in *Analog Pin Class*).

* void **start ()**

Starts the continuous conversion of the selected channel. The data register will be updated in real-time.

* void **stop ()**

Stops the continuous conversion.

* uint16_t **read ()**

Returns the current conversion result.

* **overloaded type conversion**

 *Analog Continuous* class is overloaded into `uint16_t` type and can be used as a right-hand operand as any normal `uint16_t` unsigned integer, e.g. `uint16_t res = analog_cont_object;`.

*For the injected functions list check the Injected channels section below*


### Analog Scan Class

*Analog Scan* object reads multiple (up to 16) ADC channels in sequence and saves the conversion results in a user-provided array of unsigned ints (uint16_t). The scan can work in single bursts or continuously. *Analog Scan* object utilizes DMA and works only with ADC1, as DMA is not available on ADC2. Thus only one *Analog Scan* object should be used in a program.

*Note: technically, ADC2 can be read by DMA in Dual Mode, but this mode implementation is rudimentary in this library for simplicity reasons.*

Constructor:

* **analog_scan**

Initializes the object. No arguments.

* void **init (uint16_t\* targ, uint_fast8_t num, ...)**

Initializes DMA1 and binds it via DMA channel 1 to an array at `targ` (where `targ` is a pointer to an array). `num` is the number of channels to scan, and the channels' numbers themselves follow (up to 16, channels can repeat). Thus:

```c++
uint16_t arr[8];
analog_scan analog_data;
void main(){
	analog_data.init(arr, 8, 1,2,3,1,2,3,4,5);
}
```

will make the `analog_data` object write conversion data into the `arr` array while checking channels 1,2 and 3 twice during a single scan, and channels 4 and 5 once.

* void **start ()**

Starts the continuous conversion. The array `targ` declared in the `init` function will hold the real-time data from the analog inputs provided.

* void **stop ()**

Stops the continuous conversion.

* void **read ()**

Does a single conversion (non-continuous mode) and stores the data in the `targ` array.

* void **speed (uint8_t cha, uint8_t cycles)**

Sets up the sample time on a single channel `cha` (see the table in *Analog Pin Class*).

* void **priority (uint8_t pri)**

Sets the DMA priority level (`pri` is 0..3, where 0 == low, 3 == very high).

*For the external triggers and injected functions check sections below*

### External triggers on regular channels

Regular channels of the *Analog Scan* class object can start a conversion on an external trigger (a certain event). External triggers allow avoiding the continuous scanning that consumes power and DMA resources, requesting ADC data at timed intervals instead. For example, using a timer event as an external trigger you can make scans happen every second.

* void **external (uint8_t regtrig)**

Makes triggering of the object's analog data conversion dependant on the external trigger instead of the ADON bit that forces it manually.

The `regtrig` values are:

value | macro | event
--|--|--
0 | ADC_EXT_T1CC1 | Timer 1 CC1 event
1 | ADC_EXT_T1CC2 | Timer 1 CC2 event
2 | ADC_EXT_T1CC3 | Timer 1 CC3 event
3 | ADC_EXT_T2CC2 | Timer **2** CC2 event
4 | ADC_EXT_T3TRGO | Timer **3** TRGO event
5 | ADC_EXT_T4CC4 | Timer **4** CC4 event
6 | ADC_EXT_EXTI11 | EXTI line 11
7 | ADC_EXT_SW | SWSTART bit in the ADC_CR2 register

When an external event occurs, it will force a single conversion, the results will be stored in the `targ` array provided during initialization.

* void **externalStart ()**

If `regtrig` in the previous function call was `7`, this function will start a continuous conversion (same as `start()`, but using the SWSTART bit instead of the ADON bit). This continuous conversion can be stopped with `stop()`.

* void **externalRead ()**

If the external trigger is set to `7` (SWSTART), this will force a single conversion (same as `read()`, but using the SWSTART bit instead of the ADON bit).

### Injected channels

Injected channels are available for *Analog Continuous* and *Analog Scan* objects of the ADC library. Injected channels are triggered by external events only (these include a software trigger, too), are injected into the normal scan/continuous routine immediately after the external event happens and store the conversion results in four dedicated registers. Injected channels are available for both ADC1 and ADC2.

* void **injectInit ([uint8_t jtrigger = 7])**

Enables injection on an external event and binds it to an external trigger `jtrigger` (software trigger JSWSTART by default).

`jtrigger` values are:

value | macro | event
--|--|--
0 | ADC_JEXT_T1TRGO | Timer 1 TRGO event
1 | ADC_JEXT_T1CC4 | Timer 1 CC4 event
2 | ADC_JEXT_T2TRGO | Timer **2** TRGO event
3 | ADC_JEXT_T2CC1 | Timer **2** CC1 event
4 | ADC_JEXT_T3CC4 | Timer **3** CC4 event
5 | ADC_JEXT_T4TRGO | Timer **4** TRGO event
6 | ADC_JEXT_EXTI15 | EXTI line15
7 | ADC_JEXT_SW | JSWSTART bit in the ADC_CR2 register

* void **injectAuto ()**

Alternatively, injected channels can be auto-converted after the regular channels group with the `injectAuto()` function. In this case, the external trigger is disabled and injected channels output registers will get updated after any regular conversion (single or continuous).

* void **injectTriggered ()**

Disables auto-injection and enables the external trigger mode.

* void **inject (uint8_t cha1)**
* void **inject (uint8_t cha1, uint8_t cha2)**
* void **inject (uint8_t cha1, uint8_t cha2, uint8_t cha3)**
* void **inject (uint8_t cha1, uint8_t cha2, uint8_t cha3, uint8_t cha4)**

Setup injection of 1, 2, 3 or 4 channels `chaX`. The conversion results will end up in 1st, 2nd, 3rd, and 4th injected data registers to be read by `injectRead()`.

* void **injectStart (uint_fast8_t dowait = 1)**

Start manual injection in software (JSWSTART, `jtrigger == 7`) mode. The `dowait` argument tells the function to wait for the end of a conversion and is `1` by default. A `0` here will return to the main program right after setting the JSWSTART bit, but the conversion results won't be available immediately.

* void **injectClear ()**

Clear the Injected Channel End of Conversion bit in the Status Register (for IRQ routines).

* uint16_t **injectRead (uint_fast8_t jcha)**

Read the value from the injected channel `jcha` data register.

## Non-member ADC functions

### Initializing

* void **adc1_init ()**
* void **adc2_init ()**

Enables the corresponding ADC clock, waits for the corresponding ADC to power up and calibrates it. If the ADC is already up and running, quits immediately. All the classes above incorporate the corresponding `adc_init()` function in their `init()` member functions, there's no need to call these explicitly.

*Note: analog conversions don't require the clock of the GPIO port running. Thus both `inits` don't enable it and don't do anything with the GPIO peripheral at all, the same applies to classes' `inits`. If you use pins of the same GPIO as the analog pins in some other capacity, it's a good practice to enable `Analog` mode on the ones that work as ADC inputs (the default `Input` mode also works, but consumes power). You may use inline functions `pinA0_Analog()` and similar for A1..A7, B0 and B1 to enable the `Analog` mode on needed pins.*

* void **adc_temperature ()**

Enable temperature sensor and V<sub>REFINT</sub> (ADC1 channels 16 and 17).

* void **adc_dualMode (uint8_t dmode)**

Enable Dual Mode. Please check the ST RM0008 reference manual for details on values and modes.

### Analog watchdog

Analog watchdogs allow events and interrupts to happen if the ADC data register values are above or below certain thresholds. Note that watchdogs can not start the conversion and deal with data registers only; thus they are not included in any of the classes above and must be set up separately. Watchdogs can monitor either all the channels of an ADC peripheral or only one of the channels of an ADC peripheral.

* void **adc1_watchdog (uint32_t low, uint32_t high)**
* void **adc2_watchdog (uint32_t low, uint32_t high)**

Enables the watchdog on **all regular** channels of the ADC with low and high thresholds set at `low` and `high` respectfully.

* void **adc1_injectWatchdog (uint32_t low, uint32_t high)**
* void **adc2_injectWatchdog (uint32_t low, uint32_t high)**

Same for **all injected** channels on the specified ADC.

* void **adc1_watchdog (uint8_t cha, uint32_t low, uint32_t high)**
* void **adc2_watchdog (uint8_t cha, uint32_t low, uint32_t high)**

Enables the watchdog on a **single regular** channel `cha` of the ADC; thresholds are set to `low` and `high`.

* void **adc1_injectWatchdog (uint8_t cha, uint32_t low, uint32_t high)**
* void **adc2_injectWatchdog (uint8_t cha, uint32_t low, uint32_t high)**

Same for a **single injected** channel `cha` on the specified ADC.

* void **adc1_watchdog ()**
* void **adc1_injectWatchdog ()**
* void **adc2_watchdog ()**
* void **adc2_injectWatchdog ()**

The same functions with no argument disable the corresponding watchdog.

* void **adc1_watchdogLow (uint32_t low)**
* void **adc2_watchdogLow (uint32_t low)**

Sets the low threshold.

* void **adc1_watchdogHigh (uint32_t high)**
* void **adc2_watchdogHigh (uint32_t high)**

Sets the high threshold.

* void **adc1_watchdogLowHigh (uint32_t low, uint32_t high)**
* void **adc2_watchdogLowHigh (uint32_t low, uint32_t high)**

Sets the `low` and `high` thresholds.

### Interrupts and events

While STM provides four selectable interrupts for each ADC, the ARM architecture physically supports only *one* IRQ for both peripherals: `ADC1_2_IRQHandler()`. Thus, if you have multiple interrupt requests enabled, you must make sure to check what exactly caused the interrupt routine to happen by reading the status bits.

* void **adc_IRQenable ()**
* void **adc_IRQdisable ()**

Enable/disable the global (ARM) ADC interrupt.

* void **adc1_WDinterrupt (uint8_t bit)**
* void **adc1_EOCintterrupt (uint8_t bit)**
* void **adc1_JEOCinterrupt (uint8_t bit)**
* void **adc2_WDinterrupt (uint8_t bit)**
* void **adc2_EOCintterrupt (uint8_t bit)**
* void **adc2_JEOCinterrupt (uint8_t bit)**

Enable (`bit == 1`) or disable (`bit == 0`) the corresponding interrupt on a selected ADC: Watchdog (WD), End of Conversion (EOC) or Injected End of Conversion (JEOC).

* uint8_t **adc1_Start ()**
* uint8_t **adc1_JStart ()**
* uint8_t **adc1_JEOC ()**
* uint8_t **adc1_EOC ()**
* uint8_t **adc1_WD ()**
* uint8_t **adc2_Start ()**
* uint8_t **adc2_JStart ()**
* uint8_t **adc2_JEOC ()**
* uint8_t **adc2_EOC ()**
* uint8_t **adc2_WD ()**

Return the state of the corresponding status bit.

* void **adc1_clearStart ()**
* void **adc1_clearJStart ()**
* void **adc1_clearJEOC ()**
* void **adc1_clearEOC ()**
* void **adc1_clearWD ()**
* void **adc2_clearStart ()**
* void **adc2_clearJStart ()**
* void **adc2_clearJEOC ()**
* void **adc2_clearEOC ()**
* void **adc2_clearWD ()**

Clear the corresponding status bit after the event.

## Examples

*Note: objects are named after their corresponding pins in these examples for better understanding, but it is a bad practice for a working project. Name them after the devices connected, e.g. `pot1` or `ldr3`. This way, if you need to change the pins these devices are connected to later, you'll just change the numbers in object declarations, and the code will retain its readability.*

### Analog Pin: ADC Blink

This basic example turns the Blue Pill in-built LED at pin C13 on and off depending on the position of a potentiometer connected to pin A1.
```cpp
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
```

### Analog Continuous: ADC Cont PWM

In this example, the brightness of the Blue Pill in-built LED (C13) is controlled by two potentiometers connected to pins A3 and A4 by using software PWM. Turn both knobs all the way to 'off' position to turn off the LED completely.

Note that `(A3+A4)` is the same as `(A3.read() + A4.read())`. The timers library is needed for the delay to work.
```cpp
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
```

### Analog Scan: ADC Scan 4 pots

Four potentiometers are connected to pins A0 .. A3. If the sum of the readings on pins A2 and A3 is more than the sum of the readings on pins A0 and A1, the in-built Blue Pill LED (C13) lights up and goes dark otherwise.

```cpp
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
```

### Injected channels and external events: ADC Inject

Four potentiometers are connected to pins A0 .. A3. Two pots are scanned constantly, two are injected and scanned on external event from Timer1 every 5 seconds. The output goes to a serial console (TX is on pin B6, alternative pinout used).

```cpp
#include <stm32f103_usart_func.h>
#include <stm32f103_adc_func.h>
#include <stm32f103_gpio_func.h>
#include <stm32f103_timers_func.h>

analog_scan twoPots; //analog scan object
uint16_t arr[2]; // array for analog scan values
timer1 tim1(36000, 10000); //timer1 will update once in 5 seconds
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
		txtout << "Injected A2: " << twoPots.injectRead(1) 
			<< "; A3: " << twoPots.injectRead(2) << "\r\n";
		delay_ms(1000);
	}
}
```

### Watchdog: ADC Watchdog
Two potentiometers are connected to pins A2 and A3 (*Analog Continuous* objects). When A2 goes above the `wdhigh` value, the in-built led at C13 lights up. When it goes below the `wdlow` value, the led turns off. The `wdhigh` and `wdlow` values are set to mid-point initially. A3 is being constantly updated but does nothing else.

```cpp
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
```