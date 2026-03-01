#include "AdvancedControlFlow.h"
#include "../random_string/RandomStringGenerator.h"
#include <sstream>
#include <cstdlib>

std::string AdvancedControlFlow::generateStateDispatcher() {
    std::stringstream ss;
    
    // 生成状态调度变量，使用固定名称
    ss << "volatile int st_0 = " << (rand() % 100) << ";\n";
    ss << "volatile int st_1 = st_0 ^ " << (rand() % 50) << ";\n";
    ss << "volatile int st_2 = (st_0 + st_1) % 10;\n";
    
    return ss.str();
}

std::string AdvancedControlFlow::addFakeStateTransitions() {
    std::stringstream ss;
    
    // 使用已定义的状态变量，不再创建新的
    ss << "switch ((st_0 + " << (rand() % 10) << ") % 3) {\n";
    ss << "    case 0: st_0 = (st_0 * " << (rand() % 10 + 1) << ") % 100; break;\n";
    ss << "    case 1: st_0 = (st_0 + " << (rand() % 10) << ") % 100; break;\n";
    ss << "    case 2: st_0 = (st_0 ^ " << (rand() % 10) << ") % 100; break;\n";
    ss << "}\n";
    
    return ss.str();
}

std::string AdvancedControlFlow::addAdvancedFlattening(const std::string& code) {
    std::string result = code;
    
    // 在 main 函数开始处添加状态调度变量
    size_t main_pos = result.find("int main");
    if (main_pos != std::string::npos) {
        size_t brace_pos = result.find('{', main_pos);
        if (brace_pos != std::string::npos) {
            std::string state_vars = generateStateDispatcher();
            result.insert(brace_pos + 1, "\n    " + state_vars);
            
            // 在 main 函数中随机插入状态转换（只插入 2-3 个，避免过多）
            size_t pos = brace_pos + 1;
            int count = 0;
            int insert_count = 0;
            int max_inserts = 2 + rand() % 2;  // 随机插入 2-3 个
            
            while ((pos = result.find(';', pos)) != std::string::npos && insert_count < max_inserts) {
                count++;
                if (count % 5 == 0) {  // 每 5 个分号插入一个
                    std::string fake_transition = addFakeStateTransitions();
                    result.insert(pos + 1, "\n    " + fake_transition);
                    pos += fake_transition.length() + 5;  // 跳过插入的代码
                    insert_count++;
                }
                pos++;
            }
        }
    }
    
    return result;
}
