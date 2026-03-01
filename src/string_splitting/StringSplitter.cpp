#include "StringSplitter.h"
#include "../random_string/RandomStringGenerator.h"
#include <vector>
#include <sstream>

StringSplitter::StringSplitter() {
}

std::string StringSplitter::generateSplitCode(const std::string& str) {
    if (str.empty()) {
        return "\"\"";
    }
    
    std::vector<std::string> parts;
    int part_size = 1 + rand() % 3;
    
    for (size_t i = 0; i < str.length(); i += part_size) {
        int end = std::min(static_cast<int>(i + part_size), static_cast<int>(str.length()));
        parts.push_back(str.substr(i, end - i));
    }
    
    std::stringstream ss;
    std::string result_var = "s" + RandomStringGenerator::generate(10);
    
    ss << "([]() -> std::string { std::string " << result_var << ";";
    
    for (const auto& part : parts) {
        ss << result_var << " += \"" << part << "\";";
    }
    
    ss << " return " << result_var << "; })()";
    
    return ss.str();
}

bool StringSplitter::isEncryptedString(const std::string& code, size_t quote_pos) {
    // 检查引号前是否是 decrypt 函数调用
    if (quote_pos == 0) return false;
    
    // 向前查找，跳过空格
    int check_pos = static_cast<int>(quote_pos) - 1;
    while (check_pos >= 0 && isspace(code[check_pos])) {
        check_pos--;
    }
    
    // 检查是否是 ')'，如果是则可能是 decrypt(...) 的结束
    if (check_pos >= 0 && code[check_pos] == ')') {
        int paren_count = 1;
        check_pos--;
        while (check_pos >= 0 && paren_count > 0) {
            if (code[check_pos] == ')') paren_count++;
            else if (code[check_pos] == '(') paren_count--;
            check_pos--;
        }
        
        // 检查函数名是否是 decrypt
        while (check_pos >= 0 && isspace(code[check_pos])) {
            check_pos--;
        }
        
        std::string func_name = "decrypt";
        if (check_pos + 1 >= static_cast<int>(func_name.length())) {
            std::string prev = code.substr(check_pos - func_name.length() + 1, func_name.length());
            if (prev == func_name) {
                return true;
            }
        }
    }
    
    return false;
}

std::string StringSplitter::splitString(const std::string& code) {
    std::string result = code;
    size_t pos = 0;
    
    while (pos < result.length()) {
        size_t quote_pos = result.find("\"", pos);
        if (quote_pos == std::string::npos) break;
        
        // 检查是否是已经加密的字符串
        if (isEncryptedString(result, quote_pos)) {
            pos = quote_pos + 1;
            continue;
        }
        
        // 检查是否在注释中
        if (quote_pos > 0) {
            std::string line_start = result.substr(result.rfind("\n", quote_pos) == std::string::npos ? 0 : result.rfind("\n", quote_pos), quote_pos);
            if (line_start.find("//") != std::string::npos) {
                pos = quote_pos + 1;
                continue;
            }
        }
        
        size_t next_quote_pos = result.find("\"", quote_pos + 1);
        if (next_quote_pos == std::string::npos) break;
        
        // 检查是否有转义字符（如果有转义字符，继续查找下一个引号）
        bool has_escape = false;
        size_t check_pos = quote_pos + 1;
        while (check_pos < next_quote_pos) {
            if (result[check_pos] == '\\') {
                has_escape = true;
                check_pos += 2; // 跳过转义字符和下一个字符
            } else {
                check_pos++;
            }
        }
        
        // 如果有转义字符，说明字符串内容包含特殊字符，不处理
        if (has_escape) {
            pos = next_quote_pos + 1;
            continue;
        }
        
        std::string str = result.substr(quote_pos + 1, next_quote_pos - quote_pos - 1);
        
        // 只处理长度大于 2 的字符串，避免处理过短的字符串
        if (str.length() <= 2) {
            pos = next_quote_pos + 1;
            continue;
        }
        
        std::string split_code = generateSplitCode(str);
        result.replace(quote_pos, next_quote_pos - quote_pos + 1, split_code);
        pos = quote_pos + split_code.length();
    }
    
    return result;
}

void StringSplitter::clear() {
}
