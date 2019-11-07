/*
 * STM32F103 GPIO and AFIO register definitions
 * Part of STM32F103 register and peripherals library
 *
 * Dpcumentation available in the provided MD file.
 *
 * (c) 2019 Dmitry Reznikov ontaelio(at)gmail.com
 *
 * Can be freely used according to the GNU GPL license.
 */

#ifndef STM32F103_GPIO_REG_H_
#define STM32F103_GPIO_REG_H_



//ports
#define _GPIOA_(mem_offset) (*(volatile uint32_t *)(0x40010800 + (mem_offset)))
#define _GPIOB_(mem_offset) (*(volatile uint32_t *)(0x40010C00 + (mem_offset)))
#define _GPIOC_(mem_offset) (*(volatile uint32_t *)(0x40011000 + (mem_offset)))
#define _GPIOD_(mem_offset) (*(volatile uint32_t *)(0x40011400 + (mem_offset)))
#define _GPIOE_(mem_offset) (*(volatile uint32_t *)(0x40011800 + (mem_offset)))
#define _GPIOF_(mem_offset) (*(volatile uint32_t *)(0x40011C00 + (mem_offset)))
#define _GPIOG_(mem_offset) (*(volatile uint32_t *)(0x40012000 + (mem_offset)))

//registers
#define GPIOX_CRL  0x00
#define GPIOX_CRH  0x04
#define GPIOX_IDR  0x08
#define GPIOX_ODR  0x0C
#define GPIOX_BSRR 0x10 // upper byte = reset, lower byte = set
#define GPIOX_BRR  0x14 // upper byte reserved, lower byte = reset
#define GPIOX_LCKR 0x18

//AFIO
#define _AFIO_(mem_offset) (*(volatile uint32_t *)(0x40010000 + (mem_offset)))

//AFIO registers
#define AFIO_EVCR	 0x00
#define AFIO_MAPR	 0x04
#define AFIO_EXTICR1 0x08
#define AFIO_EXTICR2 0x0C
#define AFIO_EXTICR3 0x10
#define AFIO_EXTICR4 0x14
#define AFIO_MAPR2	 0x1C

//bits
#define AFIO_EVCR_PORT	0x000F //mask
#define AFIO_EVCR_PIN	0x0070 //mask
#define AFIO_EVCR_EVOE	0x0080
//the rest reserved

#define AFIO_MAPR_SPI1_REMAP	0x00000001
#define AFIO_MAPR_I2C1_REMAP	0x00000002
#define AFIO_MAPR_USART1_REMAP	0x00000004
#define AFIO_MAPR_USART2_REMAP	0x00000008
#define AFIO_MAPR_USART3_REMAP	0x00000030 //mask
#define AFIO_MAPR_TIM1_REMAP	0x000000C0 //mask
#define AFIO_MAPR_TIM2_REMAP	0x00000300 //mask
#define AFIO_MAPR_TIM3_REMAP	0x00000C00 //mask
#define AFIO_MAPR_TIM4_REMAP	0x00001000
#define AFIO_MAPR_CAN_REMAP		0x00006000 //mask
#define AFIO_MAPR_PD01_REMAP	0x00008000
#define AFIO_MAPR_TIM5CH4_IREMAP		0x00010000
#define AFIO_MAPR_ADC1_ETRGINJ_REMAP	0x00020000
#define AFIO_MAPR_ADC1_ETRGREG_REMAP	0x00040000
#define AFIO_MAPR_ADC2_ETRGINJ_REMAP	0x00080000
#define AFIO_MAPR_ADC2_ETRGREG_REMAP	0x00100000
//3 bits reserved
#define AFIO_MAPR_SWJ_CFG		0x07000000 //mask

#define AFIO_EXTICR1_EXTI0	0x000F //mask
#define AFIO_EXTICR1_EXTI1	0x00F0 //mask
#define AFIO_EXTICR1_EXTI2	0x0F00 //mask
#define AFIO_EXTICR1_EXTI3	0xF000 //mask

#define AFIO_EXTICR2_EXTI4	0x000F //mask
#define AFIO_EXTICR2_EXTI5	0x00F0 //mask
#define AFIO_EXTICR2_EXTI6	0x0F00 //mask
#define AFIO_EXTICR2_EXTI7	0xF000 //mask

