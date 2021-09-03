#include <stdio.h>

int main()
{
    int i; //bad: uninitialized variable i
    int j; //bad: uninitialized variable j
    printf("i = %d, j = %d\n", i, j);
}
