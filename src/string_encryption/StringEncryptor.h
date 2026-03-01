#ifndef STRING_ENCRYPTOR_H
#define STRING_ENCRYPTOR_H

#include <string>

class StringEncryptor {
private:
    int key;
    std::string processEscapeSequences(const std::string& str);
    std::string encryptString(const std::string& str);
    std::string generateDecryptFunction();
public:
    StringEncryptor();
    std::pair<std::string, std::string> encryptStrings(const std::string& code);
    void clear();
};

#endif // STRING_ENCRYPTOR_H
