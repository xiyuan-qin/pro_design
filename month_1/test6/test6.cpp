#include <iostream>
using namespace std;

int main() {
    long long l, r, k;
    cin >> l >> r >> k;
    
    long long num = 1;
    bool found = false;
    
    // 处理k^0的情况，即1
    if (num >= l && num <= r) {
        cout << num << " ";
        found = true;
    }
    
    while (true) {
        long long next_num = num * k;
        // 检查是否溢出或超过r
        if (next_num > r || next_num < num) {  // 溢出或超过r则终止
            break;
        }
        num = next_num;
        if (num >= l) {  // 确认num在范围内
            cout << num << " ";
            found = true;
        }
    }
    
    if (!found) {
        cout << -1;
    }
    cout << endl;
    
    return 0;
}
