/*
 * stm32f103_flashmem.h
 *
 *  Created on: 16 но€б. 2019 г.
 *      Author: Ontaelio
 */

#ifndef STM32F103_SPI_FLASHMEM_H_
#define STM32F103_SPI_FLASHMEM_H_

#include <stm32f103_spi_reg.h>
#include <stm32f103_spi_func.h>
#include <stdio.h>

class spi_flash
{
public:
	spi_flash(spi_slave* target) : device(target){}
	void write(uint32_t address, uint8_t* arr_out, uint8_t num = 0);
	void read(uint32_t address, uint8_t* arr_in, uint16_t num);
	void fastRead(uint32_t address, uint8_t* arr_in, uint16_t num);
	void writeEnable();
	void writeDisable();
	uint8_t busy();
	void erase(uint32_t address);
	void block32erase(uint32_t address);
	void block64erase(uint32_t address);
	void chipErase();

private:
	uint16_t static const default_config = 0x0300;
	spi_slave* device;
};



#endif /* STM32F103_SPI_FLASHMEM_H_ */
