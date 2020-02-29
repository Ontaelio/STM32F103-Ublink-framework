/*
 * STM32F103 DMA functions source file
 * Part of STM32F103 register and peripherals library
 *
 * Dpcumentation available in the provided MD file.
 *
 * (c) 2019-2020 Dmitry Reznikov ontaelio(at)gmail.com
 *
 * Can be freely used according to the GNU GPL license.
 */

#include <stm32f103_dma_func.h>

void dma1_reset(uint8_t channel, uint16_t ccr)
{
	--channel;
	_DMA1_(DMA_CCR + channel*20) = ccr; //config bits
	_DMA1_(DMA_IFCR) |= DMA_IFCR_CGIF << channel*4; //clear global interrupts
}

void dma1_setup(uint8_t channel, uint32_t paddr, uint32_t maddr, uint16_t datanum, uint16_t ccr)
{
	--channel;
	_DMA1_(DMA_CCR + channel*20) &= ~DMA_EN; //disable
	_DMA1_(DMA_CMAR + channel*20) = maddr; //set memory address
	_DMA1_(DMA_CPAR + channel*20) = paddr; //set peripheral address
	_DMA1_(DMA_CNDTR + channel*20) = datanum; //number of data to be transferred
	_DMA1_(DMA_CCR + channel*20) = ccr; //config bits
}



