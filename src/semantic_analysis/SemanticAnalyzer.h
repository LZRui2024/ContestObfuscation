#ifndef SEMANTIC_ANALYZER_H
#define SEMANTIC_ANALYZER_H

#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <regex>

namespace Semantic {

// 变量信息结构
struct VariableInfo {
    std::string name;
    std::string type;
    bool isInput = false;
    bool isOutput = false;
    bool isConstant = false;
    std::vector<std::string> dependencies;
    std::string definition;
    int lineNum = 0;
};

// 表达式树节点
struct ExprNode {
    enum Type {
        VARIABLE,
        CONSTANT,
        BINARY_OP,
        UNARY_OP,
        FUNCTION_CALL,
        INPUT_READ,
        OUTPUT_WRITE
    };
    
    Type type;
    std::string value;
    std::string op;
    std::vector<std::shared_ptr<ExprNode>> children;
    std::shared_ptr<ExprNode> left;
    std::shared_ptr<ExprNode> right;
};

// 语句信息
struct StatementInfo {
    std::string original;
    std::string transformed;
    int lineNum;
    bool isInput = false;
    bool isOutput = false;
    bool isAssignment = false;
    std::string targetVar;
    std::shared_ptr<ExprNode> exprTree;
};

// 数据流图
struct DataFlowGraph {
    std::map<std::string, std::vector<std::string>> useDef;
    std::map<std::string, std::vector<std::string>> defUse;
    std::vector<std::string> inputs;
    std::vector<std::string> outputs;
};

// 主分析器类
class SemanticAnalyzer {
public:
    SemanticAnalyzer();
    
    // 分析整个程序
    void analyze(const std::string& code);
    
    // 获取变量信息
    std::vector<VariableInfo> getVariables() const;
    
    // 获取数据流图
    DataFlowGraph getDataFlow() const;
    
    // 获取输入变量
    std::vector<std::string> getInputVars() const;
    
    // 获取输出变量
    std::vector<std::string> getOutputVars() const;
    
    // 构建表达式树
    std::shared_ptr<ExprNode> buildExprTree(const std::string& expr);
    
    // 表达式等价变换
    std::string transformExpr(std::shared_ptr<ExprNode> node);
    
    // 包装输入语句
    std::string wrapInput(const std::string& inputStmt);
    
    // 包装输出语句
    std::string wrapOutput(const std::string& outputStmt);
    
    // 插入混淆计算
    std::string insertObfuscatedCalculation(const std::string& code);
    
    // 获取分析后的代码
    std::string getAnalyzedCode() const;

private:
    std::vector<VariableInfo> variables;
    std::vector<StatementInfo> statements;
    DataFlowGraph dataFlow;
    std::string analyzedCode;
    
    // 内部辅助方法
    void extractVariables(const std::string& code);
    void buildDataFlow();
    void analyzeInputOutput();
    std::string parseExpression(const std::string& expr);
    void insertFakeDependency(const std::string& var);
    void wrapWithStateMachine(const std::string& var);
};

} // namespace Semantic

#endif // SEMANTIC_ANALYZER_H
