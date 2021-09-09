# Chapter 1: Getting Started

## The first example

Let us start from a very simple example. You can save the following source code into a CPP file named as `hello.cpp`. Then you can compile it into an executable program by the command: `g++ hello.cpp`. Since the source file is in C++11 standard and the default setting of the compiler `g++` may be lower than C++11, you may get an error message to compile that it cannot compile a C++11 source file by default. By adding the option `--std=c++11`, you should compile the source file successfully by `g++ hello.cpp --std=c++11`. The default file name for the output file will be `a.out`. You can find it in the working directory.

C and C++ are not fixed languages. They keep evolving in the past decades. It is impossible to convert all the details of all C and C++ standards here. Please remember that the features you use may be in different standards, and you can specify them by option `--std` to let the compiler to compile the source code in different standards.  

```C++
//hello.cpp
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    vector<string> msg {"Hello", "C++", "World", "!"};
    
    for (const string& word : msg) //C++11 standard
    {
        cout << word << " ";
    }
    cout << endl;
}
```

To run the generated program `a.out`, you can simply to run `./a.out` in the command window. The output of the program will be
```bash
$ ./a.out 
Hello C++ World ! 
```

You can specify the output file name by an option `-o`. If you compile the source with `g++ hello.cpp --std=c++11 -o hello`, the output file will be `hello` nor `a.out`.

If you are using Linux or MacOS, you can easily compile source files using `g++` or `gcc` after you install them. If you are using Windows, you can install Windows Subsystem for Linux (WSL). Then you can have a Linux environment in your Windows, and you can use `g++`, `gcc` and some other similar tools.

## Different Programming Languages

### Binary Instructions

There are some different instruction set architectures (ISA). The instructions are in binary and executed by CPUs. A binary instruction can be like `1011000001100001`. Different ISAs are not compatible with each other. Some programs were recorded as the binary instructions on punched tapes as shown in the following figure. Anyway it is almost impossible to program some complex software from binary instructions.

