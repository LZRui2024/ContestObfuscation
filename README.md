# ContestObfuscation

### ⚠警告⚠: 建议您不要在编程考试中使用该工具，否则可能会被老师"特别关注"

> 就是图一乐吧ヾ (≧▽≦*)o  
> 本工具主要用于学习和研究 C++ 代码混淆技术，请勿用于不当用途

## 简介

用于直接混淆 CPP (编程竞赛类) 源码的工具 (目前属于测试阶段，仅供参考)

本工具通过多种混淆技术增加代码的阅读难度，同时保持代码功能完全不变。适合用于：
- 代码保护研究

## 已实现的混淆功能

### 基础混淆
1. **函数名混淆** - 将函数名替换为随机字符串
2. **变量名混淆** - 将变量名替换为随机字符串（暂时跳过）
3. **宏替换混淆** - 通过宏定义替换关键字，增加阅读难度
4. **常量加密** - 使用 XOR、位移、加减法等运算加密数字常量
5. **字符串加密** - 使用 XOR 加密字符串，运行时解密

### 代码注入
6. **注入无关代码** - 添加不影响功能的冗余代码
7. **添加无用函数** - 生成不会被调用的辅助函数
8. **函数跳转注入** - 添加中间跳转函数增加调用链复杂度
9. **异常处理混淆** - 在函数中添加 try-catch 异常处理结构

### 结构变换
10. **代码分块** - 将代码分割成多个块并重新组织
11. **控制流平坦化** - 将顺序执行转换为 switch-case 状态机
12. **循环变换** - 改变循环结构 (for/while 互换)
13. **指令替换** - 用等效指令替换原指令 (如 `a = b` → `a = b - 0`)
14. **字符串拆分与重组** - 将字符串拆分为多个部分并拼接
15. **函数内联与反内联** - 展开函数或提取为独立函数

### 高级混淆
16. **花指令混淆** - 插入看似有意义但实际无用的代码 (10 种模板)
17. **代码膨胀** - 自动展开小循环，增加代码体积
18. **控制流平坦化增强** - 添加多状态调度变量和虚假状态转换
19. **模板元编程混淆** - 添加编译时计算的模板函数 (Factorial, Fibonacci, GCD)
20. **常量表达式混淆** - 将数字常量替换为等效表达式 (如 `2` → `(1 + 1)`)
21. **内存操作混淆** - 将简单赋值替换为 memcpy 内存操作

### 运行时混淆 (新增)
22. **语义混淆** - 添加运行时不透明常量和虚假数据依赖
23. **高级混淆增强** - TEA-like 加密、状态机、不透明谓词、函数跳转干扰

## 使用方法

### 编译项目

```bash
# 使用 CMake 编译 (推荐)
cmake -B build
cmake --build build

# 或使用 g++ 直接编译
g++ -std=c++17 -o ContestObfuscation.exe \
    src/main/main.cpp \
    src/random_string/RandomStringGenerator.cpp \
    src/function_obfuscation/FunctionObfuscator.cpp \
    src/macro_replacement/MacroReplacer.cpp \
    src/irrelevant_code/IrrelevantCodeInjector.cpp \
    src/useless_functions/UselessFunctionGenerator.cpp \
    src/function_jump/FunctionJumpInjector.cpp \
    src/variable_obfuscation/VariableObfuscator.cpp \
    src/constant_encryption/ConstantEncryptor.cpp \
    src/string_encryption/StringEncryptor.cpp \
    src/code_chunking/CodeChunker.cpp \
    src/control_flow_flattening/ControlFlowFlattener.cpp \
    src/exception_obfuscation/ExceptionObfuscator.cpp \
    src/function_inlining/FunctionInliner.cpp \
    src/instruction_replacement/InstructionReplacer.cpp \
    src/loop_transformation/LoopTransformer.cpp \
    src/string_splitting/StringSplitter.cpp \
    src/equivalence_replacement/EquivalenceReplacer.cpp \
    src/fake_control_flow/FakeControlFlow.cpp \
    src/instruction_reordering/InstructionReordering.cpp \
    src/data_flow_obfuscation/DataFlowObfuscation.cpp \
    src/anti_semantic/AntiSemantic.cpp \
    src/junk_instructions/JunkInstructions.cpp \
    src/advanced_string_encryption/AdvancedStringEncryption.cpp \
    src/code_expansion/CodeExpansion.cpp \
    src/advanced_control_flow/AdvancedControlFlow.cpp \
    src/template_metaprogramming/TemplateMetaprogramming.cpp \
    src/constexpr_obfuscation/ConstexprObfuscation.cpp \
    src/memory_obfuscation/MemoryObfuscation.cpp \
    src/advanced_obfuscation/AdvancedObfuscation.cpp \
    src/semantic_analysis/SemanticAnalyzer.cpp \
    src/semantic_analysis/SemanticObfuscator.cpp \
    src/semantic_analysis/ExpressionParser.cpp
```

