#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <errno.h>

/* ============================================================
 * 1. 宏定义与结构体
 * ============================================================ */

#define MAX_INPUT_LEN 1024
#define MAX_BIGINT_LEN 2048

// 错误代码枚举：统一管理所有可能的错误类型
typedef enum {
    SUCCESS = 0,           // 计算成功
    ERR_DIV_BY_ZERO,       // 除数为零错误
    ERR_INVALID_INPUT,     // 输入格式无效
    ERR_UNSUPPORTED_OP     // 不支持的运算符
} ErrorCode;

// 计算结果结构体：包含计算结果和错误信息（支持大数）
typedef struct {
    char result[MAX_BIGINT_LEN];  // 计算结果（字符串形式，支持任意精度）
    ErrorCode err;                // 错误代码
} CalcResult;

/* ============================================================
 * 2. 函数声明
 * ============================================================ */

void run_interactive_mode(int precision);                                    // 交互模式入口
void run_cli_mode(int argc, char *argv[], int precision);                      // 命令行模式入口
CalcResult evaluate_expression(const char *expr, int precision);               // 表达式计算核心
void print_result(const char *expr, CalcResult res);            // 结果输出和错误处理
bool parse_basic_expression(const char *expr, char *num1, char *op, char *num2);  // 基础表达式解析（支持大数字符串）

// BigInt 大数运算库 - 函数声明
void bigint_add(const char *num1, const char *num2, char *result);
// 内部函数：无符号绝对值加法 (|num1| + |num2|)
// 要求：num1 和 num2 必须是纯数字字符串
static void bigint_abs_add(const char *num1, const char *num2, char *result);

// 内部函数：无符号绝对值减法 (|num1| - |num2|)
// 要求：必须保证 |num1| >= |num2|，且为纯数字字符串
static void bigint_abs_sub(const char *num1, const char *num2, char *result);

// 内部函数：无符号绝对值比较
// 返回：1 (|num1| > |num2|), 0 (|num1| == |num2|), -1 (|num1| < |num2|)
static int bigint_abs_compare(const char *num1, const char *num2);


void bigint_sub(const char *num1, const char *num2, char *result);
void bigint_mul(const char *num1, const char *num2, char *result);
void bigint_div(const char *num1, const char *num2, char *result, int precision, ErrorCode *err);
// 去除前导零：将 "000123" 格式化为 "123"
void remove_leading_zeros(char *str);

// 字符串反转：方便个位对齐计算（通常底层运算都会用到）
void reverse_string(char *str);

/* ============================================================
 * 3. BigInt 大数运算库
 * ============================================================ */

// 字符串反转：方便个位对齐计算
void reverse_string(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

// 去除前导零：将 "000123" 格式化为 "123"，保留单独的 "0"
void remove_leading_zeros(char *str) {
    int len = strlen(str);
    int i = 0;
    // 找到第一个非零字符。条件 i < len - 1 是为了防止把 "0" 删空
    while (i < len - 1 && str[i] == '0') {
        i++;
    }
    // 如果有前导零，将后面的有效数字整体前移
    if (i > 0) {
        memmove(str, str + i, len - i + 1);
    }
}

// 返回：1 (|num1| > |num2|), 0 (|num1| == |num2|), -1 (|num1| < |num2|)
static int bigint_abs_compare(const char *num1, const char *num2) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);

    // 1. 长度不同，长的那个绝对值更大
    if (len1 > len2) return 1;
    if (len1 < len2) return -1;

    // 2. 长度相同，从高位到低位逐位比较 (字典序刚好符合数字大小)
    int cmp = strcmp(num1, num2);
    if (cmp > 0) return 1;
    if (cmp < 0) return -1;

    return 0; // 完全相等
}


