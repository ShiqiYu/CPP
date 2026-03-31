#include <stdio.h>
union data
{
    int a;
    char c;
};
int main()
{
    union data endian;
    endian.a = 0x11223344;
    endian.c = 0x56;
    printf("size of endian: %ld\n", sizeof(endian));
    printf("size of endian.a: %ld,endian.a=0x%x\n", sizeof(endian.a), endian.a);
    printf("size of endian.c: %ld,endian.c=0x%x\n", sizeof(endian.c), endian.c);
    return 0;
}