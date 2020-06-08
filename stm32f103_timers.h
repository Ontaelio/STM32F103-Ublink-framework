/*
 * STM32F103 Timers and IRQ library header file
 * Part of STM32F103 register and peripherals library
 *
 * Dpcumentation available in the provided MD file.
 *
 * (c) 2019-2020 Dmitry Reznikov ontaelio(at)gmail.com
 *
 * Can be freely used according to the GNU GPL license.
 */

#ifndef STM32F103_TIMERS_H_
#define STM32F103_TIMERS_H_

#include <stm32f103_rcc_reg.h>
#include <stm32f103_gpio_reg.h>
#include <stm32f103_timers_reg.h>
#include <stdio.h>
#include <stdint.h>
#include <stm32f103_gpio.h>

//**** SysTick stuff

void delay_ms(uint32_t msecs);
void delay_us(uint32_t msecs);
inline void sysTick_stop()
{
	SYSTICK_CSR &= ~SYSTICK_CSR_ENABLE;
}
void sysTick_start(uint32_t val, uint8_t intext = 1);
inline uint32_t sysTick_read()
{
	return SYSTICK_CURVAL;
}
inline void sysTick_IRQenable()
{
	SYSTICK_CSR |= SYSTICK_CSR_TICKINT;
}
inline void sysTick_IRQdisable()
{
	SYSTICK_CSR &= ~SYSTICK_CSR_TICKINT;
}

//**** IRQ stuff

void irq_priority(uint8_t irq, uint8_t pri);
void irq_enable(uint8_t irq);
void irq_disable(uint8_t irq);

//**** STM timers stuff

//center mode and direction values, CR1
#define CENTER_UP	 0x0002
#define CENTER_DOWN  0x0004
#define CENTER_BOTH  0x0006
#define PHASECORRECT 0x0006 //Arduino term
#define UPCOUNTER	 0x0000
#define DOWNCOUNTER	 0x0001

//master-slave modes defaults
//master mode, CR2 <<4
#define MMS_RESET		0x0000
#define MMS_ENABLE		0x0001
#define MMS_UPDATE		0x0002
#define MMS_COMPPULSE	0x0003
#define MMS_COMP1		0x0004
#define MMS_COMP2		0x0005
#define MMS_COMP3		0x0006
#define MMS_COMP4		0x0007

//slave mode, SMCR
#define SMS_DISABLE		0x0000
#define SMS_ENC1		0x0001
#define SMS_ENC2		0x0002
#define SMS_ENC3		0x0003
#define SMS_RESET		0x0004
#define SMS_GATED		0x0005
#define SMS_TRIGGER		0x0006
#define SMS_EXTCLK		0x0007

//trigger selection, SMCR <<4
//may add 8 to this value to enable MSM
#define TS_ITR0			0x0000
#define TS_ITR1			0x0001
#define TS_ITR2			0x0002
#define TS_ITR3			0x0003
#define TS_TI1F_ED		0x0004
#define TS_TI1FP1		0x0005
#define TS_TI1FP2		0x0006
#define TS_ETRF			0x0007

//master timer selection, internal value, not register-connected
#define ITR_TIM1	0x0100
#define ITR_TIM2	0x0200
#define ITR_TIM3	0x0300
#define ITR_TIM4	0x0400
#define ITR_TIM5	0x0500
#define ITR_TIM8	0x0800

//output compare modes, CCMRX <<4 & <<12
#define OCM_FROZEN		0x0000
#define OCM_HIGH		0x0001
#define OCM_LOW			0x0002
#define OCM_TOGGLE		0x0003
#define OCM_FORCELOW	0x0004
#define OCM_FORCEHIGH	0x0005
#define OCM_PWM1		0x0006
#define OCM_PWM2		0x0007
// master-slave end


inline void timer1_init()
{
	TIM1_CLOCK = 1;
	AFIO_CLOCK = 1;
}

inline void timer2_init()
{
	TIM2_CLOCK = 1;
	AFIO_CLOCK = 1;}

inline void timer3_init()
{
	TIM3_CLOCK = 1;
	AFIO_CLOCK = 1;
}

inline void timer4_init()
{
	TIM4_CLOCK = 1;
	AFIO_CLOCK = 1;
}

// abstract classes

struct timer_config
{
	uint16_t CR1, CR2, SMCR, DIER, // SR, EGR,
			CCMR1, CCMR2, CCER, PSC, ARR, RCR; // CNT,
			//CCR1, CCR2, CCR3, CCR4; //, DCR; //,BDTR;
	//uint32_t DMAR; //32 bits in tim1 only
	timer_config():
		CR1	(0x0080), //basic configuration and enable (bit 0)
		CR2	(0x0000), //master mode and Hall sensor
		SMCR	(0x0000), //slave mode control
		DIER	(0x0000), //interrupt enable
			 //SR	(0x0000), //status, non-configurable, bits must be cleared inside ISRs.
			 //EGR	(0x0000), //event generator. UG here, the rest emulates events (non-configurable)
		CCMR1	(0x0000), //capture/compare mode
		CCMR2	(0x0000),
		CCER	(0x0000), //capture/compare enable
			 //CNT	(0x0000), //counter itself. Can be written to start at specific value
		PSC	(0x0000), //prescaler
		ARR	(0xFFFF)  //depth of the counter aka auto-reload
			 //RCR	(0x0000), //tim1 only, repeat counter, only one byte
			 //CCR1	(0x0000), //capture/compare value. Read-only in input
			 //CCR2	(0x0000),
			 //CCR3	(0x0000),
			 //CCR4	(0x0000)
			 //BDTR	(0x0000), //tim1 only. MOE here. Break, dead time, locks here.
			 //DCR	(0x0000), //dma control
			 //DMAR	(0x0000)  //dma burst stuff, 32 bits for tim1
		{};
};

class tim_pwm
{
protected:

	tim_pwm(uint8_t ch_num, uint16_t d): pwmMode(1), centerMode(0), direction(0), polarity(0), prescaler(0),
							  depth(d), channel(ch_num), ch_addr(channel*4 + 0x30){}
	tim_pwm() {}

public:
	uint8_t pwmMode, centerMode, direction, polarity;
	uint16_t prescaler, depth;

	virtual ~tim_pwm() {}
	virtual void init(uint8_t opendrain = 1) =0;
	virtual void enable() =0;
	virtual void disable() =0;
	virtual void write(uint16_t pwm_val) =0;
	friend class dma1;

protected:
	uint8_t channel, ch_addr, ccmr, cms_dir, ccer;
};

class timer
{
public: timer_config cfg;
protected:
	timer(uint16_t prsclr = 0x0000, uint16_t depth = 0xFFFF)
		{
			cfg.ARR = depth;
			cfg.PSC = prsclr;
		}


public:


