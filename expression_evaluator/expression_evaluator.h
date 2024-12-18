#ifndef EXPRESSION_EVALUATOR_H
#define EXPRESSION_EVALUATOR_H

#include <string>
#include <vector>
#include <stack>
#include <cctype>
#include <cmath>
#include <sstream>
#include <unordered_map>

class ExpressionEvaluator {
public:
    // 评估表达式，成功返回 true 并将结果存入 result
    bool evaluate(const std::string& expression, double& result);

private:
    enum TokenType { NUMBER, OPERATOR, PARENTHESIS };

    struct Token {
        TokenType type;
        double value; // 仅用于数字
        char op;      // 仅用于运算符和括号
    };

    // 将表达式字符串分解为标记
    bool tokenize(const std::string& expr, std::vector<Token>& tokens);

    // 将中缀表达式转换为后缀表达式
    bool toPostfix(const std::vector<Token>& tokens, std::vector<Token>& postfix);

    // 计算后缀表达式的结果
    bool computePostfix(const std::vector<Token>& postfix, double& result);

    // 判断字符是否为运算符
    bool isOperator(char c);

    // 获取运算符优先级
    int precedence(char op);
};

// 实现部分

bool ExpressionEvaluator::evaluate(const std::string& expression, double& result) {
    std::vector<Token> tokens;
    if (!tokenize(expression, tokens)) {
        return false;
    }

    std::vector<Token> postfix;
    if (!toPostfix(tokens, postfix)) {
        return false;
    }

    if (!computePostfix(postfix, result)) {
        return false;
    }

    return true;
}

bool ExpressionEvaluator::isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int ExpressionEvaluator::precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

bool ExpressionEvaluator::tokenize(const std::string& expr, std::vector<Token>& tokens) {
    size_t i = 0;
    size_t n = expr.length();
    bool expectUnary = true; // 一开始可以有一元运算符

    while (i < n) {
        if (isspace(expr[i])) {
            i++;
            continue;
        }

        if (expr[i] == '(') {
            tokens.push_back(Token{ PARENTHESIS, 0, '(' });
            i++;
            expectUnary = true;
        }
        else if (expr[i] == ')') {
            tokens.push_back(Token{ PARENTHESIS, 0, ')' });
            i++;
            expectUnary = false;
        }
        else if (isOperator(expr[i])) {
            char currentOp = expr[i];
            // 检查是否为一元运算符（仅 + 和 -）
            if ((currentOp == '+' || currentOp == '-') && expectUnary) {
                size_t start = i;
                i++; // 跳过一元运算符
                // 读取数字部分
                size_t numStart = i;
                bool hasDigits = false;
                while (i < n && (isdigit(expr[i]) || expr[i] == '.')) {
                    i++;
                    hasDigits = true;
                }
                // 处理科学计数法
                if (i < n && (expr[i] == 'e' || expr[i] == 'E')) {
                    i++;
                    if (i < n && (expr[i] == '+' || expr[i] == '-')) i++;
                    size_t expStart = i;
                    while (i < n && isdigit(expr[i])) {
                        i++;
                    }
                    if (expStart == i) { // 'e' 后无数字
                        return false;
                    }
                }
                if (!hasDigits && !(i > numStart)) {
                    return false;
                }
                std::string numStr = expr.substr(start, i - start);
                double num;
                try {
                    num = std::stod(numStr);
                }
                catch (...) {
                    return false;
                }
                tokens.push_back(Token{ NUMBER, num, 0 });
                expectUnary = false;
            }
            else {
                // 二元运算符
                tokens.push_back(Token{ OPERATOR, 0, currentOp });
                i++;
                expectUnary = true;
            }
        }
        else if (isdigit(expr[i]) || expr[i] == '.') {
            size_t start = i;
            bool hasDigits = false;
            while (i < n && (isdigit(expr[i]) || expr[i] == '.')) {
                if (isdigit(expr[i])) hasDigits = true;
                i++;
            }
            // 处理科学计数法
            if (i < n && (expr[i] == 'e' || expr[i] == 'E')) {
                i++;
                if (i < n && (expr[i] == '+' || expr[i] == '-')) i++;
                size_t expStart = i;
                while (i < n && isdigit(expr[i])) {
                    i++;
                }
                if (expStart == i) { // 'e' 后无数字
                    return false;
                }
            }
            std::string numStr = expr.substr(start, i - start);
            double num;
            try {
                num = std::stod(numStr);
            }
            catch (...) {
                return false;
            }
            tokens.push_back(Token{ NUMBER, num, 0 });
            expectUnary = false;
        }
        else {
            // 无效字符
            return false;
        }
    }

    // 检查表达式是否以运算符结尾
    if (!tokens.empty()) {
        Token last = tokens.back();
        if (last.type == OPERATOR || (last.type == PARENTHESIS && last.op == '(')) {
            return false;
        }
    }

    // 检查连续运算符（除了一元运算符）
    for (size_t j = 1; j < tokens.size(); ++j) {
        if (tokens[j].type == OPERATOR && tokens[j - 1].type == OPERATOR) {
            return false;
        }
    }

    // 检查括号是否匹配
    std::stack<char> parenStack;
    for (const auto& token : tokens) {
        if (token.type == PARENTHESIS) {
            if (token.op == '(') {
                parenStack.push('(');
            }
            else if (token.op == ')') {
                if (parenStack.empty()) return false;
                parenStack.pop();
            }
        }
    }
    if (!parenStack.empty()) return false;

    return true;
}

