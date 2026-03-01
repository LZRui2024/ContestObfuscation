#ifndef ADVANCED_CONTROL_FLOW_H
#define ADVANCED_CONTROL_FLOW_H

#include <string>

class AdvancedControlFlow {
public:
    std::string addAdvancedFlattening(const std::string& code);
    
private:
    std::string generateStateDispatcher();
    std::string addFakeStateTransitions();
};

#endif // ADVANCED_CONTROL_FLOW_H
