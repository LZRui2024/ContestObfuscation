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

std::string MacroReplacer::replaceMacros(const std::string& code) {
    std::string result = code;
    for (const auto& pair : macro_map) {
        // 跳过关键字的替换，避免破坏代码语法
        std::vector<std::string> keywords = {
            "int", "double", "float", "bool", "char", "void",
            "return", "if", "else", "for", "while", "true", "false"
        };
        if (std::find(keywords.begin(), keywords.end(), pair.first) != keywords.end()) {
            continue;
        }
        
        size_t pos = 0;
        while ((pos = result.find(pair.first, pos)) != std::string::npos) {
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
                result.replace(pos, pair.first.length(), pair.second);
                pos += pair.second.length();
            } else {
                pos += pair.first.length();
            }
        }
    }
    return result;
}

void MacroReplacer::clear() {
    macro_map.clear();
    reverse_map.clear();
    initCommonMacros();
}