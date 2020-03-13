/*
 * STM32F103 DMA register definitions
 * Part of STM32F103 register and peripherals library
 *
 * Dpcumentation available in the provided MD file.
 *
 * (c) 2019 Dmitry Reznikov ontaelio(at)gmail.com
 *
 * Can be freely used according to the GNU GPL license.
 */

#ifndef STM32F103_DMA_REG_H_
#define STM32F103_DMA_REG_H_

#include <stdio.h>
#include <stdint.h>

#define _DMA1_(mem_offset) (*(volatile uint32_t *)(0x40020000 + (mem_offset)))
#define _DMA2_(mem_offset) (*(volatile uint32_t *)(0x40020400 + (mem_offset)))



//DMA registers
#define DMA_ISR		0x00
#define DMA_IFCR	0x04

#define DMA_CCR1	0x08
#define DMA_CNDTR1	0x0C
#define DMA_CPAR1	0x10
#define DMA_CMAR1	0x14

#define DMA_CCR2	0x1C
#define DMA_CNDTR2	0x20
#define DMA_CPAR2	0x24
#define DMA_CMAR2	0x28

#define DMA_CCR3	0x30
#define DMA_CNDTR3	0x34
#define DMA_CPAR3	0x38
#define DMA_CMAR3	0x3C

#define DMA_CCR4	0x44
#define DMA_CNDTR4	0x48
#define DMA_CPAR4	0x4C
#define DMA_CMAR4	0x50

#define DMA_CCR5	0x58
#define DMA_CNDTR5	0x5C
#define DMA_CPAR5	0x60
#define DMA_CMAR5	0x64

#define DMA_CCR6	0x6C
#define DMA_CNDTR6	0x70
#define DMA_CPAR6	0x74
#define DMA_CMAR6	0x78

#define DMA_CCR7	0x80
#define DMA_CNDTR7	0x84
#define DMA_CPAR7	0x88
#define DMA_CMAR7	0x8C

// these point to channel1 to provide a base for addition
// either +20*(Channel-1) or +0x14*(Channel-1)
#define DMA_CCR		0x08
#define DMA_CNDTR	0x0C
#define DMA_CPAR	0x10
#define DMA_CMAR	0x14

#ifndef __STM32F10x_H //avoid redefining if CMSIS library present

//values
#define DMA_ISR_GIF1	(uint32_t)0x00000001
#define DMA_ISR_TCIF1	(uint32_t)0x00000002
#define DMA_ISR_HTIF1	(uint32_t)0x00000004
#define DMA_ISR_TEIF1	(uint32_t)0x00000008
#define DMA_ISR_GIF2	(uint32_t)0x00000010
#define DMA_ISR_TCIF2	(uint32_t)0x00000020
#define DMA_ISR_HTIF2	(uint32_t)0x00000040
#define DMA_ISR_TEIF2	(uint32_t)0x00000080
#define DMA_ISR_GIF3	(uint32_t)0x00000100
#define DMA_ISR_TCIF3	(uint32_t)0x00000200
#define DMA_ISR_HTIF3	(uint32_t)0x00000400
#define DMA_ISR_TEIF3	(uint32_t)0x00000800
#define DMA_ISR_GIF4	(uint32_t)0x00001000
#define DMA_ISR_TCIF4	(uint32_t)0x00002000
#define DMA_ISR_HTIF4	(uint32_t)0x00004000
#define DMA_ISR_TEIF4	(uint32_t)0x00008000
#define DMA_ISR_GIF5	(uint32_t)0x00010000
#define DMA_ISR_TCIF5	(uint32_t)0x00020000
#define DMA_ISR_HTIF5	(uint32_t)0x00040000
#define DMA_ISR_TEIF5	(uint32_t)0x00080000
#define DMA_ISR_GIF6	(uint32_t)0x00100000
#define DMA_ISR_TCIF6	(uint32_t)0x00200000
#define DMA_ISR_HTIF6	(uint32_t)0x00400000
#define DMA_ISR_TEIF6	(uint32_t)0x00800000
#define DMA_ISR_GIF7	(uint32_t)0x01000000
#define DMA_ISR_TCIF7	(uint32_t)0x02000000
#define DMA_ISR_HTIF7	(uint32_t)0x04000000
#define DMA_ISR_TEIF7	(uint32_t)0x08000000

