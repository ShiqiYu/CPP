#include <stdio.h>
int main()
{
    signed char a = 127;
    unsigned char b = 0x7f;
    char c = 0x7f;
    a=a<<1;
    b=b<<1;
    c=c<<1;
    printf("a=%x\nb=%x\nc=%x\n",a,b,c);
    printf("a=%d\nb=%d\nc=%d\n",a,b,c);
    a=a>>1;
    b=b>>1;
    c=c>>1;
    printf("a=%x\nb=%x\nc=%x\n",a,b,c);
    printf("a=%d\nb=%d\nc=%d\n",a,b,c);
    return 0;
}