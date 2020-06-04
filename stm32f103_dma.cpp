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

#include <stm32f103_dma.h>

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



void dma1::transfer(uint16_t num)
{
	_DMA1_(DMA_CCR + cha*20) &= ~DMA_CCR_EN;
	_DMA1_(DMA_CNDTR + cha*20) = num;
	_DMA1_(DMA_CCR + cha*20) |= DMA_CCR_EN;
}
void dma1::start(uint16_t num)
{
	_DMA1_(DMA_CCR + cha*20) &= ~DMA_CCR_EN;
	_DMA1_(DMA_CNDTR + cha*20) = num;
	_DMA1_(DMA_CCR + cha*20) |= DMA_CCR_CIRC;
	_DMA1_(DMA_CCR + cha*20) |= DMA_CCR_EN;
}

void dma1::stop()
{
	_DMA1_(DMA_CCR + cha*20) &= ~DMA_CCR_EN;
	_DMA1_(DMA_CCR + cha*20) &= ~DMA_CCR_CIRC;
}

void dma1::priority(uint16_t pri)
{
	_DMA1_(DMA_CCR + cha*20) &= ~0x4FFF;
	_DMA1_(DMA_CCR + cha*20) |= pri;
}

void dma1::setDMAtimerChannel(uint8_t &c)
{
	//uint32_t toffsets[4] {0x40012C00,0x40000000,0x40000400,0x40000800};
	//uint8_t t = c>>4;

	switch (c)
	{
		case DMA_TIM1_CH1: _TIM1_(TIMX_DIER) |= TIMX_DIER_CC1DE; break;
		case DMA_TIM1_CH4: _TIM1_(TIMX_DIER) |= TIMX_DIER_CC4DE; break;
		case DMA_TIM1_TRIG:_TIM1_(TIMX_DIER) |= TIMX_DIER_TDE; break;
		case DMA_TIM1_COM: _TIM1_(TIMX_DIER) |= TIMX_DIER_COMDE; c = 0x14; break;
		case DMA_TIM1_UP:  _TIM1_(TIMX_DIER) |= TIMX_DIER_UDE; break;
		case DMA_TIM1_CH3: _TIM1_(TIMX_DIER) |= TIMX_DIER_CC3DE; break;

		case DMA_TIM2_CH3: _TIM2_(TIMX_DIER) |= TIMX_DIER_CC3DE; break;
		case DMA_TIM2_UP:  _TIM2_(TIMX_DIER) |= TIMX_DIER_UDE; break;
		case DMA_TIM2_CH1: _TIM2_(TIMX_DIER) |= TIMX_DIER_CC1DE; break;
		case DMA_TIM2_CH2: _TIM2_(TIMX_DIER) |= TIMX_DIER_CC2DE; break;
		case DMA_TIM2_CH4: _TIM2_(TIMX_DIER) |= TIMX_DIER_CC4DE; break;

		case DMA_TIM3_CH3: _TIM3_(TIMX_DIER) |= TIMX_DIER_CC3DE; break;
		case DMA_TIM3_CH4: _TIM3_(TIMX_DIER) |= TIMX_DIER_CC4DE; break;
		case DMA_TIM3_UP:  _TIM3_(TIMX_DIER) |= TIMX_DIER_UDE; break;
		case DMA_TIM3_CH1: _TIM3_(TIMX_DIER) |= TIMX_DIER_CC1DE; break;
		case DMA_TIM3_TRIG:_TIM3_(TIMX_DIER) |= TIMX_DIER_TDE; break;

		case DMA_TIM4_CH1: _TIM4_(TIMX_DIER) |= TIMX_DIER_CC1DE; break;
		case DMA_TIM4_CH2: _TIM4_(TIMX_DIER) |= TIMX_DIER_CC2DE; break;
		case DMA_TIM4_CH3: _TIM4_(TIMX_DIER) |= TIMX_DIER_CC3DE; break;
		case DMA_TIM4_UP:  _TIM4_(TIMX_DIER) |= TIMX_DIER_UDE; break;

		default: break;
	}

	c &= 7; // get the channel num
	--c; //Subtract one to use later with CCR register
}

void dma1::init(uint8_t c, uint32_t paddr, uint32_t maddr, uint16_t ccr)
{
	// generic DMA setup. The DMA enable bit in the peripheral must be set manually
	cha = c-1;
	_DMA1_(DMA_CCR + cha*20) &= ~DMA_CCR_EN; //disable
	_DMA1_(DMA_CMAR + cha*20) = maddr; //set memory address
	_DMA1_(DMA_CPAR + cha*20) = paddr; //set peripheral address
	//priority, 8 bit mem, 8 bit periph, memory increments, from mem
	_DMA1_(DMA_CCR + cha*20) = ccr;
}

