# GPIO Library

## Higher abstraction level, classes

### Constructors

There are three constructors for the class gpioX:
* `gpioX()` creates a generic gpioX object. Can be used with functions governing the whole GPIO port, i.e. `init()`, `setAll(val)`, `resetAll(val)`, `readAll()`. Can also be used to declare an array of gpioX_pin objects as in `gpioA portA[16];`; each variable of this array will be representing a corresponding pin (e.g. `portA[3]` == PA3). _Note: each `gpioX()` constructor call will increment the pin it's representing, thus the first object created with `gpioX()` will be pin0, the second pin1, etc._

* `gpioX_pin(pin_num)` creates an object for a particular GPIOX pin #pin_num.

* `gpioX_pin(pin_num, mode [,cnf])` creates a pin #pin_num object and initialises it to values `mode` and `cnf`; can be used only inside functions. For `mode` and `cnf` values see `mode` member function below.

_`gpioX_pin` is an alias for `gpioX` for better readability, it refers to the same class._

Examples:
```c++
//global scope
gpioB portB; //declares an object for the GPIOB
gpioA portA[16]; //declares an array of all 16 GPIOA pins
gpioB_pin pinB12(12); //declares an object for a specific pin

//inside main()
gpioB_pin pinB3(3, OUTPUT, PUSHPULL); //declares a local object and sets up a specific pin

void debugLed()
{
    gpioC_init();
    gpioC_pin pinC13(13, OUTPUT, OPENDRAIN);
}
```
### Public variables and functions
* `uint8_t pin` the # of the GPIOX pin the object operates on
* `void init()` enables the corresponding GPIO clock; can be called from any `gpioX` or `gpioX_pin` object
* `static void init(gpio_config conf)` enables the GPIO clock and sets the control registers according to the provided `gpio_config` (see below)
* `void mode(mode [,cnf])` sets the pin operating mode. Possible values:

|mode|cnf|result|
|---|---|---|
|INPUT| |Default CNF: Floating input|
|INPUT|FLOATING|Floating input|
|INPUT|PULLUP|Input with pullup|
|INPUT|PULLDOWN|Input with pulldown|
|OUTPUT|  |Default CNF: Open-drain otput, default speed 2MHz|
|OUTPUT|OPENDRAIN|Open-drain output, default speed 2MHz|
|OUTPUT|PUSHPULL|Push-pull output, default speed 2MHz|
|OUTPUT2MHZ|_(any)_|Output speed 2MHz|
|OUTPUT10MHZ|_(any)_|Output speed 10MHz|
|OUTPUT50MHZ|_(any)_|Output speed 50MHz|

_Note that it is not possible to set Alternate Functions or Analog mode with the class object; this should be done by the corresponding peripheral libraries._

* `void set()` sets the OUTPUT pin
* `void high()` sets the OUTPUT pin (same as above)
* `void reset()` resets the OUTPUT pin
* `void low()` resets the OUTPUT pin (same as above)
* `void invert()` inverts the output of the pin
* `uint8_t read()` reads the INPUT pin, returns 1 or 0
* `void write(uint8_t val)` sets the OUTPUT pin to `val`, i.e. 0 or 1.
* `void setAll(uint32_t val)` writes `val` into the BSRR register (see STM32f103x reference manual).
* `void resetAll(uint32_t val)` writes `val` into the BRR register.
* `uint32_t readAll()` reads the contents of the IDR register.

* `void exti(uint8_t crbits)` sets the pin as a source for external interrupt/event. The following values can be used in the `crbits` argument:

macro name | value | meaning
---|---|---
EXTI_EVENT |		0x01 | EXTI event enabled
EXTI_IRQ |	0x02 | EXTI interrupt enabled
EXTI_RISING	|	0x04 | Rising edge on the EXTI line acts as a trigger
EXTI_FALLING	| 0x08 | Falling edge on the EXTI line acts as a trigger

Any number of these values can be or-ed or added as an argument for `exti()`. In addition, the following combined macros can be used: EXTI_IRQ_RISING, EXTI_IRQ_FALLING, EXTI_EVENT_RISING and EXTI_EVENT_FALLING.

* `uint8_t pending()` Checks the EXTI pending bit, returns 1 or 0.
* `void clear()` Clears the EXTI pending bit.
* `void interrupt()` Call the EXTI interrupt.

* `static void disableAll()` sets all pins to analog mode (clock disabled).
* `static void disablePins(uint16_t pins)` sets selected pins to analog mode. `pins` argument is a bitmask, with MSB being pin 15 and LSB pin 0. `1` in this mask means the pin is turned off (analog mode).
* `static gpio_config saveConfig()` saves the current pin configuration into a `gpio_config` object.
* `static void setConfig(gpio_config conf)` sets all pins to the setup provided in the `gpio_config` object.

### Configuration class

The library provides the `gpioX_config` class (X corresponds to the GPIO) that holds the pin configuration in three member variables: `crl`, `crh` and `odr`. A variable of the `gpioX_config` class can be used to set up the GPIO and save its current setup. It is used in the static member functions above.

*Note: `gpio_config` can also be used to set up GPIO quickly with an `init` member function, see above.*

### Type conversions

`gpioX_pin` class provides conversion to and from `uint8_t`, or `bool` type. Thus

* `uint8_t a = PA11` returns `1` if the input on `gpioX_pin` PA11 is high and `0` otherwise;
* `PA11 = a` sets output `gpioX_pin` A11 high if `a>0` and low otherwise.

The following examples turn the LED on pin A11 on when the button on pin A10 is pressed:

```c++
gpioA_pin A10(10);
gpioA_pin A11(11);

int main()
{
	gpioA_init();
	A10.mode(INPUT, PULLUP);
	A11.mode(OUTPUT);
	while(1) {A11 = (uint8_t)A10;} //explicit type conversion
}
```
or, using `if`:
```c++
int main()
{
	gpioA_init();
	A10.mode(INPUT, PULLUP);
	A11.mode(OUTPUT);
	while(1) {if (A10) A11.high(); else A11.low();}
}
```

## Lower abstraction level inline functions

`void gpioX_init()` - enables the GPIOX clock.

The following are machine-generated.

_X is A, B or C for GPIOA, GPIOB and GPIOC_; _N is the pin number, 0..15_; _PU = Pull Up_; _PD = Pull Down_; _OD = Open Drain_; _PP = Push Pull_; _AF = Alternate Function_; _2, 10 and 50 is the speed in MHz_.

```c++
//modes
 void pinXN_Input() //floating
 void pinXN_Input_PU()
 void pinXN_Input_PD()
 void pinXN_Analog()
 void pinXN_Output() //default push-pull 2MHz
 void pinXN_Output_OD() //default 2MHz
 void pinXN_Output_PP_2()
 void pinXN_Output_PP_10()
 void pinXN_Output_PP_50()
 void pinXN_Output_OD_2()
 void pinXN_Output_OD_10()
 void pinXN_Output_OD_50()
 void pinXN_Output_AFPP_2()
 void pinXN_Output_AFPP_10()
 void pinXN_Output_AFPP_50()
 void pinXN_Output_AFOD_2()
 void pinXN_Output_AFOD_10()
 void pinXN_Output_AFOD_50()

//actions
 uint8_t readPinXN()
 void setPinXN()
 void resetPinXN()