#define AFIO_EXTICR3_EXTI8	0x000F //mask
#define AFIO_EXTICR3_EXTI9	0x00F0 //mask
#define AFIO_EXTICR3_EXTI10	0x0F00 //mask
#define AFIO_EXTICR3_EXTI11	0xF000 //mask

#define AFIO_EXTICR4_EXTI12	0x000F //mask
#define AFIO_EXTICR4_EXTI13	0x00F0 //mask
#define AFIO_EXTICR4_EXTI14	0x0F00 //mask
#define AFIO_EXTICR4_EXTI15	0xF000 //mask

//MAPR2 bits 4:0 reserved
#define AFIO_MAPR2_TIM9_REMAP	0x0020
#define AFIO_MAPR2_TIM10_REMAP	0x0040
#define AFIO_MAPR2_TIM11_REMAP	0x0080
#define AFIO_MAPR2_TIM13_REMAP	0x0100
#define AFIO_MAPR2_TIM14_REMAP	0x0200
#define AFIO_MAPR2_FSMC_NADV	0x0400
//the rest reserved

//CRL and CRH values

// CNF:
// In input mode (MODE[1:0]=00):
// 00: Analog mode
// 01: Floating input (reset state)
// 10: Input with pull-up / pull-down
// 11: Reserved

//In output mode (MODE[1:0] > 00):
//00: General purpose output push-pull
//01: General purpose output Open-drain
//10: Alternate function output Push-pull
//11: Alternate function output Open-drain
#define CNF0_0 0x00000004
#define CNF0_1 0x00000008
#define CNF1_0 0x00000040
#define CNF1_1 0x00000080
#define CNF2_0 0x00000400
#define CNF2_1 0x00000800
#define CNF3_0 0x00004000
#define CNF3_1 0x00008000
#define CNF4_0 0x00040000
#define CNF4_1 0x00080000
#define CNF5_0 0x00400000
#define CNF5_1 0x00800000
#define CNF6_0 0x04000000
#define CNF6_1 0x08000000
#define CNF7_0 0x40000000
#define CNF7_1 0x80000000
#define CNF8_0 0x00000004
#define CNF8_1 0x00000008
#define CNF9_0 0x00000040
#define CNF9_1 0x00000080
#define CNF10_0 0x00000400
#define CNF10_1 0x00000800
#define CNF11_0 0x00004000
#define CNF11_1 0x00008000
#define CNF12_0 0x00040000
#define CNF12_1 0x00080000
#define CNF13_0 0x00400000
#define CNF13_1 0x00800000
#define CNF14_0 0x04000000
#define CNF14_1 0x08000000
#define CNF15_0 0x40000000
#define CNF15_1 0x80000000

// MODE:
// 00: Input mode (reset state)
// 01: Output mode, max speed 10 MHz.
// 10: Output mode, max speed 2 MHz.
// 11: Output mode, max speed 50 MHz.
#define MODE0_0 0x00000001
#define MODE0_1 0x00000002
#define MODE1_0 0x00000010
#define MODE1_1 0x00000020
#define MODE2_0 0x00000100
#define MODE2_1 0x00000200
#define MODE3_0 0x00001000
#define MODE3_1 0x00002000
#define MODE4_0 0x00010000
#define MODE4_1 0x00020000
#define MODE5_0 0x00100000
#define MODE5_1 0x00200000
#define MODE6_0 0x01000000
#define MODE6_1 0x02000000
#define MODE7_0 0x10000000
#define MODE7_1 0x20000000
#define MODE8_0 0x00000001
#define MODE8_1 0x00000002
#define MODE9_0 0x00000010
#define MODE9_1 0x00000020
#define MODE10_0 0x00000100
#define MODE10_1 0x00000200
#define MODE11_0 0x00001000
#define MODE11_1 0x00002000
#define MODE12_0 0x00010000
#define MODE12_1 0x00020000
#define MODE13_0 0x00100000
#define MODE13_1 0x00200000
#define MODE14_0 0x01000000
#define MODE14_1 0x02000000
#define MODE15_0 0x10000000
#define MODE15_1 0x20000000

#endif /* STM32F103_GPIO_REG_H_ */
