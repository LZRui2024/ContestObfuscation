# ContestObfuscation

### ⚠警告⚠: 建议您不要在编程考试中使用该工具，否则可能会被老师"特别关注"

> 就是图一乐吧ヾ (≧▽≦*)o  
> 本工具主要用于学习和研究 C++ 代码混淆技术，请勿用于不当用途

## 简介

用于直接混淆 CPP (编程竞赛类) 源码的工具 (目前属于测试阶段，仅供参考)

本工具通过多种混淆技术增加代码的阅读难度，同时保持代码功能完全不变。适合用于：
- 代码保护研究
- 混淆技术学习
- 逆向工程对抗练习

## 已实现的混淆功能

### 基础混淆
1. **函数名混淆** - 将函数名替换为随机字符串
2. **变量名混淆** - 将变量名替换为随机字符串
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

## 使用方法

### 编译项目

```bash
# 使用 CMake 编译
cmake -B build
cmake --build build

# 或使用 g++ 直接编译
g++ -std=c++17 -o ContestObfuscation.exe src/main/main.cpp src/random_string/RandomStringGenerator.cpp src/function_obfuscation/FunctionObfuscator.cpp src/macro_replacement/MacroReplacer.cpp src/irrelevant_code/IrrelevantCodeInjector.cpp src/useless_functions/UselessFunctionGenerator.cpp src/function_jump/FunctionJumpInjector.cpp src/variable_obfuscation/VariableObfuscator.cpp src/constant_encryption/ConstantEncryptor.cpp src/string_encryption/StringEncryptor.cpp src/code_chunking/CodeChunker.cpp src/control_flow_flattening/ControlFlowFlattener.cpp src/exception_obfuscation/ExceptionObfuscator.cpp src/function_inlining/FunctionInliner.cpp src/instruction_replacement/InstructionReplacer.cpp src/loop_transformation/LoopTransformer.cpp src/string_splitting/StringSplitter.cpp
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
#include <vector>

using namespace std;

int add(int a, int b) {
    return a + b;
}

void print_vector(const vector<int>& v) {
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}

int main() {
    int x = 5;
    int y = 10;
    int sum = add(x, y);
    cout << "Sum: " << sum << endl;
    
    vector<int> v = {1, 2, 3, 4, 5};
    print_vector(v);
    
    return 0;
}
```

### 混淆后的代码 (部分展示)

```cpp
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define Ybdajzqjirn2jzE false
#define EBgWvmG1gqrQn1o true
#define ZkAJpAnJbb9y1FY for
#define nKnUBC54FWXRMu4 else
#define OXUTwQqJ1wUYUTl return
#define KoIljfFVSmQxCCe cin
#define KVPemn2Pg2pVyxV endl
#define CRmY952XmVZOdGa while
#define QZHN5iCTmmhsGCK vector
#define vTq61Sgax0pFdRa cout
#define saPzERv036aF9Cz int
#define Pa2vV8ubf5FfJhM void

std::string decrypt(const int* arr, int length) {
    std::string result;
    for (int i = 0; i < length; i++) {
        result += static_cast<char>(arr[i] ^ 173);
    }
    return result;
}

// 无用函数
double fW1rWPwmHoY(double pjA1Wc, double pMB79r) { return (pjA1Wc * pMB79r) / (pjA1Wc + 1.0); }
void f9OBJlc8MG7() { int arr[10]; for (int i = 0; i < 10; i++) { arr[i] = rand() % 100; } }

// 函数名混淆 + 异常处理 + 控制流平坦化
int f0P7enqsrKV(int a, int b) {
    int sTX3lmdZSoK = 0;
    for (;;) {
        switch(sTX3lmdZSoK) {
        case 0:
            return a + b;
            sTX3lmdZSoK = 1;
            break;
        case 1:
            return 0;
        default:
            break;
        }
    }
}

// 变量名混淆 + 宏替换 + 字符串加密
void fVK4hCeNryJ(const QZHN5iCTmmhsGCK<int>& v) {
    try {
        throw 0;
    } catch (int em2UyQyS8YN) {
        ZkAJpAnJbb9y1FY (int vaTaPE2yf9e = 0; vaTaPE2yf9e < v.size(); vaTaPE2yf9e++) {
            vTq61Sgax0pFdRa << v[vaTaPE2yf9e] << decrypt({141});
        }
        vTq61Sgax0pFdRa << KVPemn2Pg2pVyxV;
    }
}

int main() {
    try {
        throw 0;
    } catch (int eXUj1mEIdbi) {
        saPzERv036aF9Cz vDChpTSXUHM = 5;
        saPzERv036aF9Cz vLGo3JsRmsk = 10;
        saPzERv036aF9Cz vKEQ626H0To = f0P7enqsrKV(vDChpTSXUHM, vLGo3JsRmsk);
        vTq61Sgax0pFdRa << decrypt({254,216,192,151,141}) << vKEQ626H0To << KVPemn2Pg2pVyxV;
        
        QZHN5iCTmmhsGCK<int> v = {1, 2, 3, 4, 5};
        fVK4hCeNryJ(v);
        
        OXUTwQqJ1wUYUTl 0;
    }
}
```

