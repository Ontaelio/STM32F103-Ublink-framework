/*
 * STM32F103 Timers and IRQ library source file
 * Part of STM32F103 register and peripherals library
 *
 * Dpcumentation available in the provided MD file.
 *
 * (c) 2019 Dmitry Reznikov ontaelio(at)gmail.com
 *
 * Can be freely used according to the GNU GPL license.
 */

#include <stm32f103_gpio.h>
#include <stm32f103_timers_reg.h>
#include <stm32f103_gpio_reg.h>
#include <stm32f103_timers.h>

void delay_ms(uint32_t msecs)
{
	++msecs;
	SYSTICK_RVR = 9000; //external clock from RCC at 9 MHz
	SYSTICK_CURVAL = 321; //anything
	SYSTICK_CSR = 0x00000001; //external clock, enable
	while(--msecs)
		while (!(SYSTICK_CSR & SYSTICK_CSR_COUNTFLAG)) {}
	SYSTICK_CSR = 0;
}

void delay_us(uint32_t msecs)
{
	++msecs;
	SYSTICK_RVR = 72; //HCLK at 72MHz
	SYSTICK_CURVAL = 321; //anything
	SYSTICK_CSR |= 0x00000005; //internal clock, enable
	while(--msecs)
		while (!(SYSTICK_CSR & SYSTICK_CSR_COUNTFLAG)) {}
	SYSTICK_CSR = 4;
}

void sysTick_start(uint32_t val, uint8_t intext)
{
	sysTick_stop();
	SYSTICK_RVR = val;
	SYSTICK_CURVAL = 321; //anything
	if (intext) SYSTICK_CSR |= SYSTICK_CSR_CLKSOURCE; else SYSTICK_CSR &= ~SYSTICK_CSR_CLKSOURCE;
	SYSTICK_CSR |= SYSTICK_CSR_ENABLE;
}

void irq_priority(uint8_t irq, uint8_t pri)
{
	uint8_t mo = irq & 0xFC;
	uint8_t offs = (irq & 3) * 8 + 4;
	uint32_t val = pri << offs;
	uint32_t c_val = 0xF << offs;
	IRQ_PRIORITY(mo) &= ~c_val;
	IRQ_PRIORITY(mo) |= val;
}

void irq_enable(uint8_t irq)
{
	switch (irq >> 5)
	{
	case 0: IRQ_0TO31_SER |= 1 << (irq&31); break;
	case 1: IRQ_32TO63_SER |= 1 << (irq&31); break;
	default: break;
	}
}

void irq_disable(uint8_t irq)
{
	switch (irq >> 5)
	{
	case 0: IRQ_0TO31_CER |= 1 << (irq&31); break;
	case 1: IRQ_32TO63_CER |= 1 << (irq&31); break;
	default: break;
	}
}


void timer::setCC1mode(uint16_t mode, uint8_t prld_en, uint8_t plrty, uint8_t oe)
{
	CCMR1 &= ~TIMX_CCMR1_OC1M; //clear
	CCMR1 |= (mode<<4) | (prld_en<<3); //set CC1 mode
	if (plrty) CCER |= TIMX_CCER_CC1P; else CCER &= ~(TIMX_CCER_CC1P);
	if (oe) CCER |= TIMX_CCER_CC1E; else CCER &= ~(TIMX_CCER_CC1E);
}

void timer::setCC2mode(uint16_t mode, uint8_t prld_en, uint8_t plrty, uint8_t oe)
{
	CCMR1 &= ~TIMX_CCMR1_OC2M; //clear
	CCMR1 |= mode<<12 | (prld_en<<11); //set CC1 mode
	if (plrty) CCER |= TIMX_CCER_CC2P; else CCER &= ~(TIMX_CCER_CC2P);
	if (oe) CCER |= TIMX_CCER_CC2E; else CCER &= ~(TIMX_CCER_CC2E);
}

void timer::setCC3mode(uint16_t mode, uint8_t prld_en, uint8_t plrty, uint8_t oe)
{
	CCMR2 &= ~TIMX_CCMR2_OC3M; //clear
	CCMR2 |= mode<<4 | (prld_en<<3); //set CC1 mode
	if (plrty) CCER |= TIMX_CCER_CC3P; else CCER &= ~(TIMX_CCER_CC3P);
	if (oe) CCER |= TIMX_CCER_CC3E; else CCER &= ~(TIMX_CCER_CC3E);
}

void timer::setCC4mode(uint16_t mode, uint8_t prld_en, uint8_t plrty, uint8_t oe)
{
	CCMR2 &= ~TIMX_CCMR2_OC4M; //clear
	CCMR2 |= mode<<12 | (prld_en<<11); //set CC1 mode
	if (plrty) CCER |= TIMX_CCER_CC4P; else CCER &= ~(TIMX_CCER_CC4P);
	if (oe) CCER |= TIMX_CCER_CC4E; else CCER &= ~(TIMX_CCER_CC4E);
}


