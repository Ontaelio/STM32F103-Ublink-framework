/*
 * STM32F103 ADC functions library
 * Part of STM32F103 register and peripherals library
 *
 * Documentation available in the provided MD file.
 *
 * (c) 2020 Dmitry Reznikov ontaelio(at)gmail.com
 *
 * Can be freely used according to the GNU GPL license.
 */

#include <stm32f103_adc.h>

/******* BASIC MODE, ADC2 **********/

void analog_pin::init(uint8_t cycles)
{
	adc2_init();
	if (cnum<10) _ADC2_(ADC_SMPR2) |= cycles << (cnum*3); //no need to enable GPIO
	else _ADC2_(ADC_SMPR1) |= cycles << ((cnum-10)*3);
}

uint16_t analog_pin::read()
{
	_ADC2_(ADC_SQR3) = cnum; //set the channel as the first regular conversion
	_ADC2_(ADC_CR2) |= ADC_CR2_ADON; //start regular conversion
	while(!(_ADC2_(ADC_SR) & ADC_SR_EOC)); // wait for conversion to complete
	uint32_t res = _ADC2_(ADC_DR);
	return (uint16_t)(res & 0xFFFF);
}

/******* CONTINUOUS MODE, ADC1 and ADC2 **********/

void analog_cont::init(uint8_t cycles)
{
	uint32_t* chkaddr = (uint32_t *)0x40012400;
	if (adc == chkaddr) adc1_init(); else adc2_init();

	if (cnum < 10) *(adc + ADC_SMPR2/4) |= cycles << (cnum*3); // set the conversion speed
	else *(adc + ADC_SMPR1/4) |= cycles << ((cnum-10)*3);
	//*(adc + ADC_SQR3/4) = cnum; // set the channel as the first regular conversion
	//*(adc + ADC_CR2/4) |= ADC_CR2_CONT; // setup continuous mode
	//*(adc + ADC_CR2/4) |= ADC_CR2_ADON; // start regular conversion
	//while(!(*(adc) & ADC_SR_EOC)); // ADC_SR = 0, wait for first conversion to complete
}

void analog_cont::start()
{
	*(adc + ADC_SQR3/4) = cnum; // set the channel as the first regular conversion
	*(adc + ADC_CR2/4) |= ADC_CR2_CONT; // setup continuous mode
	*(adc + ADC_CR2/4) |= ADC_CR2_ADON; // start regular conversion
	while(!(*(adc) & ADC_SR_EOC)); // ADC_SR = 0, wait for first conversion to complete
}

void analog_cont::injectInit(uint8_t jtrigger)
{
	*(adc + ADC_CR2/4) |= ADC_CR2_JEXTTRIG;
	*(adc + ADC_CR2/4) &= ~(ADC_CR2_JEXTSEL);
	*(adc + ADC_CR2/4) |= (jtrigger << 12); //set JEXTSEL
}

void analog_cont::injectWaitForResult()
{
	while (!(*(adc + ADC_SR/4) & ADC_SR_JEOC)) {}
	*(adc + ADC_SR/4) &= ~ADC_SR_JEOC;
}

void analog_cont::inject(uint8_t cha1)
{
	*(adc + ADC_JSQR/4) = cha1 << 15;
}

void analog_cont::inject(uint8_t cha1, uint8_t cha2)
{
	*(adc + ADC_JSQR/4) = (1 << 20) | (cha1 << 10) | (cha2 << 15);
}

void analog_cont::inject(uint8_t cha1, uint8_t cha2, uint8_t cha3)
{
	*(adc + ADC_JSQR/4) = (2 << 20) | (cha1 << 5) | (cha2 << 10) | (cha3 << 15);
}

void analog_cont::inject(uint8_t cha1, uint8_t cha2, uint8_t cha3, uint8_t cha4)
{
	*(adc + ADC_JSQR/4) = (2 << 20) | (cha1) | (cha2 << 5) | (cha3 << 10) | (cha4 << 15);
}

void analog_cont::injectStart(uint_fast8_t dowait)
{
	*(adc + ADC_CR2/4) |= ADC_CR2_JSWSTART;
	if (dowait) injectWaitForResult();
}

uint16_t analog_cont::injectRead(uint_fast8_t jcha)
{
	uint16_t res = *(adc + 0x38/4 + jcha*4);
	return res;
}

