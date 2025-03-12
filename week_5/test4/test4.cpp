#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> h(n);
    for (int i = 0; i < n; ++i) {
        cin >> h[i];
    }
    if (n == 0) {
        cout << 0 << endl;
        return 0;
    }
    stack<int> stk;
    long long max_area = 0;
    for (int i = 0; i < n; ++i) {
        while (!stk.empty() && h[i] <= h[stk.top()]) {
            int current = stk.top();
            stk.pop();
            int left = stk.empty() ? -1 : stk.top();
            long long width = i - left - 1;
            max_area = max(max_area, h[current] * width);
        }
        stk.push(i);
    }
    while (!stk.empty()) {
        int current = stk.top();
        stk.pop();
        int left = stk.empty() ? -1 : stk.top();
        long long width = n - left - 1;
        max_area = max(max_area, h[current] * width);
    }
    cout << max_area << endl;
    return 0;
}