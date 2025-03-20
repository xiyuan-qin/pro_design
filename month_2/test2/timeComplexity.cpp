#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <stack>

using namespace std;

// 多项式类，用于表示时间复杂度
class Polynomial {
private:
    map<int, int> coefficients; // 次数 -> 系数

public:
    // 添加一项
    void add(int coef, int power) {
        if (coef == 0) return;
        coefficients[power] += coef;
        if (coefficients[power] == 0) {
            coefficients.erase(power);
        }
    }

    // 添加另一个多项式
    void add(const Polynomial& other) {
        for (const auto& term : other.coefficients) {
            add(term.second, term.first);
        }
    }

    // 与常数相乘
    void multiply(int factor) {
        if (factor == 0) {
            coefficients.clear();
            return;
        }

        for (auto& term : coefficients) {
            term.second *= factor;
        }
    }

    // 与n^power相乘
    void multiplyByPower(int power) {
        if (power == 0) return;
        
        map<int, int> newCoefficients;
        for (const auto& term : coefficients) {
            newCoefficients[term.first + power] = term.second;
        }
        coefficients = newCoefficients;
    }

    // 转换为字符串
    string toString() const {
        if (coefficients.empty()) {
            return "0";
        }

        stringstream ss;
        bool first = true;

        // 从高次到低次输出
        for (auto it = coefficients.rbegin(); it != coefficients.rend(); ++it) {
            int power = it->first;
            int coef = it->second;
            
            if (coef == 0) continue;
            
            if (!first) {
                ss << "+";
            }
            first = false;

            if (power == 0) {
                // 常数项
                ss << coef;
            } else {
                // 变量项
                if (coef != 1) {
                    ss << coef << "*";
                }
                ss << "n";
                if (power > 1) {
                    ss << "^" << power;
                }
            }
        }
        
        return ss.str();
    }
};

// 词法分析器
class Lexer {
private:
    string input;
    size_t position;

public:
    enum TokenType {
        BEGIN, END, LOOP, OP, NUMBER, VARIABLE_N, INVALID, EOF_TOKEN
    };

    struct Token {
        TokenType type;
        int value; // 对于NUMBER类型有效
        
        Token(TokenType t, int v = 0) : type(t), value(v) {}
    };

    Lexer(const string& program) : input(program), position(0) {}

    // 跳过空白字符
    void skipWhitespace() {
        while (position < input.size() && isspace(input[position])) {
            position++;
        }
    }

    // 获取下一个标记
    Token nextToken() {
        skipWhitespace();
        
        if (position >= input.size()) {
            return Token(EOF_TOKEN);
        }

        if (isalpha(input[position])) {
            size_t start = position;
            while (position < input.size() && isalpha(input[position])) {
                position++;
            }
            
            string keyword = input.substr(start, position - start);
            
            if (keyword == "BEGIN") return Token(BEGIN);
            if (keyword == "END") return Token(END);
            if (keyword == "LOOP") return Token(LOOP);
            if (keyword == "OP") return Token(OP);
            if (keyword == "n") return Token(VARIABLE_N);
            
            cerr << "Unknown keyword: " << keyword << endl;
            return Token(INVALID);
        }
        else if (isdigit(input[position])) {
            size_t start = position;
            while (position < input.size() && isdigit(input[position])) {
                position++;
            }
            
            int value = stoi(input.substr(start, position - start));
            return Token(NUMBER, value);
        }
        
       
    }

    // 回退位置
    void backup(size_t pos) {
        position = pos;
    }

    // 获取当前位置
    size_t getPosition() const {
        return position;
    }
};

// 解析器
class Parser {
private:
    Lexer lexer;
    Lexer::Token currentToken;

    void nextToken() {
        currentToken = lexer.nextToken();
    }

    // 检查当前token类型
    bool match(Lexer::TokenType type) {
        return currentToken.type == type;
    }

    // 解析程序
    Polynomial parseProgram() {
        // 期望 "BEGIN"
        if (!match(Lexer::BEGIN)) {
            cerr << "Expected BEGIN" << endl;
            exit(1);
        }
        nextToken();
        
        // 解析语句列表
        Polynomial result = parseStatementList();
        
        // 期望 "END"
        if (!match(Lexer::END)) {
            cerr << "Expected END" << endl;
            exit(1);
        }
        nextToken();
        
        return result;
    }

    // 解析语句列表
    Polynomial parseStatementList() {
        Polynomial total;
        
        // 解析语句，直到遇到END或文件结束
        while (!match(Lexer::END) && !match(Lexer::EOF_TOKEN)) {
            Polynomial stmt = parseStatement();
            total.add(stmt);
        }
        
        return total;
    }

    // 解析单个语句
    Polynomial parseStatement() {
        if (match(Lexer::LOOP)) {
            return parseLoopStatement();
        } else if (match(Lexer::OP)) {
            return parseOpStatement();
        } else {
            cerr << "Expected LOOP or OP" << endl;
            exit(1);
        }
    }

    // 解析LOOP语句
    Polynomial parseLoopStatement() {
        // 读取 "LOOP"
        if (!match(Lexer::LOOP)) {
            cerr << "Expected LOOP" << endl;
            exit(1);
        }
        nextToken();
        
        // 读取循环次数（n或数字）
        bool isLoopN = false;
        int loopCount = 0;
        
        if (match(Lexer::VARIABLE_N)) {
            isLoopN = true;
            nextToken();
        } else if (match(Lexer::NUMBER)) {
            loopCount = currentToken.value;
            nextToken();
        } else {
            cerr << "Expected loop count or n" << endl;
            exit(1);
        }
        
        // 解析循环体
        Polynomial body = parseStatementList();
        
        // 期望 "END"
        if (!match(Lexer::END)) {
            cerr << "Expected END for LOOP" << endl;
            exit(1);
        }
        nextToken();
        
        // 计算运行时间
        if (isLoopN) {
            body.multiplyByPower(1); // 乘以n
        } else {
            body.multiply(loopCount); // 乘以常数循环次数
        }
        
        return body;
    }

    // 解析OP语句
    Polynomial parseOpStatement() {
        // 读取 "OP"
        if (!match(Lexer::OP)) {
            cerr << "Expected OP" << endl;
            exit(1);
        }
        nextToken();
        
        // 读取操作时间
        if (!match(Lexer::NUMBER)) {
            cerr << "Expected number after OP" << endl;
            exit(1);
        }
        
        int opTime = currentToken.value;
        nextToken();
        
        // 创建运行时间多项式
        Polynomial result;
        result.add(opTime, 0); // 常数项
        return result;
    }

public:
    Parser(const string& program) : lexer(program), currentToken(Lexer::INVALID) {
        nextToken();
    }

    // 开始解析
    Polynomial parse() {
        return parseProgram();
    }
};

int main() {
    try {
        // 读取输入程序，一次读取全部内容直到EOF
        string program, line;
        while (getline(cin, line)) {
            program += line + "\n";
        }
        
        if (program.empty()) {
            cerr << "Empty input" << endl;
            return 1;
        }
        
        // 解析程序并计算时间复杂度
        Parser parser(program);
        Polynomial runtime = parser.parse();
        
        // 输出结果
        cout << "Runtime = " << runtime.toString() << endl;
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
