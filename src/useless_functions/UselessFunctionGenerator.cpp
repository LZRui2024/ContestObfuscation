#include "UselessFunctionGenerator.h"
#include "../random_string/RandomStringGenerator.h"
#include <vector>
#include <cstdio>

std::string UselessFunctionGenerator::generateUselessFunction() {
    std::string function_name = "f" + RandomStringGenerator::generate(10);
    std::string param1_name = "p" + RandomStringGenerator::generate(5);
    std::string param2_name = "p" + RandomStringGenerator::generate(5);
    std::string param3_name = "p" + RandomStringGenerator::generate(5);
    
    std::vector<std::string> function_templates = {
        "int %s(int %s) { return %s; }",
        "void %s() { int x = 0; }",
        "double %s(double %s) { return %s * 2.0; }",
        "bool %s(bool %s) { return %s; }",
        "int %s(int %s, int %s) { return %s + %s - %s; }",
        "int %s(const std::string& %s) { return %s.length(); }",
        "void %s() { int arr[10]; for (int i = 0; i < 10; i++) { arr[i] = rand() % 100; } }",
        "double %s(double %s, double %s) { return (%s * %s) / (%s + 1.0); }",
        "std::string %s(const std::string& %s) { std::string result = %s; return result; }",
        "int %s() { int sum = 0; for (int i = 0; i < 100; i++) { sum += i; } return sum; }"
    };
    
    int template_index = rand() % function_templates.size();
    char buffer[256];
    
    switch (template_index) {
        case 0:
        case 1:
        case 2:
        case 3:
            snprintf(buffer, sizeof(buffer), function_templates[template_index].c_str(), 
                     function_name.c_str(), param1_name.c_str(), param1_name.c_str());
            break;
        case 4:
        case 7:
            snprintf(buffer, sizeof(buffer), function_templates[template_index].c_str(), 
                     function_name.c_str(), param1_name.c_str(), param2_name.c_str(), 
                     param1_name.c_str(), param2_name.c_str(), param1_name.c_str());
            break;
        case 5:
        case 8:
            snprintf(buffer, sizeof(buffer), function_templates[template_index].c_str(), 
                     function_name.c_str(), param1_name.c_str(), param1_name.c_str());
            break;
        case 6:
        case 9:
            snprintf(buffer, sizeof(buffer), function_templates[template_index].c_str(), 
                     function_name.c_str());
            break;
        default:
            snprintf(buffer, sizeof(buffer), function_templates[0].c_str(), 
                     function_name.c_str(), param1_name.c_str(), param1_name.c_str());
            break;
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