void dma1::init(uint8_t* src, uint8_t* targ, uint8_t c, uint16_t pri)
{
	//if timer was selected the c argument is discarded
	if (no_timer) cha = c-1; else setDMAtimerChannel(cha);

	_DMA1_(DMA_CCR + cha*20) &= ~DMA_CCR_EN; //disable
	_DMA1_(DMA_CMAR + cha*20) = (uint32_t)targ; //set memory address (to)
	_DMA1_(DMA_CPAR + cha*20) = (uint32_t)src; //set peripheral address (from)
	//priority, 8 bit mem, 8 bit periph, memory increments,
	_DMA1_(DMA_CCR + cha*20) = (uint16_t)(pri | DMA_MSIZE8 | DMA_PSIZE8 | DMA_CCR_MINC);
	//if timer not connected, memory-to-memory
	if (no_timer) _DMA1_(DMA_CCR + cha*20) |= DMA_MEM2MEM;
}

void dma1::init(uint16_t* src, uint16_t* targ, uint8_t c, uint16_t pri)
{
	//if timer was selected the c argument is discarded
	if (no_timer) cha = c-1; else setDMAtimerChannel(cha);

	_DMA1_(DMA_CCR + cha*20) &= ~DMA_CCR_EN; //disable
	_DMA1_(DMA_CMAR + cha*20) = (uint32_t)targ; //set memory address (to)
	_DMA1_(DMA_CPAR + cha*20) = (uint32_t)src; //set peripheral address (from)
	//priority, 16 bit mem, 16 bit periph, memory increments,
	_DMA1_(DMA_CCR + cha*20) = (uint16_t)(pri | DMA_MSIZE16 | DMA_PSIZE16 | DMA_CCR_MINC);
	//if timer not connected, memory-to-memory
	if (no_timer) _DMA1_(DMA_CCR + cha*20) |= DMA_MEM2MEM;
}

void dma1::init(uint32_t* src, uint32_t* targ, uint8_t c, uint16_t pri)
{
	//if timer was selected the c argument is discarded
	if (no_timer) cha = c-1; else setDMAtimerChannel(cha);

	_DMA1_(DMA_CCR + cha*20) &= ~DMA_CCR_EN; //disable
	_DMA1_(DMA_CMAR + cha*20) = (uint32_t)targ; //set memory address (to)
	_DMA1_(DMA_CPAR + cha*20) = (uint32_t)src; //set peripheral address (from)
	//priority, 32 bit mem, 32 bit periph, memory increments,
	_DMA1_(DMA_CCR + cha*20) = (uint16_t)(pri | DMA_MSIZE32 | DMA_PSIZE32 | DMA_CCR_MINC);
	//if timer not connected, memory-to-memory
	if (no_timer) _DMA1_(DMA_CCR + cha*20) |= DMA_MEM2MEM;
}

void dma1::init(uint16_t* src, spi1_slave targ, uint16_t pri)
{
	if (no_timer)
	{
	cha = 3-1; //Subtract one to use later with CCR register; channel 3 (SPI1 TX)
	targ.DMATXenable();
	}
	else setDMAtimerChannel(cha);

	_DMA1_(DMA_CCR + cha*20) &= ~DMA_CCR_EN; //disable
	_DMA1_(DMA_CMAR + cha*20) = (uint32_t)src; //set memory address
	_DMA1_(DMA_CPAR + cha*20) = (uint32_t)&(_SPI1_(SPI_DR)); //set peripheral address
	//priority, 16 bit mem, 16 bit periph, memory increments, from mem(dir=1)
	_DMA1_(DMA_CCR + cha*20) = (uint16_t)(pri | DMA_MSIZE16 | DMA_PSIZE16 | DMA_CCR_MINC | DMA_CCR_DIR);
}

void dma1::init(uint16_t* src, spi2_slave targ, uint16_t pri)
{
	if (no_timer)
	{
	cha = 5-1; //Subtract one to use later with CCR register; channel 5 (SPI2 TX)
	targ.DMATXenable();
	}
	else setDMAtimerChannel(cha);

	_DMA1_(DMA_CCR + cha*20) &= ~DMA_CCR_EN; //disable
	_DMA1_(DMA_CMAR + cha*20) = (uint32_t)src; //set memory address
	_DMA1_(DMA_CPAR + cha*20) = (uint32_t)&(_SPI2_(SPI_DR)); //set peripheral address
	//priority, 16 bit mem, 16 bit periph, memory increments, from mem(dir=1)
	_DMA1_(DMA_CCR + cha*20) = (uint16_t)(pri | DMA_MSIZE16 | DMA_PSIZE16 | DMA_CCR_MINC | DMA_CCR_DIR);
}

void dma1::init(uint8_t* src, spi1_slave targ, uint16_t pri)
{
	if (no_timer)
	{
	cha = 3-1; //Subtract one to use later with CCR register; channel 3 (SPI1 TX)
	targ.DMATXenable();
	}
	else setDMAtimerChannel(cha);

	_DMA1_(DMA_CCR + cha*20) &= ~DMA_CCR_EN; //disable
	_DMA1_(DMA_CMAR + cha*20) = (uint32_t)src; //set memory address
	_DMA1_(DMA_CPAR + cha*20) = (uint32_t)&(_SPI1_(SPI_DR)); //set peripheral address
	//priority, 8 bit mem, 8 bit periph, memory increments, from mem(dir=1)
	_DMA1_(DMA_CCR + cha*20) = (uint16_t)(pri | DMA_MSIZE8 | DMA_PSIZE8 | DMA_CCR_MINC | DMA_CCR_DIR);
}

