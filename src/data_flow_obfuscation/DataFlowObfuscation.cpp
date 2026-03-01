#include "DataFlowObfuscation.h"
#include "../random_string/RandomStringGenerator.h"
#include <regex>
#include <cstdlib>
#include <sstream>

DataFlowObfuscation::DataFlowObfuscation() : temp_var_count(0) {
}

std::string DataFlowObfuscation::introduceTempVariables(const std::string& expr) {
    std::string result = expr;
    
    // 查找简单的赋值语句
    std::regex assign_regex(R"((\w+)\s*=\s*([^;]+);)");
    std::smatch match;
    
    if (std::regex_search(result, match, assign_regex)) {
        std::string var_name = match[1].str();
        std::string value = match[2].str();
        
        // 生成临时变量
        std::string temp_var = "t" + RandomStringGenerator::generate(8);
        
        // 替换为：int temp_var = value; var_name = temp_var;
        std::stringstream new_code;
        new_code << "int " << temp_var << " = " << value << "; ";
        new_code << var_name << " = " << temp_var << ";";
        
        result = std::regex_replace(result, assign_regex, new_code.str(), std::regex_constants::format_first_only);
        temp_var_count++;
    }
    
    return result;
}

std::string DataFlowObfuscation::obfuscateDataFlow(const std::string& code) {
    std::string result = code;
    
    // 在函数体内引入临时变量
    size_t pos = result.find("{");
    while (pos != std::string::npos) {
        // 跳过预处理指令
        if (pos > 0 && result[pos-1] == '#') {
            pos = result.find("{", pos + 1);
            continue;
        }
        
        // 查找下一行
        size_t line_end = result.find(";", pos);
        if (line_end != std::string::npos && line_end < pos + 200) {
            std::string line = result.substr(pos, line_end - pos + 1);
            std::string obfuscated_line = introduceTempVariables(line);
            
            if (obfuscated_line != line) {
                result.replace(pos, line_end - pos + 1, obfuscated_line);
            }
        }
        
        pos = result.find("{", pos + 1);
    }
    
    return result;
}

void DataFlowObfuscation::clear() {
    temp_var_count = 0;
}
