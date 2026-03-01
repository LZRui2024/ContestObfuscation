#ifndef IRRELEVANT_CODE_INJECTOR_H
#define IRRELEVANT_CODE_INJECTOR_H

#include <string>

class IrrelevantCodeInjector {
private:
    std::string generateIrrelevantCode();
public:
    std::string injectIrrelevantCode(const std::string& code);
};

#endif // IRRELEVANT_CODE_INJECTOR_H