void dma1::init(uint8_t* src, spi2_slave targ, uint16_t pri)
{
	if (no_timer)
	{
	cha = 5-1; //Subtract one to use later with CCR register; channel 5 (SPI2 TX)
	targ.DMATXenable();
	}
	else setDMAtimerChannel(cha);

	_DMA1_(DMA_CCR + cha*20) &= ~DMA_CCR_EN; //disable
	_DMA1_(DMA_CMAR + cha*20) = (uint32_t)src; //set memory address
	_DMA1_(DMA_CPAR + cha*20) = (uint32_t)&(_SPI2_(SPI_DR)); //set peripheral address
	//priority, 8 bit mem, 8 bit periph, memory increments, from mem(dir=1)
	_DMA1_(DMA_CCR + cha*20) = (uint16_t)(pri | DMA_MSIZE8 | DMA_PSIZE8 | DMA_CCR_MINC | DMA_CCR_DIR);
}

void dma1::init(spi1_slave src, uint16_t* targ, uint16_t pri)
{
	if (no_timer)
	{
	cha = 2-1; //Subtract one to use later with CCR register; channel 2 (SPI1 RX)
	src.DMARXenable();
	}
	else setDMAtimerChannel(cha);

	_DMA1_(DMA_CCR + cha*20) &= ~DMA_CCR_EN; //disable
	_DMA1_(DMA_CMAR + cha*20) = (uint32_t)targ; //set memory address
	_DMA1_(DMA_CPAR + cha*20) = (uint32_t)&(_SPI1_(SPI_DR)); //set peripheral address
	//priority, 16 bit mem, 16 bit periph, memory increments,
	_DMA1_(DMA_CCR + cha*20) = (uint16_t)(pri | DMA_MSIZE16 | DMA_PSIZE16 | DMA_CCR_MINC);
}

void dma1::init(spi2_slave src, uint16_t* targ, uint16_t pri)
{
	if (no_timer)
	{
	cha = 4-1; //Subtract one to use later with CCR register; channel 4 (SPI2 RX)
	src.DMARXenable();
	}
	else setDMAtimerChannel(cha);

	_DMA1_(DMA_CCR + cha*20) &= ~DMA_CCR_EN; //disable
	_DMA1_(DMA_CMAR + cha*20) = (uint32_t)targ; //set memory address
	_DMA1_(DMA_CPAR + cha*20) = (uint32_t)&(_SPI2_(SPI_DR)); //set peripheral address
	//priority, 16 bit mem, 16 bit periph, memory increments,
	_DMA1_(DMA_CCR + cha*20) = (uint16_t)(pri | DMA_MSIZE16 | DMA_PSIZE16 | DMA_CCR_MINC);
}

void dma1::init(spi1_slave src, uint8_t* targ, uint16_t pri)
{
	if (no_timer)
	{
	cha = 2-1; //Subtract one to use later with CCR register; channel 2 (SPI1 RX)
	src.DMARXenable();
	}
	else setDMAtimerChannel(cha);

	_DMA1_(DMA_CCR + cha*20) &= ~DMA_CCR_EN; //disable
	_DMA1_(DMA_CMAR + cha*20) = (uint32_t)targ; //set memory address
	_DMA1_(DMA_CPAR + cha*20) = (uint32_t)&(_SPI1_(SPI_DR)); //set peripheral address
	//priority, 8 bit mem, 8 bit periph, memory increments,
	_DMA1_(DMA_CCR + cha*20) = (uint16_t)(pri | DMA_MSIZE8 | DMA_PSIZE8 | DMA_CCR_MINC);
}

void dma1::init(spi2_slave src, uint8_t* targ, uint16_t pri)
{
	if (no_timer)
	{
	cha = 4-1; //Subtract one to use later with CCR register; channel 4 (SPI2 RX)
	src.DMARXenable();
	}
	else setDMAtimerChannel(cha);

	_DMA1_(DMA_CCR + cha*20) &= ~DMA_CCR_EN; //disable
	_DMA1_(DMA_CMAR + cha*20) = (uint32_t)targ; //set memory address
	_DMA1_(DMA_CPAR + cha*20) = (uint32_t)&(_SPI2_(SPI_DR)); //set peripheral address
	//priority, 8 bit mem, 8 bit periph, memory increments,
	_DMA1_(DMA_CCR + cha*20) = (uint16_t)(pri | DMA_MSIZE8 | DMA_PSIZE8 | DMA_CCR_MINC);
}

