/**
 * @file 3_buzzer.c
 * @author HailayLin (hailay@qq.com)
 * @brief 
 * @version 0.1
 * @date 2020-12-09
 * 
 * @copyright Copyright (c) 2020  Hailay.site & Xihe.ai
 * 
 */

#include<REG52.H>

typedef unsigned int    u16;
typedef unsigned char   u8;

sbit beep=P1^5;

//延迟x毫秒数
void delay(u16 x)
{
    u16 i,j;
    for(i=x;i>0;i--)
        for(j=114;j>0;j--);
}

int main(){
    while (1)
    {
        beep=~beep;
        delay(1);
    }
    
}