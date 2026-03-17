#include <stdio.h>

int main() {
    float a = 0.1f, b = 0.2f, c = 0.3f;
    fprintf(stdout, "%0.2f\n", a);
    fprintf(stdout, "%0.2f\n", b);
    fprintf(stdout, "%0.2f\n", c);
    return 0;
}