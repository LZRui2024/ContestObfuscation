#include "ExceptionObfuscator.h"
#include "../random_string/RandomStringGenerator.h"
#include <vector>
#include <sstream>

ExceptionObfuscator::ExceptionObfuscator() {
}

std::string ExceptionObfuscator::generateExceptionCode(const std::string& code) {
    std::string exception_var = "e" + RandomStringGenerator::generate(10);
    
    std::stringstream ss;
    ss << "try {";
    ss << "    throw 0;";
    ss << "} catch (int " << exception_var << ") {";
    ss << "    " << code;
    ss << "}";
    
    return ss.str();
}

bool ExceptionObfuscator::isClassOrStruct(const std::string& code, size_t brace_pos) {
    int check_pos = static_cast<int>(brace_pos) - 1;
    
    while (check_pos >= 0 && isspace(code[check_pos])) {
        check_pos--;
    }
    
    int identifier_end = check_pos;
    while (check_pos >= 0 && (isalnum(code[check_pos]) || code[check_pos] == '_')) {
        check_pos--;
    }
    
    if (check_pos < 0 || identifier_end < check_pos) return false;
    
    std::string identifier = code.substr(check_pos + 1, identifier_end - check_pos);
    
    return (identifier == "struct" || identifier == "class");
}

bool ExceptionObfuscator::isFunctionBody(const std::string& code, size_t brace_pos) {
    int check_pos = static_cast<int>(brace_pos) - 1;
    
    while (check_pos >= 0 && isspace(code[check_pos])) {
        check_pos--;
    }
    
    if (check_pos < 0) return false;
    
    if (code[check_pos] == ')') {
        int paren_count = 1;
        check_pos--;
        while (check_pos >= 0 && paren_count > 0) {
            if (code[check_pos] == ')') paren_count++;
            else if (code[check_pos] == '(') paren_count--;
            check_pos--;
        }
        
        while (check_pos >= 0 && isspace(code[check_pos])) {
            check_pos--;
        }
        
        while (check_pos >= 0 && (isalnum(code[check_pos]) || code[check_pos] == '_')) {
            check_pos--;
        }
        
        while (check_pos >= 0 && isspace(code[check_pos])) {
            check_pos--;
        }
        
        if (check_pos >= 0) {
            std::vector<std::string> return_types = {"void", "int", "double", "float", "char", "std::string", "bool", "auto"};
            for (const auto& rt : return_types) {
                if (check_pos + 1 >= static_cast<int>(rt.length())) {
                    std::string prev_word = code.substr(check_pos - rt.length() + 1, rt.length());
                    if (prev_word == rt) {
                        return true;
                    }
                }
            }
        }
        
        return true;
    }
    
    return false;
}

std::string ExceptionObfuscator::obfuscateWithExceptions(const std::string& code) {
    std::string result = code;
    size_t pos = 0;
    
    while (pos < result.length()) {
        if (result.substr(pos, 2) == "//") {
            size_t end = result.find("\n", pos);
            if (end == std::string::npos) break;
            pos = end + 1;
        } else if (result.substr(pos, 2) == "/*") {
            size_t end = result.find("*/", pos + 2);
            if (end == std::string::npos) break;
            pos = end + 2;
        } else if (result.substr(pos, 8) == "#include") {
            size_t end = result.find("\n", pos);
            if (end == std::string::npos) break;
            pos = end + 1;
        } else if (result.substr(pos, 6) == "#define") {
            size_t end = result.find("\n", pos);
            if (end == std::string::npos) break;
            pos = end + 1;
        } else {
            break;
        }
    }
    
    std::vector<std::string> return_types = {"void", "int", "double", "float", "char", "std::string", "bool"};
    
    while (pos < result.length()) {
        bool found_return_type = false;
        size_t return_type_end = pos;
        
        for (const auto& return_type : return_types) {
            if (pos + return_type.length() <= result.length() && 
                result.substr(pos, return_type.length()) == return_type) {
                return_type_end = pos + return_type.length();
                found_return_type = true;
                break;
            }
        }
        
        if (!found_return_type) {
            pos++;
            continue;
        }
        
        while (return_type_end < result.length() && isspace(result[return_type_end])) {
            return_type_end++;
        }
        
        size_t name_end = result.find("(", return_type_end);
        if (name_end == std::string::npos) {
            pos = return_type_end;
            continue;
        }
        
        std::string function_name = result.substr(return_type_end, name_end - return_type_end);
        
        if (function_name == "main" || function_name.find("decrypt") != std::string::npos) {
            pos = name_end;
            continue;
        }
        
        size_t body_start = result.find("{", name_end);
        if (body_start == std::string::npos) {
            pos = name_end;
            continue;
        }
        
        if (isClassOrStruct(result, body_start)) {
            pos = body_start + 1;
            continue;
        }
        
        if (!isFunctionBody(result, body_start)) {
            pos = body_start + 1;
            continue;
        }
        
        int brace_count = 1;
        size_t body_end = body_start + 1;
        while (body_end < result.length() && brace_count > 0) {
            if (result[body_end] == '{') brace_count++;
            else if (result[body_end] == '}') brace_count--;
            body_end++;
        }
        
        if (brace_count == 0) {
            std::string function_body = result.substr(body_start + 1, body_end - body_start - 2);
            
            if (function_body.find("try {") != std::string::npos || function_body.length() < 2) {
                pos = body_end;
                continue;
            }
            
            std::string obfuscated_body = generateExceptionCode(function_body);
            
            result.replace(body_start + 1, body_end - body_start - 2, obfuscated_body);
            pos = body_start + 1 + obfuscated_body.length();
        } else {
            pos = body_end;
        }
    }
    
    return result;
}

void ExceptionObfuscator::clear() {
}
