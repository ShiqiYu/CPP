# Chapter 2: Data Types and Arithmetic Operators

Since programming is to manipulate data, and C/C++ handle data more efficiently at a lower level than many other languages such as Java, Python. To make the programs robust needs developers understand different data types and their behaviors in arithmetic expressions. Let us start from integers.

## Integer Numbers

### Variable Declaration, Initialization and Assignment

There are several kinds of integer types, and `int` should be the most commonly used one. Variables of `int` type can be declared as follows. Other types are similar.

```cpp
int n; //declare a variable
```

This line is to declare and initialize a variable.

```cpp
int n = 10; //declare and initialize
```

The following line looks very similar to the previous one. But the operations are different. But no initialization is in it. The first line is declaring a variable, and the second is assigning a value. Assignment is a different operation from initialization. The two pieces of source code are equivalent. They both declare a variable, and then its value is `10`. But if the data type is not a fundamental type (`int`, `float`, etc) and is a compound type (such as a `class` type), the two operations, initialization and assignment, may have different behaviors. The reason is that the operations in an initialization function may be different from those in an assignment function. You can get related information in the operator overloading part of this book.

```cpp
int n; //declare a variable, its value may be a random one
n = 10; //assign (not initialize) a value to the variable
```

Variables can also be initialized in the following two manners. The second one is from the C++11 standard. It can only be compiled with the C++11 standard or a newer standard.

```cpp
int n (10); //initialize 
```

```cpp
int n {10}; //initialize, C++11 standard
```

### Uninitialized Variables
It must be emphasized that the danger of uninitialization here. If a variable is not initialized, the C/C++ compiler will not report an error, even a warning. The Java compilers will report an error for an uninitialized variable. C/C++ compilers will not do that as strictly as a Java compiler. The values of uninitialized variables are also not well defined in C/C++ standards. You may get a random value from an uninitialized variable.

```cpp
//init.cpp
#include <iostream>
using namespace std;
int main()
{
    int num1; //bad: uninitialized variable
    int num2; //bad: uninitialized variable
    cout << "num1 = " << num1 << endl;
    cout << "num2 = " << num2 << endl;
}
```

The example `init.cpp` has two uninitialized variables `num1` and `num2`. They are printed out immediately after their declarations. I tried the example on my computer, and the output is as follows. If you run it on your computer, the output may be different. 

```console
num1 = 1
num2 = 74456160
```

Using uninitialized variables in your program can result in unpredictable behavior. While the program may appear to work well in some cases, it may also fail unexpectedly in others. If your program is large and appears to be working well, but problems arise when you migrate it to a different platform, debugging a random error from a large program can become a nightmare. To avoid such situations, it is important to write each line of code carefully and ensure that all variables are properly initialized.

### Overflow

C and C++ standards do not specify the width of `int`. It is 32-bit on most platforms, and `int` is equivalent to `signed int`. The range of `int` is [-2<sup>31</sup>, 2<sup>31</sup>-1]. The maximal value 2<sup>31</sup> (2,147,483,648) is not a great number that is hard to reach.

The example `overflow.cpp` multiply two integers, and their values are both `56789`. The product `c` should be `3,224,990,521`, but the program will print out `c = -1069976775`. It is a negative number, and surely it is wrong.

