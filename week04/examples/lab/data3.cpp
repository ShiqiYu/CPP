#include <stdio.h>
struct data
{
    int a;
    char c;
};
int main()
{
    struct data icx;
    icx.a = 0x11223344;
    icx.c = 0x56;
    printf("size of icx: %ld\n", sizeof(icx));
    printf("size of icx.a: %ld, icx.a=0x%x\n", sizeof(icx.a), icx.a);
    printf("size of icx.c: %ld, icx.c=0x%x\n", sizeof(icx.c), icx.c);
    return 0;
}