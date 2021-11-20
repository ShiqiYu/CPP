# Chapter 11: Dynamic Memory Management in Classes

## Some Default Operations

* Default constructor
* Default copy constructor
* Default copy assignment
* How pointer members work by default

## An Example with Dynamic Data Allocation

## Solution

## Matrix Data Management in OpenCV

## Smart Pointers

* std::unique_ptr (C++11)
* std::shared_ptr (C++11)

## Lab

Create a class for matrices which elements are in float. The class should support the follow operations and has no memory management problem. When a matrix is assigned to another by =, the two matrices will share the same data.
`class Matrix{...};`
`Matrix a(3,4);`
`Matrix b(3,4);`
`Matrix c = a + b;`
`Matrix d = a * 2.0f;`
