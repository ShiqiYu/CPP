# A Simple Calculator

Implement a calculator which can multiply two numbers.

## Requirements

1. When you run the program as follows, it will output the expression and the result. **The two numbers should be input through the command line arguments**. If the two numbers are integers, the program will multiply them in integer format.

    ```bash
    $./mul 2 3
    2 * 3 = 6
    ```

2. If the input contains some non-integer numbers, the program will try to interpret the input as floating-point numbers.

    ```bash
    ./mul 3.1416 2
    3.1416 * 2 = 6.2832
    ./mul 3.1415 2.0e-2
    3.1415 * 0.02 = 0.062832
    ```

3. It can tell that the input is not a number.
    ```bash
    ./mul a  2
    The input cannot be interpret as numbers!
    ```

4. If you input some big integers, what will happen? Please describe some possible solutions, and try to implement them.

    ```bash
    ./mul 1234567890 1234567890
    ```

5. If you input some big floating-point numbers, what will happen? Please describe some possible solutions, and try to implement them.

    ```bash
    ./mul 1.0e200 1.0e200
    ```

6. Some others which can improve the program.

## Rules:

1. Please submit your project report before its deadline. After the deadline (even 1 second), **0 score!**. The deadline is 23:59 on Sep. 25.
1. Please submit two separate files: report.pdf and source.cpp. Please do **NOT** put the two files into a compressed one.
1. Your score will also depend on the quality of your source code and your report. Your report should be easy to understand and describe your work well, especially the highlights of your work.
1. Please pay more attention to your code style. This is not ACM-ICPC contest. You have enough time to write code with both correct results and a good code style. You will get deduction if your code style is terrible. You can read Google C++ Style Guide (http://google.github.io/styleguide/cppguide.html ) or some other guide for code style.
