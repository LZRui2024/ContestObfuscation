#ifndef ANTI_SEMANTIC_H
#define ANTI_SEMANTIC_H

#include <string>

class AntiSemantic {
private:
    int goto_count;
    std::string replaceLoopWithGoto(const std::string& code);
public:
    AntiSemantic();
    std::string addAntiSemanticAnalysis(const std::string& code);
    void clear();
};

#endif // ANTI_SEMANTIC_H
