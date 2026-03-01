#ifndef FUNCTION_INLINER_H
#define FUNCTION_INLINER_H

#include <string>
#include <map>

class FunctionInliner {
public:
    FunctionInliner();
    std::string inlineFunctions(const std::string& code);
    void clear();

private:
    std::map<std::string, std::string> function_map;
    std::string extractFunctions(const std::string& code);
    std::string inlineFunctionCalls(const std::string& code);
};

#endif // FUNCTION_INLINER_H
