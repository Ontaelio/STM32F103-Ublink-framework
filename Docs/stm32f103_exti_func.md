# EXTI library

EXTI stands for external event lines. These external events can be sourced by GPIO pins and certain other peripherals and can trigger interrupts or certain functions (e.g. injected ADC conversions).

There are 19 EXTI lines on STM32F103. Lines 0 to 15 correspond to GPIO pins: line 0 is triggered by pins PA0, PB0, PC0, etc.; line 1 is PA1, PB1, PC1, etc., ... , line 15 is PA15, PB15, PC15, etc. Line 16 is connected to PVD output, line 17 to RTC Alarm event and line 18 to USB Wakeup event.

The ARM Cortex M3 architecture provides the folowing EXTI interrupt requests (10 in total):
- separate IRQs for EXTI lines 0, 1, 2, 3 and 4;
- single common IRQ for EXTI lines 5 .. 9; 
- single common IRQ for EXTI lines 10 .. 15;
- separate IRQs for EXTI lines 16 (PVD), 17 (RTC_Alert) and 18 (USB_Wakeup).

This library provides both higher level interface with the `exti` class and lower level interface with direct setup/control functions.

## Exti class and member functions

An object of the `exti` class controls a single EXTI line. Constructor:

* **exti (uint8_t ch_num)**: creates an `exti` object and binds it to EXTI line `ch_num`.

Member functions:

* void **init (uint8_t crbits)**

Initializes the line and sets it up according to the `crbits`. The following values can be used in the `crbits` parameter:

macro name | value | meaning
---|---|---
EXTI_EVENT |		0x01 | EXTI event enabled
EXTI_INTERRUPT |	0x02 | EXTI interrupt enabled
EXTI_RISING	|	0x04 | Rising edge on the EXTI line acts as a trigger
EXTI_FALLING	| 0x08 | Falling edge on the EXTI line acts as a trigger

Any number of these values can be or-ed or added as an argument for `init()`. If both rising and falling edge triggers are enabled, the EXTI line will trigger an event/interrupt twice for each incoming signal.

If interrupt is enabled in `init()`, the corresponding bit in the ARM core will also be set.

* void **gpio(uint8_t gpio)**

Enables AFIO and sets the GPIO port of the EXTI pin. `gpio` is 0 for GPIOA, 1 for GPIOB, etc. Macro constants EXTI_GPIOA, EXTI_GPIOB, etc can be used too.

* void **reset()**

Resers all the control bits for the bound EXTI line; the line can be initialized again thereafter.

* uint8_t **check()**

Returns the 'pending' status of the EXTI line (`1` if the trigger request occured and `0` if not).

* void **clear()**

Clears the 'pending' bit.

* void **interrupt()**

Generates an interrupt request on the EXTI line.

## Lower level setup/control functions

* void **exti_eventenable(uint8_t channel)**
* void **exti_eventdisable(uint8_t channel)**

Enable/disable events on the EXTI line `channel`.

* void **exti_interruptenable(uint8_t channel)**
* void **exti_interruptdisable(uint8_t channel)**

Enable/disable interrupts on the EXTI line `channel`. Enable will also set a corresponding IRQ bit in the ARM core.

* void **exti_rising(uint8_t channel)**
* void **exti_risingdisable(uint8_t channel)**

Enable/disable rising edge trigger on the EXTI line `channel`.

* void **exti_falling(uint8_t channel**)
* void **exti_fallingdisable(uint8_t channel)**

Enable/disable falling edge trigger on the EXTI line `channel`.

* void **exti_interrupt(uint8_t channel)**

Generate an interrupt request on the EXTI line `channel`.

* uint8_t **exti_check(uint8_t channel)**

Return the 'pending' bit of the EXTI line `channel`.

* void **exti_clear(uint8_t channel)**

Clear the 'pending' bit of the EXTI line `channel`.
