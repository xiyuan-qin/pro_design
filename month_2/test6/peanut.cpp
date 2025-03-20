#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>

using namespace std;

// 检查是否存在平均值大于等于mid的子数组，并返回最长的长度
pair<bool, int> check(vector<int>& nums, double mid) {
    int n = nums.size();
    vector<double> diff(n);
    for (int i = 0; i < n; i++) {
        diff[i] = nums[i] - mid;
    }
    
    vector<double> prefixSum(n + 1, 0);
    for (int i = 0; i < n; i++) {
        prefixSum[i+1] = prefixSum[i] + diff[i];
    }
    
    // 对于每个右端点j，找到最小的prefixSum[i]使得i<j
    double minPrefixSum = prefixSum[0];
    int minIndex = 0;
    bool found = false;
    int maxLen = 0;
    
    for (int j = 1; j <= n; j++) {
        // 如果从某个点i到j的子数组平均值大于等于mid
        if (prefixSum[j] - minPrefixSum >= 0) {
            found = true;
            // 找出这个i的位置，计算长度
            for (int i = minIndex; i < j; i++) {
                if (prefixSum[j] - prefixSum[i] >= 0) {
                    maxLen = max(maxLen, j - i);
                    break;
                }
            }
        }
        
        // 更新前缀和的最小值
        if (prefixSum[j] < minPrefixSum) {
            minPrefixSum = prefixSum[j];
            minIndex = j;
        }
    }
    
    return {found, maxLen};
}

int main() {
    long long n;
    cin >> n;  
    vector<int> nums(n);
    
    int minVal = INT_MAX;
    int maxVal = INT_MIN;
    
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        minVal = min(minVal, nums[i]);
        maxVal = max(maxVal, nums[i]);
    }
    
    // 二分搜索
    int left = minVal, right = maxVal;
    int finalAvg = 0;
    int finalLen = 0;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        auto [possible, len] = check(nums, mid);
        
        if (possible) {
            finalAvg = mid;
            finalLen = len;
            left = mid + 1; // 尝试更大的平均值
        } else {
            right = mid - 1; // 尝试更小的平均值
        }
    }
    
    cout << finalAvg << " " << finalLen << endl;
    return 0;
}