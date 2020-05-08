# SPI Flash Memory sub-library
#### Part of the STM32 peripherals and registers library

A simple example library to work with the `25` line of SPI flash memory chips using the [stm32f103_spi_func peripheral library](https://github.com/Ontaelio/STM32F103-libraries/blob/master/Docs/stm32f103_spi_func.md). It provides a `spi_flash` class on top of a `spi_slave` object to write, read and erase flash memory via SPI.


Constructor:

* **spi_flash(spi_slave&ast; target)**

Creates a `spi_flash` object that works with the `spi_slave` object pointed by `target`.

* void **init()**

Calls the `spi_slave` `init()` function with the default argument 0x0300.

* void **write(uint32_t address, uint8_t&ast; arr_out [, uint8_t num = 0])**

Enables write, then page-writes data from a container pointed by `arr_out` at the flash memory `address`. If `num` is 0 (default) the full page of 256 bytes is written, else `num` provides the number of bytes to be written (max 255).

* void **read(uint32_t address, uint8_t&ast; arr_in, uint16_t num)**

Reads `num` of bytes starting at flash memory address `address` into a container pointed by `arr_in`.

* void **fastRead(uint32_t address, uint8_t&ast; arr_in, uint16_t num)**

Same as `read`, but using the `fastRead` flash memory command.

* void **writeEnable()**

Enables writes on the flash memory chip. All write/erase functions of this library except `chipErase()` enable writes themselves.

* void **writeDisable()**

Disables writes on the flash memory chip.
*Note: writes get automatically disabled after each write/erase operation, so `writeDisable()` is generally not needed.*

* uint8_t **busy()**

Returns the busy status of the flash memory chip. Can be used in a `while` loop after writing and erasing memory to make sure the device finished its internal data shifting and is available for further operations:
```c++
while (device.busy());
```

* void **erase(uint32_t address)**

Sector erase (4K) at `address`.

* void **block32erase(uint32_t address)**

Block erase (32K) at `address`.

* void **block64erase(uint32_t address)**

Block erase (64K) at `address`.

* void **chipErase()**

Erases the chip memory. For safety reasons, `writeEnable()` must be explicitly called before the chip erase function.

* uint8_t **manufacturer()**

Returns the Manufacturer ID code.

* uint8_t **deviceID()**

Returns the Device ID code.

* uint32_t **JEDEC()**

Returns the JEDEC code: three bytes representing Manufacturer ID, Memory Type and Capacity.

* uint64_t **uniqueID()**

Returns the device's Unique ID.

Example:

```c++
gpioA_pin PA4(4); //create a GPIO pin object for SS first
spi1_slave winmem(&PA4); //then create a spi_slave object
spi_flash spimem(&winmem); //finally, create a spi_flash object
uint8_t muchlo[256]; //arrays to write/read data
uint8_t muchlo2[256];

main(){
spi1_init(); //initialize SPI
winmem.init(); //config the spi_slave
winmem.enable(); //enable spi_slave, then work with spi_flash

//spimem.write(0x000F00, muchlo); //writes commented out
//spimem.erase(0x000101); //erases too
while (spimem.busy()); //wait after any write/erase operation
spimem.fastRead(0x000F00, muchlo2, 256); //fastread stuff
}
```