void dma1::init(uint8_t* src, i2c1_slave targ, uint16_t pri)
{
	if (no_timer)
	{
	cha = 6-1; //Subtract one to use later with CCR register; channel 6 (I2C1 TX)
	targ.DMAenable();
	}
	else setDMAtimerChannel(cha);

	_DMA1_(DMA_CCR + cha*20) &= ~DMA_CCR_EN; //disable
	_DMA1_(DMA_CMAR + cha*20) = (uint32_t)src; //set memory address
	_DMA1_(DMA_CPAR + cha*20) = (uint32_t)&(_I2C1_(I2C_DR)); //set peripheral address
	//priority, 8 bit mem, 8 bit periph, memory increments, from mem(dir=1)
	_DMA1_(DMA_CCR + cha*20) = (uint16_t)(pri | DMA_MSIZE8 | DMA_PSIZE8 | DMA_CCR_MINC | DMA_CCR_DIR);
}

void dma1::init(uint8_t* src, i2c2_slave targ, uint16_t pri)
{
	if (no_timer)
	{
	cha = 4-1; //Subtract one to use later with CCR register; channel 4 (I2C2 TX)
	targ.DMAenable();
	}
	else setDMAtimerChannel(cha);

	_DMA1_(DMA_CCR + cha*20) &= ~DMA_CCR_EN; //disable
	_DMA1_(DMA_CMAR + cha*20) = (uint32_t)src; //set memory address
	_DMA1_(DMA_CPAR + cha*20) = (uint32_t)&(_I2C2_(I2C_DR)); //set peripheral address
	//priority, 8 bit mem, 8 bit periph, memory increments, from mem(dir=1)
	_DMA1_(DMA_CCR + cha*20) = (uint16_t)(pri | DMA_MSIZE8 | DMA_PSIZE8 | DMA_CCR_MINC | DMA_CCR_DIR);
}

void dma1::init(i2c1_slave src, uint8_t* targ, uint16_t pri)
{
	if (no_timer)
	{
	cha = 7-1; //Subtract one to use later with CCR register; channel 7 (I2C1 RX)
	src.DMAenable();
	}
	else setDMAtimerChannel(cha);

	src.LASTset(); //last byte triggers NACK

	_DMA1_(DMA_CCR + cha*20) &= ~DMA_CCR_EN; //disable
	_DMA1_(DMA_CMAR + cha*20) = (uint32_t)targ; //set memory address
	_DMA1_(DMA_CPAR + cha*20) = (uint32_t)&(_I2C1_(I2C_DR)); //set peripheral address
	//priority, 8 bit mem, 8 bit periph, memory increments,
	_DMA1_(DMA_CCR + cha*20) = (uint16_t)(pri | DMA_MSIZE8 | DMA_PSIZE8 | DMA_CCR_MINC);
}

void dma1::init(i2c2_slave src, uint8_t* targ, uint16_t pri)
{
	if (no_timer)
	{
	cha = 5-1; //Subtract one to use later with CCR register; channel 5 (I2C2 RX)
	src.DMAenable();
	}
	else setDMAtimerChannel(cha);

	src.LASTset(); //last byte triggers NACK

	_DMA1_(DMA_CCR + cha*20) &= ~DMA_CCR_EN; //disable
	_DMA1_(DMA_CMAR + cha*20) = (uint32_t)targ; //set memory address
	_DMA1_(DMA_CPAR + cha*20) = (uint32_t)&(_I2C2_(I2C_DR)); //set peripheral address
	//priority, 8 bit mem, 8 bit periph, memory increments,
	_DMA1_(DMA_CCR + cha*20) = (uint16_t)(pri | DMA_MSIZE8 | DMA_PSIZE8 | DMA_CCR_MINC);
}

void dma1::init(uint8_t* src, usart1 targ, uint16_t pri)
{
	if (no_timer)
	{
	cha = 4-1; //Subtract one to use later with CCR register; channel 4 (TX)
	targ.DMATXenable();
	}
	else setDMAtimerChannel(cha);

	_DMA1_(DMA_CCR + cha*20) &= ~DMA_CCR_EN; //disable
	_DMA1_(DMA_CMAR + cha*20) = (uint32_t)src; //set memory address
	_DMA1_(DMA_CPAR + cha*20) = (uint32_t)&(_USART1_(USART_DR)); //set peripheral address
	//priority, 8 bit mem, 8 bit periph, memory increments, from mem
	_DMA1_(DMA_CCR + cha*20) = (uint16_t)(pri | DMA_MSIZE8 | DMA_PSIZE8 | DMA_CCR_MINC | DMA_CCR_DIR);
}

