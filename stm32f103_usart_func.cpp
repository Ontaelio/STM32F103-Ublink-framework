/*
 * STM32F103 USART functions source file
 * Part of STM32F103 register and peripherals library
 *
 * Documentation available in the provided MD file.
 *
 * (c) 2019-2020 Dmitry Reznikov ontaelio(at)gmail.com
 *
 * Can be freely used according to the GNU GPL license.
 */

#include <stm32f103_usart_func.h>




void usart::sendStream(uint8_t* dat, uint32_t size)
{
	for (uint32_t k = 0; k<size; k++)
	{
		sendByte(dat[k]);
	}
}

void usart::printString(const char *str)
{
	while (*str) //print chars until termination encountered
	{
		sendByte(*str);
		++str;
	}

	//old thing, bigger code, requires string.h
	/*size_t t = strlen(str);
	for (uint_fast8_t k = 0; k<t; k++)
	{
		sendByte(str[k]);
	}*/
}

#ifdef USE_BUFFER_FOR_INTS

//this version uses buffer. May be useful if something goes wrong
void usart::printUInt(uint32_t a)
{
	char buf[10];
	uint_fast8_t t = 0;
	do
	{
		buf[t] = ((a % 10) + '0');
		a/=10;
		++t;
	} while(a);

	do
	{
		--t;
		sendByte(buf[t]);

	} while(t);
}

#else

//this version uses stack. Faster and smaller, but MAY produce errors with interrupts
void usart::printUInt(uint32_t a)
{
	uint_fast8_t cnt = 0;
	uint_fast8_t t;
	do
	{
		t = ((a % 10) + '0');
		__asm__ __volatile__ ("push {%0}" ::"r"(t):);
		a /= 10;
		++cnt;
	} while (a);

	do
	{
		__asm__ __volatile__ ("pop {%0}" :"=r"(t)::);
		sendByte((char)t);
		--cnt;
	} while (cnt);
}

#endif

void usart::printInt(int32_t a)
{
	if (a < 0) { sendByte('-'); a = abs(a); }
	printUInt(a);
}

void usart::fprintUInt(uint32_t a, uint_fast8_t s)
{
	uint32_t pow10[10] = {
     1, 10, 100, 1000, 10000,
      100000, 1000000, 10000000, 100000000, 1000000000
    };
	if (s>10) s=10;
	while((s>0) && (a<pow10[--s])) sendByte('0');
	if (a>0) printUInt(a);
}

/*
void usart::printFloat(double a)
{
	if (a<0) { sendByte('-'); a = abs(a); }
	printUInt((uint32_t)a);
	sendByte('.');
	a -= (uint32_t)a;
	a *= 100;
	if (a < 10) sendByte('0');
	printUInt(a);
}



void usart::fprintInt(int32_t a, uint_fast8_t s)
{
	if (a < 0) { sendByte('-'); a = abs(a); }
	fprintUInt(a, s);
}

void usart::fprintFloatB(long double a, uint_fast8_t s)
{
	uint32_t pow10[10] = {
     1, 10, 100, 1000, 10000,
      100000, 1000000, 10000000, 100000000, 1000000000
    };
	if (s>9) s=9;
	if (a<0) { sendByte('-'); a = abs(a); }
	printUInt((uint32_t)a);
	sendByte('.');
	a -= (uint32_t)a;
	a*=pow10[s];
	while((s>0) && (a<pow10[--s])) sendByte('0');
	if (a>0) printUInt(a);
}
*/

void usart::printFloat(long double a, uint_fast8_t s)
{

#ifdef NAN_INFINITY_ENABLED

	if (!isfinite(a))
	{
		if (isnan(a)) {printString("NaN"); return;}
		if (a<0) sendByte('-');
		printString("infinity");
		return;
	}

#endif

	if (a<0) { sendByte('-'); a = abs(a); }
	printUInt((uint32_t)a);
	sendByte('.');
	a -= (uint32_t)a;
	while(s-- && (a>0))
	{
		a*=10;
		printUInt(a);
		a -= (uint32_t)a;
	}
	//below skip 0s!
	//do a*=10; while (--s); 8 bytes more than below!
	//for (uint8_t k = 0; k<s; k++) a*=10;
	//printUInt(a);//lroundl(a));
}



