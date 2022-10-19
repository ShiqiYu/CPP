# Project 2: A Better Calculator

Please implement a much better calculator than that in Project 1. The programming language can be C or C++.

## Requirements

1. When you run your program and input an express in a line as follows, it can output the correct results. The operator precedence (order of operations) should be correct.
    ```
    2+3
    5
    5+2*3
    11
    ```
1. Use parentheses to enforce the priorities.
    ```
    (5+2)*3
    21
    ```
1. Variables can be defined as follows.
    ```
    x=3
    y=6
    x+2*y
    15
    ```
1. Some math functions can be supported.
    ```
    sqrt(3.0)
    1.7
    ```
1. It can support arbitrary precision.
    ```
    999999999999999999999999999.222222222 + 1.0
    1000000000000000000000000000.222222222
    ```
1. More features can be found in the calculator BC in Unix-like systems. You can visit this page for more information. https://www.gnu.org/software/bc/manual/html_mono/bc.html

1. Please use CMake to manage the source files if there are several.

1. Hosting your source code at GitHub.com is an option. You are strongly recommended to create a repository at GitHub.com to hold your source code for this project. Git is a good tool for version control. If so, you can just put a link in the report of the project, and do not need to upload the source code to Blackboard. If you do not host your source code at GitHub.com, please upload your source with your report to Blackboard.


## Rules:

1. Please submit your project report before its deadline. After the deadline (even 1 second), 0 score!
1. If you only implement requirements 1 and 2, the upper boundary of your score is 80. For a better score, you should implement the rest requirements. 
1. Your score will also depend on the quality of your source code and your report. Your report should be easy to understand and describe your work well, especially the highlights of your work.
1. Please pay more attention to your code style. This is not ACM-ICPC contest. You have enough time to write code with both correct results and a good code style. You will get deduction if your code style is terrible. You can read Google C++ Style Guide (http://google.github.io/styleguide/cppguide.html ) or some other guide for code style.
