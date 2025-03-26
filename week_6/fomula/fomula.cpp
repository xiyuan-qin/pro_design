#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>
#include<map>

using namespace std;

class ElementCounts{
public:
    map<string, int> element_counts;

    bool isEqual(const ElementCounts& other) const{
        return element_counts == other.element_counts;
    }

    void merge(const ElementCounts& other){
        for(const auto& [element , count] : other.element_counts){
            element_counts[element] += count;
        }
    }

    void scale(int multiplier){
        for(auto& [element , count] : element_counts){
            count *= multiplier;
        }
    }
};

// 添加前向声明
int parseNumber(const string& formula, int& pos);
string parseElement(const string& formula, int& pos);

ElementCounts parseFormula(const string& formula, int& pos){
    ElementCounts current_count;
    int base_multiplier = parseNumber(formula, pos);
    
    while (pos < formula.size()){
        if(formula[pos] == '('){
            pos++; // 跳过左括号
            ElementCounts sub_formula = parseFormula(formula, pos);
            sub_formula.scale(base_multiplier);
            base_multiplier = 1; // 重置乘数，只用于第一次
            current_count.merge(sub_formula);
        }
        else if(formula[pos] == ')'){
            pos++; // 跳过右括号
            return current_count; // 括号闭合时返回当前结果
        }
        else{
            string element = parseElement(formula, pos);
            int element_count = parseNumber(formula, pos);
            current_count.element_counts[element] += element_count * base_multiplier;
            base_multiplier = 1; // 重置乘数，只用于第一次
        }
    }
    return current_count;
}

// 实现这些函数
int parseNumber(const string& formula, int& pos) {
    int result = 0;
    while (pos < formula.length() && isdigit(formula[pos])) {
        result = result * 10 + (formula[pos] - '0');
        pos++;
    }
    return result == 0 ? 1 : result;  // 如果没有数字，返回1作为默认乘数
}

string parseElement(const string& formula, int& pos) {
    string element;
    // 元素的第一个字母必须是大写
    if (pos < formula.length() && isupper(formula[pos])) {
        element += formula[pos++];
        // 元素可能有第二个小写字母
        if (pos < formula.length() && islower(formula[pos])) {
            element += formula[pos++];
        }
    }
    return element;
}

vector<string> splitString(const string& equation, char delimiter){
    vector<string> tokens;
    string token;
    for(char ch : equation){
        if(ch == delimiter){
            if(!token.empty()){
                tokens.push_back(token);
                token.clear();
            }
        }
        else{
            token += ch;
        }
    }
    if(!token.empty()){
        tokens.push_back(token);
    }
    return tokens;
}

bool isBalancedEquation(const string& equation){
    vector<string> equation_sides = splitString(equation, '=');
    ElementCounts left_side , right_side;
    for(int side = 0 ; side < 2 ; side ++){
        vector<string> formulas = splitString(equation_sides[side], '+');
        for(const string& formula : formulas){
            int pos = 0;
            ElementCounts formula_counts = parseFormula(formula, pos);
            if(side == 0) left_side.merge(formula_counts);
            else right_side.merge(formula_counts);
        }
    }

    return left_side.isEqual(right_side);
}

int main(){
    int n ;
    cin >> n;

    while(n--){
        string s;
        cin >> s;

        if(isBalancedEquation(s)){
            puts("Y");
        }
        else{
            puts("N");
        }
    }
    return 0;
}