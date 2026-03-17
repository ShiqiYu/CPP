#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>

int is_integer(long double n){
    return n == floorl(n);
}

// 单参数数学函数处理
int calculate_math_func(const char *func_name, long double num){
    long double result;
    
    if(strcmp(func_name, "sqrt") == 0){
        if(num < 0){
            fprintf(stderr, "Invalid input: sqrt of negative number.\n");
            return 1;
        }
        result = sqrtl(num);
    }else if(strcmp(func_name, "ln") == 0 || strcmp(func_name, "log") == 0){
        if(num <= 0){
            fprintf(stderr, "Invalid input: log of non-positive number.\n");
            return 1;
        }
        result = logl(num);
    }else if(strcmp(func_name, "exp") == 0){
        result = expl(num);
    }else if(strcmp(func_name, "sin") == 0){
        result = sinl(num);
    }else if(strcmp(func_name, "cos") == 0){
        result = cosl(num);
    }else if(strcmp(func_name, "tan") == 0){
        result = tanl(num);
    }/* 你可以在这里继续添加其他函数... */
    else{
        fprintf(stderr, "Unknown function: %s\n", func_name);
        return 1;
    }
    
    // 打印结果：如果结果是整数且在 long long 范围内，打印整数；否则打印浮点数
    if(is_integer(result) && fabsl(result) <= (long double)LLONG_MAX){
        printf("%.0Lf\n", result);
    }else{
        printf("%.18Lg\n", result);
    }
    return 0;
}

void print_num(long double n){
    if(is_integer(n) && fabsl(n) <= (long double)LLONG_MAX){
        printf("%.0Lf ", n);
    }else{
        printf("%.18Lg ", n);
    }
}

int calculate(long double num1, char operator, long double num2){
        bool use_ll = is_integer(num1) && is_integer(num2) && operator != '/'
                    && num1 >= LLONG_MIN && num1 <= LLONG_MAX
                    && num2 >= LLONG_MIN && num2 <= LLONG_MAX;
        long long ll_num1 = (long long)num1;
        long long ll_num2 = (long long)num2;
        long double result_double;
        long long result_ll;

        switch(operator){
            case '+': 
                if(use_ll) result_ll = ll_num1 + ll_num2; 
                else result_double = num1 + num2; 
                break;
            case '-': 
                if(use_ll) result_ll = ll_num1 - ll_num2; 
                else result_double = num1 - num2; 
                break;
            case 'x': 
                if(use_ll) result_ll = ll_num1 * ll_num2; 
                else result_double = num1 * num2; 
                break;
            case '/': 
                if(num2 != 0){
                    use_ll = false;
                    result_double = num1 / num2;
                    break;
                }else{
                    fprintf(stderr, "A number cannot be divied by zero.\n");
                    return 1;
                }
            default:
                fprintf(stderr, "Invalid opearator.\n");
                return 1;
        }
        print_num(num1);
        printf("%c ", operator);
        print_num(num2);
        printf("= ");
        if(use_ll){
            print_num((long double)result_ll);
        }else{
            print_num(result_double);
        }
        printf("\n");
        return 0;
}

int main(int argc, char *argv[]){
    char *endptr1, *endptr2;
    if(argc > 1){
        if(argc != 4){
            fprintf(stderr, "Usage: %s <number1> <operator> <number2>\n", argv[0]);
            return 1;
        }

        long double num1 = strtold(argv[1], &endptr1);
        char operator = argv[2][0];
        long double num2 = strtold(argv[3], &endptr2);

        if(*endptr1 != '\0'){
            fprintf(stderr, "Invalid number: %s\n", argv[1]);
            return 1;
        }
        if(*endptr2 != '\0'){
            fprintf(stderr, "Invalid number: %s\n", argv[3]);
            return 1;
        }

        int res = calculate(num1, operator, num2);
        if(res != 0){
            return res;
        }
    }else{
        long double num1, num2;
        char operator;

        while(true){
            // 读取整行来处理不同格式的输入
            char line[256];
            if(!fgets(line, sizeof(line), stdin)){
                break; // EOF
            }

            char str[64];
            // 先检查是不是直接输入了 quit 或 exit
            if(sscanf(line, "%63s", str) == 1 && (strcmp(str, "quit") == 0 || strcmp(str, "exit") == 0)){
                break;
            }

            // 尝试匹配 func(num) 格式，例如 sqrt(9.0)
            char func_name[32];
            long double math_num;
            // %31[a-zA-Z] 表示最多读取31个字母；后面的括号和 %Lf 配合，允许内部有空格
            if(sscanf(line, " %31[a-zA-Z] ( %Lf )", func_name, &math_num) == 2){
                calculate_math_func(func_name, math_num);
                continue;
            }

            // 尝试正常的四则运算解析：<数字> <操作符> <数字>
            int parsed = sscanf(line, "%Lf %c %Lf", &num1, &operator, &num2);
            
            if(parsed == 3){
                int res = calculate(num1, operator, num2);
            }else{
                // 可以排除整行全空白的情况，如果有内容进入这说明格式不对
                if(sscanf(line, "%63s", str) == 1){
                    fprintf(stderr, "Invalid input.\n");
                }
            }
        }
    }
    
    return 0;
}