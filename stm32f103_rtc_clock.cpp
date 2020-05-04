/*
 * stm32f103_rtc_clock.cpp
 *
 *  Created on: 9 дек. 2019 г.
 *      Author: Ontaelio
 */

#include <stm32f103_rtc.h>
#include <stm32f103_rtc_clock.h>

uint8_t daysPerMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

bool realLeapYear(uint16_t y)
{
	bool res;
	res = !(y % 4);
	if (!(y % 100)) if (y % 400) res = false;
	return res;
}

//these work directly with the counter

Time getTime()
{
	return getTime(rtc_read());
	/*uint32_t time_val = rtc_read();
	Time res;
	uint32_t tmp_time = time_val % 86400; // get the time of the day, discarding the date

	res.Hour = tmp_time / 3600;
	uint16_t tmp_min = tmp_time % 3600;

	res.Minute = tmp_min / 60;
	res.Second = tmp_min % 60;
	return res;*/
}

Date getDate()
{
	return getDate(rtc_read());
	/*Date res;
	uint32_t time_val = rtc_read();
	uint16_t tmp_days = time_val / 86400;

	#ifndef WEEKDAYOFFSET
	res.DayOfWeek = tmp_days % 7; //while we're here. 2017 started with Sunday, so no adds
	#else
	res.DayOfWeek = tmp_days % 7 + WEEKDAYOFFSET;
	#endif

	uint16_t tmp_years = tmp_days / 1461; //number of days in 4 years with one leap
	uint16_t rem_days = tmp_days % 1461; // !!!
	if (rem_days < 1460)
	{
		res.Year = rem_days / 365 + tmp_years * 4; tmp_days = rem_days % 365;
	}
	else { res.Year = 3 + tmp_years * 4; tmp_days = 365; }

	uint8_t tmp_m = 0;
	if (leapYear(res.Year)) daysPerMonth[1] = 29; // leap year, temporary change
	while (tmp_days >= daysPerMonth[tmp_m])
	{
		tmp_days -= daysPerMonth[tmp_m];
		++tmp_m;
	}
	res.Month = tmp_m + 1;
	res.Day = tmp_days + 1;
	daysPerMonth[1] = 28; // just in case
	res.Year += YEARZERO; // finally
	return res;*/
}

void setTime(Time time)
{
	uint32_t seconds = rtc_read() / 86400; //discard time, keep date
	seconds += time2seconds(time);// (uint32_t)time.Hour * 3600 + (uint32_t)time.Minute * 60 + (uint32_t)time.Second;
	rtc_write(seconds);
}

void setDate(Date date)
{
	date.Year -= YEARZERO;
	uint16_t days = date.Year * 365 + (date.Year / 4);
	uint8_t tmp_m = 1;
	while (tmp_m < date.Month)
	{
		days += daysPerMonth[tmp_m - 1];
		++tmp_m;
	}
	days += (date.Day - 1);
	if ((date.Month > 2) && leapYear(date.Year)) ++days;
	uint32_t seconds = days * 86400;
	seconds += rtc_read() % 86400;
	rtc_write (seconds);
}

void setDateTime(Date date, Time time)
{
	/*date.Year -= YEARZERO;
	uint16_t days = date.Year * 365 + (date.Year / 4);
	uint8_t tmp_m = 1;
	while (tmp_m < date.Month)
	{
		days += daysPerMonth[tmp_m - 1];
		++tmp_m;
	}
	days += (date.Day - 1);
	if ((date.Month > 2) && leapYear(date.Year)) ++days;
	uint32_t seconds = days * 86400;
	seconds += (uint32_t)time.Hour * 3600 + (uint32_t)time.Minute * 60 + (uint32_t)time.Second;*/
	rtc_write(DateTime(date, time));
}

void setAlarm(Time time)
{
	uint32_t tt = time2seconds(time);
	uint32_t a = time2seconds(getTime());
	if (a >= tt) tt += 86400;
	setAlarm(tt);
}

void setAlarm(Date date, Time time)
{
	uint32_t tt = DateTime(date, time);
	setAlarm(tt);
}

void standByUntil(Time time)
{
	setAlarm(time);
	pwr_standBy();
}

void standByUntil(Date d, Time t)
{
	setAlarm(d, t);
	pwr_standBy();
}