```cpp
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

```console
$ g++ overflow.cpp 
$ ./a.out 
c = -1069976775
```

The number `56789` is `0xDDD5` in hexadecimal format and is a 16-bit length number. Their product is a 32-bit number `0xC0397339`. The thirty-second bit of it is 1. The result `0xC0397339` is copied into an `int` variable and its highest bit 1 is taken as the sign bit of the signed integer. That is the reason why the output is a negative number. If we use `unsigned int` for the variable `c`. The result `0xC0397339` will be taken as an unsigned 32-bit integer. It will be the result that we expect.

```cpp
int a = 56789;
int b = 56789;
unsigned int c = a * b; // the value of C will be a positive number 0xC0397339 (3224990521)
```

To expect an `int` variable to hold any integer numbers is unrealistic. Before you choose the data type for a variable, you must carefully consider its data range.


## Different Integer Types

The width of `int` in bits is not fixed in C and C++ standards. The standards just require `int` should have at least 16 bits. It is 32 bits on most modern platforms. Besides of `int`, there are `short int`, `long int` and `long long int` (`long long int` is in C++11). `short int` has 16 bits. `int` has 16 or 32 bits. `long int` has 32 or 64 bits. `long long int` has 64 bits.

`char` is also a frequently used integer type. Someone may be confused and think `char` is for characters only. Since characters are encoded into integer values, `char` indeed is an integer type and has 8 bits. `char` is wide enough for English characters, but not for Chinese, Japanese, Korean and some other characters. `char16_t` and `char32_t` have been introduced into C++11 for ranges of 16 bits and 32 bits respectively. 

The following three lines of source code are equivalent.

```cpp
char c = 'C'; // its ASCII code is 80
```

```cpp
char c = 80; // in decimal
```

```cpp
char c = 0x50; // in hexadecimal
```

The 16-bit and 32-bit character types can be declared and initialized as follows.

```cpp
char16_t c1 = u'于'; //C++11
char32_t c2 = U'于'; //C++11
```

The data widths of different integers are listed in the following table. For more details please visit https://en.cppreference.com/w/cpp/language/types

| Integer type                    | Width in bits |
|---------------------------------|---------------|
| `char`                          | 8             |
| `short` (`short int`)           | 16            |
| `int`                           | 16 or 32      |
| `long` (`long int`)             | 32 or 64      |
| `long long` (`long long int`)   | 64            |

### Signed and Unsigned Integers

`signed` or `unsigned` can be used before the integer type names to indicate if the integer is a signed one or unsigned one. When the integer is a signed one, the keyword `signed` can be omitted. It means `int` is for `signed int`, and `short` is for `signed short`. But there is an exception. `char` is not always for `signed char`, and it is `unsigned char` on some platforms. I strongly suggest always using `signed char`` or `unsigned char`, and not using `char`.

If the integer is a signed one, the highest bit (the 32nd bit for `int`) will be its sign bit. It is a negative number if the sign bit is 1, and a positive number if it is 0. The signed int and unsigned int are shown in the following figure.

![Illustration for 32-bit integers. The highest bit is the sign bit for `signed int`.](images/integer-sign-bit.png)

### Boolean Type

The Boolean type in C++ (not in C) is `bool`, and its value can be `true` or `false`. The integer value of `true` is 1, and the value of `false` is 0. The width of `bool` is 1 byte, not 1 bit. It means that a `bool` variable consumes 1 byte for data, but only uses the lowest 1 bit.

Since `bool` indeed is a kind of integer in C/C++, `bool` can be converted to other kinds of integers.

```cpp
bool b = true;
int i = b; // the value of i is 1.
```

Integers can also be converted to `bool`, and non-zero values (even floating-point numbers) will be converted to `true` as shown in the following source code. But I do not recommend doing so since it is misleading.

```cpp
bool b = -256; // unrecommended conversion. the value of b is true
```

```cpp
bool b = (bool)0.4; // unrecommended conversion. the value of b is true
```

The following equivalent source code is easier to understand. The expression `(-256 != 0)` is to judge if `-256` is equal to `0`, and its result is `true` or `false`.

```cpp
bool b = (-256 != 0); 
```

There is not a Boolean type in the C standard. Some old programs may use `typedef` to create a customized Boolean type.

```cpp
typedef char bool;
#define true 1
#define false 0
```

If you program in pure C language and want to use `bool`, you can include a header file introduced in C99. It is a better choice than to define it using `typedef`. C had no `bool` before the C99 standard. C99 adds `_Bool` for the Boolean type. Additionally, `bool` is defined as an alias of `_Bool`, `true` is as `1`  and `false` is as `0` by macros in the header file `<stdbool.h>` which is also introduced by C99.

```cpp
#include <stdbool.h>
```

### `size_t` Type

