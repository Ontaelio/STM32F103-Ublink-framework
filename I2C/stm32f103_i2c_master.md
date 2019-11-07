#I2C lib



### Setup, tweak and troubleshooting functions

* `uint8_t i2c1_resetBus([uint8_t altpins = 0])`
Checks the i2c bus and tries to reset it if it's unsynchronised, i.e. SDA line is held low. This condition may happen if the slave has its own power source (e.g. a battery). In that case when the master resets while receiving data, the slave continues to wait for the incoming clock pulse. `resetBus` provides up to nine clock pulses while monitoring SDA line, once SDA gets high it generates a START condition followed by a STOP condition and returns 0. If SDA remains low after 9 clock pulses, 1 is returned. `altpins` set to 1 or `I2C1_ALT` specifies alternative pins for i2c1; default is 0.

==_Note: `i2cX_resetBus`, if present, must be called **before** `i2cX_init` as it resets pin modes to general IO._==

* `void  i2c1_init(uint8_t speed [,uint8_t altpins = 0])`
Initialises the I2C bus in master mode with default values. `speed` is either `I2C_SM` (0) for Standard Mode (100 kHz) or `I2C_FM` (1) for Fast Mode (400 kHz). Optional `altpins` bit can be set to `I2C1_ALT` (1) to use alternative I2C1 pinout (`init` will remap pins in AFIO_MAPR).

* `void i2c1_tweak(uint8_t fs_bit, unit8_t duty_bit, uint16_t ccr_val)`
Tweaks the speeds after the default initialization. `fs_bit` and `duty_bit` are bit values (0 or 1) for F/S and DUTY registers (`fs_bit == 1` for fast mode, `0` for slow mode; `duty_bit == 1` for 16/9, `0` for default 2/1); `ccr_val` is CCR bits [11:0]. Default values are: 178 for SM and 30 for FM (less = faster), DUTY = 0. The only place to change the DUTY bit from the library.

* `void i2c1_APB1freq(uint8_t pclk1_mhz)`
By default, `i2cX_init()` assumes 36 MHz frequency for APB1 domain. This function sets a different frequency and calculates the CCR value accordingly. `pclk1_mhz` is PCLK1 speed in MHz. Must be called after `init()`; doesn't change F/S and DUTY registers.

* `void i2c1_setFreq(uint32_t i2c_freq)`
Sets the I2C frequency, changing the default values. `i2c_freq` is in Hz. Defaults are 100000 for SM and 400000 for FM. F/S and DUTY are kept. May be used with `ping` to find out the maximum working speed for the current hardware setup (generally just above 1 MHz).

* `uint8_t i2c1_ping(uint8_t addr)`
Tests the connection to the device at `addr`. Checks whether the line is busy, if so tries to reset it, generates START, sends addr, gets an aknowledgement, generates STOP. If everything went fine, returns 0. If no, returns an error code:
1: Line busy, reset failed.
2: START failed, ARLO not set.
3: START failed, ARLO was set, resetting failed.
4: No aknowledge received from `addr`.

* `uint8_t i2c1_scanAddr(uint8_t startAddr = 0x07)`
Scans the i2c bus for answering devices, starting with `startAddr + 1` and ending with `0x77` (the rest are reserved). Once the first available device is found, its address is returned. This function uses `i2cX_ping` described above and is relatively slow.

### Higher level class read/write functions
* `i2c1_slave device(uint8_t device_addr [,uint8_t reg_bits = 8])`
Creates an object for an I2C slave `device` (sample variable name) at address `device_addr`. Optional `reg_bits` value specifies the number of bits in this devices register addresses (up to 16).

* `device.write(uint16_t reg_addr, uint8_t a_byte)`
Sends a single byte `a_byte` to register address `reg_addr` of a slave object `device`.

* `device.write16(uint16_t reg_addr, uint16_t a_word)`
Sends a 16-bit word `a_word` to register address `reg_addr` of a slave object `device`. MSB first.

* `device.write32(uint16_t reg_addr, uint32_t a_word)`
Sends a 32-bit word `a_word` to register address `reg_addr` of a slave object `device`. MSB first.

* `device.writeStream(uint16_t reg_addr, uint8_t* arr, uint8_t num)`
Sends a stream of `num` bytes from an array pointed by `arr` to register address `reg_addr` of a slave object `device`. 

* `uint8_t device.read(uint16_t reg_addr)`
Reads a byte from register address `reg_addr` of a slave object `device`.

* `uint16_t device.read16(uint16_t reg_addr)`
Reads a 16-bit word from register address `reg_addr` of a slave object `device`.

* `uint32_t device.read32(uint16_t reg_addr)`
Reads a 32-bit word from register address `reg_addr` of a slave object `device`.