void standByFor(uint32_t sec)
{
	setAlarm(rtc_read() + sec);
	pwr_standBy();
}


//these work with a saved value and provide a value for above

uint32_t DateTime(Date date, Time time)
{
	date.Year -= YEARZERO;
	uint16_t days = date.Year * 365 + (date.Year / 4);
	uint16_t tmp_m = 1;
	while (tmp_m < date.Month)
	{
		days += daysPerMonth[tmp_m - 1];
		++tmp_m;
	}
	days += (date.Day - 1);
	if ((date.Month > 2) && leapYear(date.Year)) ++days;
	uint32_t seconds = days * 86400;
	seconds += time.Hour * 3600 + time.Minute * 60 + time.Second;
	return seconds;
}

Time getTime(uint32_t time_val)
{
	Time res;
	uint32_t tmp_time = time_val % 86400; // get the time of the day, discarding the date

	res.Hour = tmp_time / 3600;
	uint16_t tmp_min = tmp_time % 3600;

	res.Minute = tmp_min / 60;
	res.Second = tmp_min % 60;
	return res;
}

Date getDate(uint32_t time_val)
{
	Date res;
	uint16_t tmp_days = time_val / 86400; // the number of full days in our timer

	#ifndef WEEKDAYOFFSET
	res.DayOfWeek = tmp_days % 7; //while we're here. 2017 started with Sunday, so no adds
	#else
	res.DayOfWeek = tmp_days % 7 + WEEKDAYOFFSET;
	#endif

	uint16_t tmp_years = tmp_days / 1461; //number of days in 4 years with one leap
	uint16_t rem_days = tmp_days % 1461; // !!!
	if (rem_days < 1460)
	{
		res.Year = rem_days / 365 + tmp_years * 4; tmp_days = rem_days % 365;
	}
	else { res.Year = 3 + tmp_years * 4; tmp_days = 365; }


	uint16_t tmp_m = 0;
	if (leapYear(res.Year)) daysPerMonth[1] = 29; // leap year, temporary change
	while (tmp_days >= daysPerMonth[tmp_m])
	{
		tmp_days -= daysPerMonth[tmp_m];
		++tmp_m;
	}
	res.Month = tmp_m + 1;
	res.Day = tmp_days + 1;
	daysPerMonth[1] = 28; // just in case we keep this somewhere
	res.Year += YEARZERO; // finally
	return res;
}

//complementary functions

uint32_t date2days(Date date)
{
	uint16_t days = 0;
	uint8_t tmp_m = 1;
	while (tmp_m < date.Month)
	{
		days += daysPerMonth[tmp_m - 1];
		++tmp_m;
	}
	days += (date.Day - 1);
	if ((date.Month > 2) && realLeapYear(date.Year)) ++days;
	return days;
}

uint32_t date2days_full(Date date)
{
	uint16_t y = date.Year - YEARZERO;
	uint16_t days = y * 365 + (y / 4);
	days += date2days(date);
	return days;
}

Date days2date(uint32_t days, uint16_t year)
{
	Date res;
	if (realLeapYear(year)) daysPerMonth[1] = 29;
	uint8_t tmp_m = 0;
	uint32_t tmp_days = days;
	while (tmp_days >= daysPerMonth[tmp_m])
	{
		tmp_days -= daysPerMonth[tmp_m];
		++tmp_m;
	}
	daysPerMonth[1] = 28;
	res.Month = tmp_m + 1;
	res.Day = tmp_days + 1;
	res.Year = year;
	return res;
}

Date days2date_full(uint32_t days)
{
	uint32_t tmp_days = days;
	Date res;
#ifndef WEEKDAYOFFSET
	res.DayOfWeek = tmp_days % 7; //while we're here. 2017 started with Sunday, so no adds
#else
	res.DayOfWeek = tmp_days % 7 + WEEKDAYOFFSET;
#endif

	uint16_t tmp_years = tmp_days / 1461; //number of days in 4 years with one leap
	uint16_t rem_days = tmp_days % 1461; // !!!
	if (rem_days < 1460)
	{
		res.Year = rem_days / 365 + tmp_years * 4; tmp_days = rem_days % 365;
	}
	else { res.Year = 3 + tmp_years * 4; tmp_days = 365; }
	res = days2date(tmp_days, res.Year + YEARZERO);
	return res;
}

