#include "FakeControlFlow.h"
#include "../random_string/RandomStringGenerator.h"
#include <cstdlib>
#include <sstream>
#include <vector>

FakeControlFlow::FakeControlFlow() : fake_branch_count(0) {
}

std::string FakeControlFlow::generateOpaquePredicate() {
    // 生成永远为假的条件
    std::string predicates[] = {
        "sizeof(int) == sizeof(char)",
        "0 && 1",
        "(__cplusplus < 199711L)",
        "(nullptr != nullptr)",
        "(1 > 2 && 3 < 4)"
    };
    return predicates[rand() % 5];
}

std::string FakeControlFlow::addFakeControlFlow(const std::string& code) {
    std::string result = code;
    
    // 收集所有需要插入的位置（从后向前插入，避免位置偏移）
    std::vector<size_t> insert_positions;
    
    // 先收集所有"{"的位置
    size_t pos = result.find("{");
    while (pos != std::string::npos) {
        // 跳过预处理指令
        if (pos > 0 && result[pos-1] == '#') {
            pos = result.find("{", pos + 1);
            continue;
        }
        
        // 检查是否在字符串或注释中（简化处理）
        bool in_string = false;
        for (size_t i = 0; i < pos; i++) {
            if (result[i] == '"') {
                in_string = !in_string;
            }
        }
        if (in_string) {
            pos = result.find("{", pos + 1);
            continue;
        }
        
        insert_positions.push_back(pos);
        pos = result.find("{", pos + 1);
    }
    
    // 从后向前插入虚假代码，避免影响前面的位置
    for (int i = insert_positions.size() - 1; i >= 0; i--) {
        pos = insert_positions[i];
        
        // 生成虚假代码块 - 现在在宏替换之后执行，可以正常使用类型关键字
        std::stringstream fake_code;
        std::string var_name = "v" + RandomStringGenerator::generate(8);
        int value1 = rand() % 1000;
        int value2 = rand() % 1000;
        
        fake_code << "\n";
        fake_code << "    if (" << generateOpaquePredicate() << ") {\n";
        fake_code << "        int " << var_name << " = " << value1 << ";\n";
        fake_code << "        " << var_name << " += " << value2 << ";\n";
        fake_code << "    }\n";
        
        // 在函数体的第一个语句前插入
        size_t next_line = result.find("\n", pos);
        if (next_line != std::string::npos && next_line < pos + 50) {
            result.insert(next_line, fake_code.str());
            fake_branch_count++;
        }
    }
    
    return result;
}

void FakeControlFlow::clear() {
    fake_branch_count = 0;
}
