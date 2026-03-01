#include "ControlFlowFlattener.h"
#include "../random_string/RandomStringGenerator.h"
#include <vector>
#include <sstream>

ControlFlowFlattener::ControlFlowFlattener() {
}

std::string ControlFlowFlattener::generateStateVariable() {
    return "s" + RandomStringGenerator::generate(10);
}

bool ControlFlowFlattener::containsControlFlow(const std::string& code) {
    return code.find("switch(") != std::string::npos || 
           code.find("while(true)") != std::string::npos ||
           code.find("for(;;)") != std::string::npos;
}

std::vector<std::string> ControlFlowFlattener::extractStatements(const std::string& function_body) {
    std::vector<std::string> statements;
    std::string current_statement;
    int brace_depth = 0;
    int paren_depth = 0;
    bool in_string = false;
    char string_char = 0;
    bool in_for_loop = false;
    
    for (size_t i = 0; i < function_body.length(); i++) {
        char c = function_body[i];
        
        if (!in_string && (c == '"' || c == '\'')) {
            in_string = true;
            string_char = c;
        } else if (in_string && c == string_char && (i == 0 || function_body[i-1] != '\\')) {
            in_string = false;
        }
        
        if (!in_string) {
            if (c == '(') {
                paren_depth++;
                if (current_statement.find("for") != std::string::npos && 
                    current_statement.rfind("for") <= current_statement.length() - 3) {
                    in_for_loop = true;
                }
            } else if (c == ')') {
                paren_depth--;
                if (in_for_loop && paren_depth == 0) {
                    in_for_loop = false;
                }
            } else if (c == '{') {
                brace_depth++;
            } else if (c == '}') {
                brace_depth--;
            }
        }
        
        current_statement += c;
        
        if (c == ';' && brace_depth == 0 && paren_depth == 0 && !in_string && !in_for_loop) {
            std::string trimmed = current_statement;
            size_t start = trimmed.find_first_not_of(" \t\n\r");
            if (start != std::string::npos) {
                trimmed = trimmed.substr(start);
                if (!trimmed.empty() && trimmed != ";") {
                    statements.push_back(trimmed);
                }
            }
            current_statement = "";
        }
    }
    
    if (!current_statement.empty()) {
        std::string trimmed = current_statement;
        size_t start = trimmed.find_first_not_of(" \t\n\r");
        if (start != std::string::npos) {
            trimmed = trimmed.substr(start);
            if (!trimmed.empty() && trimmed != ";") {
                statements.push_back(trimmed);
            }
        }
    }
    
    return statements;
}

std::string ControlFlowFlattener::flattenControlFlow(const std::string& code) {
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
        std::string matched_return_type;
        
        for (const auto& return_type : return_types) {
            if (pos + return_type.length() <= result.length() && 
                result.substr(pos, return_type.length()) == return_type) {
                return_type_end = pos + return_type.length();
                matched_return_type = return_type;
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
        
        if (function_name == "main" || function_name.find("decrypt") != std::string::npos || 
            function_name.length() < 3 || function_name[0] != 'f') {
            pos = name_end;
            continue;
        }
        
        size_t body_start = result.find("{", name_end);
        if (body_start == std::string::npos) {
            pos = name_end;
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
            
            if (containsControlFlow(function_body)) {
                pos = body_end;
                continue;
            }
            
            std::vector<std::string> statements = extractStatements(function_body);
            
            if (statements.size() > 1) {
                std::string state_var = generateStateVariable();
                std::stringstream flattened;
                
                flattened << "    int " << state_var << " = 0;\n";
                flattened << "    while(true) {\n";
                flattened << "        switch(" << state_var << ") {\n";
                
                for (size_t i = 0; i < statements.size(); i++) {
                    flattened << "        case " << i << ":\n";
                    flattened << "            " << statements[i] << "\n";
                    flattened << "            " << state_var << " = " << (i + 1) << ";\n";
                    flattened << "            break;\n";
                }
                
                flattened << "        case " << statements.size() << ":\n";
                if (matched_return_type == "void") {
                    flattened << "            return;\n";
                } else {
                    flattened << "            return 0;\n";
                }
                flattened << "        default:\n";
                flattened << "            break;\n";
                flattened << "        }\n";
                flattened << "    }\n";
                
                std::string new_function_body = flattened.str();
                result.replace(body_start + 1, body_end - body_start - 2, new_function_body);
                pos = body_start + 1 + new_function_body.length();
            } else {
                pos = body_end;
            }
        } else {
            pos = body_end;
        }
    }
    
    return result;
}

void ControlFlowFlattener::clear() {
}
