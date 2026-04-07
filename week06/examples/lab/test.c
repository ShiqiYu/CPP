#include <stdio.h>
#include "swap.h"

int main()
{
    int x = 10, y = 20;
    swap(&x, &y);
    printf("x = %d, y = %d\n", x, y);
     return 0;
}