	//uint16_t CR1, CR2, SMCR, //DIER, // SR, EGR,
	//			CCMR1, CCMR2, CCER, PSC, ARR, RCR; // CNT,
			//CCR1, CCR2, CCR3, CCR4; //, DCR; //,BDTR;
	//uint32_t DMAR; //32 bits in tim1 only

	virtual ~timer() {}
 	virtual void init() =0;
	virtual void config() =0;
	virtual void enableOnly() =0;
	virtual void enable(uint16_t count = 0)  =0;
	virtual void disable() =0;
	void pulse() {enableOnly();}
	virtual uint16_t read() =0;
	//operator uint16_t() {return _TIM1_(TIMX_CNT);}


	void setMode(uint16_t mode) {cfg.CR1 &= ~0x0070; cfg.CR1 |= mode<<4;}
	void setCC1mode(uint16_t mode, uint8_t prld_en = 1, uint8_t plrty = 0, uint8_t oe = 1);
	void setCC2mode(uint16_t mode, uint8_t prld_en = 1, uint8_t plrty = 0, uint8_t oe = 1);
	void setCC3mode(uint16_t mode, uint8_t prld_en = 1, uint8_t plrty = 0, uint8_t oe = 1);
	void setCC4mode(uint16_t mode, uint8_t prld_en = 1, uint8_t plrty = 0, uint8_t oe = 1);
	void setCC1output(uint8_t oe) {cfg.CCER &= ~TIMX_CCER_CC1E; cfg.CCER |= oe;}
	void setCC2output(uint8_t oe) {cfg.CCER &= ~TIMX_CCER_CC1E; cfg.CCER |= (oe << 4);}
	void setCC3output(uint8_t oe) {cfg.CCER &= ~TIMX_CCER_CC1E; cfg.CCER |= (oe << 8);}
	void setCC4output(uint8_t oe) {cfg.CCER &= ~TIMX_CCER_CC1E; cfg.CCER |= (oe << 12);}
	void setCC1preload(uint8_t pe) {cfg.CCMR1 &= ~TIMX_CCMR1_OC1PE; cfg.CCMR1 |= (pe << 3);}
	void setCC2preload(uint8_t pe) {cfg.CCMR1 &= ~TIMX_CCMR1_OC2PE; cfg.CCMR1 |= (pe << 11);}
	void setCC3preload(uint8_t pe) {cfg.CCMR2 &= ~TIMX_CCMR2_OC3PE; cfg.CCMR2 |= (pe << 3);}
	void setCC4preload(uint8_t pe) {cfg.CCMR2 &= ~TIMX_CCMR2_OC4PE; cfg.CCMR2 |= (pe << 11);}

	void setPreload(uint16_t pre) {cfg.CR1 &= ~TIMX_CR1_ARPE; cfg.CR1 |= (pre << 7);}
	void setUpdateRequest(uint16_t cc_only) {cfg.CR1 &= ~TIMX_CR1_URS; cfg.CR1 |= (cc_only << 2);}
	void setOnePulse(uint16_t opm) {cfg.CR1 &= ~TIMX_CR1_OPM; cfg.CR1 |= (opm << 3);}

	//void setUpdateIRQ(uint8_t bit=1) 	{DIER &= ~0x0001; DIER |= bit;}
	//void setCC1IRQ(uint8_t bit=1)		{DIER &= ~0x0002; DIER |= bit<<1;}
	//void setCC2IRQ(uint8_t bit=1)		{DIER &= ~0x0004; DIER |= bit<<2;}
	//void setCC3IRQ(uint8_t bit=1)		{DIER &= ~0x0008; DIER |= bit<<3;}
	//void setCC4IRQ(uint8_t bit=1)		{DIER &= ~0x0010; DIER |= bit<<4;}
	//void setTriggerIRQ(uint8_t bit=1)	{DIER &= ~0x0040; DIER |= bit<<6;}

	//void setCC1value(uint16_t val) {CCR1 = val;}
	//void setCC2value(uint16_t val) {CCR2 = val;}
	//void setCC3value(uint16_t val) {CCR3 = val;}
	//void setCC4value(uint16_t val) {CCR4 = val;}

	void setDepth(uint16_t val) {cfg.ARR = val;}
	void setPrescaler(uint16_t val) {cfg.PSC = val;}

	//void pwmSetup(uint8_t center, uint8_t dir);
	virtual void setPWMchannel(uint8_t ch_num, uint8_t mode, uint8_t plrty, uint8_t opendrain = 1) =0;// {tim2_pwm a(ch_num); a.init();}
	virtual void pwmWrite(uint8_t ch_num, uint16_t val) =0;
	virtual void pwmEnable(uint8_t ch_num) =0;
	virtual void pwmDisable(uint8_t ch_num) =0;

	void setMaster(uint16_t mms, uint16_t ccmr = 0);
	virtual void setSlave(uint16_t sms, uint16_t ts) =0;
	void master(uint16_t mms, uint16_t ccmr = 0) {setMaster(mms, ccmr);}
	void slave(uint16_t mms, uint16_t ccmr = 0) {setSlave(mms, ccmr);}

	virtual void IRQenable() =0;
	virtual void IRQdisable() =0;

	virtual void priority(uint8_t pri) =0;

	//virtual void writeCC1(uint16_t val) =0;
	virtual void writeCC2(uint16_t val) =0;
	virtual void writeCC3(uint16_t val) =0;
	virtual void writeCC4(uint16_t val) =0;

	virtual void CC1output(uint8_t bit) =0;
	virtual void CC2output(uint8_t bit) =0;
	virtual void CC3output(uint8_t bit) =0;
	virtual void CC4output(uint8_t bit) =0;

	//BB (atomic) stuff
	//update event enable/disable (CR1->UDIS)
	virtual void updateDisable() =0;
	virtual void updateEnable() =0;

	//fast interrupt enable/disable (1 or 0)
	//virtual void updateInterrupt(uint8_t bit) =0;
	virtual void CC1interrupt(uint8_t bit) =0;
	virtual void CC2interrupt(uint8_t bit) =0;
	virtual void CC3interrupt(uint8_t bit) =0;
	virtual void CC4interrupt(uint8_t bit) =0;
	virtual void triggerInterrupt(uint8_t bit) =0;

	//check status flags
	virtual uint8_t checkUpdate() =0;
	virtual uint8_t checkCC1() =0;
	virtual uint8_t checkCC2() =0;
	virtual uint8_t checkCC3() =0;
	virtual uint8_t checkCC4() =0;
	virtual uint8_t checkTrigger() =0;

