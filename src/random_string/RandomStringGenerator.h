#ifndef RANDOM_STRING_GENERATOR_H
#define RANDOM_STRING_GENERATOR_H

#include <string>

class RandomStringGenerator {
private:
    static const char* charset;
    static const int charset_size;
    static void init();
public:
    static std::string generate(int length);
};

#endif // RANDOM_STRING_GENERATOR_H