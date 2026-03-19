#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <errno.h>

/* ============================================================
 * 1. 宏定义与结构体
 * ============================================================ */

#define MAX_BIGINT_LEN 2048

// 错误代码枚举：统一管理所有可能的错误类型
typedef enum {
    SUCCESS = 0,           // 计算成功
    ERR_DIV_BY_ZERO,       // 除数为零错误
    ERR_INVALID_INPUT,     // 输入格式无效
    ERR_INPUT_TOO_LONG,    // 输入过长/缓冲区容量不足
    ERR_UNSUPPORTED_OP     // 不支持的运算符
} ErrorCode;

/* ============================================================
 * 新增: 词法与语法分析器数据结构 (Lexer & Parser)
 * ============================================================ */
typedef enum {
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MUL,
    TOKEN_DIV,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_EOF,
    TOKEN_ERROR
} TokenType;

typedef struct {
    TokenType type;
    char value[MAX_BIGINT_LEN]; 
} Token;

#define MAX_STACK_SIZE 100

typedef struct {
    char items[MAX_STACK_SIZE][MAX_BIGINT_LEN];
    int top;
} ValueStack;

typedef struct {
    char items[MAX_STACK_SIZE];
    int top;
} OpStack;

static void init_v_stack(ValueStack *s) { s->top = -1; }
static void init_o_stack(OpStack *s) { s->top = -1; }

static ErrorCode push_v(ValueStack *s, const char *val) {
    if (s->top >= MAX_STACK_SIZE - 1) return ERR_INPUT_TOO_LONG; // 严格检查栈溢出
    s->top++;
    strncpy(s->items[s->top], val, MAX_BIGINT_LEN - 1);
    s->items[s->top][MAX_BIGINT_LEN - 1] = '\0';
    return SUCCESS;
}

static ErrorCode pop_v(ValueStack *s, char *out) {
    if (s->top < 0) return ERR_INVALID_INPUT;
    strcpy(out, s->items[s->top]);
    s->top--;
    return SUCCESS;
}

static ErrorCode push_o(OpStack *s, char op) {
    if (s->top >= MAX_STACK_SIZE - 1) return ERR_INPUT_TOO_LONG; // 严格检查栈溢出
    s->top++;
    s->items[s->top] = op;
    return SUCCESS;
}

static ErrorCode pop_o(OpStack *s, char *op) {
    if (s->top < 0) return ERR_INVALID_INPUT;
    *op = s->items[s->top];
    s->top--;
    return SUCCESS;
}

static char peek_o(OpStack *s) {
    if (s->top < 0) return '\0';
    return s->items[s->top];
}

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
ErrorCode parse_basic_expression(const char *expr, char *num1, char *op, char *num2);  // 基础表达式解析（支持大数字符串）

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
 * 2.1 内部工具函数（固定缓冲区安全拼接/规范化）
 * ============================================================ */

static bool append_char(char *dst, size_t cap, char c) {
    size_t len = strlen(dst);
    if (len + 1 >= cap) return false;
    dst[len] = c;
    dst[len + 1] = '\0';
    return true;
}

static bool append_zeros(char *dst, size_t cap, int count) {
    if (count <= 0) return true;
    size_t len = strlen(dst);
    if (len + (size_t)count >= cap) return false;
    memset(dst + len, '0', (size_t)count);
    dst[len + (size_t)count] = '\0';
    return true;
}

static bool is_ascii_digit(char c) {
    return (c >= '0' && c <= '9');
}

static bool is_all_zeros_number(const char *s) {
    if (*s == '-') s++;
    bool has_digit = false;
    while (*s) {
        if (*s == '.') { s++; continue; }
        if (*s >= '0' && *s <= '9') {
            has_digit = true;
            if (*s != '0') return false;
            s++;
            continue;
        }
        return false;
    }
    return has_digit;
}

// 前置声明：用于格式化与除法进位
static bool increment_result_integer(char *result, size_t cap);

