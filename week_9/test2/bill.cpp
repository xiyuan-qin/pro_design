#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int main(){
    int n, m;
    cin >> n >> m;// n个同学，学号从1到n

    vector<vector<int>> graph(n + 1);
    vector<int> in(n + 1, 0);// 每个节点的入度

    while(m--){
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b); // a比b好，a指向b
        in[b]++; // b的入度加1
    }

    vector<int> ans;
    priority_queue<int, vector<int>, greater<int>> q;
    
    // 首先将所有入度为0的节点入队
    for(int i = 1; i <= n; i++){
        if(in[i] == 0){
            q.push(i);
        }
    }
    
    // 执行拓扑排序
    while(!q.empty()){
        int curr = q.top();
        q.pop();
        ans.push_back(curr);
        
        // 遍历当前节点的所有邻居
        for(int next : graph[curr]){
            in[next]--;
            if(in[next] == 0){
                q.push(next);
            }
        }
    }

    for(auto x : ans){
        cout << x << " ";
    }
    cout << endl;
    return 0;
}