#include "ConstantEncryptor.h"
#include <regex>
#include <cstdlib>
#include <vector>
#include <algorithm>

ConstantEncryptor::ConstantEncryptor() {
    key = rand() % 256 + 1;
}

std::string ConstantEncryptor::encryptConstant(int value) {
    // 生成随机运算类型
    int op_type = rand() % 4;
    int a = rand() % 16 + 1;
    
    switch (op_type) {
        case 0: // 加 + 减 + 异或
            return "((" + std::to_string((value ^ key) + a) + " - " + std::to_string(a) + ") ^ " + std::to_string(key) + ")";
        case 1: // 减 + 加 + 异或
            return "((" + std::to_string((value ^ key) - a) + " + " + std::to_string(a) + ") ^ " + std::to_string(key) + ")";
        case 2: // 加 + 减 + 异或（不同的顺序）
            return "((" + std::to_string((value ^ key) + a - a) + ") ^ " + std::to_string(key) + ")";
        case 3: // 异或两次
            return "((" + std::to_string((value ^ key) ^ key ^ key) + ") ^ " + std::to_string(key) + ")";
        default:
            return "(" + std::to_string(value ^ key) + " ^ " + std::to_string(key) + ")";
    }
}

std::string ConstantEncryptor::encryptConstants(const std::string& code) {
    std::string result = code;
    
    // 识别整数常量
    std::regex constant_regex(R"((\b\d+\b))");
    std::smatch match;
    std::string temp = code;
    std::vector<std::pair<size_t, size_t>> matches;
    
    // 先收集所有匹配的位置，跳过 include 语句和宏定义
    size_t pos = 0;
    size_t total_offset = 0;
    while (std::regex_search(temp, match, constant_regex)) {
        size_t start = total_offset + match.position();
        
        // 检查是否在 include 语句中
        bool in_include = false;
        size_t check_pos = 0;
        while ((check_pos = code.find("#include", check_pos)) != std::string::npos) {
            size_t end_pos = code.find("\n", check_pos);
            if (end_pos == std::string::npos) break;
            if (start >= check_pos && start < end_pos) {
                in_include = true;
                break;
            }
            check_pos = end_pos + 1;
        }
        if (in_include) {
            temp = match.suffix();
            continue;
        }
        
        // 检查是否在宏定义中
        bool in_macro = false;
        check_pos = 0;
        while ((check_pos = code.find("#define", check_pos)) != std::string::npos) {
            size_t end_pos = code.find("\n", check_pos);
            if (end_pos == std::string::npos) break;
            if (start >= check_pos && start < end_pos) {
                in_macro = true;
                break;
            }
            check_pos = end_pos + 1;
        }
        if (in_macro) {
            temp = match.suffix();
            continue;
        }
        
        // 检查是否在标识符中
        bool in_identifier = false;
        if (start > 0 && isalnum(code[start - 1])) {
            in_identifier = true;
        }
        if (start + match.length() < code.length() && isalnum(code[start + match.length()])) {
            in_identifier = true;
        }
        if (in_identifier) {
            temp = match.suffix();
            continue;
        }
        
        // 检查是否在 for 循环的初始化部分
        bool in_for_init = false;
        check_pos = 0;
        while ((check_pos = code.rfind("for", start)) != std::string::npos) {
            size_t paren_start = code.find("(", check_pos);
            if (paren_start == std::string::npos) break;
            size_t semi_colon = code.find(";", paren_start);
            if (semi_colon == std::string::npos) break;
            if (start > paren_start && start < semi_colon) {
                in_for_init = true;
                break;
            }
            if (check_pos == 0) break;
            check_pos--;
        }
        if (in_for_init) {
            temp = match.suffix();
            continue;
        }
        
        matches.push_back({start, match.length()});
        total_offset += match.position() + match.length();
        temp = match.suffix();
    }
    
    // 按照从后往前的顺序替换，避免位置偏移
    std::sort(matches.rbegin(), matches.rend());
    for (const auto& m : matches) {
        std::string constant_str = code.substr(m.first, m.second);
        int constant = std::stoi(constant_str);
        std::string encrypted = encryptConstant(constant);
        result.replace(m.first, m.second, encrypted);
    }
    
    return result;
}