### 运行混淆

```bash
ContestObfuscation.exe <输入文件> <输出文件>
```

示例：
```bash
ContestObfuscation.exe test.cpp test_obfuscated.cpp
```

## 混淆前后对比

### 原始代码

```cpp
#include <iostream>
using namespace std;

int main() {
    int x;
    cin >> x;
    cout << x + 5 << endl;
    return 0;
}
```

### 混淆后的代码 (部分展示)

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

// 高级混淆添加的运行时混淆函数
static volatile int adv_seed = 0;
int adv_init() {
    int *p = new int(13);
    adv_seed = (int)(size_t)p & 0xFF;
    delete p;
    int v = adv_seed;
    v = (v * 3 + 7) & 0xFF;
    v = ((v << 4) | (v >> 4)) & 0xFF;
    v = (v * 0xab) >> 8;
    return 13;
}

int adv_fake_dep(int x, int y) {
    int a = x + y;
    int b = x - y;
    int c = a * b;
    int d = c + y * y;
    int e = d - x * x;
    return e;
}

int adv_flat(int n, int m) {
    int state = 0, res = 0, i = 0;
    int tbl[4] = {n, m, 0, 0};
    while(state != 99) {
        switch(state) {
            case 0: tbl[2] = tbl[0] + tbl[1]; state = 1; break;
            case 1: tbl[3] = tbl[0] * tbl[1]; state = 2; break;
            case 2:
                if((tbl[0] ^ tbl[1]) & 1) state = 3;
                else state = 3;
                break;
            case 3: res = tbl[2]; state = 99; break;
        }
    }
    return res;
}

// 宏替换
#define QXUTwQqJ1wUYUTl cin
#define ZkAJpAnJbb9y1FY for
#define KVPemn2Pg2pVyxV endl
#define vTq61Sgax0pFdRa cout

// 字符串解密函数
std::string decrypt(const int* arr, int length) {
    std::string result;
    for (int i = 0; i < length; i++) {
        result += static_cast<char>(arr[i] ^ 0xAD);
    }
    return result;
}

// 无用函数
void f9OBJlc8MG7() { int arr[10]; for (int i = 0; i < 10; i++) { arr[i] = rand() % 100; } }

