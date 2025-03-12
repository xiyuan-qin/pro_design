#include<iostream>
#include<vector>

using namespace std;

bool ifCould(int l , int r , int n , string stone){
    vector<vector<int>> prefix(n + 1, vector<int>(26, 0));//从字符串起始到第i个位置，字母j出现的次数
    
    for(int i = 1; i <= n; i++){
        // 复制前一个位置的所有字母出现情况
        for(int j = 0; j < 26; j++){
            prefix[i][j] = prefix[i-1][j];
        }
        // 更新
        prefix[i][stone[i] - 'A']++;
    }

        
        int count = 0; // 记录区间内不同字母的数量
        
        //计算区间[l,r]内每个字母是否出现
        for(int j = 0; j < 26; j++){
            if(prefix[r][j] - prefix[l-1][j] > 0){
                count++;
            }
        }
        
        if(count == 26){
            return true;
        }else{
            return false;
        }
}

int main(){
    int n;
    cin >> n;

    string stone;
    cin >> stone;
    stone = " " + stone; //从1开始

    int result = 100;
    for(int i = 0; i < n; i++){
        for(int j = i; j < n; j++){
            if(ifCould(i , j , n , stone)){
                result = min(result , j - i + 1);
            }
        }
    }
    
    
    cout << result << endl;

    return 0;
}