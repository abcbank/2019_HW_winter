#define __DELAY_BACKWARD_COMPATIBLE__ //추가! 현재 컴파일러로는 _delay_ms_()에 상수밖에 집어넣지 못한다. 이거 없으면 에러남!

#include <avr/io.h>
#include <util/delay.h>
unsigned char FND_SEG[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7C, 0x07, 0x7F, 0x67 }; //SEG 0 ~ 9
void init_system(void) // Port Initialization
{
DDRA = 0xFF; // Set Port F as output
DDRE = 0x0C; // PortE(3:2) = LED_CTRL, LED_DATA must be output
PORTE = 0x04; // LED_CTRL
PORTA = 0X01; // LEFT SEG ON
}
int main(void)
{
init_system(); //Port Initialization
int j; //segment variable
int k=70;
for(j = 0; j<4 ; j++)
{
PORTE = 0X04;
PORTA = 0X01 << j;
PORTE = 0X08; //LED DATA
PORTA = FND_SEG[j]; //numeral display through Port A
_delay_ms(1000); //Delay
}
while(1) //infinite loop
{
for(j = 0; j<4 ; j++)
{
PORTE = 0X04;
PORTA = 0X01 << j;
PORTE = 0X08;
PORTA = FND_SEG[j];
_delay_ms(k);
}
if(k>=2)
k=k-1;
//Delay is getting be short until 1ms.
}
return 0;
}