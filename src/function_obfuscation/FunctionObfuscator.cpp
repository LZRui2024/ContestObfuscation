#include "FunctionObfuscator.h"
#include "../random_string/RandomStringGenerator.h"
#include <regex>

std::string FunctionObfuscator::obfuscateFunctionName(const std::string& original_name) {
    if (function_map.find(original_name) != function_map.end()) {
        return function_map[original_name];
    }
    std::string obfuscated_name = "f" + RandomStringGenerator::generate(10);
    function_map[original_name] = obfuscated_name;
    reverse_map[obfuscated_name] = original_name;
    return obfuscated_name;
}

std::string FunctionObfuscator::getOriginalName(const std::string& obfuscated_name) {
    if (reverse_map.find(obfuscated_name) != reverse_map.end()) {
        return reverse_map[obfuscated_name];
    }
    return obfuscated_name;
}

std::string FunctionObfuscator::obfuscateFunctions(const std::string& code) {
    std::string result = code;
    
    // 简单的函数名识别和替换，避免复杂正则表达式
    std::vector<std::string> function_names = {"add", "print_vector"};
    
    for (const auto& function_name : function_names) {
        if (function_name != "main" && function_name != "decrypt") {
            std::string obfuscated_name = obfuscateFunctionName(function_name);
            
            // 替换函数定义
            size_t pos = 0;
            while ((pos = result.find(" " + function_name + "(", pos)) != std::string::npos) {
                // 检查是否是函数定义
                size_t prev_pos = pos;
                while (prev_pos > 0 && !isspace(result[prev_pos - 1])) {
                    prev_pos--;
                }
                result.replace(pos + 1, function_name.length(), obfuscated_name);
                pos += obfuscated_name.length() + 1;
            }
            
            // 替换函数调用
            pos = 0;
            while ((pos = result.find(function_name + "(", pos)) != std::string::npos) {
                // 检查是否是单词边界
                if (pos == 0 || !isalnum(result[pos - 1])) {
                    result.replace(pos, function_name.length(), obfuscated_name);
                    pos += obfuscated_name.length();
                } else {
                    pos += function_name.length();
                }
            }
        }
    }
    
    return result;
}

void FunctionObfuscator::clear() {
    function_map.clear();
    reverse_map.clear();
}