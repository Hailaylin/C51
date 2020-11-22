/*
衔接UPRE的流水灯任务

*/
#include<REG52.H>
#include<INTRINS.H>
#define uint unsigned int
#define uchar unsigned char
//init light?不用？

//延迟x毫秒数
void delay(uint x)
{
    uint i,j;
    for(i=x;i>0;i--)
        for(j=110;j>0;j--);
}

int main()
{
    uchar aa;
    aa=0xfe;
    while(1)
    {
        P2=aa;
        delay(1000);
        aa=_crol_(aa,1);
    }
}