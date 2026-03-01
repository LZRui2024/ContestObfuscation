#ifndef STRING_ENCRYPTOR_H
#define STRING_ENCRYPTOR_H

#include <string>

class StringEncryptor {
private:
    int key;
    std::string encryptString(const std::string& str);
    std::string generateDecryptFunction();
public:
    StringEncryptor();
    std::pair<std::string, std::string> encryptStrings(const std::string& code);
};

#endif // STRING_ENCRYPTOR_H