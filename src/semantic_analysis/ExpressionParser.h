#ifndef EXPRESSION_PARSER_H
#define EXPRESSION_PARSER_H

#include <string>
#include <vector>
#include <memory>
#include <map>
#include <set>

namespace Semantic {

// AST 节点类型
enum class NodeType {
    NUMBER,
    VARIABLE,
    BINARY_OP,
    UNARY_OP
};

// 二元操作符类型
enum class BinaryOp {
    ADD,      // +
    SUB,      // -
    MUL,      // *
    DIV,      // /
    MOD,      // %
    XOR,      // ^
    AND,      // &
    OR,       // |
    SHL,      // <<
    SHR,      // >>
    UNKNOWN
};

// AST 节点
struct ASTNode {
    NodeType type;
    std::string value;  // 数字或变量名
    BinaryOp op;        // 操作符
    std::shared_ptr<ASTNode> left;
    std::shared_ptr<ASTNode> right;
    
    // 判断是否是纯加法表达式
    bool isPureAddition() const;
    
    // 判断是否是等价的加法表达式（如 (a^b)+((a&b)<<1)）
    bool isEquivalentAddition() const;
    
    // 判断是否是变量 XOR 常量的形式
    bool isXorWithConstant() const;
    
    // 提取加法操作数
    std::pair<std::string, std::string> extractAdditionOperands() const;
    
    // 提取 XOR 操作数
    std::pair<std::string, int> extractXorWithConstant() const;
    
    // 判断是否是纯乘法表达式
    bool isPureMultiplication() const;
    
    // 提取乘法操作数
    std::pair<std::string, std::string> extractMultiplicationOperands() const;
};

// 表达式解析器
class ExpressionParser {
public:
    ExpressionParser();
    
    // 解析表达式字符串为 AST
    std::shared_ptr<ASTNode> parse(const std::string& expr);
    
    // 简化 AST（常量折叠等）
    std::shared_ptr<ASTNode> simplify(std::shared_ptr<ASTNode> node);
    
    // 识别混淆的加法：(a^b)+((a&b)<<1) => a+b
    std::pair<std::string, std::string> recognizeAddition(std::shared_ptr<ASTNode> node);
    
    // 识别混淆的乘法：需要特殊处理
    std::pair<std::string, std::string> recognizeMultiplication(std::shared_ptr<ASTNode> node);
    
    // 将 AST 转换回字符串
    std::string toString(std::shared_ptr<ASTNode> node);
    
private:
    size_t pos;
    std::string input;
    
    // 递归下降解析
    std::shared_ptr<ASTNode> parseExpression();
    std::shared_ptr<ASTNode> parseTerm();
    std::shared_ptr<ASTNode> parseFactor();
    std::shared_ptr<ASTNode> parsePrimary();
    
    // 词法分析
    void skipWhitespace();
    std::string readToken();
    char peek();
    char get();
    
    // 识别特定的混淆模式
    bool isXorPattern(std::shared_ptr<ASTNode> node, std::string& var1, std::string& var2);
    bool isAndShiftPattern(std::shared_ptr<ASTNode> node, std::string& var1, std::string& var2);
};

// 语义识别器
class SemanticRecognizer {
public:
    // 识别表达式的真实语义
    struct SemanticResult {
        bool recognized;
        std::string originalOp;  // 原始操作：+, -, *, /
        std::string var1;
        std::string var2;
        std::string description;
    };
    
    static SemanticResult recognize(const std::string& expr);
};

} // namespace Semantic

#endif // EXPRESSION_PARSER_H
