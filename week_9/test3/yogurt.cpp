#include <iostream>
#include <vector>
#include <queue>
#include <limits> 

using ll = long long; 

const ll INF = 1e18; 

class Edge {
public:
    int to;
    int weight;

    Edge(int to, int cost): to(to), weight(cost) {}
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    int m;
    std::cin >> n >> m;

    std::vector<std::vector<Edge>> adj(n + 1);

    for (int i = 1; i <= n; ++i) {
        adj[i - 1].emplace_back(i, 1);
        adj[i].emplace_back(i - 1, 0);
    }

    for (int i = 0; i < m; ++i) {
        int k, a, b, c;
        std::cin >> k >> a >> b >> c;
        
        int u_node = a - 1;
        int v_node = b;

        if (k == 1) { 
            adj[u_node].emplace_back(v_node, c);
        } else if (k == 2) { 
            adj[v_node].emplace_back(u_node, -c);
        } else if (k == 3) { 
            adj[u_node].emplace_back(v_node, c - 1);
        } else if (k == 4) { 
            adj[v_node].emplace_back(u_node, -(c + 1));
        } else if (k == 5) { 
            adj[u_node].emplace_back(v_node, c);
            adj[v_node].emplace_back(u_node, -c);
        }
    }

    std::vector<ll> dist(n + 1, INF);
    std::vector<int> cnt(n + 1, 0);
    std::vector<bool> in_queue(n + 1, false);
    std::queue<int> q;

    dist[0] = 0;
    q.emplace(0);
    in_queue[0] = true;
    cnt[0] = 1;

    bool possible = true;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        in_queue[u] = false;

        for (const auto& edge : adj[u]) {
            int v = edge.to;
            int weight = edge.weight;
            
            if (dist[u] != INF && dist[v] > dist[u] + weight) { 
                dist[v] = dist[u] + weight;
                
                if (!in_queue[v]) { 
                    q.emplace(v);
                    in_queue[v] = true;
                    cnt[v]++;
                    
                    if (cnt[v] > n) { 
                        possible = false;
                        goto end_spfa;
                    }
                }
            }
        }
    }

end_spfa:

    if (!possible) {
        std::cout << "impossible" << std::endl;
    } else {
        if (dist[n] == INF) {
           std::cout << "impossible" << std::endl; 
        } else {
           std::cout << dist[n] << std::endl;
        }
    }

    return 0;
}