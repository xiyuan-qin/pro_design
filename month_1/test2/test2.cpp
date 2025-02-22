#include<iostream>
#include<string>
#include<cctype>

using namespace std;

/**
 * 三个条件：
 * 1. 大小写都有
 * 2. 全部的26个字母都有
 * 3. 不会出现连续重复的字母，但是可以有重复的字母
 */

int main() {
    int n;
    cin >> n;
    for(int i = 0 ; i < n ; i++ ){
        string str;
        cin >> str;
            int upper = 0, lower = 0;
            int letter[26] = {0};
            for (int i = 0; i < str.size(); i++) {
                if (str[i] >= 'A' && str[i] <= 'Z') {// 大写字母
                    upper = 1;
                    letter[str[i] - 'A'] = 1;

                } else if (str[i] >= 'a' && str[i] <= 'z') {// 小写字母
                    lower = 1;
                    letter[str[i] - 'a'] = 1;
                }
                
            }
            int sum = 0;
            for (int i = 0; i < 26; i++) {
                sum += letter[i];
            }
            if (sum == 26 && upper && lower) {
                cout << "no" << endl;
            } else {
                cout << "yes" << endl;
            }
        

    }
    return 0;
}