#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;
using ll = long long;


vector<ll> dijkstra(int src, int n, const vector<vector<pair<int, ll>>>& graph) {
    vector<ll> dist(n + 1, 1e18);
    dist[src] = 0;
    
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    pq.push({0, src});// {dist[v], v}，到顶点v的最短距离和v
    
    while(!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        
        if(d > dist[u]) continue; // 跳过已经有更好路径的节点
        
        for(auto [v, w] : graph[u]) {
            if(dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});  
            }
        }
    }
    
    return dist;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    while(T--){
        int n, m;
        cin >> n >> m;
        
        // 使用邻接表表示图，提高效率
        vector<vector<pair<int, ll>>> forward_graph(n + 1);
        vector<vector<pair<int, ll>>> backward_graph(n + 1);
        
        for(int i = 0; i < m; i++){
            int u, v;
            ll w;
            cin >> u >> v >> w;
            forward_graph[u].push_back({v, w});  // 原图
            backward_graph[v].push_back({u, w}); // 反图
        }
        
        // 计算从1到各点的最短路径
        vector<ll> to_dist = dijkstra(1, n, forward_graph);
        
        // 计算从各点到1的最短路径
        vector<ll> from_dist = dijkstra(1, n, backward_graph);
        
        ll total_cost = 0;
        for(int i = 2; i <= n; i++){  // 1是始发站
            if(to_dist[i] != 1e18 && from_dist[i] != 1e18){
                total_cost += (to_dist[i] + from_dist[i]);
            }
        }
        
        cout << total_cost << endl;
    }
    
    return 0;
}
