/*
 * mbi5252.cpp
 *
 *  Created on: 18 дек. 2019 г.
 *      Author: Ontaelio
 */

#include <mbi5252.h>

void mbi5252::vsync()
{
	//GCLK->disable();
	delay_us(2);
	LE->high();
	DCLKpulse();
	DCLKpulse();
	DCLKpulse();
	LE->low();
	delay_us(2);
	//GCLK->enable();
}

void mbi5252::gclk_setup(uint16_t d, uint16_t m)
{
	GCLK->disable();
	GCLK->depth = d;
	GCLK->pwmMode = 2;
	GCLK->init(1);
	GCLK->write(m);
	GCLK->enable();
}

void mbi5252::sendOneLED(uint16_t dat)
{

	/*for (uint16_t k=0x2000; k>0x0000; k>>=1)
	{
		if (dat&k) SDI->high(); else SDI->low();
		DCLKpulse();
	}*/

	for (uint16_t k=13; k>0; k--)
	{
		if ((dat>>k)&1) SDI->high(); else SDI->low();
		DCLKpulse();
	}
	if (dat&1) SDI->high(); else SDI->low();
	DCLKpulse();

	SDI->low();
	DCLKpulse();
	//DCLKpulse();

	LE->high();
	DCLK->high();
	LE->low();
	DCLK->low();
	//SDI->low();

}

void mbi5252::sendOneSet(uint16_t* data)
{
	for (uint8_t k=16; k>0; k--) sendOneLED(data[k-1]);
}

void mbi5252::sendOneFrame(uint16_t* data)
{
	for (uint8_t k=16; k>0; k--) sendOneSet(&data[(k-1)*16]);
}



void mbi5252::config1(uint16_t c1)
{
	LE->high();
	for (uint8_t k=0; k<14; ++k) DCLKpulse();

	LE->low();
	for (uint16_t k=0x8000; k>0x0008; k>>=1)
	{
		if (c1&k) SDI->high(); else SDI->low();
		DCLKpulse();
	}
	LE->high(); //4 dclk pulses to set
	if (c1&0x0008) SDI->high(); else SDI->low();
	DCLKpulse();
	if (c1&0x0004) SDI->high(); else SDI->low();
	DCLKpulse();
	if (c1&0x0002) SDI->high(); else SDI->low();
	DCLKpulse();
	if (c1&0x0001) SDI->high(); else SDI->low();
	DCLKpulse();
	LE->low();
}

void mbi5252::config2(uint16_t c2)
{
	c2|=0x1010; //default reserved values
	LE->high();
	for (uint8_t k=0; k<14; ++k) DCLKpulse();
	LE->low();
	for (uint16_t k=0x8000; k>0x0080; k>>=1)
	{
		if (c2&k) SDI->high(); else SDI->low();
		DCLKpulse();
	}
	LE->high(); //8 dclk pulses to set
	for (uint16_t k=0x0080; k>0x0000; k>>=1)
	{
		if (c2&k) SDI->high(); else SDI->low();
		DCLKpulse();
	}
	LE->low();
}

void mbi5252::init(uint16_t d, uint16_t m)
{
	config1(cr1);
	config2(cr2);
	//gclk_setup(d, m);
}
