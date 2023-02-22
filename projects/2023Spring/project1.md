# A simple calculator

Implement a calculator which can add, subtract, multiply and divide two numbers.

## Requirements

1. The programming language should only be C, **NOT** C++. Please save your source code into a `*.c` file, and compile it using a C compiler such as gcc (not g++). 

1. When you run the program as follows, it will print the expression and the result. **The two numbers should be input through the command line arguments**. 

    ```bash
    $./calculator 2 + 3
    2 + 3 = 5
    $./calculator 2 - 3
    2 - 3 = -1
    $./calculator 2 * 3
    2 * 3 = 6
    $./calculator 2 / 3
    2 / 3 = 0.66666667
    ```

1. It can tell the reason why the operation cannot be carried out.
    ```bash
    ./calculator 3.14 / 0
    A number cannot be divied by zero.
    ```

1. It can tell the reason when the input is not a number.
    ```bash
    ./calculator a * 2
    The input cannot be interpret as numbers!
    ```

1. If you input some big numbers, what will happen? Please provide some possible solutions, and try to implement them.

    ```bash
    ./calculator 987654321 * 987654321 # The result should be 975461057789971041
    ```
    ```bash
    ./calculator 1.0e200 1.0e200 # The result should be 1.0e400
    ```

6. Some others which can improve the program.

## Rules:

1. Please submit your project report before its deadline. After the deadline (even 1 second), **0 score!** The deadline is 23:59 on March 5.

1. Please submit the files as: report.pdf, xxx.c, Please do **NOT** put the files into a compressed one.

1. Your score will also depend on the quality of your source code and your report. Your report should be easy to understand and describe your work well, especially the highlights of your work.

1. Please pay more attention to your code style. This is not ACM-ICPC contest. You have enough time to write code with both correct results and a good code style. You will get a deduction if your code style is terrible. You can read Google C++ Style Guide (http://google.github.io/styleguide/cppguide.html ) or some other guide for code style.

