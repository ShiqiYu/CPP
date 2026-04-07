#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int numA = 0x11223344;
    
    char *pA = (char*)&numA;
    if (pA[0] == 0x44) {
        printf("System is Little-Endian (LE)\n");
    } else if (pA[0] == 0x11) {
        printf("System is Big-Endian (BE)\n");
    } else {
        printf("Unknown Endianness\n");
    }

    if(argc == 2){
        if(argv[1][0]=='H'){
            int *pnumB = (int*)malloc(sizeof(int));
            if(pnumB != NULL){
                char *pB = (char*)pnumB;
                for(int i = 0; i < sizeof(int); i++){
                    pB[i] = pA[sizeof(int) - 1 - i];
                }
                printf("Swapped value at Heap location: 0x%08X\n", *pnumB);
                
                free(pnumB);
                pnumB = NULL; 
            } 
        }
        else if(argv[1][0]=='S'){
            int numB;
            char *pB = (char*)&numB;
            for(int i = 0; i < sizeof(int); i++){
                pB[i] = pA[sizeof(int) - 1 - i];
            }
            printf("Swapped value at Stack location: 0x%08X\n", numB);
        } else {
            printf("Invalid argument. Please specify 'H' or 'S'.\n");
        }
    } else {
         printf("Usage: %s H|S\n", argv[0]);
    }
    
    return 0;
}
