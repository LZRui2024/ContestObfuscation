#include "VariableObfuscator.h"
#include "../random_string/RandomStringGenerator.h"
#include <regex>

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
    
    // 替换变量使用
    for (const auto& pair : variable_map) {
        std::regex use_regex(R"((\b)" + pair.first + R"(\b))");
        result = std::regex_replace(result, use_regex, pair.second);
    }
    
    return result;
}

void VariableObfuscator::clear() {
    variable_map.clear();
}