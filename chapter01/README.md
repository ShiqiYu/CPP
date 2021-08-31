# Chapter 1: Get Started

## The first example

Let us start from a very simple example. You can save the following source code into a CPP file named as `hello.cpp`. Then you can compile it into an executable program by the command: `g++ hello.cpp`. Since the source file is in C++11 standard and the default setting of the compiler `g++` may be lower than C++11, you may get an error message to compile that it cannot compile a C++11 source file by default. You should compile the source file successfully by command `g++ hello.cpp --std=c++11`. The default file name for the output file will be `a.out`. You can find it in the working directory.

C and C++ are not fixed languages. They keep evolving in the past decades. It is impossible to conver all the details of all C and C++ standards here. Please remember that the features you use may be in different standards, and you can specify them by option `--std`. 

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

If you are using Linux or MacOS, you can easily compile source files using `g++` or `gcc` if you have installed them. If you are using Windows, you can install Windows Subsystem for Linux (WSL). Then you can have a Linux environment in your Windows, and you can use `g++`, `gcc` and some other similar tools.


## A very brief history of programming languages

Binary instruction - ASM - advanced programming language - (Java) - script programming language - scratch

## History of C and C++

Does we still need C and C++?

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
