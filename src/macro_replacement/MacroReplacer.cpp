#include "MacroReplacer.h"
#include "../random_string/RandomStringGenerator.h"
#include <vector>
#include <cctype>
#include <algorithm>

MacroReplacer::MacroReplacer() {
    initCommonMacros();
}

void MacroReplacer::initCommonMacros() {
    std::vector<std::string> common_terms = {
        "cout", "cin", "endl", "vector", "string", "int", "double", "float",
        "bool", "char", "void", "return", "if", "else", "for", "while",
        "true", "false"
    };
    
    for (const auto& term : common_terms) {
        std::string macro_name;
        do {
            macro_name = RandomStringGenerator::generate(15);
        } while (isdigit(macro_name[0]));
        macro_map[term] = macro_name;
        reverse_map[macro_name] = term;
    }
}

std::string MacroReplacer::generateMacros() {
    std::string macros;
    for (const auto& pair : macro_map) {
        macros += "#define " + pair.second + " " + pair.first + "\n";
    }
    macros += "\n";
    return macros;
}

bool MacroReplacer::isInStringLiteral(const std::string& code, size_t pos) {
    bool in_string = false;
    bool in_char = false;
    bool escaped = false;
    
    for (size_t i = 0; i < pos && i < code.length(); i++) {
        if (escaped) {
            escaped = false;
            continue;
        }
        
        if (code[i] == '\\') {
            escaped = true;
            continue;
        }
        
        if (code[i] == '"') {
            in_string = !in_string;
        } else if (code[i] == '\'' && !in_string) {
            in_char = !in_char;
        }
    }
    
    return in_string || in_char;
}

bool MacroReplacer::isInComment(const std::string& code, size_t pos) {
    // 检查是否在单行注释中
    size_t line_start = code.rfind("\n", pos);
    if (line_start == std::string::npos) {
        line_start = 0;
    } else {
        line_start++;
    }
    
    std::string line = code.substr(line_start, pos - line_start);
    if (line.find("//") != std::string::npos) {
        return true;
    }
    
    // 检查是否在多行注释中（简化处理）
    size_t comment_start = code.rfind("/*", pos);
    if (comment_start != std::string::npos) {
        size_t comment_end = code.find("*/", comment_start);
        if (comment_end == std::string::npos || pos > comment_end) {
            return comment_end == std::string::npos;
        }
    }
    
    return false;
}

std::string MacroReplacer::replaceMacros(const std::string& code) {
    std::string result = code;
    
    // 收集所有需要替换的位置（跳过字符串和注释）
    std::vector<std::pair<size_t, size_t>> replace_positions;
    
    for (const auto& pair : macro_map) {
        // 跳过关键字的替换，避免破坏代码语法
        std::vector<std::string> keywords = {
            "int", "double", "float", "bool", "char", "void",
            "return", "if", "else", "for", "while", "true", "false"
        };
        if (std::find(keywords.begin(), keywords.end(), pair.first) != keywords.end()) {
            continue;
        }
        
        // 跳过单个字母的替换，避免破坏字符串字面量
        if (pair.first.length() <= 1) {
            continue;
        }
        
        size_t pos = 0;
        while ((pos = result.find(pair.first, pos)) != std::string::npos) {
            // 检查是否在字符串或字符常量中
            if (isInStringLiteral(result, pos)) {
                pos += pair.first.length();
                continue;
            }
            
            // 检查是否在注释中
            if (isInComment(result, pos)) {
                pos += pair.first.length();
                continue;
            }
            
            // 检查是否在预处理指令中
            bool in_preprocessor = false;
            size_t check_pos = result.rfind("#", pos);
            if (check_pos != std::string::npos) {
                size_t end_pos = result.find("\n", check_pos);
                if (end_pos != std::string::npos && pos >= check_pos && pos < end_pos) {
                    in_preprocessor = true;
                }
            }
            if (in_preprocessor) {
                pos += pair.first.length();
                continue;
            }
            
            // 检查是否在 using namespace 语句中
            bool in_using_namespace = false;
            check_pos = result.rfind("using namespace", pos);
            if (check_pos != std::string::npos) {
                size_t end_pos = result.find("\n", check_pos);
                if (end_pos != std::string::npos && pos >= check_pos && pos < end_pos) {
                    in_using_namespace = true;
                }
            }
            if (in_using_namespace) {
                pos += pair.first.length();
                continue;
            }
            
            bool is_word = true;
            if (pos > 0 && (isalnum(result[pos - 1]) || result[pos - 1] == ':')) {
                // 检查是否是命名空间或类的一部分，如 std::string
                if (pos > 1 && result[pos - 1] == ':' && result[pos - 2] == ':') {
                    // 是命名空间或类的一部分，需要替换
                    is_word = true;
                } else {
                    is_word = false;
                }
            }
            if (pos + pair.first.length() < result.length() && (isalnum(result[pos + pair.first.length()]) || result[pos + pair.first.length()] == ':')) {
                is_word = false;
            }
            if (is_word) {
                replace_positions.push_back({pos, pair.first.length()});
                pos += pair.first.length();
            } else {
                pos += pair.first.length();
            }
        }
    }
    
    // 从后向前替换，避免位置偏移
    std::sort(replace_positions.begin(), replace_positions.end(),
              [](const std::pair<size_t, size_t>& a, const std::pair<size_t, size_t>& b) {
                  return a.first > b.first;
              });
    
    for (const auto& rp : replace_positions) {
        size_t pos = rp.first;
        size_t len = rp.second;
        const std::string& original = result.substr(pos, len);
        const std::string& replacement = macro_map[original];
        result.replace(pos, len, replacement);
    }
    
    return result;
}

void MacroReplacer::clear() {
    macro_map.clear();
    reverse_map.clear();
    initCommonMacros();
}
