#include "ExceptionObfuscator.h"
#include "../random_string/RandomStringGenerator.h"
#include <sstream>
#include <regex>

std::string ExceptionObfuscator::wrapInTryCatch(const std::string& code) {
    std::string result = code;
    
    // 在 main 函数外层包裹 try-catch
    std::regex main_regex(R"((int\s+main\s*\([^)]*\)\s*\{))");
    
    std::smatch match;
    if (std::regex_search(result, match, main_regex)) {
        size_t main_pos = match.position();
        size_t brace_pos = result.find('{', main_pos);
        
        if (brace_pos != std::string::npos) {
            std::stringstream ss;
            ss << result.substr(0, brace_pos + 1);
            ss << "\n    try {";
            
            // 找到 main 函数的内容
            std::string rest = result.substr(brace_pos + 1);
            
            // 添加虚假的 catch 块
            ss << "\n    } catch (const std::exception& e) {\n";
            ss << "        volatile int " << RandomStringGenerator::generate(8) << " = 0;\n";
            ss << "        (void)e;\n";
            ss << "    } catch (...) {\n";
            ss << "        volatile int " << RandomStringGenerator::generate(8) << " = 0;\n";
            ss << "    }\n";
            
            ss << rest;
            
            result = ss.str();
        }
    }
    
    return result;
}

std::string ExceptionObfuscator::addExceptionHandling(const std::string& code) {
    return wrapInTryCatch(code);
}