/******* SCAN MODE, ADC1 **********/

void analog_scan::init(uint16_t* targ, uint_fast8_t num, ...)
{
	adc1_init();
	va_list vl;
	va_start(vl, num);

	//setup DMA channel 1
	dma1_init();
	_DMA1_(DMA_CCR1) &= ~(DMA_CCR_EN);
	_DMA1_(DMA_CPAR1) = 0x40012400 + ADC_DR;
	_DMA1_(DMA_CMAR1) = (uint32_t)targ;
	_DMA1_(DMA_CNDTR1) = (uint16_t)num;
	//ccr = medium priority | 16 bit mem | 32 pit periphery | memory increment | circular
	_DMA1_(DMA_CCR1) = (uint16_t)(DMA_PLMEDIUM | DMA_MSIZE16 | DMA_PSIZE32 | DMA_CCR_MINC | DMA_CCR_CIRC);

	//enable SCAN
	_ADC1_(ADC_CR1) |= ADC_CR1_SCAN;
	//enable DMA
	_ADC1_(ADC_CR2) |= ADC_CR2_DMA;

	//clear SQRs and set the num of channels
	_ADC1_(ADC_SQR1) = (uint32_t)((num-1) << 20);
	_ADC1_(ADC_SQR2) = (uint32_t)0;
	_ADC1_(ADC_SQR3) = (uint32_t)0;

	//setup channels
	for (uint_fast8_t k = 0; k<num; k++)
	{
		if (k<7) _ADC1_(ADC_SQR3) |= (va_arg(vl, uint32_t))<<(k*5);
		else if (k<13) _ADC1_(ADC_SQR2) |= (va_arg(vl, uint32_t))<<((k-7)*5);
		else _ADC1_(ADC_SQR1) |= (va_arg(vl, uint32_t))<<((k-13)*5);
	}
	va_end(vl);

	_DMA1_(DMA_CCR1) |= DMA_CCR_EN;
}

void analog_scan::external(uint8_t regtrig)
{
	_ADC1_(ADC_CR2) &= ~(ADC_CR2_EXTSEL); //clear
	_ADC1_(ADC_CR2) |= ADC_CR2_EXTTRIG | regtrig << 17;
}

void analog_scan::speed(uint_fast8_t cha, uint8_t cycles)
{
	if (cha<10) {_ADC1_(ADC_SMPR2) &= ~(7 << cha*3);_ADC1_(ADC_SMPR2) |= cycles << (cha*3);}
	else {_ADC1_(ADC_SMPR1) &= ~(7 << (cha-10)*3);_ADC1_(ADC_SMPR2) |= cycles << ((cha-10)*3);}
}

void analog_scan::injectInit(uint8_t jtrigger)
{
	_ADC1_(ADC_CR2) &= ~(ADC_CR2_JEXTSEL);
	_ADC1_(ADC_CR2) |= (jtrigger << 12); //set JEXTSEL
	_ADC1_(ADC_CR2) |= ADC_CR2_JEXTTRIG; //enable trigger
}

void analog_scan::injectWaitForResult()
{
	while (!(_ADC1_(ADC_SR) & ADC_SR_JEOC)) {}
	_ADC1_(ADC_SR) &= ~ADC_SR_JEOC;
}

void analog_scan::inject(uint8_t cha1)
{
	_ADC1_(ADC_JSQR) = cha1 << 15;
}

void analog_scan::inject(uint8_t cha1, uint8_t cha2)
{
	_ADC1_(ADC_JSQR) = (1 << 20) | (cha1 << 10) | (cha2 << 15);
}

void analog_scan::inject(uint8_t cha1, uint8_t cha2, uint8_t cha3)
{
	_ADC1_(ADC_JSQR) = (2 << 20) | (cha1 << 5) | (cha2 << 10) | (cha3 << 15);
}

void analog_scan::inject(uint8_t cha1, uint8_t cha2, uint8_t cha3, uint8_t cha4)
{
	_ADC1_(ADC_JSQR) = (2 << 20) | (cha1) | (cha2 << 5) | (cha3 << 10) | (cha4 << 15);
}

void analog_scan::injectStart(uint_fast8_t dowait)
{
	_ADC1_(ADC_CR2) |= ADC_CR2_JSWSTART;
	if (dowait) injectWaitForResult();
}

