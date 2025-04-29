#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    
    vector<int> nums(n);
    for(int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    unordered_map<int, long long> sum;
    for(int num : nums) {
        sum[num] += num;
    }
    
    vector<int> values;
    for(auto p : sum) {
        values.push_back(p.first);
    }
    sort(values.begin(), values.end());
    
    int m = values.size();
    vector<vector<long long>> dp(m, vector<long long>(2, 0));

    dp[0][0] = 0;
    dp[0][1] = sum[values[0]];
    
    for(int i = 1; i < m; i++) {
        dp[i][0] = max(dp[i-1][0], dp[i-1][1]);
        
        if(values[i] - values[i-1] == 1) {
            dp[i][1] = dp[i-1][0] + sum[values[i]];
        } else {
            dp[i][1] = max(dp[i-1][0], dp[i-1][1]) + sum[values[i]];
        }
    }
    
    cout << max(dp[m-1][0], dp[m-1][1]) << endl;
    
    return 0;
}

