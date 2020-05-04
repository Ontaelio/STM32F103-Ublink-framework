/*
 * stm32f103_rtc_clock.h
 *
 *  Created on: 9 дек. 2019 г.
 *      Author: Ontaelio
 */

#ifndef STM32F103_RTC_CLOCK_H_
#define STM32F103_RTC_CLOCK_H_

#include <stdio.h>
#include <stdint.h>
#include <stm32f103_rtc.h>

//#define WEEKDAYOFFSET 4 // for a leap year 0 use 4
#define YEARZERO 2017  //2017 is default, starts on Sunday
#define UNIXSECONDSOFFSET 1483228800 //UNIX time offset for year 2017
//constexpr int8_t UNIXTIMEZONE = 3; //can be negative; used in UNIXtime functions only
#define UNIXTIMEZONE (int8_t)3

inline uint16_t leapYear(uint16_t a) { return ((a & 3) == 3); } // for use with YEARZERO
inline bool realLeapYear(uint16_t); //checks the real year number

struct Date
{
	Date() : Year(2017), Month(1), Day(1), DayOfWeek(0) {}
	Date(uint16_t y, uint16_t m, uint16_t d, uint16_t dw = 0) : Year(y), Month(m), Day(d), DayOfWeek(dw) {}
	uint16_t Year;
	uint16_t Month;
	uint16_t Day;
	uint16_t DayOfWeek;
	Date& operator++ ();
	Date operator++ (int);
	Date& operator+= (const uint16_t&);
	Date& operator+= (const time_interval& timint);
};

struct Time
{
	Time() : Hour(0), Minute(0), Second(0) {}// = default;
	Time(uint16_t h, uint16_t m, uint16_t s = 0) : Hour(h), Minute(m), Second(s) {}
	uint16_t Hour;
	uint16_t Minute;
	uint16_t Second;
	Time& operator++ ();
	Time operator++ (int);
	Time& operator+= (const uint16_t&);
	Time& operator+= (const time_interval&);
	Time& operator-= (const time_interval&);
};

//these work directly with the counter
Time getTime();
Date getDate();
void setTime(Time time);
void setDate(Date date);
void setDateTime(Date date, Time time);
void setAlarm(Time);
void setAlarm(Date, Time);
void standByUntil(Time);
void standByUntil(Date, Time);
void standByFor(uint32_t);


//these work with a saved value
uint32_t DateTime(Date date, Time time);
Time getTime(uint32_t time_val);
Date getDate(uint32_t time_val);

//complementary functions
uint32_t date2days(Date date);
uint32_t date2days_full(Date date);
Date days2date(uint32_t days, uint16_t year);
Date days2date_full(uint32_t days);
uint32_t time2seconds(Time t);
Time seconds2time(uint32_t time_val);
uint32_t interval2seconds(time_interval t);
time_interval seconds2interval(uint32_t time_val);
time_interval duration(const Time& start, const Time& end);
uint32_t duration(const Date& start, const Date& end);

//UNIX time conversions
Date UNIXdate(const uint32_t& uxsec);
Time UNIXtime(const uint32_t& uxsec);
uint32_t UNIXtime(const Date& dat, const Time& tim);

//overloaded operators
uint8_t operator== (const Date& fst, const Date& snd);
uint8_t operator!= (const Date& fst, const Date& snd);
uint8_t operator> (const Date& date1, const Date& date2);
uint8_t operator< (const Date& date1, const Date& date2);
Date operator+ (const Date& date, const uint16_t& days);
Date operator+ (const uint16_t& days, const Date& date);
Date operator+ (const Date& date, const time_interval& timint);
Date operator+ (const time_interval& timint, const Date& date);
uint32_t operator- (const Date& date1, const Date& date2);

uint8_t operator== (const Time& fst, const Time& snd);
uint8_t operator!= (const Time& fst, const Time& snd);
uint8_t operator> (const Time& time1, const Time& time2);
uint8_t operator< (const Time& time1, const Time& time2);
Time operator+ (const Time& time, const uint32_t& seconds);
Time operator+ (const uint32_t& seconds, const Time& time);
Time operator+ (const Time& time, const time_interval& time2);
Time operator+ (const time_interval& time2, const Time& time);
time_interval operator- (const Time& time1, const Time& time2);
Time operator- (const Time& time, const time_interval& timeint);

#endif /* STM32F103_RTC_CLOCK_H_ */
