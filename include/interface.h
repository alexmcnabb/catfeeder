#include <Arduino.h>

/*
This device can be accessed over I2C or Serial via USB
The interface consists of a register bank. Some registers are read only, some are read-write
When registers are written over I2C, the first byte sets the address pointer
The address pointer auto-increments with reads and writes
The I2C device address is set via some IO lines

The serial interface operates basically the same way, but with a header on the start of the packets
Lost bytes could cause issues, as there's no real resync system, but it should be fine using the virtual serial interface
Serial interface uses it's own address pointer, so both interfaces are safe to use simultaneously

Write
    [0xAA] [Length] [Address pointer] [Data] [Data] [Data] ....
    Length is address pointer plus data
Write response
    [0xAA]
Read
    [0xAB] [Length]
    Length is number of data bytes
Read response
    [0xAB] [Data] [Data] [Data] [Data] [Data] ....

*/

#define NUM_REGS 18
extern volatile uint8_t registerMap[NUM_REGS];
extern const uint8_t registerWriteMask[NUM_REGS];

extern volatile int32_t* regCurrentPosition;
extern volatile int32_t* regTargetPosition;
extern volatile int16_t* regTargetVelocity;
extern volatile int16_t* regP;
extern volatile int16_t* regI;
extern volatile int16_t* regD;
extern volatile uint8_t* regControl;
extern volatile uint8_t* regMaxPWM;

void updateSerialInterface();
void initInterface();