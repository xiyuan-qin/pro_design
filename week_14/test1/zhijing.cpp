#include <iostream>
#include <vector>
#include <utility>          
#include <algorithm>

using namespace std;
using PathInfo = pair<int, long long>;

PathInfo dfs(int u, int p,
             const vector<vector<int>>& adj,
             int& diameter_len,
             long long& diameter_count) {

    int max1_len = 0;
    long long max1_cnt = 1;

    int max2_len = 0;
    long long max2_cnt = 0;

    for (int v : adj[u]) {
        if (v == p) { 
            continue;
        }

        PathInfo child_path_info = dfs(v, u, adj, diameter_len, diameter_count);
        int child_subtree_len = child_path_info.first;
        long long child_subtree_cnt = child_path_info.second;

        int len_via_v = child_subtree_len + 1;
        long long cnt_via_v = child_subtree_cnt;

        if (max1_len > 0) {
            int current_path_len_thru_u = max1_len + len_via_v;
            long long current_path_count_thru_u = max1_cnt * cnt_via_v;

            if (current_path_len_thru_u > diameter_len) {
                diameter_len = current_path_len_thru_u;
                diameter_count = current_path_count_thru_u;
            } else if (current_path_len_thru_u == diameter_len) {
                diameter_count += current_path_count_thru_u;
            }
        }

        if (len_via_v > max1_len) {
            max2_len = max1_len;
            max2_cnt = max1_cnt;
            max1_len = len_via_v;
            max1_cnt = cnt_via_v;
        } else if (len_via_v == max1_len) {
            max1_cnt += cnt_via_v;
        } else if (len_via_v > max2_len) {
            max2_len = len_via_v;
            max2_cnt = cnt_via_v;
        } else if (len_via_v == max2_len) {
            max2_cnt += cnt_via_v;
        }
    }

   
    if (max1_len > diameter_len) {
        diameter_len = max1_len;
        diameter_count = max1_cnt;
    } else if (max1_len == diameter_len) {
        diameter_count += max1_cnt;
    }

    return PathInfo(max1_len, max1_cnt);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    if (n == 0) {
        cout << 0 << " " << 0 << endl;
        return 0;
    }

    vector<vector<int>> adj(n + 1);
    if (n > 1) {
        for (int i = 0; i < n - 1; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }

    int diameter_len = 0;
    long long diameter_count = 0; 

    dfs(1, 0, adj, diameter_len, diameter_count);

    cout << diameter_len << " " << diameter_count << endl;

    return 0;
}