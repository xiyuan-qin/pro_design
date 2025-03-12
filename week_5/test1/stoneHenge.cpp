#include<iostream>
#include<vector>

using namespace std;

int main(){
    int n, m;
    cin >> n;

    string stone;
    cin >> stone;
    stone = " " + stone; //从1开始
    
    
    vector<vector<int>> prefix(n + 1, vector<int>(26, 0));//从字符串起始到第i个位置，字母j出现的次数
    
    for(int i = 1; i <= n; i++){
        // 复制前一个位置的所有字母出现情况
        for(int j = 0; j < 26; j++){
            prefix[i][j] = prefix[i-1][j];
        }
        // 更新
        prefix[i][stone[i] - 'A']++;
    }
    
    cin >> m;

    for(int i = 0; i < m; i++){
        int l, r;
        cin >> l >> r;
        
        int count = 0; // 记录区间内不同字母的数量
        
        //计算区间[l,r]内每个字母是否出现
        for(int j = 0; j < 26; j++){
            if(prefix[r][j] - prefix[l-1][j] > 0){
                count++;
            }
        }
        
        if(count == 26){
            cout << "YES" << endl;
        }else{
            cout << "NO" << endl;
        }
    }

    return 0;
}