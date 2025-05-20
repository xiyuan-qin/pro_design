#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
using namespace std;

int main() {
    long long n, m;
    cin >> n >> m;
    
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    vector<long long> prefixSum(n + 1, 0);
    for (int i = 0; i < n; i++) {
        prefixSum[i + 1] = prefixSum[i] + a[i];
    }
    
    long long maxSum = 0; 
    
    deque<int> q;
    q.push_back(0); 
    
    for (int i = 1; i <= n; i++) {
        while (!q.empty() && i - q.front() > m) {
            q.pop_front();
        }
        
        if (!q.empty()) {
            maxSum = max(maxSum, prefixSum[i] - prefixSum[q.front()]);
        }
        
        while (!q.empty() && prefixSum[i] <= prefixSum[q.back()]) {
            q.pop_back();
        }
        
        q.push_back(i);
    }
    
    cout << maxSum << endl;
    return 0;
}
