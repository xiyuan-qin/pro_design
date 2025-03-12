#include <iostream>
#include <vector>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int& num : a) {
            cin >> num;
        }
        
        if (n == 0) {
            cout << "0 0\n";
            continue;
        }
        
        ll cash_profit = 0;
        int cash_trans = 0;
        ll hold_profit = -a[0];
        int hold_trans = 1;
        
        for (int i = 1; i < n; ++i) {
            int price = a[i];
            
            // Update cash state
            ll new_cash_profit = cash_profit;
            int new_cash_trans = cash_trans;
            ll candidate = hold_profit + price;
            if (candidate > new_cash_profit) {
                new_cash_profit = candidate;
                new_cash_trans = hold_trans + 1;
            } else if (candidate == new_cash_profit) {
                new_cash_trans = min(new_cash_trans, hold_trans + 1);
            }
            
            // Update hold state
            ll new_hold_profit = hold_profit;
            int new_hold_trans = hold_trans;
            candidate = cash_profit - price;
            if (candidate > new_hold_profit) {
                new_hold_profit = candidate;
                new_hold_trans = cash_trans + 1;
            } else if (candidate == new_hold_profit) {
                new_hold_trans = min(new_hold_trans, cash_trans + 1);
            }
            
            // Apply updates
            cash_profit = new_cash_profit;
            cash_trans = new_cash_trans;
            hold_profit = new_hold_profit;
            hold_trans = new_hold_trans;
        }
        
        cout << cash_profit << ' ' << cash_trans << '\n';
    }
    
    return 0;
}