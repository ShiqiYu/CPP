# Chapter 3: Branching and Looping Statements

## `if` Statement

`if` statement can conditionally execute code, and is a frequently used statement in programming. The execution depends on Boolean expressions. Such as in the following example, When the value of `num` is less than `5`, the statement will be executed and print "The number is less than 5." 

```cpp
// if.cpp
int num  = 2;
// some operations may change num's value
if (num < 5)
    cout << "The number is less than 5." << endl;
```

If it is a compound statement to be executed, the compound statement should be brace-enclosed. Even if it is a one-line statement, it can also be brace-enclosed.
```cpp
if (num == 5 )
{
    cout << "The number is 5." << endl;
    //some other lines
}
```

`else` statement will be executed when the condition follows `if` is not true.

```cpp
if (num == 5 )
{
    cout << "The number is 5." << endl;
}
else
{
    cout << "The number is not 5." << endl;
}
```

If there are multiple conditions to be evaluated, you can use `else if` as follows. The first condition `num < 5` will be evaluated first, and then the second condition `num > 10`. If no matched conditions, the `else` statement will be executed. It should be noted that if the first condition is true, the second condition in `else if` will not be evaluated.

```cpp
if (num < 5)
    cout << "The number is less than 5." << endl;
else if (num > 10)
    cout << "The number is greater than 10." << endl;
else
    cout << "The number is in range [5, 10]." << endl;
```

`else` will be associated with the closest `if`. In the following code, `else` is associated with `if(num < 5)`, not `if(num < 10)`. Even no error is in the following code, some compilers, which are smart enough, will also give some warning messages since it may confuse readers.

```cpp
if(num < 10)
if(num < 5)
cout << "The number is less than 5" << endl;
else
cout << "Where I'm?" << endl;
```

To make the source code easier to understand, I suggest using braces and indents to format the source code as follows.

```cpp
if(num < 20)
{
    if(num < 5)
        cout << "The number is less than 5" << endl;
    else
        cout << "Where I'm?" << endl;
}
```

## `? :` operator

The ternary conditional operator `? :` is also widely used to simplify some `if else` statements. Let us look at the following code first. The variable `factor` will be assigned different values depending on the condition of `isPositive`.

```cpp
//ternary.cpp
bool isPositive = true;
int factor = 0;
//some operations may change isPositive's value
if(isPositive)
    factor = 1;
else
    factor = -1;
```

There are 4 lines of source code in the previous program for `if else`. The 4 lines of `if else` statement can be replaced by one line using a ternary condition operator `? :`.

```cpp
factor = isPositive ? 1 : -1;
```

If the condition before `?` is true, the value will be the expression between `?` and `:`. Otherwise, the value will be the expression after `:`.

The previous example can even be simplified to an expression without a jump statement. In the instructions compiled from `if`, `? :`, `for`, `while` and some others, there are jump statements. Different from them, the following code does not contain jumps. Since `isPositive` is Boolean and can be converted to `int` implicitly, so the conditional assignment by `if else` is converted a single assignment. It may be more efficient, at least not less efficient than `if else`. Sometimes our C/C++ compilers may optimize the generated binary executive code by converting `if else` to the following style statement. Anyway, not all `? :` statements can be converted to the following style statement.

```cpp
factor = (isPositive) * 2 - 1;
```

## Conditional Expressions

There is a conditional expression following `if` or `else if`, such as `num < 5` in the following example. It should be an expression that is convertible to `bool`. It can be a relational expression, a logical expression or a combination of them.

```cpp
if (num < 5)
    cout << "The number is less than 5. " << endl;
```
### Relational Expressions

