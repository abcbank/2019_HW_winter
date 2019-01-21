#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void init_port(void)
{
	DDRF = 0xF0;
	PORTF = 0x00;
	DDRE = 0x00;
	PORTE = 0xFF;
}

void init_interrupt(void)
{
	EIMSK = 0x00; // When changing ISCn1/ISCn0 bits, the interrupt must be disabled by clearing its Interrupt Enable bit
					// in the EIMSK Register.
					// Otherwise an interrupt can occur when the bits are changed.
	EICRA = 0x00;
	EICRB = 0x08;
	EIMSK = 0x20;
	EIFR = 0xFF;
}

int main(void)
{
	init_port();
	init_interrupt();
	sei();
	
unsigned int i = 0;
   DDRF = 0xF0;
   DDRG = 0x00;
   PORTF = 0x10;
   
   while(1)
   {   if(i>3) {i = 0 ; PORTF = 0x10;};
      while(!(~PING & 0x01)) ;
      _delay_ms(10);
      
      
      PORTF = PORTF<<1;
      
      while(~PING & 0x01) ;
      _delay_ms(10);
      i=i+1;
   }
	return 0;

}
	ISR(INT5_vect)

{
	PORTF = ~PORTF;
}
