#include "VariableObfuscator.h"
#include "../random_string/RandomStringGenerator.h"
#include <regex>

bool VariableObfuscator::isInStringLiteral(const std::string& code, size_t pos) {
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

std::string VariableObfuscator::obfuscateVariables(const std::string& code) {
    std::string result = code;
    
    // 识别变量声明
    std::regex var_regex(R"((\w+)\s+([a-zA-Z_]\w*)(\s*=\s*[^;]*)?\s*;)", std::regex::ECMAScript);
    std::smatch match;
    std::string temp = code;
    
    while (std::regex_search(temp, match, var_regex)) {
        std::string var_name = match[2].str();
        // 检查是否在 using namespace 语句中
        bool in_using_namespace = false;
        size_t match_pos = match.position();
        size_t check_pos = code.rfind("using namespace", match_pos);
        if (check_pos != std::string::npos) {
            size_t end_pos = code.find("\n", check_pos);
            if (end_pos != std::string::npos && match_pos >= check_pos && match_pos < end_pos) {
                in_using_namespace = true;
            }
        }
        if (!in_using_namespace && var_name != "int" && var_name != "double" && var_name != "float" && var_name != "bool" && var_name != "char" && var_name != "void" && var_name != "string" && var_name != "vector" && var_name != "std") {
            variable_map[var_name] = "v" + RandomStringGenerator::generate(10);
        }
        temp = match.suffix();
    }
    
    // 替换变量使用（跳过字符串字面量中的内容）
    for (const auto& pair : variable_map) {
        std::string var_name = pair.first;
        std::string new_name = pair.second;
        
        size_t pos = 0;
        while ((pos = result.find(var_name, pos)) != std::string::npos) {
            // 检查是否在字符串字面量中
            if (isInStringLiteral(result, pos)) {
                pos += var_name.length();
                continue;
            }
            
            // 检查是否是完整的单词
            bool is_word_start = (pos == 0 || !isalnum(result[pos - 1]) && result[pos - 1] != '_');
            bool is_word_end = (pos + var_name.length() >= result.length() || !isalnum(result[pos + var_name.length()]) && result[pos + var_name.length()] != '_');
            
            if (is_word_start && is_word_end) {
                result.replace(pos, var_name.length(), new_name);
                pos += new_name.length();
            } else {
                pos += var_name.length();
            }
        }
    }
    
    return result;
}

void VariableObfuscator::clear() {
    variable_map.clear();
}
