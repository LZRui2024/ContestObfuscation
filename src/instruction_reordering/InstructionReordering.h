#ifndef INSTRUCTION_REORDERING_H
#define INSTRUCTION_REORDERING_H

#include <string>

class InstructionReordering {
private:
    int reorder_count;
    std::string reorderIndependentStatements(const std::string& func_body);
public:
    InstructionReordering();
    std::string reorderInstructions(const std::string& code);
    void clear();
};

#endif // INSTRUCTION_REORDERING_H
