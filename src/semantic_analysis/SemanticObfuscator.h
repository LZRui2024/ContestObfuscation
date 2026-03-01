#ifndef SEMANTIC_OBFUSCATOR_H
#define SEMANTIC_OBFUSCATOR_H

#include <string>
#include "ExpressionParser.h"

class SemanticObfuscator {
public:
    std::string addSemanticObfuscation(const std::string& code);
    
private:
    Semantic::ExpressionParser parser;
    
    std::string wrapInputWithObfuscation(const std::string& code);
    std::string wrapOutputWithStateMachine(const std::string& code);
    std::string wrapRecognizedExpression(const std::string& expr, const std::string& coutName);
};

#endif // SEMANTIC_OBFUSCATOR_H
