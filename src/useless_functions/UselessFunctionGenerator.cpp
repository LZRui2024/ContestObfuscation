#include "UselessFunctionGenerator.h"
#include "../random_string/RandomStringGenerator.h"
#include <vector>
#include <cstdio>

std::string UselessFunctionGenerator::generateUselessFunction() {
    std::string function_name = "f" + RandomStringGenerator::generate(10);
    std::string param1_name = "a" + RandomStringGenerator::generate(5);
    std::string param2_name = "b" + RandomStringGenerator::generate(5);  // 使用不同的前缀
    std::string param3_name = "c" + RandomStringGenerator::generate(5);
    
    std::vector<std::string> function_templates = {
        // 简单单参数函数 - 2 个占位符
        "int %s(int %s) { return %s; }",
        "void %s() { int x = 0; }",
        "double %s(double %s) { return %s * 2.0; }",
        "bool %s(bool %s) { return %s; }",
        
        // 简单双参数函数 - 6 个占位符
        "int %s(int %s, int %s) { return %s + %s - %s; }",
        "double %s(double %s, double %s) { return (%s + %s) / 2.0; }",
        
        // 字符串函数 - 3 个占位符
        "int %s(const std::string& %s) { return %s.length(); }",
        "std::string %s(const std::string& %s) { return %s; }",
        
        // 无参数函数
        "void %s() { int arr[10]; for (int i = 0; i < 10; i++) { arr[i] = rand() % 100; } }",
        "int %s() { int sum = 0; for (int i = 0; i < 100; i++) { sum += i; } return sum; }",
        
        // 复杂单参数 - 4 个占位符
        "int %s(int %s) { volatile int t = %s; return t ^ 0; }",
        "double %s(double %s) { return %s >= 0 ? %s : -%s; }",
        "int %s(int %s) { return %s == 0 ? 1 : %s; }",
        
        // 复杂双参数 - 8 个占位符
        "int %s(int %s, int %s) { return (%s & %s) | (%s ^ %s); }",
        "bool %s(bool %s, bool %s) { return %s && %s || !(%s); }",
        "double %s(double %s, double %s) { return %s < %s ? %s : %s; }"
    };
    
    int template_index = rand() % function_templates.size();
    char buffer[256];
    
    // 根据参数数量和占位符数量分组
    std::vector<int> no_params = {8, 9};  // 无参数函数
    std::vector<int> one_param_2args = {0, 1, 2, 3};  // 单参数 2 个占位符
    std::vector<int> one_param_3args = {6, 7};  // 字符串函数 3 个占位符
    std::vector<int> one_param_4args = {10, 11, 12};  // 复杂单参数 4 个占位符
    std::vector<int> two_params_6args = {4, 5};  // 简单双参数 6 个占位符
    std::vector<int> two_params_8args = {13, 14, 15};  // 复杂双参数 8 个占位符
    
    auto contains = [](const std::vector<int>& vec, int val) {
        for (int v : vec) if (v == val) return true;
        return false;
    };
    
    if (contains(no_params, template_index)) {
        snprintf(buffer, sizeof(buffer), function_templates[template_index].c_str(), function_name.c_str());
    } else if (contains(one_param_2args, template_index)) {
        snprintf(buffer, sizeof(buffer), function_templates[template_index].c_str(), 
                 function_name.c_str(), param1_name.c_str(), param1_name.c_str());
    } else if (contains(one_param_3args, template_index)) {
        snprintf(buffer, sizeof(buffer), function_templates[template_index].c_str(), 
                 function_name.c_str(), param1_name.c_str(), param1_name.c_str());
    } else if (contains(one_param_4args, template_index)) {
        snprintf(buffer, sizeof(buffer), function_templates[template_index].c_str(), 
                 function_name.c_str(), param1_name.c_str(), param1_name.c_str(), param1_name.c_str(), param1_name.c_str());
    } else if (contains(two_params_6args, template_index)) {
        snprintf(buffer, sizeof(buffer), function_templates[template_index].c_str(), 
                 function_name.c_str(), param1_name.c_str(), param2_name.c_str(), 
                 param1_name.c_str(), param2_name.c_str(), param1_name.c_str());
    } else if (contains(two_params_8args, template_index)) {
        snprintf(buffer, sizeof(buffer), function_templates[template_index].c_str(), 
                 function_name.c_str(), param1_name.c_str(), param2_name.c_str(), 
                 param1_name.c_str(), param2_name.c_str(), param1_name.c_str(), param2_name.c_str(), 
                 param1_name.c_str(), param2_name.c_str());
    } else {
        snprintf(buffer, sizeof(buffer), function_templates[0].c_str(), 
                 function_name.c_str(), param1_name.c_str(), param1_name.c_str());
    }
    
    return std::string(buffer);
}

std::string UselessFunctionGenerator::generateUselessFunctions(int count) {
    std::string functions;
    for (int i = 0; i < count; i++) {
        functions += generateUselessFunction() + "\n";
    }
    return functions;
}