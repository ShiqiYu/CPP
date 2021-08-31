# Programming in C++ Efficiently

Course 'CS205 C/C++ Program Design' in 2021 Fall at Southern University of Science and Technology.

## Chapter 1: Get Started

### The first example

A C++ example with C++20 standard

### What’s a programming language

Binary instruction - ASM - advanced programming language - (Java) - script programming language - scratch

### History of C and C++

Does we still need C and C++?

### A complete sample

* two cpp files, a header file are compiled together
* what’s a compiler
* what’s a linker
* the difference between compiled languages with script languages 
* how they work
* the speed

### More on C/C++ programming

* proprecessor
* function
* header 

### Lab: 

Compile with gcc
Install VS code and run the first example

## Chapter 2: Data types and Arithmetic Operators

### Integer numbers

* variables and their values
* overflow (be careful!)
* char and integer
* unicode(?)

### Floating point numbers

* binary format
* precision (32F and 64F), don’t f1==f2

### Arithmetic Operators 

* + - * / %
* Data type conversions (explicitly, implicitly) 
* auto in C++11 and later
* ++, - - , +=, -=, *=, /=, 

### Lab

* test integer range
* conversion between char and integer
* test float number precision

## Chapter 3: Loops and Branching Statements

### if-else if- else

### ? : operator

### for loop (break, continue)

### while loop (break, continue)

### switch case (break )

### goto

### Relational expressions

 <, <=, >, >=, ==, !=

### Logical expressions ( and, or, not), precedence

### bool and integers

### Lab
* a calculator? 
* Makefile (how to manage multiple source files using a Makefile)

## Chapter 4: Data Structures

### Arrays (be careful of out of range)

### Array-style strings

### Structures

### Unions

### Enumerations

### Lab: 

* create an array and the element is of a structure 
* cmake (automatically generate a Makefile according to the environment). 

## Chapter 5: Input and Output

### C style input and output

### C++ style input and output

### Lab:

* Read from a binary, and print out in tex format
* How to debug using VS Code.

## Chapter 6: Memory and Pointer

### Pointer 

### Allocate memory: C style

### Allocate memory: C++ style

### const variables 

`const int * p; int * const p;`

### Common mistakes of using a pointer

* null pointer, random pointer
* out of range
* memory leak

### Lab

* allocate memory for an array string, modify elements by integer values one by one, then print out the result as a string. Please try to modify the element out of range and see what will happen.

## Chapter 7: Basics of Functions

### Function arguments (pass by value)

### array and pointer arguments

### C style array strings

### struct arguments (copy data or address)

### Reference and const

### Lab:

* an example to test integer arguments, pointer argument and reference arguments

## Chapter 8: Advances in Functions

### inline function (why inline? Comparison with macro)

### Default arguments

### Function overloading

### Function templates

### Recursion 

### Pointer to functions

### Lab:

* implement a function with default arguments.
* overload a function which can compute the absolute value for an array, the array can be int, float and double 
`vabs(int * p, int n); //should n be int or size_t, what's the difference, please create an arrary with more than 2^31 elements` 
`vabs(float * p, int n);`
`vabs(float * p, int n);`

## Chapter 9: Speedup Your Program

### Compiler options (-O3 for GCC, -Wall, etc…)

### SIMD (SSE, AVX, NEON, RISC-V, Universal Intrinsics of OpenCV)

### OpenMP

### Memory Hierarchies and Speed

### Crop ROI from a 2D Matrix

### Intel, ARM and RISC-V Architechture 

### Lab:

Create two 1Mx1K float matrices matA and matB, compute matA + matB.

* compute the result row by row and col by col, compare the performance difference
* use -O3 to improve the speed
* improve the speed using SIMD, will the speed be improved? Why?


## Chapter 10: Basics of Classes

### Class Definition

* build-in types and user defined types
* data componient and method/functions

### Using a Class

* Access control: public and private
* Create an object and access members
* const member functions
* const member variables
* static member variables

### Constructors and Destructors

* Constructors
* Default Constructors
* Destructors
* Initialization

### this pointer

### Lab

Create a simple class. Please try to test:

* access a private member
* modify a const data member
* modify a data member in a const function
* initializate a const data member

## Chapter 11: Advances in Classes

### operator overloading

Constructor and assignment

```
Student s2=s1;
Student s3;
s3=s1;
```

### friend Functions

### << operator

### Automatic Conversions and Type Casts for Classes

### Lab

overload + and << for your own defined class

## Chapter 12: Dynamic Memory Management in Classes

### Some Default Operations

* Default constructor
* Copy constructor
* Assign operator
* Default destructor
* How pointer members work defaultly

### An Example with Dynamic Data Allocation

### Solution

### Matrix Data Management in OpenCV

### Lab

Create a class for matrices which elements are in float. The class should support the follow operations and has no memory management problem. When a matrix is assigned to another by =, the two matrices will share the same data.
`class Matrix{...};`
`Matrix a(3,4);`
`Matrix b(3,4);`
`Matrix c = a + b;`
`Matrix d = a * 2.0f;`

## Chapter 13: Class Inheritance

### Deriving a Class

* Constructor
* Destructor

### Static and Dynamic Binding

### Vitural Functions

### Access Control (protected)

### Dynamic Memory Management

### Lab

## Chapter 14: Class Templates and std Library

### Defining a Class Template

### Templates in OpenCV

### Templates in std

### Lab

Create a matrix template class which can handle different data types.

## Chapter 15: Exceptions

## Chapter 16: Friend Classes and Nested Classes
