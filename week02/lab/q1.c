#include <stdio.h>
int main()
{
    signed char a = 127; // 01111111
    unsigned char b = 0x7f; // 01111111
    char c = 0x7f; // 01111111
    a = a << 1; // 11111110
    b = b << 1;
    c = c << 1;
    printf("a=%x\nb=%x\nc=%x\n", a, b, c);
    printf("a=%d\nb=%d\nc=%d\n", a, b, c);
    a = a >> 1; // 11111111
    b = b >> 1; // 01111111
    c = c >> 1; // 11111111
    printf("a=%x\nb=%x\nc=%x\n", a, b, c);
    printf("a=%d\nb=%d\nc=%d\n", a, b, c);
    return 0;
}
/*
a=fffffffe
b=fe
c=fffffffe
a=-2
b=254
c=-2
a=ffffffff
b=7f
c=ffffffff
a=-1
b=127
c=-1
*/