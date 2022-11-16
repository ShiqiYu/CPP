# Project 4: Matrix Multiplication in C

Please implement matrix multiplication in C and try your best to improve its speed. The project is an improvement of Project 3. You can reuse the source code in Project 3, but should present your improvements and different parts in the report.

## Requirements

1. Implement a function `matmul_plain()` in a straightforward way using several loops as the benchmark.

1. Implement a function `matmul_improved()` using SIMD, OpenMP and other technologies to improve the speed. You can compare it with `matmul_plain(`)`. 

1. Test the performance using 16x16, 128x128, 1Kx1K, 8Kx8K and 64Kx64K matrices. You can generate some matrics with random values to test your function.

1. Compare your implementation with the matrix multiplication in OpenBLAS (https://www.openblas.net/). The results by your implementation should be the same or very similar with those by OpenBLAS. Can your implementation be as fast as OpenBLAS?

1. [Optional] Test your program on X86 and ARM platforms, and describe the differences.

## Rules:

1. Please submit your project report before its deadline. After the deadline, **23:59 on Nov. 27**, (even 1 second), **0 score!**.

1. Please submit the files as: report.pdf, source1.c, source2.c, header.h. You can also just put the link of your GitHub repository in your report, and do not need to submit source files. Please do **NOT** put the files into a compressed one.

1. Your score will also depend on the quality of your source code and your report. Your report should be easy to understand and describe your work well, especially the highlights of your work.

1. Please pay more attention to your code style. This is not ACM-ICPC contest. You have enough time to write code with both correct results and a good code style. You will get deduction if your code style is terrible. You can read Google C++ Style Guide (http://google.github.io/styleguide/cppguide.html ) or some other guide for code style.