// 严格解析数字，规则：最多一个点，且点两边都有数字
static bool parse_number_strict(const char **p, char *out, size_t cap) {
    size_t idx = 0;
    int int_digits = 0;
    int frac_digits = 0;

    while (**p && is_ascii_digit(**p)) {
        if (idx + 1 >= cap) return false;
        out[idx++] = **p;
        (*p)++;
        int_digits++;
    }
    if (int_digits == 0) return false;

    if (**p == '.') {
        if (idx + 1 >= cap) return false;
        out[idx++] = **p;
        (*p)++;

        while (**p && is_ascii_digit(**p)) {
            if (idx + 1 >= cap) return false;
            out[idx++] = **p;
            (*p)++;
            frac_digits++;
        }
        if (frac_digits == 0) return false;
    }

    out[idx] = '\0';
    return true;
}

// 解析并展开科学计数法（方案 A：输入支持，输出不使用科学计数法）
// 规则（严格一致）：
// - mantissa 必须符合 parse_number_strict（digits 或 digits.digits，点两边都有数字）
// - 可选指数部分： [e|E][+-]?digits（至少一位数字）
// - token 内不允许空格
// 输出：展开后的普通十进制字符串（可带 '-'、可带 '.'）
static ErrorCode parse_number_token(const char **p, int is_negative, char *out, size_t cap) {
    const char *cur = *p;

    char mantissa[MAX_BIGINT_LEN];
    if (!parse_number_strict(&cur, mantissa, sizeof(mantissa))) {
        return ERR_INVALID_INPUT;
    }

    // 解析可选指数
    long exp = 0;
    int exp_sign = 1;
    bool has_exp = false;

    if (*cur == 'e' || *cur == 'E') {
        has_exp = true;
        cur++;
        if (*cur == '+') { exp_sign = 1; cur++; }
        else if (*cur == '-') { exp_sign = -1; cur++; }

        if (!is_ascii_digit(*cur)) return ERR_INVALID_INPUT;

        // 累积指数，并在超过上限时提前拒绝
        while (is_ascii_digit(*cur)) {
            int d = *cur - '0';
            if (exp > (MAX_BIGINT_LEN - d) / 10) return ERR_INPUT_TOO_LONG;
            exp = exp * 10 + d;
            cur++;
        }
        exp *= exp_sign;

        // 展开会导致补 0 非常多时，直接判为过长
        if (exp > MAX_BIGINT_LEN || exp < -MAX_BIGINT_LEN) return ERR_INPUT_TOO_LONG;
    }

    // mantissa -> digits + frac_len
    char digits[MAX_BIGINT_LEN];
    int frac_len = 0;
    size_t di = 0;
    for (size_t i = 0; mantissa[i] != '\0'; i++) {
        if (mantissa[i] == '.') continue;
        if (di + 1 >= sizeof(digits)) return ERR_INPUT_TOO_LONG;
        digits[di++] = mantissa[i];
    }
    digits[di] = '\0';

    const char *dot = strchr(mantissa, '.');
    if (dot) frac_len = (int)strlen(dot + 1);

    // 如果 mantissa 全 0，结果就是 0（避免生成一堆 0）
    if (is_all_zeros_number(mantissa)) {
        if (cap < 2) return ERR_INPUT_TOO_LONG;
        out[0] = '0';
        out[1] = '\0';
        *p = cur;
        return SUCCESS;
    }

    long scale = (long)frac_len - (has_exp ? exp : 0); // 最终小数位数

    char tmp[MAX_BIGINT_LEN];
    tmp[0] = '\0';
    if (is_negative) {
        if (!append_char(tmp, sizeof(tmp), '-')) return ERR_INPUT_TOO_LONG;
    }

    // 生成展开后的普通十进制
    size_t digits_len = strlen(digits);
    if (scale <= 0) {
        // 小数点右移：digits 后补 0
        if (strlen(tmp) + digits_len + (size_t)(-scale) + 1 > sizeof(tmp)) return ERR_INPUT_TOO_LONG;
        strncat(tmp, digits, sizeof(tmp) - strlen(tmp) - 1);
        if (!append_zeros(tmp, sizeof(tmp), (int)(-scale))) return ERR_INPUT_TOO_LONG;
    } else {
        // 小数点左移：在 digits 倒数 scale 位插入
        long pos = (long)digits_len - scale;
        if (pos > 0) {
            // 例如 12345, scale=2 => 123.45
            if (strlen(tmp) + digits_len + 2 > sizeof(tmp)) return ERR_INPUT_TOO_LONG;
            strncat(tmp, digits, (size_t)pos);
            if (!append_char(tmp, sizeof(tmp), '.')) return ERR_INPUT_TOO_LONG;
            strncat(tmp, digits + pos, sizeof(tmp) - strlen(tmp) - 1);
        } else {
            // 例如 123, scale=5 => 0.00123
            if (!append_char(tmp, sizeof(tmp), '0')) return ERR_INPUT_TOO_LONG;
            if (!append_char(tmp, sizeof(tmp), '.')) return ERR_INPUT_TOO_LONG;
            if (!append_zeros(tmp, sizeof(tmp), (int)(-pos))) return ERR_INPUT_TOO_LONG;
            if (strlen(tmp) + digits_len + 1 > sizeof(tmp)) return ERR_INPUT_TOO_LONG;
            strncat(tmp, digits, sizeof(tmp) - strlen(tmp) - 1);
        }
    }

    // 写回 out
    size_t tlen = strlen(tmp);
    if (tlen + 1 > cap) return ERR_INPUT_TOO_LONG;
    memcpy(out, tmp, tlen + 1);

    *p = cur;
    return SUCCESS;
}

