# Chapter 3: Branching and Looping Statements

## `if` Statement

`if` statement can conditionally execute code, and is a frequently used statement in programming. The execution depends on Boolean expressions. Such as in the following example, When the value of `num` is less than `5`, the statement will be executed and print "The number is less than 5." 

```cpp
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

## Conditions

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
| Inclusive OR   | `\|\|`               | or                    | `a \|\| b`, `a or b`|

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

## `while` loop (`break`, `continue`)

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

The test takes place before each iteration in a `while` loop. There is a `do-while` loop, and the test takes place after each iteration in it. The following `do-while` loop behavior is the same with the previous `while` loop. 

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

## `for` loop (`break`, `continue`)

## `switch case` (`break`)

## `goto` statement

## Exercises

* a calculator? 

* Makefile (how to manage multiple source files using a Makefile)
