# SPI functions peripheral library

#### Part of the STM32F103 peripheral library

Notes:
1) CRC check not supported.
2) _SSOE_ (using the default NSS pin automatically) not supported . You can still use the default pin with soft SS just by declaring it as any other GPIO pin.
3) BIDIMODE supported only for one-way communication, either input via MISO or output via MOSI, freeing the other pin. Bidirectional transmission on one pin is not supported by any function of this library.
4) Higher level functions work in master mode only.


### Higher Level (class) functions

The higher level of the library consists of an abstract class `spi_slave` and two polymorphed classes `spi1_slave` and `spi2_slave` that provide the functions to work with slave SPI objects. Multiple slaves with unique configurations on one SPI channel can be created and used sequentially by `enable`ing and `disable`ing when needed. `spi1_slave` and `spi2_slave` classes are functually identical.

Constructor:

* **spi1_slave(gpio_pin&ast; pin)**

Creates a SPI slave object and binds a `pin` to it. `pin` is a pointer to a gpioX_pin object from the GPIO_func library. This pin is used as a chip select (aka SS, aka NSS) pin for the slave. Example:

```c++
uint16_t leds[16] = {0xFFFF, 0X00, 0X00, 0XF000}; //an array of LED values
gpioA_pin PA2(2); //PA2 pin object
spi1_slave dm634(&PA2); //PA2 is used as SS/Latch pin for the dm634 SPI slave

main(){
gpioA_init(); //init GPIOA
spi1_init(); //init SPI1
dm634.init(BIDI_OUTPUT | SOFT_SS | SPIBR8 | DATAFRAME_16); //init and config the object
dm634.enable(); //enable SPI1 slave
dm634.writeStream(leds, 16); //send 16 half-words there
dm634.ss_low(); //needed as DM634 is not fully SPI-compatible, see below
}
```

* void **ss_low()**
* void **ss_high()**

These functions turn the slave SS pin high (slave disabled) or low (slave active and waiting for transmission). Generally not needed, as other functions of this library use these by themselves; may be useful with some semi-SPI protocols that name SS pin a 'latch' pin and require a different behaviour from it (like sending a pulse to latch data, then staying low as with DM634 chips).

* void **init([uint16_t conf = default_config])**

Initializes the SS pin and saves the CR1 bits provided in `conf` (or the default config) for later use in `enable()`. Does not initialize the SPI peripheral (use `spi1_init()` for this). SE and MSTR bits don't need to be present in `conf`, they are set by the library when appropriate.