uint32_t time2seconds(Time t)
{
	return t.Hour * 3600 + t.Minute * 60 + t.Second;
}

Time seconds2time(uint32_t time_val)
{
	Time res;
	uint32_t tmp_time = time_val % 86400; // get the time of the day, discarding the date

	res.Hour = tmp_time / 3600;
	uint16_t tmp_min = tmp_time % 3600;

	res.Minute = tmp_min / 60;
	res.Second = tmp_min % 60;
	return res;
}

uint32_t interval2seconds(time_interval t)
{
	return t.days * 86400 + t.hours * 3600 + t.minutes * 60 + t.seconds;
}

time_interval seconds2interval(uint32_t time_val)
{
	time_interval res;
	res.days = time_val / 86400;
	uint32_t tmp_time = time_val % 86400; // get the time of the day, discarding the date

	res.hours = tmp_time / 3600;
	uint16_t tmp_min = tmp_time % 3600;

	res.minutes = tmp_min / 60;
	res.seconds = tmp_min % 60;
	return res;
}

time_interval duration(const Time& start, const Time& end)
{
	uint32_t seconds1 = time2seconds(start);
	uint32_t seconds2 = time2seconds(end);
	if (seconds2 < seconds1) seconds2 += 86400;
	return seconds2interval(seconds2 - seconds1);
}

uint32_t duration(const Date& start, const Date& end)
{
	uint32_t d1 = date2days_full(start);
	uint32_t d2 = date2days_full(end);
	d2 -= d1;
	++d2;
	return d2;
}

//UNIX time conversions
Date UNIXdate(const uint32_t& uxsec)
{
	uint32_t uxd = (uxsec - UNIXSECONDSOFFSET + (UNIXTIMEZONE*3600))/86400;
	return days2date_full(uxd);

}

Time UNIXtime(const uint32_t& uxsec)
{
	uint32_t uxt = (uxsec - UNIXSECONDSOFFSET + (UNIXTIMEZONE * 3600));// % 86400;
	return seconds2time(uxt);

}

uint32_t UNIXtime(const Date& dat, const Time& tim)
{
	uint32_t res = date2days_full(dat) * 86400 + UNIXSECONDSOFFSET;
	res += time2seconds(tim);
	res -= UNIXTIMEZONE * 3600;
	return res;
}

//overloaded operators: Date

uint8_t operator== (const Date& fst, const Date& snd)
{
	if (snd.Month == 2 && snd.Day == 29 && fst.Month == 3 && fst.Day== 1 && (!realLeapYear(fst.Year))) return 1;
	else return fst.Month == snd.Month && fst.Day == snd.Day;
}

uint8_t operator!= (const Date& fst, const Date& snd)
{
	return !(fst == snd);
}

uint8_t operator> (const Date& date1, const Date& date2)
{
	Date cd = getDate();
	Date d1 = date1;
	Date d2 = date2;
	cd.Year = 2020;
	d1.Year = 2020;
	d2.Year = 2020;
	uint32_t cdays = date2days(cd);
	uint32_t days1 = date2days(d1);
	uint32_t days2 = date2days(d2);
	if (days1 < cdays) days1 += 400;
	if (days2 < cdays) days2 += 400;
	return (days1 > days2);
}

uint8_t operator< (const Date& date1, const Date& date2)
{
	Date cd = getDate();
	Date d1 = date1;
	Date d2 = date2;
	cd.Year = 2020;
	d1.Year = 2020;
	d2.Year = 2020;
	uint32_t cdays = date2days(cd);
	uint32_t days1 = date2days(d1);
	uint32_t days2 = date2days(d2);
	if (days1 < cdays) days1 += 400;
	if (days2 < cdays) days2 += 400;
	return (days1 < days2);
}

Date Date::operator++ (int)
{
	Date saved = *this;
	++*this;
	return saved;
}

Date& Date::operator++ ()
{
	Day++;
	if (realLeapYear(Year)) daysPerMonth[1] = 29;
	if (Day > daysPerMonth[Month-1])
	{
		Day = 1;
		Month++;
		if (Month > 12)
		{
			Month = 1;
			Year++;
		}
	}
	DayOfWeek++;
	DayOfWeek %= 7;
	daysPerMonth[1] = 28;
	return *this;
}

