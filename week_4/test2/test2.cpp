#include<iostream>
#include<algorithm>

using namespace std;

long long totalPrints(long long t, int x, int y) {
    if (t < min(x, y))
        return 0;
    
    long long firstCopyTime = min(x, y);
    long long remainingTime = t - firstCopyTime;
    long long additionalCopies = (remainingTime / x) + (remainingTime / y);
    

    return 1 + additionalCopies;
}

int main(){
    int n, x, y;
    cin >> n >> x >> y;
    
    long long left = 0, right = (long long)n * max(x, y);
    while (left < right) {
        long long mid = left + (right - left) / 2;
        if (totalPrints(mid, x, y) < n) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    cout << left << endl;
    return 0;
}