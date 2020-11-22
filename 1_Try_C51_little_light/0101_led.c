#include "REG52.H"
#define uint unsigned int
sbit led0=P2^0;
sbit led1=P2^1;
//延迟的毫秒数
void delay(uint time)
{
	uint i,j;
	for(i=0;i<time;i++)
		for(j=0;j<110;j++);
}

void main()
{
	//init
	led0=led1=1;

	led0=0;
	delay(1000);
	led0=1;
	led1=0;
	delay(1000);
}