# AVR HW 스터디
- 개요
  - 3학년 실험을 대비한 AVR 학습 및 실습

## 예산
   - AVR 보드
   - AVR Studio 4
   - 케이블선
## 참여 인원
   - Boot4AVR
     - 김지형, 양형균, 이준형, 이재영, 권희정, 이석호, 최희정

## 개발 환경 설정
   -Software 
      -AVR Studio 4
   1. 해당 [영상](https://www.youtube.com/watch?v=4LK3vprsKRM)을 따라 설치.
         조영범 교수님께서 제공해주신 AVR Studio 4 사용. 상위버전은 설정도 복잡하고 오류날 가능성도 높기 때문에 사용을 지양할 것.
   2. msys-1.0-vista64라는 파일 압축 해제 및 C:\WinAVR-20100110\utils\bin 에 붙여넣기.
   - Hardware
      - AVR Board

추천 자료
![마이크로컨트롤러 AVR ATMEGA128](../img/book_01.jpg)
마이크로 컨트롤러 AVR ATmega128/이상설 지음/2013년 발행

## 개발 과정
Day 01 
  1. AVR보드 LED 점등 코드 해석 및 실습
  2. AVR을 활용하여 설계할 물품 토의    

Day 02
   1. ATmega128의 기본 구조 학습
   2. 7segment를 활용한 실습

Day 03
   1. Switch를 활용한 실습
   2. Interupt를 활용한 타이머 제작

### Day01
- 일시 : 2019.01.11 20:00 ~ 22:00
- 작성자 : 유재덕

학습 목표
  1. AVR보드 LED 점등 코드 해석 및 실습
  2. AVR을 활용하여 설계할 물품 토의


#### 1. AVR보드 LED점등 코드 해석 및 실습
######example01
```c
#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 1000000UL

int main(void){
   unsigned int i;
   DDRF= 0xF0;      //DDRX : X reg set up
    PORTF= 0x10;    //set X reg(8bit)
   
   while(1){
      for(i=0; i<4;i++){
         _delay_ms(1000);
         PORTF=PORTF<<1;    //shift
      }
      PORTF=0x10;
   }
   DDRB=0x80;
   DDRF=0xF0;
   DDRG=0x00;
   PORTF=0x10;
}
```
코드 설명
Port F - 회로에서 LED를 키고 끄는것을 제어하는 역할
DDRF[0:7] - F Port init.
   - 만약 DDRF[4] = 1 일때, DDRF[4]는 output이라는 의미
   - 만약 DDRF[4] = 0 일때, DDRF[4]는 input이라는 의미

PORTF[0:7] - value of F Port
LED 점등의 경우 상위 4bit, 즉 DDRF[0:3]과 PORTF[0:3]만 사용

ex)
```c
DDRF=0xF0;
```
[0,0,0,0,0,0,0,0] ㅡ>[1,1,1,1,0,0,0,0]
상위 4 bit를 사용한다고 메인 보드에 예고

```c
PORTF=0x10;
```
[0,0,0,0,0,0,0,0] ㅡ>[0,0,0,1,0,0,0,0]
해당 비트의 값을 1로만듦. 1=점등

###### 프로그램 업로드
![AVR_upload1](../img/AVR_01.png)
- Click Configuration Options

![AVR_upload2](../img/AVR_02.png)
- Set frequency 16,000,000(보드마다 다름)

![AVR_upload3](../img/AVR_03.png)
-Build program

![AVR_upload4](../img/AVR_04.bmp)
- Click Display 'Connect' Dialog

![AVR_upload5](../img/AVR_05.bmp)
- Check connected port at Device Manager, set Platform(STK5000) and Port. Then, press Connect.

![AVR_upload6](../img/AVR_06.png)
- Check fuse bit of board. 

![AVR_upload7](../img/AVR_07.png)
- Read Signature of board.

![AVR_upload8](../img/AVR_08.png)
Set Input HEX File as coded file, press Program

