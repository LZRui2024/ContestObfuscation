#include "SemanticAnalyzer.h"
#include <sstream>
#include <algorithm>
#include <stack>
#include <iostream>

namespace Semantic {

SemanticAnalyzer::SemanticAnalyzer() {}

void SemanticAnalyzer::analyze(const std::string& code) {
    analyzedCode = code;
    extractVariables(code);
    analyzeInputOutput();
    buildDataFlow();
}

void SemanticAnalyzer::extractVariables(const std::string& code) {
    // 提取变量声明
    std::regex var_decl_regex(R"((int|float|double|char|long|short|unsigned)\s+(\w+)\s*[;=])");
    std::sregex_iterator it(code.begin(), code.end(), var_decl_regex);
    std::sregex_iterator end;
    
    int lineNum = 1;
    while (it != end) {
        VariableInfo var;
        var.type = (*it)[1].str();
        var.name = (*it)[2].str();
        var.lineNum = lineNum++;
        variables.push_back(var);
        ++it;
    }
}

void SemanticAnalyzer::analyzeInputOutput() {
    std::regex cin_regex(R"(cin\s*>>\s*(\w+))");
    std::regex cout_regex(R"(cout\s*<<\s*([^;]+))");
    
    std::sregex_iterator it(analyzedCode.begin(), analyzedCode.end(), cin_regex);
    std::sregex_iterator end;
    
    while (it != end) {
        std::string var = (*it)[1].str();
        dataFlow.inputs.push_back(var);
        
        // 标记变量为输入
        for (auto& varInfo : variables) {
            if (varInfo.name == var) {
                varInfo.isInput = true;
                break;
            }
        }
        ++it;
    }
    
    // 简单处理输出（实际应该更复杂）
    for (const auto& var : variables) {
        if (!var.isInput && var.type == "int") {
            dataFlow.outputs.push_back(var.name);
        }
    }
}

void SemanticAnalyzer::buildDataFlow() {
    // 构建简单的使用 - 定义链
    std::regex assign_regex(R"((\w+)\s*=\s*([^;]+);)");
    std::sregex_iterator it(analyzedCode.begin(), analyzedCode.end(), assign_regex);
    std::sregex_iterator end;
    
    while (it != end) {
        std::string target = (*it)[1].str();
        std::string expr = (*it)[2].str();
        
        // 查找表达式中的变量
        std::regex var_regex(R"(\b(\w+)\b)");
        std::sregex_iterator vit(expr.begin(), expr.end(), var_regex);
        
        while (vit != end) {
            std::string var = (*vit)[1].str();
            if (var != target && var != "cin" && var != "cout" && var != "endl") {
                dataFlow.useDef[target].push_back(var);
                dataFlow.defUse[var].push_back(target);
            }
            ++vit;
        }
        ++it;
    }
}

std::vector<VariableInfo> SemanticAnalyzer::getVariables() const {
    return variables;
}

DataFlowGraph SemanticAnalyzer::getDataFlow() const {
    return dataFlow;
}

std::vector<std::string> SemanticAnalyzer::getInputVars() const {
    return dataFlow.inputs;
}

std::vector<std::string> SemanticAnalyzer::getOutputVars() const {
    return dataFlow.outputs;
}

std::shared_ptr<ExprNode> SemanticAnalyzer::buildExprTree(const std::string& expr) {
    // 简化实现：创建一个简单的节点
    auto node = std::make_shared<ExprNode>();
    node->type = ExprNode::BINARY_OP;
    node->value = expr;
    return node;
}

std::string SemanticAnalyzer::transformExpr(std::shared_ptr<ExprNode> node) {
    if (!node) return "";
    
    // 简单的等价变换
    if (node->type == ExprNode::BINARY_OP) {
        // 可以在这里实现更复杂的变换
        return node->value;
    }
    return node->value;
}

std::string SemanticAnalyzer::wrapInput(const std::string& inputStmt) {
    // 包装输入语句，添加虚假依赖
    std::stringstream ss;
    ss << "    {\n";
    ss << "        int adv_tmp = 0;\n";
    ss << "        " << inputStmt << "\n";
    ss << "        adv_tmp = adv_fake_dep(" << dataFlow.inputs[0] << ", " << dataFlow.inputs[0] << ");\n";
    ss << "    }\n";
    return ss.str();
}

std::string SemanticAnalyzer::wrapOutput(const std::string& outputStmt) {
    // 包装输出语句，通过状态机计算
    std::stringstream ss;
    ss << "    {\n";
    ss << "        int adv_result = adv_flat(" << dataFlow.inputs[0] << ", " << dataFlow.inputs[0] << ");\n";
    ss << "        " << outputStmt << "\n";
    ss << "    }\n";
    return ss.str();
}

std::string SemanticAnalyzer::insertObfuscatedCalculation(const std::string& code) {
    std::string result = code;
    
    // 找到 main 函数的开始
    size_t main_pos = result.find("int main");
    if (main_pos == std::string::npos) return result;
    
    size_t brace_pos = result.find('{', main_pos);
    if (brace_pos == std::string::npos) return result;
    
    // 在 main 函数开始处添加初始化
    std::stringstream ss;
    ss << "\n";
    ss << "    // Semantic-based obfuscation\n";
    ss << "    int adv_k = adv_init();\n";
    ss << "    int adv_fake = adv_fake_dep(adv_k, adv_k);\n";
    ss << "    (void)adv_fake;\n";
    
    result.insert(brace_pos + 1, ss.str());
    
    // 查找并包装输入语句
    std::regex cin_regex(R"((\s*)(cin\s*>>\s*\w+\s*;))");
    std::string wrapped = std::regex_replace(result, cin_regex, "$1{ $2 int adv_tmp = adv_fake_dep(adv_k, adv_k); (void)adv_tmp; }");
    
    // 查找并包装输出语句（通过状态机）
    std::regex cout_regex(R"((\s*)(cout\s*<<\s*[^;]+;))");
    
    // 更复杂的替换逻辑（简化实现）
    result = wrapped;
    
    analyzedCode = result;
    return result;
}

std::string SemanticAnalyzer::getAnalyzedCode() const {
    return analyzedCode;
}

} // namespace Semantic
