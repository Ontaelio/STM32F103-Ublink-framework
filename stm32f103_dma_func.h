/*
 * STM32F103 DMA functions header file
 * Part of STM32F103 register and peripherals library
 *
 * Dpcumentation available in the provided MD file.
 *
 * (c) 2019-2020 Dmitry Reznikov ontaelio(at)gmail.com
 *
 * Can be freely used according to the GNU GPL license.
 */

#ifndef STM32F103_DMA_FUNC_H_
#define STM32F103_DMA_FUNC_H_

#include <stdio.h>
#include <stdint.h>
#include <stm32f103_usart_func.h>
#include <stm32f103_dma_reg.h>
#include <stm32f103_rcc_reg.h>
#include <stm32f103_spi_func.h>
#include <stm32f103_adc_func.h>
#include <stm32f103_i2c_master.h>

#ifndef STM32F103_TIMERS_REG_H_
//interrupt set-enable registers
#define IRQ_0TO31_SER	*(volatile uint32_t *) 0xE000E100
#define IRQ_0TO31_CER	*(volatile uint32_t *) 0xE000E180

#define IRQ_DMA1_Channel1	0x00000800
#define IRQ_DMA1_Channel2	0x00001000
#define IRQ_DMA1_Channel3	0x00002000
#define IRQ_DMA1_Channel4	0x00004000
#define IRQ_DMA1_Channel5	0x00008000
#define IRQ_DMA1_Channel6	0x00010000
#define IRQ_DMA1_Channel7	0x00020000
#endif //timers library defined end

#define DMA_SPI1_DR	0x4001300C
#define DMA_SPI2_DR	0x4001380C

#define DMA_EN		(uint16_t)0x0001
#define DMA_TCIE	(uint16_t)0x0002
#define DMA_HTIE	(uint16_t)0x0004
#define DMA_TEIE	(uint16_t)0x0008
#define DMA_DIR		(uint16_t)0x0010
#define DMA_CIRC	(uint16_t)0x0020
#define DMA_PINC	(uint16_t)0x0040
#define DMA_MINC	(uint16_t)0x0080
#define DMA_PSIZE8	(uint16_t)0x0000
#define DMA_PSIZE16	(uint16_t)0x0100
#define DMA_PSIZE32	(uint16_t)0x0200
#define DMA_MSIZE8	(uint16_t)0x0000
#define DMA_MSIZE16	(uint16_t)0x0400
#define DMA_MSIZE32	(uint16_t)0x0800
#define DMA_PLLOW	(uint16_t)0x0000
#define DMA_PLMEDIUM (uint16_t)0x1000
#define DMA_PLHIGH	(uint16_t)0x2000
#define DMA_PLVHIGH	(uint16_t)0x3000
#define DMA_MEM2MEM	(uint16_t)0x4000

#define PER2MEM			0x0000
#define MEM2PER			0x0010
#define MEM2MEM			0x4000
#define PER2MEM_CIRC	0x0020
#define MEM2PER_CIRC	0x0030
//Circular mode can not be used with mem2mem (p. 279 of Ref Man)

#define PRI_LOW			0x0000
#define PRI_MEDIUM		0x1000
#define PRI_HIGH		0x2000
#define PRI_VHIGH		0x3000

#define PSIZE8			0x0000
#define PSIZE16			0x0100
#define PSIZE32			0x0200
#define PSIZE8_INCR		0x0040
#define PSIZE16_INCR	0x0140
#define PSIZE32_INCR	0x0240

#define MSIZE8			0x0000
#define MSIZE16			0x0400
#define MSIZE32			0x0800
#define MSIZE8_INCR		0x0080
#define MSIZE16_INCR	0x0480
#define MSIZE32_INCR	0x0880

#define DMA_COMPLETE	0x0002
#define DMA_HALF		0x0004
#define DMA_HALF_COMPLETE	0x0006
#define DMA_ERROR		0x0008

