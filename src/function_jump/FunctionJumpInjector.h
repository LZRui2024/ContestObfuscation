#ifndef FUNCTION_JUMP_INJECTOR_H
#define FUNCTION_JUMP_INJECTOR_H

#include <string>
#include <map>
#include <vector>

class FunctionJumpInjector {
public:
    std::string injectFunctionJumps(const std::string& code);
    std::string getJumpTableDeclaration() const;
    void clear();

private:
    std::map<std::string, std::string> function_map;
    std::vector<std::string> jump_functions;
    std::string table_name;
    std::string wrapper_name;
};

#endif // FUNCTION_JUMP_INJECTOR_H