// 固定精度输出：四舍五入（half-up）到 precision 位，并补足尾随 0
// 约定：precision >= 0；输入 s 是十进制字符串（可带 '-'、可带 '.'）
static ErrorCode format_fixed_precision(char *s, size_t cap, int precision) {
    if (precision < 0) return ERR_INVALID_INPUT;

    // 全 0 直接归一
    if (is_all_zeros_number(s)) {
        if (precision == 0) {
            if (cap < 2) return ERR_INPUT_TOO_LONG;
            strcpy(s, "0");
            return SUCCESS;
        }
        // "0." + precision 个 0
        if (cap < (size_t)(2 + precision + 1)) return ERR_INPUT_TOO_LONG;
        s[0] = '0';
        s[1] = '.';
        for (int i = 0; i < precision; i++) s[2 + i] = '0';
        s[2 + precision] = '\0';
        return SUCCESS;
    }

    int neg = (s[0] == '-');
    char *p = s + (neg ? 1 : 0);

    // 先去掉整数部分前导 0（不动小数尾 0）
    char *dot = strchr(p, '.');
    char *int_end = dot ? dot : (p + strlen(p));
    while (p + 1 < int_end && *p == '0') {
        memmove(p, p + 1, strlen(p + 1) + 1);
        dot = strchr(p, '.');
        int_end = dot ? dot : (p + strlen(p));
    }

    // 确保存在 '.'（当 precision > 0 时）
    if (precision > 0 && !dot) {
        size_t len = strlen(s);
        if (len + 1 >= cap) return ERR_INPUT_TOO_LONG;
        s[len] = '.';
        s[len + 1] = '\0';
        dot = strchr(p, '.');
    }

    // 计算当前小数位数
    dot = strchr(p, '.');
    int frac_len = dot ? (int)strlen(dot + 1) : 0;

    // precision==0：看第一位小数决定是否进位，然后去掉小数点及后面
    if (precision == 0) {
        int round_digit = 0;
        if (dot && frac_len > 0) round_digit = dot[1] - '0';
        if (round_digit >= 5) {
            if (!increment_result_integer(s, cap)) return ERR_INPUT_TOO_LONG;
        }
        if (dot) *dot = '\0';
        // 消除可能产生的 "-0"
        if (strcmp(s, "-0") == 0) strcpy(s, "0");
        return SUCCESS;
    }

    // 小数位不足：补 0 到 precision+1（为了统一后面取 round_digit 的逻辑）
    if (frac_len < precision + 1) {
        size_t len = strlen(s);
        int need = (precision + 1) - frac_len;
        if (len + (size_t)need >= cap) return ERR_INPUT_TOO_LONG;
        for (int i = 0; i < need; i++) s[len + i] = '0';
        s[len + need] = '\0';
        dot = strchr(p, '.');
        frac_len = (int)strlen(dot + 1);
    }

    // 此时 frac_len >= precision+1，round_digit 就是第 precision+1 位
    dot = strchr(p, '.');
    char *frac = dot + 1;
    int round_digit = frac[precision] - '0';

    // 先截断到 precision 位（保留一位 round_digit 之前的位）
    frac[precision] = '\0';

    if (round_digit >= 5) {
        int carry = 1;
        // 从小数最后一位向前进位
        for (int i = precision - 1; i >= 0 && carry; i--) {
            if (frac[i] < '9') { frac[i] = (char)(frac[i] + 1); carry = 0; }
            else { frac[i] = '0'; }
        }
        if (carry) {
            // 小数全 9，进位到整数
            *dot = '\0'; // 暂时去掉小数点
            if (!increment_result_integer(s, cap)) return ERR_INPUT_TOO_LONG;
            // 重新加回小数点与 precision 个 0
            size_t len = strlen(s);
            if (len + 1 + (size_t)precision >= cap) return ERR_INPUT_TOO_LONG;
            s[len] = '.';
            for (int i = 0; i < precision; i++) s[len + 1 + i] = '0';
            s[len + 1 + precision] = '\0';
            return SUCCESS;
        }
    }

    // 补足到 precision 位（因为前面可能截断/或本来就不足）
    dot = strchr(p, '.');
    frac = dot + 1;
    int now = (int)strlen(frac);
    if (now < precision) {
        size_t len = strlen(s);
        int need = precision - now;
        if (len + (size_t)need >= cap) return ERR_INPUT_TOO_LONG;
        for (int i = 0; i < need; i++) s[len + i] = '0';
        s[len + need] = '\0';
    }

    return SUCCESS;
}

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
    char inverted_num2[MAX_BIGINT_LEN];

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

