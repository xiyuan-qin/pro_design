#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>

using namespace std;

class BinaryIndexedTree {
private:
    vector<long long> BIT; 
    int n;

    int lowbit(int x) {
        return x & (-x);
    }

public:
    BinaryIndexedTree(int size) : n(size) {
        BIT.resize(size + 1, 0);
    }

    void build(const vector<int>& A) {
        // 直接初始化BIT数组
        for (int i = 0; i < n; i++) {
            add(i+1, A[i]);
        }
    }

    void add(int i, int delta) {
        for (int j = i; j <= n; j += lowbit(j))
            BIT[j] += delta;
    }

    long long sum(int k) {  
        long long ans = 0;  
        for (int i = k; i > 0; i -= lowbit(i))
            ans += BIT[i];
        return ans;
    }

    long long rangeSum(int left, int right) {  
        return sum(right) - sum(left - 1);
    }
};

int main(){
    int n, q;
    cin >> n >> q;
    vector<int> A(n);

    for(int i = 0; i < n; i++){
        cin >> A[i];
    }
    BinaryIndexedTree BIT(n);
    BIT.build(A);
    while(q--){
        int opt;
        cin >> opt;
        if(opt == 1){
            int i, delta;
            cin >> i >> delta;
            A[i-1] += delta; 
            BIT.add(i, delta);
        } else if(opt == 2){
            int l, r;
            cin >> l >> r;
            cout << BIT.rangeSum(l, r) << endl;
        }
    }
    return 0;
}