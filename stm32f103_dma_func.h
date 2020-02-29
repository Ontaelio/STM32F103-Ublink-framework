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
#include <stm32f103_dma_reg.h>
#include <stm32f103_rcc_reg.h>
#include <stm32f103_spi_reg.h>

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
inline void dma1_enable(uint8_t channel) {_DMA1_(DMA_CCR + (--channel)*20) |= DMA_EN;}
inline void dma1_disable(uint8_t channel) {_DMA1_(DMA_CCR + (--channel)*20) &= ~DMA_EN;}
inline void dma1_IRQenable(uint8_t channel) {IRQ_0TO31_SER |= (uint32_t)0x0000400<<channel;}
inline void dma1_IRQdisable(uint8_t channel) {IRQ_0TO31_CER |= (uint32_t)0x0000400<<channel;}

inline uint8_t dma1_transfercomplete(uint8_t channel) {return ((_DMA1_(DMA_ISR)>>((--channel)*4 + 1))&1);}


//void dma1_ifclear(uint8_t channel);
//void dma1_completeclear(uint8_t channel);
//void dma1_halfclear(uint8_t channel);
//void dma1_errorclear(uint8_t channel);
//void dma1_paddr(uint8_t channel, uint32_t paddr);
//void dma1_maddr(uint8_t channel, uint32_t maddr);
//void dma1_datanum(uint8_t channel, uint16_t datanum);
//void dma1_enable(uint8_t channel);
//void dma1_disable(uint8_t channel);
//void dma1_IRQenable(uint8_t channel);
//void dma1_IRQdisable(uint8_t channel);


/*
void dma1_msize(uint8_t channel, uint8_t size);
void dma1_psize(uint8_t channel, uint8_t size);
void dma1_pl(uint8_t channel, uint8_t pl);
void dma1_dir(uint8_t channel, uint8_t dir);
void dma1_mem2mem(uint8_t channel, uint8_t m2m);
void dma1_circ(uint8_t channel, uint8_t circ);
void dma1_minc(uint8_t channel, uint8_t minc);
void dma1_pinc(uint8_t channel, uint8_t pinc);
*/

class dma1_channel{
public:
	dma1_channel(uint8_t chnl): channel(chnl), ccr(0), cndtr(0), cpar(0), cmar(0){}
	dma1_channel();
	void init() {dma1_init();}
	void paddr(uint32_t s) {cpar = s;}
	void maddr(uint32_t t) {cmar = t;}
	void datanum(uint16_t n) {cndtr = n;}
	void config(uint16_t cval) {ccr = cval;}
	void size(uint8_t per, uint8_t mem) {ccr &= ~0xF0FF; ccr|= per<<8 | mem<<10;}
	void increment(uint8_t per, uint8_t mem) {ccr &= ~0xFF3F; ccr|= per<<6 | mem<<7;}
	void priority(uint8_t pri) {ccr&= ~0xCFFF; ccr |= pri<<12;}
	void direction(uint8_t dir, uint8_t circ, uint8_t m2m) {ccr&= ~0xBFCF; ccr|= dir<<4 | circ<<5 | m2m<<14;}
	void interrupts(uint8_t irq) {ccr&=0xFFF1; ccr |= irq<<1;}
	void setup() {dma1_setup(channel, cpar, cmar, cndtr, ccr);}
	void reset() {dma1_reset(channel, 0); setup();}
	void enable() {dma1_enable(channel);}
	void disable() {dma1_disable(channel);}

	void IRQenable() {IRQ_0TO31_SER |= (uint32_t)0x0000400<<channel;}
	void IRQdisable() {IRQ_0TO31_CER |= (uint32_t)0x0000400<<channel;}

	void clearError() {dma1_errorclear(channel);}
	void clearHalf() {dma1_halfclear(channel);}
	void clearComplete() {dma1_completeclear(channel);}
	void clearAll() {dma1_ifclear(channel);}


	uint8_t channel;
	uint16_t ccr, cndtr;
	uint32_t cpar, cmar;
};








#endif /* STM32F103_DMA_FUNC_H_ */
