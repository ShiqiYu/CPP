#include<stdio.h>
int main() 
{ 
    int numbers1[] = {2,4,6,8,10};
    int sum = 0;
    int *p1 = &numbers1[1];
    printf("numbers1 = %p\n", (void*)numbers1);
    printf("p1       = %p\n", (void*)p1);
    for(int i = 0; i < 3; i++) 
        sum += *(p1+i);
    printf("sum      = %d\n",sum);
    
    int numbers2[5]={1,2,3,4,5};
    int *p2 = (int*)(&numbers2 + 1);
    printf("numbers2     = %p\n", (void*)numbers2);
    printf("numbers2 + 4 = %p\n", (void*)(numbers2 + 4));
    printf("p2           = %p\n", (void*)p2);
    printf("*(numbers2+1)= %d\n",*(numbers2+1));
    printf("*(p2-1)       = %d\n",*(p2-1));
    return 0;
}
