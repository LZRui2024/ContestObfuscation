#ifndef MEMORY_OBFUSCATION_H
#define MEMORY_OBFUSCATION_H

#include <string>

class MemoryObfuscation {
public:
    std::string addMemoryOperations(const std::string& code);
    
private:
    std::string replaceWithMemcpy(const std::string& code);
};

#endif // MEMORY_OBFUSCATION_H
