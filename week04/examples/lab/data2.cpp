#include <stdio.h>
int main()
{
    char SC[] = "SUSTECH";
    char sc[] = {'s', 'u', 's', 't', 'e', 'c', 'h'};
    printf("size of SC: %ld bytes, sc: %ld\n", sizeof(SC), sizeof(sc));
    return 0;
}