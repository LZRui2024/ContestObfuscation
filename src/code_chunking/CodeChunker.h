#ifndef CODE_CHUNKER_H
#define CODE_CHUNKER_H

#include <string>

class CodeChunker {
private:
    std::string generateChunkFunction();
public:
    std::string chunkCode(const std::string& code);
};

#endif // CODE_CHUNKER_H