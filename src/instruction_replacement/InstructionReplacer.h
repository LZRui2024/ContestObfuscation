#ifndef INSTRUCTION_REPLACER_H
#define INSTRUCTION_REPLACER_H

#include <string>

class InstructionReplacer {
public:
    InstructionReplacer();
    std::string replaceInstructions(const std::string& code);
    void clear();

private:
    std::string replaceAssignment(const std::string& code);
    std::string replaceArithmetic(const std::string& code);
};

#endif // INSTRUCTION_REPLACER_H
