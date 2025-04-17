#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

void preProcess(string &str) {
    // 把所有的元音字母都变成a
    for(int i = 0; i < str.size(); i++) {
        if(str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u') {
            str[i] = 'a';
        }
    }
}


int longestPalindromeSubstr(const string &s) {
    int n = s.length();
    if (n == 0) return 0;
    
    //在每个字符间插入特殊字符
    string t = "#";
    for (int i = 0; i < n; i++) {
        t += s[i];
        t += "#";
    }
    
    n = t.length();
    vector<int> p(n, 0); // 回文半径
    int center = 0, right = 0; // 中心和右边界
    int maxLen = 0; // 最长回文子串长度
    
    for (int i = 0; i < n; i++) {

        if (right > i) {// 对称
            p[i] = min(right - i, p[2 * center - i]);
        }
        
        // 中心扩展
        while (i - p[i] - 1 >= 0 
            && i + p[i] + 1 < n //同时向左检查i-1-p[i]和向右检查i+1+p[i]位置的字符
            && t[i - p[i] - 1] == t[i + p[i] + 1]) {//如果两边字符相同，p[i]增加1，继续扩展

            p[i]++;
        }
        
        if (i + p[i] > right) {
            center = i;
            right = i + p[i];
        }
        
        maxLen = max(maxLen, p[i]);
    }
    
    // 在添加特殊字符后的字符串中，maxLen即为原始字符串的最长回文子串长度
    return maxLen;
}

int main() {
    int n;
    cin >> n;
    string str;
    cin >> str;
    
    preProcess(str); 
    
    cout << longestPalindromeSubstr(str) << endl;
    
    return 0;
}