void tim1_pwm::init(uint8_t opendrain)
{
	gpioA_init();

	if (opendrain)
	switch (channel)
	{
		case 1: pinA8_Output_AFOD_50(); break;
		case 2: pinA9_Output_AFOD_50(); break;
		case 3: pinA10_Output_AFOD_50(); break;
		case 4: pinA11_Output_AFOD_50(); break;
	}

	else

	switch (channel)
	{
		case 1: pinA8_Output_AFPP_50(); break;
		case 2: pinA9_Output_AFPP_50(); break;
		case 3: pinA10_Output_AFPP_50(); break;
		case 4: pinA11_Output_AFPP_50(); break;
	}


}

void tim1_pwm::enable()
{
	//disable timer
	_TIM1_(TIMX_CR1) = 0; //&= ~TIM1_CR1_CEN;

	ccmr = 0x68 | ((pwmMode - 1)<<4);
	cms_dir = centerMode<<5 | direction<<4;
	ccer = (polarity << 1) | 1;


	switch(channel)
	{
	case 1:
			//channel 1
			_TIM1_(TIMX_CCMR1) &= ~0x00FF; //clear
			_TIM1_(TIMX_CCMR1) |= ccmr;//0x68;//ccmr; //set
			_TIM1_(TIMX_CCER)  &= ~0x0003; //clear
			_TIM1_(TIMX_CCER)  |= ccer; //output on
			break;
	case 2:
			//channel 2
			_TIM1_(TIMX_CCMR1) &= ~0xFF00; //clear
			_TIM1_(TIMX_CCMR1) |= ccmr<<8; //set
			_TIM1_(TIMX_CCER)  &= ~0x0030; //clear
			_TIM1_(TIMX_CCER)  |= ccer<<4; //output on
			break;
	case 3:
			//channel 3
			_TIM1_(TIMX_CCMR2) &= ~0x00FF; //clear
			_TIM1_(TIMX_CCMR2) |= ccmr; //set
			_TIM1_(TIMX_CCER)  &= ~0x0300; //clear
			_TIM1_(TIMX_CCER)  |= ccer<<8; //output on
			break;
	case 4:
			//channel 4
			_TIM1_(TIMX_CCMR2) &= ~0xFF00; //clear
			_TIM1_(TIMX_CCMR2) |= ccmr<<8; //set
			_TIM1_(TIMX_CCER)  &= ~0x3000; //clear
			_TIM1_(TIMX_CCER)  |= ccer<<12; //output on
			break;
	}

	//setup timer
	_TIM1_(TIMX_PSC) = prescaler; //prescaler
	_TIM1_(TIMX_ARR) = depth; //prescaler
	_TIM1_(TIMX_CR1) = TIMX_CR1_ARPE; //set preload and clear the rest
	_TIM1_(TIMX_CR1) |= cms_dir; //set center mode and direction

	//reset counters
	_TIM1_(TIMX_EGR) |= TIMX_EGR_UG;
	_TIM1_(TIMX_BDTR) |= TIMX_BDTR_MOE;// | TIMX_BDTR_OSSI;
	//enable
	//_TIM1_(TIMX_CR1) |= TIMX_CR1_CEN;
	BB_TIM1_CR1_CEN = 1;
}

void tim2_pwm::init(uint8_t opendrain)
{
	uint8_t remap = (_AFIO_(AFIO_MAPR) & AFIO_MAPR_TIM2_REMAP) >> 8;
	gpioA_init();
	if (remap) gpioB_init();

	if (opendrain)
	switch (channel)
	{
		case 1: if (remap&1) pinA15_Output_AFOD_50(); else pinA0_Output_AFOD_50(); break;
		case 2: if (remap&1) pinB3_Output_AFOD_50(); else pinA1_Output_AFOD_50(); break;
		case 3: if (remap&2) pinB10_Output_AFOD_50(); else pinA2_Output_AFOD_50(); break;
		case 4: if (remap&2) pinB11_Output_AFOD_50(); else pinA3_Output_AFOD_50(); break;
	}

	else

	switch (channel)
	{
		case 1: if (remap&1) pinA15_Output_AFPP_50(); else pinA0_Output_AFPP_50(); break;
		case 2: if (remap&1) pinB3_Output_AFPP_50(); else pinA1_Output_AFPP_50(); break;
		case 3: if (remap&2) pinB10_Output_AFPP_50(); else pinA2_Output_AFPP_50(); break;
		case 4: if (remap&2) pinB11_Output_AFPP_50(); else pinA3_Output_AFPP_50(); break;
	}

}