void usart::getStream(uint8_t* dat, uint16_t size)
{
	for (uint16_t k = 0; k<size; k++)
	{
		dat[k] = getByte();
	}
}

char usart::getChar()
{
	char res;
	res = getByte();
	return res;
}

uint64_t usart::getUInt()
{
	uint64_t res = 0;
	uint8_t b;
	do b = getByte() - 48; while (b>9);
	do
	{
		res = res*10 + b;
		b = getByte() - 48;
	} while (b<10);
	return res;
}

int64_t usart::getInt()
{
	int res = 0;
	uint8_t b;
	uint_fast8_t neg = 0;
	do b = getByte(); while ((b-48)>9 && (b!='-'));
	if (b == '-') {neg = 1; b = getByte() - 48;} else b-=48;
	do
	{
		res = res*10 + b;
		b = getByte() - 48;
	} while (b<10);
	if (neg) res = 0-res;
	return res;
}

long double usart::getFloat()
{
	long double res = 0;
	uint32_t divider = 10;
	uint8_t b;
	do {b = getByte(); if (b == '-') res = -0; b-=48;} while (b>9);
	do
	{
		res = res*10 + b;
		b = getByte() - 48;
	} while (b<10);
	if (b != 254) return res;
	res = (uint32_t)res;
	b = getByte() - 48;
	while (b<10)
	{
		res = res + (double)b/divider;
		b = getByte() - 48;
		divider *= 10;
	}
	return res;
}

void usart::getString(char* arr)
{
	char c;
	do
	{
		c = getByte();
		if (c>31) {*arr = c; ++arr;}
	} while (c>31);
	*arr = 0;
}


void usart::printUInt64(uint64_t a)
{
	char buf[20];
	uint_fast8_t t = 0;
	do
	{
		buf[t] = ((a % 10) + '0');
		a/=10;
		++t;
	} while(a);

	do sendByte(buf[--t]); while(t);
}

void usart::printInt64(int64_t a)
{
	if (a < 0) { sendByte('-'); a = abs(a); }
	printUInt64(a);
}

//not sure about this. Can be substituted in cout or totally omitted
//if omitted should mention c_str in docs.
void usart::printCPPString(std::string s)
{
	printString(s.c_str());
}



usart& operator << (usart& out, const char* str)
{
	out.printString(str); return out;
}

usart& operator << (usart& out, const unsigned dat)
{
	out.printUInt(dat); return out;
}

usart& operator << (usart& out, const uint8_t dat)
{
	out.printUInt(dat); return out;
}

usart& operator << (usart& out, const uint16_t dat)
{
	out.printUInt(dat); return out;
}

usart& operator << (usart& out, const uint32_t dat)
{
	out.printUInt(dat); return out;
}

usart& operator << (usart& out, const uint64_t dat)
{
	out.printUInt(dat); return out;
}

usart& operator << (usart& out, const float dat)
{
	out.printFloat(dat); return out;
}

usart& operator << (usart& out, const double dat)
{
	out.printFloat(dat); return out;
}

usart& operator << (usart& out, const long double dat)
{
	out.printFloat(dat); return out;
}

usart& operator << (usart& out, const int dat)
{
	out.printInt(dat); return out;
}

usart& operator << (usart& out, const int8_t dat)
{
	out.printInt(dat); return out;
}

usart& operator << (usart& out, const int16_t dat)
{
	out.printInt(dat); return out;
}

usart& operator << (usart& out, const int32_t dat)
{
	out.printInt(dat); return out;
}

usart& operator << (usart& out, const int64_t dat)
{
	out.printInt(dat); return out;
}

usart& operator << (usart& out, const char ch)
{
	out.sendByte(ch); return out;
}

