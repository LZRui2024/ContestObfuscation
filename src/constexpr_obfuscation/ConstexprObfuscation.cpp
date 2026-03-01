#include "ConstexprObfuscation.h"
#include "../random_string/RandomStringGenerator.h"
#include <sstream>
#include <regex>
#include <cstdlib>

std::string ConstexprObfuscation::replaceWithConstexpr(const std::string& code) {
    std::string result = code;
    
    // 替换整数常量为表达式（跳过变量声明和预处理指令）
    std::regex int_regex(R"(\b(\d+)\b)");
    
    std::smatch match;
    std::string temp = result;
    std::string output;
    size_t last_pos = 0;
    
    int count = 0;
    while (std::regex_search(temp, match, int_regex)) {
        output += temp.substr(0, match.position());
        
        std::string num_str = match.str();
        
        // 检查是否在变量声明中（前面有 int, volatile 等关键字）
        if (output.size() > 5) {
            std::string prefix = output.substr(output.size() - 10);
            if (prefix.find("int ") != std::string::npos ||
                prefix.find("volatile ") != std::string::npos ||
                prefix.find("auto ") != std::string::npos ||
                prefix.find("double ") != std::string::npos ||
                prefix.find("#") != std::string::npos) {
                output += num_str;
                temp = match.suffix();
                continue;
            }
        }
        
        // 随机选择一些数字替换为表达式
        if (rand() % 5 == 0 && num_str.size() <= 2) {
            int num = std::stoi(num_str);
            int a = rand() % (num + 10);
            int b = num - a;
            
            std::stringstream ss;
            if (rand() % 2 == 0) {
                ss << "(" << a << " + " << b << ")";
            } else {
                ss << "(" << (a + 5) << " - " << (5 - b) << ")";
            }
            output += ss.str();
            count++;
        } else {
            output += num_str;
        }
        
        temp = match.suffix();
    }
    
    output += temp;
    return output;
}

std::string ConstexprObfuscation::obfuscateConstants(const std::string& code) {
    return replaceWithConstexpr(code);
}
