/*
 * STM32F103 RCC register definitions
 * Part of STM32F103 register and peripherals library
 *
 * Dpcumentation available in the provided MD file.
 *
 * (c) 2019 Dmitry Reznikov ontaelio(at)gmail.com
 *
 * Can be freely used according to the GNU GPL license.
 */

#ifndef STM32F103_RCC_REG_H_
#define STM32F103_RCC_REG_H_

#include <stdio.h>
#include <stdint.h>

#define _RCC_(mem_offset) (*(volatile uint32_t *)(0x40021000 + (mem_offset)))

// registers
#define RCC_CR 0x00
#define RCC_CFGR 0x04
#define RCC_CIR 0x08
#define RCC_APB2RSTR 0x0C
#define RCC_APB1RSTR 0x10
#define RCC_AHBENR 0x14
#define RCC_APB2ENR 0x18
#define RCC_APB1ENR 0x1C
#define RCC_BDCR 0x20
#define RCC_CSR 0x24

//bitband
//0x42000000 + offset * 0x20 + bit * 4

#define BB_RCC_BASE 	*(volatile uint32_t *) 0x42420000
#define BB_RCC_AHBENR	*(volatile uint32_t *) 0x42420280
#define BB_RCC_APB2ENR	*(volatile uint32_t *) 0x42420300
#define BB_RCC_APB1ENR	*(volatile uint32_t *) 0x42420380

//AHB
#define DMA1_CLOCK		*(volatile uint32_t *) 0x42420280
#define DMA2_CLOCK		*(volatile uint32_t *) 0x42420284
#define SRAM_CLOCK		*(volatile uint32_t *) 0x42420288
//reserved
#define FLITF_CLOCK	*(volatile uint32_t *) 0x42420290
//reserved
#define CRC_CLOCK		*(volatile uint32_t *) 0x42420298
//reserved
#define FSMC_CLOCK		*(volatile uint32_t *) 0x424202A0
//reserved
#define SDIO_CLOCK		*(volatile uint32_t *) 0x424202A8
//rest reserved

//APB2
#define AFIO_CLOCK		*(volatile uint32_t *) 0x42420300
//reserved
#define GPIOA_CLOCK		*(volatile uint32_t *) 0x42420308
#define GPIOB_CLOCK		*(volatile uint32_t *) 0x4242030C
#define GPIOC_CLOCK		*(volatile uint32_t *) 0x42420310
#define GPIOD_CLOCK		*(volatile uint32_t *) 0x42420314
#define GPIOE_CLOCK		*(volatile uint32_t *) 0x42420318
#define GPIOF_CLOCK		*(volatile uint32_t *) 0x4242031C
#define GPIOG_CLOCK		*(volatile uint32_t *) 0x42420320
#define ADC1_CLOCK		*(volatile uint32_t *) 0x42420324
#define ADC2_CLOCK		*(volatile uint32_t *) 0x42420328
#define TIM1_CLOCK		*(volatile uint32_t *) 0x4242032C
#define SPI1_CLOCK		*(volatile uint32_t *) 0x42420330
#define TIM8_CLOCK		*(volatile uint32_t *) 0x42420334
#define USART1_CLOCK	*(volatile uint32_t *) 0x42420338
#define ADC3_CLOCK		*(volatile uint32_t *) 0x4242033C
//reserved
//reserved
//reserved
#define TIM9_CLOCK		*(volatile uint32_t *) 0x4242034C
#define TIM10_CLOCK		*(volatile uint32_t *) 0x42420350
#define TIM11_CLOCK		*(volatile uint32_t *) 0x42420354
//rest reserved

