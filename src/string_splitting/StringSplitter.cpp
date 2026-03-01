#include "StringSplitter.h"
#include "../random_string/RandomStringGenerator.h"
#include <regex>
#include <vector>
#include <sstream>

StringSplitter::StringSplitter() {
}

std::string StringSplitter::generateSplitCode(const std::string& str) {
    if (str.empty()) {
        return "\"\"";
    }
    
    // 将字符串分成多个部分
    std::vector<std::string> parts;
    int part_size = 1 + rand() % 3; // 每个部分的大小为1-3个字符
    
    for (int i = 0; i < str.length(); i += part_size) {
        int end = std::min(i + part_size, (int)str.length());
        parts.push_back(str.substr(i, end - i));
    }
    
    // 生成重组代码
    std::stringstream ss;
    std::string result_var = "s" + RandomStringGenerator::generate(10);
    
    ss << "([]() -> std::string { std::string " << result_var << ";";
    
    for (const auto& part : parts) {
        ss << result_var << " += \"" << part << "\";";
    }
    
    ss << " return " << result_var << "; })()";
    
    return ss.str();
}

std::string StringSplitter::splitString(const std::string& code) {
    std::string result = code;
    size_t pos = 0;
    
    while (pos < result.length()) {
        // 查找双引号
        size_t quote_pos = result.find("\"", pos);
        if (quote_pos == std::string::npos) break;
        
        // 查找下一个双引号
        size_t next_quote_pos = result.find("\"", quote_pos + 1);
        if (next_quote_pos == std::string::npos) break;
        
        // 提取字符串内容
        std::string str = result.substr(quote_pos + 1, next_quote_pos - quote_pos - 1);
        
        // 生成分拆代码
        std::string split_code = generateSplitCode(str);
        
        // 替换字符串
        result.replace(quote_pos, next_quote_pos - quote_pos + 1, split_code);
        
        // 更新位置
        pos = quote_pos + split_code.length();
    }
    
    return result;
}

void StringSplitter::clear() {
}
