#ifndef CODE_EXPANSION_H
#define CODE_EXPANSION_H

#include <string>

class CodeExpansion {
public:
    std::string expandLoops(const std::string& code);
    
private:
    std::string expandForLoop(const std::string& code);
};

#endif // CODE_EXPANSION_H