##### 토의 사항
- [예제 코드](#example01)의 마지막 네 줄의 용도는 무엇인가?

##### Trouble Shoot
- 코드에서 설정한 delay에 비해 빠르게 점등되는 보드가 몇몇 있다. 어쨰서 이런 현상이 일어나는가?
  - AVR Studio의 기준 주파수가 있고, 보드 내의 기준 주파수가 있다. 이 둘이 서로 일치하지 않는 상황에서 코드를 업로드할 경우, 보드와 코트 사이에 충돌이 생길 수 있다. 

- 몇몇 보드는 AVR Studio에서 액세스 자체를 할 수 없다. 해당 현상의 원인은 무엇인가?
  - fuse bit을 임의로 바꾼 몇몇 보드들이 임의로 바꾼 환경과 보드의 환경이 서로 어긋나면서 보드 자체가 액세스를 거부하는 것으로 추정된다.


#### 제작 아이디어 토의
1. 타이머
2. [적외선 레이더](https://kocoafab.cc/make/view/444)
 서브모터와 적외선 거리 센서를 활용해 적외선 레이더 제작
3. [솔라 트레커](https://kocoafab.cc/make/view/341)
  서브모터와 조도센서를 활용해 솔라 트레커를 제작
  솔라 트레커 : 빛(광원)의 움직임에 따라 이동하는 장치
4. [적외선 리모콘](https://kocoafab.cc/tutorial/view/703)
   IRremote 모듈을 활용하여 적외선 리모콘 제작

5. 버스 정류장 open api 활용
   버스 정류장 open api를 활용하여 보다 개선된 방법으로 사용자에게 버스 운행 정보를 제공할 수 있는 장치 제작


### Day02
학습 목표
   1. ATmega128의 기본 구조 학습
   2. 7segment를 활용한 실습

#### ATmega128의 기본 구조
- 6개의 8비트 양방향 병렬 I/O 포트
  - Port A~ Port F
- 1개의 5비트 양방향 병렬 I/O 포트
  - Port G
- Port A~ Port E
  - 범용 I/O 포트로 사용될 경우 read-modify-write동작 가능. 즉, 입출력 방향 변경 없이 SBI(Set Bit) 및 CBI(Clear Bit) 명령에서 포트의 동작방향이 달라질 수 있다.
- DDRxn
  - x : Port A ~ Port G
  - n : 각 포트의 비트번호
  - 입출력 방향을 설정. 1: 출력 0: 입력
  - Read & Write
- PORTxn
  - 데이터 출력
  - Read & Write
- PINxn
  - 포트 입력
  - Read
- SFIOR (Special Function I/O Register)의 PUD
  - PUD비트를 1로 설정하면 그 기능이 금지
보다 자세한 기능이 궁금하다면 [ATmega128 매뉴얼](http://www.kjit.bme.hu/images/stories/targyak/mechatronika_robot_mcu/SH_kepzes/atmel_atmega128_manual.pdf)을 참고

#### 7segment를 활용한 실습
###### example02
```c
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
```
- DDR A : 사용하기 위해 초기화하는 PIN을 의미 
- DDR E : Port E에서 E2, E3 핀 사용
   - PE2 : LED_CTL
   - PE3 : LED_DATA
- Port A : E3과 E4에 따라 의미하는것이 달라짐. 7 Segment Control p.27 참고
   - E2일때 : Port A는 활성화되는 segment들을 결정함
   - E3일때 : Port A는 한  segment 점등하는 LED를 의미함
```c
for(j = 0; j<4 ; j++)
{
PORTE = 0X04;
PORTA = 0X01 << j;
PORTE = 0X08; //LED DATA
PORTA = FND_SEG[j]; //numeral display through Port A
_delay_ms(1000); //Delay
}
```
Port E = 0X04;
   -E[0,0,0,0,0,1,0,0] : E2 = 1
   -E2=1일때, Port A는 켜지는 LED를 의미한다.

Port A = 0X01 << j 
   -A[0,0,0,0,0,0,0,1] : A1 = 1
   -A를 j만큼 shift하면서 1에 해당하는 segment를 점등한다.

Port E = 0X08;
   -E[0,0,0,0,1,0,0,0] : E4 = 1
   -E3=1일때, Port A는 LED에 나타나는 숫자를 의미한다

Port A = FND_SEG[j] 
   -FND(Flexible Number Display)는 segment의 다른 표현
   -j라는 숫자가 segment에 표기될 수 있도록, 임의의 Port A의 값들을 조정해줌.
   ![7 segment](http://www.circuitstoday.com/wp-content/uploads/2016/03/7_segment_display_pin_outs.png)
##### Trouble Shooting
- [예제 코드](#example02)의 #define 구문을 제외할 경우, 해당 코드는 실행되지 않는다.  
  - 과거 _delay_ms() 함수의 매개변수는 변수 또한 쓰일 수 있었다. 그에 비해 최근 버전의 컴파일러는 _delay_ms() 함수의 매개변수로 상수만을 받도록 설계되었다. 결국 이는 코드가 컴파일러의 변화에 따라가지 못해 일어난 오류라 할 수 있다.


### Day03
학습 목표
   1. Switch 실습
   2. Interrupt를 활용해 타이머 제작

#### 1. Switch 실습
- AVR switch 회로
  ![switch](../img/switch/switch01.png)
  - 스위치의 input은 DIN[0:4], INT[4:5]에 해당한다.
- AVR 메인 보드 회로
  ![main](../img/board_main.png)
  - DIN[0:4]는 PortG[0:4]의 input에 해당한다.
- 결국, PortG[0:4]를 0으로 설정하여 특정 스위치의 input을 받아올 수 있다.
######example
```c
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
```
```c
DDRG = 0x00;
```
- switch의 output은 Pin D의 input이 된다. 
- SW5만 사용하므로 Pin D[0]를 0으로 설정(나머지는 X)
```c
DDRF = 0xF0;
```
- LED에 해당하는 Port F를 output으로 설정.
```c
PORTF = 0x10;
```
- 디폴트 값으로 첫번째 LED를 on
```c
      while(!(~PING & 0x01));    
      _delay_ms(10); 
      PORTF = PORTF<<1; 
```
- SW5가 눌리면 10ms 후  Port F를 1만큼 shift
```c
      while(~PING & 0x01);  //버튼을 off할때까지 대기
      _delay_ms(10);
      i=i+1;
```
- 눌렀던 SW5를 때면 10ms 후 i값 증가

##### Trouble Shooting

#### 2. Interrupt를 활용해 타이머 제작
- Interrupt
  - 외부의 요구에 의해서 현재 실행 중인 프로그램을 잠시 중단하고 보다 시급한 작업을 먼저 수행한 후 다시 실행중이던 프로그램을 복귀하는 것.
  - 외부에서 신호를 준다는 점에서 polling과 다름
  - ATmega128 board에선 INT4, INT5가 interrupt로 작동 가능하다.

- Polling
  - 특정 주기마다 작업을 중단하며 외부의 요구 사항을 확인하는 것.
  - 내부에서 외부의 요구를 확인한다는 점에서 interrupt와 다름

######example01
```c
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
```
- INT4 = 1이 되면 interrupt가 발생해 Port F의 값들이 반전된다.


```c
void init_port(void) //초기화 
{
   DDRF = 0xF0;
   PORTF = 0x00; //input
   DDRE = 0x00;
   PORTE = 0xFF;
}
```
- DDRF : LED부분을 output을 사용
- Port F : 처음엔 전부 off 상태
- DDRE : INT5의 output은 Pin E[5]의 input이 된다. 따라서 DDRE[5] = 0으로 설정
- Port E : Port E[5] = 1일때 interrupt 발생? Port E를 0XFF로 설정하면 초기 한번 발생하고 시작하지 않나?

```c
void init_interrupt(void)
{
   EIMSK = 0x00;
   EICRA = 0x00; 
   EICRB = 0x08;
   EIMSK = 0x20;
   EIFR = 0xFF;
}
```
- EIMSK(External Interrupt Mask Register) 
  -  어떤 입력을 Interupt로 사용할지 결정.
- EICRx(External Interrupt Control Register)
  -  어떤 입력에 반응할지 결정. 스위치가 눌리는 순간 interrupt를 작동할지, 아니면 스위치가 눌렸다 다시 올라가는 순간 interrupt를 작동할지 결정해줌.
  -  https://blog.naver.com/dhfl1849/220828498160
- EIRF(External Interrupt Flag Register)
  - 어떤 interrupt가 트리거가 되었는가를 표시함.
  - 해당 interrupt service routine으로 jump하면 0으로 설정

#####Trouble Shooting
[AVR] 코드와는 달리 INT4를 누를때 interrupt 발생한다.
- Schematic과 비교해보면, 저항 R27과 INT5가 연결되어 있다. 보드에는 INT4와 R27과 연결되어있음