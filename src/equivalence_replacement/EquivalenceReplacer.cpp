#include "EquivalenceReplacer.h"
#include "../random_string/RandomStringGenerator.h"
#include <regex>
#include <cstdlib>

EquivalenceReplacer::EquivalenceReplacer() : replacement_count(0) {
}

std::string EquivalenceReplacer::replaceMultiplication(const std::string& expr) {
    std::string result = expr;
    
    // 替换 * 2 为 << 1
    std::regex mul2_regex(R"((\w+)\s*\*\s*2\b)");
    result = std::regex_replace(result, mul2_regex, "(($1 << 1) + ($1 & 1) - ($1 & 1))");
    
    // 替换 * 4 为 << 2
    std::regex mul4_regex(R"((\w+)\s*\*\s*4\b)");
    result = std::regex_replace(result, mul4_regex, "(($1 << 2) + (($1 >> 1) & 3) - (($1 >> 1) & 3))");
    
    // 替换 * 8 为 << 3
    std::regex mul8_regex(R"((\w+)\s*\*\s*8\b)");
    result = std::regex_replace(result, mul8_regex, "(($1 << 3) + (($1 >> 2) & 7) - (($1 >> 2) & 7))");
    
    return result;
}

std::string EquivalenceReplacer::replaceDivision(const std::string& expr) {
    std::string result = expr;
    
    // 替换 / 2 为 >> 1
    std::regex div2_regex(R"((\w+)\s*/\s*2\b)");
    result = std::regex_replace(result, div2_regex, "((($1 + 1) >> 1) + (($1 + 1) & 1) - (($1 + 1) & 1))");
    
    // 替换 / 4 为 >> 2
    std::regex div4_regex(R"((\w+)\s*/\s*4\b)");
    result = std::regex_replace(result, div4_regex, "((($1 + 3) >> 2) + (($1 + 3) & 3) - (($1 + 3) & 3))");
    
    return result;
}

std::string EquivalenceReplacer::replaceAddition(const std::string& expr) {
    std::string result = expr;
    
    // 替换 a + b 为 (a ^ b) + 2*(a & b)
    std::regex add_regex(R"((\w+)\s*\+\s*(\w+))");
    result = std::regex_replace(result, add_regex, "(($1 ^ $2) + (($1 & $2) << 1))");
    
    return result;
}

std::string EquivalenceReplacer::replaceSubtraction(const std::string& expr) {
    std::string result = expr;
    
    // 替换 a - b 为 (a ^ b) - 2*((~a) & b)
    std::regex sub_regex(R"((\w+)\s*-\s*(\w+))");
    result = std::regex_replace(result, sub_regex, "(($1 ^ $2) + (($1 & $2) << 1) - ($2 << 1))");
    
    return result;
}

std::string EquivalenceReplacer::replaceEquivalences(const std::string& code) {
    std::string result = code;
    
    // 随机选择是否应用每种替换
    if (rand() % 2) {
        result = replaceMultiplication(result);
        replacement_count++;
    }
    
    if (rand() % 2) {
        result = replaceDivision(result);
        replacement_count++;
    }
    
    if (rand() % 2) {
        result = replaceAddition(result);
        replacement_count++;
    }
    
    if (rand() % 2) {
        result = replaceSubtraction(result);
        replacement_count++;
    }
    
    return result;
}

void EquivalenceReplacer::clear() {
    replacement_count = 0;
}