### 主要变化

| 特性 | 混淆前 | 混淆后 |
|------|--------|--------|
| 函数名 | `add`, `print_vector` | `f0P7enqsrKV`, `fVK4hCeNryJ` |
| 变量名 | `x`, `y`, `sum` | `vDChpTSXUHM`, `vLGo3JsRmsk` |
| 关键字 | `for`, `return`, `cout` | `ZkAJpAnJbb9y1FY`, `OXUTwQqJ1wUYUTl`, `vTq61Sgax0pFdRa` |
| 字符串 | `"Sum: "` | `decrypt({254,216,192,151,141})` |
| 控制流 | 顺序执行 | switch-case 状态机 |
| 异常处理 | 无 | try-catch 包裹 |
| 代码行数 | ~25 行 | ~100+ 行 |

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

### ⚠️ 部分支持
- 模板
- 继承
- 多态

### ❌ 暂不支持
- Lambda 表达式
- 右值引用
- constexpr 函数

## 注意事项

1. **编译警告**: 混淆后的代码可能会产生编译警告（如不可达代码），这属于正常现象
2. **代码体积**: 混淆后代码体积会显著增大（通常 3-5 倍）
3. **调试困难**: 混淆后的代码几乎无法调试
4. **性能影响**: 部分混淆技术可能轻微影响性能
5. **兼容性**: 不保证所有 C++ 代码都能成功混淆

## 技术细节

### 控制流平坦化
将函数的顺序执行转换为基于状态机的 switch-case 结构：
```cpp
// 原始
int add(int a, int b) {
    return a + b;
}

// 平坦化后
int add(int a, int b) {
    int state = 0;
    while(true) {
        switch(state) {
        case 0:
            return a + b;
            state = 1;
            break;
        case 1:
            return 0;
        }
    }
}
```

### 字符串加密
使用 XOR 加密，运行时解密：
```cpp
// 原始
cout << "Hello" << endl;

// 加密后
cout << decrypt({45, 38, 43, 43, 46}) << endl;
```

### 常量加密
使用多种运算加密常量：
```cpp
// 原始
int x = 5;

// 加密后
int x = ((116) ^ 113);  // 116 XOR 113 = 5
```

## 项目结构

```
ContestObfuscation/
├── src/
│   ├── main/                     # 主程序入口
│   ├── random_string/            # 随机字符串生成
│   ├── function_obfuscation/     # 函数名混淆
│   ├── variable_obfuscation/     # 变量名混淆
│   ├── macro_replacement/        # 宏替换
│   ├── constant_encryption/      # 常量加密
│   ├── string_encryption/        # 字符串加密
│   ├── irrelevant_code/          # 无关代码注入
│   ├── useless_functions/        # 无用函数生成
│   ├── function_jump/            # 函数跳转注入
│   ├── code_chunking/            # 代码分块
│   ├── control_flow_flattening/  # 控制流平坦化
│   ├── instruction_replacement/  # 指令替换
│   ├── string_splitting/         # 字符串拆分
│   ├── function_inlining/        # 函数内联
│   ├── loop_transformation/      # 循环变换
│   └── exception_obfuscation/    # 异常处理混淆
├── test.cpp                      # 测试文件
└── CMakeLists.txt                # CMake 配置
```

## 贡献

欢迎提交 Issue 和 Pull Request！

## 许可证

MIT License

---

**再次提醒**: 本工具仅供学习和研究使用，请勿用于作弊或其他不当用途！(๑•̀ㅂ•́)و✧
