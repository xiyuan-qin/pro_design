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
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        
        if (n == 0) {
            cout << "0 0\n";
            continue;
        }
        
        //现金
        ll cash_profit = 0;         // 初始持有现金，利润为0
        int cash_trans = 0;         // 初始交易次数为0
        ll hold_profit = -a[0];     // 买入第一天后的利润
        int hold_trans = 1;         // 买入操作计为1次交易
        
        for (int i = 1; i < n; ++i) {
            int price = a[i];
            
            // 更新持有现金状态 - 可以从持股状态通过卖出转移而来
            ll new_cash_profit = cash_profit;  // 默认保持不变
            int new_cash_trans = cash_trans;
            ll candidate = hold_profit + price;  // 卖出的潜在利润
            
            if (candidate > new_cash_profit) {  // 如果卖出更有利
                new_cash_profit = candidate;
                new_cash_trans = hold_trans + 1;  // 卖出算一次交易
            } else if (candidate == new_cash_profit) {  // 利润相同时
                new_cash_trans = min(new_cash_trans, hold_trans + 1);  // 选择交易次数更少的
            }
            
            // 更新持有状态 - 可以从持现金状态通过买入转移而来
            ll new_hold_profit = hold_profit;  // 默认保持不变
            int new_hold_trans = hold_trans;
            candidate = cash_profit - price;  // 买入的潜在利润
            
            if (candidate > new_hold_profit) {  // 如果买入更有利
                new_hold_profit = candidate;
                new_hold_trans = cash_trans + 1;  // 买入算一次交易
            } else if (candidate == new_hold_profit) {  // 利润相同时
                new_hold_trans = min(new_hold_trans, cash_trans + 1);  // 选择交易次数更少的
            }
            
            // 应用状态更新
            cash_profit = new_cash_profit;
            cash_trans = new_cash_trans;
            hold_profit = new_hold_profit;
            hold_trans = new_hold_trans;
        }
        
        cout << cash_profit << ' ' << cash_trans << '\n';
    }
    
    return 0;
}