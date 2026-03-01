#ifndef FUNCTION_OBFUSCATOR_H
#define FUNCTION_OBFUSCATOR_H

#include <string>
#include <unordered_map>

class FunctionObfuscator {
private:
    std::unordered_map<std::string, std::string> function_map;
    std::unordered_map<std::string, std::string> reverse_map;
public:
    std::string obfuscateFunctionName(const std::string& original_name);
    std::string getOriginalName(const std::string& obfuscated_name);
    std::string obfuscateFunctions(const std::string& code);
    void clear();
};

#endif // FUNCTION_OBFUSCATOR_H