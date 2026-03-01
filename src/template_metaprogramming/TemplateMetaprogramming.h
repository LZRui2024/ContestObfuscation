#ifndef TEMPLATE_METAPROGRAMMING_H
#define TEMPLATE_METAPROGRAMMING_H

#include <string>

class TemplateMetaprogramming {
public:
    std::string addTemplateMetaprogramming(const std::string& code);
    
private:
    std::string generateTemplateFunctions();
    std::string generateConstexprFunctions();
};

#endif // TEMPLATE_METAPROGRAMMING_H
