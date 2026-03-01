#include "IrrelevantCodeInjector.h"
#include "../random_string/RandomStringGenerator.h"
#include <random>
#include <vector>

std::string IrrelevantCodeInjector::generateIrrelevantCode() {
    std::vector<std::string> code_snippets = {
        // 循环类
        "for (int i = 0; i < 1; i++) { volatile int _t = i; }",
        "for (int j = 0; j <= 0; j++) { int temp = j * 2; }",
        "while (0) { int k = 0; k++; }",
        "do { volatile int x = 1; } while (false)",
        
        // 条件类
        "if (1 > 2) { int a = 10; } else { int b = 20; }",
        "if (nullptr == nullptr) { volatile int val = 0; }",
        "if (true && false) { int test = 1; }",
        "if (0 != 0) { int dummy = 99; }",
        
        // 代码块类
        "{ volatile int temp1 = 1, temp2 = 2; auto sum = temp1 + temp2; }",
        "{ int arr[3] = {1, 2, 3}; volatile int x = arr[0]; }",
        "{ auto lambda = []() { return 42; }; (void)lambda; }",
        
        // switch 类
        "switch (1) { case 0: break; case 1: break; default: break; }",
        "switch (2 + 2) { case 4: break; default: break; }",
        
        // 表达式类
        "(void)(3 + 4 * 5)",
        "static_cast<void>(100)",
        "volatile int unused_flag = false; (void)unused_flag;",
        
        // 数组和向量
        "int dummy_arr[5] = {0};",
        "std::vector<int> temp_vec; temp_vec.reserve(0);",
        
        // 函数调用
        "std::ios_base::sync_with_stdio(false);"
    };
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, code_snippets.size() - 1);
    return code_snippets[distrib(gen)];
}

std::string IrrelevantCodeInjector::injectIrrelevantCode(const std::string& code) {
    std::string result = code;
    std::vector<size_t> semicolon_positions;
    
    // 先收集所有分号的位置
    std::string temp_code = code;
    size_t pos = 0;
    size_t total_pos = 0;
    
    while ((pos = temp_code.find(";")) != std::string::npos) {
        semicolon_positions.push_back(total_pos + pos);
        total_pos += pos + 1;
        temp_code = temp_code.substr(pos + 1);
        if (temp_code.empty()) break;
    }
    
    // 按照从后往前的顺序插入，避免位置偏移
    int count = 0;
    for (auto it = semicolon_positions.rbegin(); it != semicolon_positions.rend(); ++it) {
        size_t current_pos = *it;
        
        // 检查是否在 using namespace 语句中
        bool in_using_namespace = false;
        size_t check_pos = code.rfind("using namespace", current_pos);
        if (check_pos != std::string::npos) {
            size_t end_pos = code.find("\n", check_pos);
            if (end_pos != std::string::npos && current_pos >= check_pos && current_pos < end_pos) {
                in_using_namespace = true;
            }
        }
        if (in_using_namespace) {
            count++;
            continue;
        }
        
        // 检查是否在 for 循环的条件部分
        bool in_for_condition = false;
        check_pos = code.rfind("for", current_pos);
        if (check_pos != std::string::npos) {
            size_t paren_start = code.find("(", check_pos);
            if (paren_start != std::string::npos) {
                size_t paren_end = code.find(")", paren_start);
                if (paren_end != std::string::npos && current_pos > paren_start && current_pos < paren_end) {
                    in_for_condition = true;
                }
            }
        }
        if (in_for_condition) {
            count++;
            continue;
        }
        
        // 检查是否在函数调用中
        bool in_function_call = false;
        check_pos = code.rfind("(", current_pos);
        if (check_pos != std::string::npos) {
            size_t paren_end = code.find(")", current_pos);
            if (paren_end != std::string::npos && current_pos > check_pos && current_pos < paren_end) {
                in_function_call = true;
            }
        }
        if (in_function_call) {
            count++;
            continue;
        }
        
        // 检查是否在向量初始化中
        bool in_vector_init = false;
        check_pos = code.rfind("{", current_pos);
        if (check_pos != std::string::npos) {
            size_t brace_end = code.find("}", current_pos);
            if (brace_end != std::string::npos && current_pos > check_pos && current_pos < brace_end) {
                in_vector_init = true;
            }
        }
        if (in_vector_init) {
            count++;
            continue;
        }
        
        // 更随机的插入频率，避免固定模式
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(1, 3);
        
        if (count % distrib(gen) == 0) {
            std::string irrelevant_code = generateIrrelevantCode();
            result.insert(current_pos + 1, " " + irrelevant_code + ";");
        }
        count++;
    }
    
    return result;
}