void tim2_pwm::enable()
{
	//disable timer
	_TIM2_(TIMX_CR1) = 0; //&= ~TIM2_CR1_CEN;

	ccmr = 0x68 | (pwmMode - 1)<<4;
	cms_dir = centerMode<<5 | direction<<4;
	ccer = (polarity << 1) | 1;


	switch(channel)
	{
	case 1:
			//channel 1
			_TIM2_(TIMX_CCMR1) &= ~0x00FF; //clear
			_TIM2_(TIMX_CCMR1) |= ccmr; //set
			_TIM2_(TIMX_CCER)  &= ~0x0003; //clear
			_TIM2_(TIMX_CCER)  |= ccer; //output on
			break;
	case 2:
			//channel 2
			_TIM2_(TIMX_CCMR1) &= ~0xFF00; //clear
			_TIM2_(TIMX_CCMR1) |= ccmr<<8; //set
			_TIM2_(TIMX_CCER)  &= ~0x0030; //clear
			_TIM2_(TIMX_CCER)  |= ccer<<4; //output on
			break;
	case 3:
			//channel 3
			_TIM2_(TIMX_CCMR2) &= ~0x00FF; //clear
			_TIM2_(TIMX_CCMR2) |= ccmr; //set
			_TIM2_(TIMX_CCER)  &= ~0x0300; //clear
			_TIM2_(TIMX_CCER)  |= ccer<<8; //output on
			break;
	case 4:
			//channel 4
			_TIM2_(TIMX_CCMR2) &= ~0xFF00; //clear
			_TIM2_(TIMX_CCMR2) |= ccmr<<8; //set
			_TIM2_(TIMX_CCER)  &= ~0x3000; //clear
			_TIM2_(TIMX_CCER)  |= ccer<<12; //output on
			break;
	}

	//setup timer
	_TIM2_(TIMX_PSC) = prescaler; //prescaler
	_TIM2_(TIMX_ARR) = depth; //prescaler
	_TIM2_(TIMX_CR1) = TIMX_CR1_ARPE; //set preload and clear the rest
	_TIM2_(TIMX_CR1) |= cms_dir; //set center mode and direction

	//reset counters
	_TIM2_(TIMX_EGR) |= TIMX_EGR_UG;

	//enable
	//_TIM2_(TIMX_CR1) |= TIMX_CR1_CEN;
	BB_TIM2_CR1_CEN = 1;
}

void tim3_pwm::init(uint8_t opendrain)
{
	uint8_t remap = (_AFIO_(AFIO_MAPR) & AFIO_MAPR_TIM3_REMAP) >> 8;
	gpioB_init();
	if (!remap) gpioA_init();

	if (opendrain)
	switch (channel)
	{
		case 1: if (remap&2) pinB4_Output_AFOD_50(); else pinA6_Output_AFOD_50(); break;
		case 2: if (remap&2) pinB5_Output_AFOD_50(); else pinA7_Output_AFOD_50(); break;
		case 3: pinB0_Output_AFOD_50(); break;
		case 4: pinB1_Output_AFOD_50(); break;
	}

	else
	switch (channel)
	{
		case 1: if (remap&2) pinB4_Output_AFPP_50(); else pinA6_Output_AFPP_50(); break;
		case 2: if (remap&2) pinB5_Output_AFPP_50(); else pinA7_Output_AFPP_50(); break;
		case 3: pinB0_Output_AFPP_50(); break;
		case 4: pinB1_Output_AFPP_50(); break;
	}
}

void tim3_pwm::enable()
{
	//disable timer
	_TIM3_(TIMX_CR1) = 0; //&= ~TIM3_CR1_CEN;

	ccmr = 0x68 | (pwmMode - 1)<<4;
	cms_dir = centerMode<<5 | direction<<4;
	ccer = (polarity << 1) | 1;


	switch(channel)
	{
	case 1:
			//channel 1
			_TIM3_(TIMX_CCMR1) &= ~0x00FF; //clear
			_TIM3_(TIMX_CCMR1) |= ccmr; //set
			_TIM3_(TIMX_CCER)  &= ~0x0003; //clear
			_TIM3_(TIMX_CCER)  |= ccer; //output on
			break;
	case 2:
			//channel 2
			_TIM3_(TIMX_CCMR1) &= ~0xFF00; //clear
			_TIM3_(TIMX_CCMR1) |= ccmr<<8; //set
			_TIM3_(TIMX_CCER)  &= ~0x0030; //clear
			_TIM3_(TIMX_CCER)  |= ccer<<4; //output on
			break;
	case 3:
			//channel 3
			_TIM3_(TIMX_CCMR2) &= ~0x00FF; //clear
			_TIM3_(TIMX_CCMR2) |= ccmr; //set
			_TIM3_(TIMX_CCER)  &= ~0x0300; //clear
			_TIM3_(TIMX_CCER)  |= ccer<<8; //output on
			break;
	case 4:
			//channel 4
			_TIM3_(TIMX_CCMR2) &= ~0xFF00; //clear
			_TIM3_(TIMX_CCMR2) |= ccmr<<8; //set
			_TIM3_(TIMX_CCER)  &= ~0x3000; //clear
			_TIM3_(TIMX_CCER)  |= ccer<<12; //output on
			break;
	}

	//setup timer
	_TIM3_(TIMX_PSC) = prescaler; //prescaler
	_TIM3_(TIMX_ARR) = depth; //prescaler
	_TIM3_(TIMX_CR1) = TIMX_CR1_ARPE; //set preload and clear the rest
	_TIM3_(TIMX_CR1) |= cms_dir; //set center mode and direction

	//reset counters
	_TIM3_(TIMX_EGR) |= TIMX_EGR_UG;

	//enable
	//_TIM3_(TIMX_CR1) |= TIMX_CR1_CEN;
	BB_TIM3_CR1_CEN = 1;
}

