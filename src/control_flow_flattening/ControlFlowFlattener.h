#ifndef CONTROL_FLOW_FLATTENER_H
#define CONTROL_FLOW_FLATTENER_H

#include <string>
#include <vector>

class ControlFlowFlattener {
public:
    ControlFlowFlattener();
    std::string flattenControlFlow(const std::string& code);
    void clear();

private:
    std::string generateStateVariable();
    std::string generateCaseStatement(int state, const std::string& code);
    bool containsControlFlow(const std::string& code);
    std::vector<std::string> extractStatements(const std::string& function_body);
};

#endif // CONTROL_FLOW_FLATTENER_H
