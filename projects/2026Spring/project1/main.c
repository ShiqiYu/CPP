/*
Date: 2026.3.18
Discription:
    This program implements a simple calculator, which has 2 input patterns:
        1. Command line arguments: ./a.out <number1> <operator> <number2>
        2. Interactive mode: Users can input expressions in the terminal, and the program will output the result. Users can type "quit" or "exit" to exit.
Note:
    The calculator supports both the following operators: +, -, *, /, %, &, |, ^ and common math functions like sqrt, ln/log, exp, sin, cos, tan, hex, etc. (e.g., "sqrt(2)", "ln(10)", "sin(3.14)").
    For the modulus and bitwise operators, both operands must be integers within the range of long long.
    If the input is invalid (e.g., division by zero, invalid operator, non-integer operands for modulus/bitwise), the program will print an error message to stderr and continue running.
    If you are inputting through command line argument and using shell special characters like '*', '|', '&', '^' as operators, make sure to quote them (e.g., './a.out 2 '*' 3' or './a.out 2 \| 3').
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <float.h>
#include <ctype.h>

bool IsInteger(long double n)
{
    if (isnan(n) || isinf(n)) return false;
    return fabsl(n - roundl(n)) < LDBL_EPSILON;
}

void PrintNum(long double n)
{
    if (IsInteger(n) && fabsl(n) <= (long double)LLONG_MAX)
    {
        // Output integers without decimal point, and avoid scientific notation for large integers
        printf("%.0Lf", n);
    }
    else
    {
        // Output with 18 decimal places (or in scientific notation if it's very large/small)
        printf("%.18Lg", n);
    }
}

// single variable math fuctions: sqrt, ln/log, exp, sin, cos, tan, etc.
int CalculateMathFunction(const char *func_name, long double num)
{
    long double result;

    if (strcmp(func_name, "sqrt") == 0)
    {
        if (num < 0)
        {
            fprintf(stderr, "Invalid input: sqrt of negative number.\n");
            return 1;
        }
        result = sqrtl(num);
    }
    else if (strcmp(func_name, "ln") == 0 || strcmp(func_name, "log") == 0)
    {
        // log_e(num)
        if (num <= 0)
        {
            fprintf(stderr, "Invalid input: log of non-positive number.\n");
            return 1;
        }
        result = logl(num);
    }
    else if (strcmp(func_name, "exp") == 0)
    {
        // e^num
        result = expl(num);
    }
    else if (strcmp(func_name, "sin") == 0)
    {
        result = sinl(num);
    }
    else if (strcmp(func_name, "cos") == 0)
    {
        result = cosl(num);
    }
    else if (strcmp(func_name, "tan") == 0)
    {
        result = tanl(num);
    }
    else if (strcmp(func_name, "abs") == 0)
    {
        result = fabsl(num);
    }
    else if (strcmp(func_name, "hex") == 0)
    {
        if (!IsInteger(num) || num < (long double)LLONG_MIN || num > (long double)LLONG_MAX)
        {
            fprintf(stderr, "Invalid input: hex conversion requires integer within long long range.\n");
            return 1;
        }
        printf(" 0x%llX\n", (unsigned long long)(long long)num);
        return 0;
    }
    else
    {
        fprintf(stderr, "Unknown function: %s\n", func_name);
        return 1;
    }

    PrintNum(result);
    printf("\n");
    return 0;
}

int Calculate(long double num_1, char operator, long double num_2)
{
    long double result;
    bool support_ll = IsInteger(num_1) && IsInteger(num_2) && num_1 >= LLONG_MIN && num_1 <= LLONG_MAX && num_2 >= LLONG_MIN && num_2 <= LLONG_MAX;

    switch (operator)
    {
    case '+':
        result = num_1 + num_2;
        break;
    case '-':
        result = num_1 - num_2;
        break;
    case 'x':
        result = num_1 * num_2;
        break;
    case '*':
        result = num_1 * num_2;
        break;
    case 'X':
        result = num_1 * num_2;
        break;
    case '/':
        if (num_2 != 0)
        {
            result = num_1 / num_2;
            break;
        }
        else
        {
            fprintf(stderr, "A number cannot be divied by zero.\n");
            return 1;
        }
    case '%':
        if (support_ll)
        {
            long long n1 = (long long)num_1;
            long long n2 = (long long)num_2;
            if (n2 == 0) { fprintf(stderr, "Error: Modulo by zero.\n"); return 1; }
            //  deal with LLONG_MIN % -1 
            if (n1 == LLONG_MIN && n2 == -1) result = 0; 
            else result = (long double)(n1 % n2);
            break;
        }
        else
        {
            fprintf(stderr, "Modulus operator requires integer operands within long long range.\n");
            return 1;
        }
    case '&':
        if (support_ll)
        {
            result = (long double)((long long)num_1 & (long long)num_2);
            break;
        }
        else
        {
            fprintf(stderr, "Bitwise AND operator requires integer operands within long long range.\n");
            return 1;
        }
    case '|':
        if (support_ll)
        {
            result = (long double)((long long)num_1 | (long long)num_2);
            break;
        }
        else
        {
            fprintf(stderr, "Bitwise OR operator requires integer operands within long long range.\n");
            return 1;
        }
    case '^':
        if (support_ll)
        {
            result = (long double)((long long)num_1 ^ (long long)num_2);
            break;
        }
        else
        {
            fprintf(stderr, "Bitwise XOR operator requires integer operands within long long range.\n");
            return 1;
        }

    default:
        fprintf(stderr, "Invalid opearator.\n");
        return 1;
    }
    PrintNum(num_1);
    printf(" ");
    printf("%c ", operator);
    PrintNum(num_2);
    printf(" ");
    printf("= ");
    PrintNum(result);
    printf("\n");
    return 0;
}

int ParseAndCalculate(const char *input_str)
{
    // function
    char func_name[32];
    char arg_str[64];
    if (sscanf(input_str, " %31[a-zA-Z] ( %63[^)] )", func_name, arg_str) == 2)
    {
        char *end;
        long double math_num = strtold(arg_str, &end);

        // modification
        if (end == arg_str) 
        {
            return -1;
        }
        
        while (*end != '\0') 
        {
            if (!isspace((unsigned char)*end)) 
            {
                return -1;
            }
            end++;
        }

        return CalculateMathFunction(func_name, math_num);
    }

    // arithmetic expression
    long double num_1, num_2;
    char operator;
    char extra[2];
    if (sscanf(input_str, "%Lf %c %Lf %1s", &num_1, &operator, &num_2, extra) == 3)
    {
        return Calculate(num_1, operator, num_2);
    }

    // error
    return -1;
}

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        char args_str[1024];
        // Safely append arguments with a space separator
        int offset = 0;
        for (int i = 1; i < argc && offset < sizeof(args_str) - 1; ++i)
        {
            int written = snprintf(args_str + offset, sizeof(args_str) - offset, "%s ", argv[i]);
            if (written > 0)
            {
                offset += written;
            }
        }

        int res = ParseAndCalculate(args_str);
        
        if(res == 0)
        {
            return 0;
        }
        else if (res > 0)
        {
            return res; // calculation error
        }
        else
        {
            // parsing error
            if (argc == 4 || argc == 2)
            {
                fprintf(stderr, "The input cannot be interpret as numbers!\n");
            }
            else
            {
                fprintf(stderr, "Usage: %s <number1> <operator> <number2> or %s func(<number>)\n", argv[0], argv[0]);
                fprintf(stderr, "Note: If you are using shell special characters like '*', '|', '&', '^' as operators, make sure to quote them.\n");
            }
            return 1;
        }
    }
    else
    {
        printf("Interactive Mode (type 'exit' to quit):\n");
        while (true)
        {
            // read line
            char line[512];
            if (!fgets(line, sizeof(line), stdin))
            {
                break; // EOF
            }

            char str[64];
            if (sscanf(line, "%63s", str) == 1 && (strcmp(str, "quit") == 0 || strcmp(str, "exit") == 0))
            {
                printf("Goodbye!\n");
                break;
            }

            int res = ParseAndCalculate(line);

            if (res == -1)
            {
                char t1[64], t2[64], t3[64], t4[64];
                int token_count = sscanf(line, "%63s %63s %63s %63s", t1, t2, t3, t4);
                if (token_count > 0)
                {
                    if (token_count == 1 || token_count == 3)
                    {
                        fprintf(stderr, "The input cannot be interpret as numbers!\n");
                    }
                    else
                    {
                        fprintf(stderr, "Usage: <number1> <operator> <number2> or func(<number>)\n");
                    }
                }
            }
        }
    }

    return 0;
}