//APB1
#define TIM2_CLOCK		*(volatile uint32_t *) 0x42420380
#define TIM3_CLOCK		*(volatile uint32_t *) 0x42420384
#define TIM4_CLOCK		*(volatile uint32_t *) 0x42420388
#define TIM5_CLOCK		*(volatile uint32_t *) 0x4242038C
#define TIM6_CLOCK		*(volatile uint32_t *) 0x42420390
#define TIM7_CLOCK		*(volatile uint32_t *) 0x42420394
#define TIM12_CLOCK		*(volatile uint32_t *) 0x42420398
#define TIM13_CLOCK		*(volatile uint32_t *) 0x4242039C
#define TIM14_CLOCK		*(volatile uint32_t *) 0x424203A0
//reserved
//reserved
#define WWDG_CLOCK		*(volatile uint32_t *) 0x424203AC
//reserved
//reserved
#define SPI2_CLOCK		*(volatile uint32_t *) 0x424203B8
#define SPI3_CLOCK		*(volatile uint32_t *) 0x424203BC
//reserved
#define USART2_CLOCK	*(volatile uint32_t *) 0x424203C4
#define USART3_CLOCK	*(volatile uint32_t *) 0x424203C8
#define USART4_CLOCK	*(volatile uint32_t *) 0x424203CC
#define USART5_CLOCK	*(volatile uint32_t *) 0x424203D0
#define I2C1_CLOCK		*(volatile uint32_t *) 0x424203D4
#define I2C2_CLOCK		*(volatile uint32_t *) 0x424203D8
#define USB_CLOCK		*(volatile uint32_t *) 0x424203DC
//reserved
#define CAN_CLOCK		*(volatile uint32_t *) 0x424203E4
//reserved
#define BKP_CLOCK		*(volatile uint32_t *) 0x424203EC
#define PWR_CLOCK		*(volatile uint32_t *) 0x424203F0
#define DAC_CLOCK		*(volatile uint32_t *) 0x424203F4
//2x reserved

#ifndef __STM32F10x_H //avoid redefining if CMSIS library present

// values
#define RCC_CR_HSION		0x00000001
#define RCC_CR_HSIRDY		0x00000001
//reserved
#define RCC_CR_HSITRIM		0x000000F8 //mask
#define RCC_CR_HSICAL		0x0000FF00 //mask
#define RCC_CR_HSEON		0x00010000
#define RCC_CR_HSERDY		0x00020000
#define RCC_CR_HSEBYP		0x00040000
#define RCC_CR_CSSON		0x00080000
//4 bits reserved
#define RCC_CR_PLLON		0x01000000
#define RCC_CR_PLLRDY		0x02000000
//the rest reserved

#define RCC_CFGR_SW			0x00000003 //mask
#define RCC_CFGR_SWS		0x0000000C //mask
#define RCC_CFGR_HPRE		0x000000F0 //mask
#define RCC_CFGR_PPRE1		0x00000700 //mask
#define RCC_CFGR_PPRE2		0x00003800 //mask
#define RCC_CFGR_ADCPRE		0x0000C000 //mask
#define RCC_CFGR_PLLSRC		0x00010000
#define RCC_CFGR_PLLXTPRE	0x00020000
#define RCC_CFGR_PLLMUL		0x003C0000 //mask
#define RCC_CFGR_USBPRE		0x00400000
//reserved
#define RCC_CFGR_MCO		0x07000000 //mask

#define RCC_CIR_LSIRDYF		0x00000001
#define RCC_CIR_LSERDYF		0x00000002
#define RCC_CIR_HSIRDYF		0x00000004
#define RCC_CIR_HSERDYF		0x00000008
#define RCC_CIR_PLLRDYF		0x00000010
//reserved x2
#define RCC_CIR_CSSF		0x00000080
#define RCC_CIR_LSIRDYIE	0x00000100
#define RCC_CIR_LSERDYIE	0x00000200
#define RCC_CIR_HSIRDYIE	0x00000400
#define RCC_CIR_HSERDYIE	0x00000800
#define RCC_CIR_PLLRDYIE	0x00001000
//reserved x3
#define RCC_CIR_LSIRDYC		0x00010000
#define RCC_CIR_LSERDYC		0x00020000
#define RCC_CIR_HSIRDYC		0x00040000
#define RCC_CIR_HSERDYC		0x00080000
#define RCC_CIR_PLLRDYC		0x00100000
//reserved x2
#define RCC_CIR_CSSC		0x00800000
//the rest reserved

