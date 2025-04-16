# Project 5: GPU Acceleration with CUDA

## Requirements

1. Implement the expression **B** = *a* **A** + *b*, where *a* and *b* are scalars, **A** and **B** are matrices of the same size. You can implement it by modifying the example `matadd.cu`.

2. Compare the matrix multiplication by OpenBLAS on CPU with that by cuBLAS on GPU. cuBLAS is a GPU-accelerated library provided by NVIDIA. Do not use some huge matrics, and 4096x4096 should be large enough. We have a lot of students to share the server. Surely you can use your computer if you have an NVIDIA GPU. 

3. (Optional) Something interesting on GPU.

## Tips

1. The function in cuBLAS is `cublasSgemm()`.

2. Our course server will be very busy in the last few days to the deadline. 

## Rules

1. **Deadline**: Please submit your project report before its deadline. The deadline is **23:59, June 2**. After the deadline (even 1 second), **0 score!** No deadline extension for any students. 


1. **Format**: Please submit the files as: *.pdf, xxx.cu, xxx.h. Please do **NOT** put the files into a compressed one. To uncompress a lot of files will cost time for instructors. PDF format can make the layout of the report to be consistent on any computer. 


1. **Report**: Your score will also depend on the quality of your source code **and your report**. Your report should be easy to understand and describe your work well, especially the highlights of your work. If you do not know how to write the report, just assume you are a developer in a company and are reporting to your manager that you have developed a good calculator.

1. **Code style**: Please pay more attention to your code style. This is not ACM-ICPC contest. You have enough time to write code with both correct results and a good code style. You will get a deduction if your code style is terrible. You can read Google C++ Style Guide (<http://google.github.io/styleguide/cppguide.html>) or some other guide for code style. You may lose points on your project if your code is ugly.

1. **ChatGPT**: You can use ChatGPT as your personal coach. Such as you can use ChatGPT or some other similar tools to polish the text in your report. But ChatGPT can also generate some rubbish that looks good but contains nothing. It will waste the time of the instructor to review those empty words, and also make you lose points on your project. ChatGPT can also generate a framework of the source code, and help improve the quality of your source code. If you use it for that, please mention it in the report. You are responsible for all materials you submit, not ChatGPT.