int main() {
    // 运行时混淆调用
    int adv_k = adv_init();
    int adv_fake = adv_fake_dep(adv_k, adv_k);
    int adv_state = adv_k - 13;
    
    // 控制流平坦化增强
    volatile int st_0 = (39 + 41);
    volatile int st_1 = st_0 ^ 14;
    volatile int st_2 = (st_0 + st_1) % 10;
    
    try {
    } catch (const std::exception& e) {
        volatile int CbGJwA5H = 0;
        (void)e;
    switch ((st_0 + 7) % 3) {
        case 0: st_0 = (st_0 * 8) % 100; break;
        case 1: st_0 = (st_0 + 7) % 100; break;
        case 2: st_0 = (st_0 ^ 7) % 100; break;
    }
    }
    
    // 输入输出（宏替换后）
    QXUTwQqJ1wUYUTl >> x;
    int adv_tmp_x = adv_fake_dep(x, x);
    (void)adv_tmp_x;
    
    // 输出语句（经过等价替换混淆）
    vTq61Sgax0pFdRa << ((x + 5)) << KVPemn2Pg2pVyxV;
    
    return 0;
}
```

### 主要变化

| 特性 | 混淆前 | 混淆后 |
|------|--------|--------|
| 函数名 | `main` | `main` (保留) |
| 变量名 | `x` | `x` (保留，未混淆) |
| 关键字 | `cin`, `cout`, `endl` | 宏替换为随机名 |
| 控制流 | 顺序执行 | switch-case 状态机 + 多状态调度 |
| 运行时混淆 | 无 | `adv_init`, `adv_fake_dep`, `adv_flat` |
| 异常处理 | 无 | try-catch 包裹 |
| 花指令 | 无 | 多种volatile变量干扰 |
| 模板函数 | 无 | Factorial, Fibonacci, GCD |
| 代码行数 | ~10 行 | ~100+ 行 |

## 支持的语言特性

### ✅ 已支持
- 基本数据类型 (int, double, float, char, bool, string)
- 函数定义与调用
- 变量声明与赋值
- 条件语句 (if/else)
- 循环语句 (for/while)
- 数组和 vector
- 字符串字面量
- 数字常量
- struct 和 class 定义
- 成员函数
- **模板元编程** (Factorial, Fibonacci, GCD)
- **constexpr 函数**
- **异常处理** (try-catch 包装)
- **运行时混淆** (新增)

### ⚠️ 部分支持
- 模板
- 继承
- 多态

### ❌ 暂不支持
- Lambda 表达式
- 右值引用

## 注意事项

1. **编译警告**: 混淆后的代码可能会产生编译警告（如不可达代码），这属于正常现象
2. **代码体积**: 混淆后代码体积会显著增大（通常 10-20 倍）
3. **调试困难**: 混淆后的代码几乎无法调试
4. **性能影响**: 部分混淆技术可能轻微影响性能（花指令、状态转换等）
5. **兼容性**: 不保证所有 C++ 代码都能成功混淆
6. **MSVC 支持**: 需要包含所有头文件，使用标准 C++ 语法
7. **混淆步骤**: 总共 31 步混淆流程，每步都可能改变代码结构

## 技术细节

### 运行时混淆函数

**adv_init()** - 运行时不透明常量：
```cpp
int adv_init() {
    int *p = new int(13);        // 堆地址
    adv_seed = (int)(size_t)p & 0xFF;  // 运行时值
    delete p;
    // 复杂位运算混淆
    int v = adv_seed;
    v = (v * 3 + 7) & 0xFF;
    v = ((v << 4) | (v >> 4)) & 0xFF;
    v = (v * 0xab) >> 8;
    return 13;
}
```

**adv_fake_dep()** - 虚假数据依赖：
```cpp
int adv_fake_dep(int x, int y) {
    int a = x + y;
    int b = x - y;
    int c = a * b;
    int d = c + y * y;
    int e = d - x * x;
    return e;  // 创建复杂数据流但结果取决于输入
}
```

**adv_flat()** - 控制流扁平化状态机：
```cpp
int adv_flat(int n, int m) {
    int state = 0, res = 0;
    int tbl[4] = {n, m, 0, 0};
    while(state != 99) {
        switch(state) {
            case 0: tbl[2] = tbl[0] + tbl[1]; state = 1; break;
            case 1: tbl[3] = tbl[0] * tbl[1]; state = 2; break;
            case 2: state = 3; break;
            case 3: res = tbl[2]; state = 99; break;
        }
    }
    return res;
}
```

### 控制流平坦化
将函数的顺序执行转换为基于状态机的 switch-case 结构

### 字符串加密
使用 XOR 加密，运行时解密

### 模板元编程
添加编译时计算的模板函数

## 项目结构

```
ContestObfuscation/
├── src/
│   ├── main/                     # 主程序入口
│   ├── random_string/            # 随机字符串生成
│   ├── function_obfuscation/     # 函数名混淆
│   ├── variable_obfuscation/     # 变量名混淆（暂时跳过）
│   ├── macro_replacement/        # 宏替换
│   ├── constant_encryption/      # 常量加密
│   ├── string_encryption/        # 字符串加密
│   ├── irrelevant_code/          # 无关代码注入
│   ├── useless_functions/        # 无用函数生成
│   ├── function_jump/           # 函数跳转注入
│   ├── code_chunking/           # 代码分块
│   ├── control_flow_flattening/ # 控制流平坦化
│   ├── instruction_replacement/ # 指令替换
│   ├── string_splitting/        # 字符串拆分
│   ├── function_inlining/       # 函数内联
│   ├── loop_transformation/     # 循环变换
│   ├── exception_obfuscation/   # 异常处理混淆
│   ├── equivalence_replacement/ # 等价表达式替换
│   ├── fake_control_flow/       # 虚假控制流
│   ├── instruction_reordering/  # 指令重排序
│   ├── data_flow_obfuscation/   # 数据流混淆
│   ├── anti_semantic/           # 反语义分析
│   ├── junk_instructions/       # 花指令
│   ├── advanced_string_encryption/ # 高级字符串加密
│   ├── code_expansion/          # 代码膨胀
│   ├── advanced_control_flow/   # 控制流平坦化增强
│   ├── template_metaprogramming/ # 模板元编程
│   ├── constexpr_obfuscation/   # 常量表达式混淆
│   ├── memory_obfuscation/      # 内存操作混淆
│   ├── advanced_obfuscation/    # 高级混淆
│   └── semantic_analysis/        # 语义混淆（新增）
├── test.cpp                     # 测试文件
├── CMakeLists.txt               # CMake 配置
└── README.md                    # 本文件
```

## 贡献

欢迎提交 Issue 和 Pull Request！

## 许可证

MIT License

---

**再次提醒**: 本工具仅供学习和研究使用，请勿用于作弊或其他不当用途！(๑•̀ㅂ•́)و✧
