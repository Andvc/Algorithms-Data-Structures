#include <iostream>
#include <vector>
#include <utility>
#include <sstream>
#include "expression_evaluator.h"

int main() {
    ExpressionEvaluator evaluator;
    std::string expr;

    // 测试用例
    std::vector<std::pair<std::string, std::string>> testCases = {
        {"1+2", "3"},
        {"(1+2)*3", "9"},
        {"1 + 2 * 3 - 4 / 2", "5"},
        {"-1 + 2", "1"},
        {"1+-2.1", "-1.1"},
        {"2e2 + 1", "201"},
        {"-1 + 2e2", "199"},
        {"1++2.1", "ILLEGAL"},
        {"(1+2", "ILLEGAL"},
        {"1+2)", "ILLEGAL"},
        {"1+/2", "ILLEGAL"},
        {"1/0", "ILLEGAL"},
        {"--1 + 2", "ILLEGAL"},
        {"1 +* 2", "ILLEGAL"},
        {"", "ILLEGAL"},
        {"   ", "ILLEGAL"},
        {"3.5e+2 - 100", "250"},
        {"(2+3)*(5-2)/3", "5"},
        {"4*(5+(6-2))/ (3+1)", "8"},
        {"-2.5 * 4", "-10"},
        {"-2.5 * -4", "10"},
        {"1 + (2 * (2.5 + 2.5))", "11"},
        {"1 + 2e-2", "1.02"},
        {"1 + 2e", "ILLEGAL"},
        {"1 + 2e+", "ILLEGAL"},
        {"1 + 2e-2", "1.02"},
        {"-1+2e2", "199"},
        {"1.2.3 + 4", "ILLEGAL"},
        {"1 + (2 * 3))", "ILLEGAL"},
        {"(1 + (2 * 3)", "ILLEGAL"},
        {"(1 + 2) * (3 / (4 - 4))", "ILLEGAL"}, // Division by zero
        {"5 + ", "ILLEGAL"},
        {"+5", "5"},
        {"-5", "-5"},
        {"-5 + 3", "-2"},
        {"+5 + +3", "8"},
        {"-5 + +3", "-2"},
    };

    std::cout << "运行测试用例:\n";
    for (const auto& test : testCases) {
        double res;
        bool valid = evaluator.evaluate(test.first, res);
        if (valid) {
            std::ostringstream oss;
            oss << res;
            // 去掉末尾的.0
            std::string resStr = oss.str();
            if (resStr.find('.') != std::string::npos) {
                // 移除末尾的0和可能的点
                resStr.erase(resStr.find_last_not_of('0') + 1, std::string::npos);
                if (resStr.back() == '.') {
                    resStr.pop_back();
                }
            }
            std::cout << "表达式: \"" << test.first << "\" = " << resStr << "\n";
        }
        else {
            std::cout << "表达式: \"" << test.first << "\" = ILLEGAL\n";
        }
    }

    std::cout << "\n请输入一个中缀表达式（或按Ctrl+D结束）：\n";
    while (std::getline(std::cin, expr)) {
        if (expr.empty() || expr.find_first_not_of(' ') == std::string::npos) {
            std::cout << "ILLEGAL\n";
            continue;
        }
        double result;
        bool valid = evaluator.evaluate(expr, result);
        if (valid) {
            std::ostringstream oss;
            oss << result;
            // 去掉末尾的.0
            std::string resStr = oss.str();
            if (resStr.find('.') != std::string::npos) {
                // 移除末尾的0和可能的点
                resStr.erase(resStr.find_last_not_of('0') + 1, std::string::npos);
                if (resStr.back() == '.') {
                    resStr.pop_back();
                }
            }
            std::cout << resStr << "\n";
        }
        else {
            std::cout << "ILLEGAL\n";
        }
    }

    return 0;
}
