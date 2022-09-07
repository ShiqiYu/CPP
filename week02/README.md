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

The number `56789` is `0xDDD5` in hexadecimal format, and is a 16-bit length number. Their product is a 32-bit number `0xC0397339`. The thirty second bit of it is 1. The result `0xC0397339` is copied into an `int` variable and its highest bit 1 is taken as the sign bit of the signed integer. That is the reason why the output is a negative number. If we use `unsigned int` for `c`. The result `0xC0397339` will be taken as an unsigned 32-bit integer. It will be the result that we expect.

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

We may think computers are always accurate. But it is not. Floating-point operations always bring some tiny errors. Those errors cannot be eliminated. What we can do is to manage them not to cause a problem.

Why floating-point data cannot so accurate? We can go deeper into the floating-point format. The following figure[^float_format] shows an example of a 32-bit floating-point number. There are 1 sign bit, 8 exponent bits and 23 fraction bits.  

![The illustration of a 32-bit floating-point number.](images/float_format.svg)

The value of a 32-bit floating-point number is $(-1)^{b_{31}} \times 2^{(b_{30}b_{29} \dots b_{23})_2 - 127} \times (1.b_{22}b_{21} \dots b_0)_2$. Its minimal normal is $\pm 1.175,494,3\times 10^{-38}$, and the maximal one is $\pm 3.402,823,4\times 10^{38}$. Since a 32-bit floating-point number has much larger data range than a 32-bit integer, its precision is limited, even worse than a 32-bit integer sometimes. There are infinite numbers between 0 and 1.0. We cannot use a limited length binary vector for infinite numbers. There are only limited numbers between 0 and 1.0 can be represented by a floating-point numbers. The rest cannot and they disappear in the space of a floating-point number. According to the floating-point equation, any combination of 32 zeros and ones cannot represent an accurate `1.2`, and only an approximation `1.200000047683716` is in its space.

Since there are precision errors for floating-point numbers, using `==` to compare two floating-point numbers is a bad choice. If the difference between two numbers is less than a very small number, such as `FLT_EPSILON` or `DBL_EPSILON` for `float` and `double` respectively, we can think they are equal.

```C++
if (f1 == f2)  //bad
{
    // ...
}

if (fabs(f1 - f2) < FLT_EPSILON) // good
{
    // ...
}
```

The following example `precision.cpp` demonstrates a large number add a small one, the result will be the same with the large one. It is also caused by the precision errors.

```C++
//precision.cpp
#include <iostream>
using namespace std;

int main()
{
    float f1 = 2.34E+10f;
    float f2 = f1 + 10;

    cout.setf(ios_base::fixed, ios_base::floatfield); // fixed-point
    cout << "f1 = " << f1 << endl;
    cout << "f2 = " << f2 << endl;
    cout << "f1 - f2 = " << f1 - f2 << endl;
    cout << "(f1 - f2 == 0) = " << (f1 - f2 == 0) << endl;
    return 0;
}
```

The output:

```bash
f1 = 23399999488.000000
f2 = 23399999488.000000
f1 - f2 = 0.000000
(f1 - f2 == 0) = 1
```

There are two typical floating-point types, `float` and `double`. They are for the single-precision floating point numbers and double-precision numbers. The former one has 32 bits, and the later has 64 bits. `double` has a wider range and a best precision than `float`. But `float` operations are normally much faster than `double` ones.

Please be careful with division operations, if the divisor is 0, the result may be `INF` or `NAN`. The example `nan.cpp` demonstrates how to produce invalid floating-point numbers.

```C++
//nan.cpp
#include <iostream>
using namespace std;

int main()
{
    float f1 = 2.0f / 0.0f;
    float f2 = 0.0f / 0.0f;
    cout << f1 << endl;
    cout << f2 << endl;
    return 0;
}
```

Output:

```bash
inf
nan
```

## Constant Numbers and Constant Variables

```C++
95 // decimal 
0137// octal 
0x5F // hexadecimal 

95 // int 
95u // unsigned int 
95l // long 
95ul // unsigned long 
95lu // unsigned long 

3.14159 // 3.14159
6.02e13 // 6.02 x 10^13 
1.6e-9 // 1.6 x 10^-9 
3.0 // 3.0 

6.02e13f // float 
6.02e13 // double
6.02e13L // long double 
```

If a variable/object is const-qualified, it cannot be modified. It must be initialized when you define it.

```C++
const float PI = 3.1415926f;
PI += 1; //error!
```


## Arithmetic Operators


The arithmetric operators are listed in the following table. 

