#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>
using namespace std;

const int MOD = 1e9 + 7;

vector<pair<int, int>> factorize(int c) {
    vector<pair<int, int>> res;
    if (c == 1) return res;
    for (int i = 2; i * i <= c; ++i) {
        if (c % i == 0) {
            int cnt = 0;
            while (c % i == 0) {
                cnt++;
                c /= i;
            }
            res.emplace_back(i, cnt);
        }
    }
    if (c > 1) {
        res.emplace_back(c, 1);
    }
    return res;
}

long long pow_mod(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n, m;
    cin >> n >> m;
    
    vector<vector<pair<int, int>>> pre_factor(101);
    for (int c = 1; c <= 100; ++c) {
        pre_factor[c] = factorize(c);
    }
    
    unordered_map<int, vector<long long>> diff_map;
    
    for (int i = 0; i < m; ++i) {
        int l, r, c, b;
        cin >> l >> r >> c >> b;
        if (c == 1) continue;
        auto factors = pre_factor[c];
        for (auto& [p, e] : factors) {
            long long add = (long long)e * b;
            if (add == 0) continue;
            if (diff_map.find(p) == diff_map.end()) {
                diff_map[p] = vector<long long>(n + 2, 0LL);
            }
            auto& diff = diff_map[p];
            diff[l] += add;
            if (r + 1 <= n) {
                diff[r + 1] -= add;
            }
        }
    }
    
    long long result = 1;
    for (auto& [p, diff] : diff_map) {
        long long current = 0;
        long long min_exp = LLONG_MAX;
        for (int i = 1; i <= n; ++i) {
            current += diff[i];
            if (current < min_exp) {
                min_exp = current;
            }
        }
        if (min_exp > 0) {
            result = (result * pow_mod(p, min_exp, MOD)) % MOD;
        }
    }
    
    cout << result << endl;
    return 0;
}