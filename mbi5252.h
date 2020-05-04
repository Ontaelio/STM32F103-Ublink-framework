/*
 * mbi5252.h
 *
 *  Created on: 18 дек. 2019 г.
 *      Author: Ontaelio
 */

#ifndef MBI5252_H_
#define MBI5252_H_

#include <stm32f103_gpio.h>
#include <stm32f103_timers.h>

class mbi5252
{
public:
	mbi5252(gpio_pin* sdi, gpio_pin* dclk, gpio_pin* le, tim_pwm* gclk):
		cr1(0x002B),
		cr2(0x1010),
		DCLK(dclk),
		LE(le),
		SDI(sdi),
		GCLK(gclk) {};
	void sendOneLED(uint16_t dat);
	void sendOneSet(uint16_t* data);
	void sendOneFrame(uint16_t* data);
	void gclk_setup(uint16_t d, uint16_t m);
	void vsync();
	void config1(uint16_t c1);
	void config2(uint16_t c2);
	void reset();


	void setGhostElimination(uint8_t val) {val&=1; cr1&=~0x8000; cr1 |= val<<15;}
	void setScanLines(uint8_t val) {--val; val&=15; cr1&=~0x0F00; cr1 |= val<<8;}
	void setGSmode(uint8_t val) {val&=1; cr1&=~0x0080; cr1 |= val<<7;}
	void setGCLKmultiplier(uint8_t val) {val&=1; cr1&=~0040; cr1 |= val<<6;}
	void setBrightness(uint8_t val) {val&=63; cr1&=~0x003F; cr1 |= val;}
	void setDoubleRefresh(uint8_t val) {val&=1; cr2&=~0x0400; cr2 |= val<<10;}
	void setDimLineCompensation(uint8_t val) {val&=7; cr2&=~0x000E; cr2 |= val<<1;}
	void init(uint16_t d = 0x0001, uint16_t m = 0x0001);

	uint16_t cr1, cr2; // = 0x002B, cr2 = 0x1010;

private:
	void DCLKpulse() {DCLK->high();DCLK->low();}
	gpio_pin* DCLK, *LE, *SDI;
	tim_pwm* GCLK;

};


#endif /* MBI5252_H_ */
