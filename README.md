# Programming in C++ Efficiently

If you are a publisher and would like to publish the textbook worldwide, you can contact Prof. Shiqi Yu <yusq@sustech.edu.cn>.

Course 'CS205 C/C++ Program Design' in 2021 Fall at Southern University of Science and Technology.

## [Chapter 1: Getting Started](week01/README.md)

## [Chapter 2: Data Types and Arithmetic Operators](week02/README.md)

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
