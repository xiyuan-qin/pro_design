#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main(){
    int n, V;
    cin >> n >> V;

    vector<int> w(n, 0);  
    vector<int> c(n, 0);  
    vector<int> k(n, 0);  

    for(int i = 0; i < n; i++){
        cin >> w[i] >> c[i] >> k[i];
    }


    int groupCount = 0;
    for(int i = 0; i < n; i++){
        groupCount = max(groupCount, k[i]);
    }

   
    vector<vector<pair<int, int>>> groups(groupCount + 1);
    for(int i = 0; i < n; i++){
        groups[k[i]].push_back({w[i], c[i]});
    }


    vector<int> dp(V + 1, 0);
    
    for(int g = 1; g <= groupCount; g++){ // 遍历每个组
        for(int j = V; j >= 0; j--){ // 逆序遍历容量
            for(auto& item : groups[g]){ // 遍历组内每个物品
                int weight = item.first;
                int value = item.second;
                if(j >= weight){
                    dp[j] = max(dp[j], dp[j - weight] + value);
                }
            }
        }
    }

    cout << dp[V] << endl;
    return 0;
}