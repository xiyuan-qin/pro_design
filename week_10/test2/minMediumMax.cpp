#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> nums(n);
    
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    sort(nums.begin(), nums.end());
    
    int min_val = nums[0];
    int max_val = nums[n-1];
    

    double median;
    if (n % 2 == 1) {
        median = nums[n/2];
    } else {
        median = (nums[n/2-1] + nums[n/2]) / 2.0;
    }
    cout << max_val << " ";
    
    if (median == (int)median) {
        cout << (int)median;
    } else {
        cout << fixed << setprecision(1) << median;
    }
    
    cout << " " << min_val << endl;
    
    return 0;
}


