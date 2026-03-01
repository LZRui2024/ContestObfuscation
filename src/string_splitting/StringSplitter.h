#ifndef STRING_SPLITTER_H
#define STRING_SPLITTER_H

#include <string>

class StringSplitter {
public:
    StringSplitter();
    std::string splitString(const std::string& code);
    void clear();

private:
    std::string generateSplitCode(const std::string& str);
    bool isEncryptedString(const std::string& code, size_t quote_pos);
};

#endif // STRING_SPLITTER_H
