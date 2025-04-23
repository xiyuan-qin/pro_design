#include <iostream>
#include <vector>
#include <algorithm>
#include <ios>

using namespace std;

class SegmentTree {
private:
    vector<int> tree;
    int n;
    
public:
    SegmentTree(int size) {
        n = size;
        tree.resize(4 * size, 0); 
    }
    
    // 更新单个位置的值
    void update(int idx, int val) {
        update(0, 0, n-1, idx, val);
    }
    
    // 查询区间[l,r]的最大值
    int query(int l, int r) {
        return query(0, 0, n-1, l, r);
    }
    
private:
    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] = val;
            return;
        }
        
        int mid = (start + end) / 2;
        if (idx <= mid)
            update(2*node+1, start, mid, idx, val);
        else
            update(2*node+2, mid+1, end, idx, val);
            
        tree[node] = max(tree[2*node+1], tree[2*node+2]);
    }
    
    int query(int node, int start, int end, int l, int r) {
        if (l > end || r < start)
            return 0; // 超出范围，返回不影响最大值的值
            
        if (l <= start && end <= r)
            return tree[node];
            
        int mid = (start + end) / 2;
        int left_max = query(2*node+1, start, mid, l, r);
        int right_max = query(2*node+2, mid+1, end, l, r);
        
        return max(left_max, right_max);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int m; long long p;
    cin >> m >> p;
    
    SegmentTree segTree(m);
    int pre = 0;
    int menu_size = 0;
    
    while (m--) {
        char option;
        cin >> option;
        
        if (option == 'Q') {
            int max_shown_num = 0;
            cin >> max_shown_num;
            
            int left = menu_size - max_shown_num;
            pre = segTree.query(left, menu_size - 1);
            cout << pre << '\n';
        } else {
            int num;
            cin >> num;
            int flavor = (num + pre) % p;
            
            segTree.update(menu_size, flavor);
            menu_size++;
        }
    }
    
    return 0;
}