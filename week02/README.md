# Chapter 2: Data Types and Arithmetic Operators

Since programming is to manipulate data, and C/C++ handle data more efficiently at a lower level than many other languages such as Java, Python. To make the programs robust needs the developers understand different data types and their behaviors in arithmetic expressions.

## Integer numbers

### Variable Declaration, Initialization and Assignment

There are several kinds of integer types, and `int` should be the most used one. Variables of `int` type can be declared as follows. Other types are the same.

```C++
int n; //declare a variable
```

This line is to declare and initialize a variable.

```C++
int n = 10; //declare and initialize
```

The following line looks very similar with the previous one. But the operations are different. There is not initialization in it. The first line is declaring a variable, and the second is to assign a value. Assignment is a different operation with initialization. The two pieces of source code are equivalent. They both declare a variable, and then the value is `10`. But if the data type is not a fundamental type (`int`, `float`, etc) and is a compound type (such as a `class` type), the two operations, initialization and assignment, may have different behaviors. You can get related information in the operator overloading part of this book.

```C++
int n; //declare a variable, its value may be a random one
n = 10; //assign (not initialize) a value to the variable
```

Variables can also be initialized in the following two manners. The second one is from a C++11 standard. It can only be compiled with the C++11 or a newer standard.

```C++
int n (10); //initialize 
```

```C++
int n {10}; //initialize, C++11 standard
```

### Uninitialized Variables

I must emphasis the danger of uninitialization here. If a variable is not initialized, the C/C++ compiler will not report an error, even a warning. The Java compilers will report an error for an uninitialized variable. C/C++ compilers will not do that as strictly as Java compilers. The values of uninitialized variables are also not well defined in C/C++ standards. You may get a random value from an uninitialized variable.

```C++
//init.cpp
#include <stdio.h>
int main()
{
    int i; //bad: uninitialized variable i
    int j; //bad: uninitialized variable j
    printf("i = %d, j = %d\n", i, j);
    return 0;
}
```

The example `init.cpp` has two uninitialized variables `i` and `j`. They are printed out immediately after their declarations. I tried the example on different platforms `x86_64` and `arm64`, and different results were given. Random values were given on `x86_64`, but zeros on `arm64`.

```bash
$ file a.out
a.out: Mach-O 64-bit executable x86_64
$ ./a.out  
i = 2, j = 13299749
```
```bash
$ file a.out 
a.out: Mach-O 64-bit executable arm64
$ ./a.out 
i = 0, j = 0
```

If you use some uninitialized variables, sometimes your program can work very well, such as the example on `arm64`. Sometime it cannot. If it is a huge program and works very well, but bugs appear when you port it to another platform. It will be your nightmare to debug a random error from a huge program. To avoid those situations, it is better to write each line of source code carefully.

### Overflow

C and C++ standards do not specify the width of `int`. It is 32-bit on most platforms, and `int` is equivalent to `signed int`. The range of `int` is [-2<sup>31</sup>, 2<sup>31</sup>-1]. The maximal value 2<sup>31</sup> (2,147,483,648) is not a great number which is hard to reach.

The example `overflow.cpp` multiply two integers which values are both `56789`. The product `c` should be `3,224,990,521`, but the program will print out `c = -1069976775`. It is a negative number, and surely it is wrong.

```C++
//overflow.cpp
#include <iostream>
using namespace std;

int main()
{
    int a = 56789;
    int b = 56789;
    int c = a * b;
    cout << "c = " << c << endl;
    return 0;
}
```

The compilation command and the output:

```bash
$ g++ overflow.cpp 
$ ./a.out 
c = -1069976775
```

The number 56789 is 0xDDD5 in hexadecimal format, and is a 16-bit length number. Their product is a 32-bit number 0xC0397339. The thirty second bit of it is 1. The result 0xC0397339 is copied into an `int` variable and its highest bit 1 is taken as the sign bit of the signed integer. That is the reason why the output is a negative number. If we use `unsigned int` for `c`. The result 0xC0397339 will be taken as an unsigned 32-bit integer. It will be the result that we expect.

```C++
int a = 56789;
int b = 56789;
unsigned int c = a * b; // the value of C will be a positive number 0xC0397339 (3224990521)
```

To expect an `int` variable to hold any integer numbers is unrealistic. Before you choose the data type for a variable, you must carefully consider its data range.


### Different Integer Types

The width in bits of `int` is not fixed in C and C++ standards. The standards just require `int` should have at least 16 bits. It is 32 bits on most modern platforms. Besides of `int`, there are `short int`, `long int` and `long long int` (`long long int` is in C++11). `short int` has 16 bits. `int` has 16 or 32 bits. `long int` has 32 or 64 bit. `long long int` has 64 bits.

`char` is also a frequently used integer type. Someone may be confused and think `char` is for characters only. Since characters are encoded into integer values, `char` indeed is an integer type and has 8 bits. `char` is wide enough for English characters, but not for Chinese, Japanese, Korean and some other characters. `char16_t` and `char32_t` have been introduced into C++11 for ranges of 16 bits and 32 bits respectively. 

The following three lines of source code are equivalent.

```C++
char c = 'C'; // its ASCII code is 80
```

```C++
char c = 80; // in decimal
```

```C++
char c = 0x50; // in hexadecimal
```

The 16-bit and 32-bit character type can be declared and initialized as follows.

```C++
char16_t c1 = u'于'; //C++11
char32_t c2 = U'于'; //C++11
```

The data width of different integers are listed in the following table. For more details please visit https://en.cppreference.com/w/cpp/language/types

