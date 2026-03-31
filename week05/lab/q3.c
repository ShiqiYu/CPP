#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    int numA = 0x11223344;
    unsigned char *cp = (unsigned char *)&numA;
    if (*cp == 0x44) {
        printf("Data A_addr: %p, A_data: 0x%08x, This is LE\n", &numA, numA);
    }else {
        printf("Data A_addr: %p, A_data: 0x%08x, This is BE\n", &numA, numA);
    }
    if (argc == 2)
    {
        if (argv[1][0] == 'H')
        {
            int *pnumB = (int *)malloc(sizeof(int));
            if (pnumB != NULL)
            { /*complete code here*/
                unsigned char *src = (unsigned char *)&numA;
                unsigned char *dst = (unsigned char *)pnumB;
                for (int i = 0; i < sizeof(int); i++) {
                    dst[i] = src[sizeof(int) - 1 - i];
                }
                printf("Data B_addr: %p, B_data: 0x%08x\n", pnumB, *pnumB);
                free(pnumB);
            }
        }
        else if (argv[1][0] == 'S')
        { /*complete code here*/
            int numB = 0;
            unsigned char *src = (unsigned char *)&numA;
            unsigned char *dst = (unsigned char *)&numB;
            for (int i = 0; i < sizeof(int); i++) {
                dst[i] = src[sizeof(int) - 1 - i];
            }
            printf("Data B_addr: %p, B_data: 0x%08x\n", &numB, numB);
        }
    }
    return 0;
}