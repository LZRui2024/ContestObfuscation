#ifndef FUNCTION_JUMP_INJECTOR_H
#define FUNCTION_JUMP_INJECTOR_H

#include <string>
#include <unordered_map>

class FunctionJumpInjector {
private:
    std::unordered_map<std::string, std::string> function_map;
    std::string generateJumpFunction(const std::string& original_function);
public:
    std::string injectFunctionJumps(const std::string& code);
    std::string generateJumpFunctions();
    void clear();
};

#endif // FUNCTION_JUMP_INJECTOR_H