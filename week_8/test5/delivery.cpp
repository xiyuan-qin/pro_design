#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<climits>

using namespace std;

struct Edge {
    int to;        // 目标顶点
    int weight;    // 承重量
    int time;      // 通行时间
};

bool hasPathWithinTimeLimit(const vector<vector<Edge>>& graph, int n, int minWeight, int timeLimit) {
    vector<int> minTime(n + 1, INT_MAX);
    minTime[1] = 0;
    
    queue<int> q;
    q.push(1);
    
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        
        for (const Edge& edge : graph[current]) {
            // 只考虑承重量>=minWeight的边
            if (edge.weight >= minWeight) {
                int newTime = minTime[current] + edge.time;
                // 如果找到更短的路径且在时间限制内
                if (newTime < minTime[edge.to] && newTime <= timeLimit) {
                    minTime[edge.to] = newTime;
                    q.push(edge.to);
                }
            }
        }
    }
    
    return minTime[n] <= timeLimit;
}

int main() {
    int X;
    cin >> X;
    while (X--) {
        int n, m, time_limit;
        cin >> n >> m >> time_limit; 
        
        vector<vector<Edge>> graph(n + 1);
        int maxPossibleWeight = 0;
        
        for (int i = 0; i < m; i++) {
            int a, b, c, d;
            cin >> a >> b >> c >> d;
            graph[a].push_back({b, c, d});
            graph[b].push_back({a, c, d});
            maxPossibleWeight = max(maxPossibleWeight, c);
        }
        
        // 二分
        int left = 1, right = maxPossibleWeight;
        int result = 0;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (hasPathWithinTimeLimit(graph, n, mid, time_limit)) {
                // 可以承受更大重量
                result = mid;
                left = mid + 1;
            } else {
                // 不能承受这么大重量
                right = mid - 1;
            }
        }
        
        cout << result << endl;
    }
    return 0;
}