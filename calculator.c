#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_INPUT_LEN 1024

// 定义错误代码，方便统一管理错误类型
typedef enum {
    SUCCESS = 0,
    ERR_DIV_BY_ZERO,
    ERR_INVALID_INPUT,
    ERR_UNSUPPORTED_OP
} ErrorCode;

// 用于存储解析和计算结果的结构体
typedef struct {
    double result;
    ErrorCode err;
} CalcResult;

// --- 函数声明 ---
void run_interactive_mode();
void run_cli_mode(int argc, char *argv[]);
CalcResult evaluate_expression(const char *expr);
void print_result(const char *expr, CalcResult res);
bool parse_basic_expression(const char *expr, double *a, char *op, double *b);

// --- 主函数 ---
int main(int argc, char *argv[]) {
    if (argc > 1) {
        // 有命令行参数，进入命令行模式
        run_cli_mode(argc, argv);
    } else {
        // 无参数，进入交互模式
        run_interactive_mode();
    }
    return 0;
}

// --- 模式实现 ---

void run_cli_mode(int argc, char *argv[]) {
    char expr[MAX_INPUT_LEN] = {0};
    
    // 将所有参数拼接成一个完整的表达式字符串，忽略空格
    for (int i = 1; i < argc; ++i) {
        strncat(expr, argv[i], MAX_INPUT_LEN - strlen(expr) - 1);
        if (i < argc - 1) {
            strncat(expr, " ", MAX_INPUT_LEN - strlen(expr) - 1);
        }
    }

    CalcResult res = evaluate_expression(expr);
    print_result(expr, res);
}

void run_interactive_mode() {
    char input[MAX_INPUT_LEN];

    while (1) {
        printf("> "); // 提示符
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break; 
        }

        // 去除末尾换行符
        input[strcspn(input, "\n")] = 0;

        // 检查退出指令
        if (strcmp(input, "quit") == 0) {
            break;
        }
        
        // 忽略空输入
        if (strlen(input) == 0) continue;

        CalcResult res = evaluate_expression(input);
        
        // 交互模式下通常只输出结果或错误
        if (res.err == SUCCESS) {
            printf("%g\n", res.result);
        } else {
            print_result(input, res); // 复用错误打印逻辑
        }
    }
}

// --- 核心计算逻辑 ---

CalcResult evaluate_expression(const char *expr) {
    CalcResult res = {0.0, SUCCESS};
    double a = 0.0, b = 0.0;
    char op = 0;

    // 1. 解析表达式 (这里你需要实现更严谨的解析逻辑)
    if (!parse_basic_expression(expr, &a, &op, &b)) {
        res.err = ERR_INVALID_INPUT;
        return res;
    }

    // 2. 执行计算
    switch (op) {
        case '+': res.result = a + b; break;
        case '-': res.result = a - b; break;
        case '*': res.result = a * b; break;
        case '/':
            if (b == 0.0) {
                res.err = ERR_DIV_BY_ZERO;
            } else {
                res.result = a / b;
            }
            break;
        default:
            res.err = ERR_UNSUPPORTED_OP;
    }

    return res;
}

bool parse_basic_expression(const char *expr, double *a, char *op, double *b) {
    // 提示：要满足要求 4 (识别非数字)，你不能简单使用 sscanf，
    int matched = sscanf(expr, "%lf %c %lf", a, op, b);
    return (matched == 3);
}

// --- 结果输出与错误处理 ---

void print_result(const char *expr, CalcResult res) {
    switch (res.err) {
        case SUCCESS:
            printf("%s = %g\n", expr, res.result);
            break;
        case ERR_DIV_BY_ZERO:
            printf("A number cannot be divied by zero.\n");
            break;
        case ERR_INVALID_INPUT:
            printf("The input cannot be interpret as numbers!\n");
            break;
        case ERR_UNSUPPORTED_OP:
            printf("Unsupported operation.\n");
            break;
    }
}