#define DMA_TIM1_CH1	0x12
#define DMA_TIM1_CH4	0x14
#define DMA_TIM1_TRIG	0x1C
#define DMA_TIM1_COM	0x10
#define DMA_TIM1_UP		0x15
#define DMA_TIM1_CH3	0x16

#define DMA_TIM2_CH3	0x21
#define DMA_TIM2_UP		0x22
#define DMA_TIM2_CH1	0x25
#define DMA_TIM2_CH2	0x27
#define DMA_TIM2_CH4	0x2F

#define DMA_TIM3_CH3	0x32
#define DMA_TIM3_CH4	0x33
#define DMA_TIM3_UP		0x3B
#define DMA_TIM3_CH1	0x36
#define DMA_TIM3_TRIG	0x3E

#define DMA_TIM4_CH1	0x41
#define DMA_TIM4_CH2	0x44
#define DMA_TIM4_CH3	0x45
#define DMA_TIM4_UP		0x47

//to use with <<(Channel-1) on IFCR
#define DMA_GIFCLEAR (uint32_t)0x00000001


void dma1_reset(uint8_t channel, uint16_t ccr = 0);
void dma1_setup(uint8_t channel, uint32_t paddr, uint32_t maddr, uint16_t datanum, uint16_t ccr);

//DMA registers are calculated as [offset] + 0d20*(channel_num - 1)

inline void dma1_init() {_RCC_(RCC_AHBENR) |= RCC_AHBENR_DMA1EN;}


inline void dma1_ifclear(uint8_t channel) {_DMA1_(DMA_IFCR) |= DMA_IFCR_CGIF << (--channel)*4;}
inline void dma1_completeclear(uint8_t channel) {_DMA1_(DMA_IFCR) |= DMA_IFCR_CTCIF << (--channel)*4;}
inline void dma1_halfclear(uint8_t channel) {_DMA1_(DMA_IFCR) |= DMA_IFCR_CHTIF << (--channel)*4;}
inline void dma1_errorclear(uint8_t channel) {_DMA1_(DMA_IFCR) |= DMA_IFCR_CTEIF << (--channel)*4;}
inline void dma1_paddr(uint8_t channel, uint32_t paddr) {_DMA1_(DMA_CPAR + (--channel)*20) = paddr;}
inline void dma1_maddr(uint8_t channel, uint32_t maddr) {_DMA1_(DMA_CMAR + (--channel)*20) = maddr;}
inline void dma1_datanum(uint8_t channel, uint16_t datanum) {_DMA1_(DMA_CNDTR + (--channel)*20) = datanum;};
inline void dma1_enable(uint8_t channel) {_DMA1_(DMA_CCR + (--channel)*20) |= DMA_CCR_EN;}
inline void dma1_disable(uint8_t channel) {_DMA1_(DMA_CCR + (--channel)*20) &= ~DMA_CCR_EN;}
inline void dma1_IRQenable(uint8_t channel) {IRQ_0TO31_SER |= (uint32_t)0x0000400<<channel;}
inline void dma1_IRQdisable(uint8_t channel) {IRQ_0TO31_CER |= (uint32_t)0x0000400<<channel;}
inline void dma1_errorenable(uint8_t channel) {_DMA1_(DMA_CCR + (--channel)*20) |= DMA_CCR_TEIE;}
inline void dma1_halfenable(uint8_t channel) {_DMA1_(DMA_CCR + (--channel)*20) |= DMA_CCR_HTIE;}
inline void dma1_completeenable(uint8_t channel) {_DMA1_(DMA_CCR + (--channel)*20) |= DMA_CCR_TCIE;}
inline void dma1_errordisable(uint8_t channel) {_DMA1_(DMA_CCR + (--channel)*20) &= ~DMA_CCR_TEIE;}
inline void dma1_halfdisable(uint8_t channel) {_DMA1_(DMA_CCR + (--channel)*20) &= ~DMA_CCR_HTIE;}
inline void dma1_completedisable(uint8_t channel) {_DMA1_(DMA_CCR + (--channel)*20) &= ~DMA_CCR_TCIE;}