uint16_t analog_scan::injectRead(uint_fast8_t jcha)
{
	uint16_t res = _ADC1_(0x38 + jcha*4);
	return res;
}

void adc1_init()
{
	if (_ADC1_(ADC_CR2) & ADC_CR2_ADON) return; //check if init() already done
	ADC1_CLOCK = 1;
	_ADC1_(ADC_CR2) |= ADC_CR2_ADON;
	delay_us(2); // 1us to power up ADC, second to make sure 2 cycles passed
	_ADC1_(ADC_CR2) |= ADC_CR2_CAL;
	while (_ADC1_(ADC_CR2) & ADC_CR2_CAL); //wait for calibration to finish
}

void adc2_init()
{
	if (_ADC2_(ADC_CR2) & ADC_CR2_ADON) return; //check if init() already done
	ADC2_CLOCK = 1;
	_ADC2_(ADC_CR2) |= ADC_CR2_ADON;
	delay_us(2); // 1us to power up ADC, second to make sure 2 cycles passed
	_ADC2_(ADC_CR2) |= ADC_CR2_CAL;
	while (_ADC2_(ADC_CR2) & ADC_CR2_CAL); //wait for calibration to finish
}

void adc1_watchdog(uint32_t low, uint32_t high)
{
	_ADC1_(ADC_LTR) = low;
	_ADC1_(ADC_HTR) = high;
	_ADC1_(ADC_CR1) &= ~(ADC_CR1_AWDSGL);
	_ADC1_(ADC_CR1) |= ADC_CR1_AWDEN;
}

void adc1_watchdog(uint8_t cha, uint32_t low, uint32_t high)
{
	_ADC1_(ADC_LTR) = low;
	_ADC1_(ADC_HTR) = high;
	_ADC1_(ADC_CR1) &= ~(0x0000001F);
	_ADC1_(ADC_CR1) |= ADC_CR1_AWDSGL | ADC_CR1_AWDEN | cha;
}

void adc1_injectWatchdog(uint32_t low, uint32_t high)
{
	_ADC1_(ADC_LTR) = low;
	_ADC1_(ADC_HTR) = high;
	_ADC1_(ADC_CR1) &= ~(ADC_CR1_AWDSGL);
	_ADC1_(ADC_CR1) |= ADC_CR1_JAWDEN;
}

void adc1_injectWatchdog(uint8_t cha, uint32_t low, uint32_t high)
{
	_ADC1_(ADC_LTR) = low;
	_ADC1_(ADC_HTR) = high;
	_ADC1_(ADC_CR1) &= ~(0x0000001F);
	_ADC1_(ADC_CR1) |= ADC_CR1_AWDSGL | ADC_CR1_JAWDEN | cha;
}

void adc2_watchdog(uint32_t low, uint32_t high)
{
	_ADC2_(ADC_LTR) = low;
	_ADC2_(ADC_HTR) = high;
	_ADC2_(ADC_CR1) &= ~(ADC_CR1_AWDSGL);
	_ADC2_(ADC_CR1) |= ADC_CR1_AWDEN;
}

void adc2_watchdog(uint8_t cha, uint32_t low, uint32_t high)
{
	_ADC2_(ADC_LTR) = low;
	_ADC2_(ADC_HTR) = high;
	_ADC2_(ADC_CR1) &= ~(0x0000001F);
	_ADC2_(ADC_CR1) |= ADC_CR1_AWDSGL | ADC_CR1_AWDEN | cha;
}

void adc2_injectWatchdog(uint32_t low, uint32_t high)
{
	_ADC2_(ADC_LTR) = low;
	_ADC2_(ADC_HTR) = high;
	_ADC2_(ADC_CR1) &= ~(ADC_CR1_AWDSGL);
	_ADC2_(ADC_CR1) |= ADC_CR1_JAWDEN;
}

void adc2_injectWatchdog(uint8_t cha, uint32_t low, uint32_t high)
{
	_ADC2_(ADC_LTR) = low;
	_ADC2_(ADC_HTR) = high;
	_ADC2_(ADC_CR1) &= ~(0x0000001F);
	_ADC2_(ADC_CR1) |= ADC_CR1_AWDSGL | ADC_CR1_JAWDEN | cha;
}
