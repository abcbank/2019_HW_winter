#include <avr/io.h>
#include <util/delay.h>

int main()
{
   unsigned int i = 0;
   DDRF = 0xF0;   //LED 네 개를 output으로 설정
   DDRG = 0x00;   //DDRG[0] = 0, 즉 PinG 0를 input으로 설정
   PORTF = 0x10;  //PortF[5] = 1, 즉 첫번째 LED를 on
   
   while(1)
   {   if(i>3) {i = 0 ; PORTF = 0x10;} //한바퀴 돌면 초기화
      
      while(!(~PING & 0x01));    //버튼이 on할때까지 대기
      _delay_ms(10); //10ms=확인 간격
      PORTF = PORTF<<1; //PortF를 shift, 즉 다음 pin의 LED를 on

      while(~PING & 0x01);  //버튼을 off할때까지 대기
      _delay_ms(10);

      i=i+1;
   }

   DDRB = 0x80;
   DDRF = 0xF0;
   PORTF = 0x10;
   DDRG = 0x00;

}