# Project 5: A Class for Matrices

Please use C++ to implement a class.

## Requirements

1. Design a class for matrices, and the class should contain the data of a matrix and related information such the number of rows, the number of columns, the number of channels, etc.

1. The class should support different data types. It means that the matrix elements can be `unsigned char`, `short`, `int`, `float`, `double`, etc.

1. Do not use memory hard copy if a matrix object is assigned to another. Please carefully handle the memory management to avoid memory leaks and to release memory multiple times.

1. Implement some frequently used operators including but not limited to `=`, `==`, `+`, `-`, `*`, etc. Surely the matrix multiplication in Project 4 can be included.

1. Implement region of interest (ROI) to avoid memory hard copy.

1. [Optional] Test your program on X86 and ARM platforms, and describe the differences.

1. [Tip] Class `cv::Mat` is a good example for this project. https://docs.opencv.org/master/d3/d63/classcv_1_1Mat.html 

## Rules:
1. Please submit your project report before its deadline. After the deadline, **23:59 on Dec. 18**, (even 1 second), **0 score!**.

1. Please submit the files as: report.pdf, source1.c, source2.c, header.h. You can also just put the link of your GitHub repository in your report, and do not need to submit source files. Please do **NOT** put the files into a compressed one.

1. Your score will also depend on the quality of your source code and your report. Your report should be easy to understand and describe your work well, especially the highlights of your work.

1. Please pay more attention to your code style. This is not ACM-ICPC contest. You have enough time to write code with both correct results and a good code style. You will get deduction if your code style is terrible. You can read Google C++ Style Guide (http://google.github.io/styleguide/cppguide.html ) or some other guide for code style.