#define RCC_APB2RSTR_AFIORST 0x0001
//reserved
#define RCC_APB2RSTR_IOPARST 0x0004
#define RCC_APB2RSTR_IOPBRST 0x0008
#define RCC_APB2RSTR_IOPCRST 0x0010
#define RCC_APB2RSTR_IOPDRST 0x0020
#define RCC_APB2RSTR_IOPERST 0x0040
#define RCC_APB2RSTR_IOPFRST 0x0080
#define RCC_APB2RSTR_IOPGRST 0x0100
#define RCC_APB2RSTR_ADC1RST 0x0200
#define RCC_APB2RSTR_ADC2RST 0x0400
#define RCC_APB2RSTR_TIM1RST 0x0800
#define RCC_APB2RSTR_SPI1RST 0x1000
#define RCC_APB2RSTR_TIM8RST 0x2000
#define RCC_APB2RSTR_USART1RST 0x4000
#define RCC_APB2RSTR_ADC3RST 0x8000
//reserved
//reserved
//reserved
#define RCC_APB2RSTR_TIM9RST  0x00080000
#define RCC_APB2RSTR_TIM10RST 0x00100000
#define RCC_APB2RSTR_TIM11RST 0x00200000
//rest reserved

#define RCC_APB1RSTR_TIM2RST  0x0001
#define RCC_APB1RSTR_TIM3RST  0x0002
#define RCC_APB1RSTR_TIM4RST  0x0004
#define RCC_APB1RSTR_TIM5RST  0x0008
#define RCC_APB1RSTR_TIM6RST  0x0010
#define RCC_APB1RSTR_TIM7RST  0x0020
#define RCC_APB1RSTR_TIM12RST 0x0040
#define RCC_APB1RSTR_TIM13RST 0x0080
#define RCC_APB1RSTR_TIM14RST 0x0100
//reserved
//reserved
#define RCC_APB1RSTR_WWDGRST  0x0800
//reserved
//reserved
#define RCC_APB1RSTR_SPI2RST  0x4000
#define RCC_APB1RSTR_SPI3RST  0x8000
//reserved
#define RCC_APB1RSTR_USART2RST 0x00020000
#define RCC_APB1RSTR_USART3RST 0x00040000
#define RCC_APB1RSTR_USART4RST 0x00080000
#define RCC_APB1RSTR_USART5RST 0x00100000
#define RCC_APB1RSTR_I2C1RST   0x00200000
#define RCC_APB1RSTR_I2C2RST   0x00400000
#define RCC_APB1RSTR_USBRST    0x00800000
//reserved
#define RCC_APB1RSTR_CAN1RST   0x02000000
#define RCC_APB1RSTR_CAN2RST   0x02000000
#define RCC_APB1RSTR_BKPRST    0x08000000
#define RCC_APB1RSTR_PWRRST    0x10000000
#define RCC_APB1RSTR_DACRST    0x20000000
//reserved
//reserved

#define RCC_AHBENR_DMA1EN	0x0001
#define RCC_AHBENR_DMA2EN	0x0002
#define RCC_AHBENR_SRAMEN	0x0004
//reserved
#define RCC_AHBENR_FLITFEN	0x0010
//reserved
#define RCC_AHBENR_CRCEN	0x0040
//reserved
#define RCC_AHBENR_FSMCEN	0x0100
//reserved
#define RCC_AHBENR_SDIOEN	0x0400
//reserved x5