| Integer type                    | Width in bits |
|---------------------------------|---------------|
| `char`                          | 8             |
| `short` (`short int`)           | 16            |
| `int`                           | 16 or 32      |
| `long` (`long int`)             | 32 or 64      |
| `long long` (`long long int`)   | 64            |

### Signed and Unsigned Integers

`signed` or `unsigned` can be used before the type names to indicate if the integer is a signed one or unsigned one. When the integer is a signed one, the keyword `signed` can be omitted. It means `int` is for `signed int`, and `short` is for `signed short`. But there is an exception. `char` is not always for `signed char`, and it is `unsigned char` on some platforms. I strongly suggest you alway to use `signed char` or `unsigned char`, and not use `char`.

If the integer is a signed one, the highest bit (the 32th bit for `int`) will be its sign bit. It is a negative number if the sign bit is 1, and a positive number if 0 as shown in the following figure.

![Illustration for 32-bit integers. The highest bit is the sign bit for `signed int`.](images/integer-sign-bit.png)

### Boolean Type

The boolean type in C++ (not in C) is `bool`, and its value can be `true` or `false`. The integer value of `true` is 1, and the value of `false` is 0. The width of `bool` is 1 byte, not 1 bit. It means that a `bool` variable consumes 1 byte for data, but only uses the lowest 1 bit.

Since `bool` indeed is a kind of integer in C/C++, `bool` can be converted to other kinds of integers.

```C++
bool b = true;
int i = b; // the value of i is 1.
```

Integers can also be converted to `bool`, and non-zero values will be converted to `true` as shown in the following source code. But I do not recommend to do so since it is misleading.

```C++
bool b = -256; // unrecommended conversion. the value of b is true
```

The following equivalent source code is easier to understand. The expression `(-256 != 0)` is to judge if `-256` is equal to `0`, and the result is `true` or `false`.

```C++
bool b = (-256 != 0); 
```

There is not a boolean type in C standard. Some old programs using `typedef` to create a customized boolean type.

```C++
typedef char bool;
#define true 1
#define false 0
```

If you program in pure C language and want to use `bool`, you can include a header file introduced in C99. It is a better choice than to define it using `typedef`.

```C++
#include <stdbool.h>
```

### `size_t` Type

Another frequently used integer type is `size_t`. It is the type of the result of `sizeof` operator. It can store the maximum size of a theoretically possible object of any type. Computer memory kept increasing in the past and will continue to increase in the future. We often need an integer variable to store the data size of a specific piece of memory. `unsigned int` is not enough since its maximum value is 2<sup>32</sup>, 4GB for memory. `malloc()` function which can allocates `size` bytes of memory takes a argument of type `size_t`. If its argument `size` is `int` type, its maximum memory is 2GB, and 4GB for `unsigned int`. 

```C++
void* malloc( size_t size );
```

The width of `size_t` depend on platforms, and is 64 bits for most modern platforms. Since it can store the maximum size of a theoretically possible object of any type, you can safely use for memory size.

### Fixed Width Integer Types

Different widths for the same integer type may cause the program difficult to port to different platforms. Some fixed width integer types are introduced in `<cstdint>` since C++11. They are `int8_t`, `uint8_t`, `int16_t`, `uint16_t`, `int32_t`, `uint32_t`, `int64_t`, `uint64_t`, etc. There are some useful macros such as `INT_MAX`, `INT_MIN`, `INT8_MAX`, `UINT8_MAX`, etc.  


## `sizeof` Operator

`sizeof` can yields the size in bytes of a type or an object/variable. Example `size.cpp` demonstrates how to use `sizeof` to get the width of different data types and variables. Not only the fundamental types, it can also take a compound type or any variables as its input.

```C++
//size.cpp
#include <iostream>
using namespace std;

int main()
{
    int i = 0;
    short s = 0;
    cout << "sizeof(int)=" << sizeof(int) << endl;
    cout << "sizeof(i)=" << sizeof(i) << endl;
    cout << "sizeof(short)=" << sizeof(s) << endl;
    cout << "sizeof(long)=" << sizeof(long) << endl;
    cout << "sizeof(size_t)=" << sizeof(size_t) << endl;

    return 0;
}
```

The output of the example on my computer is 

```bash
sizeof(int)=4
sizeof(i)=4
sizeof(short)=2
sizeof(long)=8
sizeof(size_t)=8
```

Someone may think `sizeof` is a function since its grammar looks like. But it is an operator, not a function. Functions cannot take a data type as an argument. `sizeof(int)` is to take type `int` as its input. 


## Floating-Point Numbers

Before introducing floating-point numbers, I would like to introduce the follow example `float.cpp`. `f1` is assigned `1.2`, and then is multiplied to `1000000000000000` (15 zeros). We may think `f2` should be `1200000000000000`. But if we print `f1` and `f2` with a very high precision, we will find a terrible truth. `f2` is not what we expected, and even `f1` is also not exactly equal to `1.2`.

```C++
//float.cpp
#include <iomanip>
using namespace std;
int main()
{
    float f1 = 1.2f;
    float f2 =  f1 * 1000000000000000;
    cout << std::fixed << std::setprecision(15) << f1 << endl;
    cout << std::fixed << std::setprecision(15) << f2 << endl;
    return 0;
}
```

The output is:

```bash
1.200000047683716
1200000038076416.000000000000000
```

We may think computers are always accurate. But it is not. In floating-point operations, computers always bring some tiny errors. Those errors cannot be eliminated. What we can do is to manage them not to cause a problem.


## Arithmetic Operators

- - - - / %
- Data type conversions (explicitly, implicitly)
- auto in C++11 and later
- ++, - - , +=, -=, \*=, /=,

## Lab

- test integer range
- conversion between char and integer
- test float number precision
