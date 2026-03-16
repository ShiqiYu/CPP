#include <stdio.h>
int main()
{
    double a = 0.1;
    double b = 0.2;
    double c = 0.3;

    fprintf(stdout, "%.2f\n", a);
    fprintf(stdout, "%.2f\n", b);
    fprintf(stdout, "%.2f\n", c);
    return 0;
}