Date& Date::operator+= (const uint16_t &days)
{
	uint16_t ld = days;
	if (ld > 0) do
	{
		++* this;
		--ld;
	}
	while (ld);
	return *this;
}

Date& Date::operator+= (const time_interval& timint)
{
	*this += timint.days;
	Time a = getTime();
	Time b = a + timint;
	if (b.Hour < a.Hour)++* this; //check if the next day will start
	return *this;
}

Date operator+ (const Date& date, const uint16_t& days)
{
	Date res = date;
	res += days;
	return res;
}

Date operator+ (const uint16_t& days, const Date& date)
{
	Date res = date;
	res += days;
	return res;
}

Date operator+ (const Date& date, const time_interval& timint)
{
	Date res = date;
	res += timint;
	return res;
}

Date operator+ (const time_interval& timint, const Date& date)
{
	Date res = date;
	res += timint;
	return res;
}

uint32_t operator- (const Date& date1, const Date& date2)
{
	return (duration(date2, date1) - 1);
}


//Time operators

uint8_t operator== (const Time& fst, const Time& snd)
{
	return fst.Hour == snd.Hour && fst.Minute == snd.Minute;
}

uint8_t operator!= (const Time& fst, const Time& snd)
{
	return !(fst == snd);
}

uint8_t operator> (const Time& time1, const Time& time2)
{
	Time cur_time = getTime();
	time_interval intr1 = duration(cur_time, time1);
	time_interval intr2 = duration(cur_time, time2);
	return (interval2seconds(intr1) > interval2seconds(intr2));
}

uint8_t operator< (const Time& time1, const Time& time2)
{
	Time cur_time = getTime();
	time_interval intr1 = duration(cur_time, time1);
	time_interval intr2 = duration(cur_time, time2);
	return (interval2seconds(intr1) < interval2seconds(intr2));
}

Time& Time::operator++ ()
{
	Hour++;
	Hour %= 24;
	return *this;
}

Time Time::operator++ (int)
{
	Time saved = *this;
	++* this;
	return saved;
}

Time& Time::operator+= (const uint16_t &min)
{
	uint16_t tmp_min = (uint16_t)Minute + min;
	while (tmp_min > 59)
	{
		Hour++;
		Hour %= 24;
		tmp_min -= 60;
	}
	Minute = tmp_min;
	return *this;
}

Time& Time::operator+= (const time_interval& time2)
{
	uint32_t seconds = interval2seconds(time2);
	//*this = *this + seconds;
	uint16_t th = (uint32_t)seconds / 3600;
	uint16_t ts = (uint32_t)seconds % 3600;
	uint16_t tm = ts / 60;
	ts %= 60;
	Second += ts;
	if (Second > 59) { tm++; Second -= 60; }
	Minute += tm;
	if (Minute > 59) { th++; Minute -= 60; }
	th %= 24;
	Hour += th;
	Hour %= 24;
	return *this;
}

Time operator+ (const Time& time, const uint32_t& seconds)
{
	Time res = time;
	uint16_t th = (uint32_t)seconds / 3600;
	uint16_t ts = (uint32_t)seconds % 3600;
	uint16_t tm = ts / 60;
	ts %= 60;
	res.Second += ts;
	if (res.Second > 59) { tm++; res.Second -= 60; }
	res.Minute += tm;
	if (res.Minute > 59) { th++; res.Minute -= 60; }
	th %= 24;
	res.Hour += th;
	res.Hour %= 24;
	return res;
}

Time operator+ (const uint32_t& seconds, const Time& time)
{
	return time + seconds;
}


Time operator+ (const Time& time, const time_interval& time2)
{
	Time res = time;
	res += time2;
	return res;
}

Time operator+ (const time_interval& time2, const Time& time)
{
	Time res = time;
	res += time2;
	return res;
}

time_interval operator- (const Time& time1, const Time& time2)
{
	return duration(time2, time1);
}

Time operator- (const Time& time, const time_interval& timeint)
{
	Time res = time;
	res -= timeint;
	return res;
}

Time& Time::operator-= (const time_interval& time2)
{
	uint32_t seconds = 86400 - time2.hours*3600 - time2.minutes*60 - time2.seconds;
	*this = *this + seconds;
	return *this;
}