void bigint_add(const char *num1, const char *num2, char *result) {
    // 正数为 1，负数为 -1
    int sign1 = 1, sign2 = 1;
    const char *abs_num1 = num1;
    const char *abs_num2 = num2;

    if (num1[0] == '-') {
        sign1 = -1;
        abs_num1++;
    }
    if (num2[0] == '-') {
        sign2 = -1;
        abs_num2++;
    }
    if (sign1 == sign2) {
        // 同号相加
        if (sign1 == -1) {
            *result = '-';
            result++; // 结果指针后移，腾出负号的位置
        }
        bigint_abs_add(abs_num1, abs_num2, result);
        
    } else {
        // 异号相加
        int cmp = bigint_abs_compare(abs_num1, abs_num2);
        
        if (cmp == 0) {
            // 绝对值相等结果为 0
            strcpy(result, "0");
            
        } else if (cmp > 0) {
            if (sign1 == -1) {
                *result = '-';
                result++;
            }
            bigint_abs_sub(abs_num1, abs_num2, result);
            
        } else {
            if (sign2 == -1) {
                *result = '-';
                result++;
            }
            bigint_abs_sub(abs_num2, abs_num1, result);
        }
    }
}

// 无符号绝对值加法 (|num1| + |num2|)
static void bigint_abs_add(const char *num1, const char *num2, char *result) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    
    // 指针指向各自的个位 (字符串末尾)
    int i = len1 - 1;
    int j = len2 - 1;
    
    int k = 0;       // result 的索引
    int carry = 0;   // 进位

    // 只要还有位没算完，或者还有进位，就继续加
    while (i >= 0 || j >= 0 || carry > 0) {
        // 如果该数字已经遍历完，则将其位视为 0
        int digit1 = (i >= 0) ? num1[i] - '0' : 0;
        int digit2 = (j >= 0) ? num2[j] - '0' : 0;

        int sum = digit1 + digit2 + carry;
        
        result[k++] = (sum % 10) + '0'; // 当前位的结果
        carry = sum / 10;               // 计算新的进位
        
        i--;
        j--;
    }
    
    result[k] = '\0'; // 加上字符串结束符
    
    // 因为我们是从个位开始写入 result 的，所以此时的高位在右边，需要反转回来
    reverse_string(result);
}

// 无符号绝对值减法 (|num1| - |num2|)
// 前提：|num1| 必然大于等于 |num2|
static void bigint_abs_sub(const char *num1, const char *num2, char *result) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    
    int i = len1 - 1;
    int j = len2 - 1;
    
    int k = 0;
    int borrow = 0; // 借位标志

    // 因为前提是 |num1| >= |num2|，所以我们只需要遍历到 num1 结束即可
    while (i >= 0) {
        int digit1 = num1[i] - '0';
        int digit2 = (j >= 0) ? num2[j] - '0' : 0;

        int diff = digit1 - digit2 - borrow;

        // 如果不够减，向高位借10
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result[k++] = diff + '0';
        i--;
        j--;
    }
    result[k] = '\0';

    // 反转字符串恢复正常的高低位顺序
    reverse_string(result);

    // 去除相减可能产生的前导零 (例如 100 - 99 会算出 001，需要变成 1)
    remove_leading_zeros(result);
}



void bigint_sub(const char *num1, const char *num2, char *result) {
    // 我们需要一个临时数组来存储反转符号后的 num2
    char inverted_num2[MAX_INPUT_LEN];

    // 特殊情况：如果 num2 是 "0"，不需要加负号（避免出现 "-0"）
    if (strcmp(num2, "0") == 0) {
        strcpy(inverted_num2, "0");
    } 
    // 如果 num2 是负数，去掉负号变成正数
    else if (num2[0] == '-') {
        strcpy(inverted_num2, num2 + 1); // 指针加1，跳过 '-'
    } 
    // 如果 num2 是正数，在前面补上负号
    else {
        inverted_num2[0] = '-';
        strcpy(inverted_num2 + 1, num2);
    }
    // 核心：调用带符号加法器
    bigint_add(num1, inverted_num2, result);
}

