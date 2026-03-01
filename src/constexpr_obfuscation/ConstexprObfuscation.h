#ifndef CONSTEXPR_OBFUSCATION_H
#define CONSTEXPR_OBFUSCATION_H

#include <string>

class ConstexprObfuscation {
public:
    std::string obfuscateConstants(const std::string& code);
    
private:
    std::string replaceWithConstexpr(const std::string& code);
};

#endif // CONSTEXPR_OBFUSCATION_H