// 内部工具：无符号数字字符串乘以 0..9 的单个数字
static void bigint_abs_mul_digit(const char *num, int digit, char *out) {
    if (digit <= 0) {
        strcpy(out, "0");
        return;
    }
    if (digit == 1) {
        strcpy(out, num);
        return;
    }
    int len = (int)strlen(num);
    int carry = 0;
    int k = 0;
    for (int i = len - 1; i >= 0; i--) {
        int v = (num[i] - '0') * digit + carry;
        out[k++] = (char)('0' + (v % 10));
        carry = v / 10;
    }
    while (carry > 0) {
        out[k++] = (char)('0' + (carry % 10));
        carry /= 10;
    }
    out[k] = '\0';
    reverse_string(out);
    remove_leading_zeros(out);
}

// 内部工具：对余数执行一次“乘10取一位商”的除法步进
// 返回：0..9 的当前位商；失败返回 -1（通常是缓冲区不足）
static int div_step(char *rem, size_t rem_cap, const char *divisor) {
    if (!append_char(rem, rem_cap, '0')) return -1;

    int lo = 0, hi = 9, best = 0;
    char prod[MAX_BIGINT_LEN * 2];
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        bigint_abs_mul_digit(divisor, mid, prod);
        int cmp = bigint_abs_compare(rem, prod);
        if (cmp >= 0) { best = mid; lo = mid + 1; }
        else { hi = mid - 1; }
    }

    if (best > 0) {
        char next_rem[MAX_BIGINT_LEN * 2];
        bigint_abs_mul_digit(divisor, best, prod);
        bigint_abs_sub(rem, prod, next_rem);
        strcpy(rem, next_rem);
    } else {
        remove_leading_zeros(rem);
    }
    return best;
}

// 内部工具：将 result（可能带 '-'）的整数部分 +1（按绝对值进位）
static bool increment_result_integer(char *result, size_t cap) {
    size_t len = strlen(result);
    if (len == 0) return false;

    int neg = (result[0] == '-');
    char *start = result + (neg ? 1 : 0);
    size_t start_idx = (size_t)(start - result);

    // 从末尾向前进位
    for (ssize_t i = (ssize_t)len - 1; i >= (ssize_t)start_idx; i--) {
        if (result[i] < '0' || result[i] > '9') return false;
        if (result[i] < '9') {
            result[i] = (char)(result[i] + 1);
            return true;
        }
        result[i] = '0';
    }

    // 产生了新的最高位 1，需要插入
    if (len + 1 >= cap) return false;
    if (neg) {
        memmove(result + 2, result + 1, len - 0); // 包含 '\0'
        result[1] = '1';
    } else {
        memmove(result + 1, result, len + 1);
        result[0] = '1';
    }
    return true;
}