usart& operator >> (usart& in, char* str)
{
	in.getString(str);
	return in;
}

usart& operator >> (usart& in, char &dat)
{
	dat = in.getChar();
	return in;
}

usart& operator >> (usart& in, unsigned &dat)
{
	dat = in.getUInt();
	return in;
}

usart& operator >> (usart& in, uint8_t &dat)
{
	dat = in.getUInt();
	return in;
}

usart& operator >> (usart& in, uint16_t &dat)
{
	dat = in.getUInt();
	return in;
}

usart& operator >> (usart& in, uint32_t &dat)
{
	dat = in.getUInt();
	return in;
}

usart& operator >> (usart& in, uint64_t &dat)
{
	dat = in.getUInt();
	return in;
}


usart& operator >> (usart& in, int &dat)
{
	dat = in.getInt();
	return in;
}

usart& operator >> (usart& in, int8_t &dat)
{
	dat = in.getInt();
	return in;
}

usart& operator >> (usart& in, int16_t &dat)
{
	dat = in.getInt();
	return in;
}

usart& operator >> (usart& in, int32_t &dat)
{
	dat = in.getInt();
	return in;
}

usart& operator >> (usart& in, int64_t &dat)
{
	dat = in.getInt();
	return in;
}

usart& operator >> (usart& in, float &dat)
{
	dat = in.getFloat();
	return in;
}

usart& operator >> (usart& in, double &dat)
{
	dat = in.getFloat();
	return in;
}

usart& operator >> (usart& in, long double &dat)
{
	dat = in.getFloat();
	return in;
}





void usart1::init(uint32_t baud, uint_fast8_t remap)
{
	if (remap)
	{
		//enable GPIOB | USART1 |alt func
		_RCC_(RCC_APB2ENR) |= RCC_APB2ENR_IOPBEN | RCC_APB2ENR_USART1EN | RCC_APB2ENR_AFIOEN;
		//remap the pins
		_AFIO_(AFIO_MAPR) |= AFIO_MAPR_USART1_REMAP;
		//configure pins; TX(PB6) alt push-pull output; RX(PB7) input
		pinB6_Output_AFPP_50(); //these are in gpio_func header
		pinB7_Input();
	}
	else
	{
		//enable GPIOA | USART1 |alt func
		_RCC_(RCC_APB2ENR) |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_USART1EN | RCC_APB2ENR_AFIOEN;
		//configure pins; TX(PA9) alt push-pull output; RX(PA10) input
		pinA9_Output_AFPP_50(); //these are in gpio_func header
		pinA10_Input();
	}

	//set speed
	_USART1_(USART_BRR) = APB2SPEED/baud;
	//enable USART
	_USART1_(USART_CR1) |= USART_CR1_UE;
	//enable TX and RX
	_USART1_(USART_CR1) |= USART_CR1_TE | USART_CR1_RE;
}

void usart1::sendByte(uint8_t dat)
{
	while(!(_USART1_(USART_SR) & USART_SR_TC));
	_USART1_(USART_DR) = dat;
}

uint8_t usart1::getByte()
{
	uint8_t res;
	while(!(_USART1_(USART_SR) & USART_SR_RXNE));
	res = _USART1_(USART_DR);
	return res;
}

uint8_t usart1::dumpRX()
{
	volatile uint8_t dumpres;
	while(!(_USART1_(USART_SR) & USART_SR_IDLE)) {delay_ms(10);} //{dumpres = getByte();}
	dumpres = getByte(); //_USART1_(USART_DR);
	return dumpres;
}

void usart1::IRQenable(uint16_t irqs)
{
	IRQ_32TO63_SER |= IRQ_USART1;
	_USART1_(USART_CR1) &= ~0x01F0; //clear interrupt enables
	_USART1_(USART_CR3) &= ~0x0401; //clear interrupt enables
	_USART1_(USART_CR1) |= (irqs & 0x01F0); //set particular bits
	_USART1_(USART_CR3) |= (irqs & 0x0401); //set particular bits
}
