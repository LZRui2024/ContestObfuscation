#ifndef EXCEPTION_OBFUSCATOR_H
#define EXCEPTION_OBFUSCATOR_H

#include <string>

class ExceptionObfuscator {
public:
    ExceptionObfuscator();
    std::string obfuscateWithExceptions(const std::string& code);
    void clear();

private:
    std::string generateExceptionCode(const std::string& code);
    bool isClassOrStruct(const std::string& code, size_t brace_pos);
    bool isFunctionBody(const std::string& code, size_t brace_pos);
};

#endif // EXCEPTION_OBFUSCATOR_H
