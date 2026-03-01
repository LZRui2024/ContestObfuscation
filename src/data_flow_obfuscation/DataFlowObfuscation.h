#ifndef DATA_FLOW_OBFUSCATION_H
#define DATA_FLOW_OBFUSCATION_H

#include <string>

class DataFlowObfuscation {
private:
    int temp_var_count;
    std::string introduceTempVariables(const std::string& expr);
public:
    DataFlowObfuscation();
    std::string obfuscateDataFlow(const std::string& code);
    void clear();
};

#endif // DATA_FLOW_OBFUSCATION_H