// 统一的大数除法：同时支持整数计算与高精度小数扩展
void bigint_div(const char *num1, const char *num2, char *result, int precision, ErrorCode *err) {
    // 0. 错误拦截：除数不能为 0
    if (is_all_zeros_number(num2)) {
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
    char current_rem[MAX_BIGINT_LEN * 2] = "0"; // 当前余数
    char temp_quo[MAX_BIGINT_LEN * 2] = "";     // 暂存商
    int quo_idx = 0;

    // ==========================================
    // 阶段一：整数长除法 (消化被除数的每一位)
    // ==========================================
    for (int i = 0; abs1[i] != '\0'; i++) {
        // 拼接下一位数字 (如果当前是 "0"，直接覆盖)
        if (strcmp(current_rem, "0") == 0) current_rem[0] = '\0';
        if (!append_char(current_rem, sizeof(current_rem), abs1[i])) {
            *err = ERR_INPUT_TOO_LONG;
            return;
        }

        // 试商（0..9 二分），避免连减
        int lo = 0, hi = 9, best = 0;
        char prod[MAX_BIGINT_LEN * 2];
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            bigint_abs_mul_digit(abs2, mid, prod);
            int cmp = bigint_abs_compare(current_rem, prod);
            if (cmp >= 0) { best = mid; lo = mid + 1; }
            else { hi = mid - 1; }
        }
        if (best > 0) {
            char next_rem[MAX_BIGINT_LEN * 2];
            bigint_abs_mul_digit(abs2, best, prod);
            bigint_abs_sub(current_rem, prod, next_rem);
            strcpy(current_rem, next_rem);
        } else {
            remove_leading_zeros(current_rem);
        }
        temp_quo[quo_idx++] = (char)('0' + best);
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
    // 阶段二：小数扩展计算 + 四舍五入（half-up）
    // ==========================================
    if (precision > 0) {
        int round_digit = 0;
        int wrote = 0;
        char frac[MAX_BIGINT_LEN + 2];

        if (strcmp(current_rem, "0") != 0) {
            for (int i = 0; i < precision; i++) {
                if (strcmp(current_rem, "0") == 0) break;
                int d = div_step(current_rem, sizeof(current_rem), abs2);
                if (d < 0) { *err = ERR_INPUT_TOO_LONG; return; }
                frac[wrote++] = (char)('0' + d);
            }

            // 额外算一位用于四舍五入
            if (strcmp(current_rem, "0") != 0) {
                int d = div_step(current_rem, sizeof(current_rem), abs2);
                if (d < 0) { *err = ERR_INPUT_TOO_LONG; return; }
                round_digit = d;
            }
        }

        if (round_digit >= 5) {
            int carry = 1;
            for (int i = wrote - 1; i >= 0 && carry; i--) {
                if (frac[i] < '9') { frac[i] = (char)(frac[i] + 1); carry = 0; }
                else { frac[i] = '0'; }
            }
            if (carry) {
                if (!increment_result_integer(result, MAX_BIGINT_LEN)) {
                    *err = ERR_INPUT_TOO_LONG;
                    return;
                }
            }
        }

        if (wrote > 0) {
            result[k++] = '.';
            for (int i = 0; i < wrote; i++) result[k++] = frac[i];
        }
    } else if (precision == 0 && strcmp(current_rem, "0") != 0) {
        // precision==0 时：看第一位小数决定是否进位
        int d = div_step(current_rem, sizeof(current_rem), abs2);
        if (d < 0) { *err = ERR_INPUT_TOO_LONG; return; }
        if (d >= 5) {
            if (!increment_result_integer(result, MAX_BIGINT_LEN)) {
                *err = ERR_INPUT_TOO_LONG;
                return;
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
    if (argc >= 3 && (strcmp(argv[1], "-p") == 0)) {
        char *endptr;
        errno = 0;
        long p = strtol(argv[2], &endptr, 10);
        
        // 检查输入是否完全是数字，以及是否发生溢出
        if (errno == ERANGE) {
            fprintf(stderr, "Error: Precision too large. Maximum allowed is %d.\n", MAX_BIGINT_LEN);
            return 1;
        }
        if (*endptr != '\0' || p < 0) {
            fprintf(stderr, "Error: Invalid precision value. It must be a non-negative integer.\n");
            return 1;
        }
        if (p > MAX_BIGINT_LEN) {
            fprintf(stderr, "Error: Precision too large. Maximum allowed is %d.\n", MAX_BIGINT_LEN);
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
    char expr[MAX_BIGINT_LEN] = {0};
    
    // 将所有参数拼接成一个完整的表达式字符串
    for (int i = 0; i < argc; ++i) {
        strncat(expr, argv[i], MAX_BIGINT_LEN - strlen(expr) - 1);
        if (i < argc - 1) {
            strncat(expr, " ", MAX_BIGINT_LEN - strlen(expr) - 1);
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
    char input[MAX_BIGINT_LEN];

    while (1) {
        printf("> "); // 命令提示符
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;  // EOF
        }

        // 去除末尾换行符
        input[strcspn(input, "\n")] = 0;

        // 1. 跳过所有的前导空格
        char *cmd_ptr = input;
        while (*cmd_ptr && isspace(*cmd_ptr)) cmd_ptr++;

        // 忽略完全为空的输入
        if (strlen(cmd_ptr) == 0) continue;

        // 2. 检查退出指令
        if (strcmp(cmd_ptr, "quit") == 0) {
            break;
        }

        // 3. 进入独立的“系统命令分发器 (Dispatcher)”体系
        if (cmd_ptr[0] == '-') {
            // 解析修改精度的指令 "-p"（支持 "-p2", "-p  2" 等任意带空格格式）
            if (strncmp(cmd_ptr, "-p", 2) == 0) {
                // 指针跳过 "-p" 本身，直指后缀部分
                const char *num_part = cmd_ptr + 2;
                
                // 跳过可能跟随在 "-p" 和数字中间的任意个空格
                while (*num_part != '\0' && isspace(*num_part)) num_part++;
                
                if (*num_part == '\0') {
                    // 如果后面什么都没跟
                    printf("Error: Missing precision value after '-p'.\n");
                    continue;
                }

                char *endptr;
                errno = 0;
                long p = strtol(num_part, &endptr, 10);
                
                // 跳过数字后面可能跟随的无意义空格
                while (*endptr != '\0' && isspace(*endptr)) endptr++;
                
                if (errno == ERANGE) {
                    printf("Error: Precision too large. Maximum allowed is %d.\n", MAX_BIGINT_LEN);
                } else if (*endptr != '\0' || p < 0) {
                    printf("Error: Invalid precision value. It must be a non-negative integer.\n");
                } else if (p > MAX_BIGINT_LEN) {
                    printf("Error: Precision too large. Maximum allowed is %d.\n", MAX_BIGINT_LEN);
                } else {
                    precision = (int)p;
                    printf("Precision set to %d\n", precision);
                }
            } else {
                // 未来扩展：比如输入了 -scale 或者不存在的 -abc
                printf("Error: Unknown command '%s'\n", cmd_ptr);
            }
            // 命令体系不参与后续大数数学计算，直接结束本次轮询
            continue;
        }

        // 4. 数学表达式计算
        CalcResult res = evaluate_expression(cmd_ptr, precision);
        
        // 交互模式下通常只输出结果或错误
        if (res.err == SUCCESS) {
            printf("%s\n", res.result);  // 输出字符串形式的大数结果
        } else {
            print_result(cmd_ptr, res); // 复用错误打印逻辑
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
// 工具 1：提取整数部分并计算小数位数（去掉小数点）
static bool extract_decimal(const char *input, char *out_str, size_t cap, int *scale) {
    const char *dot = strchr(input, '.');
    if (!dot) {
        size_t in_len = strlen(input);
        if (in_len >= cap) return false;
        memcpy(out_str, input, in_len + 1);
        *scale = 0;
        return true;
    }

    size_t int_len = (size_t)(dot - input);
    size_t frac_len = strlen(dot + 1);
    if (int_len + frac_len >= cap) return false;

    memcpy(out_str, input, int_len);
    memcpy(out_str + int_len, dot + 1, frac_len);
    out_str[int_len + frac_len] = '\0';
    *scale = (int)frac_len;
    return true;
}

// 工具 2：在结果字符串倒数第 N 位插入小数点
void insert_decimal(char *str, int scale) {
    if (scale <= 0) return;
    
    int len = strlen(str);
    int is_negative = (str[0] == '-');
    int num_len = is_negative ? len - 1 : len;
    
    // 安全检查，防止大 scale 或结果长度溢出
    if (scale > MAX_BIGINT_LEN) return;

    // 中间缓冲区：按大数上限预留空间
    char temp[MAX_BIGINT_LEN + 4] = {0};
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
        // 数字部分的起始位置（跳过符号）
        int start = is_negative ? 1 : 0;
        // 在数字部分中倒数 scale 位插入小数点
        int insert_pos = start + (num_len - scale);

        strncpy(temp, str, insert_pos);
        temp[insert_pos] = '.';
        strcpy(temp + insert_pos + 1, str + insert_pos);
    }

    strcpy(str, temp);
}

// ==================== LEXER & SHUNTING-YARD PARSER ====================

// 获取操作符优先级
static int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// 词法切词器：按 Token 提取
static Token get_next_token(const char **p, bool expects_unary) {
    Token t;
    t.type = TOKEN_ERROR;
    t.value[0] = '\0';

    // 跳过多余空格
    while (**p && isspace(**p)) (*p)++;

    if (**p == '\0') {
        t.type = TOKEN_EOF;
        return t;
    }

    char c = **p;

    // 解析数字或一元符号
    if (is_ascii_digit(c) || c == '.' || (c == '-' && expects_unary) || (c == '+' && expects_unary)) {
        if (c == '+' && expects_unary) {
            // 不接受显式正号
            return t; 
        }
        int neg = 0;
        const char *start = *p;
        if (c == '-') {
            neg = 1;
            (*p)++;
            // 如果紧接的不是数字或点，那是孤立的减号（不该在一元上下文中，防错）
            if (!is_ascii_digit(**p) && **p != '.') {
                *p = start; // 回退
                t.type = TOKEN_MINUS;
                t.value[0] = '-'; t.value[1] = '\0';
                (*p)++;
                return t;
            }
        } else {
            *p = start; // 恢复位置让 parse_number_token 处理
        }
        
        // 调用底层的底层安全数字解析（科学计数法扩展）
        ErrorCode ec = parse_number_token(p, neg, t.value, MAX_BIGINT_LEN);
        if (ec != SUCCESS) {
            return t; // 错误 token
        }
        t.type = TOKEN_NUMBER;
        return t;
    }

    // 解析普通符号
    (*p)++;
    t.value[0] = c; t.value[1] = '\0';
    switch (c) {
        case '+': t.type = TOKEN_PLUS; break;
        case '-': t.type = TOKEN_MINUS; break;
        case '*': t.type = TOKEN_MUL; break;
        case '/': t.type = TOKEN_DIV; break;
        case '(': t.type = TOKEN_LPAREN; break;
        case ')': t.type = TOKEN_RPAREN; break;
        default: break; // 不认识的符号返回 TOKEN_ERROR
    }
    return t;
}

// 核心套用单个算子
static ErrorCode apply_operator(ValueStack *vals, char op, int precision) {
    char num2[MAX_BIGINT_LEN], num1[MAX_BIGINT_LEN];
    ErrorCode err;
    if ((err = pop_v(vals, num2)) != SUCCESS) return ERR_INVALID_INPUT;
    if ((err = pop_v(vals, num1)) != SUCCESS) return ERR_INVALID_INPUT;

    char int1[MAX_BIGINT_LEN * 2], int2[MAX_BIGINT_LEN * 2];
    int scale1, scale2;
    char result[MAX_BIGINT_LEN] = "0";

    if (!extract_decimal(num1, int1, sizeof(int1), &scale1) ||
        !extract_decimal(num2, int2, sizeof(int2), &scale2)) {
        return ERR_INPUT_TOO_LONG;
    }

    if (op == '+' || op == '-') {
        if (is_all_zeros_number(num1) && is_all_zeros_number(num2)) {
            return push_v(vals, "0");
        }
        int max_scale = (scale1 > scale2) ? scale1 : scale2;
        if (!append_zeros(int1, sizeof(int1), max_scale - scale1) ||
            !append_zeros(int2, sizeof(int2), max_scale - scale2)) {
            return ERR_INPUT_TOO_LONG;
        }
        if (op == '+') bigint_add(int1, int2, result);
        else bigint_sub(int1, int2, result);
        insert_decimal(result, max_scale);

    } else if (op == '*') {
        if (is_all_zeros_number(num1) || is_all_zeros_number(num2)) {
            return push_v(vals, "0");
        }
        bigint_mul(int1, int2, result);
        insert_decimal(result, scale1 + scale2);

    } else if (op == '/') {
        if (is_all_zeros_number(num2)) return ERR_DIV_BY_ZERO;
        if (is_all_zeros_number(num1)) return push_v(vals, "0");
        int max_scale = (scale1 > scale2) ? scale1 : scale2;
        if (!append_zeros(int1, sizeof(int1), max_scale - scale1) ||
            !append_zeros(int2, sizeof(int2), max_scale - scale2)) {
            return ERR_INPUT_TOO_LONG;
        }
        ErrorCode div_err;
        bigint_div(int1, int2, result, precision, &div_err);
        if (div_err != SUCCESS) return div_err;

    } else {
        return ERR_UNSUPPORTED_OP;
    }

    ErrorCode format_err = format_fixed_precision(result, sizeof(result), precision);
    if (format_err != SUCCESS) return format_err;
    return push_v(vals, result);
}

// 调度场算法主控
CalcResult evaluate_expression(const char *expr, int precision) {
    CalcResult res;
    strcpy(res.result, "");
    res.err = SUCCESS;

    ValueStack v_stack; init_v_stack(&v_stack);
    OpStack o_stack; init_o_stack(&o_stack);

    bool expects_unary = true; // 起始一定期待数字或一元符号
    const char *p = expr;

    while (1) {
        Token t = get_next_token(&p, expects_unary);
        if (t.type == TOKEN_ERROR) {
            res.err = ERR_INVALID_INPUT;
            return res;
        }
        if (t.type == TOKEN_EOF) {
            break;
        }

        if (t.type == TOKEN_NUMBER) {
            if ((res.err = push_v(&v_stack, t.value)) != SUCCESS) return res;
            expects_unary = false; 
        } 
        else if (t.type == TOKEN_LPAREN) {
            if ((res.err = push_o(&o_stack, '(')) != SUCCESS) return res;
            expects_unary = true;
        } 
        else if (t.type == TOKEN_RPAREN) {
            while (peek_o(&o_stack) != '(') {
                if (peek_o(&o_stack) == '\0') {
                    res.err = ERR_INVALID_INPUT; // 括号不匹配
                    return res;
                }
                char op; pop_o(&o_stack, &op);
                if ((res.err = apply_operator(&v_stack, op, precision)) != SUCCESS) return res;
            }
            char scrap; pop_o(&o_stack, &scrap); // 弹出 '('
            expects_unary = false; // 右括号后面不应该立刻跟一元符号（除非遇到下一个运算符）
        } 
        else { // 四则运算符
            // 巧妙处理独立一元减号（例如 "-(2+3)" 被剥离为 "-1 * (2+3)"）
            // 这样能完美在双栈调度场中保留乘法的优先级
            if (expects_unary && t.value[0] == '-') {
                if ((res.err = push_v(&v_stack, "-1")) != SUCCESS) return res;
                t.value[0] = '*'; // 把这一个减号 Token 继续扮演成乘号参与循环
            } else if (expects_unary && t.value[0] == '+') {
                res.err = ERR_INVALID_INPUT; // 不接受显式正号
                return res;
            }

            while (peek_o(&o_stack) != '\0' && peek_o(&o_stack) != '(' &&
                   precedence(peek_o(&o_stack)) >= precedence(t.value[0])) {
                char op; pop_o(&o_stack, &op);
                if ((res.err = apply_operator(&v_stack, op, precision)) != SUCCESS) return res;
            }
            if ((res.err = push_o(&o_stack, t.value[0])) != SUCCESS) return res;
            expects_unary = true; // 符号之后必须有数字或一元符号
        }
    }

    // 清空堆栈里剩下的符号
    while (peek_o(&o_stack) != '\0') {
        char op; pop_o(&o_stack, &op);
        if (op == '(') {
            res.err = ERR_INVALID_INPUT; // 不匹配的括号（左括号多余）
            return res;
        }
        if ((res.err = apply_operator(&v_stack, op, precision)) != SUCCESS) return res;
    }

    // 安全检查，值栈内只能剩下一个最终结果
    if (v_stack.top != 0) { 
        res.err = ERR_INVALID_INPUT; // 数字太多没算完（比如输入 "5 5"）
        return res;
    }

    pop_v(&v_stack, res.result);
    return res;
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
        case ERR_INPUT_TOO_LONG:
            printf("Error: Input is too long.\n");
            break;
        case ERR_UNSUPPORTED_OP:
            printf("Unsupported operation.\n");
            break;
    }
}