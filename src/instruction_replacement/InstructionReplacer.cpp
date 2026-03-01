#include "InstructionReplacer.h"
#include "../random_string/RandomStringGenerator.h"
#include <regex>

InstructionReplacer::InstructionReplacer() {
}

std::string InstructionReplacer::replaceAssignment(const std::string& code) {
    std::string result = code;
    size_t pos = 0;
    
    while (pos < result.length()) {
        // 查找赋值操作符
        size_t assign_pos = result.find("=", pos);
        if (assign_pos == std::string::npos) break;
        
        // 查找变量名
        size_t var_start = assign_pos;
        while (var_start > 0 && (isalnum(result[var_start - 1]) || result[var_start - 1] == '_')) {
            var_start--;
        }
        std::string var_name = result.substr(var_start, assign_pos - var_start);
        
        // 查找分号
        size_t semicolon_pos = result.find(";" , assign_pos);
        if (semicolon_pos == std::string::npos) break;
        
        // 提取值
        size_t value_start = assign_pos + 1;
        while (value_start < semicolon_pos && isspace(result[value_start])) {
            value_start++;
        }
        size_t value_end = semicolon_pos;
        while (value_end > value_start && isspace(result[value_end - 1])) {
            value_end--;
        }
        std::string value = result.substr(value_start, value_end - value_start);
        
        // 检查是否是简单的赋值语句
        if (!var_name.empty() && !value.empty()) {
            // 生成复杂的赋值语句
            std::string temp_var = "t" + RandomStringGenerator::generate(10);
            std::string new_code = temp_var + " = " + value + "; " + var_name + " = " + temp_var + ";";
            result.replace(var_start, semicolon_pos - var_start + 1, new_code);
            pos = var_start + new_code.length();
        } else {
            pos = semicolon_pos + 1;
        }
    }
    
    return result;
}

std::string InstructionReplacer::replaceArithmetic(const std::string& code) {
    std::string result = code;
    size_t pos = 0;
    
    while (pos < result.length()) {
        // 查找加法操作符
        size_t add_pos = result.find("+", pos);
        if (add_pos == std::string::npos) break;
        
        // 查找赋值操作符
        size_t assign_pos = result.rfind("=", add_pos);
        if (assign_pos == std::string::npos) {
            pos = add_pos + 1;
            continue;
        }
        
        // 查找分号
        size_t semicolon_pos = result.find(";" , add_pos);
        if (semicolon_pos == std::string::npos) break;
        
        // 提取变量名
        size_t var_start = assign_pos;
        while (var_start > 0 && (isalnum(result[var_start - 1]) || result[var_start - 1] == '_')) {
            var_start--;
        }
        std::string var_name = result.substr(var_start, assign_pos - var_start);
        
        // 提取左操作数
        size_t left_start = assign_pos + 1;
        while (left_start < add_pos && isspace(result[left_start])) {
            left_start++;
        }
        size_t left_end = add_pos;
        while (left_end > left_start && isspace(result[left_end - 1])) {
            left_end--;
        }
        std::string left = result.substr(left_start, left_end - left_start);
        
        // 提取右操作数
        size_t right_start = add_pos + 1;
        while (right_start < semicolon_pos && isspace(result[right_start])) {
            right_start++;
        }
        size_t right_end = semicolon_pos;
        while (right_end > right_start && isspace(result[right_end - 1])) {
            right_end--;
        }
        std::string right = result.substr(right_start, right_end - right_start);
        
        // 检查是否是简单的加法运算
        if (!var_name.empty() && !left.empty() && !right.empty()) {
            // 生成复杂的算术运算
            std::string temp_var1 = "t" + RandomStringGenerator::generate(10);
            std::string temp_var2 = "t" + RandomStringGenerator::generate(10);
            std::string new_code = temp_var1 + " = " + left + "; " + temp_var2 + " = " + right + "; " + var_name + " = " + temp_var1 + " + " + temp_var2 + ";";
            result.replace(var_start, semicolon_pos - var_start + 1, new_code);
            pos = var_start + new_code.length();
        } else {
            pos = semicolon_pos + 1;
        }
    }
    
    return result;
}

std::string InstructionReplacer::replaceInstructions(const std::string& code) {
    std::string result = code;
    
    // 替换赋值语句
    result = replaceAssignment(result);
    
    // 替换算术运算
    result = replaceArithmetic(result);
    
    return result;
}

void InstructionReplacer::clear() {
}
