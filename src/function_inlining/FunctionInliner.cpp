#include "FunctionInliner.h"
#include "../random_string/RandomStringGenerator.h"
#include <regex>
#include <sstream>

FunctionInliner::FunctionInliner() {
}

std::string FunctionInliner::extractFunctions(const std::string& code) {
    std::string result = code;
    size_t pos = 0;
    
    while (pos < code.length()) {
        // 查找函数定义的开始
        size_t function_start = code.find(" ", pos);
        if (function_start == std::string::npos) break;
        
        // 查找函数名
        size_t name_start = function_start + 1;
        size_t name_end = code.find("(", name_start);
        if (name_end == std::string::npos) break;
        
        std::string function_name = code.substr(name_start, name_end - name_start);
        // 跳过main函数
        if (function_name == "main") {
            pos = name_end;
            continue;
        }
        
        // 查找函数体的开始
        size_t body_start = code.find("{", name_end);
        if (body_start == std::string::npos) break;
        
        // 查找函数体的结束（处理嵌套大括号）
        int brace_count = 1;
        size_t body_end = body_start + 1;
        while (body_end < code.length() && brace_count > 0) {
            if (code[body_end] == '{') brace_count++;
            else if (code[body_end] == '}') brace_count--;
            body_end++;
        }
        
        if (brace_count == 0) {
            std::string function_body = code.substr(body_start + 1, body_end - body_start - 2);
            function_map[function_name] = function_body;
        }
        
        pos = body_end;
    }
    
    return result;
}

std::string FunctionInliner::inlineFunctionCalls(const std::string& code) {
    std::string result = code;
    
    // 识别函数调用
    for (const auto& pair : function_map) {
        std::string function_name = pair.first;
        std::string function_body = pair.second;
        
        size_t pos = 0;
        while (true) {
            // 查找函数名
            size_t name_pos = result.find(" " + function_name + "(", pos);
            if (name_pos == std::string::npos) {
                // 尝试查找没有空格的情况
                name_pos = result.find(function_name + "(", pos);
                if (name_pos == std::string::npos) break;
            }
            
            // 查找函数调用的结束
            int paren_count = 1;
            size_t end_pos = name_pos + function_name.length() + 1;
            while (end_pos < result.length() && paren_count > 0) {
                if (result[end_pos] == '(') paren_count++;
                else if (result[end_pos] == ')') paren_count--;
                end_pos++;
            }
            
            if (paren_count == 0) {
                // 替换函数调用为函数体
                result.replace(name_pos, end_pos - name_pos, function_body);
                pos = name_pos + function_body.length();
            } else {
                pos = end_pos;
            }
        }
    }
    
    return result;
}

std::string FunctionInliner::inlineFunctions(const std::string& code) {
    std::string result = code;
    
    // 提取函数定义
    result = extractFunctions(result);
    
    // 内联函数调用
    result = inlineFunctionCalls(result);
    
    return result;
}

void FunctionInliner::clear() {
    function_map.clear();
}
