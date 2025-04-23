#include<iostream>
#include<cmath>
#include<vector>
#include<algorithm>

using namespace std;

class SegmentTree {
private:
    vector<int> d;
    vector<int> a;
    vector<int> b;
    int n;

    void build(int s, int t, int p) {
        if (s == t) {
            d[p] = a[s];
            return;
        }
        int m = s + ((t - s) >> 1);
        build(s, m, p * 2), build(m + 1, t, p * 2 + 1);
        d[p] = d[p * 2] + d[(p * 2) + 1];
    }

    int getsum(int l, int r, int s, int t, int p) {
        if (l <= s && t <= r)
            return d[p];
        int m = s + ((t - s) >> 1), sum = 0;
        
        if (b[p]) {
            d[p * 2] += b[p] * (m - s + 1);
            d[p * 2 + 1] += b[p] * (t - m);
            b[p * 2] += b[p];
            b[p * 2 + 1] += b[p];
            b[p] = 0;
        }
        
        if (l <= m) sum += getsum(l, r, s, m, p * 2);
        if (r > m) sum += getsum(l, r, m + 1, t, p * 2 + 1);
        return sum;
    }

    void update(int l, int r, int c, int s, int t, int p) {
        if (l <= s && t <= r) {
            d[p] += (t - s + 1) * c;
            b[p] += c;
            return;
        }
        int m = s + ((t - s) >> 1);
        
        if (b[p] && s != t) {
            d[p * 2] += b[p] * (m - s + 1);
            d[p * 2 + 1] += b[p] * (t - m);
            b[p * 2] += b[p];
            b[p * 2 + 1] += b[p];
            b[p] = 0;
        }
        
        if (l <= m) update(l, r, c, s, m, p * 2);
        if (r > m) update(l, r, c, m + 1, t, p * 2 + 1);
        d[p] = d[p * 2] + d[p * 2 + 1];
    }
    
public:
    SegmentTree(const vector<int>& arr) {
        a = arr;
        n = arr.size();
        d.resize(4 * n);
        b.resize(4 * n);
        build(0, n - 1, 1);
    }
    
    int query(int l, int r) {
        return getsum(l, r, 0, n - 1, 1);
    }
    
    void modify(int l, int r, int val) {
        update(l, r, val, 0, n - 1, 1);
    }
};