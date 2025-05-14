#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    vector<vector<long long>> dp(1 << n, vector<long long>(n, 0));
    
    for (int i = 0; i < n; i++) {
        dp[1 << i][i] = 1;
    }
    
    for (int mask = 1; mask < (1 << n); mask++) {
        for (int last = 0; last < n; last++) {
            if (!(mask & (1 << last))) continue;
            
            for (int next = 0; next < n; next++) {
                if (mask & (1 << next)) continue;
                
                if (abs(a[last] - a[next]) > k) {
                    dp[mask | (1 << next)][next] += dp[mask][last];
                }
            }
        }
    }
    
    long long result = 0;
    for (int last = 0; last < n; last++) {
        result += dp[(1 << n) - 1][last];
    }
    
    cout << result << endl;
    
    return 0;
}