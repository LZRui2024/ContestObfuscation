#include "CodeExpansion.h"
#include "../random_string/RandomStringGenerator.h"
#include <sstream>
#include <regex>

std::string CodeExpansion::expandForLoop(const std::string& code) {
    std::string result = code;
    
    // 简单的循环展开：将小循环展开
    // 例如：for(int i=0; i<3; i++) { body; } 
    // 展开为：{ int i=0; body; i++; body; i++; body; }
    
    std::regex for_regex(R"(\bfor\s*\(\s*int\s+(\w+)\s*=\s*(\d+)\s*;\s*\1\s*<\s*(\d+)\s*;\s*\+\+\1\s*\)\s*\{([^}]*)\})");
    
    std::smatch match;
    if (std::regex_search(result, match, for_regex)) {
        std::string var_name = match[1];
        int start = std::stoi(match[2]);
        int end = std::stoi(match[3]);
        std::string body = match[4];
        
        // 只展开小循环（最多 5 次）
        if (end - start <= 5 && end - start > 0) {
            std::stringstream ss;
            ss << "{ int " << var_name << " = " << start << ";";
            
            for (int i = start; i < end; i++) {
                ss << body;
                if (i < end - 1) {
                    ss << " " << var_name << "++;";
                }
            }
            ss << " }";
            
            result = std::regex_replace(result, for_regex, ss.str());
        }
    }
    
    return result;
}

std::string CodeExpansion::expandLoops(const std::string& code) {
    std::string result = code;
    
    // 多次尝试展开循环
    for (int i = 0; i < 3; i++) {
        result = expandForLoop(result);
    }
    
    return result;
}
