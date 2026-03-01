#ifndef FAKE_CONTROL_FLOW_H
#define FAKE_CONTROL_FLOW_H

#include <string>

class FakeControlFlow {
private:
    int fake_branch_count;
    std::string generateOpaquePredicate();
public:
    FakeControlFlow();
    std::string addFakeControlFlow(const std::string& code);
    void clear();
};

#endif // FAKE_CONTROL_FLOW_H
