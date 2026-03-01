#ifndef USELESS_FUNCTION_GENERATOR_H
#define USELESS_FUNCTION_GENERATOR_H

#include <string>

class UselessFunctionGenerator {
private:
    std::string generateUselessFunction();
public:
    std::string generateUselessFunctions(int count);
};

#endif // USELESS_FUNCTION_GENERATOR_H