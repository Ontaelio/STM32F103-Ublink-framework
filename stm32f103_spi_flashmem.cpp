/*
 * STM32F103 SPI Flash memory sub-ibrary source file
 * Part of STM32F103 register and peripherals library
 *
 * Dpcumentation available in the provided MD file.
 *
 * (c) 2019 Dmitry Reznikov ontaelio(at)gmail.com
 *
 * Can be freely used according to the GNU GPL license.
 */

#include <stm32f103_spi_reg.h>
#include <stm32f103_spi_func.h>
#include <stm32f103_spi_flashmem.h>
#include <stdio.h>


void spi_flash::write(uint32_t address, uint8_t* arr_out, uint8_t innum)
{
	uint16_t num = innum;
	if (!innum) num = 256;
	writeEnable();
	device -> ss_low();
	device -> writeData(0x02);
	device -> writeData(address >> 16);
	device -> writeData((address >> 8)&0xFF);
	device -> writeData(address & 0xFF);
	device -> writeStream(arr_out, num);
	device -> ss_high();
}

void spi_flash::read(uint32_t address, uint8_t* arr_in, uint16_t num)
{
	uint8_t command[4] = {0x03};
	command[1] = (address&0xFF0000)>>16;
	command[2] = (address&0x00FF00)>>8;
	command[3] = (address&0x0000FF);
	device -> seqTransfer(command, 4, arr_in, num);
}

void spi_flash::fastRead(uint32_t address, uint8_t* arr_in, uint16_t num)
{
	uint8_t command[5] = {0x0B};
	command[1] = (address&0xFF0000)>>16;
	command[2] = (address&0x00FF00)>>8;
	command[3] = (address&0x0000FF);
	command[4] = 0;
	device -> seqTransfer(command, 5, arr_in, num);
}

void spi_flash::writeEnable()
{
	device -> write(0x06);
}

void spi_flash::writeDisable()
{
	device -> write(0x04);
}

uint8_t spi_flash::busy()
{
	device -> ss_low();
	device -> writeData(0x05);
	device -> readData();
	device -> writeData(0);
	uint8_t res = device -> readData();
	device -> ss_high();
	return (res & 1);
}

void spi_flash::erase(uint32_t address)
{
	uint8_t command[4] = {0x20};
	command[1] = (address&0xFF0000)>>16;
	command[2] = (address&0x00FF00)>>8;
	command[3] = (address&0x0000FF);
	writeEnable();
	device -> writeStream(command, 4);
}

void spi_flash::block32erase(uint32_t address)
{
	uint8_t command[4] = {0x52};
	command[1] = (address&0xFF0000)>>16;
	command[2] = (address&0x00FF00)>>8;
	command[3] = (address&0x0000FF);
	writeEnable();
	device -> writeStream(command, 4);
}

void spi_flash::block64erase(uint32_t address)
{
	uint8_t command[4] = {0xD8};
	command[1] = (address&0xFF0000)>>16;
	command[2] = (address&0x00FF00)>>8;
	command[3] = (address&0x0000FF);
	writeEnable();
	device -> writeStream(command, 4);
}
void spi_flash::chipErase()
{
	device -> write(0xC7);
}