bool ExpressionEvaluator::toPostfix(const std::vector<Token>& tokens, std::vector<Token>& postfix) {
    std::stack<Token> opStack;
    for (const auto& token : tokens) {
        if (token.type == NUMBER) {
            postfix.push_back(token);
        }
        else if (token.type == OPERATOR) {
            while (!opStack.empty() && opStack.top().type == OPERATOR &&
                   precedence(opStack.top().op) >= precedence(token.op)) {
                postfix.push_back(opStack.top());
                opStack.pop();
            }
            opStack.push(token);
        }
        else if (token.type == PARENTHESIS) {
            if (token.op == '(') {
                opStack.push(token);
            }
            else if (token.op == ')') {
                bool foundLeftParen = false;
                while (!opStack.empty()) {
                    Token topToken = opStack.top();
                    opStack.pop();
                    if (topToken.type == PARENTHESIS && topToken.op == '(') {
                        foundLeftParen = true;
                        break;
                    }
                    else {
                        postfix.push_back(topToken);
                    }
                }
                if (!foundLeftParen) return false; // 括号不匹配
            }
        }
    }

    while (!opStack.empty()) {
        Token topToken = opStack.top();
        opStack.pop();
        if (topToken.type == PARENTHESIS) return false; // 括号不匹配
        postfix.push_back(topToken);
    }

    return true;
}

bool ExpressionEvaluator::computePostfix(const std::vector<Token>& postfix, double& result) {
    std::stack<double> evalStack;
    for (const auto& token : postfix) {
        if (token.type == NUMBER) {
            evalStack.push(token.value);
        }
        else if (token.type == OPERATOR) {
            if (evalStack.size() < 2) return false;
            double b = evalStack.top(); evalStack.pop();
            double a = evalStack.top(); evalStack.pop();
            double res;
            switch (token.op) {
                case '+': res = a + b; break;
                case '-': res = a - b; break;
                case '*': res = a * b; break;
                case '/':
                    if (b == 0) return false;
                    res = a / b;
                    break;
                default: return false;
            }
            evalStack.push(res);
        }
    }
    if (evalStack.size() != 1) return false;
    result = evalStack.top();
    return true;
}

#endif // EXPRESSION_EVALUATOR_H
