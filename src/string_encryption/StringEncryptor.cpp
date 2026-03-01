#include "StringEncryptor.h"
#include <regex>
#include <cstdlib>

StringEncryptor::StringEncryptor() {
    key = rand() % 256 + 1;
}

std::string StringEncryptor::encryptString(const std::string& str) {
    std::string encrypted;
    for (char c : str) {
        encrypted += std::to_string(static_cast<unsigned char>(c) ^ key) + ",";
    }
    if (!encrypted.empty()) {
        encrypted.pop_back();
    }
    return "decrypt({" + encrypted + "})";
}

std::string StringEncryptor::generateDecryptFunction() {
    return "std::string decrypt(const int* arr, int length) {\n" 
         "    std::string result;\n" 
         "    for (int i = 0; i < length; i++) {\n" 
         "        result += static_cast<char>(arr[i] ^ " + std::to_string(key) + ");\n" 
         "    }\n" 
         "    return result;\n" 
         "}\n" 
         "std::string decrypt(std::initializer_list<int> arr) {\n" 
         "    return decrypt(arr.begin(), arr.size());\n" 
         "}\n";
}

std::pair<std::string, std::string> StringEncryptor::encryptStrings(const std::string& code) {
    std::string result = code;
    std::regex string_regex(R"delim("([^"]*)")delim");
    std::smatch match;
    
    std::string temp = result;
    size_t pos = 0;
    
    while (std::regex_search(temp, match, string_regex)) {
        size_t match_pos = result.find(match.str(), pos);
        if (match_pos == std::string::npos) break;
        
        std::string str = match[1].str();
        std::string encrypted = encryptString(str);
        result.replace(match_pos, match.length(), encrypted);
        
        pos = match_pos + encrypted.length();
        temp = result.substr(pos);
    }
    
    std::string decrypt_function = generateDecryptFunction();
    return {result, decrypt_function};
}