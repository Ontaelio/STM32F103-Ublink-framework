# GPIO Func

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

_Note that it is not possible to set Alternate Functions or Analog mode with the class object; this should be done by the corresponding periphery libraries._

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

The following variables are commented out in the source code because they produce warnings from the compiler, although they _do_ work:

* `volatile uint32_t* BRR` points at the BRR register.
* `volatile uint32_t* BSRR` points at the BSRR register.
* `volatile uint32_t* IDR` points at the IDR register.


## Lower abstraction level inline functions

`void gpioX_init()` - enables the GPIOX clock.

The following were machine-generated.

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
