# Simple Calculator using C

本文档主要详解如何为计算器增加**小数计算（decimal）**的功能，以及如何让用户**手动指定保留精度（manual precision）**。我们将逐行拆解这部分的修改代码，一步步讲解给 C 语言新手听。

## 1. Basic function (基础功能扩展)

### 1.4 decimal (小数提取与组装)
因为我们用的是纯字符数组来实现的超大数计算（BigInt），它天然只认识加减乘除里的数字（不认识小数点）。要让程序支持浮点数，我们的思路是：**先拔掉小数点！**，假装它是个超大的整数去底层算，算完拿到整数形态的结果后，再**重新把小数点插回去！**

为此，我们需要两个工具函数。

**提取小数点 `extract_decimal`:**
```c
// out_str 是负责接盘纯数字串的盒子，scale 是负责记住小数点后面有几位的变量
void extract_decimal(const char *input, char *out_str, int *scale) {
    // 语法：strchr 用于在字符串(input)中找字符(.)首次出现的位置。找不到就返回 NULL(即0)
    char *dot = strchr(input, '.');
    if (!dot) { 
        // 如果没找到小数点，那这就直接是一个整数
        strcpy(out_str, input); // 原封不动搬运过去
        *scale = 0; // 小数位数为 0
    } else {
        // 如果找到了！比如 "123.45"，指针dot就停在 '.' 的位置
        int int_len = dot - input;     // 两个指针相减，绝妙地算出了前面整数部分的长度 (即"123"的长度，3)
        
        // 提走整数部分
        // strncpy 拷贝前 n 个字符。拷贝完了别忘了手动在结尾加个 '\0' 封口，否则电脑不知道字符串在哪结束！
        strncpy(out_str, input, int_len);
        out_str[int_len] = '\0';
        
        // 提走小数部分，紧紧粘在刚刚提出来的整数后面
        strcat(out_str, dot + 1);      // 把小数点后面的字符("45")串联在out_str末尾。结果变成了 "12345"
        
        // 记住小数刻度位数
        *scale = strlen(dot + 1);      // 测量一下小数点后面("45")有多长，存入scale(记录为2)
    }
}
```

**插入回小数点 `insert_decimal`:**
```c
// str 是刚刚从BigInt计算出来的纯整数结果(如 "333")，scale是应该还原的小数位数(如 2)
void insert_decimal(char *str, int scale) {
    if (scale <= 0) return; // 没有小数刻度就不用干活
    
    int len = strlen(str); // 看看现在的数字有几位长 (3)
    int is_negative = (str[0] == '-'); // 第一位如果是减号，标记为负数
    int num_len = is_negative ? len - 1 : len; // 如果是负数，实际纯数字长度要减掉负号占的1个坑位
    
    if (scale > MAX_INPUT_LEN) return; // 保护机制：如果要求的精度太离谱(比如要点在几万位后)，坚决不干！

    char temp[MAX_INPUT_LEN * 2] = {0}; // 准备一个新本子(空数组)来写插入小数点后的模样
    int temp_idx = 0; // 这个变量记录我们正在本子的哪个位置下笔
    
    if (is_negative) temp[temp_idx++] = '-'; // 如果原本有负号，最前面咱们先把负号补在开头
    
    if (num_len <= scale) { 
        // 情景1：数字总长度都没小数位数多 (比如算出了 333，但要求小数点在后边4位)
        // 那就是说明这是个零点几的小数，我们得在前面补零："0.0333"
        temp[temp_idx++] = '0'; // 补上最初的那个零 "0"
        temp[temp_idx++] = '.'; // 补上点       "0."
        for (int i = 0; i < scale - num_len; i++) {
            temp[temp_idx++] = '0'; // 中间差了几位补几个零 "0.0"
        }
        strcpy(temp + temp_idx, str + (is_negative ? 1 : 0)); // 最后把原本的"333"搬过来
    } else {
        // 情景2：正常数字 (算出了"12345"，小数位是2位，变成"123.45")
        int insert_pos = len - scale;  // 从开头数，第几位该下笔写小数点 (5-2=3，即在位置3下笔)
        strncpy(temp, str, insert_pos); // 先把前面的"123"抄下来
        temp[insert_pos] = '.';         // 在空出来的位置填上小数点
        strcpy(temp + insert_pos + 1, str + insert_pos); // 再把剩下的"45"续在点号后面
    }
    
    // 扫除尾部没用的0 (比如算完了是 "123.4500" 需要整理为 "123.45")
    if (strchr(temp, '.')) { 
        int final_len = strlen(temp);
        while (final_len > 0 && temp[final_len - 1] == '0') final_len--; // 从最后往前看，全是0就砍掉长度
        if (final_len > 0 && temp[final_len - 1] == '.') final_len--; // 如果0砍完了露出来个孤单的 ".", 一并砍了 ("123." 变 "123")
        temp[final_len] = '\0'; // 宣告新字符串在这个截断的尾部结束
    }
    
    strcpy(str, temp); // 把在草稿纸(temp)上完全画好的新样子，一把盖回原来的 str 里。
}
```

### 1.6 manual precision (手动调整除法精度)
除法是个非常特殊的家伙，因为比如 10 / 3 是除不尽的。它需要人告诉它，到底往后推算几位就停手。

