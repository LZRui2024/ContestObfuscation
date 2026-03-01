#include "TemplateMetaprogramming.h"
#include "../random_string/RandomStringGenerator.h"
#include <sstream>
#include <cstdlib>

std::string TemplateMetaprogramming::generateTemplateFunctions() {
    std::stringstream ss;
    
    // 添加模板元编程函数
    ss << "\n// Template metaprogramming utilities\n";
    ss << "template<int N>\n";
    ss << "struct Factorial {\n";
    ss << "    static const int value = N * Factorial<N - 1>::value;\n";
    ss << "};\n\n";
    ss << "template<>\n";
    ss << "struct Factorial<0> {\n";
    ss << "    static const int value = 1;\n";
    ss << "};\n\n";
    
    ss << "template<int N>\n";
    ss << "struct Fibonacci {\n";
    ss << "    static const int value = Fibonacci<N - 1>::value + Fibonacci<N - 2>::value;\n";
    ss << "};\n\n";
    ss << "template<>\n";
    ss << "struct Fibonacci<0> {\n";
    ss << "    static const int value = 0;\n";
    ss << "};\n\n";
    ss << "template<>\n";
    ss << "struct Fibonacci<1> {\n";
    ss << "    static const int value = 1;\n";
    ss << "};\n\n";
    
    ss << "template<int A, int B>\n";
    ss << "struct GCD {\n";
    ss << "    static const int value = GCD<B, A % B>::value;\n";
    ss << "};\n\n";
    ss << "template<int A>\n";
    ss << "struct GCD<A, 0> {\n";
    ss << "    static const int value = A;\n";
    ss << "};\n\n";
    
    return ss.str();
}

std::string TemplateMetaprogramming::generateConstexprFunctions() {
    std::stringstream ss;
    
    std::string func_name = "calc_" + RandomStringGenerator::generate(8);
    
    ss << "\n// Constexpr utilities\n";
    ss << "constexpr int " << func_name << "(int n) {\n";
    ss << "    return n <= 1 ? 1 : n * " << func_name << "(n - 1);\n";
    ss << "}\n\n";
    
    ss << "constexpr int power(int base, int exp) {\n";
    ss << "    return exp == 0 ? 1 : base * power(base, exp - 1);\n";
    ss << "}\n\n";
    
    ss << "constexpr int sum(int n) {\n";
    ss << "    return n <= 0 ? 0 : n + sum(n - 1);\n";
    ss << "}\n\n";
    
    return ss.str();
}

std::string TemplateMetaprogramming::addTemplateMetaprogramming(const std::string& code) {
    std::string result = code;
    
    // 在使用命名空间之后添加模板函数
    size_t using_namespace_pos = result.find("using namespace");
    if (using_namespace_pos != std::string::npos) {
        size_t end_of_line = result.find(';', using_namespace_pos);
        if (end_of_line != std::string::npos) {
            std::string templates = generateTemplateFunctions() + generateConstexprFunctions();
            result.insert(end_of_line + 1, "\n" + templates);
        }
    }
    
    return result;
}