void dma1::init(uint8_t* src, usart2 targ, uint16_t pri)
{
	if (no_timer)
	{
	cha = 7-1; //Subtract one to use later with CCR register; channel 7 (TX)
	targ.DMATXenable();
	}
	else setDMAtimerChannel(cha);

	_DMA1_(DMA_CCR + cha*20) &= ~DMA_CCR_EN; //disable
	_DMA1_(DMA_CMAR + cha*20) = (uint32_t)src; //set memory address
	_DMA1_(DMA_CPAR + cha*20) = (uint32_t)&(_USART2_(USART_DR)); //set peripheral address
	//priority, 8 bit mem, 8 bit periph, memory increments, from mem
	_DMA1_(DMA_CCR + cha*20) = (uint16_t)(pri | DMA_MSIZE8 | DMA_PSIZE8 | DMA_CCR_MINC | DMA_CCR_DIR);
}

void dma1::init(uint8_t* src, usart3 targ, uint16_t pri)
{
	if (no_timer)
	{
	cha = 2-1; //Subtract one to use later with CCR register; channel 2 (TX)
	targ.DMATXenable();
	}
	else setDMAtimerChannel(cha);

	_DMA1_(DMA_CCR + cha*20) &= ~DMA_CCR_EN; //disable
	_DMA1_(DMA_CMAR + cha*20) = (uint32_t)src; //set memory address
	_DMA1_(DMA_CPAR + cha*20) = (uint32_t)&(_USART3_(USART_DR)); //set peripheral address
	//priority, 8 bit mem, 8 bit periph, memory increments, from mem
	_DMA1_(DMA_CCR + cha*20) = (uint16_t)(pri | DMA_MSIZE8 | DMA_PSIZE8 | DMA_CCR_MINC | DMA_CCR_DIR);
}

void dma1::init(usart1 src, uint8_t* targ, uint16_t pri)
{
	if (no_timer)
	{
	cha = 5-1; //Subtract one to use later with CCR register; channel 5 (RX)
	src.DMARXenable();
	}
	else setDMAtimerChannel(cha);

	_DMA1_(DMA_CCR + cha*20) &= ~DMA_CCR_EN; //disable
	_DMA1_(DMA_CMAR + cha*20) = (uint32_t)targ; //set memory address
	_DMA1_(DMA_CPAR + cha*20) = (uint32_t)&(_USART1_(USART_DR)); //set peripheral address
	//priority, 8 bit mem, 8 bit periph, memory increments,
	//_DMA1_(DMA_CCR + cha*20) = (uint16_t)(pri | DMA_MSIZE8 | DMA_PSIZE8 | DMA_CCR_MINC);
	_DMA1_(DMA_CCR + cha*20) = (uint16_t)(pri | MSIZE8_INCR | PSIZE8);
}

void dma1::init(usart2 src, uint8_t* targ, uint16_t pri)
{
	if (no_timer)
	{
	cha = 6-1; //Subtract one to use later with CCR register; channel 6 (RX)
	src.DMARXenable();
	}
	else setDMAtimerChannel(cha);

	_DMA1_(DMA_CCR + cha*20) &= ~DMA_CCR_EN; //disable
	_DMA1_(DMA_CMAR + cha*20) = (uint32_t)targ; //set memory address
	_DMA1_(DMA_CPAR + cha*20) = (uint32_t)&(_USART2_(USART_DR)); //set peripheral address
	//priority, 8 bit mem, 8 bit periph, memory increments,
	_DMA1_(DMA_CCR + cha*20) = (uint16_t)(pri | DMA_MSIZE8 | DMA_PSIZE8 | DMA_CCR_MINC);
}

void dma1::init(usart3 src, uint8_t* targ, uint16_t pri)
{
	if (no_timer)
	{
	cha = 3-1; //Subtract one to use later with CCR register; channel 3 (RX)
	src.DMARXenable();
	}
	else setDMAtimerChannel(cha);

	_DMA1_(DMA_CCR + cha*20) &= ~DMA_CCR_EN; //disable
	_DMA1_(DMA_CMAR + cha*20) = (uint32_t)targ; //set memory address
	_DMA1_(DMA_CPAR + cha*20) = (uint32_t)&(_USART3_(USART_DR)); //set peripheral address
	//priority, 8 bit mem, 8 bit periph, memory increments,
	_DMA1_(DMA_CCR + cha*20) = (uint16_t)(pri | DMA_MSIZE8 | DMA_PSIZE8 | DMA_CCR_MINC);
}

void dma1::init(analog_cont src, uint16_t targ, uint16_t pri)
{
	if (no_timer)
	{
	cha = 1-1; //Subtract one to use later with CCR register; channel 1 (ADC)
	src.DMAenable();
	}
	else setDMAtimerChannel(cha);

	_DMA1_(DMA_CCR + cha*20) &= ~DMA_CCR_EN; //disable
	_DMA1_(DMA_CMAR + cha*20) = (uint32_t)targ; //set memory address
	_DMA1_(DMA_CPAR + cha*20) = (uint32_t)&(_ADC1_(ADC_DR)); //set peripheral address
	//priority, 16 bit mem, 16 bit periph, memory increments,
	_DMA1_(DMA_CCR + cha*20) = (uint16_t)(pri | DMA_MSIZE16 | DMA_PSIZE16 | DMA_CCR_MINC);
}

