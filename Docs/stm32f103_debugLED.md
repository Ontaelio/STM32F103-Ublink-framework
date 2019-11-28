# DebugLED library

---

The DebugLED library provides the means to turn on the LED on PC13 pin (the built-in pin on the Blue Pill). No GPIO initialization is required*; the `debugLED()` function can be dropped anywhere in the code to find the place the program misbehaves. The following inline functions are present:

* void **debugLED()**

Lights up the LED.

* void **debugLEDoff()**

Shuts the LED.

* void **setDebugLED()**

Exactly the same as `debugLED()`. Don't ask.

----
&ast; `stm32f103_gpio_reg.h` still needs to be present though.
