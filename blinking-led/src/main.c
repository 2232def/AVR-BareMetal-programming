#include <avr/io.h>     // register names: DDRB, PORTB, PB5 ...
#include <util/delay.h> // _delay_ms(); needs F_CPU (set in Makefile)

int main(void) {
  DDRB |= (1 << PB5); // make PB5 an output

  while (1) {
    PORTB |= (1 << PB5); // PB5 high  -> LED on
    _delay_ms(500);

    PORTB &= ~(1 << PB5); // PB5 low   -> LED off
    _delay_ms(500);
  }

  return 0; // never reached
}
