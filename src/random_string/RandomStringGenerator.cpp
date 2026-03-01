#include "RandomStringGenerator.h"
#include <cstdlib>
#include <ctime>

const char* RandomStringGenerator::charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
const int RandomStringGenerator::charset_size = 62;

void RandomStringGenerator::init() {
    static bool initialized = false;
    if (!initialized) {
        srand(static_cast<unsigned int>(time(nullptr)));
        initialized = true;
    }
}

std::string RandomStringGenerator::generate(int length) {
    init();
    std::string result;
    result.reserve(length);
    for (int i = 0; i < length; ++i) {
        result += charset[rand() % charset_size];
    }
    return result;
}