![Five- and eight-hole punched paper tape](https://upload.wikimedia.org/wikipedia/commons/thumb/0/00/PaperTapes-5and8Hole.jpg/640px-PaperTapes-5and8Hole.jpg)

### Assembly Languages

Compared with binary instructions, an assembly language (ASM) is more human readable even it still a low-level programming language. The ASM instruction `MOV AL, 61h` means to load number 97 (61 in hexadecimal) into register AL. There is a strong correspondance between the ASM instructions and the the CPU code instructions. So you can regard ASM is just a human readable machine instructions, and can only compile and run on a specific CPU architecture. Nowadays, few programmers use assembly languages. Assembly languages are only used for hardware drivers, low level part of an operating system, real-time systems and some others.

![Sample assembly language source code](https://upload.wikimedia.org/wikipedia/commons/thumb/f/f3/Motorola_6800_Assembly_Language.png/377px-Motorola_6800_Assembly_Language.png)

### High-level Languages

C, C++, Java, Python, SQL and most programming languages we use nowadays are all high-level languages. Some programmers who are only familiar with some scripting languages such as Python may think C and C++ are difficult and are low-level languages. You can think C and C++ are lower than scripting languages, but they are not low-level languages. C and C++ are user-friendly, written in simple English words and can be compiled on different platforms.

### Scripting Languages

Many scripting languages such as Python are very popular for their simple syntax. Scripting languages are usually interpreted and not compiled. It is the interpreter to run and act by following the commands in a scripting languages. For a compiled language, the compiler will generate an executable file from the source code. Then the generated file is executed, nor the compile to be executed. Scripting languages normally have much lower efficiency than compiled languages. Someone may argue that Python can run very efficiently and even be for deep learning. The truth is that Python heavily depends on various modules which are written in C or C++ for the efficiency.

Java is an exception. It tres to take the advantages of scripting languages and compiled languages. Java is compiled into bytecode, but executed on the Java Virtual Machine (JVM) nor the operating system directly. Actually some other scripting languages have also take similar strategies to speedup the their execution. Sometime the boundary between scripting languages and compiled languages is not so clear.

### Visual Languages

A visual programming language can let the users manipulate some graphical elements to create programs. This kind of languages is very friendly to users especially users not computer experts. Scratch is a successful visual language for kids to learn programming.

![Scratch programming GUI](https://upload.wikimedia.org/wikipedia/commons/thumb/e/e3/Scratch_3.0_GUI.png/640px-Scratch_3.0_GUI.png)

### Why We Still Need C and C++

C and C++ are not easy languages. The program developed by beginners tends to crash. Beginners are prone to frustration at the beginning of learning C or C++. This book tries to reduce it and makes a smooth start. It will be easier if the learner has a better understanding on computer architectures.

Even we have many 'easy' languages, C and C++ are still important languages, and there is no good substitution for their tasks. Most fundamental software is developed by C or C++. Linux, Windows and most OS are written in C. The software by C or C++ can be a very long list, Apache web server,  Oracle, MySQL, Adobe Photoshop, Google Chrome, Microsoft Office, OpenCV, gcc compiler, ... If you care about efficiency, C or C++ may be your best choice, sometimes your only choice. C and C++ are must learn languages for the students in computer science.

## Compile and Link

Now we have a longer example. In the example, function `main()` calls function `mul()`, and `mul()` can return the product argument `a` and argument `b` by multiplying them.

```C++
//mainmul.cpp
#include <iostream>

using namespace std;

int mul(int a, int b)
{
    return a * b;
}
int main()
{
    int a, b;
    int result;

    cout << "Pick two integers:";
    cin >> a;
    cin >> b;

    result = mul(a, b);

    cout << "The result is " << result << endl;
    return 0;
}
```

Since the file name of the source file is `mainmul.cpp`, we can compile it using `g++ mainmul.cpp -o mainmul` and generate an executable file `mainmul`. If the source code is long, we can put all source code into one file. But it is not convenient to manage the source file. To better manage the source code, we can put the source code into different files according to their functions. Such as we can put function `main()` into file `main.cpp`, and `mul()` into `mul.cpp`. Then they can be like the following.

```C++
//main.cpp
#include <iostream>
#include "mul.hpp"

using namespace std;
int main()
{
    int a, b;
    int result;

    cout << "Pick two integers:";
    cin >> a;
    cin >> b;

    result = mul(a, b);

    cout << "The result is " << result << endl;
    return 0;
}
```

```C++
//mul.hpp
#pragma once
int mul(int a, int b);
```

```C++
//mul.cpp
#include "mul.hpp"

int mul(int a, int b)
{
    return a * b;
}
```

Then we can compile the two source files by `g++ -c main.cpp` and `g++ -c mul.cpp` specifically. The object files `main.o` and `mul.o` will be generated. Then we can link the two object files into an executable file by `g++ main.o mul.o -o mul`. Here the option `-c` is to tell the compiler `g++` to compile the source file only. To compile and link multiple files together, you can simply use `g++ main.cpp mul.cpp -o mul`. But if you have many files in your project, it may take very long time to compile all files. It is better to compile the changed files only. If you do not want to type the commands one by one, you can use a `Makefile` to save the rules for compilation and link and then a command `make` can help you do everything.

You may notice that we have three files here. `*.c` and `*.cpp` files are source files. `*.h` and `*hpp` are header files. We normally use a header file to store the declarations of functions. A function declaration introduces the function name and its type (arguments). If there is not a header file, the compiler will do not know what `mul` is when we compile `main.cpp`, and it will pop error message like the following. `mul` is an undeclared identifier, and the compiler does not know how to handle it.

```bash
$ g++ -c main.cpp
main.cpp:14:14: error: use of undeclared identifier 'mul'
    result = mul(a, b);
             ^
1 error generated.
```

`#include` macro is to insert the contents in `mul.hpp` into `main.cpp`. Then the source file after preprocessing will be like the following. Even the compile cannot find the body (definition) of function `mul()`, it will know its interface. How it takes arguments and what type will be returned. A linker will find the body of function `mul.o` and link the two object files together and generate an executable file.
```C++
#include <iostream>
int mul(int a, int b); //#include "mul.hpp" is replaced by the contents in mul.hpp

using namespace std;
int main()
{
    int a, b;
    int result;

    cout << "Pick two integers:";
    cin >> a;
    cin >> b;

    result = mul(a, b);

    cout << "The result is " << result << endl;
    return 0;
}
```

## Different Errors

### Compilation Errors

### Link Errors

### Runtime Errors

## Preprocessor

Compilation is briefly introduced in the previous part. There are several steps to the compilation before a compiler really compiles the source code. The previous step before the compilation is preprocessing.

Preprocessing directives begin with a `#` character, and each directive occupies one line. The most commonly used preprocessing directives are `include`, `define`, `undef`, `if`, `ifdef`, `ifndef`, `else`, `elif`, `endif`, `line`, `error` and `pragma`. `include` is just introduced, and it appears in almost all source files.

`define` is another popular directive, and can be used to define some macros. In the following source code we define `PI` as `3.14` by using `#define PI 3.14`.

```C++
#define PI 3.14
double len(double r)
{
    return 2.0 * PI * r;
}
```

After preprocessing, the source code will be as the following. `PI` has been replaced with `3.14`. Then it will be sent to a compiler. Macro `PI` is not a variable. The preprocessing for macros is like text replacement.

```C++
double len(double r)
{
    return 2.0 * 3.14 * r;
}
```

Since macros behaviors like text replacement, sometimes it is dangerous and cause bugs. If we define `PI` as `2.14+1.0`, the statement is grammatically correct.

```C++
#define PI 2.14+1.0
double len(double r)
{
    return 2.0 * PI * r;
}
```

But after preprocessing the return value of the function will be `4.28+r`, nor `2.0*3.14*r`. It may be not what you expected. Anyway the source code will be compiled successfully, and the compiler will not report any warning and error. You should be very careful when you use macros. 

```C++
double len(double r)
{
    return 2.0 * 2.14+1.0 * r; //= 4.28 + r
}
```

We can even define a macro which works like a function. Sometimes macros can achieve better efficiency than functions since macros have no overhead of function callings.

```C+++
#define MAX(a,b) (((a)>(b))?(a):(b))

int main()
{
    //...
    float a = 2.0f;
    float b = 3.0f;
    float m;
    m = MAX(a, b);
    //...
}
```

## Command Line Arguments

We can pass some values to our programs through the command line. The command we use previously `g++ hello.cpp -o hello` send three command line arguments `hello.cpp`, `-o` and `hello` to the compiler `g++`. 

The command line arguments can be handled using `main()` arguments. The function argument `argc` refers to the number of the command arguments, and `argv[]` is a pointer array. Each element in `argv[]` points to a `char` array string.

```C++
//argument.cpp
#include <iostream>

using namespace std;
int main(int argc, char * argv[])
{
    for (int i = 0; i < argc; i++)
        cout << i << ": " << argv[i] << endl;
}
```

When the program from the above code is executed with some arguments, it will print the arguments one by one with their indices.

```bash
$ ./argument hello.cpp -o hello
0: ./argument
1: hello.cpp
2: -o
3: hello
```

## Exercises 
