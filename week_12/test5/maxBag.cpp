#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n;
    ll m;
    cin >> n >> m;
    
    vector<ll> w(n), c(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i] >> c[i];
    }
    
    if (n <= 40) {
        int mid = n / 2;

        map<ll, ll> first;
        first[0] = 0;
        
        for (int i = 0; i < mid; i++) {
            vector<pair<ll, ll>> temp;
            for (auto& [weight, value] : first) {
                if (weight + w[i] <= m) {
                    temp.push_back({weight + w[i], value + c[i]});
                }
            }
            
            for (auto& [weight, value] : temp) {
                if (first.count(weight) == 0 || first[weight] < value) {
                    first[weight] = value;
                }
            }
        }

        ll result = 0;
        map<ll, ll> second;
        second[0] = 0;
        
        for (int i = mid; i < n; i++) {
            vector<pair<ll, ll>> temp;
            for (auto& [weight, value] : second) {
                if (weight + w[i] <= m) {
                    temp.push_back({weight + w[i], value + c[i]});
                }
            }
            
            for (auto& [weight, value] : temp) {
                if (second.count(weight) == 0 || second[weight] < value) {
                    second[weight] = value;
                }
            }
        }
        
        for (auto& [weight1, value1] : first) {
            auto it = second.upper_bound(m - weight1);
            if (it != second.begin()) {
                --it;
                if (weight1 + it->first <= m) {
                    result = max(result, value1 + it->second);
                }
            }
        }
        
        cout << result << endl;
    } else {
        vector<pair<double, int>> ratio(n);
        for (int i = 0; i < n; i++) {
            ratio[i] = {(double)c[i] / w[i], i};
        }
        
        sort(ratio.rbegin(), ratio.rend());

        vector<pair<ll, ll>> selected;
        for (int i = 0; i < min(30, n); i++) {
            int idx = ratio[i].second;
            selected.push_back({w[idx], c[idx]});
        }
        
        ll max_weight = min(m, 100000LL);
        vector<ll> dp(max_weight + 1, 0);
        
        for (auto& [weight, value] : selected) {
            for (ll j = max_weight; j >= weight; j--) {
                dp[j] = max(dp[j], dp[j - weight] + value);
            }
        }
        
        cout << dp[max_weight] << endl;
    }
    
    return 0;
}