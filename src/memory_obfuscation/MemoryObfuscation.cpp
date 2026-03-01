#include "MemoryObfuscation.h"
#include "../random_string/RandomStringGenerator.h"
#include <sstream>
#include <regex>
#include <cstdlib>
#include <algorithm>

std::string MemoryObfuscation::replaceWithMemcpy(const std::string& code) {
    std::string result = code;
    
    // 查找简单的赋值语句（跳过变量声明和 switch 语句）
    size_t pos = 0;
    while ((pos = result.find('=', pos)) != std::string::npos) {
        // 检查是否在字符串或注释中
        size_t line_start = result.rfind('\n', pos);
        if (line_start == std::string::npos) line_start = 0;
        
        std::string line = result.substr(line_start, pos - line_start);
        
        // 跳过变量声明
        if (line.find("int ") != std::string::npos || 
            line.find("volatile ") != std::string::npos ||
            line.find("auto ") != std::string::npos ||
            line.find("double ") != std::string::npos) {
            pos++;
            continue;
        }
        
        // 跳过 switch 语句
        if (line.find("switch") != std::string::npos) {
            pos++;
            continue;
        }
        
        // 查找分号
        size_t semicolon = result.find(';', pos);
        if (semicolon == std::string::npos || semicolon > pos + 50) {
            pos++;
            continue;
        }
        
        std::string stmt = result.substr(pos + 1, semicolon - pos - 1);
        
        // 检查是否是简单赋值（右边只有一个变量）
        std::regex simple_assign_regex(R"(\s*(\w+)\s*)");
        std::smatch match;
        if (std::regex_match(stmt, match, simple_assign_regex)) {
            std::string dest = match[1];
            
            // 检查左边是否是变量（不是常量或临时值）
            // 向左查找，确认 dest 是赋值的目标
            std::string left_side = result.substr(line_start, pos - line_start);
            std::regex assign_target_regex(R"(.*\s+(\w+)\s*=\s*.*)");
            std::smatch target_match;
            if (!std::regex_match(left_side, target_match, assign_target_regex)) {
                pos++;
                continue;
            }
            
            std::string target = target_match[1];
            
            // 跳过如果目标是数字（常量）
            if (std::all_of(target.begin(), target.end(), ::isdigit)) {
                pos++;
                continue;
            }
            
            // 随机决定是否替换为内存操作
            if (rand() % 5 == 0) {
                std::string temp_var = "tmp_" + RandomStringGenerator::generate(6);
                std::stringstream ss;
                ss << "{ int " << temp_var << " = " << stmt << "; memcpy(&" << target << ", &" << temp_var << ", sizeof(" << target << ")); }";
                result.replace(pos - 1, semicolon - pos + 2, ss.str());
                pos += ss.str().length();
            } else {
                pos = semicolon + 1;
            }
        } else {
            pos = semicolon + 1;
        }
    }
    
    return result;
}

std::string MemoryObfuscation::addMemoryOperations(const std::string& code) {
    std::string result = code;
    
    // 添加内存操作头文件
    if (result.find("#include <cstring>") == std::string::npos) {
        size_t first_include = result.find("#include");
        if (first_include != std::string::npos) {
            size_t end_of_line = result.find('\n', first_include);
            if (end_of_line != std::string::npos) {
                result.insert(end_of_line, "\n#include <cstring>");
            }
        }
    }
    
    // 替换赋值操作为内存操作
    result = replaceWithMemcpy(result);
    
    return result;
}
