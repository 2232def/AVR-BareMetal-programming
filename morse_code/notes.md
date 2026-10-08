1. what is Timer?
Timer is a register in the AVR architecture.

Timer value increases/decreases automatically at a predefined rate.

Timer generally have a resolution of 8 to 16 bits.

So a 8bit timer is 8 bits wide so capable of holding value within 0-255.


2. Why do we need the clock and timer?

Clock
A steady high/low signal. At 16 MHz one cycle is 62.5 ns.
Synchronization: flip-flops capture inputs only on a clock edge, so every part of the chip acts together on stable values.
CPU speed: each instruction takes a fixed number of cycles (out takes 1, sbi and lds take 2).
Peripheral timing: UART bit timing, SPI/I²C clocks, the ADC clock and timer counting all derive from it.
Source: the UNO R3's 16 MHz comes from an external resonator, which is less accurate than a crystal. The internal RC oscillator (about 8 MHz) is another option. The source is chosen by fuses, and a wrong choice can leave the chip with no clock.
F_CPU only tells your code the real speed so _delay_ms() and baud math are right. It does not change the hardware.
Timer
A counter register (TCNT0) that hardware increments on each clock tick, with no CPU work.
Accurate: it counts the stable clock, so compiler output and interrupts don't affect it.
CPU stays free: time passes in the background.
Used for: delays, PWM, pulse-width measurement, ADC triggers and waking from sleep.
The math (16 MHz, prescaler 64, CTC)
16,000,000 ÷ 64 = 250,000 ticks per second, so one tick is 4 µs
1 ms = 250 ticks, so OCR0A = 249

The prescaler is needed because an 8-bit counter overflows after 256 ticks, which is only 16 µs without division.