	//event generators
	virtual void updateEvent() =0;
	virtual void CC1event() =0;
	virtual void CC2event() =0;
	virtual void CC3event() =0;
	virtual void CC4event() =0;
	virtual void triggerEvent() =0;

	//interrupt flag cleaners, should use BB for these most certainly
	virtual void clearUpdate() =0;
	virtual void clearCC1() =0;
	virtual void clearCC2() =0;
	virtual void clearCC3() =0;
	virtual void clearCC4() =0;
	virtual void clearTrigger() =0;
	virtual void clearAll() =0;

	//DMA stuff
	virtual void DMATRGenable() =0;
	virtual void DMACCenable(uint8_t ch_num) =0;
	virtual void DMAUPenable() =0;
	virtual void DMATRGdisable() =0;
	virtual void DMACCdisable(uint8_t ch_num) =0;
	virtual void DMAUPdisable() =0;
	virtual void DMAburst(uint8_t burst) =0;
	virtual void DMAbase(uint8_t base) =0;


};

// inherited classes

class tim1_pwm : public tim_pwm
{
public:
//	tim1_pwm(uint8_t ch_num): pwmMode(1), centerMode(0), direction(0), polarity(0), prescaler(0),
//							  depth(0xFFFF), channel(ch_num), ch_addr(channel*4 + 0x30){};
	tim1_pwm(uint8_t ch_num, uint16_t d = 0xFFFF): tim_pwm(ch_num, d){}
	tim1_pwm(): tim_pwm(){}
	void init(uint8_t opendrain = 1);
	void enable();
	void disable() {_TIM1_(TIMX_CCER) &= ~(1<<((channel-1)*4));} //output off
	void write(uint16_t pwm_val) {_TIM1_(ch_addr) = pwm_val;}
	void updateEvent() {BB_TIM1_EGR_UG = 1;}
	void CCevent() {_TIM1_(TIMX_EGR) |= 1<<channel;}

	//check status flags
	uint8_t checkUpdate() {return (_TIM1_(TIMX_SR) & TIMX_SR_UIF);}
	uint8_t checkCC() {return ((_TIM1_(TIMX_SR) >> channel) & 1);}
	void clearUpdate() {_TIM1_(TIMX_SR) &= ~TIMX_SR_UIF;}
	void clearCC() {_TIM1_(TIMX_SR) &= ~(1<<channel);}

	void DMAenable() {_TIM1_(TIMX_DIER) |= (1 << (channel+8));}
	void DMAdisable() {_TIM1_(TIMX_DIER) &= ~(1 << (channel+8));}

	operator uint16_t() {return _TIM1_(ch_addr);}
	tim1_pwm& operator= (const uint16_t& a) {write(a); return *this;}
	tim1_pwm& operator++ () {write (_TIM1_(ch_addr) + 1); return *this;}
	tim1_pwm operator++ (int) {write (_TIM1_(ch_addr) + 1); return *this;}
	tim1_pwm& operator-- () {write (_TIM1_(ch_addr) - 1); return *this;}
	tim1_pwm operator-- (int) {write (_TIM1_(ch_addr) - 1); return *this;}
	tim1_pwm& operator+= (const uint16_t& a) {write (_TIM1_(ch_addr) + a); return *this;}
	tim1_pwm& operator-= (const uint16_t& a) {write (_TIM1_(ch_addr) - a); return *this;}
	//uint8_t pwmMode, centerMode, direction, polarity;
	//uint16_t prescaler, depth;

private:
	//uint8_t channel, ch_addr, ccmr, cms_dir, ccer;
};

class tim2_pwm : public tim_pwm
{
public:
//	tim2_pwm(uint8_t ch_num): pwmMode(1), centerMode(0), direction(0), polarity(0), prescaler(0),
//							  depth(0xFFFF), channel(ch_num), ch_addr(channel*4 + 0x30){};
	tim2_pwm(uint8_t ch_num, uint16_t d = 0xFFFF): tim_pwm(ch_num, d){}
	tim2_pwm(): tim_pwm(){}
	void init(uint8_t opendrain = 1);
	void enable();
	void disable() {_TIM2_(TIMX_CCER) &= ~(1<<((channel-1)*4));} //output off
	void write(uint16_t pwm_val) {_TIM2_(ch_addr) = pwm_val;}
	void updateEvent() {BB_TIM2_EGR_UG = 1;}
	void CCevent() {_TIM2_(TIMX_EGR) |= 1<<channel;}

	//check status flags
	uint8_t checkUpdate() {return (_TIM2_(TIMX_SR) & TIMX_SR_UIF);}
	uint8_t checkCC() {return ((_TIM2_(TIMX_SR) >> channel) & 1);}
	void clearUpdate() {_TIM2_(TIMX_SR) &= ~TIMX_SR_UIF;}
	void clearCC() {_TIM2_(TIMX_SR) &= ~(1<<channel);}

	void DMAenable() {_TIM2_(TIMX_DIER) |= (1 << (channel+8));}
	void DMAdisable() {_TIM2_(TIMX_DIER) &= ~(1 << (channel+8));}

	operator uint16_t() {return _TIM2_(ch_addr);}
	tim2_pwm& operator= (const uint16_t& a) {write(a); return *this;}
	tim2_pwm& operator++ () {write (_TIM2_(ch_addr) + 1); return *this;}
	tim2_pwm operator++ (int) {write (_TIM2_(ch_addr) + 1); return *this;}
	tim2_pwm& operator-- () {write (_TIM2_(ch_addr) - 1); return *this;}
	tim2_pwm operator-- (int) {write (_TIM2_(ch_addr) - 1); return *this;}
	tim2_pwm& operator+= (const uint16_t& a) {write (_TIM2_(ch_addr) + a); return *this;}
	tim2_pwm& operator-= (const uint16_t& a) {write (_TIM2_(ch_addr) - a); return *this;}
	//uint8_t pwmMode, centerMode, direction, polarity;
	//uint16_t prescaler, depth;

private:
	//uint8_t channel, ch_addr, ccmr, cms_dir, ccer;
};

class tim3_pwm : public tim_pwm
{
public:
//	tim3_pwm(uint8_t ch_num): pwmMode(1), centerMode(0), direction(0), polarity(0), prescaler(0),
//							  depth(0xFFFF), channel(ch_num), ch_addr(channel*4 + 0x30){};
	tim3_pwm(uint8_t ch_num, uint16_t d = 0xFFFF): tim_pwm(ch_num, d){}
	tim3_pwm(): tim_pwm(){}
	void init(uint8_t opendrain = 1);
	void enable();
	void disable() {_TIM3_(TIMX_CCER) &= ~(1<<((channel-1)*4));} //output off
	void write(uint16_t pwm_val) {_TIM3_(ch_addr) = pwm_val;}
	void updateEvent() {BB_TIM3_EGR_UG = 1;}
	void CCevent() {_TIM3_(TIMX_EGR) |= 1<<channel;}

