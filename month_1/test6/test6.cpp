#include <iostream>
#include <vector>
using namespace std;

int main() {
    long long l, r, k;
    cin >> l >> r >> k;
    vector<long long> res;
    long long current = 1;
    
    if (current >= l && current <= r) {
        res.push_back(current);
    }
    
    while (current <= r / k) {
        current *= k;
        if (current >= l && current <= r) {
            res.push_back(current);
        }
    }
    
    if (res.empty()) {
        cout << -1;
    } else {
        for (size_t i = 0; i < res.size(); ++i) {
            if (i > 0) {
                cout << ' ';
            }
            cout << res[i];
        }
    }
    cout << endl;
    
    return 0;
}