#ifndef LOOP_TRANSFORMER_H
#define LOOP_TRANSFORMER_H

#include <string>

class LoopTransformer {
public:
    LoopTransformer();
    std::string transformLoops(const std::string& code);
    void clear();

private:
    std::string transformForLoop(const std::string& code);
    std::string transformWhileLoop(const std::string& code);
};

#endif // LOOP_TRANSFORMER_H