	//check status flags
	uint8_t checkUpdate() {return (_TIM3_(TIMX_SR) & TIMX_SR_UIF);}
	uint8_t checkCC() {return ((_TIM3_(TIMX_SR) >> channel) & 1);}
	void clearUpdate() {_TIM3_(TIMX_SR) &= ~TIMX_SR_UIF;}
	void clearCC() {_TIM3_(TIMX_SR) &= ~(1<<channel);}

	void DMAenable() {_TIM3_(TIMX_DIER) |= (1 << (channel+8));}
	void DMAdisable() {_TIM3_(TIMX_DIER) &= ~(1 << (channel+8));}

	operator uint16_t() {return _TIM3_(ch_addr);}
	tim3_pwm& operator= (const uint16_t& a) {write(a); return *this;}
	tim3_pwm& operator++ () {write (_TIM3_(ch_addr) + 1); return *this;}
	tim3_pwm operator++ (int) {write (_TIM3_(ch_addr) + 1); return *this;}
	tim3_pwm& operator-- () {write (_TIM3_(ch_addr) - 1); return *this;}
	tim3_pwm operator-- (int) {write (_TIM3_(ch_addr) - 1); return *this;}
	tim3_pwm& operator+= (const uint16_t& a) {write (_TIM3_(ch_addr) + a); return *this;}
	tim3_pwm& operator-= (const uint16_t& a) {write (_TIM3_(ch_addr) - a); return *this;}
	//uint8_t pwmMode, centerMode, direction, polarity;
	//uint16_t prescaler, depth;

private:
	//uint8_t channel, ch_addr, ccmr, cms_dir, ccer;
};

class tim4_pwm : public tim_pwm
{
public:
//	tim4_pwm(uint8_t ch_num): pwmMode(1), centerMode(0), direction(0), polarity(0), prescaler(0),
//							  depth(0xFFFF), channel(ch_num), ch_addr(channel*4 + 0x30){};
	tim4_pwm(uint8_t ch_num, uint16_t d = 0xFFFF): tim_pwm(ch_num, d){}
	tim4_pwm(): tim_pwm(){}
	void init(uint8_t opendrain = 1);
	void enable();
	void disable() {_TIM4_(TIMX_CCER) &= ~(1<<((channel-1)*4));} //output off
	void write(uint16_t pwm_val) {_TIM4_(ch_addr) = pwm_val;}
	void updateEvent() {BB_TIM4_EGR_UG = 1;}
	void CCevent() {_TIM4_(TIMX_EGR) |= 1<<channel;}

	//check status flags
	uint8_t checkUpdate() {return (_TIM4_(TIMX_SR) & TIMX_SR_UIF);}
	uint8_t checkCC() {return ((_TIM4_(TIMX_SR) >> channel) & 1);}
	void clearUpdate() {_TIM4_(TIMX_SR) &= ~TIMX_SR_UIF;}
	void clearCC() {_TIM4_(TIMX_SR) &= ~(1<<channel);}

	void DMAenable() {_TIM4_(TIMX_DIER) |= (1 << (channel+8));}
	void DMAdisable() {_TIM4_(TIMX_DIER) &= ~(1 << (channel+8));}

	operator uint16_t() {return _TIM4_(ch_addr);}
	tim4_pwm& operator= (const uint16_t& a) {write(a); return *this;}
	tim4_pwm& operator++ () {write (_TIM4_(ch_addr) + 1); return *this;}
	tim4_pwm operator++ (int) {write (_TIM4_(ch_addr) + 1); return *this;}
	tim4_pwm& operator-- () {write (_TIM4_(ch_addr) - 1); return *this;}
	tim4_pwm operator-- (int) {write (_TIM4_(ch_addr) - 1); return *this;}
	tim4_pwm& operator+= (const uint16_t& a) {write (_TIM4_(ch_addr) + a); return *this;}
	tim4_pwm& operator-= (const uint16_t& a) {write (_TIM4_(ch_addr) - a); return *this;}
	//uint8_t pwmMode, centerMode, direction, polarity;
	//uint16_t prescaler, depth;

private:
	//uint8_t channel, ch_addr, ccmr, cms_dir, ccer;
};

typedef tim1_pwm tim1_pin;
typedef tim2_pwm tim2_pin;
typedef tim3_pwm tim3_pin;
typedef tim4_pwm tim4_pin;



class timer1: public timer
{
public:
	timer1(uint16_t prsclr = 0x0000, uint16_t depth = 0xFFFF): timer(prsclr, depth), BDTR(TIMX_BDTR_MOE) {}
	uint16_t BDTR;

	void init() {timer1_init();}
	void config();
	void enableOnly() {BB_TIM1_CR1_CEN = 1;}
	void enable(uint16_t count = 0);
	void disable() {BB_TIM1_CR1_CEN = 0;}
	uint16_t read() {return _TIM1_(TIMX_CNT);}
	operator uint16_t() {return _TIM1_(TIMX_CNT);}

	//void master(uint16_t mms, uint16_t ccmr = 0);
	void setSlave(uint16_t sms, uint16_t ts);
	void setMasterOutput(uint16_t moe) {BDTR &= ~TIMX_BDTR_MOE; BDTR |= (moe << 15);}

	//void setCOMIRQ(uint8_t bit=1)		{DIER &= ~0x0020; DIER |= bit<<5;} //tim1 only
	//void setBreakIRQ(uint8_t bit=1)		{DIER &= ~0x0080; DIER |= bit<<7;} //tim1 only

	//void pwmSetup(uint8_t center, uint8_t dir);
	void setPWMchannel(uint8_t ch_num, uint8_t mode, uint8_t plrty, uint8_t opendrain = 1);
	void pwmWrite(uint8_t ch_num, uint16_t val) {_TIM1_(ch_num*4 + 0x30) = val;}
	void pwmEnable(uint8_t ch_num);
	void pwmDisable(uint8_t ch_num);

	//for consistency with other timers. Here they enable the update event IRQ
	void IRQenable() {IRQ_0TO31_SER |= IRQ_BITMASK_TIM1_UP;}
	void IRQdisable() {IRQ_0TO31_CER |= IRQ_BITMASK_TIM1_UP;}