Another frequently used integer type is `size_t`. It is the type of the `sizeof` operator. It can store the maximum size of a theoretically possible object of any type. Computer memory kept increasing in the past decades and will continue to increase in the future. We often need an integer variable to store the data size of a specific piece of memory. `unsigned int` is not enough since its maximum value is 2<sup>32</sup>, 4GB for memory. `malloc()` function which can allocates `size` bytes of memory takes an argument of type `size_t`. If its argument `size` is `int` type, its maximum memory is 2GB, and 4GB for `unsigned int`. 

```cpp
void* malloc( size_t size );
```

The width of `size_t` depends on the platforms. It is 64 bits for most modern platforms. Since it can store the maximum size of a theoretically possible object of any type, you can safely use it for memory sizes.

### `sizeof` Operator

`sizeof` can yield the size in bytes of a type or an object/variable. Example `size.cpp` demonstrates how to use `sizeof` to get the width of different data types and variables. Not only the fundamental types, it can also take a compound type or any variables as its input.

```cpp
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

```console
sizeof(int)=4
sizeof(i)=4
sizeof(short)=2
sizeof(long)=8
sizeof(size_t)=8
```

Someone may think `sizeof` is a function since its grammar looks like. But it is an operator, not a function. Functions cannot take a data type as an argument. `sizeof(int)` is to take type `int` as its input. To yield the width of an expression (or a variable), it can also be used as `sizeof expression`. But `sizeof type` cannot work. The following code shows how it works without parentheses.

```cpp
//size2.cpp
#include <iostream>
using namespace std;

int main()
{
    int i = 0;
    short s = 0;
    cout << "sizeof int =" << sizeof int  << endl; // error
    cout << "sizeof i =" << sizeof i  << endl; // okay
    cout << "sizeof short =" << sizeof s  << endl; // okay
    cout << "sizeof long =" << sizeof long  << endl; // error
    cout << "sizeof size_t =" << sizeof size_t  << endl; // error

    return 0;
}
```
### Fixed Width Integer Types

Different widths for the same integer type may cause the program difficult to port to different platforms. Some fixed width integer types are introduced in `<cstdint>` since C++11. They are `int8_t`, `uint8_t`, `int16_t`, `uint16_t`, `int32_t`, `uint32_t`, `int64_t`, `uint64_t`, etc. There are some useful macros such as `INT_MAX`, `INT_MIN`, `INT8_MAX`, `UINT8_MAX`, etc. Those integer types can explicitly declare the widths of variables. 

## Floating-Point Numbers

Before introducing floating-point numbers, I would like to introduce the following example `float.cpp`. `f1` is assigned `1.2`, and then is multiplied by `1000000000000000` (15 zeros). We may think `f2` should be `1200000000000000`. But if we print `f1` and `f2` with very high precision, we will find a terrible truth. `f2` is not what we expected, and even `f1` is also not exactly equal to `1.2`.

```cpp
//float.cpp
#include <iomanip>
using namespace std;
int main()
{
    float f1 = 1.2f;
    float f2 =  f1 * 1000000000000000;
    cout << std::fixed << std::setprecision(15) << f1 << endl;
    cout << std::fixed << std::setprecision(1) << f2 << endl;
    return 0;
}
```

The output is:

```console
1.200000047683716
1200000038076416.0
```

We may think computers are always accurate. But it is not. Floating-point operations always bring some tiny errors. Those errors cannot be eliminated. What we can do is manage them not to cause a problem.

Why cannot floating-point data be accurate? We can go deeper into the floating-point format. The following figure[^float_format] shows an example of a 32-bit floating-point number. There are 1 sign bit, 8 exponent bits and 23 fraction bits.  

![The illustration of a 32-bit floating-point number.](images/float_format.svg)

The value of a 32-bit floating-point number is $(-1)^{b_{31}} \times 2^{(b_{30}b_{29} \dots b_{23})_2 - 127} \times (1.b_{22}b_{21} \dots b_0)_2$. Its minimal normal is $\pm 1.175,494,3\times 10^{-38}$, and the maximal one is $\pm 3.402,823,4\times 10^{38}$. Since a 32-bit floating-point number has a much larger data range than a 32-bit integer, its precision is limited, even worse than a 32-bit integer sometimes. There are infinite numbers between 0 and 1.0. We cannot use a limited-length binary vector for infinite numbers. There are only limited numbers between 0 and 1.0 which be represented by floating-point numbers. The rest disappears in the space of a floating-point number. According to the floating-point equation, any combination of binary codes cannot represent an accurate `1.2`, and only an approximation `1.200000047683716` is in its space.

Since there are precision errors for floating-point numbers, using `==` to compare two floating-point numbers is a bad choice. If the difference between two numbers is less than a very small number, such as `FLT_EPSILON` or `DBL_EPSILON` for `float` and `double` respectively, we can think they are equal.

```cpp
if (f1 == f2)  //bad
{
    // ...
}

