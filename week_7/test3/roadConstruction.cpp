#include<iostream>
#include<vector>

using namespace std;

// 并查集实现
class UnionFind {
private:
    vector<int> parent;
    int count; // 连通分量数量
    
public:
    UnionFind(int n) {
        parent.resize(n + 1);
        for (int i = 1; i <= n; i++) {
            parent[i] = i;
        }
        count = n;
    }
  
    int find(int x) {
        // 找到根节点
        int root = x;
        while (parent[root] != root) {
            root = parent[root];
        }
        
 
        while (x != root) {
            int next = parent[x];
            parent[x] = root;
            x = next;
        }
        
        return root;
    }
    
    // 返回是否成功合并（之前未连通返回true）
    bool unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX == rootY) {
            return false; // 已经连通
        }
        
        parent[rootX] = rootY;
        count--;
        return true;
    }
    
    // 获取还需要的路径数
    int getRemainingRoads() {
        return count - 1;
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    
    UnionFind uf(n);
    
    while (m--) {
        int a, b;
        cin >> a >> b;
        
        // 尝试连接两个村庄
        uf.unite(a, b);
        
        // 输出还需要建设的道路数量
        cout << uf.getRemainingRoads() << endl;
    }
    
    return 0;
}