#define DMA_IFCR_CGIF1	(uint32_t)0x00000001
#define DMA_IFCR_CTCIF1	(uint32_t)0x00000002
#define DMA_IFCR_CHTIF1	(uint32_t)0x00000004
#define DMA_IFCR_CTEIF1	(uint32_t)0x00000008
#define DMA_IFCR_CGIF2	(uint32_t)0x00000010
#define DMA_IFCR_CTCIF2	(uint32_t)0x00000020
#define DMA_IFCR_CHTIF2	(uint32_t)0x00000040
#define DMA_IFCR_CTEIF2	(uint32_t)0x00000080
#define DMA_IFCR_CGIF3	(uint32_t)0x00000100
#define DMA_IFCR_CTCIF3	(uint32_t)0x00000200
#define DMA_IFCR_CHTIF3	(uint32_t)0x00000400
#define DMA_IFCR_CTEIF3	(uint32_t)0x00000800
#define DMA_IFCR_CGIF4	(uint32_t)0x00001000
#define DMA_IFCR_CTCIF4	(uint32_t)0x00002000
#define DMA_IFCR_CHTIF4	(uint32_t)0x00004000
#define DMA_IFCR_CTEIF4	(uint32_t)0x00008000
#define DMA_IFCR_CGIF5	(uint32_t)0x00010000
#define DMA_IFCR_CTCIF5	(uint32_t)0x00020000
#define DMA_IFCR_CHTIF5	(uint32_t)0x00040000
#define DMA_IFCR_CTEIF5	(uint32_t)0x00080000
#define DMA_IFCR_CGIF6	(uint32_t)0x00100000
#define DMA_IFCR_CTCIF6	(uint32_t)0x00200000
#define DMA_IFCR_CHTIF6	(uint32_t)0x00400000
#define DMA_IFCR_CTEIF6	(uint32_t)0x00800000
#define DMA_IFCR_CGIF7	(uint32_t)0x01000000
#define DMA_IFCR_CTCIF7	(uint32_t)0x02000000
#define DMA_IFCR_CHTIF7	(uint32_t)0x04000000
#define DMA_IFCR_CTEIF7	(uint32_t)0x08000000

#define DMA_CCR_EN		(uint32_t)0x00000001
#define DMA_CCR_TCIE	(uint32_t)0x00000002
#define DMA_CCR_HTIE	(uint32_t)0x00000004
#define DMA_CCR_TEIE	(uint32_t)0x00000008
#define DMA_CCR_DIR		(uint32_t)0x00000010
#define DMA_CCR_CIRC	(uint32_t)0x00000020
#define DMA_CCR_PINC	(uint32_t)0x00000040
#define DMA_CCR_MINC	(uint32_t)0x00000080
#define DMA_CCR_PSIZE0	(uint32_t)0x00000100
#define DMA_CCR_PSIZE1	(uint32_t)0x00000200
#define DMA_CCR_MSIZE0	(uint32_t)0x00000400
#define DMA_CCR_MSIZE1	(uint32_t)0x00000800
#define DMA_CCR_PL0		(uint32_t)0x00001000
#define DMA_CCR_PL1		(uint32_t)0x00002000
#define DMA_CCR_MEM2MEM	(uint32_t)0x00004000
//reserved

#endif //CMSIS stuff

//to use with <<(Channel - 1)
#define DMA_ISR_GIF		(uint32_t)0x00000001
#define DMA_ISR_TCIF	(uint32_t)0x00000002
#define DMA_ISR_HTIF	(uint32_t)0x00000004
#define DMA_ISR_TEIF	(uint32_t)0x00000008
#define DMA_IFCR_CGIF	(uint32_t)0x00000001
#define DMA_IFCR_CTCIF	(uint32_t)0x00000002
#define DMA_IFCR_CHTIF	(uint32_t)0x00000004
#define DMA_IFCR_CTEIF	(uint32_t)0x00000008

//masks
#define DMA_CCR_PSIZE	(uint16_t)0x0300
#define DMA_CCR_MSIZE	(uint16_t)0x0C00
#define DMA_CCR_PL		(uint16_t)0x3000

#endif /* STM32F103_DMA_REG_H_ */
