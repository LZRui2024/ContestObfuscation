#include "StringEncryptor.h"
#include <vector>
#include <cstdlib>

StringEncryptor::StringEncryptor() {
    key = rand() % 256 + 1;
}

std::string StringEncryptor::processEscapeSequences(const std::string& str) {
    std::string processed;
    for (size_t i = 0; i < str.length(); i++) {
        if (str[i] == '\\' && i + 1 < str.length()) {
            char next = str[i + 1];
            switch (next) {
                case 'n': processed += '\n'; break;
                case 't': processed += '\t'; break;
                case 'r': processed += '\r'; break;
                case '\\': processed += '\\'; break;
                case '"': processed += '"'; break;
                case '\'': processed += '\''; break;
                case '0': processed += '\0'; break;
                case 'a': processed += '\a'; break;
                case 'b': processed += '\b'; break;
                case 'f': processed += '\f'; break;
                case 'v': processed += '\v'; break;
                default: 
                    processed += str[i];
                    processed += next;
                    break;
            }
            i++;
        } else {
            processed += str[i];
        }
    }
    return processed;
}

std::string StringEncryptor::encryptString(const std::string& str) {
    std::string processed = processEscapeSequences(str);
    std::string encrypted;
    for (char c : processed) {
        encrypted += std::to_string(static_cast<unsigned char>(c) ^ key) + ",";
    }
    if (!encrypted.empty()) {
        encrypted.pop_back();
    }
    return "decrypt({" + encrypted + "})";
}

std::string StringEncryptor::generateDecryptFunction() {
    return "std::string decrypt(const int* arr, int length) {\n" 
         "    std::string result;\n" 
         "    for (int i = 0; i < length; i++) {\n" 
         "        result += static_cast<char>(arr[i] ^ " + std::to_string(key) + ");\n" 
         "    }\n" 
         "    return result;\n" 
         "}\n" 
         "std::string decrypt(std::initializer_list<int> arr) {\n" 
         "    return decrypt(arr.begin(), arr.size());\n" 
         "}\n";
}

std::pair<std::string, std::string> StringEncryptor::encryptStrings(const std::string& code) {
    std::string result = code;
    size_t pos = 0;
    
    while (pos < result.length()) {
        // 跳过注释和预处理指令
        if (pos + 1 < result.length() && result.substr(pos, 2) == "//") {
            size_t end = result.find("\n", pos);
            if (end == std::string::npos) break;
            pos = end + 1;
            continue;
        }
        if (pos + 1 < result.length() && result.substr(pos, 2) == "/*") {
            size_t end = result.find("*/", pos + 2);
            if (end == std::string::npos) break;
            pos = end + 2;
            continue;
        }
        if (pos + 8 <= result.length() && result.substr(pos, 8) == "#include") {
            size_t end = result.find("\n", pos);
            if (end == std::string::npos) break;
            pos = end + 1;
            continue;
        }
        if (pos + 6 <= result.length() && result.substr(pos, 6) == "#define") {
            size_t end = result.find("\n", pos);
            if (end == std::string::npos) break;
            pos = end + 1;
            continue;
        }
        
        // 查找双引号
        size_t quote_start = result.find("\"", pos);
        if (quote_start == std::string::npos) break;
        
        // 检查是否是字符串字面量的开始（前面不是字母数字或下划线）
        if (quote_start > 0) {
            char prev_char = result[quote_start - 1];
            if (isalnum(prev_char) || prev_char == '_' || prev_char == ']') {
                // 可能是 R"(...)" 原始字符串或字符串字面量的一部分，跳过
                pos = quote_start + 1;
                continue;
            }
        }
        
        // 查找匹配的结束双引号（处理转义字符）
        size_t quote_end = quote_start + 1;
        while (quote_end < result.length()) {
            if (result[quote_end] == '\\' && quote_end + 1 < result.length()) {
                quote_end += 2; // 跳过转义字符
                continue;
            }
            if (result[quote_end] == '"') {
                break;
            }
            quote_end++;
        }
        
        if (quote_end >= result.length()) break;
        
        // 提取字符串内容（不包括引号）
        std::string str_content = result.substr(quote_start + 1, quote_end - quote_start - 1);
        
        // 跳过空字符串、过短的字符串和只包含转义序列的字符串
        if (str_content.length() <= 1) {
            pos = quote_end + 1;
            continue;
        }
        
        // 跳过只包含转义序列的字符串（如 \n, \t 等）
        if (str_content.length() == 2 && str_content[0] == '\\') {
            pos = quote_end + 1;
            continue;
        }
        
        // 加密字符串
        std::string encrypted = encryptString(str_content);
        
        // 替换
        result.replace(quote_start, quote_end - quote_start + 1, encrypted);
        pos = quote_start + encrypted.length();
    }
    
    std::string decrypt_function = generateDecryptFunction();
    return {result, decrypt_function};
}

void StringEncryptor::clear() {
    key = rand() % 256 + 1;
}
