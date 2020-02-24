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

## Classes and their member functions

###Analog Pin Class

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

###Analog Continuous Class

Up to two pins (ADC1 _and_ ADC2) can be set up as *Analog Continuous* objects providing real-time continuous conversions on selected channels. Additional channels can be used in injected mode. The continuous mode uses its ADC peripheral fully, so no other `analog` object can be set up on the same ADC.

Constructor:

* **analog_cont (uint8_t adc, uint8_t cha)**

Initializes an object and binds it to the ADC #`adc` and the channel `cha`. `adc` can be 1 or 2 and represents ADC1 and ADC2 respectfully.

* void **init (uint8_t cycles = 0)**

Initializes and calibrates the bound ADC using `adcX_init()`. Optional `cycles` argument sets the sample time (see the table in *Analog Pin Class*).

* void **start ()**

Starts the continuous conversion of the selected channel. The data register will be updated in real time.

* void **stop ()**

Stops the continuous conversion.

* uint16_t **read ()**

Returns the current conversion result. An overloaded **=** operator can also be used for the same purpose (i.e. `uint16_t res = analog_cont_object;`).

*For the injected functions list check the Injected channels section below*


###Analog Scan Class

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

will make the `analog_data` object write conversion data into the `arr` array, while checking channels 1,2 and 3 twice during a single scan, and channels 4 and 5 once.

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

Regular channels of the *Analog Scan* class object can start convertion on an external trigger (a certain event). External triggers allow avoiding the continuous scanning that consumes power and DMA resources, requesting ADC data at timed intervals instead. For example, using a atimer event as an external trigger you can make scans happen every second.

* void **external (uint8_t regtrig)**

Makes triggering of the object's analog data convertion dependant on the external trigger instead of the ADON bit that forces it manually.

The `regtrig` values are:

value | name 
--|--
0 | Timer 1 CC1 event
1 | Timer 1 CC2 event
2 | Timer 1 CC3 event
3 | Timer **2** CC2 event
4 | Timer **3** TRGO event
5 | Timer **4** CC4 event
6 | EXTI line 11
7 | SWSTART bit in the ADC_CR2 register

When an external event occurs, it will force a single conversion, the results will be stored in the `targ` array provided during initialization.

* void **externalStart ()**

If `regtrig` in the previuous function call was `7`, this function will start a continuous conversion (same as `start()`, but using the SWSTART bit instead of the ADON bit). This continuous conversion can be stopped with `stop()`.

* void **externalRead ()**

If the external trigger is set to `7` (SWSTART), this will force a single conversion (same as `read()`, but using the SWSTART bit instead of the ADON bit).

### Injected channels

Injected channels are available for *Analog Continuous* and *Analog Scan* objects of the ADC library. Injected channels are triggered by external events only (these include a software trigger, too), are injected into the normal scan/continuous routine immediately after the external event happens and store the conversion results in four dedicated registers. Injected channels are available for both ADC1 and ADC2.

* void **injectInit ([uint8_t jtrigger = 7])**

Enables injection on an external event and binds it to an external trigger `jtrigger` (software trigger JSWSTART by default).

`jtrigger` values are:

value | name 
--|--
0 | Timer 1 TRGO event
1 | Timer 1 CC4 event
2 |  Timer **2** TRGO event
3 |  Timer **2** CC1 event
4 |  Timer **3** CC4 event
5 |  Timer **4** TRGO event
6 |  EXTI line15
7 |  JSWSTART bit in the ADC_CR2 register

* void **injectAuto ()**

Alternatively, injected channels can be auto-converted after the regular channels group with `injectAuto()` function. In this case, external trigger is disables and injected channels output registers will get updated after any regular conversion (single or continuous).

* void **injectTriggered ()**

Disables auto-injection and enables the external trigger mode.

* void **inject (uint8_t cha1)**
* void **inject (uint8_t cha1, uint8_t cha2)**
* void **inject (uint8_t cha1, uint8_t cha2, uint8_t cha3)**
* void **inject (uint8_t cha1, uint8_t cha2, uint8_t cha3, uint8_t cha4)**

Setup injection of 1, 2, 3 or 4 channels `chaX`. The conversion results will end up in 1st, 2nd, 3rd and 4th injected data registers to be read by `injectRead()`.

* void **injectStart (uint_fast8_t dowait = 1)**

Start manual injection in software (JSWSTART, `jtrigger == 7`) mode. The `dowait` argument tells the function to wait for the end of conversion and is `1` by default. A `0` here will return back to the main program right after setting the JSWSTART bit, but the convertion results won't be available immediately.

* void **injectClear ()**

Clear the Injected Channel End of Conversion bit in the Status Register (for IRQ routines).

* uint16_t **injectRead (uint_fast8_t jcha)**

Read the value from the injected channel `jcha` data register.

## Non-member ADC functions

### Initializing

* void **adc1_init ()**
* void **adc2_init ()**

Enables the corresponding ADC clock, waits for the corresponding ADC to power up and calibrates it. If the ADC is already up and running, quits immediately. All the classes above incorporate the corresponding `adc_init()` function in their `init()` member functions, there's no need to call these explicitly.

* void **adc_temperature ()**

Enable temperature sensor and V<sub>REFINT</sub> (ADC1 channels 16 and 17).

* void **adc_dualMode (uint8_t dmode)**

Enable Dual Mode. Please check the ST RM0008 reference manual for details on values and modes.

### Analog watchdog

Analog watchdogs allow events and interrupts to happen if the ADC data register values are above or below certain thresholds. Note that watchdogs can not start the conversion and deal with data registers only; thus they're not included in any of the classes above and must be set up separately. Watchdogs can monitor either all the channels of an ADC peripheral or only one of the channels of an ADC peripheral.

Functions listed below deal with ADC1, ADC2 has the same number of functions called `adc2_*****()`.

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

Same functions with no argument disable the corresponding watchdog.

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