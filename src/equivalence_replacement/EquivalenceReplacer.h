#ifndef EQUIVALENCE_REPLACER_H
#define EQUIVALENCE_REPLACER_H

#include <string>
#include <unordered_map>

class EquivalenceReplacer {
private:
    int replacement_count;
    std::string replaceMultiplication(const std::string& expr);
    std::string replaceDivision(const std::string& expr);
    std::string replaceAddition(const std::string& expr);
    std::string replaceSubtraction(const std::string& expr);
public:
    EquivalenceReplacer();
    std::string replaceEquivalences(const std::string& code);
    void clear();
};

#endif // EQUIVALENCE_REPLACER_H
