#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<stack>

using namespace std;

bool isVowel(char c) {
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

int main(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    
    string result;
    bool inVowelGroup = false;
    
    for (int i = 0; i < n; i++) {
        if (isVowel(s[i])) {
            if (!inVowelGroup) {
                // 如果这是一组元音的第一个，添加到结果
                result += s[i];
                inVowelGroup = true;
            }
            // 如果是元音组中的非第一个，忽略不处理
        } else {
            // 如果是辅音，添加到结果并重置元音组标志
            result += s[i];
            inVowelGroup = false;
        }
    }
    
    cout << result << endl;
    
    return 0;
}