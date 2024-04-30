# Project 4: A Class to Describe a Matrix

In Project 3, you may use `struct Matrix` to describe a matrix in C. C++ has more features than C. Now it is time to use C++ to implement a `class Matrix` to describe a matrix. This will help you to better understand the C++ features. **Make sure the class is easy to use and, importantly, memory-safe.**

## Requirements

1. The class should support different data types. It means that the matrix elements can be `unsigned char`, `short`, `int`, `float`, `double`, etc. Some data members are listed as follows. To be simple, you can just implement the class for 2D matrices. 
```C
class Matrix
{
    size_t rows;
    size_t cols;
    unsigned char * data;
    // ...
};
```

2. Do not use memory hard copy if a matrix object is assigned to another. Please carefully handle the memory management to avoid memory leaks and avoid releasing memory multiple times.

3. Operation overloading including but not limited to `=`, `==`, `+`, `-`, `*`, etc. Surely the matrix multiplication in Project 3 can be included.

4. Implement region of interest (ROI) to avoid memory hard copy. The region of a matrix `Matrix a` can be described by another object `Matrix b`. The two objects, `a` and `b`, share the same memory.

## Tip

Class `cv::Mat` is a good example for this project. https://docs.opencv.org/master/d3/d63/classcv_1_1Mat.html 

## Rules

1. **Deadline**: Please submit your project report before its deadline. The deadline is **23:59, May 19**. After the deadline (even 1 second), **0 score!** No deadline extension for any students. 


1. **Format**: Please submit the files as: *.pdf, xxx.cpp, xxx.cpp, xxx.h. Please do **NOT** put the files into a compressed one. To uncompress a lot of files will cost time for instructors. PDF format can make the layout of the report to be consistent on any computer. 


1. **Report**: Your score will also depend on the quality of your source code **and your report**. Your report should be easy to understand and describe your work well, especially the highlights of your work. If you do not know how to write the report, just assume you are a developer in a company and are reporting to your manager that you have developed a good calculator.

1. **Code style**: Please pay more attention to your code style. This is not ACM-ICPC contest. You have enough time to write code with both correct results and a good code style. You will get a deduction if your code style is terrible. You can read Google C++ Style Guide (<http://google.github.io/styleguide/cppguide.html>) or some other guide for code style. You may lose points on your project if your code is ugly.

1. **ChatGPT**: You can use ChatGPT as your personal coach. Such as you can use ChatGPT or some other similar tools to polish the text in your report. But ChatGPT can also generate some rubbish that looks good but contains nothing. It will waste the time of the instructor to review those empty words, and also make you lose points on your project. ChatGPT can also generate a framework of the source code, and help improve the quality of your source code. If you use it for that, please mention it in the report. You are responsible for all materials you submit, not ChatGPT.