#define RCC_APB2ENR_AFIOEN 0x0001
//reserved
#define RCC_APB2ENR_IOPAEN 0x0004
#define RCC_APB2ENR_IOPBEN 0x0008
#define RCC_APB2ENR_IOPCEN 0x0010
#define RCC_APB2ENR_IOPDEN 0x0020
#define RCC_APB2ENR_IOPEEN 0x0040
#define RCC_APB2ENR_IOPFEN 0x0080
#define RCC_APB2ENR_IOPGEN 0x0100
#define RCC_APB2ENR_ADC1EN 0x0200
#define RCC_APB2ENR_ADC2EN 0x0400
#define RCC_APB2ENR_TIM1EN 0x0800
#define RCC_APB2ENR_SPI1EN 0x1000
#define RCC_APB2ENR_TIM8EN 0x2000
#define RCC_APB2ENR_USART1EN 0x4000
#define RCC_APB2ENR_ADC3EN 0x8000
//reserved
//reserved
//reserved
#define RCC_APB2ENR_TIM9EN  0x00080000
#define RCC_APB2ENR_TIM10EN 0x00100000
#define RCC_APB2ENR_TIM11EN 0x00200000
//rest reserved

#define RCC_APB1ENR_TIM2EN  0x0001
#define RCC_APB1ENR_TIM3EN  0x0002
#define RCC_APB1ENR_TIM4EN  0x0004
#define RCC_APB1ENR_TIM5EN  0x0008
#define RCC_APB1ENR_TIM6EN  0x0010
#define RCC_APB1ENR_TIM7EN  0x0020
#define RCC_APB1ENR_TIM12EN 0x0040
#define RCC_APB1ENR_TIM13EN 0x0080
#define RCC_APB1ENR_TIM14EN 0x0100
//reserved
//reserved
#define RCC_APB1ENR_WWDGEN  0x0800
//reserved
//reserved
#define RCC_APB1ENR_SPI2EN  0x4000
#define RCC_APB1ENR_SPI3EN  0x8000
//reserved
#define RCC_APB1ENR_USART2EN 0x00020000
#define RCC_APB1ENR_USART3EN 0x00040000
#define RCC_APB1ENR_USART4EN 0x00080000
#define RCC_APB1ENR_USART5EN 0x00100000
#define RCC_APB1ENR_I2C1EN   0x00200000
#define RCC_APB1ENR_I2C2EN   0x00400000
#define RCC_APB1ENR_USBEN    0x00800000
//reserved
#define RCC_APB1ENR_CAN1EN   0x02000000
#define RCC_APB1ENR_CAN2EN   0x04000000
#define RCC_APB1ENR_BKPEN    0x08000000
#define RCC_APB1ENR_PWREN    0x10000000
#define RCC_APB1ENR_DACEN    0x20000000
//reserved
//reserved

#define RCC_APB2ENR_ALL		0x0038FFFD //mask
#define RCC_APB1ENR_ALL		0x3AFEC9FF //mask
#define RCC_AHBENR_ALL		0x00000557 //mask

#define RCC_BDCR_LSEON		0x00000001
#define RCC_BDCR_LSERDY		0x00000002
#define RCC_BDCR_LSEBYP		0x00000004
//reserved x5
#define RCC_BDCR_RTCSEL		0x00000300 //mask
//reserved x5
#define RCC_BDCR_RTCEN		0x00008000
#define RCC_BDCR_BDRST		0x00010000
//reserved to the end

#define RCC_CSR_LSION		0x00000001
#define RCC_CSR_LSIRDY		0x00000002
//reserved x22
#define RCC_CSR_RMVF		0x01000000
//reserved
#define RCC_CSR_PINRSTF		0x04000000
#define RCC_CSR_PORRSTF		0x08000000
#define RCC_CSR_SFTRSTF		0x10000000
#define RCC_CSR_IWDGRSTF	0x20000000
#define RCC_CSR_WWDGRSTF	0x40000000
#define RCC_CSR_LPWRRSTF	0x80000000

#endif //CMSIS stuff

//CMSIS defines these as CAN1
#define RCC_APB1RSTR_CANRST  0x02000000
#define RCC_APB1ENR_CANEN    0x02000000

#define RCC_APB2ENR_ALL		0x0038FFFD //mask
#define RCC_APB1ENR_ALL		0x3AFEC9FF //mask
#define RCC_AHBENR_ALL		0x00000557 //mask



#endif /* STM32F103_RCC_REG_H_ */
