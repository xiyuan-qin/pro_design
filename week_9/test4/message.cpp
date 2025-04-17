#include<iostream>
#include<vector>
#include<algorithm>
#include<stack>

using namespace std;

vector<vector<int>> graph;
vector<int> dfn, low, scc_id, indegree_scc;
vector<bool> in_stack;
stack<int> stk;
int idx = 0, scc_cnt = 0;

void tarjan(int u) {
    dfn[u] = low[u] = ++idx;
    stk.push(u);
    in_stack[u] = true;
    for (int v : graph[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (in_stack[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {
        ++scc_cnt;
        int x;
        do {
            x = stk.top(); stk.pop();
            in_stack[x] = false;
            scc_id[x] = scc_cnt;
        } while (x != u);
    }
}

int main(){
    int n, m;
    cin >> n >> m;
    graph.assign(n + 1, vector<int>());
    dfn.assign(n + 1, 0);
    low.assign(n + 1, 0);
    scc_id.assign(n + 1, 0);
    in_stack.assign(n + 1, false);
    for(int i = 0; i < m; ++i){
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
    }
    for(int i = 1; i <= n; ++i){
        if(!dfn[i]) tarjan(i);
    }
    indegree_scc.assign(scc_cnt + 1, 0);
    for(int u = 1; u <= n; ++u){
        for(int v : graph[u]){
            if(scc_id[u] != scc_id[v]){
                indegree_scc[scc_id[v]]++;
            }
        }
    }
    int ans = 0;
    for(int i = 1; i <= scc_cnt; ++i){
        if(indegree_scc[i] == 0) ans++;
    }
    cout << ans << endl;
    return 0;
}