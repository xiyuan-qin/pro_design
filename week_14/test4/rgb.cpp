#include <iostream>
#include <vector>
using namespace std;

long long power(long long base, long long exp) {
    long long res = 1;
    long long mod = 998244353;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

long long modInverse(long long n) {
    long long mod = 998244353;
    return power(n, mod - 2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    long long inv4 = modInverse(4);
    long long mod = 998244353;

    while (T--) {
        long long n;
        cin >> n;

        long long term_3_pow_n = power(3, n);
        long long numerator_val;

        if (n % 2 == 0) { 
            numerator_val = (term_3_pow_n + 3) % mod;
        } else { 
            numerator_val = (term_3_pow_n + 1) % mod;
        }
        
        if (numerator_val < 0) {
            numerator_val += mod;
        }

        long long ans = (numerator_val * inv4) % mod;
        cout << ans << endl;
    }

    return 0;
}