There are 6 relational (comparison) operators as listed as follows. The value of a relational expression will be `true` or `false`. You can also regard them as `1` or `0`. Even in some programming languages, such as in Java, `true` is different from `1``, here in C or C++, you can think `true` is equivalent to `1` and `false` is `0`.

| Operation name                  | Example       |
|---------------------------------|---------------|
| equal to                        | `a == b`      |
| not equal to                    | `a != b`      |
| less than                       | `a < b`       |
| greater than                    | `a > b`       |
| less than or equal to           | `a <= b`      |
| greater than or equal to        | `a >= b`      |


### Logical Expressions

There are 3 logical operators as listed in the following table. In logical expressions, the operands are expected to be Boolean. If they are not, they will be converted to `bool` implicitly.

| Operator name  | Symbol-like operator | keyword-like operator | Example             |
|----------------|----------------------|-----------------------|---------------------|
| negation       | `!`                  | not                   | `!a`, `not a`       |
| AND            | `&&`                 | and                   | `a && b`, `a and b` |
| Inclusive OR   | `||`                 | or                    | `a || b`, `a or b`  |

It should be noted that the precedences of the 3 logical operators are different. `not` operator has the highest precedence, then `and`, and `or` has the lowest precedence among them.

### Non-Boolean Expressions

If the conditional expressions in `if` statements are not Boolean, they will be converted to `bool` implicitly. It is the same in the conditions of `for`, `while` and `switch` statements. If the value of the conditional expression is `char`, `int`, `long`, `float` or `double`, non-zero values will be converted to `true`, and the rest values will be `false`.

The following example is correct in grammar. But it is not recommended. A condition of `count == 0` or `(count < FLT_EPSILON) && (count > -FLT_EPSILON)` will be better.
```cpp
float count = 0.2f; 
if (count) // not recommend to use a float-point number
    cout << "There are some." << endl;
```

A pointer, which is an unsigned integer actually, can also be used in a conditional expression. `(!p)` in the following example is equivalent to `(p == NULL)`.

```cpp
int * p = new int[1024];
if (!p) // if(p == NULL)
    cout << "Memory allocation failed." << endl;
```

### A Trap in Conditional Expressions

Whereas in a `if` statement, a `while` loop or a `for` loop, you have to be careful enough not to misspell `==` as `=` in conditional expressions. It is a common error among beginners. The following loop is an endless loop.

```cpp
bool flag = false;
// Do something ...
if (flag = true) // error!
{
    // Do something
}
```
There are many kinds of expressions, such as `3 + 4`, `a + b` and `a == b`. They all have value. `a = b`  is also an expression, and its value is `a`, which is assigned the value of `b`. So `if(flag = true)` is equivalent to `if(true)`, the body will be executed whatever the value of `flag` is.

If you can understand that `a = b` is an expression and has a value, then it is also easy to understand `int m = (b = 8);` in the following code. It means `m` will be assigned as the value of `(b = 8)
```cpp
int b = 0;
int m = (b = 8);
```

## `while` loop

The syntax of the `while` loop is as follows. If the conditional expression is `true`, the loop body will be executed. 
```cpp
while( expression )
{
    //...
}
```

In the following example, the variable `num` is initialized to `10`. The condition `num > 0` is `true` since `num` is `10`. Then the loop body is executed, and `num` becomes `9` after executing `num--`. The loop body will be executed 10 times until `num` is 0.

```cpp
// while.cpp
#include <iostream>
using namespace std;
int main()
{
    int num = 10;
    while(num > 0)
    {
        cout << "num = " << num << endl;
        num--;
    }
}
```

The test takes place before each iteration in a `while` loop. There is a `do-while` loop, and the test takes place after each iteration in it. The following `do-while` loop behavior is the same as the previous `while` loop. 

```cpp
int num = 10;
do
{
    cout << "num = " << num << endl;
    num--;
}while (num > 0);
```

But be careful that the loop body will be executed in the first iteration even the conditional expression is not `true`. Such as the following example will print a line.

```cpp
int num = 0; // the condition is false
do
{ //but the body will be execuated in the 1st iteration
    cout << "num = " << num << endl;
    num--;
}while (num > 0);
```
The output of the previous example.
```console
num = 0
```

### `break` statement

The `break` statement will terminate a loop when it is executed. The remaining part of the loop body will not be executed also.

```cpp
int num = 10;
while (num > 0)
{
    if (num == 5)
        break;
    cout << "num = " << num << endl;
    num--;
}
// jump to here after `break` is executed
```

