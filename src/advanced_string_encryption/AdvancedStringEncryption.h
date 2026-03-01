#ifndef ADVANCED_STRING_ENCRYPTION_H
#define ADVANCED_STRING_ENCRYPTION_H

#include <string>

class AdvancedStringEncryption {
public:
    std::string encryptStrings(const std::string& code);
    
private:
    std::string xorEncode(const std::string& str, int key);
    std::string base64Encode(const std::string& str);
    std::string generateEncryptedString(const std::string& str);
};

#endif // ADVANCED_STRING_ENCRYPTION_H
