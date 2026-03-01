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
};

#endif // STRING_SPLITTER_H
