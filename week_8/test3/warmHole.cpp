#include<iostream>
#include<vector>
#include<map>
#include<climits>

using namespace std;

class Edge {
public:
    int from, to, weight;
};

int main(){
    int F;
    cin >> F;
    while(F--){
        int n, m, w;
        cin >> n >> m >> w;
        
        // 存储所有边
        vector<Edge> edges;
        for(int i = 0; i < m; i++) {
            int s, e, t;
            cin >> s >> e >> t;
            edges.push_back({s, e, t});
            edges.push_back({e, s, t}); // 双向边
        }
        
        for(int i = 0; i < w; i++) {
            int s, e, t;
            cin >> s >> e >> t;
            edges.push_back({s, e, -t}); // 虫洞是负权边
        }
        
        bool hasNegativeCycle = false;
        
        // 初始化距离
        vector<int> dist(n + 1, 0);  
        
        for(int i = 0; i < n; i++) {
            for(const auto& edge : edges) {
                int u = edge.from;
                int v = edge.to;
                int w = edge.weight;
                if(dist[u] != INT_MAX) {
                    dist[v] = min(dist[v], dist[u] + w);
                }
            }
        }
        
        for(const auto& edge : edges) {
            int u = edge.from;
            int v = edge.to;
            int w = edge.weight;
            if(dist[u] != INT_MAX && 
               dist[u] + w < dist[v]) {
                hasNegativeCycle = true;
                break;
            }
        }
        
        if(hasNegativeCycle) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}