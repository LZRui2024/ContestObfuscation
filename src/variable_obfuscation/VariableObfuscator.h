#ifndef VARIABLE_OBFUSCATOR_H
#define VARIABLE_OBFUSCATOR_H

#include <string>
#include <unordered_map>

class VariableObfuscator {
private:
    std::unordered_map<std::string, std::string> variable_map;
public:
    std::string obfuscateVariables(const std::string& code);
    void clear();
};

#endif // VARIABLE_OBFUSCATOR_H