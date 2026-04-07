#include <iostream>
using namespace std;
int main()
{
    int matrix[][4] = {1,3,5,7,9,11,13,15,17,19}; 
    int *p = *(matrix + 1);
    p += 3;
    cout << "*p++ = " << *p++ << endl; 
    
    // Part 2: String and pointer casting
    const char *str = "Welcome to programming." ;
    long *q = (long *)str;
    q++;
    char *r = (char *)q;
    cout << r << endl;
    
    // Part 3: Endianness and pointer casting
    unsigned int num = 0x3E56AF67 ;
    unsigned short *pshort = (unsigned short *) &num;
    cout << "*pshort = 0x" <<  hex << *pshort << endl;
    
    return 0;
}
