#include "AntiSemantic.h"
#include "../random_string/RandomStringGenerator.h"
#include <regex>
#include <sstream>

AntiSemantic::AntiSemantic() : goto_count(0) {
}

std::string AntiSemantic::replaceLoopWithGoto(const std::string& code) {
    std::string result = code;
    
    // 查找简单的 for 循环
    std::regex for_regex(R"(for\s*\(\s*int\s+(\w+)\s*=\s*(\d+)\s*;\s*\1\s*<\s*(\d+)\s*;\s*\+\+\1\s*\)\s*\{([^}]*)\})");
    std::smatch match;
    
    if (std::regex_search(result, match, for_regex)) {
        std::string var_name = match[1].str();
        std::string init_val = match[2].str();
        std::string limit = match[3].str();
        std::string body = match[4].str();
        
        std::string label_start = "loop_start_" + RandomStringGenerator::generate(6);
        std::string label_end = "loop_end_" + RandomStringGenerator::generate(6);
        
        std::stringstream goto_version;
        goto_version << "int " << var_name << " = " << init_val << ";\n";
        goto_version << label_start << ":\n";
        goto_version << "if (" << var_name << " >= " << limit << ") goto " << label_end << ";\n";
        goto_version << body << "\n";
        goto_version << var_name << "++;\n";
        goto_version << "goto " << label_start << ";\n";
        goto_version << label_end << ";\n";
        
        result = std::regex_replace(result, for_regex, goto_version.str(), std::regex_constants::format_first_only);
        goto_count++;
    }
    
    return result;
}

std::string AntiSemantic::addAntiSemanticAnalysis(const std::string& code) {
    std::string result = code;
    
    // 替换 for 循环为 goto 版本
    result = replaceLoopWithGoto(result);
    
    return result;
}

void AntiSemantic::clear() {
    goto_count = 0;
}