To provide `conf` you can either:
1. Calculate the 16-bit CR1 register value and include that value as is (default is 0x0300);
2. Use definitions from the `stm32f103_spi_reg` or the standard CMSIS library in the format SPI_CR1_XXX, where XXX is the name of the bit as stated in the STM32F10X reference manual. Include bits to be set, the rest will remain 0s.
3. Use the template: `init (mode | data_frame | soft_ss | lsb | baud_rate | clk) where:

place|define|value|result
---|---|---|---
mode | BIDI_INPUT |0x8000| Input-only mode, MISO pin active, MOSI pin free for other uses as GPIO pin (*Note: not as an AF pin!*)
| | BIDI_OUTPUT |0xC000| Output-only, MOSI pin active, MISO free
|  | FULL_DUPLEX |0| Full duplex mode, both pins used
data_frame | DATAFRAME_16 |0x0800| 16 bits data frame format
| | DATAFRAME_8 |0| 8 bits data frame format
soft_ss | SOFT_SS |0x0300| Software slave management, will also set the Internal slave select bit. This will free the NSS pin for other uses.
| lsb | LSB_FIRST |0x0080| LSB first
| | MSB_FIRST |0|MSB first
baud_rate| SPIBR2 |0| PCLK/2
| | SPIBR4 |0x0008| PCLK/4
| | SPIBR8 |0x0010| PCLK/8
| | SPIBR16 |0x0018| PCLK/16
| | SPIBR32 |0x0020| PCLK/32
| | SPIBR64 |0x0028| PCLK/64
| | SPIBR128 |0x0030| PCLK/128
| | SPIBR256 |0x0038| PCLK/256
clk | CLK_LOWRISE |0| CLK low when idle, rising capture edge
| | CLK_LOWFALL |0x0001| CLK low, falling edge
| | CLK_HIGHRISE |0x0003| CLK high when idle, rising edge
| | CLK_HIGHFALL |0x0002| CLK high, falling edge

The default CR1 initialization value is: `FULL_DUPLEX | DATAFRAME_8 | SOFT_SS | MSB_FIRST | SPIBR2 | CLK_LOWRISE`, i.e., `0x0300`, as only `SOFT_SS` sets any bits.

Values of `0` can be omitted. Thus, the default initialization can be written as just `SOFT_SS`, the result will be the same.

* void **enable()**

(Disables SPI channel), sets up the configuration bits provided in `init()`, then enables SPI channel. With multiple SPI slaves having different configs, `enable()` must be called each time the respective slave is about to be accessed. If the slaves have the same config, or there is only one slave, `enable()` can be called just once after the `init()`, unless SPI gets disabled with `disable()` somewhere in the code.

* void **disable()**

Disables SPI channel.

* void **write(uint16_t dat)**

Starts the communication (`ss_pin` = low), sends a single byte/2-byte word (depending on the DFF setting) to the slave, then closes the communication driving SS high.

* void **writeData(uint16_t dat)**

Sends a single byte/half word to the slave without starting or closing communication.

* void **writeStream(void&ast; arr, uint8_t num)**

Starts the communication, sends a stream of `num` bytes/words from an array pointed by `arr`, then closes the communication driving SS high.

_Note: `read` functions except `readData` work in `BIDI_INPUT` mode (output disabled) only. Not tested._

* uint16_t **read()**

Starts the communication, reads a byte/word from the incoming stream.

* int16_t **readData()** 

Reads a byte/half-word from the slave without starting or closing communication.

* void **readStream(void&ast; arr, uint8_t num)**

Starts the communication, then reads an incoming sream of `num` bytes/words into an array pointed by `arr`, closing the communication thereafter.
_Note: `transfer` should be used to read data from SPI in FULL_DUPLEX mode. The way SPI works, to receive something, SPI has to send something, even if the slave doesn't read it._

* uint16_t **transfer(uint16_t dat_out)**

Opens the communication, sends a byte/half-word `dat_out` using `writeData` then proceeds to read a byte/half-word from the slave using `readData`, driving SS pin high thereafter.

* void **transferStream(void&ast; arr_out, void&ast; arr_in, uint16_t num)**

*Note: `num` must be at least 2.*
*Note: `arr_out` and `arr_in` may point to arrays of either bytes (`uint8_t`) or half-words (`uint16_t`); DFF bit must be set to use 16-bit communication.*
Starts the communication, then sends `num` bytes/half-words from the container pointed by `arr_out` while simuntaneously receiving bytes/half-words into the container pointed by `arr_in`. `transferStream` uses the 'proper' way of communication described as 'Method 2' in the reference manual, see `spi1_transferData` below.

* void **seqTransfer(uint8_t&ast; arr_out, uint16_t num_out, uint8_t&ast; arr_in, uint16_t num_in)**

*Note: 8-bit mode only*
Starts communication, sends `num_out` of bytes from the container pointed by `arr_out`, then immediately proceeds to receive `num_in` bytes into the container pointed by `arr_in`. Can be used with flash memory chip for reading data from an address.

* void **DMATXenable()**
* void **DMARXenable()**
* void **DMATXdisable()**
* void **DMARXdisable()**

Enables/disables DMA requests for sending (TX) and receiving (RX) data.

/*** *this was removed into separate flashmem library*
* void **readFlash(uint32_t command, uint8_t&ast; arr_in, uint16_t num)**

For use with flash memory chips. Starts communication, sends 4 bytes of `command` (usually, the command and the 24-bit address), then immediately reads `num` of bytes into the container pointed by `arr_in`. 8-bit only.
**********/

### Lower level functions

LL functions work with the SPI directly and may be used in both slave and master modes. These functions don't control the NSS pin and can not start the SPI communications by themselves. `spi1_xxx` and `spi2_xxx` functions are identical except for the alternative pin mapping option available on SPI1 only.

* void **spi1_init([uint8_t af = 0])**

Initializes the SPI periphery and pins. Non-zero `af` specifies alternative pin mapping (SPI1 only), the remap must be done elsewhere in the code.
*Note: alternative map pins are used by JTAG by default; JTAG must be disabled prior to remapping. Thus `af` is untested in this library.*

* void **spi1_initMaster(uint16_t data_frame, uint16_t baud_rate [, uint16_t bidimode = 0, uint8_t sc = 1, uint8_t af = 0])**

Initializes the SPI periphery and pins and configures SPI as a master with the provided CR1 values. Check the table in `spi1_slave::init()` above for the pre-defined values for `data_frame`, `baud_rate` and `bidimode` (mode). `sc` selects software NSS (any non-zero value) or hardware NSS (zero).

* void **spi1_writeData(uint16_t dat)**

Sends a byte/word in continous mode.

* uint16_t **spi1_readData()**

Reads an incoming byte/word in continuous mode.

* void **spi1_transferStart(uint16_t dat)**

Writes `dat` into DR register. Used to start a 'proper' transfer sequence.

* uint16_t **spi1_transferData(uint16_t dat_out)**

Follows the 'proper' transfer loop described in the ref manual (25.3.5, Handling data transmission and reception): waits for TX, writes `dat_out` into the DR register, waits for RXNE, reads data from DR and returns it. The loop of `transferDatas` must be preceded by `transferStart` and followed by `transferEnd`.

* uint16_t **spi1_transferEnd()**

Reads last value from DR. Used to end a 'proper' transfer sequence.

* uint16_t **spi1_writeReadData(uint16_t dat_out)**

Simpler transfer sequence that should be a bit slower than the 'proper' one, as it doesn't write into DR while the previous value is getting shifted out and follows a sequentual procedure: write first, wait for TX, wait for RXNE, read.

* void **spi1_IRQenable()**
* void **spi1_IRQdisable()**

Enable/disable global SPIx global interrupt in the ARM core.

* void **spi1_TXinterrupt(uint8_t bit)**
* void **spi1_RXinterrupt(uint8_t bit)**
* void **spi1_JEOCinterrupt(uint8_t bit)**

Enable (bit == 1) or disable (bit == 0) the particular interrupt generation (TX empty, RX not empty, error).

* void **spi1_SSoutput(uint8_t bit)**

Enable/disable SS output in master mode.



