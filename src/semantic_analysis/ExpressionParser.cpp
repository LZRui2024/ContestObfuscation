#include "ExpressionParser.h"
#include <algorithm>
#include <cctype>
#include <sstream>

namespace Semantic {

bool ASTNode::isPureAddition() const {
    return type == NodeType::BINARY_OP && op == BinaryOp::ADD;
}

bool ASTNode::isEquivalentAddition() const {
    // 识别模式：(a^b)+((a&b)<<1)
    if (type != NodeType::BINARY_OP || op != BinaryOp::ADD)
        return false;
    
    if (!left || !right)
        return false;
    
    std::string xorVar1, xorVar2;
    std::string andVar1, andVar2;
    
    // 检查左边是否是 a^b
    if (left->type == NodeType::BINARY_OP && left->op == BinaryOp::XOR) {
        if (left->left->type == NodeType::VARIABLE && left->right->type == NodeType::VARIABLE) {
            xorVar1 = left->left->value;
            xorVar2 = left->right->value;
        }
    }
    
    // 检查右边是否是 (a&b)<<1
    if (right->type == NodeType::BINARY_OP && right->op == BinaryOp::SHL) {
        if (right->left->type == NodeType::BINARY_OP && right->left->op == BinaryOp::AND) {
            if (right->left->left->type == NodeType::VARIABLE && 
                right->left->right->type == NodeType::VARIABLE) {
                andVar1 = right->left->left->value;
                andVar2 = right->left->right->value;
            }
        }
        // 检查移位量是否为 1
        if (right->right->type == NodeType::NUMBER && right->right->value == "1") {
            // 验证变量是否匹配
            if (xorVar1 == andVar1 && xorVar2 == andVar2)
                return true;
        }
    }
    
    return false;
}

bool ASTNode::isXorWithConstant() const {
    // 识别模式：var ^ constant
    if (type != NodeType::BINARY_OP || op != BinaryOp::XOR)
        return false;
    
    if (!left || !right)
        return false;
    
    // 检查是否一边是变量，另一边是数字
    if (left->type == NodeType::VARIABLE && right->type == NodeType::NUMBER)
        return true;
    if (left->type == NodeType::NUMBER && right->type == NodeType::VARIABLE)
        return true;
    
    return false;
}

std::pair<std::string, std::string> ASTNode::extractAdditionOperands() const {
    if (type == NodeType::BINARY_OP && op == BinaryOp::ADD) {
        if (left && right && left->type == NodeType::VARIABLE && right->type == NodeType::VARIABLE) {
            return {left->value, right->value};
        }
    }
    return {"", ""};
}

std::pair<std::string, int> ASTNode::extractXorWithConstant() const {
    if (type == NodeType::BINARY_OP && op == BinaryOp::XOR) {
        if (left && right) {
            if (left->type == NodeType::VARIABLE && right->type == NodeType::NUMBER) {
                return {left->value, std::stoi(right->value)};
            }
            if (left->type == NodeType::NUMBER && right->type == NodeType::VARIABLE) {
                return {right->value, std::stoi(left->value)};
            }
        }
    }
    return {"", 0};
}

bool ASTNode::isPureMultiplication() const {
    return type == NodeType::BINARY_OP && op == BinaryOp::MUL;
}

std::pair<std::string, std::string> ASTNode::extractMultiplicationOperands() const {
    if (type == NodeType::BINARY_OP && op == BinaryOp::MUL) {
        if (left && right && left->type == NodeType::VARIABLE && right->type == NodeType::VARIABLE) {
            return {left->value, right->value};
        }
    }
    return {"", ""};
}

ExpressionParser::ExpressionParser() : pos(0) {}

std::shared_ptr<ASTNode> ExpressionParser::parse(const std::string& expr) {
    input = expr;
    pos = 0;
    return parseExpression();
}

std::shared_ptr<ASTNode> ExpressionParser::parseExpression() {
    auto left = parseTerm();
    
    while (true) {
        skipWhitespace();
        char op = peek();
        
        if (op == '+') {
            get();
            auto node = std::make_shared<ASTNode>();
            node->type = NodeType::BINARY_OP;
            node->op = BinaryOp::ADD;
            node->left = left;
            node->right = parseTerm();
            left = node;
        } else if (op == '-') {
            get();
            auto node = std::make_shared<ASTNode>();
            node->type = NodeType::BINARY_OP;
            node->op = BinaryOp::SUB;
            node->left = left;
            node->right = parseTerm();
            left = node;
        } else {
            break;
        }
    }
    
    return left;
}

std::shared_ptr<ASTNode> ExpressionParser::parseTerm() {
    auto left = parseFactor();
    
    while (true) {
        skipWhitespace();
        char op = peek();
        
        if (op == '*') {
            get();
            auto node = std::make_shared<ASTNode>();
            node->type = NodeType::BINARY_OP;
            node->op = BinaryOp::MUL;
            node->left = left;
            node->right = parseFactor();
            left = node;
        } else if (op == '/') {
            get();
            auto node = std::make_shared<ASTNode>();
            node->type = NodeType::BINARY_OP;
            node->op = BinaryOp::DIV;
            node->left = left;
            node->right = parseFactor();
            left = node;
        } else if (op == '%') {
            get();
            auto node = std::make_shared<ASTNode>();
            node->type = NodeType::BINARY_OP;
            node->op = BinaryOp::MOD;
            node->left = left;
            node->right = parseFactor();
            left = node;
        } else if (op == '^') {
            get();
            auto node = std::make_shared<ASTNode>();
            node->type = NodeType::BINARY_OP;
            node->op = BinaryOp::XOR;
            node->left = left;
            node->right = parseFactor();
            left = node;
        } else if (op == '&') {
            get();
            auto node = std::make_shared<ASTNode>();
            node->type = NodeType::BINARY_OP;
            node->op = BinaryOp::AND;
            node->left = left;
            node->right = parseFactor();
            left = node;
        } else if (op == '|') {
            get();
            auto node = std::make_shared<ASTNode>();
            node->type = NodeType::BINARY_OP;
            node->op = BinaryOp::OR;
            node->left = left;
            node->right = parseFactor();
            left = node;
        } else {
            break;
        }
    }
    
    return left;
}

std::shared_ptr<ASTNode> ExpressionParser::parseFactor() {
    skipWhitespace();
    
    // 处理左移位
    auto node = parsePrimary();
    
    while (true) {
        skipWhitespace();
        if (peek() == '<' && input[pos + 1] == '<') {
            pos += 2;
            auto shiftNode = std::make_shared<ASTNode>();
            shiftNode->type = NodeType::BINARY_OP;
            shiftNode->op = BinaryOp::SHL;
            shiftNode->left = node;
            shiftNode->right = parsePrimary();
            node = shiftNode;
        } else {
            break;
        }
    }
    
    return node;
}

std::shared_ptr<ASTNode> ExpressionParser::parsePrimary() {
    skipWhitespace();
    
    char c = peek();
    
    // 处理括号
    if (c == '(') {
        get();
        auto node = parseExpression();
        skipWhitespace();
        if (peek() == ')') get();
        return node;
    }
    
    // 处理数字
    if (std::isdigit(c)) {
        std::string num;
        while (std::isdigit(peek())) {
            num += get();
        }
        auto node = std::make_shared<ASTNode>();
        node->type = NodeType::NUMBER;
        node->value = num;
        return node;
    }
    
    // 处理变量名
    if (std::isalpha(c) || c == '_') {
        std::string var;
        while (std::isalnum(peek()) || peek() == '_') {
            var += get();
        }
        auto node = std::make_shared<ASTNode>();
        node->type = NodeType::VARIABLE;
        node->value = var;
        return node;
    }
    
    // 错误处理
    return nullptr;
}

void ExpressionParser::skipWhitespace() {
    while (std::isspace(peek())) pos++;
}

std::string ExpressionParser::readToken() {
    std::string token;
    while (std::isalnum(peek()) || peek() == '_') {
        token += get();
    }
    return token;
}

char ExpressionParser::peek() {
    if (pos >= input.length()) return '\0';
    return input[pos];
}

char ExpressionParser::get() {
    if (pos >= input.length()) return '\0';
    return input[pos++];
}

std::shared_ptr<ASTNode> ExpressionParser::simplify(std::shared_ptr<ASTNode> node) {
    if (!node) return node;
    
    // 递归简化子节点
    node->left = simplify(node->left);
    node->right = simplify(node->right);
    
    // 常量折叠
    if (node->type == NodeType::BINARY_OP) {
        if (node->left && node->left->type == NodeType::NUMBER &&
            node->right && node->right->type == NodeType::NUMBER) {
            
            int leftVal = std::stoi(node->left->value);
            int rightVal = std::stoi(node->right->value);
            int result = 0;
            
            switch (node->op) {
                case BinaryOp::ADD: result = leftVal + rightVal; break;
                case BinaryOp::SUB: result = leftVal - rightVal; break;
                case BinaryOp::MUL: result = leftVal * rightVal; break;
                case BinaryOp::XOR: result = leftVal ^ rightVal; break;
                case BinaryOp::AND: result = leftVal & rightVal; break;
                case BinaryOp::OR:  result = leftVal | rightVal; break;
                case BinaryOp::SHL: result = leftVal << rightVal; break;
                default: break;
            }
            
            node->type = NodeType::NUMBER;
            node->value = std::to_string(result);
            node->left = nullptr;
            node->right = nullptr;
        }
    }
    
    return node;
}

std::pair<std::string, std::string> ExpressionParser::recognizeAddition(std::shared_ptr<ASTNode> node) {
    if (!node) return {"", ""};
    
    // 情况 1：纯加法 a + b
    if (node->isPureAddition()) {
        auto operands = node->extractAdditionOperands();
        if (!operands.first.empty() && !operands.second.empty()) {
            return operands;
        }
    }
    
    // 情况 2：等价的加法 (a^b)+((a&b)<<1)
    if (node->isEquivalentAddition()) {
        if (node->left && node->left->type == NodeType::BINARY_OP && node->left->op == BinaryOp::XOR) {
            if (node->left->left && node->left->right) {
                return {node->left->left->value, node->left->right->value};
            }
        }
    }
    
    return {"", ""};
}

std::pair<std::string, std::string> ExpressionParser::recognizeMultiplication(std::shared_ptr<ASTNode> node) {
    if (!node) return {"", ""};
    
    // 纯乘法 a * b
    if (node->isPureMultiplication()) {
        return node->extractMultiplicationOperands();
    }
    
    return {"", ""};
}

std::string ExpressionParser::toString(std::shared_ptr<ASTNode> node) {
    if (!node) return "";
    
    switch (node->type) {
        case NodeType::NUMBER:
            return node->value;
        case NodeType::VARIABLE:
            return node->value;
        case NodeType::BINARY_OP: {
            std::string opStr;
            switch (node->op) {
                case BinaryOp::ADD: opStr = " + "; break;
                case BinaryOp::SUB: opStr = " - "; break;
                case BinaryOp::MUL: opStr = " * "; break;
                case BinaryOp::DIV: opStr = " / "; break;
                case BinaryOp::XOR: opStr = " ^ "; break;
                case BinaryOp::AND: opStr = " & "; break;
                case BinaryOp::OR:  opStr = " | "; break;
                case BinaryOp::SHL: opStr = " << "; break;
                default: opStr = " ? "; break;
            }
            return "(" + toString(node->left) + opStr + toString(node->right) + ")";
        }
        default:
            return "";
    }
}

SemanticRecognizer::SemanticResult SemanticRecognizer::recognize(const std::string& expr) {
    SemanticResult result;
    result.recognized = false;
    
    ExpressionParser parser;
    auto ast = parser.parse(expr);
    
    if (!ast) return result;
    
    // 尝试识别加法
    auto addOperands = parser.recognizeAddition(ast);
    if (!addOperands.first.empty() && !addOperands.second.empty()) {
        result.recognized = true;
        result.originalOp = "+";
        result.var1 = addOperands.first;
        result.var2 = addOperands.second;
        result.description = "Addition: " + result.var1 + " + " + result.var2;
        return result;
    }
    
    // 尝试识别乘法
    auto mulOperands = parser.recognizeMultiplication(ast);
    if (!mulOperands.first.empty() && !mulOperands.second.empty()) {
        result.recognized = true;
        result.originalOp = "*";
        result.var1 = mulOperands.first;
        result.var2 = mulOperands.second;
        result.description = "Multiplication: " + result.var1 + " * " + result.var2;
        return result;
    }
    
    // 尝试识别 var + (constant ^ constant) 模式
    if (ast->type == NodeType::BINARY_OP && ast->op == BinaryOp::ADD) {
        if (ast->left && ast->left->type == NodeType::VARIABLE &&
            ast->right && ast->right->type == NodeType::BINARY_OP && ast->right->op == BinaryOp::XOR) {
            if (ast->right->left && ast->right->left->type == NodeType::NUMBER &&
                ast->right->right && ast->right->right->type == NodeType::NUMBER) {
                // 计算常量 XOR
                int const1 = std::stoi(ast->right->left->value);
                int const2 = std::stoi(ast->right->right->value);
                int constResult = const1 ^ const2;
                
                result.recognized = true;
                result.originalOp = "+";
                result.var1 = ast->left->value;
                result.var2 = std::to_string(constResult);
                result.description = "Addition: " + result.var1 + " + " + std::to_string(constResult) + " (from " + ast->right->left->value + " ^ " + ast->right->right->value + ")";
                return result;
            }
        }
    }
    
    // 尝试识别 (constant ^ constant) + var 模式
    if (ast->type == NodeType::BINARY_OP && ast->op == BinaryOp::ADD) {
        if (ast->left && ast->left->type == NodeType::BINARY_OP && ast->left->op == BinaryOp::XOR &&
            ast->right && ast->right->type == NodeType::VARIABLE) {
            if (ast->left->left && ast->left->left->type == NodeType::NUMBER &&
                ast->left->right && ast->left->right->type == NodeType::NUMBER) {
                // 计算常量 XOR
                int const1 = std::stoi(ast->left->left->value);
                int const2 = std::stoi(ast->left->right->value);
                int constResult = const1 ^ const2;
                
                result.recognized = true;
                result.originalOp = "+";
                result.var1 = std::to_string(constResult);
                result.var2 = ast->right->value;
                result.description = "Addition: " + std::to_string(constResult) + " + " + result.var2 + " (from " + ast->left->left->value + " ^ " + ast->left->right->value + ")";
                return result;
            }
        }
    }
    
    // 尝试识别 var ^ constant 模式（简化为变量）
    if (ast->isXorWithConstant()) {
        auto xorOperands = ast->extractXorWithConstant();
        if (!xorOperands.first.empty()) {
            result.recognized = true;
            result.originalOp = "^";
            result.var1 = xorOperands.first;
            result.var2 = std::to_string(xorOperands.second);
            result.description = "XOR: " + result.var1 + " ^ " + std::to_string(xorOperands.second);
            return result;
        }
    }
    
    return result;
}

} // namespace Semantic