void bigint_mul(const char *num1, const char *num2, char *result) {
    // 0. 特殊情况提前处理：乘以 0 的结果必定是 0
    if (strcmp(num1, "0") == 0 || strcmp(num2, "0") == 0 || 
        strcmp(num1, "-0") == 0 || strcmp(num2, "-0") == 0) {
        strcpy(result, "0");
        return;
    }

    // 1. 确定符号并提取纯数字部分
    int is_negative = 0;
    const char *abs1 = num1;
    const char *abs2 = num2;

    if (num1[0] == '-') {
        is_negative ^= 1; // 使用异或，遇负则反转状态
        abs1++;
    }
    if (num2[0] == '-') {
        is_negative ^= 1;
        abs2++;
    }

    int len1 = strlen(abs1);
    int len2 = strlen(abs2);
    int total_len = len1 + len2;

    // 分配一个临时数组来存储计算过程中的各位数字，初始化为 0
    int *temp_res = (int *)calloc(total_len, sizeof(int));
    if (!temp_res) {
        strcpy(result, "Error: Memory allocation failed");
        return;
    }

    // 2. 核心：两层循环，模拟竖式乘法
    for (int i = len1 - 1; i >= 0; i--) {
        for (int j = len2 - 1; j >= 0; j--) {
            int digit1 = abs1[i] - '0';
            int digit2 = abs2[j] - '0';
            
            // 乘积加上当前位上原有的值（之前累加进位留下来的）
            int mul = digit1 * digit2 + temp_res[i + j + 1];

            // 当前位保留个位数
            temp_res[i + j + 1] = mul % 10;
            // 十位数作为进位，累加到高一位
            temp_res[i + j] += mul / 10;
        }
    }

    // 3. 构造最终的字符串结果
    int k = 0;
    // 如果结果是负数，先在字符串头部加上负号
    if (is_negative) {
        result[k++] = '-';
    }

    // 找到第一个非零位（跳过前导零）
    int start = 0;
    while (start < total_len && temp_res[start] == 0) {
        start++;
    }

    // 把临时数组里的数字转换成字符存入 result
    for (int i = start; i < total_len; i++) {
        result[k++] = temp_res[i] + '0';
    }
    result[k] = '\0';

    free(temp_res); // 释放临时内存
}


//

// 统一的大数除法：同时支持整数计算与高精度小数扩展
void bigint_div(const char *num1, const char *num2, char *result, int precision, ErrorCode *err) {
    // 0. 错误拦截：除数不能为 0
    if (strcmp(num2, "0") == 0 || strcmp(num2, "-0") == 0) {
        *err = ERR_DIV_BY_ZERO;
        return;
    }
    *err = SUCCESS;

    // 1. 解析符号并提取绝对值
    int sign1 = (num1[0] == '-') ? -1 : 1;
    int sign2 = (num2[0] == '-') ? -1 : 1;
    int is_negative = (sign1 != sign2);

    const char *abs1 = (sign1 == -1) ? num1 + 1 : num1;
    const char *abs2 = (sign2 == -1) ? num2 + 1 : num2;

    // 用于暂存除法过程中的数据
    char current_rem[MAX_INPUT_LEN * 2] = "0"; // 当前余数
    char temp_quo[MAX_INPUT_LEN * 2] = "";     // 暂存商
    int quo_idx = 0;

    // ==========================================
    // 阶段一：整数长除法 (消化被除数的每一位)
    // ==========================================
    for (int i = 0; abs1[i] != '\0'; i++) {
        // 拼接下一位数字 (如果当前是 "0"，直接覆盖)
        int len = strlen(current_rem);
        if (strcmp(current_rem, "0") == 0) len = 0;
        current_rem[len] = abs1[i];
        current_rem[len + 1] = '\0';

        int count = 0;
        char next_rem[MAX_INPUT_LEN * 2];
        // 只要够减，就一直减
        while (bigint_abs_compare(current_rem, abs2) >= 0) {
            bigint_abs_sub(current_rem, abs2, next_rem);
            strcpy(current_rem, next_rem);
            count++;
        }
        temp_quo[quo_idx++] = count + '0';
    }
    temp_quo[quo_idx] = '\0';

    // 格式化整数商 (去除前导零)
    char *p_quo = temp_quo;
    while (*p_quo == '0' && *(p_quo + 1) != '\0') p_quo++;
    if (temp_quo[0] == '\0') {
        strcpy(temp_quo, "0"); // 如果结果为空，说明是0
        p_quo = temp_quo;
    }

    // 组装最终结果的整数部分
    int k = 0;
    // 只有当商不为 0 或者后续有小数时，才加上负号，防止出现 "-0"
    if (is_negative && (strcmp(p_quo, "0") != 0 || strcmp(current_rem, "0") != 0)) {
        result[k++] = '-';
    }
    strcpy(result + k, p_quo);
    k += strlen(p_quo);

    // ==========================================
    // 阶段二：小数扩展计算 (如果还有余数，且要求精度 > 0)
    // ==========================================
    if (strcmp(current_rem, "0") != 0 && precision > 0) {
        result[k++] = '.'; // 点上小数点
        
        for (int i = 0; i < precision; i++) {
            // 拼接 '0' (余数乘 10)
            strcat(current_rem, "0");

            int count = 0;
            char next_rem[MAX_INPUT_LEN * 2];
            while (bigint_abs_compare(current_rem, abs2) >= 0) {
                bigint_abs_sub(current_rem, abs2, next_rem);
                strcpy(current_rem, next_rem);
                count++;
            }
            result[k++] = count + '0';

            // 如果某一步余数为 0，说明除尽了，提前结束
            if (strcmp(current_rem, "0") == 0) {
                break;
            }
        }
    }
    
    result[k] = '\0'; // 封口字符串
}