void dma1::init(analog_cont src1, analog_cont src2, uint32_t targ, uint16_t pri)
{
	if (no_timer)
	{
	cha = 1-1; //Subtract one to use later with CCR register; channel 1 (ADC)
	src1.DMAenable();
	}
	else setDMAtimerChannel(cha);

	adc_dualMode(7); // fast interleaved mode; max conversion time is 7 cycles

	_DMA1_(DMA_CCR + cha*20) &= ~DMA_CCR_EN; //disable
	_DMA1_(DMA_CMAR + cha*20) = (uint32_t)targ; //set memory address
	_DMA1_(DMA_CPAR + cha*20) = (uint32_t)&(_ADC1_(ADC_DR)); //set peripheral address
	//priority, 32 bit mem, 32 bit periph, memory increments,
	_DMA1_(DMA_CCR + cha*20) = (uint16_t)(pri | DMA_MSIZE32 | DMA_PSIZE32 | DMA_CCR_MINC);
}

void dma1::init(usart1 src, spi1_slave targ, uint16_t pri)
{
	cha = 5-1; // usart1 RX channel 5
	src.DMARXenable();
	_DMA1_(DMA_CCR + cha*20) &= ~DMA_CCR_EN; //disable
	_DMA1_(DMA_CMAR + cha*20) = (uint32_t)&(_SPI1_(SPI_DR)); //set 'memory' address
	_DMA1_(DMA_CPAR + cha*20) = (uint32_t)&(_ADC1_(ADC_DR)); //set peripheral address
	//priority, 8 bit mem, 8 bit periph, memory increments,
	_DMA1_(DMA_CCR + cha*20) = (uint16_t)(pri | DMA_MSIZE8 | DMA_PSIZE8 | DMA_CCR_MINC);
}

void dma1::init(uint16_t* src, tim1_pwm targ, uint8_t uedma, uint16_t pri)
{
	switch (targ.channel)
	{
		case 1: cha = 2-1; break;
		//case 2: cha = 2-1; break; // no DMA for ch2
		case 3: cha = 6-1; break;
		case 4: cha = 4-1; break;
		default: break;
	}
	//CCDS assures the DMA request is sent on update, but the DMA channel remains CC-connected
	if (uedma) _TIM1_(TIMX_CR2) |= TIMX_CR2_CCDS; else _TIM1_(TIMX_CR2) &= ~TIMX_CR2_CCDS;
	targ.DMAenable(); // channel dma enable
	_DMA1_(DMA_CCR + cha*20) &= ~DMA_CCR_EN; //disable
	_DMA1_(DMA_CMAR + cha*20) = (uint32_t)src; //set memory address
	_DMA1_(DMA_CPAR + cha*20) = (uint32_t)&(_TIM1_(targ.ch_addr)); //set peripheral address
	//priority, 16 bit mem, 16 bit periph, memory increments, from mem
	_DMA1_(DMA_CCR + cha*20) = (uint16_t)(pri | DMA_MSIZE16 | DMA_PSIZE16 | DMA_CCR_MINC | DMA_CCR_DIR);
}

void dma1::init(uint16_t* src, tim2_pwm targ, uint8_t uedma, uint16_t pri)
{
	switch (targ.channel)
	{
		case 1: cha = 5-1; break;
		case 2: cha = 7-1; break;
		case 3: cha = 1-1; break;
		case 4: cha = 7-1; break;
		default: break;
	}
	if (uedma) _TIM2_(TIMX_CR2) |= TIMX_CR2_CCDS; else _TIM2_(TIMX_CR2) &= ~TIMX_CR2_CCDS;
	targ.DMAenable(); // channel dma enable
	_DMA1_(DMA_CCR + cha*20) &= ~DMA_CCR_EN; //disable
	_DMA1_(DMA_CMAR + cha*20) = (uint32_t)src; //set memory address
	_DMA1_(DMA_CPAR + cha*20) = (uint32_t)&(_TIM2_(targ.ch_addr)); //set peripheral address
	//priority, 16 bit mem, 16 bit periph, memory increments, from mem
	_DMA1_(DMA_CCR + cha*20) = (uint16_t)(pri | DMA_MSIZE16 | DMA_PSIZE16 | DMA_CCR_MINC | DMA_CCR_DIR);
}

void dma1::init(uint16_t* src, tim3_pwm targ, uint8_t uedma, uint16_t pri)
{
	switch (targ.channel)
	{
		case 6: cha = 2-1; break;
		//case 2: cha = 2-1; break; // no DMA for ch2
		case 3: cha = 2-1; break;
		case 4: cha = 3-1; break;
		default: break;
	}
	if (uedma) _TIM3_(TIMX_CR2) |= TIMX_CR2_CCDS; else _TIM3_(TIMX_CR2) &= ~TIMX_CR2_CCDS;
	targ.DMAenable(); // channel dma enable
	_DMA1_(DMA_CCR + cha*20) &= ~DMA_CCR_EN; //disable
	_DMA1_(DMA_CMAR + cha*20) = (uint32_t)src; //set memory address
	_DMA1_(DMA_CPAR + cha*20) = (uint32_t)&(_TIM3_(targ.ch_addr)); //set peripheral address
	//priority, 16 bit mem, 16 bit periph, memory increments, from mem
	_DMA1_(DMA_CCR + cha*20) = (uint16_t)(pri | DMA_MSIZE16 | DMA_PSIZE16 | DMA_CCR_MINC | DMA_CCR_DIR);
}

