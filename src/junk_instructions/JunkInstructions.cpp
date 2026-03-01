#include "JunkInstructions.h"
#include "../random_string/RandomStringGenerator.h"
#include <cstdlib>
#include <sstream>
#include <vector>

std::string JunkInstructions::generateJunkCode() {
    int template_type = rand() % 10;
    std::string var_name = "j" + RandomStringGenerator::generate(6);
    int v1 = rand() % 100 + 1;
    int v2 = v1;  // 确保相减为 0
    int v3 = rand() % 100 + 1;
    int v4 = rand() % 10 + 1;
    
    std::stringstream ss;
    
    switch (template_type) {
        case 0:
            ss << "volatile int " << var_name << " = (" << v1 << " ^ " << v2 << ") | (" << v3 << " & ~" << v4 << ");";
            break;
        case 1:
            ss << "volatile int " << var_name << " = (" << v1 << " & " << v2 << ") ^ (" << v3 << " | " << v4 << ");";
            break;
        case 2:
            ss << "volatile int " << var_name << " = ((" << v1 << " << " << v4 << ") >> " << v4 << ") & " << v3 << ";";
            break;
        case 3:
            ss << "volatile int " << var_name << " = (" << v1 << " - " << v2 << ") * (" << v3 << " + " << v4 << ");";
            break;
        case 4:
            ss << "volatile int " << var_name << " = (" << v1 << " / " << v1 << ") - 1;";
            break;
        case 5:
            ss << "volatile int " << var_name << " = " << v3 << " % (" << v4 << " + " << v1 % 10 + ");";
            break;
        case 6: {
            std::string var2 = "k" + RandomStringGenerator::generate(6);
            ss << "volatile int " << var_name << " = " << v1 << "; " << var2 << " = " << v3 << " - " << var_name << ";";
            break;
        }
        case 7:
            ss << "volatile int " << var_name << " = ((" << v1 << " + " << v2 << ") * (" << v3 << " - " << v4 << ")) / (" << v1 << " + " << v4 << ");";
            break;
        case 8:
            ss << "volatile int " << var_name << " = (" << v1 << " << " << v4 << ") | (" << v3 << " >> " << v4 << ");";
            break;
        case 9:
            ss << "volatile int " << var_name << " = rand() % " << v3 << " + rand() % " << v4 << ";";
            break;
    }
    
    return ss.str();
}

std::string JunkInstructions::addJunkInstructions(const std::string& code) {
    std::string result = code;
    
    // 在每 5 个分号后插入花指令
    int count = 0;
    size_t pos = 0;
    
    while ((pos = result.find(';', pos)) != std::string::npos) {
        count++;
        
        // 随机插入花指令
        if (count % 5 == 0 && rand() % 3 == 0) {
            std::string junk = generateJunkCode();
            result.insert(pos + 1, " " + junk);
        }
        
        pos++;
    }
    
    return result;
}
