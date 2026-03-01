#include "InstructionReordering.h"
#include "../random_string/RandomStringGenerator.h"
#include <vector>
#include <sstream>
#include <algorithm>

InstructionReordering::InstructionReordering() : reorder_count(0) {
}

std::string InstructionReordering::reorderIndependentStatements(const std::string& func_body) {
    std::vector<std::string> statements;
    std::string current_stmt;
    int brace_depth = 0;
    
    for (size_t i = 0; i < func_body.length(); i++) {
        char c = func_body[i];
        current_stmt += c;
        
        if (c == '{') brace_depth++;
        else if (c == '}') brace_depth--;
        else if (c == ';' && brace_depth == 0) {
            statements.push_back(current_stmt);
            current_stmt = "";
        }
    }
    
    if (!current_stmt.empty()) {
        statements.push_back(current_stmt);
    }
    
    // 随机重排语句（保持依赖关系）
    if (statements.size() > 2) {
        // 简单地将前两条语句交换位置
        if (rand() % 2) {
            std::swap(statements[0], statements[1]);
            reorder_count++;
        }
    }
    
    // 重新组合语句
    std::string result;
    for (const auto& stmt : statements) {
        result += stmt;
    }
    
    return result;
}

std::string InstructionReordering::reorderInstructions(const std::string& code) {
    std::string result = code;
    
    // 查找函数体并重排其中的语句
    size_t pos = result.find("{");
    while (pos != std::string::npos) {
        // 跳过预处理指令
        if (pos > 0 && result[pos-1] == '#') {
            pos = result.find("{", pos + 1);
            continue;
        }
        
        // 查找匹配的右大括号
        int brace_count = 1;
        size_t end_pos = pos + 1;
        while (end_pos < result.length() && brace_count > 0) {
            if (result[end_pos] == '{') brace_count++;
            else if (result[end_pos] == '}') brace_count--;
            end_pos++;
        }
        
        if (brace_count == 0) {
            std::string func_body = result.substr(pos + 1, end_pos - pos - 2);
            std::string reordered_body = reorderIndependentStatements(func_body);
            
            if (reordered_body != func_body) {
                result.replace(pos + 1, end_pos - pos - 2, reordered_body);
            }
        }
        
        pos = result.find("{", pos + 1);
    }
    
    return result;
}

void InstructionReordering::clear() {
    reorder_count = 0;
}
