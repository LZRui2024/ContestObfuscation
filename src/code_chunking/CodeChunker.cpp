#include "CodeChunker.h"
#include "../random_string/RandomStringGenerator.h"
#include <vector>

std::string CodeChunker::generateChunkFunction() {
    std::string function_name = "c" + RandomStringGenerator::generate(10);
    return "void " + function_name + "() {}\n";
}

std::string CodeChunker::chunkCode(const std::string& code) {
    std::string result = code;
    std::vector<size_t> semicolon_positions;
    
    // 先收集所有分号的位置
    std::string temp_code = code;
    size_t pos = 0;
    size_t total_pos = 0;
    
    while ((pos = temp_code.find(";")) != std::string::npos) {
        semicolon_positions.push_back(total_pos + pos);
        total_pos += pos + 1;
        temp_code = temp_code.substr(pos + 1);
        if (temp_code.empty()) break;
    }
    
    // 按照从后往前的顺序插入，避免位置偏移
    int count = 0;
    for (auto it = semicolon_positions.rbegin(); it != semicolon_positions.rend(); ++it) {
        if (count % 10 == 0) {
            // 不再插入函数调用，只添加空语句
            result.insert(*it + 1, "");
        }
        count++;
    }
    
    return result;
}