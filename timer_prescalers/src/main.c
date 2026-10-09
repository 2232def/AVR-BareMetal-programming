#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>

volatile uint8_t count;
void main() {
  // prescaler f_cpu_clk/1024
  TCCR0B |= (1 << CS02) | (1 << CS00);

  // enable overflow interrupt
  TIMSK0 |= (1 << TOIE0);

  // initialize counter
  TCNT0 = 0;

  // Initialize the variable
  count = 0;

  // port B
  DDRB |= (1 << PB5);

  // enable global interrupt
  sei();

  // Infinite loop
  while (1)
    ;
}

ISR(TIMER0_OVF_vect) {
  count++;

  if (count >= 61) {
    PORTB ^= (1 << PB5);

    count = 0;
  }
}
