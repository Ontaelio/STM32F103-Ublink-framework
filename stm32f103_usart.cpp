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

#include <stm32f103_usart.h>




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
}

void usart::printHex(unsigned val)
{
	uint8_t k = 32;
	printString("0x");
	while (k-=4)
		if (val >> k) sendByte(hexChar((val >> k)&0x0F));
	sendByte(hexChar(val&0x0F));
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
	do b = getByte() - 48; while ((uint8_t)b>9);
	do
	{
		res = res*10 + b;
		b = getByte() - 48;
	} while (b<10);
	return res;
}

int64_t usart::getInt()
{
	int64_t res = 0;
	uint8_t b;
	int8_t neg = 0;
	do b = getByte(); while ((uint8_t)(b-48)>9 && (b!='-'));
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
	uint8_t b = 0;
	int8_t neg = 0;
	do {b = getByte(); if (b == '-') neg = 1; b-=48;} while ((uint8_t)b>9);
	do
	{
		res = res*10 + b;
		b = getByte() - 48;
	} while (b<10);
	if (b != 254) {if (neg) res = 0-res; return res;}
	res = (uint32_t)res;
	b = getByte() - 48;
	while (b<10)
	{
		res = res + (double)b/divider;
		b = getByte() - 48;
		divider *= 10;
	}
	if (neg) res = 0-res;
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
	out.printUInt64(dat); return out;
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
	out.printInt64(dat); return out;
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


void usart_mem::sendByte(uint8_t dat)
{
	if (dat == 27) counter = 0; //escape = return to front
	else if (dat != 0)
	{
		stream[counter] = dat;
		++counter;
		if (counter == size) counter = 0;
	}
}

uint8_t usart_mem::getByte()
{
	if (stream[counter == 27]) counter = 0;
	uint8_t res = stream[counter];
	++counter;
	if (counter == size) counter = 0;
	return res;
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

void usart1::initTX(uint32_t baud, uint_fast8_t remap)
{
	if (remap)
	{
		//enable GPIOB | USART1 |alt func
		_RCC_(RCC_APB2ENR) |= RCC_APB2ENR_IOPBEN | RCC_APB2ENR_USART1EN | RCC_APB2ENR_AFIOEN;
		//remap the pins
		_AFIO_(AFIO_MAPR) |= AFIO_MAPR_USART1_REMAP;
		//configure pins; TX(PB6) alt push-pull output
		pinB6_Output_AFPP_50(); //these are in gpio_func header
	}
	else
	{
		//enable GPIOA | USART1 |alt func
		_RCC_(RCC_APB2ENR) |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_USART1EN | RCC_APB2ENR_AFIOEN;
		//configure pins; TX(PA9) alt push-pull output
		pinA9_Output_AFPP_50(); //these are in gpio_func header
	}

	//set speed
	_USART1_(USART_BRR) = APB2SPEED/baud;
	//enable USART
	_USART1_(USART_CR1) |= USART_CR1_UE;
	//enable TX and RX
	_USART1_(USART_CR1) |= USART_CR1_TE;
}

void usart1::initRX(uint32_t baud, uint_fast8_t remap)
{
	if (remap)
	{
		//enable GPIOB | USART1 |alt func
		_RCC_(RCC_APB2ENR) |= RCC_APB2ENR_IOPBEN | RCC_APB2ENR_USART1EN | RCC_APB2ENR_AFIOEN;
		//remap the pins
		_AFIO_(AFIO_MAPR) |= AFIO_MAPR_USART1_REMAP;
		//configure pins; RX(PB7) input
		pinB7_Input();
	}
	else
	{
		//enable GPIOA | USART1 |alt func
		_RCC_(RCC_APB2ENR) |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_USART1EN | RCC_APB2ENR_AFIOEN;
		//configure pins; RX(PA10) input
		pinA10_Input();
	}

	//set speed
	_USART1_(USART_BRR) = APB2SPEED/baud;
	//enable USART
	_USART1_(USART_CR1) |= USART_CR1_UE;
	//enable TX and RX
	_USART1_(USART_CR1) |= USART_CR1_RE;
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

void usart1::IRQenable(uint16_t irqs)
{
	IRQ_32TO63_SER |= IRQ_USART1;
	_USART1_(USART_CR1) &= ~0x01F0; //clear interrupt enables
	_USART1_(USART_CR3) &= ~0x0401; //clear interrupt enables
	_USART1_(USART_CR1) |= (irqs & 0x01F0); //set particular bits
	_USART1_(USART_CR3) |= (irqs & 0x0401); //set particular bits
}

void usart1::sendStreamDMA(uint8_t* dat, uint16_t size)
{
	DMATXenable();
	//channel 4 (TX), paddr, maddr, num,  ccr = high pri, 8 bit mem, 8 bit periph, memory increments, non-circular
	//mem2per
	dma1_setup( 4, //0x40013804,
				(uint32_t)&(_USART1_(USART_DR)),
				(uint32_t)dat,
				size,
				(uint16_t)(DMA_PLHIGH | DMA_MSIZE8 | DMA_PSIZE8 | DMA_CCR_MINC | DMA_CCR_DIR));
	while(!(_USART1_(USART_SR) & USART_SR_TC));
	dma1_enable(4);
}


void usart1::getStreamDMA(uint8_t* dat, uint16_t size)
{
	DMARXenable();
	//channel 5 (RX), paddr, maddr, num,  ccr = high pri, 8 bit mem, 8 bit periph, memory increments, non-circular
	dma1_setup( 5, //0x40013804,
				(uint32_t)&(_USART1_(USART_DR)),
				(uint32_t)dat,
				size,
				(uint16_t)(DMA_PLHIGH | DMA_MSIZE8 | DMA_PSIZE8 | DMA_CCR_MINC));
	dma1_enable(5);
}

void usart1::startTX(uint8_t* dat, uint16_t size, uint16_t pri)
{
	DMATXenable();
	//channel 4 (TX), paddr, maddr, num,  ccr = pri, 8 bit mem, 8 bit periph, memory increments, from mem, circular
	dma1_setup( 4, //0x40013804,
				(uint32_t)&(_USART1_(USART_DR)),
				(uint32_t)dat,
				size,
				(uint16_t)(pri | DMA_MSIZE8 | DMA_PSIZE8 | DMA_CCR_MINC | DMA_CCR_DIR | DMA_CCR_CIRC));
	while(!(_USART1_(USART_SR) & USART_SR_TC));
	dma1_enable(4);
}

void usart1::startRX(uint8_t* dat, uint16_t size, uint16_t pri)
{
	DMARXenable();
	//channel 5 (RX), paddr, maddr, num,  ccr = pri, 8 bit mem, 8 bit periph, memory increments, circular
	dma1_setup( 5, //0x40013804,
				(uint32_t)&(_USART1_(USART_DR)),
				(uint32_t)dat,
				size,
				(uint16_t)(pri | DMA_MSIZE8 | DMA_PSIZE8 | DMA_CCR_MINC | DMA_CCR_CIRC));
	dma1_enable(5);
}

void usart1::stopTX() {dma1_disable(4); DMATXdisable();}
void usart1::stopRX() {dma1_disable(5); DMARXdisable();}


void usart2::init(uint32_t baud, uint_fast8_t remap)
{
	/*if (remap)
	{
		//enable GPIOB | USART2 |alt func
		_RCC_(RCC_APB2ENR) |= RCC_APB2ENR_IOPBEN | RCC_APB2ENR_USART1EN | RCC_APB2ENR_AFIOEN;
		//remap the pins
		_AFIO_(AFIO_MAPR) |= AFIO_MAPR_USART2_REMAP;
		//configure pins; TX(PB6) alt push-pull output; RX(PB7) input
		pinB6_Output_AFPP_50(); //these are in gpio_func header
		pinB7_Input();
	}
	else*/
	{
		//enable GPIOA | USART1 |alt func
		_RCC_(RCC_APB2ENR) |= RCC_APB2ENR_IOPAEN |  RCC_APB2ENR_AFIOEN;
		_RCC_(RCC_APB1ENR) |= RCC_APB1ENR_USART2EN;
		//configure pins; TX(PA2) alt push-pull output; RX(PA3) input
		pinA2_Output_AFPP_50(); //these are in gpio_func header
		pinA3_Input();
	}

	//set speed
	_USART2_(USART_BRR) = APB1SPEED/baud;
	//enable USART
	_USART2_(USART_CR1) |= USART_CR1_UE;
	//enable TX and RX
	_USART2_(USART_CR1) |= USART_CR1_TE | USART_CR1_RE;
}

void usart2::initTX(uint32_t baud, uint_fast8_t remap)
{
	/*if (remap)
	{
		//enable GPIOB | USART2 |alt func
		_RCC_(RCC_APB2ENR) |= RCC_APB2ENR_IOPBEN | RCC_APB2ENR_USART1EN | RCC_APB2ENR_AFIOEN;
		//remap the pins
		_AFIO_(AFIO_MAPR) |= AFIO_MAPR_USART2_REMAP;
		//configure pins; TX(PB6) alt push-pull output;
		pinB6_Output_AFPP_50(); //these are in gpio_func header
	}
	else*/
	{
		//enable GPIOA | USART1 |alt func
		_RCC_(RCC_APB2ENR) |= RCC_APB2ENR_IOPAEN |  RCC_APB2ENR_AFIOEN;
		_RCC_(RCC_APB1ENR) |= RCC_APB1ENR_USART2EN;
		//configure pins; TX(PA2) alt push-pull output
		pinA2_Output_AFPP_50(); //these are in gpio_func header
	}

	//set speed
	_USART2_(USART_BRR) = APB1SPEED/baud;
	//enable USART
	_USART2_(USART_CR1) |= USART_CR1_UE;
	//enable TX and RX
	_USART2_(USART_CR1) |= USART_CR1_TE;
}

void usart2::initRX(uint32_t baud, uint_fast8_t remap)
{
	/*if (remap)
	{
		//enable GPIOB | USART2 |alt func
		_RCC_(RCC_APB2ENR) |= RCC_APB2ENR_IOPBEN | RCC_APB2ENR_USART1EN | RCC_APB2ENR_AFIOEN;
		//remap the pins
		_AFIO_(AFIO_MAPR) |= AFIO_MAPR_USART2_REMAP;
		//configure pins; RX(PB7) input
		pinB7_Input();
	}
	else*/
	{
		//enable GPIOA | USART1 |alt func
		_RCC_(RCC_APB2ENR) |= RCC_APB2ENR_IOPAEN |  RCC_APB2ENR_AFIOEN;
		_RCC_(RCC_APB1ENR) |= RCC_APB1ENR_USART2EN;
		//configure pins; RX(PA3) input
		pinA3_Input();
	}

	//set speed
	_USART2_(USART_BRR) = APB1SPEED/baud;
	//enable USART
	_USART2_(USART_CR1) |= USART_CR1_UE;
	//enable TX and RX
	_USART2_(USART_CR1) |= USART_CR1_RE;
}


void usart2::sendByte(uint8_t dat)
{
	while(!(_USART2_(USART_SR) & USART_SR_TC));
	_USART2_(USART_DR) = dat;
}

uint8_t usart2::getByte()
{
	uint8_t res;
	while(!(_USART2_(USART_SR) & USART_SR_RXNE));
	res = _USART2_(USART_DR);
	return res;
}

void usart2::IRQenable(uint16_t irqs)
{
	IRQ_32TO63_SER |= IRQ_USART2;
	_USART2_(USART_CR1) &= ~0x01F0; //clear interrupt enables
	_USART2_(USART_CR3) &= ~0x0401; //clear interrupt enables
	_USART2_(USART_CR1) |= (irqs & 0x01F0); //set particular bits
	_USART2_(USART_CR3) |= (irqs & 0x0401); //set particular bits
}

void usart2::sendStreamDMA(uint8_t* dat, uint16_t size)
{
	DMATXenable();
	//channel 7 (TX), paddr, maddr, num,  ccr = high pri, 8 bit mem, 8 bit periph, memory increments, non-circular
	//mem2per
	dma1_setup( 7,
				(uint32_t)&(_USART2_(USART_DR)),
				(uint32_t)dat,
				size,
				(uint16_t)(DMA_PLHIGH | DMA_MSIZE8 | DMA_PSIZE8 | DMA_CCR_MINC | DMA_CCR_DIR));
	while(!(_USART2_(USART_SR) & USART_SR_TC));
	dma1_enable(7);
}


void usart2::getStreamDMA(uint8_t* dat, uint16_t size)
{
	DMARXenable();
	//channel 6 (RX), paddr, maddr, num,  ccr = high pri, 8 bit mem, 8 bit periph, memory increments, non-circular
	dma1_setup( 6,
				(uint32_t)&(_USART2_(USART_DR)),
				(uint32_t)dat,
				size,
				(uint16_t)(DMA_PLHIGH | DMA_MSIZE8 | DMA_PSIZE8 | DMA_CCR_MINC));
	dma1_enable(6);
}

void usart2::startTX(uint8_t* dat, uint16_t size, uint16_t pri)
{
	DMATXenable();
	//channel 7 (TX), paddr, maddr, num,  ccr = pri, 8 bit mem, 8 bit periph, memory increments, from mem, circular
	dma1_setup( 7,
				(uint32_t)&(_USART2_(USART_DR)),
				(uint32_t)dat,
				size,
				(uint16_t)(pri | DMA_MSIZE8 | DMA_PSIZE8 | DMA_CCR_MINC | DMA_CCR_DIR | DMA_CCR_CIRC));
	while(!(_USART2_(USART_SR) & USART_SR_TC));
	dma1_enable(7);
}

void usart2::startRX(uint8_t* dat, uint16_t size, uint16_t pri)
{
	DMARXenable();
	//channel 6 (RX), paddr, maddr, num,  ccr = pri, 8 bit mem, 8 bit periph, memory increments, circular
	dma1_setup( 6,
				(uint32_t)&(_USART2_(USART_DR)),
				(uint32_t)dat,
				size,
				(uint16_t)(pri | DMA_MSIZE8 | DMA_PSIZE8 | DMA_CCR_MINC | DMA_CCR_CIRC));
	dma1_enable(6);
}

void usart2::stopTX() {dma1_disable(4); DMATXdisable();}
void usart2::stopRX() {dma1_disable(5); DMARXdisable();}

void usart3::init(uint32_t baud, uint_fast8_t remap)
{
	/*if (remap)
	{
		//enable GPIOB | USART1 |alt func
		_RCC_(RCC_APB2ENR) |= RCC_APB2ENR_IOPBEN | RCC_APB2ENR_USART1EN | RCC_APB2ENR_AFIOEN;
		//remap the pins
		_AFIO_(AFIO_MAPR) |= AFIO_MAPR_USART3_REMAP;
		//configure pins; TX(PB6) alt push-pull output; RX(PB7) input
		pinB6_Output_AFPP_50(); //these are in gpio_func header
		pinB7_Input();
	}
	else*/
	{
		//enable GPIOA | USART3 |alt func
		_RCC_(RCC_APB2ENR) |= RCC_APB2ENR_IOPBEN |  RCC_APB2ENR_AFIOEN;
		_RCC_(RCC_APB1ENR) |= RCC_APB1ENR_USART3EN;
		//configure pins; TX(PB10) alt push-pull output; RX(PB11) input
		pinB10_Output_AFPP_50(); //these are in gpio_func header
		pinB11_Input();
	}

	//set speed
	_USART3_(USART_BRR) = APB1SPEED/baud;
	//enable USART
	_USART3_(USART_CR1) |= USART_CR1_UE;
	//enable TX and RX
	_USART3_(USART_CR1) |= USART_CR1_TE | USART_CR1_RE;
}

void usart3::initTX(uint32_t baud, uint_fast8_t remap)
{
	/*if (remap)
	{
		//enable GPIOB | USART1 |alt func
		_RCC_(RCC_APB2ENR) |= RCC_APB2ENR_IOPBEN | RCC_APB2ENR_USART1EN | RCC_APB2ENR_AFIOEN;
		//remap the pins
		_AFIO_(AFIO_MAPR) |= AFIO_MAPR_USART3_REMAP;
		//configure pins; TX(PB6) alt push-pull output
		pinB6_Output_AFPP_50(); //these are in gpio_func header
	}
	else*/
	{
		//enable GPIOA | USART3 |alt func
		_RCC_(RCC_APB2ENR) |= RCC_APB2ENR_IOPBEN |  RCC_APB2ENR_AFIOEN;
		_RCC_(RCC_APB1ENR) |= RCC_APB1ENR_USART3EN;
		//configure pins; TX(PB10) alt push-pull output
		pinB10_Output_AFPP_50(); //these are in gpio_func header
	}

	//set speed
	_USART3_(USART_BRR) = APB1SPEED/baud;
	//enable USART
	_USART3_(USART_CR1) |= USART_CR1_UE;
	//enable TX and RX
	_USART3_(USART_CR1) |= USART_CR1_TE;
}

void usart3::initRX(uint32_t baud, uint_fast8_t remap)
{
	/*if (remap)
	{
		//enable GPIOB | USART1 |alt func
		_RCC_(RCC_APB2ENR) |= RCC_APB2ENR_IOPBEN | RCC_APB2ENR_USART1EN | RCC_APB2ENR_AFIOEN;
		//remap the pins
		_AFIO_(AFIO_MAPR) |= AFIO_MAPR_USART3_REMAP;
		//configure pins; RX(PB7) input
		pinB7_Input();
	}
	else*/
	{
		//enable GPIOA | USART3 |alt func
		_RCC_(RCC_APB2ENR) |= RCC_APB2ENR_IOPBEN |  RCC_APB2ENR_AFIOEN;
		_RCC_(RCC_APB1ENR) |= RCC_APB1ENR_USART3EN;
		//configure pins; RX(PB11) input
		pinB11_Input();
	}

	//set speed
	_USART3_(USART_BRR) = APB1SPEED/baud;
	//enable USART
	_USART3_(USART_CR1) |= USART_CR1_UE;
	//enable TX and RX
	_USART3_(USART_CR1) |= USART_CR1_RE;
}

void usart3::sendByte(uint8_t dat)
{
	while(!(_USART3_(USART_SR) & USART_SR_TC));
	_USART3_(USART_DR) = dat;
}

uint8_t usart3::getByte()
{
	uint8_t res;
	while(!(_USART3_(USART_SR) & USART_SR_RXNE));
	res = _USART3_(USART_DR);
	return res;
}

void usart3::IRQenable(uint16_t irqs)
{
	IRQ_32TO63_SER |= IRQ_USART3;
	_USART3_(USART_CR1) &= ~0x01F0; //clear interrupt enables
	_USART3_(USART_CR3) &= ~0x0401; //clear interrupt enables
	_USART3_(USART_CR1) |= (irqs & 0x01F0); //set particular bits
	_USART3_(USART_CR3) |= (irqs & 0x0401); //set particular bits
}

void usart3::sendStreamDMA(uint8_t* dat, uint16_t size)
{
	DMATXenable();
	//channel 2 (TX), paddr, maddr, num,  ccr = high pri, 8 bit mem, 8 bit periph, memory increments, non-circular
	//mem2per
	dma1_setup( 2, //0x40013804,
				(uint32_t)&(_USART3_(USART_DR)),
				(uint32_t)dat,
				size,
				(uint16_t)(DMA_PLHIGH | DMA_MSIZE8 | DMA_PSIZE8 | DMA_CCR_MINC | DMA_CCR_DIR));
	while(!(_USART3_(USART_SR) & USART_SR_TC));
	dma1_enable(2);
}


void usart3::getStreamDMA(uint8_t* dat, uint16_t size)
{
	DMARXenable();
	//channel 3 (RX), paddr, maddr, num,  ccr = high pri, 8 bit mem, 8 bit periph, memory increments, non-circular
	dma1_setup( 3, //0x40013804,
				(uint32_t)&(_USART3_(USART_DR)),
				(uint32_t)dat,
				size,
				(uint16_t)(DMA_PLHIGH | DMA_MSIZE8 | DMA_PSIZE8 | DMA_CCR_MINC));
	dma1_enable(3);
}

void usart3::startTX(uint8_t* dat, uint16_t size, uint16_t pri)
{
	DMATXenable();
	//channel 2 (TX), paddr, maddr, num,  ccr = pri, 8 bit mem, 8 bit periph, memory increments, from mem, circular
	dma1_setup( 2, //0x40013804,
				(uint32_t)&(_USART3_(USART_DR)),
				(uint32_t)dat,
				size,
				(uint16_t)(pri | DMA_MSIZE8 | DMA_PSIZE8 | DMA_CCR_MINC | DMA_CCR_DIR | DMA_CCR_CIRC));
	while(!(_USART3_(USART_SR) & USART_SR_TC));
	dma1_enable(2);
}

void usart3::startRX(uint8_t* dat, uint16_t size, uint16_t pri)
{
	DMARXenable();
	//channel 3 (RX), paddr, maddr, num,  ccr = pri, 8 bit mem, 8 bit periph, memory increments, circular
	dma1_setup( 3, //0x40013804,
				(uint32_t)&(_USART3_(USART_DR)),
				(uint32_t)dat,
				size,
				(uint16_t)(pri | DMA_MSIZE8 | DMA_PSIZE8 | DMA_CCR_MINC | DMA_CCR_CIRC));
	dma1_enable(3);
}

void usart3::stopTX() {dma1_disable(4); DMATXdisable();}
void usart3::stopRX() {dma1_disable(5); DMARXdisable();}

char hexChar(uint8_t val)
{
	char c;
	if (val > 9) c = val + 55;
	else c = val + 48;
	return c;
}
