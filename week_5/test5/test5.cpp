#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>
using namespace std;

const int MOD = 1e9 + 7;

vector<pair<int, int>> factorize(int c) {
    vector<pair<int, int>> res;
    if (c == 1) return res;
    for (int p = 2; p * p <= c; ++p) {
        if (c % p == 0) {
            int cnt = 0;
            while (c % p == 0) {
                cnt++;
                c /= p;
            }
            res.emplace_back(p, cnt);
        }
    }
    if (c > 1) res.emplace_back(c, 1);
    return res;
}

vector<vector<pair<int, int>>> precompute_factors() {
    vector<vector<pair<int, int>>> factors(101);
    for (int c = 0; c <= 100; ++c) {
        factors[c] = factorize(c);
    }
    return factors;
}

long long mod_pow(long long a, long long b, long long mod) {
    long long res = 1;
    a %= mod;
    while (b > 0) {
        if (b % 2 == 1)
            res = res * a % mod;
        a = a * a % mod;
        b /= 2;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    auto pre_factors = precompute_factors();
    int n, m;
    cin >> n >> m;
    unordered_map<int, vector<long long>> diff_map;

    while (m--) {
        int l, r, c, b;
        cin >> l >> r >> c >> b;
        if (b == 0) continue;
        const auto& factors = pre_factors[c];
        for (const auto& [p, k] : factors) {
            long long delta = static_cast<long long>(k) * b;
            if (delta == 0) continue;
            auto& diff = diff_map[p];
            if (diff.empty()) {
                diff.resize(n + 2, 0);
            }
            diff[l] += delta;
            diff[r + 1] -= delta;
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
            result = result * mod_pow(p, min_exp, MOD) % MOD;
        }
    }

    cout << result << endl;
    return 0;
}