### `continue` statement
The `continue` statement will also change the routine of the loop, but it will not terminate the loop. The program will skip the remaining part of the loop body and continue the next iteration. In the following example, `num = 5` will not be printed, but `num = 4` should be. Really? Please run the source code to check if everything is correct.

```cpp
int num = 10;
while (num > 0)
{
    if (num == 5)
        continue; // "num = 5" will not be printed
    cout << "num = " << num << endl;
    num--;
}
```



## `for` loop

The syntax of the `for` loop is as follows. There are an initialization clause, a conditional expression and an iteration expression following the keyword `for`.
```cpp
for (init-clause; cond-expression; iteration-expression)
    loop-statement
```

The following code demonstrates the usage of `for`. The variable `i` is initialized to 1. The value of `i` will increase 1 by `i++` in each iteration. The iteration will continue until the condition `i < 10` becomes `false`.

```cpp
int sum = 0;
for(int i = 0; i < 10; i++)
{
    sum += i;
    cout << "Line " << i << endl;
}
cout << "sum = " << sum << endl;
```

The previous `for` loop can be converted to a `while` loop as follows. The only difference between the two pieces of code is the scope of `i`. The scope of `i` is inside the `for` loop body in the previous example. But it is outside of the `while` loop body since it is declared outside of the loop body.
```cpp
int sum = 0;
int i = 0; // put the init-clause here
while(i < 10) // while is followed by the cond-expression
{
    sum += i;
    cout << "Line " << i << endl;
    i++; // put the iteration-expression here
}
cout << "sum = " << sum << endl;
```

A `while` loop can also be converted to a `for` loop as shown in the following example.
```cpp
while(num > 0)
{
    cout << "num = " << num << endl;
    num--;
}
```

```cpp
for(; num > 0; )
{
    cout << "num = " << num << endl;
    num--;
}
```

Some may be curious that the previous `for` loop has no initialization clause and iteration expression. The truth is that even the conditional expression can be omitted as follows.

```cpp
for(; ; )
{
    if (num <= 0)
        break;
    cout << "num = " << num << endl;
    num--;
}
```

The behaviors of `break` and `continue` are the same as those in the `while` loop. The details will not be presented here again.

## `goto` statement
The `goto` statement can make the program jump to the desired location. Too many `goto` statements may break the flow of execution. It is an unrecommended statement. The most frequently used place is for error handling. In the function `mysqure()`, a label `EXIT_ERROR` is declared. If the argument cannot meet the requrement, the program will use `goto` to jump to location `EXIT_ERROR` where are the error handling source code. 

The `goto` statement is widely used in Linux kernel functions, which are in the C language. Those functions normally exit from multiple locations, and some common work such as cleanup has to be done. But in C++ exceptions are more commonly used error handling which is introduced in a later chapter.

```cpp
//goto.cpp
float mysquare(float value)
{
    float result = 0.0f;
    if(value >= 1.0f || value <= 0)
    {
        cerr << "The input is out of range." << endl;
        goto EXIT_ERROR;
    }
    result = value * value;
    return result;
  EXIT_ERROR:
    //do sth such as closing files here
    return 0.0f;
}
```
## `switch` Statement

The `switch` statement can execute one of several statements depending on the value of an expression. The expression follows the keyword `switch`, and it is `input_char` in the following example. Some beginners may forget `break`, which prevents executing the following statements. If `switch` is understood in the `if - else if - else` manner, `break` is easy to omit. Actually, you can think there are many entrances defined by `case`, and `switch` works like `goto`. The execution will start from a matched entrance defined by `case`, continue until reaching `break`.

```cpp
//switch.cpp
switch (input_char)
{
    case 'a':
    case 'A':
        cout << "Move left." << endl;
        break;
    case 'd':
    case 'D':
        cout << "Move right." << endl;
        break;
    default: 
        cout << "Undefined key." << endl;
        break;
}
```

## Exercises

* Please use a Makefile to manage multiple source files. You can use `make` to compile and link, and `make clean` to remove all generated files.
