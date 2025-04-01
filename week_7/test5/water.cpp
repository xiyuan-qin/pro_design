#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class  Edge {
public:
    Edge(int u, int v, int cost) : u(u), v(v), cost(cost) {}
    int u, v, cost;
    bool operator<(const Edge& other) const {
        return cost < other.cost;
    }
};

class UnionFind {
private:
    vector<int> parent, rank;
public:
    UnionFind(int n) {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
        }
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    bool unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        
        if (rootX == rootY) return false;
        
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else {
            parent[rootY] = rootX;
            if (rank[rootX] == rank[rootY]) {
                rank[rootX]++;
            }
        }
        return true;
    }
};

int main() {
    int n, m, p;
    cin >> n >> m >> p;
    
    vector<Edge> edges;
    
    // 添加原有的水渠边
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        edges.emplace_back(a, b, c);
    }
    
    // 添加超级节点到每个田地的边，表示抽水机
    for (int i = 1; i <= n; i++) {
        edges.emplace_back(0, i, p);
    }
    
    // 按成本排序边
    sort(edges.begin(), edges.end());
    
    // Kruskal算法求最小生成树
    UnionFind uf(n);
    long long total_cost = 0;
    
    for (auto e : edges) {
        if (uf.unite(e.u, e.v)) {
            total_cost += e.cost;
        }
    }
    
    cout << total_cost << endl;
    
    return 0;
}