	//tim1 only
	void IRQ_BRK_enable() {IRQ_0TO31_SER |= IRQ_BITMASK_TIM1_BRK;}
	void IRQ_UP_enable() {IRQ_0TO31_SER |= IRQ_BITMASK_TIM1_UP;}
	void IRQ_BITMASK_TRG_COM_enable() {IRQ_0TO31_SER |= IRQ_BITMASK_TIM1_TRG_COM;}
	void IRQ_CC_enable() {IRQ_0TO31_SER |= IRQ_BITMASK_TIM1_CC;}
	void IRQ_BRK_disable() {IRQ_0TO31_CER |= IRQ_BITMASK_TIM1_BRK;}
	void IRQ_UP_disable() {IRQ_0TO31_CER |= IRQ_BITMASK_TIM1_UP;}
	void IRQ_BITMASK_TRG_COM_disable() {IRQ_0TO31_CER |= IRQ_BITMASK_TIM1_TRG_COM;}
	void IRQ_CC_disable() {IRQ_0TO31_CER |= IRQ_BITMASK_TIM1_CC;}

	//capture/compare channels
	static void writeCC1(uint16_t val) {_TIM1_(TIMX_CCR1) = val;}
	void writeCC2(uint16_t val) {_TIM1_(TIMX_CCR2) = val;}
	void writeCC3(uint16_t val) {_TIM1_(TIMX_CCR3) = val;}
	void writeCC4(uint16_t val) {_TIM1_(TIMX_CCR4) = val;}

	void CC1output(uint8_t bit) {BB_TIM1_CCER_CC1E = bit;}
	void CC2output(uint8_t bit) {BB_TIM1_CCER_CC2E = bit;}
	void CC3output(uint8_t bit) {BB_TIM1_CCER_CC3E = bit;}
	void CC4output(uint8_t bit) {BB_TIM1_CCER_CC4E = bit;}

	//BB (atomic) stuff
	//update event enable/disable (CR1->UDIS)
	void updateDisable() {BB_TIM1_CR1_UDIS = 0;}
	void updateEnable() {BB_TIM1_CR1_UDIS = 1;}

	//fast interrupt enable/disable (1 or 0)
	void updateInterrupt(uint8_t bit) {BB_TIM1_DIER_UIE = bit;}
	void CC1interrupt(uint8_t bit) {BB_TIM1_DIER_CC1IE = bit;}
	void CC2interrupt(uint8_t bit) {BB_TIM1_DIER_CC2IE = bit;}
	void CC3interrupt(uint8_t bit) {BB_TIM1_DIER_CC3IE = bit;}
	void CC4interrupt(uint8_t bit) {BB_TIM1_DIER_CC4IE = bit;}
	void COMinterrupt(uint8_t bit) {BB_TIM1_DIER_COMIE = bit;}
	void triggerInterrupt(uint8_t bit) {BB_TIM1_DIER_TIE = bit;}
	void breakInterrupt(uint8_t bit) {BB_TIM1_DIER_BIE = bit;}

	//check status flags
	uint8_t checkUpdate() {return (_TIM1_(TIMX_SR) & TIMX_SR_UIF);}
	uint8_t checkCC1() {return ((_TIM1_(TIMX_SR) & TIMX_SR_CC1IF)>>1);}
	uint8_t checkCC2() {return ((_TIM1_(TIMX_SR) & TIMX_SR_CC2IF)>>2);}
	uint8_t checkCC3() {return ((_TIM1_(TIMX_SR) & TIMX_SR_CC3IF)>>3);}
	uint8_t checkCC4() {return ((_TIM1_(TIMX_SR) & TIMX_SR_CC4IF)>>4);}
	uint8_t checkCOM() {return ((_TIM1_(TIMX_SR) & TIMX_SR_COMIF)>>5);}
	uint8_t checkTrigger() {return ((_TIM1_(TIMX_SR) & TIMX_SR_TIF)>>6);}
	uint8_t checkBreak() {return ((_TIM1_(TIMX_SR) & TIMX_SR_BIF)>>7);}


	//event generators
	void updateEvent() {BB_TIM1_EGR_UG = 1;}
	void CC1event() {BB_TIM1_EGR_CC1G = 1;}
	void CC2event() {BB_TIM1_EGR_CC2G = 1;}
	void CC3event() {BB_TIM1_EGR_CC3G = 1;}
	void CC4event() {BB_TIM1_EGR_CC4G = 1;}
	void COMevent() {BB_TIM1_EGR_COMG = 1;}
	void triggerEvent() {BB_TIM1_EGR_TG = 1;}
	void breakEvent() {BB_TIM1_EGR_BG = 1;}

	//interrupt flag cleaners, should use BB for these most certainly
	void clearUpdate() {BB_TIM1_SR_UIF = 0;}
	void clearCC1() {BB_TIM1_SR_CC1IF = 0;}
	void clearCC2() {BB_TIM1_SR_CC2IF = 0;}
	void clearCC3() {BB_TIM1_SR_CC3IF = 0;}
	void clearCC4() {BB_TIM1_SR_CC4IF = 0;}
	void clearCOM() {BB_TIM1_SR_COMIF = 0;}
	void clearTrigger() {BB_TIM1_SR_TIF = 0;}
	void clearBreak() {BB_TIM1_SR_BIF = 0;}
	void clearAll() {_TIM1_(TIMX_SR) = 0;}

	//IRQ priority
	void priority(uint8_t pri);
	void BRKpriority(uint8_t pri) {irq_priority(TIM1_BRK_IRQ, pri);}
	void UPpriority(uint8_t pri) {irq_priority(TIM1_UP_IRQ, pri);}
	void TRG_COMpriority(uint8_t pri) {irq_priority(TIM1_TRG_COM_IRQ, pri);}
	void CCpriority(uint8_t pri) {irq_priority(TIM1_CC_IRQ, pri);}

	//DMA stuff
	void DMACOMenable() {_TIM1_(TIMX_DIER) |= TIMX_DIER_COMDE;}
	void DMATRGenable() {_TIM1_(TIMX_DIER) |= TIMX_DIER_TDE;}
	void DMACCenable(uint8_t ch_num = 0);
	void DMAUPenable() {_TIM1_(TIMX_DIER) |= TIMX_DIER_UDE;}
	void DMACOMdisable()  {_TIM1_(TIMX_DIER) &= ~TIMX_DIER_COMDE;}
	void DMATRGdisable()  {_TIM1_(TIMX_DIER) &= ~TIMX_DIER_TDE;}
	void DMACCdisable(uint8_t ch_num = 0);
	void DMAUPdisable()  {_TIM1_(TIMX_DIER) &= ~TIMX_DIER_UDE;}
	void DMAburst(uint8_t burst) {_TIM1_(TIMX_DCR) &= ~TIMX_DCR_DBL; _TIM1_(TIMX_DCR) |= ((--burst) << 8);}
	void DMAbase(uint8_t base) {_TIM1_(TIMX_DCR) &= ~TIMX_DCR_DBA; _TIM1_(TIMX_DCR) |= base;}

private:
};

