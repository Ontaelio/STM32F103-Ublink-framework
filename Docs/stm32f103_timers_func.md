# Timer functions peripheral library

----

The timer_func library provides some basic means to deal with timers, PWMs and interrupts. This guide consists of the following sections:

[SysTick timer](#systick-timer) - dealing with the ARM core timer

[Timer initialization](#timer-initialization) - Timer init() function

[PWM pin class](#pwm-pin-class) - a simple way to create PWM pins

[Timer class](#timer-class) - more comprehensive timers and interrupts control class

----

## SysTick timer

#### SysTick defined symbolic names
Register addresses:

Register name | `#define`
-|-
SysTick Control and Status Register | `SYSTICK_CSR`
SysTick Reload Value Register | `SYSTICK_RVR`
SysTick Current Value Register | `SYSTICK_CURVAL`
SysTick Calibration Value Register | `SYSTICK_CALIB`

Register values: 
```c++
SYSTICK_CSR_COUNTFLAG	= 0x00010000
SYSTICK_CSR_CLKSOURCE	= 0x00000004
SYSTICK_CSR_TICKINT 	= 0x00000002
SYSTICK_CSR_ENABLE      = 0x00000001
```
#### SysTick functions

* void **delay_ms(uint32_t msecs)**

`msecs` ms delay, uses 'external' 9 MHz clock source.

* void **delay_us(uint32_t usecs)**

`usecs` μs delay, uses 'internal' HCLK clock source.

*Note: `delays` shouldn't be used along with the SysTick interrupt*

* void **sysTick_start(uint32_t val, uint8_t intext = 1)**

(Re)starts the SysTick timer counting from `val` to 0. `val` is 24-bit (0x00FFFFFF max). `intext` refers to clock source selection: 1 = HCLK (72 MHz); 0 = 'external' clock source (9 MHz); defaults to HCLK if omitted.

* void **sysTick_stop()**

Stops the SysTick timer.

* uint32_t **sysTick_read()**

Returns the current SysTick timer value.

* void **sysTick_intEnable()**

Enables SysTick interrupt.

* void **sysTick_intDisable()**

Disables SysTick interrupt.

----

## Timer initialization

* void **timerX_init()**

Enables the clocks for Timer X and AFIO.

----

## PWM pin class

The PWM class is a simple instrument to quickly set up PWM output pins Arduino-style. Each class object represents a single PWM output. If constant PWM outputs are exactly what's needed, this class is the best solution; for other cases a more complex TimerX class has it's own set of PWM functions.

Constructor:
* **timX_pwm(uint8_t ch_num)** *(X is the timer number, 1 .. 4)*

Declares an object of `timX_pwm` class using channel `ch_num` of timer X as PWM output. Check the microcontroller pinout to see which pin corresponds to which output. The table below provides some reference, but timer remapping is a bit more complicated than that (with partial and full remaps).

Timer channel | Default pin | Remap pin
--|--|--
Timer1 Channel 1 | PA8 |
Timer1 Channel 2 | PA9 |
Timer1 Channel 3 | PA10 |
Timer1 Channel 4 | PA11 |
Timer2 Channel 1 | PA0 | PA15
Timer2 Channel 2 | PA1 | PB3
Timer2 Channel 3 | PA2 | PB10
Timer2 Channel 4 | PA3 | PB11
Timer3 Channel 1 | PA6 | PB4
Timer3 Channel 2 | PA7 | PB5
Timer3 Channel 3 | PB0 | 
Timer3 Channel 4 | PB1 |
Timer4 Channel 1 | PB6 |
Timer4 Channel 2 | PB7 |
Timer4 Channel 3 | PB8 |
Timer4 Channel 4 | PB9 |

* void **init([uint8_t pushpull = 0])**

Initializes the SS pin and its GPIO port. If `pushpull` is non-zero, the pin will be configured as a push-pull output, else an open drain output (default). `init()` checks whether the timer outputs were remapped and adjusts accordingly. Timer1 complementary outputs not supported.

*Note: `init` doesn't initialize the timer, `timerX_init()` must be used.*

A `timX_pwm` class object has a number of variables that hold configuration values used to set up the PWM channel when it gets enabled. These variables are assigned with default values in the constructor and can be changed before enabling the PWM channel. These variables are:

variable | values | default
--|--|--
**pwmMode** | 1: PWM Mode 1 (active when CNT<CCR)<br>2: PWM Mode 2 (active when CNT>CCR)| 1
**centerMode** | Center Aligned mode selection<br>0: Edge-aligned mode<br>1, 2 or 3: Center-aligned aka Phase corect mode<br>(1, 2 and 3 have the same effect with PWM) | 0
**direction** | In edge-aligned mode:<br>0: upcounter, 1: downcounter | 0
**polarity** | 0: active high, 1: active low | 0
**prescaler** |Timer prescaler, 0 .. 0xFFFF | 0
**depth** | Timer reload value, 0 .. 0xFFFF | 0xFFFF

The rest of the configuration registers values are hard-coded into the PWM timer configuration.

* void **enable()**

Sets up the timer according to the provided values and enables the PWM output channel.

* void **disable()**

Disables the output of the PWM channel.

* void **write(uint16_t pwm_val)**

Sets the PWM output to the provided `value`. Can be used before `enable` to pre-set the compare value.

----

## Timer class

`timerX` objects hold all the settable register values and provide some rudimentary functions for the most common timer operations and register bits assigments. Multiple `timerX` objects with different configs for the same timer allow quick operation mode switching with `enable` member function.

The object has a number of `public` variables corresponding to the number of settable timer registers. These variables can be assigned with values (16-bit half words, except Timer1 DMAR register that is 32-bit); these values are written into the corresponding registers with `config` or `enable` member functions. The variables are named according to the registers they represent:

`CR1, CR2, SMCR, DIER, CCMR1, CCMR2, CCER, PSC, ARR, RCR, CCR1, CCR2, CCR3, CCR4, BDTR, DCR, DMAR` *(RCR and BDTR are Timer1 only)*

The call to constructor initializes all these variables to the corresponding register reset value (`0` for all except `ARR` that resets at `0xFFFF`). `ARR` (`depth`) and `PSC` (`prsclr`) values can be assigned in constructor.

#### Constructor

* **timerX([uint16_t prsclr = 0x0000, uint16_t depth = 0xFFFF])** *X is 1 .. 4*

Creates a `timerX` object and assigns default values to the internal register variables; prescaler and auto reload values may be provided here.

#### Timer control member functions

* void **init()**

Calls `timerX_init()`, initializing the timerX. Included for possible convenience.

* void **config()**

Assigns all the register variable values to the corresponding timer registers. Calls an update event (no interrupt generated) prior to writing CR1. Doesn't enable the timer, unless `CEN` bit was explicitly included in the `CR1` variable (not recommended).

* void **enableOnly()**

Enables the timer setting the `CEN` bit in CR1.

* void **disable()**

Enables the timer resetting the `CEN` bit in CR1.

* void **enable([uint16_t count = 0])**

Configures and enables the timer, optionally setting the CNT counter register to `count` and not the default value provided by the update event. In fact, this function calls the previous ones in the following order: `disable`, `config`, `enableOnly`.

* uint16_t **read()**

Returns the current counter value.

#### Setup member functions

All the setup functions set the internal class variables. They don't write anything into the actual registers; `config` or `enable` must be called after them.

* void **master(uint16_t mms [, uint16_t ccmr = 0])**

Sets up the master mode. `mms` corresponds to the three MMS bits of the CR2 register and may contain a value 0..7. The following defined constants may be used:

name | value | meaning
--|--|--
MMS_RESET |		0x0000 | Reset mode, slave controlled by the UG bit in EGR
MMS_ENABLE |		0x0001 | Enable mode, counter enable acts as the trigger
MMS_UPDATE	|	0x0002 | Update mode, update event is a trigger
MMS_COMPPULSE|	0x0003 | Compare Pulse mode, CC1IF flag is a trigger
MMS_COMP1	|	0x0004 | Compare 1, OC1REF acts as a trigger
MMS_COMP2	|	0x0005 | Compare 2, OC2REF acts as a trigger
MMS_COMP3	|	0x0006 | Compare 3, OC3REF acts as a trigger
MMS_COMP4	|0x0007 | Compare 4, OC4REF acts as a trigger

The optional `ccmr` argument sets up the Output compare mode (three OCXM bits of the CCMRX registers, values 1..7) for Compare modes 1-4. The following defines are provided:

name | value | meaning
--|--|--
OCM_FROZEN	|	0x0000 | Frozen, compare match has no effect on output
OCM_HIGH	|	0x0001 | Channel active on match
OCM_LOW		|	0x0002 | Channel inactive on match
OCM_TOGGLE	|	0x0003 | Toggle channel output on match
OCM_FORCELOW |	0x0004 | Force inactive level
OCM_FORCEHIGH |	0x0005 | Force active level
OCM_PWM1	|	0x0006 | PWM mode 1: active when CNT<CCR
OCM_PWM2	|	0x0007 | PWM mode 2: active when CNT>CCR

* void **slave(uint16_t sms, uint16_t ts)**

Sets up the slave mode. `sms` corresponds to the three SMS bits (0..7) and `ts` to the two TS bits (0..3) of the SMCR register. `ts` argument has an alternative set of values, see below.

`sms` defined constants:

name | value | meaning
--|--|--
SMS_DISABLE	|	0x0000 | Slave mode disabled
SMS_ENC1	|	0x0001 | Encoder mode 1
SMS_ENC2	|	0x0002 | Encoder mode 2
SMS_ENC3	|	0x0003 | Encoder mode 3
SMS_RESET	|	0x0004 | Reset mode
SMS_GATED	|	0x0005 | Gated mode
SMS_TRIGGER	|	0x0006 | Trigger mode
SMS_EXTCLK	|	0x0007 | External clock mode 1

`ts` has two sets of defines. First one:

name | value | meaning
--|--|--
TS_ITR0 |		0x0000 | Internal Trigger 0 (see below)
TS_ITR1	|		0x0001 | Internal Trigger 1 (see below)
TS_ITR2	|		0x0002 | Internal Trigger 2 (see below)
TS_ITR3	|		0x0003 | Internal Trigger 3 (see below)
TS_TI1F_ED	|	0x0004 | TI1 Edge Detector
TS_TI1FP1	|	0x0005 | Filtered Timer Input 1
TS_TI1FP2	|	0x0006 | Filtered Timer Input 2
TS_ETRF		|	0x0007 | External Trigger Input
8 can be added to these values to enable MSM.

The second alternative set of `ts` defines can be used for simple Internal Trigger 0..3 configuration (i.e. specifying the master timer name instead of the ITR value):

name | meaning
--|--
ITR_TIM1 | Timer1 is the master
ITR_TIM2 | Timer2 is the master
ITR_TIM3 | Timer3 is the master
ITR_TIM4 | Timer4 is the master

The library will provide the correct ITR value for the TS bits according to the slave/master timer configuration.

void **setMode(uint16_t mode)**

Sets the timer counting mode, i.e. CMS **and** DIR bits of CR1. The value of `mode` is 3-bit, 0..6, where LSB is the DIR bit. The following constants are defined:

name | value | meaning
--|--|--
CENTER_UP	| 0x0002 | Center-aligned mode 1, compare interrupt on upcount
CENTER_DOWN | 0x0004 | Center-aligned mode 2, compare interrupt on downcount
CENTER_BOTH | 0x0006 | Center-aligned mode 3, compare interrupt both up and down
PHASECORRECT | 0x0006 | Same as Center-aligned 3, Atmel term
UPCOUNTER	| 0x0000 | Edge-aligned mode, upcounter
DOWNCOUNTER	 | 0x0001 | Edge-aligned mode, downcounter

* void **setDepth(uint16_t val)**

Sets the timer auto-reload value (ARR).

* void **setPrescaler(uint16_t val)**

Sets the timer prescaler (PSC).

* void **setRepetitions(uint16_t val)**

*Timer1 only* Sets the repetitions counter (RCR). Note that while the register is 16-bit, only 8 bits are available, thus no more than 255 here.

* void **setCC1value(uint16_t val)**
* void **setCC2value(uint16_t val)**
* void **setCC3value(uint16_t val)**
* void **setCC4value(uint16_t val)**

Set the capture/compare value for channels 1..4 (CCRX).

* void **setUpdateIRQ([uint8_t bit=1])**
* void **setCC1IRQ([uint8_t bit=1]})**	
* void **setCC2IRQ([uint8_t bit=1])**	
* void **setCC3IRQ([uint8_t bit=1])**	
* void **setCC4IRQ([uint8_t bit=1])**	
* void **setCOMIRQ([uint8_t bit=1])** *Timer1 only*
* void **setTriggerIRQ([uint8_t bit=1])**
* void **setBreakIRQ([uint8_t bit=1])** *Timer1 only*

Set (1, default) or reset (0) the corresponding interrupt enable bits (DIER).

#### PWM control member functions

* void **pwmSetup(uint8_t center, uint8_t dir)**

Sets up PWM mode. `center` corresponds to the CMS bits in CR1; `dir` is the DIR bit. `center == 1` selects center-aligned mode, while `dir` selects the counter direction if `center` is zero. Sets the ARPE bit in CR1. This functions doesn't write into the actual register and is similar to the `setMode` function.

* void **pwmChannel(uint8_t ch_num, uint8_t mode, uint8_t plrty [, uint8_t pushpull = 0])**

Sets up the PWM channel `ch_num`. `mode` is the PWM mode (1 or 2), `plrty` is polarity (0 or 1). Optional `pushpull` argument, if set, will configure the output pin into the push-pull mode; defaul is open-drain. This function will initialize the output pin, but won't write anything into the timer registers.

* void **pwmWrite(uint8_t ch_num, uint16_t val)**

Outputs `val` on the PWM channel `ch_num`, writing it into the corresponding CCR register.

* void **pwmEnable(uint8_t ch_num)**

Enables the PWM channel output. This function writes both into the internal variable CCER and the timer CCER register (thus physically enabling the output).

* void **pwmDisable(uint8_t ch_num)**

Disables the PWM channel output. This function writes both into the internal variable CCER and the timer CCER register (thus physically disabling the output).

#### Direct register manipulation member functions

The following access the timer and/or ARM core registers directly without modifying the internal class variables.

* void **IRQenable()**
* void **IRQdisable()**

Enables/disables Timer IRQ for timers 2, 3 and 4 (ARM core). For timer1 this enables/disables the Update Interrupt (TIM1_UP).

*Timer 1 only:*
* void **IRQ_BRK_enable()**
* void **IRQ_UP_enable()**
* void **IRQ_TRG_COM_enable()**
* void **IRQ_CC_enable()**
* void **IRQ_BRK_disable()**
* void **IRQ_UP_disable()**
* void **IRQ_TRG_COM_disable()**
* void **IRQ_CC_disable()**

Enable/disable Timer1 interrupts in ARM core.

void **writeCC1(uint16_t val)**
void **writeCC2(uint16_t val)**
void **writeCC3(uint16_t val)**
void **writeCC4(uint16_t val)**

Write `val` into the CCRX register (capture/compare value).

*The following functions are atomic, i.e. they use bit-band aliases for maximum speed*

void **updateDisable()**
void **updateEnable()**

Disables/enables update event (UDIS bit in the CR1 register).

* void **updateInterrupt(uint8_t bit)**
* void **CC1interrupt(uint8_t bit)**
* void **CC2interrupt(uint8_t bit)**
* void **CC3interrupt(uint8_t bit)**
* void **CC4interrupt(uint8_t bit)**
* void **COMinterrupt(uint8_t bit)** *Timer1 only*
* void **triggerInterrupt(uint8_t bit)**
* void **breakInterrupt(uint8_t bit)** *Timer1 only*

Enable (`bit == 1`) or disable (`bit == 0`) timer interrupts.

* void **clearUpdate()**
* void **clearCC1()**
* void **clearCC2()**
* void **clearCC3()**
* void **clearCC4()**
* void **clearCOM()** *Timer1 only*
* void **clearTrigger()**
* void **clearBreak()** *Timer1 only*

Clear the certain named interrupt flag in the SR register.

* void **clearAll()**

Clear the SR register (all the interrupt/overcapture flags are reset).

* void **updateEvent()**
* void **CC1event()**
* void **CC2event()**
* void **CC3event()**
* void **CC4event()**
* void **COMevent()** *Timer1 only*
* void **triggerEvent()**
* void **breakEvent()** *Timer1 only*

Generate an event (set a bit in the EGR register).

## Examples

1) SysTick interrupt, changes output on pin B6 with 1 second intervals

```c++
gpioB_pin PB6(6);

extern "C"
{
void SysTick_Handler(void)
{
PB6.invert();
}
}

int main()
{
	gpioB_init();
	PB6.mode(OUTPUT);
	sysTick_intEnable();
	sysTick_start(9000000, 0);
	while(1){};
}
```

2) PWM and SysTick delays, pin PB6

```c++
tim4_pwm pwm2(1);

int main()
{

	timer4_init();
	pwm2.init();
	pwm2.polarity = 0;
	//pwm2.depth(1);
	//pwm2.prescaler(0xFFFF);
	pwm2.enable();
	pwm2.write(1000);

	while(1)
	{
	for (uint16_t k = 0xFFFF; k>0; --k)
	{
		pwm2.write(k);
		delay_us(10);
	}
	for (uint16_t k = 0; k<0xFFFF; ++k)
	{
		pwm2.write(k);
		delay_us(10);
	}
	delay_ms(1000);
	}
}
```
