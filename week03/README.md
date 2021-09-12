# Chapter 3: Loops and Branching Statements

## `if` Statement

`if` statement can conditionally execute code, and is a frequently used statement in programming. When the value of `num` is less than `5`, the statement will be executed and print "The number is less than 5." 

```C++
int num  = 2;
// some operations may change num's value
if (num < 5)
    cout << "The number is less than 5." << endl;
```

If it is a compound statement to be executed, the compound statement should be brace-enclosed. Even it is an one-line statement, it can also be brace-enclosed.
```C++
if (num == 5 )
{
    cout << "The number is 5." << endl;
    //some other lines
}
```

`else` statement will be executed when the condition follows `if` is not true.

```C++
if (num == 5 )
{
    cout << "The number is 5." << endl;
}
else
{
    cout << "The number is not 5." << endl;
}
```

If there are multiple conditions to be evaluated, you can use `else if` as follows. The first condition `num < 5` will be evaluated first, and then the second condition `num > 10`. If no matched conditions, the `else` statement will be executed.

```C++
if (num < 5)
    cout << "The number is less than 5." << endl;
else if (num > 10)
    cout << "The number is greater than 10." << endl;
else
    cout << "The number is in range [5, 10]." << endl;
```

`else` will be associated with the closest `if`. In the following code, `else` is associated with `if(num < 5)`, not `if(num < 10)`. Even no error is in the following code, some compilers will also give some warning messages since it may confuse readers.

```C++
if(num < 10)
if(num < 5)
cout << "The number is less than 5" << endl;
else
cout << "Where I'm?" << endl;
```

To make the source code easier to understand, I suggest to use braces and indents to format the source code as follows.

```C++
if(num < 20)
{
    if(num < 5)
        cout << "The number is less than 5" << endl;
    else
        cout << "Where I'm?" << endl;
}
```

## `? :` operator

The ternary conditional operator `? :` is also widely used to replace some `if else` statements.

```C++
bool isPositive = true;
int factor = 0;
//some operations may change isPositive's value
if(isPositive)
    factor = 1;
else
    factor = -1;
```

The `if else` statement can be replaced by one line code as follows.

```C++
factor = isPositive ? 1 : -1;
```

If the condition before `?` is true, the value will be the one between `?` and `:`. Otherwise, the value will be the one after `:`.

For the previous example, it can even be simplified to an expression without jump. In the instructions compiled from `if`, `? :`, `for`, `while` and some others, there are jump statements. Different with them, the following code does not contain jumps. It should be more efficient most of the time. But not all `? :` statements can be converted to the following style statement.

```C++
factor = (isPositive) * 2 - 1;
```

## Conditions

### Relational Expressions

### Logical Expressions

### Non-Boolean Expressions


## for loop (break, continue)

## while loop (break, continue)

## switch case (break )

## goto

## Exercises

* a calculator? 

* Makefile (how to manage multiple source files using a Makefile)