class timer2: public timer
{
public:
	timer2(uint16_t prsclr = 0x0000, uint16_t depth = 0xFFFF): timer(prsclr, depth) {}

 	void init() {timer2_init();}
	void config();
	void enableOnly() {BB_TIM2_CR1_CEN = 1;}
	void enable(uint16_t count = 0);
	void disable() {BB_TIM2_CR1_CEN = 0;}
	uint16_t read() {return _TIM2_(TIMX_CNT);}
	operator uint16_t() {return _TIM1_(TIMX_CNT);}

	//void master(uint16_t mms, uint16_t ccmr = 0);
	void setSlave(uint16_t sms, uint16_t ts);

	//void pwmSetup(uint8_t center, uint8_t dir);
	void setPWMchannel(uint8_t ch_num, uint8_t mode, uint8_t plrty, uint8_t opendrain = 1);// {tim2_pwm a(ch_num); a.init();}
	void pwmWrite(uint8_t ch_num, uint16_t val) {_TIM2_(ch_num*4 + 0x30) = val;}
	void pwmEnable(uint8_t ch_num);
	void pwmDisable(uint8_t ch_num);

	void IRQenable() {IRQ_0TO31_SER |= IRQ_BITMASK_TIM2;}
	void IRQdisable() {IRQ_0TO31_CER |= IRQ_BITMASK_TIM2;}

	//capture/compare channels
	void writeCC1(uint16_t val) {_TIM2_(TIMX_CCR1) = val;}
	void writeCC2(uint16_t val) {_TIM2_(TIMX_CCR2) = val;}
	void writeCC3(uint16_t val) {_TIM2_(TIMX_CCR3) = val;}
	void writeCC4(uint16_t val) {_TIM2_(TIMX_CCR4) = val;}

	void CC1output(uint8_t bit) {BB_TIM2_CCER_CC1E = bit;}
	void CC2output(uint8_t bit) {BB_TIM2_CCER_CC2E = bit;}
	void CC3output(uint8_t bit) {BB_TIM2_CCER_CC3E = bit;}
	void CC4output(uint8_t bit) {BB_TIM2_CCER_CC4E = bit;}

	//BB (atomic) stuff
	//update event enable/disable (CR1->UDIS)
	void updateDisable() {BB_TIM2_CR1_UDIS = 0;}
	void updateEnable() {BB_TIM2_CR1_UDIS = 1;}

	//fast interrupt enable/disable (1 or 0)
	void updateInterrupt(uint8_t bit) {BB_TIM2_DIER_UIE = bit;}
	void CC1interrupt(uint8_t bit) {BB_TIM2_DIER_CC1IE = bit;}
	void CC2interrupt(uint8_t bit) {BB_TIM2_DIER_CC2IE = bit;}
	void CC3interrupt(uint8_t bit) {BB_TIM2_DIER_CC3IE = bit;}
	void CC4interrupt(uint8_t bit) {BB_TIM2_DIER_CC4IE = bit;}
	void triggerInterrupt(uint8_t bit) {BB_TIM2_DIER_TIE = bit;}

	//check status flags
	uint8_t checkUpdate() {return (_TIM2_(TIMX_SR) & TIMX_SR_UIF);}
	uint8_t checkCC1() {return ((_TIM2_(TIMX_SR) & TIMX_SR_CC1IF)>>1);}
	uint8_t checkCC2() {return ((_TIM2_(TIMX_SR) & TIMX_SR_CC2IF)>>2);}
	uint8_t checkCC3() {return ((_TIM2_(TIMX_SR) & TIMX_SR_CC3IF)>>3);}
	uint8_t checkCC4() {return ((_TIM2_(TIMX_SR) & TIMX_SR_CC4IF)>>4);}
	uint8_t checkTrigger() {return ((_TIM2_(TIMX_SR) & TIMX_SR_TIF)>>6);}


	//event generators
	void updateEvent() {BB_TIM2_EGR_UG = 1;}
	void CC1event() {BB_TIM2_EGR_CC1G = 1;}
	void CC2event() {BB_TIM2_EGR_CC2G = 1;}
	void CC3event() {BB_TIM2_EGR_CC3G = 1;}
	void CC4event() {BB_TIM2_EGR_CC4G = 1;}
	void triggerEvent() {BB_TIM2_EGR_TG = 1;}

	//interrupt flag cleaners, should use BB for these most certainly
	void clearUpdate() {BB_TIM2_SR_UIF = 0;} //{_TIM2_(TIMX_SR) &= ~TIMX_SR_UIF;}
	void clearCC1() {BB_TIM2_SR_CC1IF = 0;} //{_TIM2_(TIMX_SR) &= ~TIMX_SR_CC1IF;}
	void clearCC2() {BB_TIM2_SR_CC2IF = 0;} //{_TIM2_(TIMX_SR) &= ~TIMX_SR_CC2IF;}
	void clearCC3() {BB_TIM2_SR_CC3IF = 0;} //{_TIM2_(TIMX_SR) &= ~TIMX_SR_CC3IF;}
	void clearCC4() {BB_TIM2_SR_CC4IF = 0;} //{_TIM2_(TIMX_SR) &= ~TIMX_SR_CC4IF;}
	void clearTrigger() {BB_TIM2_SR_TIF = 0;} //{_TIM2_(TIMX_SR) &= ~TIMX_SR_TIF;}
	void clearAll() {_TIM2_(TIMX_SR) = 0;}

	//IRQ priority
	void priority(uint8_t pri) {irq_priority(TIM2_IRQ, pri);}

	//DMA stuff
	void DMATRGenable() {_TIM2_(TIMX_DIER) |= TIMX_DIER_TDE;}
	void DMACCenable(uint8_t ch_num = 0);
	void DMAUPenable() {_TIM2_(TIMX_DIER) |= TIMX_DIER_UDE;}
	void DMATRGdisable()  {_TIM2_(TIMX_DIER) &= ~TIMX_DIER_TDE;}
	void DMACCdisable(uint8_t ch_num = 0);
	void DMAUPdisable()  {_TIM2_(TIMX_DIER) &= ~TIMX_DIER_UDE;}
	void DMAburst(uint8_t burst) {_TIM2_(TIMX_DCR) &= ~TIMX_DCR_DBL; _TIM2_(TIMX_DCR) |= ((--burst) << 8);}
	void DMAbase(uint8_t base) {_TIM2_(TIMX_DCR) &= ~TIMX_DCR_DBA; _TIM2_(TIMX_DCR) |= base;}


private:

};

