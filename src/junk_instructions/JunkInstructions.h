#ifndef JUNK_INSTRUCTIONS_H
#define JUNK_INSTRUCTIONS_H

#include <string>

class JunkInstructions {
public:
    std::string addJunkInstructions(const std::string& code);
    
private:
    std::string generateJunkCode();
};

#endif // JUNK_INSTRUCTIONS_H