void tim4_pwm::init(uint8_t opendrain)
{
	gpioB_init();

	if (opendrain)
	switch (channel)
	{
		case 1: pinB6_Output_AFOD_50(); break;
		case 2: pinB7_Output_AFOD_50(); break;
		case 3: pinB8_Output_AFOD_50(); break;
		case 4: pinB9_Output_AFOD_50(); break;
	}
	else
	switch (channel)
	{
		case 1: pinB6_Output_AFPP_50(); break;
		case 2: pinB7_Output_AFPP_50(); break;
		case 3: pinB8_Output_AFPP_50(); break;
		case 4: pinB9_Output_AFPP_50(); break;
	}
}

void tim4_pwm::enable()
{
	//disable timer
	_TIM4_(TIMX_CR1) = 0; //&= ~TIM4_CR1_CEN;

	ccmr = 0x68 | (pwmMode - 1)<<4;
	cms_dir = centerMode<<5 | direction<<4;
	ccer = (polarity << 1) | 1;


	switch(channel)
	{
	case 1:
			//channel 1
			_TIM4_(TIMX_CCMR1) &= ~0x00FF; //clear
			_TIM4_(TIMX_CCMR1) |= ccmr; //set
			_TIM4_(TIMX_CCER)  &= ~0x0003; //clear
			_TIM4_(TIMX_CCER)  |= ccer; //output on
			break;
	case 2:
			//channel 2
			_TIM4_(TIMX_CCMR1) &= ~0xFF00; //clear
			_TIM4_(TIMX_CCMR1) |= ccmr<<8; //set
			_TIM4_(TIMX_CCER)  &= ~0x0030; //clear
			_TIM4_(TIMX_CCER)  |= ccer<<4; //output on
			break;
	case 3:
			//channel 3
			_TIM4_(TIMX_CCMR2) &= ~0x00FF; //clear
			_TIM4_(TIMX_CCMR2) |= ccmr; //set
			_TIM4_(TIMX_CCER)  &= ~0x0300; //clear
			_TIM4_(TIMX_CCER)  |= ccer<<8; //output on
			break;
	case 4:
			//channel 4
			_TIM4_(TIMX_CCMR2) &= ~0xFF00; //clear
			_TIM4_(TIMX_CCMR2) |= ccmr<<8; //set
			_TIM4_(TIMX_CCER)  &= ~0x3000; //clear
			_TIM4_(TIMX_CCER)  |= ccer<<12; //output on
			break;
	}

	//setup timer
	_TIM4_(TIMX_PSC) = prescaler; //prescaler
	_TIM4_(TIMX_ARR) = depth; //prescaler
	_TIM4_(TIMX_CR1) = TIMX_CR1_ARPE; //set preload and clear the rest
	_TIM4_(TIMX_CR1) |= cms_dir; //set center mode and direction

	//reset counters
	_TIM4_(TIMX_EGR) |= TIMX_EGR_UG;

	//enable
	//_TIM4_(TIMX_CR1) |= TIMX_CR1_CEN;
	BB_TIM4_CR1_CEN = 1;
}

