#include <iostream>
#include <vector>
#include <tuple>
#include <iomanip>

using namespace std;

bool hasCycle(int n, const vector<tuple<int,int,int,int>>& edges, double mid) {
   
    vector<double> dist(n+1, 0.0);
    
    
    for (int i = 0; i < n; ++i) {
        bool updated = false;
        
        for (const auto &e : edges) {
            int u, v, p, v_val;
            tie(u, v, p, v_val) = e;  
            
            
            double w = p - mid * v_val;
            
            
            if (dist[u] + w > dist[v]) {
                dist[v] = dist[u] + w;
                updated = true;
            }
        }
        
        
        if (!updated) break;
    }
    
    
    for (const auto &e : edges) {
        int u, v, p, v_val;
        tie(u, v, p, v_val) = e;
        double w = p - mid * v_val;
        
        if (dist[u] + w > dist[v] + 1e-9) { 
            return true; 
        }
    }
    
    return false; 
}


int main() {
    int n, m;
    cin >> n >> m;
    vector<tuple<int,int,int,int>> edges;
    
    for (int i = 0; i < m; ++i) {
        int u, v, p, v_val;
        cin >> u >> v >> p >> v_val;  
        edges.emplace_back(u, v, p, v_val);
    }
    
    double left = 0.0, right = 2000.0; 
    
    // 二分查找最大比值
    while (right - left > 1e-6) {  
        double mid = (left + right) / 2;
        if (hasCycle(n, edges, mid)) {
            left = mid;
        } else {
            right = mid;  
        }
    }
    
    cout << fixed << setprecision(1) << left << endl;
    return 0;
}