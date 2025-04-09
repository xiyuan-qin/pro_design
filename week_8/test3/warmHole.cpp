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
        // 读入普通道路（双向）
        for(int i = 0; i < m; i++) {
            int s, e, t;
            cin >> s >> e >> t;
            edges.push_back({s, e, t});
            edges.push_back({e, s, t}); // 双向边
        }
        
        // 读入虫洞（单向，时间为负）
        for(int i = 0; i < w; i++) {
            int s, e, t;
            cin >> s >> e >> t;
            edges.push_back({s, e, -t}); // 注意虫洞是负权边
        }
        
        // 判断是否存在负环
        bool hasNegativeCycle = false;
        
        // 初始化距离
        vector<int> dist(n + 1, 0);  // 所有点初始化为0，因为我们只关心是否存在负环
        
        // Bellman-Ford算法的n次迭代
        for(int i = 0; i < n; i++) {
            for(const auto& edge : edges) {
                if(dist[edge.from] != INT_MAX && 
                   dist[edge.from] + edge.weight < dist[edge.to]) {
                    dist[edge.to] = dist[edge.from] + edge.weight;
                }
            }
        }
        
        // 额外进行一次松弛操作，如果还能更新，说明存在负环
        for(const auto& edge : edges) {
            if(dist[edge.from] != INT_MAX && 
               dist[edge.from] + edge.weight < dist[edge.to]) {
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