* `device.readStream(uint16_t reg_addr, uint8_t* arr, uint8_t num)`
Reads a stream of `num` bytes starting with register address `reg_addr` of a slave `device` into an array pointed by `arr`.

**Class application example**
```c++
i2c1_slave eeprom(0x50, 12); //an EEPROM chip with 12-bit register addresses
i2c1_slave clock(0x68); //and RTC chip with default 8-bit register addresses
uint8_t things[16]; //an array of bytes

int main(){
    i2c1_resetBus(); //the RTC chip typically has a battery, it may hang the bus
                     //due to microcontroller reset
    i2c1_init(I2C_FM); //fast mode

    eeprom.readStream(0xAA0, things, 16); //read 16 bytes starting with reg addr 0xAA0
                                          //into the array things[]
    eeprom.write32(0x00A, 0x1234AAAA); //write a 32-bit word starting with reg addr 0x00A

    uint8_t secondsBSD = clock.read(0x00); //read seconds from the RTC chip
}
```
### Lower level general functions

* `void i2c1_start(uint8_t addr)`
Starts communication: waits for the line to be clear, generates START followed by the 7-bit device address `addr`, waits for the acknowledge.

* `void i2c1_writeByte(uint8_t stuff)`
Sends the byte `stuff` and keeps the communication open.

* `void i2c1_writeLast(uint8_t stuff)`
Sends the byte `stuff` then waits for the BTF bit to be set meaning the transmission from the shift register into the slave device is over. Should be used if only one byte is being sent. Can be used to send a stream of bytes in bad conditions, according to the datasheet (slower, but ensures each byte was really sent and acknowledged). Thus no STOP in this function, it must be generated separately.

* `void i2c1_writeStream (uint8_t* arr, uint8_t num)`
Writes a stream of `num` bytes from an array pointed at by `arr` (either a pointer to the needed member or just the name of the array without square braces). The last byte is sent with `writeLast`; STOP required to be generated separately.

* `void i2c1_stop()`
Generates STOP.

*Note: all the read functions must be preceded by sending the register address to be read.*

**'Method 2' read functions (recommended)**

* `uint8_t i2c1_readOneByte(uint8_t addr)`
Restarts, sets up, generates STOP, returns one byte from a device at `addr`.

* `uint8_t i2c1_readFirstOfTwo(uint8_t addr)`
Restarts, sets up, reads one byte from a device at `addr`, generates STOP, sets up DR with the second one. Returns the first of the two bytes, the second can be read from DR right away (see below).

* `uint8_t i2c1_readFirstOfThree(uint8_t addr)`
Restarts, sets up, reads one byte, generates STOP and sets up two remaining bytes in DR and the shift register. Returns the first byte; the second one can be read from DR right away, the third one must be read after checking RXNE or a small delay. `addr` is again the slave device address. 

* `void i2c1_readStreamMethod2 (uint8_t addr, uint8_t* arr, uint8_t num)`
Reads `num` bytes into the array pointed at by `arr`. `num` **must** be more than three (function doesn't check this).

* `uint8_t i2c1_DR()`
Returns contents of DR.

* `inline void i2c1_checkRXNE()`
Waits for RXNE to get set. *Possible endless loop if used in a wrong place*.

**'Method 1' read functions (faster and smaller code, possible errors)**
* `void i2c1_readStart(uint8_t addr)`
Starts an incoming communication, sending RESTART, waiting for the `addr` to be acknowledged and setting ACK bit high. 

* `uint8_t i2c1_readByte()`
Reads a byte from the slave device, keeping communication open for further receives.

* `uint8_t i2c1_readLast()`
Resets the ACK bit then reads a byte. The connection must be closed thereafter by sending STOP; this function doesn't do it to maintain integrity with `writeLast`.

* `void i2c1_readStream(uint8_t* arr, uint8_t num)`
Reads a stream of `num` bytes into an array pointed by `arr`. Last byte is read with `readLast`, requires a STOP to be sent separately.

_Note: the W/R bit in `addr` is added by the library functions._

**Typical application for 'Method 1'**
Consider an EEPROM chip with 12-bit register addressing. The chip is at the default address 0x50, the register we're dealing with is 0xAAA.
To write a byte `a_byte` // write a stream from `some_array[16]`
```c++
i2c1_start(0x50);
i2c1_writeByte(0xAAA >> 8); 
i2c1_writeByte(0xAAA & 0xFF);
i2c1_writeLast(a_byte); //i2c1_writeStream(some_array, 16);
i2c1_stop();
```
To read a byte into `a_byte`// read a stream of bytes into `some_array[16]`
```c++
i2c1_start(0x50);
i2c1_writeByte(0xAAA >> 8);
i2c1_writeByte(0xAAA & 0xFF);
i2c1_readStart(0x50);
a_byte = i2c1_readLast(); //i2c1_readStream(some_array, 16);
i2c1_stop();
```