class timer3: public timer
{
public:
	timer3(uint16_t prsclr = 0x0000, uint16_t depth = 0xFFFF): timer(prsclr, depth) {}

 	void init() {timer3_init();}
	void config();
	void enableOnly() {BB_TIM3_CR1_CEN = 1;}
	void enable(uint16_t count = 0);
	void disable() {BB_TIM3_CR1_CEN = 0;}
	uint16_t read() {return _TIM3_(TIMX_CNT);}
	operator uint16_t() {return _TIM1_(TIMX_CNT);}

	//void master(uint16_t mms, uint16_t ccmr = 0);
	void setSlave(uint16_t sms, uint16_t ts);

	//void pwmSetup(uint8_t center, uint8_t dir);
	void setPWMchannel(uint8_t ch_num, uint8_t mode, uint8_t plrty, uint8_t opendrain = 1);
	void pwmWrite(uint8_t ch_num, uint16_t val) {_TIM3_(ch_num*4 + 0x30) = val;}
	void pwmEnable(uint8_t ch_num);
	void pwmDisable(uint8_t ch_num);

	void IRQenable() {IRQ_0TO31_SER |= IRQ_BITMASK_TIM3;}
	void IRQdisable() {IRQ_0TO31_CER |= IRQ_BITMASK_TIM3;}

	//capture/compare channels
	void writeCC1(uint16_t val) {_TIM3_(TIMX_CCR1) = val;}
	void writeCC2(uint16_t val) {_TIM3_(TIMX_CCR2) = val;}
	void writeCC3(uint16_t val) {_TIM3_(TIMX_CCR3) = val;}
	void writeCC4(uint16_t val) {_TIM3_(TIMX_CCR4) = val;}

	void CC1output(uint8_t bit) {BB_TIM3_CCER_CC1E = bit;}
	void CC2output(uint8_t bit) {BB_TIM3_CCER_CC2E = bit;}
	void CC3output(uint8_t bit) {BB_TIM3_CCER_CC3E = bit;}
	void CC4output(uint8_t bit) {BB_TIM3_CCER_CC4E = bit;}

	//BB (atomic) stuff
	//update event enable/disable (CR1->UDIS)
	void updateDisable() {BB_TIM3_CR1_UDIS = 0;}
	void updateEnable() {BB_TIM3_CR1_UDIS = 1;}

	//fast interrupt enable/disable (1 or 0)
	void updateInterrupt(uint8_t bit) {BB_TIM3_DIER_UIE = bit;}
	void CC1interrupt(uint8_t bit) {BB_TIM3_DIER_CC1IE = bit;}
	void CC2interrupt(uint8_t bit) {BB_TIM3_DIER_CC2IE = bit;}
	void CC3interrupt(uint8_t bit) {BB_TIM3_DIER_CC3IE = bit;}
	void CC4interrupt(uint8_t bit) {BB_TIM3_DIER_CC4IE = bit;}
	void triggerInterrupt(uint8_t bit) {BB_TIM3_DIER_TIE = bit;}

	//check status flags
	uint8_t checkUpdate() {return (_TIM3_(TIMX_SR) & TIMX_SR_UIF);}
	uint8_t checkCC1() {return ((_TIM3_(TIMX_SR) & TIMX_SR_CC1IF)>>1);}
	uint8_t checkCC2() {return ((_TIM3_(TIMX_SR) & TIMX_SR_CC2IF)>>2);}
	uint8_t checkCC3() {return ((_TIM3_(TIMX_SR) & TIMX_SR_CC3IF)>>3);}
	uint8_t checkCC4() {return ((_TIM3_(TIMX_SR) & TIMX_SR_CC4IF)>>4);}
	uint8_t checkTrigger() {return ((_TIM3_(TIMX_SR) & TIMX_SR_TIF)>>6);}

	//event generators
	void updateEvent() {BB_TIM2_EGR_UG = 1;}
	void CC1event() {BB_TIM2_EGR_CC1G = 1;}
	void CC2event() {BB_TIM2_EGR_CC2G = 1;}
	void CC3event() {BB_TIM2_EGR_CC3G = 1;}
	void CC4event() {BB_TIM2_EGR_CC4G = 1;}
	void triggerEvent() {BB_TIM2_EGR_TG = 1;}

	//interrupt flag cleaners, should use BB for these most certainly
	void clearUpdate() {BB_TIM3_SR_UIF = 0;} //{_TIM3_(TIMX_SR) &= ~TIMX_SR_UIF;}
	void clearCC1() {BB_TIM3_SR_CC1IF = 0;} //{_TIM3_(TIMX_SR) &= ~TIMX_SR_CC1IF;}
	void clearCC2() {BB_TIM3_SR_CC2IF = 0;} //{_TIM3_(TIMX_SR) &= ~TIMX_SR_CC2IF;}
	void clearCC3() {BB_TIM3_SR_CC3IF = 0;} //{_TIM3_(TIMX_SR) &= ~TIMX_SR_CC3IF;}
	void clearCC4() {BB_TIM3_SR_CC4IF = 0;} //{_TIM3_(TIMX_SR) &= ~TIMX_SR_CC4IF;}
	void clearTrigger() {BB_TIM3_SR_TIF = 0;} //{_TIM3_(TIMX_SR) &= ~TIMX_SR_TIF;}
	void clearAll() {_TIM3_(TIMX_SR) = 0;}

	//IRQ priority
	void priority(uint8_t pri) {irq_priority(TIM3_IRQ, pri);}

	//DMA stuff
	void DMATRGenable() {_TIM3_(TIMX_DIER) |= TIMX_DIER_TDE;}
	void DMACCenable(uint8_t ch_num = 0);
	void DMAUPenable() {_TIM3_(TIMX_DIER) |= TIMX_DIER_UDE;}
	void DMATRGdisable()  {_TIM3_(TIMX_DIER) &= ~TIMX_DIER_TDE;}
	void DMACCdisable(uint8_t ch_num = 0);
	void DMAUPdisable()  {_TIM3_(TIMX_DIER) &= ~TIMX_DIER_UDE;}
	void DMAburst(uint8_t burst) {_TIM3_(TIMX_DCR) &= ~TIMX_DCR_DBL; _TIM3_(TIMX_DCR) |= ((--burst) << 8);}
	void DMAbase(uint8_t base) {_TIM3_(TIMX_DCR) &= ~TIMX_DCR_DBA; _TIM3_(TIMX_DCR) |= base;}

private:

};

class timer4: public timer
{
public:
	timer4(uint16_t prsclr = 0x0000, uint16_t depth = 0xFFFF): timer(prsclr, depth) {}

