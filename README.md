# Programming in C/C++ Efficiently

Course 'CS205 C/C++ Program Design' in 2021 Fall at Southern University of Science and Technology. The lecture videos can be found at https://www.bilibili.com/video/BV1Vf4y1P7pq

## [Chapter 1: Getting Started](week01/README.md) 

* [Lecture notes](week01/Lecture01.pptx)
* [Lab notes](week01/Lab01.pptx)
* [Examples](week01/examples)

## [Chapter 2: Data Types and Arithmetic Operators](week02/README.md)

* [Lecture notes](week02/Lecture02.pptx)
* [Lab notes](week02/Lab02.pptx)
* [Examples](week02/examples)

## [Chapter 3: Loops and Branching Statements](week03/README.md)

* [Lecture notes](week03/Lecture03.pptx)
* [Lab notes](week03/Lab03.pptx)
* [Examples](week03/examples)

## [Chapter 4: Data Structures](week04/README.md)

* [Lecture notes](week04/Lecture04.pptx)
* [Lab notes](week04/Lab04.pptx)
* [Examples](week04/examples)

## [Chapter 5: Memory and Pointer](week05/README.md)

* [Lecture notes](week05/Lecture05.pptx)
* [Lab notes](week05/Lab05.pptx)
* [Examples](week05/examples)

## Chapter 6: Basics of Functions

### Function arguments (pass by value)

### array and pointer arguments

### C style array strings

### struct arguments (copy data or address)

### Reference and const

### Lab:

* an example to test integer arguments, pointer argument and reference arguments

## Chapter 7: Advances in Functions

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

## Chapter 8: Speedup Your Program

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


## Chapter 9: Basics of Classes

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

## Chapter 10: Advances in Classes

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

## Chapter 11: Dynamic Memory Management in Classes

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

## Chapter 12: Class Inheritance

### Deriving a Class

* Constructor
* Destructor

### Static and Dynamic Binding

### Vitural Functions

### Access Control (protected)

### Dynamic Memory Management

### Lab

## Chapter 13: Class Templates and std Library

### Defining a Class Template

### Templates in OpenCV

### Templates in std

### Lab

Create a matrix template class which can handle different data types.

## Chapter 14: Exceptions

## Chapter 15: Friend Classes and Nested Classes

## Reference
1. Mr. Yitong Wang's repo for the course in Fall 2020. https://github.com/YeeTone/CS205-2020Fall
