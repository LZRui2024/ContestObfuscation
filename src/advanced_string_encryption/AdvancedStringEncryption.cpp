#include "AdvancedStringEncryption.h"
#include "../random_string/RandomStringGenerator.h"
#include <sstream>
#include <regex>

const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

std::string AdvancedStringEncryption::base64Encode(const std::string& str) {
    std::string ret;
    int i = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];
    size_t in_len = str.size();
    const char* bytes_to_encode = str.c_str();
    
    while (in_len--) {
        char_array_3[i++] = *(bytes_to_encode++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;
            
            for (i = 0; i < 4; i++)
                ret += base64_chars[char_array_4[i]];
            i = 0;
        }
    }
    
    if (i) {
        for (int j = i; j < 3; j++)
            char_array_3[j] = '\0';
        
        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;
        
        for (int j = 0; j < i + 1; j++)
            ret += base64_chars[char_array_4[j]];
        
        while (i++ < 3)
            ret += '=';
    }
    
    return ret;
}

std::string AdvancedStringEncryption::xorEncode(const std::string& str, int key) {
    std::stringstream ss;
    for (char c : str) {
        ss << std::hex << (c ^ key) << " ";
    }
    return ss.str();
}

std::string AdvancedStringEncryption::generateEncryptedString(const std::string& str) {
    int xor_key = rand() % 255 + 1;
    std::string xored = xorEncode(str, xor_key);
    std::string encoded = base64Encode(xored);
    
    std::stringstream ss;
    ss << "decrypt({";
    for (size_t i = 0; i < encoded.size(); i++) {
        ss << static_cast<int>(encoded[i]);
        if (i < encoded.size() - 1) ss << ", ";
    }
    ss << "}, " << xor_key << ")";
    
    return ss.str();
}

std::string AdvancedStringEncryption::encryptStrings(const std::string& code) {
    std::string result = code;
    
    // 查找所有字符串字面量
    std::regex string_regex(R"("([^"\\]|\\.)*")");
    
    std::smatch match;
    std::string temp = result;
    std::string output;
    size_t last_pos = 0;
    
    while (std::regex_search(temp, match, string_regex)) {
        output += temp.substr(0, match.position());
        
        std::string str = match.str();
        
        // 跳过预处理指令和已经加密的字符串
        if (str.find("decrypt") == std::string::npos && 
            str.find("#") == std::string::npos) {
            // 移除引号
            std::string content = str.substr(1, str.size() - 2);
            
            // 转义字符处理
            if (content.find("\\") == std::string::npos && 
                content.find("\"") == std::string::npos &&
                content.size() > 2) {
                output += generateEncryptedString(content);
            } else {
                output += str;
            }
        } else {
            output += str;
        }
        
        temp = match.suffix();
        last_pos = match.position() + match.length();
    }
    
    output += temp;
    return output;
}
