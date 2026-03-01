#ifndef EXCEPTION_OBFUSCATION_H
#define EXCEPTION_OBFUSCATION_H

#include <string>

class ExceptionObfuscator {
public:
    std::string addExceptionHandling(const std::string& code);
    
private:
    std::string wrapInTryCatch(const std::string& code);
};

#endif // EXCEPTION_OBFUSCATION_H