void timer1::config()
{
	//_TIM1_(TIMX_DMAR) = DMAR;
	//_TIM1_(TIMX_DCR) = DCR;
	_TIM1_(TIMX_BDTR) = BDTR; //tim1 only
	if (!(CCMR1 & TIMX_CCMR2_CC4S)) _TIM1_(TIMX_CCR4) = CCR4;
	if (!(CCMR1 & TIMX_CCMR2_CC3S)) _TIM1_(TIMX_CCR3) = CCR3;
	if (!(CCMR1 & TIMX_CCMR1_CC2S)) _TIM1_(TIMX_CCR2) = CCR2;
	if (!(CCMR1 & TIMX_CCMR1_CC1S)) _TIM1_(TIMX_CCR1) = CCR1;
	_TIM1_(TIMX_RCR) = RCR;
	_TIM1_(TIMX_ARR) = ARR;
	_TIM1_(TIMX_PSC) = PSC;
	//_TIM1_(TIMX_CNT) = CNT;
	_TIM1_(TIMX_CCER) = CCER;
	_TIM1_(TIMX_CCMR2) = CCMR2;
	_TIM1_(TIMX_CCMR1) = CCMR1;
	//_TIM1_(TIMX_DIER) = DIER;
	_TIM1_(TIMX_SMCR) = SMCR;
	_TIM1_(TIMX_CR2) = CR2;
	_TIM1_(TIMX_CR1) |= TIMX_CR1_UDIS; //update event disable to avoid IRQ
	timer1::updateEvent();
	_TIM1_(TIMX_CR1) = CR1;
}

void timer1::enable(uint16_t count)
{
	timer1::disable();
	timer1::config();
	if (count) _TIM1_(TIMX_CNT) = count;
	timer1::enableOnly();
}

void timer1::master(uint16_t mms, uint16_t ccmr)
{
	CR2 &= ~TIMX_CR2_MMS; CR2 |= mms<<4;
	switch (mms)
	{
	case 4: CCMR1 &= ~0x00FF; CCMR1 |= ccmr<<4; break;
	case 5: CCMR1 &= ~0xFF00; CCMR1 |= ccmr<<12; break;
	case 6: CCMR2 &= ~0x00FF; CCMR2 |= ccmr<<4; break;
	case 7: CCMR2 &= ~0xFF00; CCMR2 |= ccmr<<12; break;
	default: break;
	}
}

void timer1::slave(uint16_t sms, uint16_t ts)
{
	SMCR &= ~(TIMX_SMCR_SMS | TIMX_SMCR_TS);
	if (ts & 0xFF00)
		switch (ts>>8)
		{
		case 2: ts = 1; break;
		case 3: ts = 2; break;
		case 4: ts = 3; break;
		case 5: ts = 0; break;
		case 8: break;
		default: break;
		}
	SMCR |= (ts<<4) | sms;
}

void timer1::pwmSetup(uint8_t center, uint8_t dir)
{
	CR1 &= ~TIMX_CR1_CMS;
	CR1 |= center<<5;
	if (dir) CR1 |= TIMX_CR1_DIR; else CR1 &= ~TIMX_CR1_DIR;
    CR1 |= TIMX_CR1_ARPE;
}

void timer1::pwmChannel(uint8_t ch_num, uint8_t mode, uint8_t plrty, uint8_t opendrain)
{
	tim1_pwm a(ch_num);
	uint16_t CCMR_clr;
	uint16_t CCMR_tmp = 0x68 | (mode - 1)<<4;
	uint16_t CCER_tmp = ((plrty << 1) | 1) << ((ch_num-1)*4);
	a.init(opendrain);
	if (ch_num & 1) CCMR_clr = 0x00FF; else {CCMR_clr = 0xFF00; CCMR_tmp <<= 8;}
	if (ch_num & 2) {CCMR2 &= ~CCMR_clr; CCMR2 |= CCMR_tmp;}
				else {CCMR1 &= ~CCMR_clr; CCMR1 |= CCMR_tmp;}
	CCER &= ~(3<< ((ch_num-1)*4));
	CCER |= CCER_tmp;
}

void timer1::pwmEnable(uint8_t ch_num)
{
	uint16_t tmp = (1 << (ch_num-1)*4);
	_TIM1_(TIMX_CCER) |= tmp;
	CCER |= tmp;
}
void timer1::pwmDisable(uint8_t ch_num)
{
	uint16_t tmp = (1 << (ch_num-1)*4);
	_TIM1_(TIMX_CCER) &= ~tmp;
	CCER &= ~tmp;
}

void timer1::DMACCenable(uint8_t ch_num)
{
	if (ch_num) _TIM1_(TIMX_DIER) |= (1 << (ch_num + 8));
	else _TIM1_(TIMX_DIER) |= TIMX_DIER_CCDE;
}

void timer1::DMACCdisable(uint8_t ch_num)
{
	if (ch_num) _TIM1_(TIMX_DIER) &= ~(1 << (ch_num + 8));
	else _TIM1_(TIMX_DIER) &= ~TIMX_DIER_CCDE;
}


