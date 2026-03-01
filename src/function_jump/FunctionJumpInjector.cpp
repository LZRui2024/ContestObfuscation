#include "FunctionJumpInjector.h"
#include "../random_string/RandomStringGenerator.h"
#include <regex>

std::string FunctionJumpInjector::generateJumpFunction(const std::string& function_name) {
    return "void " + function_name + "() {}\n";
}

std::string FunctionJumpInjector::generateJumpFunctions() {
    std::string functions;
    for (const auto& pair : function_map) {
        functions += generateJumpFunction(pair.second);
    }
    return functions;
}

std::string FunctionJumpInjector::injectFunctionJumps(const std::string& code) {
    std::string result = code;
    
    // 只在函数体中插入跳转函数调用，不替换原有函数调用
    size_t pos = 0;
    int count = 0;
    
    // 跳过预处理指令
    while (pos < result.length()) {
        if (result.substr(pos, 2) == "//") {
            // 跳过单行注释
            size_t end = result.find("\n", pos);
            if (end == std::string::npos) break;
            pos = end + 1;
        } else if (result.substr(pos, 2) == "/*") {
            // 跳过多行注释
            size_t end = result.find("*/", pos + 2);
            if (end == std::string::npos) break;
            pos = end + 2;
        } else if (result.substr(pos, 8) == "#include") {
            // 跳过#include指令
            size_t end = result.find("\n", pos);
            if (end == std::string::npos) break;
            pos = end + 1;
        } else {
            break;
        }
    }
    
    while ((pos = result.find("{", pos)) != std::string::npos) {
        // 检查是否是函数定义的开始
        bool is_function_def = false;
        size_t check_pos = pos;
        while (check_pos > 0 && !isspace(result[check_pos - 1])) {
            check_pos--;
        }
        if (check_pos > 0) {
            // 向前查找函数定义的特征
            std::string prev_part = result.substr(check_pos, pos - check_pos);
            // 简单检查是否包含函数定义的特征，如返回类型和函数名
            if (prev_part.find("(") != std::string::npos && prev_part.find(")") != std::string::npos) {
                is_function_def = true;
            }
        }
        
        if (count % 3 == 0 && !is_function_def) {
            std::string jump_function = "j" + RandomStringGenerator::generate(10);
            function_map[jump_function] = jump_function; // 记录生成的跳转函数
            result.insert(pos + 1, " " + jump_function + "();\n");
            pos += jump_function.length() + 4;
        }
        pos++;
        count++;
    }
    
    return result;
}

void FunctionJumpInjector::clear() {
    function_map.clear();
}