void dma1::init(uint16_t* src, tim4_pwm targ, uint8_t uedma, uint16_t pri)
{
	switch (targ.channel)
	{
		case 1: cha = 1-1; break;
		case 2: cha = 4-1; break;
		case 3: cha = 5-1; break;
		//case 4: cha = 4-1; break; // no DMA for ch4
		default: break;
	}
	if (uedma) _TIM4_(TIMX_CR2) |= TIMX_CR2_CCDS; else _TIM4_(TIMX_CR2) &= ~TIMX_CR2_CCDS;
	targ.DMAenable(); // channel dma enable
	_DMA1_(DMA_CCR + cha*20) &= ~DMA_CCR_EN; //disable
	_DMA1_(DMA_CMAR + cha*20) = (uint32_t)src; //set memory address
	_DMA1_(DMA_CPAR + cha*20) = (uint32_t)&(_TIM4_(targ.ch_addr)); //set peripheral address
	//priority, 16 bit mem, 16 bit periph, memory increments, from mem
	_DMA1_(DMA_CCR + cha*20) = (uint16_t)(pri | DMA_MSIZE16 | DMA_PSIZE16 | DMA_CCR_MINC | DMA_CCR_DIR);
}

void dma1::init(uint16_t* src, timer1 targ, uint8_t numofch, uint16_t pri)
{
	cha = 5-1;
	_DMA1_(DMA_CCR + cha*20) &= ~DMA_CCR_EN; //disable

	targ.DMAburst(numofch); //num of data to transfer in one burst
	targ.DMAbase(13); //CCR1
	targ.DMAUPenable();

	_DMA1_(DMA_CMAR + cha*20) = (uint32_t)src; //set memory address
	_DMA1_(DMA_CPAR + cha*20) = (uint32_t)&(_TIM1_(TIMX_DMAR)); //set peripheral address
	//priority, 16 bit mem, 16 bit periph, memory increments, from mem
	_DMA1_(DMA_CCR + cha*20) = (uint16_t)(pri | DMA_MSIZE16 | DMA_PSIZE16 | DMA_CCR_MINC | DMA_CCR_DIR);
}

void dma1::init(uint16_t* src, timer2 targ, uint8_t numofch, uint16_t pri)
{
	cha = 2-1;
	_DMA1_(DMA_CCR + cha*20) &= ~DMA_CCR_EN; //disable

	targ.DMAburst(numofch); //num of data to transfer in one burst
	targ.DMAbase(13); //CCR1
	targ.DMAUPenable();

	_DMA1_(DMA_CMAR + cha*20) = (uint32_t)src; //set memory address
	_DMA1_(DMA_CPAR + cha*20) = (uint32_t)&(_TIM2_(TIMX_DMAR)); //set peripheral address
	//priority, 16 bit mem, 16 bit periph, memory increments, from mem
	_DMA1_(DMA_CCR + cha*20) = (uint16_t)(pri | DMA_MSIZE16 | DMA_PSIZE16 | DMA_CCR_MINC | DMA_CCR_DIR);
}

void dma1::init(uint16_t* src, timer3 targ, uint8_t numofch, uint16_t pri)
{
	cha = 3-1;
	_DMA1_(DMA_CCR + cha*20) &= ~DMA_CCR_EN; //disable

	targ.DMAburst(numofch); //num of data to transfer in one burst
	targ.DMAbase(13); //CCR1
	targ.DMAUPenable();

	_DMA1_(DMA_CMAR + cha*20) = (uint32_t)src; //set memory address
	_DMA1_(DMA_CPAR + cha*20) = (uint32_t)&(_TIM3_(TIMX_DMAR)); //set peripheral address
	//priority, 16 bit mem, 16 bit periph, memory increments, from mem
	_DMA1_(DMA_CCR + cha*20) = (uint16_t)(pri | DMA_MSIZE16 | DMA_PSIZE16 | DMA_CCR_MINC | DMA_CCR_DIR);
}

void dma1::init(uint16_t* src, timer4 targ, uint8_t numofch, uint16_t pri)
{
	cha = 7-1;
	_DMA1_(DMA_CCR + cha*20) &= ~DMA_CCR_EN; //disable

	targ.DMAburst(numofch); //num of data to transfer in one burst
	targ.DMAbase(13); //CCR1
	targ.DMAUPenable();

	_DMA1_(DMA_CMAR + cha*20) = (uint32_t)src; //set memory address
	_DMA1_(DMA_CPAR + cha*20) = (uint32_t)&(_TIM4_(TIMX_DMAR)); //set peripheral address
	//priority, 16 bit mem, 16 bit periph, memory increments, from mem
	_DMA1_(DMA_CCR + cha*20) = (uint16_t)(pri | DMA_MSIZE16 | DMA_PSIZE16 | DMA_CCR_MINC | DMA_CCR_DIR);
}