void timer2::config()
{
	//_TIM2_(TIMX_DMAR) = DMAR;
	//_TIM2_(TIMX_DCR) = DCR;
	if (!(CCMR1 & TIMX_CCMR2_CC4S)) _TIM2_(TIMX_CCR4) = CCR4;
	if (!(CCMR1 & TIMX_CCMR2_CC3S)) _TIM2_(TIMX_CCR3) = CCR3;
	if (!(CCMR1 & TIMX_CCMR1_CC2S)) _TIM2_(TIMX_CCR2) = CCR2;
	if (!(CCMR1 & TIMX_CCMR1_CC1S)) _TIM2_(TIMX_CCR1) = CCR1;
	_TIM2_(TIMX_ARR) = ARR;
	_TIM2_(TIMX_PSC) = PSC;
	//_TIM2_(TIMX_CNT) = CNT;
	_TIM2_(TIMX_CCER) = CCER;
	_TIM2_(TIMX_CCMR2) = CCMR2;
	_TIM2_(TIMX_CCMR1) = CCMR1;
	//_TIM2_(TIMX_DIER) = DIER;
	_TIM2_(TIMX_SMCR) = SMCR;
	_TIM2_(TIMX_CR2) = CR2;
	_TIM2_(TIMX_CR1) |= TIMX_CR1_UDIS; //update event disable to avoid IRQ
	timer2::updateEvent();
	_TIM2_(TIMX_CR1) = CR1;
}

void timer2::enable(uint16_t count)
{
	timer2::disable();
	timer2::config();
	if (count) _TIM2_(TIMX_CNT) = count;
	timer2::enableOnly();
}

void timer2::master(uint16_t mms, uint16_t ccmr)
{
	CR2 &= ~TIMX_CR2_MMS; CR2 |= mms<<4;
	switch (mms)
	{
	case 4: CCMR1 &= ~0x00FF; CCMR1 |= ccmr<<4; break;
	case 5: CCMR1 &= ~0xFF00; CCMR1 |= ccmr<<12; break;
	case 6: CCMR2 &= ~0x00FF; CCMR2 |= ccmr<<4; break;
	case 7: CCMR2 &= ~0xFF00; CCMR2 |= ccmr<<12; break;
	default: break;
	}
}

void timer2::slave(uint16_t sms, uint16_t ts)
{
	SMCR &= ~(TIMX_SMCR_SMS | TIMX_SMCR_TS);
	if (ts & 0xFF00)
		switch (ts>>8)
		{
		case 1: ts = 0; break;
		case 3: ts = 2; break;
		case 4: ts = 3; break;
		case 5: break;
		case 8: ts = 1; break;
		default: break;
		}
	SMCR |= (ts<<4) | sms;
}


void timer2::pwmSetup(uint8_t center, uint8_t dir)
{
	CR1 &= ~TIMX_CR1_CMS;
	CR1 |= center<<5;
	if (dir) CR1 |= TIMX_CR1_DIR; else CR1 &= ~TIMX_CR1_DIR;
	CR1 |= TIMX_CR1_ARPE;
}

void timer2::pwmChannel(uint8_t ch_num, uint8_t mode, uint8_t plrty, uint8_t opendrain)
{
	tim2_pwm a(ch_num);
	uint16_t CCMR_clr;
	uint16_t CCMR_tmp = 0x68 | (mode - 1)<<4;
	uint16_t CCER_tmp = ((plrty << 1) | 1) << ((ch_num-1)*4);
	a.init(opendrain);
	if (ch_num & 1) CCMR_clr = 0x00FF; else {CCMR_clr = 0xFF00; CCMR_tmp <<= 8;}
	if (ch_num & 2) {CCMR2 &= ~CCMR_clr; CCMR2 |= CCMR_tmp;}
				else {CCMR1 &= ~CCMR_clr; CCMR1 |= CCMR_tmp;}
	CCER &= ~(3<< ((ch_num-1)*4));
	CCER |= CCER_tmp;
}

void timer2::pwmEnable(uint8_t ch_num)
{
	uint16_t tmp = (1 << (ch_num-1)*4);
	_TIM2_(TIMX_CCER) |= tmp;
	CCER |= tmp;
}
void timer2::pwmDisable(uint8_t ch_num)
{
	uint16_t tmp = (1 << (ch_num-1)*4);
	_TIM2_(TIMX_CCER) &= ~tmp;
	CCER &= ~tmp;
}

void timer2::DMACCenable(uint8_t ch_num)
{
	if (ch_num) _TIM2_(TIMX_DIER) |= (1 << (ch_num + 8));
	else _TIM2_(TIMX_DIER) |= TIMX_DIER_CCDE;
}

void timer2::DMACCdisable(uint8_t ch_num)
{
	if (ch_num) _TIM2_(TIMX_DIER) &= ~(1 << (ch_num + 8));
	else _TIM2_(TIMX_DIER) &= ~TIMX_DIER_CCDE;
}


