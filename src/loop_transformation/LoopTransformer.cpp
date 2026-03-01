#include "LoopTransformer.h"
#include "../random_string/RandomStringGenerator.h"
#include <sstream>

LoopTransformer::LoopTransformer() {
}

std::string LoopTransformer::transformForLoop(const std::string& code) {
    std::string result = code;
    size_t pos = 0;
    
    while (pos < result.length()) {
        // 查找for关键字
        size_t for_pos = result.find("for", pos);
        if (for_pos == std::string::npos) break;
        
        // 检查是否是单词
        if (for_pos > 0 && isalnum(result[for_pos - 1])) {
            pos = for_pos + 3;
            continue;
        }
        
        // 查找左括号
        size_t left_paren = result.find("(", for_pos);
        if (left_paren == std::string::npos) break;
        
        // 查找右括号
        size_t right_paren = result.find(")", left_paren);
        if (right_paren == std::string::npos) break;
        
        // 查找左大括号
        size_t left_brace = result.find("{", right_paren);
        if (left_brace == std::string::npos) break;
        
        // 查找右大括号（处理嵌套）
        int brace_count = 1;
        size_t right_brace = left_brace + 1;
        while (right_brace < result.length() && brace_count > 0) {
            if (result[right_brace] == '{') brace_count++;
            else if (result[right_brace] == '}') brace_count--;
            right_brace++;
        }
        if (brace_count != 0) {
            pos = right_brace;
            continue;
        }
        
        // 提取循环初始化、条件和增量
        std::string loop_content = result.substr(left_paren + 1, right_paren - left_paren - 1);
        size_t semicolon1 = loop_content.find(";" , 0);
        size_t semicolon2 = loop_content.find(";" , semicolon1 + 1);
        if (semicolon1 == std::string::npos || semicolon2 == std::string::npos) {
            pos = right_brace;
            continue;
        }
        
        std::string init = loop_content.substr(0, semicolon1);
        std::string condition = loop_content.substr(semicolon1 + 1, semicolon2 - semicolon1 - 1);
        std::string increment = loop_content.substr(semicolon2 + 1);
        
        // 提取循环体
        std::string body = result.substr(left_brace + 1, right_brace - left_brace - 2);
        
        // 生成复杂的循环形式
        std::stringstream ss;
        ss << init << "; ";
        ss << "while (true) {";
        ss << "    if (!((" << condition << "))) break;";
        ss << "    " << body;
        ss << "    " << increment << ";";
        ss << "}";
        
        // 替换循环
        std::string new_loop = ss.str();
        result.replace(for_pos, right_brace - for_pos, new_loop);
        pos = for_pos + new_loop.length();
    }
    
    return result;
}

std::string LoopTransformer::transformWhileLoop(const std::string& code) {
    std::string result = code;
    size_t pos = 0;
    
    while (pos < result.length()) {
        // 查找while关键字
        size_t while_pos = result.find("while", pos);
        if (while_pos == std::string::npos) break;
        
        // 检查是否是单词
        if (while_pos > 0 && isalnum(result[while_pos - 1])) {
            pos = while_pos + 5;
            continue;
        }
        
        // 查找左括号
        size_t left_paren = result.find("(", while_pos);
        if (left_paren == std::string::npos) break;
        
        // 查找右括号
        size_t right_paren = result.find(")", left_paren);
        if (right_paren == std::string::npos) break;
        
        // 查找左大括号
        size_t left_brace = result.find("{", right_paren);
        if (left_brace == std::string::npos) break;
        
        // 查找右大括号（处理嵌套）
        int brace_count = 1;
        size_t right_brace = left_brace + 1;
        while (right_brace < result.length() && brace_count > 0) {
            if (result[right_brace] == '{') brace_count++;
            else if (result[right_brace] == '}') brace_count--;
            right_brace++;
        }
        if (brace_count != 0) {
            pos = right_brace;
            continue;
        }
        
        // 提取循环条件
        std::string condition = result.substr(left_paren + 1, right_paren - left_paren - 1);
        
        // 提取循环体
        std::string body = result.substr(left_brace + 1, right_brace - left_brace - 2);
        
        // 生成复杂的循环形式
        std::stringstream ss;
        ss << "for (;;) {";
        ss << "    if (!((" << condition << "))) break;";
        ss << "    " << body;
        ss << "}";
        
        // 替换循环
        std::string new_loop = ss.str();
        result.replace(while_pos, right_brace - while_pos, new_loop);
        pos = while_pos + new_loop.length();
    }
    
    return result;
}

std::string LoopTransformer::transformLoops(const std::string& code) {
    std::string result = code;
    
    // 转换for循环
    result = transformForLoop(result);
    
    // 转换while循环
    result = transformWhileLoop(result);
    
    return result;
}

void LoopTransformer::clear() {
}
