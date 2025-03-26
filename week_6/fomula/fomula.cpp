#include <iostream>
#include <string>
#include <map>
#include <cctype>

using namespace std;

// 解析化学式，返回每种元素的原子数
map<string, long long> parseFormula(const string& formula, int& pos);

// 解析元素或括号内的化学式
map<string, long long> parseTerm(const string& formula, int& pos) {
    map<string, long long> elements;
    
    if (formula[pos] == '(') {
        pos++; // 跳过左括号
        elements = parseFormula(formula, pos);
        pos++; // 跳过右括号
    } else {
        string element;
        element += formula[pos++];
        
        // 如果后面跟着小写字母，则是两字母元素
        if (pos < formula.length() && islower(formula[pos])) {
            element += formula[pos++];
        }
        
        elements[element] = 1;
    }
    
    // 解析系数
    long long count = 0;
    while (pos < formula.length() && isdigit(formula[pos])) {
        count = count * 10 + (formula[pos++] - '0');
    }
    
    // 如果没有指定系数，默认为1
    if (count == 0) {
        count = 1;
    }
    
    // 将项中的元素乘以系数
    for (auto& elem : elements) {
        elem.second *= count;
    }
    
    return elements;
}

// 解析化学式
map<string, long long> parseFormula(const string& formula, int& pos) {
    map<string, long long> elements;
    
    while (pos < formula.length() && formula[pos] != '+' && formula[pos] != '=' && formula[pos] != ')') {
        map<string, long long> termElements = parseTerm(formula, pos);
        
        // 合并项中的元素到化学式
        for (const auto& elem : termElements) {
            elements[elem.first] += elem.second;
        }
    }
    
    return elements;
}

// 解析表达式，即化学式的组合
map<string, long long> parseExpression(const string& expr) {
    map<string, long long> totalElements;
    int pos = 0;
    
    while (pos < expr.length()) {
        // 解析系数
        long long coef = 0;
        while (pos < expr.length() && isdigit(expr[pos])) {
            coef = coef * 10 + (expr[pos++] - '0');
        }
        
        // 如果没有指定系数，默认为1
        if (coef == 0) {
            coef = 1;
        }
        
        // 解析化学式
        map<string, long long> formulaElements = parseFormula(expr, pos);
        
        // 将化学式中的元素乘以系数
        for (const auto& elem : formulaElements) {
            totalElements[elem.first] += elem.second * coef;
        }
        
        // 跳过加号
        if (pos < expr.length() && expr[pos] == '+') {
            pos++;
        }
    }
    
    return totalElements;
}

// 判断化学方程式是否配平
bool isBalanced(const string& equation) {
    // 分割等号左右两边的表达式
    size_t eqPos = equation.find('=');
    string leftExpr = equation.substr(0, eqPos);
    string rightExpr = equation.substr(eqPos + 1);
    
    // 解析左右两边的表达式
    map<string, long long> leftElements = parseExpression(leftExpr);
    map<string, long long> rightElements = parseExpression(rightExpr);
    
    // 比较左右两边的元素原子数
    if (leftElements.size() != rightElements.size()) {
        return false;
    }
    
    for (const auto& elem : leftElements) {
        if (rightElements.find(elem.first) == rightElements.end() || 
            rightElements[elem.first] != elem.second) {
            return false;
        }
    }
    
    return true;
}

int main() {
    int n;
    cin >> n;
    
    for (int i = 0; i < n; i++) {
        string equation;
        cin >> equation;
        
        if (isBalanced(equation)) {
            cout << "Y" << endl;
        } else {
            cout << "N" << endl;
        }
    }
    
    return 0;
}
