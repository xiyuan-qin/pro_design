#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>

using namespace std;

class BinaryIndexedTree {
private:
    vector<int> BIT;
    int n;

    int lowbit(int x) {
        return x & (-x);
    }

public:
    BinaryIndexedTree(int size) : n(size) {
        BIT.resize(size + 1, 0);
    }

    void build(const vector<int>& A) {
        fill(BIT.begin(), BIT.end(), 0);
        
        for (int i = 1; i <= n; i++) {
            BIT[i] += A[i - 1];
            int j = i + lowbit(i);
            if (j <= n) { 
                BIT[j] += BIT[i];
            }
        }
    }

    void edit(int i, int delta) {
        for (int j = i; j <= n; j += lowbit(j))
            BIT[j] += delta;
    }

    int sum(int k) {
        int ans = 0;
        for (int i = k; i > 0; i -= lowbit(i))
            ans += BIT[i];
        return ans;
    }

    int rangeSum(int left, int right) {
        return sum(right) - sum(left - 1);
    }
};