inline uint8_t dma1_globalinterrupt(uint8_t channel) {return ((_DMA1_(DMA_ISR)>>((--channel)*4))&1);}
inline uint8_t dma1_transfercomplete(uint8_t channel) {return ((_DMA1_(DMA_ISR)>>((--channel)*4 + 1))&1);}
inline uint8_t dma1_halftransfer(uint8_t channel) {return ((_DMA1_(DMA_ISR)>>((--channel)*4 + 2))&1);}
inline uint8_t dma1_transfererror(uint8_t channel) {return ((_DMA1_(DMA_ISR)>>((--channel)*4 + 3))&1);}



class usart1;
class usart2;
class usart3;
class analog_cont;

class dma1
{
public:
	dma1(): cha (0){}
	dma1(uint8_t tmr): cha(tmr){}

	void init(uint8_t c, uint32_t paddr, uint32_t maddr, uint16_t ccr); //generic

	void init(uint8_t c, uint8_t* src, uint8_t* targ, uint16_t pri = DMA_PLHIGH); // mem2mem 8bits
	void init(uint8_t c, uint16_t* src, uint16_t* targ, uint16_t pri = DMA_PLHIGH);  // mem2mem 16bits
	void init(uint8_t c, uint32_t* src, uint32_t* targ, uint16_t pri = DMA_PLHIGH);  // mem2mem 32bits

	void init(uint16_t* src, spi1_slave targ, uint16_t pri = DMA_PLHIGH); // mem 2 spi1 16bit
	void init(uint16_t* src, spi2_slave targ, uint16_t pri = DMA_PLHIGH); // mem 2 spi2 16bit
	void init(uint8_t* src, spi1_slave targ, uint16_t pri = DMA_PLHIGH); // mem 2 spi1 8bit
	void init(uint8_t* src, spi2_slave targ, uint16_t pri = DMA_PLHIGH); // mem 2 spi2 8bit
	void init(spi1_slave src, uint16_t* targ, uint16_t pri = DMA_PLHIGH); // spi1 2 mem 16bit
	void init(spi2_slave src, uint16_t* targ, uint16_t pri = DMA_PLHIGH); // spi2 2 mem 16bit
	void init(spi1_slave src, uint8_t* targ, uint16_t pri = DMA_PLHIGH); // spi1 2 mem 8bit
	void init(spi2_slave src, uint8_t* targ, uint16_t pri = DMA_PLHIGH); // spi2 2 mem 8bit

	void init(uint8_t* src, i2c1_slave targ, uint16_t pri = DMA_PLHIGH); // mem 2 i2c1
	void init(uint8_t* src, i2c2_slave targ, uint16_t pri = DMA_PLHIGH); // mem 2 i2c2
	void init(i2c1_slave src, uint8_t* targ, uint16_t pri = DMA_PLHIGH); // i2c1 2 mem
	void init(i2c2_slave src, uint8_t* targ, uint16_t pri = DMA_PLHIGH); // i2c2 2 mem

	void init(uint8_t* src, usart1 targ, uint16_t pri = DMA_PLHIGH); //mem 2 usart1 							ok
	void init(uint8_t* src, usart2 targ, uint16_t pri = DMA_PLHIGH); //mem 2 usart2
	void init(uint8_t* src, usart3 targ, uint16_t pri = DMA_PLHIGH); //mem 2 usart3
	void init(usart1 src, uint8_t* targ, uint16_t pri = DMA_PLHIGH); //usart1 2 mem 							ok
	void init(usart2 src, uint8_t* targ, uint16_t pri = DMA_PLHIGH); //usart2 2 mem
	void init(usart3 src, uint8_t* targ, uint16_t pri = DMA_PLHIGH); //usart3 2 mem

	void init(analog_cont src, uint16_t targ, uint16_t pri = DMA_PLHIGH); //adc1 2 mem
	void init(analog_cont src1, analog_cont src2, uint32_t targ, uint16_t pri = DMA_PLHIGH); //adc1&2 2 mem

