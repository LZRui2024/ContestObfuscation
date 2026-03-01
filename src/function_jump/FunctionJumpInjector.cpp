#include "FunctionJumpInjector.h"
#include "../random_string/RandomStringGenerator.h"
#include <sstream>
#include <regex>

std::string FunctionJumpInjector::injectFunctionJumps(const std::string& code) {
    std::string result = code;
    
    // 在 main 函数之前插入干扰函数
    size_t main_pos = result.find("int main");
    if (main_pos != std::string::npos) {
        std::stringstream ss;
        
        // 生成 3 个干扰函数
        for (int i = 0; i < 3; i++) {
            std::string func = "a" + RandomStringGenerator::generate(4);
            std::string var = "b" + RandomStringGenerator::generate(4);
            ss << "int " << func << "() { int " << var << " = " << (i * 17 + 7) << "; " << var << " = (" << var << " ^ 0x1234); return " << var << "; }\n";
        }
        
        result.insert(main_pos, ss.str());
    }
    
    return result;
}

std::string FunctionJumpInjector::getJumpTableDeclaration() const {
    return "";
}

void FunctionJumpInjector::clear() {
    function_map.clear();
    jump_functions.clear();
    table_name.clear();
    wrapper_name.clear();
}
