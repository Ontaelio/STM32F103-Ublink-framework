/*
 * STM32F103 SPI Flash memory sub-library header file
 * Part of STM32F103 register and peripherals library
 *
 * Dpcumentation available in the provided MD file.
 *
 * (c) 2019 Dmitry Reznikov ontaelio(at)gmail.com
 *
 * Can be freely used according to the GNU GPL license.
 */

#ifndef STM32F103_SPI_FLASHMEM_H_
#define STM32F103_SPI_FLASHMEM_H_

#include <stdio.h>
#include <stdint.h>
#include <stm32f103_spi.h>
#include <stm32f103_spi_reg.h>


class spi_flash
{
public:
	spi_flash(spi_slave* target) : device(target){}
	void init() {device -> init(0x0300);}
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
	uint8_t manufacturer();
	uint8_t deviceID();
	uint32_t JEDEC();
	uint64_t uniqueID();


private:
	uint16_t static const default_config = 0x0300;
	spi_slave* device;
};



#endif /* STM32F103_SPI_FLASHMEM_H_ */
