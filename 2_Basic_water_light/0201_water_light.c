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
        for(j=114;j>0;j--);
}
//清空灯+延时毫秒数
void clear(uint time){
    P2=0xff;
    delay(time);
}
//亮的方向，l左,r右；位移起始值;每次位移的间隔时间;位移次数
void move_direction(char direc,uchar a,uint time,int ci)
{
    void delay(uint x);
    void clear(uint time);
    uint i;
    for(i=0;i<ci;i++){
        P2=a;           //把位移计算后的值交给管脚实现，不加=白干
        if(direc=='l') a=_crol_(a,1);
        else a=_cror_(a,1);
        delay(time);
    }
}
//灯从中间到两边k (扩)，从两边到中间s(缩);延时时间
void move_KuoSuo(char direc,uint time){
    void delay(uint x);
    void clear(uint time);
    int i;              //unsigned int 没负数，整到负数就会报错出bug
    uchar a[4]={0x18,0x24,0x42,0x81};//00011000 00100100 01000010 10000001
    if(direc=='k'){
        for(i=0;i<4;i++){
            P2=~a[i];
            delay(time);
        }
    }
    else if(direc=='s'){
        for(i=3;i>=0;i--){  //如果是i>=0就会出问题，灯乱闪，要一个一个debug才行，和取反~可能有关系
            P2=~a[i];
            delay(time);
        }
    }
    i=0;
    clear(2000);
}

void all_light_off(int n )
{ 
    void delay(uint x);
    void clear(uint time);
    int i;
    for (i=0; i<n; i++){
        P2=0x00;        //全部亮
        delay(200);
        clear(200);
    }
}

//第一个灯亮1次，第二个2次etc……，到第n个灯
void factorial_light(int n)
{
    void delay(uint x);
    void clear(uint time);
    uchar init=0x80;    //1000`0000
    int i;
    init=~init;
    for ( i = 1; i <= n; i++)
    {
        P2=init;
        delay(200);
        init=_cror_(init, i);
        clear(1);
    }
}

void jiange_light(int n)
{
    void delay(uint x);
    void clear(uint time);
    uchar light=0xaa;    //1010·1010 取反 01010101
    int i;
    light=~light;
    for ( i=1; i<=n; i++){  //要循环亮灭的次数
        P2=light;
        delay(200);
        P2=~light;
        delay(200);
    }
}

//Written in Hebeu Library , studying with KangKang.
void my_light(void)
{
    void MyHeart(int happyTimes);
    int youSeatBesideMe=1, happy=8, youLeave=1;
    while (youSeatBesideMe){
        MyHeart(happy);
        if (youLeave) break;
    }
}

void iWantToSpentYearsOfTimeWithYou(int years)
{
    int loveYouYear, yearOfSecond;
    yearOfSecond=365*24*60*60;
    for (loveYouYear=0; loveYouYear < years; loveYouYear++){
        delay(yearOfSecond);
    }
}

//n显示heart的次数,用8个led灯输出心形……效果和我想的不太一样啊
void MyHeart(int happyTimes)
{
    uchar heart[10]={
        0xff,   //1111`1111 先整两个测试一下,ok
        0x99,   //1001`1001
        0x66,   //0110`1110
        0x7e,   //0111`1110
        0xbd,   //1011`1101
        0xdb,   //1101`1011
        0xe7,   //1110`0111
        0xff,   //1111`1111
    };

    uchar *heartTimes=heart, *heartEnd=heart+happyTimes;

    for (; heartTimes < heartEnd; heartTimes++){
        P2=*heartTimes;
        delay(300);
    }
    iWantToSpentYearsOfTimeWithYou(10000);
}

uchar ll,rr;            //一定要在外部定义,不然在main()内定义int类会出错
int main()
{
    int end=100;
    int i;              //i不能在while循环里面定义，很奇怪，编译器可以能是极其古老的版本
    ll=0xfe;            //给管脚一起赋值，右边是0就是从左边开始亮……有点反人类
    rr=0x7f;
    while (end!=0)
    {
        //1
        move_direction('l',ll,200,8);
        clear(2000);
        //2
        move_direction('r',rr,200,8);
        clear(2000);
        //3
        move_direction('l',ll,200,8);
        move_direction('r',rr,200,8);
        clear(2000);
        //4
        for (i=1; i<=3; i++){
            move_KuoSuo('k',200);
        }
        clear(2000);
        //5
        for (i=1; i<=3; i++){
            move_KuoSuo('s',200);
        }
        clear(2000);
        //6
        all_light_off(3);
        move_direction('l',ll,200,8);
        clear(2000);
        //7
        factorial_light(4);
        clear(2000);
        //8
        jiange_light(3);
        clear(2000);
        //9-free-my_light暂停5s
        my_light();
        clear(2000);
        end--;
    }
    return 0;
}
/*  测试流水灯代码
    for(i=0;i<8;i++){
        P2=ll;
        ll=_crol_(ll,1);
        delay(200);
    }
*/