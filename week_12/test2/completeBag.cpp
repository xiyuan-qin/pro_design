#include<iostream>
#include<vector>

using namespace std;

int main(){
    int n , contability_of_bag;
    cin >> n >> contability_of_bag;

    vector<int> weight(n, 0);
    vector<int> value(n, 0);
    
    for(int i = 0; i < n; i++){
        cin >> weight[i];
        cin >> value[i];
    }

    vector<vector<int>> dp(n + 1, vector<int>(contability_of_bag + 1, 0));
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= contability_of_bag; j++){
            if(weight[i - 1] <= j){// 确保背包能装下当前物品
                dp[i][j] = max(dp[i - 1][j], dp[i][j - weight[i - 1]] + value[i - 1]);
            } else {// 不然只能装之前的物品
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    cout << dp[n][contability_of_bag] << endl;
    return 0;
}