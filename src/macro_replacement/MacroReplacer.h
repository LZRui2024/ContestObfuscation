#ifndef MACRO_REPLACER_H
#define MACRO_REPLACER_H

#include <string>
#include <unordered_map>

class MacroReplacer {
private:
    std::unordered_map<std::string, std::string> macro_map;
    std::unordered_map<std::string, std::string> reverse_map;
    void initCommonMacros();
    bool isInStringLiteral(const std::string& code, size_t pos);
    bool isInComment(const std::string& code, size_t pos);
public:
    MacroReplacer();
    std::string generateMacros();
    std::string replaceMacros(const std::string& code);
    void clear();
};

#endif // MACRO_REPLACER_H