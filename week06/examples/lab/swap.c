#include "swap.h"

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}