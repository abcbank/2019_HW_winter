#include<avr/io.h>
#include<avr/interrupt.h>

void init_port(void) //초기화 
{
   DDRF = 0xF0;
   PORTF = 0x00; //input
   DDRE = 0x00;
   PORTE = 0xFF;
}

void init_interrupt(void)
{
   EIMSK = 0x00;
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
   while(1)
   {
   }
   return 0;
}

ISR(INT5_vect)
{
   PORTF = ~PORTF;
}