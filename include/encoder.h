#include <Arduino.h>

/*
Quadrature encoder decoder
Encoder inputs should be connected to PD2 and PD3, using external interrupts INT2 and INT3
Both IRSs are identical, but with reversed direction. One uses add and adc instructions, and the other uses sub and sbc isntructions
By my count each take 28 cycles to execute and testing shows a max working frequency of ~350K counts per second, or 87.5k pulses per second.
I'd recommend driving it at no more then 200K counts per second, but there will be missed counts if other interrupts are being called.
ISR_NAKED is used so that we can optimise the prologue and epilogue sections ourselves

As the numbers are stored in signed 16bit counters, these should be read by the main process fast enough to ensure they don't overflow
As long as updateEncoderCounts is called at least 10x per second
The 32 bit long integer will overflow after three hours at 200k counts per second.
*/

void initEncoder();
void updateEncoderCounts();
int32_t getEncoderCount();