/* ============================================================
 * 5. 交互模式与主函数
 * ============================================================ */

/**
 * 程序主函数
 * 根据命令行参数判断运行模式：
 * - 有参数：命令行模式，计算后输出结果并退出
 * - 无参数：交互模式，持续接收用户输入
 */
int main(int argc, char *argv[]) {
    int precision = 6; // 默认精度
    int arg_idx = 1;

    // 解析 -p 或 --precision 选项
    if (argc >= 3 && (strcmp(argv[1], "-p") == 0 || strcmp(argv[1], "--precision") == 0)) {
        char *endptr;
        errno = 0;
        long p = strtol(argv[2], &endptr, 10);
        
        // 检查输入是否完全是数字，以及是否发生溢出
        if (errno == ERANGE || *endptr != '\0' || p < 0) {
            fprintf(stderr, "Error: Invalid precision value. It must be a non-negative integer.\n");
            return 1;
        }
        
        // 限制最大精度，避免内部数组 current_rem 等溢出MAX_INPUT_LEN
        // 当前大数除法计算缓冲区容量是 MAX_INPUT_LEN * 2 (即 2048)
        // 留出一定空间给初始数字和除法逻辑
        if (p > MAX_INPUT_LEN) {
            fprintf(stderr, "Error: Precision too large. Maximum allowed is %d.\n", MAX_INPUT_LEN);
            return 1;
        }
        
        precision = (int)p;
        arg_idx = 3;
    }

    if (arg_idx < argc) {
        // 有表达式参数，进入命令行模式
        run_cli_mode(argc - arg_idx, argv + arg_idx, precision);
    } else {
        // 无表达式参数，进入交互模式
        run_interactive_mode(precision);
    }
    return 0;
}

/**
 * 命令行模式实现
 * 将命令行参数拼接成表达式字符串，计算并输出结果
 * 
 * @param argc 命令行参数个数
 * @param argv 命令行参数数组
 * @param precision 保留的小数位数
 */
void run_cli_mode(int argc, char *argv[], int precision) {
    char expr[MAX_INPUT_LEN] = {0};
    
    // 将所有参数拼接成一个完整的表达式字符串
    for (int i = 0; i < argc; ++i) {
        strncat(expr, argv[i], MAX_INPUT_LEN - strlen(expr) - 1);
        if (i < argc - 1) {
            strncat(expr, " ", MAX_INPUT_LEN - strlen(expr) - 1);
        }
    }

    CalcResult res = evaluate_expression(expr, precision);
    print_result(expr, res);
}

/**
 * 交互模式实现
 * 持续接收用户输入，逐行计算并输出结果，直到用户输入 "quit" 或 EOF
 */
