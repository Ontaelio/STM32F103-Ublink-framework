/*
 * STM32F103 RTC timer, BKP and PWR library header
 * Part of STM32F103 register and peripherals library
 *
 * Dpcumentation available in the provided MD file.
 *
 * (c) 2019 Dmitry Reznikov ontaelio(at)gmail.com
 *
 * Can be freely used according to the GNU GPL license.
 */

#ifndef STM32F103_RTC_H_
#define STM32F103_RTC_H_

#include <stdio.h>
#include <stdint.h>
#include <stm32f103_rtc_reg.h>
#include <stm32f103_bkp_reg.h>
#include <stm32f103_pwr_reg.h>


#ifndef STM32F103_TIMERS_REG_H_
//interrupt set-enable registers
#define IRQ_0TO31_SER	*(volatile uint32_t *) 0xE000E100
#define IRQ_32TO63_SER	*(volatile uint32_t *) 0xE000E104
#define IRQ_0TO31_CER	*(volatile uint32_t *) 0xE000E180
#define IRQ_32TO63_CER	*(volatile uint32_t *) 0xE000E184

#define IRQ_TAMPER			0x00000004
#define IRQ_RTC				0x00000008
#define IRQ_RTCAlarm		0x00000200
#endif


struct time_interval
{
	time_interval() : days(0), hours(0), minutes(0), seconds(0), millis(0) {}
	time_interval(uint32_t sec) :
		days(sec / 86400),
		hours((sec % 86400) / 3600),
		minutes((sec % 86400) % 3600 / 60),
		seconds(sec % 60),
		millis (0){}
	uint16_t days;
	uint16_t hours;
	uint16_t minutes;
	uint16_t seconds;
	uint16_t millis; //this 'millis' is in fact 1/1024 of a second
	operator uint32_t() const { return days * 86400 + hours * 3600 + minutes * 60 + seconds; }
	//time_interval& operator= (const uint32_t& a);
};


/*
struct Date
{
	uint16_t Year;
	uint8_t Month;
	uint8_t Day;
	uint8_t DayOfWeek;
};

struct Time
{
	uint8_t Hour;
	uint8_t Minute;
	uint8_t Second;
};

extern uint8_t daysPerMonth[12];
inline uint8_t leapYear(uint16_t a) { return ((a & 3) == 3); }
*/
void rtc_init(uint32_t presc = 0x7FFF);
void rtc_reset();
void rtc_write(uint32_t);
uint32_t rtc_read();
void setAlarm(uint32_t);
void setAlarmIRQ(uint8_t);
void setSecondIRQ(uint8_t);
void setRTCoverflowIRQ(uint8_t);

void pwr_standBy();
//void pwr_stop();
//void pwr_sleep();
//void pwr_sleepOnExit() {SYSTEM_CONTROL_REGISTER |= SLEEPONEXIT;}

void wakeUpFromStandby();

inline void IRQ_RTC_enable() {IRQ_0TO31_SER |= IRQ_RTC;}
inline void IRQ_RTC_disable() {IRQ_0TO31_CER |= IRQ_RTC;}
inline void IRQ_RTCAlarm_enable() {IRQ_32TO63_SER |= IRQ_RTCAlarm;}
inline void IRQ_RTCAlarm_disable() {IRQ_32TO63_CER |= IRQ_RTCAlarm;}
inline void IRQ_TAMPER_enable() {IRQ_0TO31_SER |= IRQ_TAMPER;}
inline void IRQ_TAMPER_disable() {IRQ_0TO31_CER |= IRQ_TAMPER;}

//fast functions, using bit-band aliases
inline void clearAlarm() {BB_RTC_CRL_ALRF = 0;}
inline void clearSecond() {BB_RTC_CRL_SECF = 0;}
inline void clearRTCoverflow() {BB_RTC_CRL_OWF = 0;}




//Backup domain
void backupByte(uint8_t, uint8_t);
void backupWord(uint8_t, uint16_t);
uint8_t restoreByte(uint8_t);
uint16_t restoreWord(uint8_t);



/*
Time getTime();
Date getDate();
void setTime(Time);
void setDate(Date);
void setDateTime(Date, Time);
*/


#endif /* STM32F103_RTC_H_ */
