/*
 * stm32f103_rtc_func.cpp
 *
 *  Created on: 3 äåê. 2019 ã.
 *      Author: Ontaelio
 */

#include <stm32f103_rtc_reg.h>
#include <stm32f103_rcc_reg.h>
#include <stdio.h>
#include <stm32f103_rtc.h>
#include <stm32f103_timers.h>

void rtc_init(uint32_t presc)
{
	_RCC_(RCC_APB1ENR) |= RCC_APB1ENR_PWREN; //enable power and backup clocks
	_RCC_(RCC_APB1ENR) |= RCC_APB1ENR_BKPEN; //after reset
	_PWR_(PWR_CR) |= PWR_CR_DBP; //disable write protection

	if (!(_RCC_(RCC_BDCR) & RCC_BDCR_RTCEN)) //check if RTC is already on
	{
		_RCC_(RCC_BDCR) |= RCC_BDCR_LSEON;
		while (!(_RCC_(RCC_BDCR) & RCC_BDCR_LSERDY)) {}
		_RCC_(RCC_BDCR) &= ~RCC_BDCR_RTCSEL;
		_RCC_(RCC_BDCR) |= 1<<8; //LSE clock used; 01 in RTCSEL 1<<8 // 10 for LSI 1<<9
								//3<<8 for HSI as a clock source

		_RCC_(RCC_BDCR) |= RCC_BDCR_RTCEN; //enable RTC

		while (!(_RTC_(RTC_CRL) & RTC_CRL_RTOFF)) {} //wait for write complete
		_RTC_(RTC_CRL) |= RTC_CRL_CNF; //enable config writes
		_RTC_(RTC_PRLH) = presc >> 16;
		_RTC_(RTC_PRLL) = presc & 0xFFFF; //s 0x7FFF == 1 second tick
		_RTC_(RTC_CRL) &= ~RTC_CRL_CNF; //do the actual write
		while (!(_RTC_(RTC_CRL) & RTC_CRL_RTOFF)) {} //wait for write complete

		_RCC_(RCC_BDCR) |= RCC_BDCR_RTCEN; //enable RTC

		_RTC_(RTC_CRL) &= ~RTC_CRL_RSF; //clear synch flag

		while (!(_RTC_(RTC_CRL) & RTC_CRL_RSF)) {} //wait for synch
	}
}

void rtc_reset()
{
	_RCC_(RCC_APB1ENR) |= RCC_APB1ENR_PWREN; //enable power and backup clocks
	_RCC_(RCC_APB1ENR) |= RCC_APB1ENR_BKPEN; //after reset
	_PWR_(PWR_CR) |= PWR_CR_DBP; //disable write protection
	_RCC_(RCC_BDCR) |= RCC_BDCR_BDRST; //reset backup domain
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	_RCC_(RCC_BDCR) &= ~RCC_BDCR_BDRST; //clear reset backup domain
}


void rtc_write(uint32_t timer_val)
{
	while (!(_RTC_(RTC_CRL) & RTC_CRL_RTOFF)) {} //wait for write complete
	_RTC_(RTC_CRL) |= RTC_CRL_CNF; //enable CNT writes
	_RTC_(RTC_CNTH) = timer_val>>16;
	_RTC_(RTC_CNTL) = timer_val&0xFFFF;
	_RTC_(RTC_CRL) &= ~RTC_CRL_CNF; //do the actual write
	while (!(_RTC_(RTC_CRL) & RTC_CRL_RTOFF)) {} //wait for write complete
	_RTC_(RTC_CRL) &= ~RTC_CRL_RSF; //clear synch flag
	while (!(_RTC_(RTC_CRL) & RTC_CRL_RSF)) {} //wait for synch
}

uint32_t rtc_read()
{
	return (_RTC_(RTC_CNTH)<<16) +  _RTC_(RTC_CNTL);
}

void setAlarm(uint32_t al_val)
{
	while (!(_RTC_(RTC_CRL) & RTC_CRL_RTOFF)) {} //wait for write complete
	_RTC_(RTC_CRL) |= RTC_CRL_CNF; //enable CNT writes
	_RTC_(RTC_ALRH) = al_val>>16;
	_RTC_(RTC_ALRL) = al_val&0xFFFF;
	_RTC_(RTC_CRL) &= ~RTC_CRL_CNF; //do the actual write
	while (!(_RTC_(RTC_CRL) & RTC_CRL_RTOFF)) {} //wait for write complete
}

void setAlarmIRQ(uint8_t a)
{
	while (!(_RTC_(RTC_CRL) & RTC_CRL_RTOFF)) {} //wait for write complete
	BB_RTC_CRH_ALRIE = a;
}

void setSecondIRQ(uint8_t a)
{
	while (!(_RTC_(RTC_CRL) & RTC_CRL_RTOFF)) {} //wait for write complete
	BB_RTC_CRH_SECIE = a;
}

void setRTCoverflowIRQ(uint8_t a)
{
	while (!(_RTC_(RTC_CRL) & RTC_CRL_RTOFF)) {} //wait for write complete
	BB_RTC_CRH_OWIE = a;
}

void pwr_standBy()
{
	_PWR_(PWR_CR) |= PWR_CR_DBP;
	_PWR_(PWR_CR) |= PWR_CR_CWUF; //clear wakeup flag
	SYSTEM_CONTROL_REGISTER |= DEEPSLEEP; //set deep sleep in Cortex SCR
	_PWR_(PWR_CR) |= PWR_CR_PDDS; //set deep sleep in STM
	asm("wfe"); //wait for event

//	WFI (Wait for Interrupt) or WFE (Wait for Event) while:
//– Set SLEEPDEEP in Cortex®-M3 System Control register
//– Set PDDS bit in Power Control register (PWR_CR)
//– Clear WUF bit in Power Control/Status register (PWR_CSR)
//– No interrupt (for WFI) or event (for WFI) is pending
}


//void pwr_sleep()
//{

//}

void wakeUpFromStandby()
{
	_PWR_(PWR_CR) |= PWR_CR_DBP;
	_PWR_(PWR_CR) |= PWR_CR_CWUF; //clear wakeup flag
	clearAlarm();
}


void backupByte(uint8_t place, uint8_t dat)
{
	_BKP_(BKP_DR1 + (place/2)*4) = dat<<((place%1)*8);
}

void backupWord(uint8_t place, uint16_t dat)
{
	_BKP_(BKP_DR1 + (place*4)) = dat;
}

uint8_t restoreByte(uint8_t place)
{
	return _BKP_(BKP_DR1 + (place/2)*4) >> ((place%1)*8);
}

uint16_t restoreWord(uint8_t place)
{
	return _BKP_(BKP_DR1 + (place*4));
}