void timer3::config()
{
	//_TIM3_(TIMX_DMAR) = DMAR;
	//_TIM3_(TIMX_DCR) = DCR;
	if (!(CCMR1 & TIMX_CCMR2_CC4S)) _TIM3_(TIMX_CCR4) = CCR4;
	if (!(CCMR1 & TIMX_CCMR2_CC3S)) _TIM3_(TIMX_CCR3) = CCR3;
	if (!(CCMR1 & TIMX_CCMR1_CC2S)) _TIM3_(TIMX_CCR2) = CCR2;
	if (!(CCMR1 & TIMX_CCMR1_CC1S)) _TIM3_(TIMX_CCR1) = CCR1;
	_TIM3_(TIMX_ARR) = ARR;
	_TIM3_(TIMX_PSC) = PSC;
	//_TIM3_(TIMX_CNT) = CNT;
	_TIM3_(TIMX_CCER) = CCER;
	_TIM3_(TIMX_CCMR2) = CCMR2;
	_TIM3_(TIMX_CCMR1) = CCMR1;
	//_TIM3_(TIMX_DIER) = DIER;
	_TIM3_(TIMX_SMCR) = SMCR;
	_TIM3_(TIMX_CR2) = CR2;
	_TIM3_(TIMX_CR1) |= TIMX_CR1_UDIS; //update event disable to avoid IRQ
	timer3::updateEvent();
	_TIM3_(TIMX_CR1) = CR1;
}

void timer3::enable(uint16_t count)
{
	timer3::disable();
	timer3::config();
	if (count) _TIM3_(TIMX_CNT) = count;
	timer3::enableOnly();
}

void timer3::master(uint16_t mms, uint16_t ccmr)
{
	CR2 &= ~TIMX_CR2_MMS; CR2 |= mms<<4;
	switch (mms)
	{
	case 4: CCMR1 &= ~0x00FF; CCMR1 |= ccmr<<4; break;
	case 5: CCMR1 &= ~0xFF00; CCMR1 |= ccmr<<12; break;
	case 6: CCMR2 &= ~0x00FF; CCMR2 |= ccmr<<4; break;
	case 7: CCMR2 &= ~0xFF00; CCMR2 |= ccmr<<12; break;
	default: break;
	}
}

void timer3::slave(uint16_t sms, uint16_t ts)
{
	SMCR &= ~(TIMX_SMCR_SMS | TIMX_SMCR_TS);
	if (ts & 0xFF00)
		switch (ts>>8)
		{
		case 1: ts = 0; break;
		case 2: ts = 1; break;
		case 4: ts = 3; break;
		case 5: ts = 2; break;
		case 8: break;
		default: break;
		}
	SMCR |= (ts<<4) | sms;
}


void timer3::pwmSetup(uint8_t center, uint8_t dir)
{
	CR1 &= ~TIMX_CR1_CMS;
	CR1 |= center<<5;
	if (dir) CR1 |= TIMX_CR1_DIR; else CR1 &= ~TIMX_CR1_DIR;
	CR1 |= TIMX_CR1_ARPE;
}

void timer3::pwmChannel(uint8_t ch_num, uint8_t mode, uint8_t plrty, uint8_t opendrain)
{
	tim3_pwm a(ch_num);
	uint16_t CCMR_clr;
	uint16_t CCMR_tmp = 0x68 | (mode - 1)<<4;
	uint16_t CCER_tmp = ((plrty << 1) | 1) << ((ch_num-1)*4);
	a.init(opendrain);
	if (ch_num & 1) CCMR_clr = 0x00FF; else {CCMR_clr = 0xFF00; CCMR_tmp <<= 8;}
	if (ch_num & 2) {CCMR2 &= ~CCMR_clr; CCMR2 |= CCMR_tmp;}
				else {CCMR1 &= ~CCMR_clr; CCMR1 |= CCMR_tmp;}
	CCER &= ~(3<< ((ch_num-1)*4));
	CCER |= CCER_tmp;
}

void timer3::pwmEnable(uint8_t ch_num)
{
	uint16_t tmp = (1 << (ch_num-1)*4);
	_TIM3_(TIMX_CCER) |= tmp;
	CCER |= tmp;
}
void timer3::pwmDisable(uint8_t ch_num)
{
	uint16_t tmp = (1 << (ch_num-1)*4);
	_TIM3_(TIMX_CCER) &= ~tmp;
	CCER &= ~tmp;
}

void timer3::DMACCenable(uint8_t ch_num)
{
	if (ch_num) _TIM3_(TIMX_DIER) |= (1 << (ch_num + 8));
	else _TIM3_(TIMX_DIER) |= TIMX_DIER_CCDE;
}

void timer3::DMACCdisable(uint8_t ch_num)
{
	if (ch_num) _TIM3_(TIMX_DIER) &= ~(1 << (ch_num + 8));
	else _TIM3_(TIMX_DIER) &= ~TIMX_DIER_CCDE;
}