| Operator name | Syntax |
|---------------|--------|
| unary plus    | `+a`     |
| unary minus   | `-a`     |
| addition      | `a + b`  |
| subtraction   | `a - b`  |
| multiplication| `a * b`  |
| division      | `a / b`  |
| modulo        | `a % b`  |
| bitwise NOT   | `~a`     |
| bitwise AND   | `a & b`  |
| bitwise OR    | `a | b`  |
| bitwise XOR   | `a ^ b`  |
| bitwise left shift  | `a << b` |
| bitwise right shift | `a >> b` |

The operators and their operants can connected together to create an expression. Some are simple ones such as `a + b`, and some may be a long one with multiple operators such as `a + b * c / (e + f)`. The expression can be assigned to a variable.

```C++
int result = a + b * c / (e + f);
```

### Data Type Conversions

There are many data types in C and C++, but only four types are for arithmetic operations. They are `int`, `long`, `float` and `double`. If the operands are not the four types, they will be converted to one of the four implicitly. It can be explained by the following code. The types of `char1` and `char2` are all `unsigned char`, and their maximal values are `255`. If the operation of `char1 + char2` is in `unsigned char` type, the sum `256` will overflow since there is not `256` in `unsigned char`. In the operation, `char1` and `char2` will be converted `int` implicitly first, then the two `int` values are added together. 

```C++
unsigned char char1 = 255;
unsigned char char2 = 1;
int num = char1 + char2; // why num = 256?
```

The following piece of source code is equivalent to the previous one. 

```C++
unsigned char char1 = 255;
unsigned char char2 = 1;
int num = (int)char1 + (int)char2; //convert to explicitly
```

In this example, `float` number `1.2f` will be converted to `double` first, and then the two numbers are added together. Their sum is `4.6` (not `4.6f`). The last step is to assign a `double` number `4.6` to an integer variable `num`. Compilers will give a warning message to indicate that the assignment will loss data.

```C++
int num = 1.2f + 3.4; // -> 1.2 + 3.4 -> 4.6 -> 4
```

The equivalent code is as follows, and compilers will not give warning messages since you convert the result to `int` explicitly. Compilers will think you know clearly what you do. Explicit type conversions are recommended in most cases.

```C++
int num = (int)((double)1.2f + 3.4); 
```

The programmers should be very careful with data type conversions because it will cause data loss. The typical one is that `(int)3.6` will be an integer `3`. The fractional part of a floating point number will be lost.

The following code may also be easy to mislead us. Since `17` and `5` are all `int`, so the operation is an `int` addition, not a `float` addition. The result of the expression `17 / 5` is an integer `3`, not a floating-point `3.4f`. That's the reason why `float_num` is `3.0f`, not `3.4f`.

```C++
float float_num = 17 / 5; // f = 3.0f, not 3.4f.
```

When we convert numbers according to the direction from `char` -> `short` -> `int` -> `long` -> `float` -> `double` -> `long double`, normally there is not data loss. But if the conversion is in the opposite direction from `long double` to `char`, it will cause data loss and compilers will warning you most of the time. It is not alway true. Some big integer numbers in `int` may loss precision when they are converted to `float` as shown in the following code.

```C++
int num_int1 = 2059198192;
float num_float = num_int1;
int num_int2 = num_float; // num_int2 = 2059198208
```

### `auto` Type

The placeholder type specifier `auto` is introduced in C++11. The real type of a variable with `auto` is deduced by from its initializer. We can declare and initialize some variables as follows.

```C++
auto a = 2; // type of a is int
auto bc = 2.3; // type of b is double
auto c; //valid in C, but not in C++
auto d = a * 1.2; // type of d is double
```

Once the type of an `auto` variable is deduced, its type will be fixed and not change again. In the following source code, `a` is initialized as an `int` type, and then assigned a double `2.3`. `2.3` will be converted to a `int` value `2` implicitly first, and then assigned to the variable `a`. So the value of `a` should be `2`, not `2.3` since `a` is in type `int`.

```C++
auto a = 2; // type of a is int
a = 2.3; // Will a be converted to a double type variable? NO!
```

### Assignment Operators

Besides of `=`, there are some compound-assignment operators as shown in the following table. They are convenient when we change the lvalue of an operator.

| Assignment expression| Equivalent expression|
|-----------|--------------|
| `a = b`   |              |
| `a += b`  | `a = a + b`  |
| `a -= b`  | `a = a - b`  |
| `a *= b`  | `a = a * b`  |
| `a /= b`  | `a = a / b`  |
| `a %= b`  | `a = a % b`  |
| `a &= b`  | `a = a & b`  |
| `a |= b`  | `a = a | b`  |
| `a ^= b`  | `a = a ^ b`  |
| `a <<= b` | `a = a << b` |
| `a >>= b` | `a = a >> b` |

## Exercises

- test integer range
- conversion between char and integer
- test float number precision

[^float_format]: https://en.wikipedia.org/wiki/Single-precision_floating-point_format