为了让用户能自己传参数告诉我们想要几位精度（如 `-p 2` 只要留两位），我们要在 `main` 函数以及交互模式里搞起“拦截过滤”。

**在 `main` 里识别启动参数:**
```c
int main(int argc, char *argv[]) {
    int precision = 6;  // 我们给个默认精度兜底，这叫防呆设计，就算他不输我们也有个准头。
    int arg_idx = 1;    // 默认从第一个参数开始就是数学表达式

    // 检查：如果参数起码有3个起步 (如 ./calc -p 2，这就有程序名+选项+数字 共三个了) 
    // 而且第二个参数确定就是 "-p" 或者 "--precision"
    if (argc >= 3 && (strcmp(argv[1], "-p") == 0 || strcmp(argv[1], "--precision") == 0)) {
        
        char *endptr; // 这个指针，等下 strtol 把数字抠到哪断了，它就指在哪。用来查错极其好用。
        errno = 0;    // 系统错误码。开干前先清零。
        
        // strtol是把字符串转成long整形。它比atoi强在它非常严谨
        // argv[2] 就是紧跟着的那个数字字符串，比如 "4"
        long p = strtol(argv[2], &endptr, 10); // "10"的意思是用10进制理解数字
        
        // 开始三连发灵魂拷问 (查错):
        // 1. errno == ERANGE: 卧槽你输入的是不是超级大，直接爆内存上限了？
        // 2. *endptr != '\0': 指针抠完数字发现停在半道了(比如你输入的是 "2abc" 或者 "2 !")，你输入的根本不纯净！
        // 3. p < 0: 精确的位数怎么可能是负数？
        if (errno == ERANGE || *endptr != '\0' || p < 0) {
            fprintf(stderr, "Error: Invalid precision value. It must be a non-negative integer.\n");
            return 1; // 一旦发现用户瞎搞，果断报错退出，保护程序
        }
        
        // 再次严防死守: 你的精度合法，但你要求算几万位，我内部数组(MAX_INPUT_LEN)可装不下啊！
        if (p > MAX_INPUT_LEN) {
            fprintf(stderr, "Error: Precision too large. Maximum allowed is %d.\n", MAX_INPUT_LEN);
            return 1;
        }
        
        precision = (int)p; // 历经九九八十一难，终于把纯洁合法的设定赋值了！
        arg_idx = 3; // 因为第1和第2个参数是 "-p" 和 "数字"，被我们处理掉了，所以真正的数字算式得从第3处(引脚3)开始找！
    }
    
    // ... 然后把提取出的 precision 一路当作参数传递给 run_cli_mode 还是 evaluate_expression 即可。
```

**在交互模式中的中途拦截修改:**
交互模式是不退出的瞎敲模式，我们要能识别出用户打进来的设定指令。

```c
void run_interactive_mode(int precision) {
    char input[MAX_INPUT_LEN];

    while (1) {
        printf("> ");
        if (fgets(input, sizeof(input), stdin) == NULL) break;
        input[strcspn(input, "\n")] = 0; 
        
        // // // 重点来了 // // // 
        // 刚刚截获了一行用户的输入 (放在了 input 变量里)，接下来去查有没有指令
        
        // strncmp 会比较前 n 个字符。如果是 "-p " 恰好匹配上了：
        if (strncmp(input, "-p ", 3) == 0) {
            
            // 指针跳过前面的 "-p "，直指后面的数字部分。比如 "-p 4" 中的 "4"
            const char *num_part = input + 3;
            
            char *endptr;
            errno = 0;
            // 还是同一款神器：把那串数字字符串转换成实打实的整数
            long p = strtol(num_part, &endptr, 10);
            
            // 跳过可能跟随的空格 (比如有些人粗心打成了 "-p 4   ")
            while (*endptr != '\0' && isspace(*endptr)) endptr++;
            
            // 老规矩安全检查
            if (errno == ERANGE || *endptr != '\0' || p < 0) {
                printf("Error: Invalid precision value. It must be a non-negative integer.\n");
            } else if (p > MAX_INPUT_LEN) {
                printf("Error: Precision too large. Maximum allowed is %d.\n", MAX_INPUT_LEN);
            } else { // 如果完美无瑕疵！
                precision = (int)p; // 让大局变量吃下这个新精度
                printf("Precision set to %d\n", precision); // 报出喜讯
            }
            // 不要忘了！这只是为了调代码的指令，千万别傻傻地继续往下塞给数学公式去算 "-p 4"。
            // 必须 continue！让循环立刻跳回开头，重新打印个 '> ' 回到待命状态。
            continue;
        }
    }
    // ... 后方照常是处理真正加减乘除计算的代码部分
}
```

最后一步，只消打开计算过程的心脏 `evaluate_expression` 就能起效了。
```c
CalcResult evaluate_expression(const char *expr, int precision) {
    // 终于！在遇见除法的时候，我们不再把位数写死了。而是把那个千辛万苦历经风霜，受尽最严格考验的参数 precision 给喂了过去。
    // 大数除法算盘，给我启动！
    } else if (op == '/') {
        // ... (对齐0的代码)
        bigint_div(int1, int2, res.result, precision, &res.err); 
    } 
```

至此，小数点提取、植回和小数精度设定的前后端整个流程完全被打通。