 	void init() {timer4_init();}
	void config();
	void enableOnly() {BB_TIM4_CR1_CEN = 1;}
	void enable(uint16_t count = 0);
	void disable() {BB_TIM4_CR1_CEN = 0;}
	uint16_t read() {return _TIM4_(TIMX_CNT);}
	operator uint16_t() {return _TIM1_(TIMX_CNT);}

	//void master(uint16_t mms, uint16_t ccmr = 0);
	void setSlave(uint16_t sms, uint16_t ts);

	//void pwmSetup(uint8_t center, uint8_t dir);
	void setPWMchannel(uint8_t ch_num, uint8_t mode, uint8_t plrty, uint8_t opendrain = 1);// {tim2_pwm a(ch_num); a.init();}
	void pwmWrite(uint8_t ch_num, uint16_t val) {_TIM4_(ch_num*4 + 0x30) = val;}
	void pwmEnable(uint8_t ch_num);
	void pwmDisable(uint8_t ch_num);

	void IRQenable() {IRQ_0TO31_SER |= IRQ_BITMASK_TIM4;}
	void IRQdisable() {IRQ_0TO31_CER |= IRQ_BITMASK_TIM4;}

	//capture/compare channels
	void writeCC1(uint16_t val) {_TIM4_(TIMX_CCR1) = val;}
	void writeCC2(uint16_t val) {_TIM4_(TIMX_CCR2) = val;}
	void writeCC3(uint16_t val) {_TIM4_(TIMX_CCR3) = val;}
	void writeCC4(uint16_t val) {_TIM4_(TIMX_CCR4) = val;}

	void CC1output(uint8_t bit) {BB_TIM4_CCER_CC1E = bit;}
	void CC2output(uint8_t bit) {BB_TIM4_CCER_CC2E = bit;}
	void CC3output(uint8_t bit) {BB_TIM4_CCER_CC3E = bit;}
	void CC4output(uint8_t bit) {BB_TIM4_CCER_CC4E = bit;}

	//BB (atomic) stuff
	//update event enable/disable (CR1->UDIS)
	void updateDisable() {BB_TIM4_CR1_UDIS = 0;}
	void updateEnable() {BB_TIM4_CR1_UDIS = 1;}

	//fast interrupt enable/disable (1 or 0)
	void updateInterrupt(uint8_t bit) {BB_TIM4_DIER_UIE = bit;}
	void CC1interrupt(uint8_t bit) {BB_TIM4_DIER_CC1IE = bit;}
	void CC2interrupt(uint8_t bit) {BB_TIM4_DIER_CC2IE = bit;}
	void CC3interrupt(uint8_t bit) {BB_TIM4_DIER_CC3IE = bit;}
	void CC4interrupt(uint8_t bit) {BB_TIM4_DIER_CC4IE = bit;}
	void triggerInterrupt(uint8_t bit) {BB_TIM4_DIER_TIE = bit;}

	//check status flags
	uint8_t checkUpdate() {return (_TIM4_(TIMX_SR) & TIMX_SR_UIF);}
	uint8_t checkCC1() {return ((_TIM4_(TIMX_SR) & TIMX_SR_CC1IF)>>1);}
	uint8_t checkCC2() {return ((_TIM4_(TIMX_SR) & TIMX_SR_CC2IF)>>2);}
	uint8_t checkCC3() {return ((_TIM4_(TIMX_SR) & TIMX_SR_CC3IF)>>3);}
	uint8_t checkCC4() {return ((_TIM4_(TIMX_SR) & TIMX_SR_CC4IF)>>4);}
	uint8_t checkTrigger() {return ((_TIM4_(TIMX_SR) & TIMX_SR_TIF)>>6);}

	//event generators
	void updateEvent() {BB_TIM4_EGR_UG = 1;}
	void CC1event() {BB_TIM4_EGR_CC1G = 1;}
	void CC2event() {BB_TIM4_EGR_CC2G = 1;}
	void CC3event() {BB_TIM4_EGR_CC3G = 1;}
	void CC4event() {BB_TIM4_EGR_CC4G = 1;}
	void triggerEvent() {BB_TIM4_EGR_TG = 1;}

	//interrupt flag cleaners, should use BB for these most certainly
	void clearUpdate() {BB_TIM4_SR_UIF = 0;} //{_TIM4_(TIMX_SR) &= ~TIMX_SR_UIF;}
	void clearCC1() {BB_TIM4_SR_CC1IF = 0;} //{_TIM4_(TIMX_SR) &= ~TIMX_SR_CC1IF;}
	void clearCC2() {BB_TIM4_SR_CC2IF = 0;} //{_TIM4_(TIMX_SR) &= ~TIMX_SR_CC2IF;}
	void clearCC3() {BB_TIM4_SR_CC3IF = 0;} //{_TIM4_(TIMX_SR) &= ~TIMX_SR_CC3IF;}
	void clearCC4() {BB_TIM4_SR_CC4IF = 0;} //{_TIM4_(TIMX_SR) &= ~TIMX_SR_CC4IF;}
	void clearTrigger() {BB_TIM4_SR_TIF = 0;} //{_TIM4_(TIMX_SR) &= ~TIMX_SR_TIF;}
	void clearAll() {_TIM4_(TIMX_SR) = 0;}

	//IRQ priority
	void priority(uint8_t pri) {irq_priority(TIM4_IRQ, pri);}

		//DMA stuff
	void DMATRGenable() {_TIM4_(TIMX_DIER) |= TIMX_DIER_TDE;}
	void DMACCenable(uint8_t ch_num = 0);
	void DMAUPenable() {_TIM4_(TIMX_DIER) |= TIMX_DIER_UDE;}
	void DMATRGdisable()  {_TIM4_(TIMX_DIER) &= ~TIMX_DIER_TDE;}
	void DMACCdisable(uint8_t ch_num = 0);
	void DMAUPdisable()  {_TIM4_(TIMX_DIER) &= ~TIMX_DIER_UDE;}
	void DMAburst(uint8_t burst) {_TIM4_(TIMX_DCR) &= ~TIMX_DCR_DBL; _TIM4_(TIMX_DCR) |= ((--burst) << 8);}
	void DMAbase(uint8_t base) {_TIM4_(TIMX_DCR) &= ~TIMX_DCR_DBA; _TIM4_(TIMX_DCR) |= base;}

private:
};

class timer1_s
{
public:
	timer1_s() {};
	void init();
	void init (uint16_t depth, uint16_t prescaler = 0);
	void init (uint16_t depth, uint16_t prescaler = 0, uint16_t cc1 = 0, uint16_t cc2 = 0, uint16_t cc3 = 0, uint16_t cc4 = 0);
	void enable();
	void disable();

};

#endif /* STM32F103_TIMERS_H_ */