void dma1::init(uint16_t* src, gpioA targ, int16_t pri)
{
	setDMAtimerChannel(cha);
	_DMA1_(DMA_CCR + cha*20) &= ~DMA_CCR_EN; //disable
	_DMA1_(DMA_CMAR + cha*20) = (uint32_t)src; //set memory address
	_DMA1_(DMA_CPAR + cha*20) = (uint32_t)&(_GPIOA_(GPIOX_ODR)); //set peripheral address
	//priority, 8 bit mem, 8 bit periph, memory increments, from mem
	_DMA1_(DMA_CCR + cha*20) = (uint16_t)(pri | DMA_MSIZE16 | DMA_PSIZE32| DMA_CCR_MINC | DMA_CCR_DIR);
}

void dma1::init(uint16_t* src, gpioB targ, int16_t pri)
{
	setDMAtimerChannel(cha);
	_DMA1_(DMA_CCR + cha*20) &= ~DMA_CCR_EN; //disable
	_DMA1_(DMA_CMAR + cha*20) = (uint32_t)src; //set memory address
	_DMA1_(DMA_CPAR + cha*20) = (uint32_t)&(_GPIOB_(GPIOX_ODR)); //set peripheral address
	//priority, 8 bit mem, 8 bit periph, memory increments, from mem
	_DMA1_(DMA_CCR + cha*20) = (uint16_t)(pri | DMA_MSIZE16 | DMA_PSIZE32| DMA_CCR_MINC | DMA_CCR_DIR);
}

void dma1::init(uint16_t* src, gpioC targ, int16_t pri)
{
	setDMAtimerChannel(cha);
	_DMA1_(DMA_CCR + cha*20) &= ~DMA_CCR_EN; //disable
	_DMA1_(DMA_CMAR + cha*20) = (uint32_t)src; //set memory address
	_DMA1_(DMA_CPAR + cha*20) = (uint32_t)&(_GPIOC_(GPIOX_ODR)); //set peripheral address
	//priority, 8 bit mem, 8 bit periph, memory increments, from mem
	_DMA1_(DMA_CCR + cha*20) = (uint16_t)(pri | DMA_MSIZE16 | DMA_PSIZE32| DMA_CCR_MINC | DMA_CCR_DIR);
}

void dma1::init(uint32_t* src, gpioA targ, int16_t pri)
{
	setDMAtimerChannel(cha);
	_DMA1_(DMA_CCR + cha*20) &= ~DMA_CCR_EN; //disable
	_DMA1_(DMA_CMAR + cha*20) = (uint32_t)src; //set memory address
	_DMA1_(DMA_CPAR + cha*20) = (uint32_t)&(_GPIOA_(GPIOX_BSRR)); //set peripheral address
	//priority, 8 bit mem, 8 bit periph, memory increments, from mem
	_DMA1_(DMA_CCR + cha*20) = (uint16_t)(pri | DMA_MSIZE32 | DMA_PSIZE32| DMA_CCR_MINC | DMA_CCR_DIR);
}

void dma1::init(uint32_t* src, gpioB targ, int16_t pri)
{
	setDMAtimerChannel(cha);
	_DMA1_(DMA_CCR + cha*20) &= ~DMA_CCR_EN; //disable
	_DMA1_(DMA_CMAR + cha*20) = (uint32_t)src; //set memory address
	_DMA1_(DMA_CPAR + cha*20) = (uint32_t)&(_GPIOB_(GPIOX_BSRR)); //set peripheral address
	//priority, 8 bit mem, 8 bit periph, memory increments, from mem
	_DMA1_(DMA_CCR + cha*20) = (uint16_t)(pri | DMA_MSIZE32 | DMA_PSIZE32| DMA_CCR_MINC | DMA_CCR_DIR);
}

void dma1::init(uint32_t* src, gpioC targ, int16_t pri)
{
	setDMAtimerChannel(cha);
	_DMA1_(DMA_CCR + cha*20) &= ~DMA_CCR_EN; //disable
	_DMA1_(DMA_CMAR + cha*20) = (uint32_t)src; //set memory address
	_DMA1_(DMA_CPAR + cha*20) = (uint32_t)&(_GPIOC_(GPIOX_BSRR)); //set peripheral address
	//priority, 8 bit mem, 8 bit periph, memory increments, from mem
	_DMA1_(DMA_CCR + cha*20) = (uint16_t)(pri | DMA_MSIZE32 | DMA_PSIZE32| DMA_CCR_MINC | DMA_CCR_DIR);
}
