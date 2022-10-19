# Project 3: A Libray for Matrix Operations in C

## Requirements

1. The programming language can only be C, not C++. Please save your source code into `*.c` files, and compile them using a C compiler such as gcc (not g++). Try to use Makefile or CMake to manage your source code.

1. Design a `struct` for matrices, and the `struct` should contain the data of a matrix, the number of columns, the number of rows, etc. 

1. Only `float` elements in a matrix are supported. You do not need to implement some other types.

1. Implement some functions to 
    * create a matrix, `createMatrix()`.
    * delete a matrix, `deleteMatrix()`.
    * copy a matrix (copy the data from a matrix to another), `copyMatrix()`.
    * add two matrices, `addMatrix()`.
    * subtraction of two matrices, `subtractMatrix()`
    * add a scalar to a matrix.
    * subtract a scalar from a matrix.
    * multiply a matrix with a scalar.
    * multiply two matrices.
    * find the minimal and maximal values of a matrix.
    * some other functions needed

1. The designed functions should be safe and easy to use. Suppose you are designing a library for others to use. You do not need to focus on the optimization in this project, ease of use is more important. 

## Rules:

1. Please submit your project report before its deadline. After the deadline, **23:59 on Oct. 30**, (even 1 second), **0 score!**.
1. Please submit the files as: report.pdf, source1.c, source2.c, header.h. I think you do not need more than 5 files for the project. Please do **NOT** put the files into a compressed one.
1. Your score will also depend on the quality of your source code and your report. Your report should be easy to understand and describe your work well, especially the highlights of your work.
1. Please pay more attention to your code style. This is not ACM-ICPC contest. You have enough time to write code with both correct results and a good code style. You will get deduction if your code style is terrible. You can read Google C++ Style Guide (http://google.github.io/styleguide/cppguide.html ) or some other guide for code style.