	void init(usart1 src, spi1_slave targ, uint16_t pri = DMA_PLHIGH); //will write the rest once tested

	void init(uint16_t* src, tim1_pwm targ, uint8_t uedma = 0, uint16_t pri = DMA_PLVHIGH); //copy pwm value at the CC event		ok
	void init(uint16_t* src, tim2_pwm targ, uint8_t uedma = 0, uint16_t pri = DMA_PLVHIGH);
	void init(uint16_t* src, tim3_pwm targ, uint8_t uedma = 0, uint16_t pri = DMA_PLVHIGH);
	void init(uint16_t* src, tim4_pwm targ, uint8_t uedma = 0, uint16_t pri = DMA_PLVHIGH);

	void init(uint16_t* src, timer1 targ, uint8_t numofch = 4, uint16_t pri = DMA_PLVHIGH); // copy one-four CC values at UE		ok
	void init(uint16_t* src, timer2 targ, uint8_t numofch = 4, uint16_t pri = DMA_PLVHIGH);
	void init(uint16_t* src, timer3 targ, uint8_t numofch = 4, uint16_t pri = DMA_PLVHIGH);
	void init(uint16_t* src, timer4 targ, uint8_t numofch = 4, uint16_t pri = DMA_PLVHIGH);


	void init(uint16_t* src, gpioA targ, int16_t pri = DMA_PLHIGH);	// use ODR, overwrite all 16 pins			ok
	void init(uint16_t* src, gpioB targ, int16_t pri = DMA_PLHIGH);
	void init(uint16_t* src, gpioC targ, int16_t pri = DMA_PLHIGH);

	void init(uint32_t* src, gpioA targ, int16_t pri = DMA_PLHIGH); // use BSRR (atomic write)					ok
	void init(uint32_t* src, gpioB targ, int16_t pri = DMA_PLHIGH);
	void init(uint32_t* src, gpioC targ, int16_t pri = DMA_PLHIGH);


	void transfer(uint16_t num = 1); //do one transfer
	void start(uint16_t num = 1); //start circular transfer
	void stop(); //stop circular transfer
	void disable() {_DMA1_(DMA_CCR + cha*20) &= ~DMA_CCR_EN;} //disable dma channel
	void priority(uint16_t pri);

	void reset() {dma1_reset((cha + 1), 0);}

	void IRQenable() {IRQ_0TO31_SER |= (uint32_t)0x0000800<<cha;}
	void IRQdisable() {IRQ_0TO31_CER |= (uint32_t)0x0000800<<cha;}

	void enableError() {dma1_errorenable(cha + 1);}
	void enableHalf() {dma1_halfenable(cha + 1);}
	void enableComplete() {dma1_completeenable(cha + 1);}
	void disableError() {dma1_errordisable(cha + 1);}
	void disableHalf() {dma1_halfdisable(cha + 1);}
	void disableComplete() {dma1_completedisable(cha + 1);}

	uint8_t interrupt(uint8_t channel) {return ((_DMA1_(DMA_ISR)>>(cha*4))&1);}
	uint8_t complete(uint8_t channel) {return ((_DMA1_(DMA_ISR)>>(cha*4 + 1))&1);}
	uint8_t half(uint8_t channel) {return ((_DMA1_(DMA_ISR)>>(cha*4 + 2))&1);}
	uint8_t error(uint8_t channel) {return ((_DMA1_(DMA_ISR)>>(cha*4 + 3))&1);}


	void clearError() {dma1_errorclear((cha + 1));}
	void clearHalf() {dma1_halfclear((cha + 1));}
	void clearComplete() {dma1_completeclear((cha + 1));}
	void clearAll() {dma1_ifclear((cha + 1));}

	uint8_t cha;
	//uint32_t* baza = _DMA1_(0);
private:
	void setDMAtimerChannel(uint8_t &c);
};

typedef dma1 dma;

#endif /* STM32F103_DMA_FUNC_H_ */