void run_interactive_mode(int precision) {
    char input[MAX_INPUT_LEN];

    while (1) {
        printf("> "); // 命令提示符
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;  // EOF
        }

        // 去除末尾换行符
        input[strcspn(input, "\n")] = 0;

        // 检查退出指令
        if (strcmp(input, "quit") == 0) {
            break;
        }

        // 检查修改精度的指令: 支持 "-p <n>"
        if (strncmp(input, "-p ", 3) == 0) {
            
            const char *num_part = input + 3;
            
            char *endptr;
            errno = 0;
            long p = strtol(num_part, &endptr, 10);
            
            // 跳过可能跟随的空格
            while (*endptr != '\0' && isspace(*endptr)) endptr++;
            
            if (errno == ERANGE || *endptr != '\0' || p < 0) {
                printf("Error: Invalid precision value. It must be a non-negative integer.\n");
            } else if (p > MAX_INPUT_LEN) {
                printf("Error: Precision too large. Maximum allowed is %d.\n", MAX_INPUT_LEN);
            } else {
                precision = (int)p;
                printf("Precision set to %d\n", precision);
            }
            continue;
        }
        
        // 忽略空输入
        if (strlen(input) == 0) continue;

        CalcResult res = evaluate_expression(input, precision);
        
        // 交互模式下通常只输出结果或错误
        if (res.err == SUCCESS) {
            printf("%s\n", res.result);  // 输出字符串形式的大数结果
        } else {
            print_result(input, res); // 复用错误打印逻辑
        }
    }
}

/* ============================================================
 * 4. 表达式解析与核心计算逻辑
 * ============================================================ */

/**
 * 表达式计算核心函数（支持大数运算）
 * 解析输入表达式并使用 BigInt 库进行计算
 * 
 * @param expr 待计算的表达式字符串（格式：\"num1 op num2\"）
 * @return 包含计算结果或错误信息的 CalcResult 结构体
 */
// 工具 1：提取整数部分并计算小数位数
void extract_decimal(const char *input, char *out_str, int *scale) {
    char *dot = strchr(input, '.');
    if (!dot) {
        strcpy(out_str, input);
        
        *scale = 0;
    } else {
        int int_len = dot - input;
        strncpy(out_str, input, int_len);
        out_str[int_len] = '\0';
        strcat(out_str, dot + 1);
        *scale = strlen(dot + 1);
    }
}

// 工具 2：在结果字符串倒数第 N 位插入小数点
void insert_decimal(char *str, int scale) {
    if (scale <= 0) return;
    
    int len = strlen(str);
    int is_negative = (str[0] == '-');
    int num_len = is_negative ? len - 1 : len;
    
    // 安全检查，防止大 scale 溢出
    if (scale > MAX_INPUT_LEN) return;

    char temp[MAX_INPUT_LEN * 2] = {0};
    int temp_idx = 0;
    
    if (is_negative) temp[temp_idx++] = '-';
    
    if (num_len <= scale) {
        temp[temp_idx++] = '0';
        temp[temp_idx++] = '.';
        for (int i = 0; i < scale - num_len; i++) {
            temp[temp_idx++] = '0';
        }
        strcpy(temp + temp_idx, str + (is_negative ? 1 : 0));
    } else {
        int insert_pos = len - scale;
        strncpy(temp, str, insert_pos);
        temp[insert_pos] = '.';
        strcpy(temp + insert_pos + 1, str + insert_pos);
    }
    
    if (strchr(temp, '.')) {
        int final_len = strlen(temp);
        while (final_len > 0 && temp[final_len - 1] == '0') final_len--;
        if (final_len > 0 && temp[final_len - 1] == '.') final_len--;
        temp[final_len] = '\0';
    }
    
    strcpy(str, temp);
}

