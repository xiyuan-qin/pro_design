#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 1e5 + 5;
vector<int> tree[MAXN];
int max_depth[MAXN][2]; 
int result[MAXN];       


void dfs1(int u, int fa) {
    max_depth[u][0] = max_depth[u][1] = 0;
    
    for (int v : tree[u]) {
        if (v == fa) continue;
        dfs1(v, u);
        int curr_depth = max_depth[v][0] + 1;
        if (curr_depth > max_depth[u][0]) {
            max_depth[u][1] = max_depth[u][0];
            max_depth[u][0] = curr_depth;
        } else if (curr_depth > max_depth[u][1]) {
            max_depth[u][1] = curr_depth;
        }
    }
}


void dfs2(int u, int fa, int from_parent) {
    result[u] = max(max_depth[u][0], from_parent);
    
    for (int v : tree[u]) {
        if (v == fa) continue;
        
        int new_from_parent;
        if (max_depth[v][0] + 1 == max_depth[u][0]) {
            new_from_parent = max(max_depth[u][1] + 1, from_parent + 1);
        } else {
            new_from_parent = max(max_depth[u][0] + 1, from_parent + 1);
        }
        dfs2(v, u, new_from_parent);
    }
}

int main() {
    int n;
    cin >> n;
    
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        if(a >= 1 && a <= n && b >= 1 && b <= n) {
            tree[a].push_back(b);
            tree[b].push_back(a);
        }
    }
    
    dfs1(1, 0); 
    dfs2(1, 0, 0);
    
    for (int i = 1; i <= n; i++) {
        cout << result[i] << " ";
    }
    cout << endl;
    
    return 0;
}