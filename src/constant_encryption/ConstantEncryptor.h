#ifndef CONSTANT_ENCRYPTOR_H
#define CONSTANT_ENCRYPTOR_H

#include <string>

class ConstantEncryptor {
private:
    int key;
    std::string encryptConstant(int value);
public:
    ConstantEncryptor();
    std::string encryptConstants(const std::string& code);
};

#endif // CONSTANT_ENCRYPTOR_H