if (fabs(f1 - f2) < FLT_EPSILON) // good
{
    // ...
}
```

The following example `precision.cpp` demonstrates if a large number is added to a small one, the result will be the same as the large one. It is caused by the precision problem.

```cpp
//precision.cpp
#include <iostream>
using namespace std;

int main()
{
    float f1 = 23400000000;
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

```console
f1 = 23399999488.000000
f2 = 23399999488.000000
f1 - f2 = 0.000000
(f1 - f2 == 0) = 1
```

There are two typical floating-point types, `float` and `double`. They are for the single-precision floating-point numbers and double-precision numbers specifically. The former has 32 bits, and the latter has 64 bits. `double` has a wider range and a better precision than `float`. But `float` operations are normally much faster than `double` ones.

Please be careful with division operations, if the divisor is zero, the result may be `INF` or `NAN`. The example `nan.cpp` demonstrates how to produce invalid floating-point numbers.

```cpp
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

```console
inf
nan
```

## Constant Numbers and Constant Variables

Constant numbers can be in decimal, octal or hexadecimal. An integer number like `95` will be interpreted as an `int`. `95u` will be an `unsigned int`, and `95ul` will be an `unsigned long`. Floating-point numbers can be `3.141592` or `6.02e13`, but the two numbers are all in `double`. A postfix `f` is needed for `float` numbers, such as `6.02e13f`. Some more examples are listed as follows.

```cpp
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

```cpp
const float pi = 3.1415926f;
pi += 1; //error!
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
| bitwise OR    | `a \| b`  |
| bitwise XOR   | `a ^ b`  |
| bitwise left shift  | `a << b` |
| bitwise right shift | `a >> b` |

The operators and their operants can be connected together to create an expression. Some are simple ones such as `a + b`, and some may be long ones with multiple operators such as `a + b * c / (e + f)`. The expression can be assigned to a variable.

```cpp
int result = a + b * c / (e + f);
```

### Data Type Conversions

There are many data types in C and C++, but only four types are for arithmetic operations. They are `int`, `long`, `float` and `double`. If the operands are not the four types, they will be converted to one of the four implicitly. It can be explained by the following code. The types of `char1` and `char2` are all `unsigned char`, and their maximal values are `255`. If the operation of `char1 + char2` is in `unsigned char` type, the sum `256` will overflow since no `256` is in `unsigned char`. In the operation, `char1` and `char2` will be converted `int` implicitly first, then the two `int` values are added together. 

```cpp
unsigned char char1 = 255;
unsigned char char2 = 1;
int num = char1 + char2; // why num = 256?
```

The following piece of source code is equivalent to the previous one. 

```cpp
unsigned char char1 = 255;
unsigned char char2 = 1;
int num = (int)char1 + (int)char2; //convert to explicitly
```

In this example, `float` number `1.2f` will be converted to `double` first, and then the two numbers are added together. Their sum is `4.6` (not `4.6f`). The last step is to assign a `double` number `4.6` to an integer variable `num`. Compilers will give a warning message to indicate that the assignment may lose data.

```cpp
int num = 1.2f + 3.4; // -> 1.2 + 3.4 -> 4.6 -> 4
```

The equivalent code is as follows, and compilers will not give warning messages since you convert the result to `int` explicitly. Compilers will think you know clearly what you do. Explicit type conversions are recommended in most cases.

```cpp
int num = (int)((double)1.2f + 3.4); 
```

The programmers should be very careful with data type conversions because it will cause data loss. The typical one is that `(int)3.6` will be an integer `3`. The fractional part of a floating point number will be lost.

The following code may also be easy to mislead us. Since `17` and `5` are all `int`, so the operation is an `int` division, not a `float` division. The result of the expression `17 / 5` is an integer `3`, not a floating-point `3.4f`. That's the reason why `float_num` is `3.0f`, not `3.4f`.

```cpp
float float_num = 17 / 5; // f = 3.0f, not 3.4f.
```

When we convert numbers according to the direction from `char` -> `short` -> `int` -> `long` -> `float` -> `double` -> `long double`, normally there is not data loss. But if the conversion is in the opposite direction from `long double` to `char`, it will cause data loss and compilers will warn you most of the time. But it is not always true. Some big integer numbers in `int` may loss precision when they are converted to `float` as shown in the following code.

```cpp
int num_int1 = 100000004;
float num_float = num_int1;
int num_int2 = num_float; // num_int2 = 100000000
```

### `auto` Type

The placeholder type specifier `auto` is introduced in C++11. The real type of a variable with `auto` is deduced by its initializer. We can declare and initialize some variables as follows.

```cpp
auto a = 2; // type of a is int
auto bc = 2.3; // type of b is double
auto c; //valid in C, but not in C++
auto d = a * 1.2; // type of d is double
```

Once the type of an `auto` variable is deduced, its type will be fixed and not change again. In the following source code, `a` is initialized as an `int` type and then assigned a double `2.3`. `2.3` will be converted to an `int` value `2` implicitly first, and then assigned to the variable `a`. So the value of `a` should be `2`, not `2.3` since `a` is in type `int`. Please be careful with the real data type by `auto`.

```cpp
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
| `a \|= b`  | `a = a \| b`  |
| `a ^= b`  | `a = a ^ b`  |
| `a <<= b` | `a = a << b` |
| `a >>= b` | `a = a >> b` |

## Special Notes

In programming of C or C++, the developers are expected to understand all the details of different data types. Different from Python, the values in a variable can increase even out of the boundary of `int32`, the real storage for variables will adapt automatically. In Java, more warnings and errors will be given to prevent you from overflowing or precision problems. But in C or C++, there are much less warnings. You have to be very careful with different data types since your program will be wrong even no compilation errors. 

Besides, we also need to change the idea that computers are accurate. If the computation is carried out with floating-point numbers, there must be some tiny errors. We should realize that tiny errors are always there. What we can do is just to control the errors since they are difficult to eliminate.

To repeat, the numbers may be out of range, the computation may have errors, the results may be integer division, not floating-point division, etc. Please try to explore all possibilities and how the instructions work when you write a line of source code. More thinking and deeper understanding, fewer bugs.

## Exercises

Compile and run the following source code. Is the output exactly match what you expect? If not, explain why?
```cpp
#include <iostream>

using std::cout;
using std::endl;

int main() {
    int num1 = 1234567890;
    int num2 = 1234567890;
    int sum = num1 + num2;
    cout << "sum = " << sum << endl;

    float f1 = 1234567890.0f;
    float f2 = 1.0f;
    float fsum = f1 + f2;
    cout << "fsum = " << fsum << endl;
    cout << "(fsum == f1) is " << (fsum == f1) << endl;

    float f = 0.1f;
    float sum10x = f + f + f + f + f + f + f + f + f + f;
    float mul10x = f * 10;

    cout<<"sum10x = "<< sum10x << endl;
    cout<<"mul10x = "<< mul10x << endl;
    cout<<"(sum10x == 1) is "<< (sum10x == 1.0) << endl;
    cout<<"(mul10x == 1) is "<< (mul10x == 1.0) << endl;
    return 0;
}
```
[^float_format]: https://en.wikipedia.org/wiki/Single-precision_floating-point_format