void timer4::config()
{
	//_TIM4_(TIMX_DMAR) = DMAR;
	//_TIM4_(TIMX_DCR) = DCR;
	if (!(CCMR1 & TIMX_CCMR2_CC4S)) _TIM4_(TIMX_CCR4) = CCR4;
	if (!(CCMR1 & TIMX_CCMR2_CC3S)) _TIM4_(TIMX_CCR3) = CCR3;
	if (!(CCMR1 & TIMX_CCMR1_CC2S)) _TIM4_(TIMX_CCR2) = CCR2;
	if (!(CCMR1 & TIMX_CCMR1_CC1S)) _TIM4_(TIMX_CCR1) = CCR1;
	_TIM4_(TIMX_ARR) = ARR;
	_TIM4_(TIMX_PSC) = PSC;
	//_TIM4_(TIMX_CNT) = CNT;
	_TIM4_(TIMX_CCER) = CCER;
	_TIM4_(TIMX_CCMR2) = CCMR2;
	_TIM4_(TIMX_CCMR1) = CCMR1;
	//_TIM4_(TIMX_DIER) = DIER;
	_TIM4_(TIMX_SMCR) = SMCR;
	_TIM4_(TIMX_CR2) = CR2;
	_TIM4_(TIMX_CR1) |= TIMX_CR1_UDIS; //update event disable to avoid IRQ
	timer4::updateEvent();
	_TIM4_(TIMX_CR1) = CR1;
}

void timer4::enable(uint16_t count)
{
	timer4::disable();
	timer4::config();
	if (count) _TIM4_(TIMX_CNT) = count;
	timer4::enableOnly();
}

void timer4::master(uint16_t mms, uint16_t ccmr)
{
	CR2 &= ~TIMX_CR2_MMS; CR2 |= mms<<4;
	switch (mms)
	{
	case 4: CCMR1 &= ~0x00FF; CCMR1 |= ccmr<<4; break;
	case 5: CCMR1 &= ~0xFF00; CCMR1 |= ccmr<<12; break;
	case 6: CCMR2 &= ~0x00FF; CCMR2 |= ccmr<<4; break;
	case 7: CCMR2 &= ~0xFF00; CCMR2 |= ccmr<<12; break;
	default: break;
	}
}

void timer4::slave(uint16_t sms, uint16_t ts)
{
	SMCR &= ~(TIMX_SMCR_SMS | TIMX_SMCR_TS);
	if (ts & 0xFF00)
		switch (ts>>8)
		{
		case 1: ts = 0; break;
		case 2: ts = 1; break;
		case 3: ts = 2; break;
		case 5: break;
		case 8: ts = 3; break;
		default: break;
		}
	SMCR |= (ts<<4) | sms;
}


void timer4::pwmSetup(uint8_t center, uint8_t dir)
{
	CR1 &= ~TIMX_CR1_CMS;
	CR1 |= center<<5;
	if (dir) CR1 |= TIMX_CR1_DIR; else CR1 &= ~TIMX_CR1_DIR;
	CR1 |= TIMX_CR1_ARPE;
}

void timer4::pwmChannel(uint8_t ch_num, uint8_t mode, uint8_t plrty, uint8_t opendrain)
{
	tim4_pwm a(ch_num);
	uint16_t CCMR_clr;
	uint16_t CCMR_tmp = 0x68 | (mode - 1)<<4;
	uint16_t CCER_tmp = ((plrty << 1) | 1) << ((ch_num-1)*4);
	a.init(opendrain);
	if (ch_num & 1) CCMR_clr = 0x00FF; else {CCMR_clr = 0xFF00; CCMR_tmp <<= 8;}
	if (ch_num & 2) {CCMR2 &= ~CCMR_clr; CCMR2 |= CCMR_tmp;}
				else {CCMR1 &= ~CCMR_clr; CCMR1 |= CCMR_tmp;}
	CCER &= ~(3<< ((ch_num-1)*4));
	CCER |= CCER_tmp;
}

void timer4::pwmEnable(uint8_t ch_num)
{
	uint16_t tmp = (1 << (ch_num-1)*4);
	_TIM4_(TIMX_CCER) |= tmp;
	CCER |= tmp;
}
void timer4::pwmDisable(uint8_t ch_num)
{
	uint16_t tmp = (1 << (ch_num-1)*4);
	_TIM4_(TIMX_CCER) &= ~tmp;
	CCER &= ~tmp;
}

void timer4::DMACCenable(uint8_t ch_num)
{
	if (ch_num) _TIM4_(TIMX_DIER) |= (1 << (ch_num + 8));
	else _TIM4_(TIMX_DIER) |= TIMX_DIER_CCDE;
}

void timer4::DMACCdisable(uint8_t ch_num)
{
	if (ch_num) _TIM4_(TIMX_DIER) &= ~(1 << (ch_num + 8));
	else _TIM4_(TIMX_DIER) &= ~TIMX_DIER_CCDE;
}
