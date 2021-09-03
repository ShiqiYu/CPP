# Chapter 1: Get Started

## The first example

Let us start from a very simple example. You can save the following source code into a CPP file named as `hello.cpp`. Then you can compile it into an executable program by the command: `g++ hello.cpp`. Since the source file is in C++11 standard and the default setting of the compiler `g++` may be lower than C++11, you may get an error message to compile that it cannot compile a C++11 source file by default. By adding the option `--std=c++11`, you should compile the source file successfully by `g++ hello.cpp --std=c++11`. The default file name for the output file will be `a.out`. You can find it in the working directory.

C and C++ are not fixed languages. They keep evolving in the past decades. It is impossible to convert all the details of all C and C++ standards here. Please remember that the features you use may be in different standards, and you can specify them by option `--std` to let the compiler to compile the source code in different standards.  

```C++
//C++ example in C++11
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    vector<string> msg {"Hello", "C++", "World", "!"};
    
    for (const string& word : msg)
    {
        cout << word << " ";
    }
    cout << endl;
}
```

To run the generated program `a.out`, you can simply to run `./a.out` in the command window. The output of the program will be
```
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

## A complete sample

* two cpp files, a header file are compiled together
* what’s a compiler
* what’s a linker
* the difference between compiled languages with script languages 
* how they work
* the speed

## More on C/C++ programming

* proprecessor
* function
* header 

## Lab: 

Compile with gcc
Install VS code and run the first example