CalcResult evaluate_expression(const char *expr, int precision) {
    CalcResult res;
    strcpy(res.result, "");  // 初始化空字符串
    res.err = SUCCESS;
    
    char num1[MAX_BIGINT_LEN] = {0};
    char num2[MAX_BIGINT_LEN] = {0};
    char op = 0;

    // 1. 解析表达式为两个大数和一个运算符
    if (!parse_basic_expression(expr, num1, &op, num2)) {
        res.err = ERR_INVALID_INPUT;
        return res;
    }

    // 2. 剥离小数点并准备参数
    char int1[MAX_INPUT_LEN * 2], int2[MAX_INPUT_LEN * 2];
    int scale1, scale2;
    extract_decimal(num1, int1, &scale1);
    extract_decimal(num2, int2, &scale2);

    // 3. 执行包含小数逻辑的运算
    if (op == '+' || op == '-') {
        int max_scale = (scale1 > scale2) ? scale1 : scale2;
        while (scale1 < max_scale) { strcat(int1, "0"); scale1++; }
        while (scale2 < max_scale) { strcat(int2, "0"); scale2++; }
        
        if (op == '+') bigint_add(int1, int2, res.result);
        else bigint_sub(int1, int2, res.result);
        
        insert_decimal(res.result, max_scale);
        
    } else if (op == '*') {
        bigint_mul(int1, int2, res.result);
        insert_decimal(res.result, scale1 + scale2);
        
    } else if (op == '/') {
        int max_scale = (scale1 > scale2) ? scale1 : scale2;
        while (scale1 < max_scale) { strcat(int1, "0"); scale1++; }
        while (scale2 < max_scale) { strcat(int2, "0"); scale2++; }
        
        // 传入指定的精度
        bigint_div(int1, int2, res.result, precision, &res.err); 
    } else {
        res.err = ERR_UNSUPPORTED_OP;
    }

    return res;
}

/**
 * 基础表达式解析函数（支持大数字符串）
 * 将形如 "a op b" 的字符串解析为两个数字字符串和一个运算符
 * 支持的运算符：+ - * /
 * 支持负数：例如 "-123 + 456" 或 "789 * -100"
 *
 * @param expr  输入表达式字符串
 * @param num1  解析得到的第一个数字输出缓冲区（MAX_BIGINT_LEN 长度）
 * @param op    解析得到的运算符指针
 * @param num2  解析得到的第二个数字输出缓冲区（MAX_BIGINT_LEN 长度）
 * @return 解析成功返回 true，否则返回 false
 */
bool parse_basic_expression(const char *expr, char *num1, char *op, char *num2) {
    // 跳过前导空白
    while (*expr && isspace(*expr)) expr++;
    
    // 解析第一个数字（支持负号）
    int num1_len = 0;
    if (*expr == '-') {
        num1[num1_len++] = '-';
        expr++;
    } else if (*expr == '+') {
        expr++;
    }
    
    // 检查是否有数字部分（允许小数点）
    if (!isdigit(*expr) && *expr != '.') return false;
    
    while (isdigit(*expr) || *expr == '.') {
        num1[num1_len++] = *expr++;
    }
    num1[num1_len] = '\0';
    
    // 跳过运算符前的空白
    while (*expr && isspace(*expr)) expr++;
    
    // 检查运算符
    if (!*expr || !strchr("+-*/", *expr)) {
        return false;
    }
    *op = *expr++;
    
    // 跳过运算符后的空白
    while (*expr && isspace(*expr)) expr++;
    
    // 解析第二个数字（支持负号）
    int num2_len = 0;
    if (*expr == '-') {
        num2[num2_len++] = '-';
        expr++;
    } else if (*expr == '+') {
        expr++;
    }
    
    // 检查是否有数字部分（允许小数点）
    if (!isdigit(*expr) && *expr != '.') return false;
    
    while (isdigit(*expr) || *expr == '.') {
        num2[num2_len++] = *expr++;
    }
    num2[num2_len] = '\0';
    
    // 跳过末尾空白
    while (*expr && isspace(*expr)) expr++;
    
    // 检查是否已读取所有有效字符
    return (*expr == '\0');
}

/**
 * 结果输出与错误处理函数
 * 根据计算结果的错误代码输出相应的信息（支持大数结果显示）
 *
 * @param expr 原始表达式字符串（用于成功时的显示）
 * @param res  计算结果结构体（包含字符串形式的大数结果）
 */
void print_result(const char *expr, CalcResult res) {
    switch (res.err) {
        case SUCCESS:
            printf("%s = %s\n", expr, res.result);  // 输出字符串形式的大数
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