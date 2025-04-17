#include<iostream>
#include<vector>
#include<algorithm> 

using namespace std;

bool check(vector<bool>& visited){
    for(auto x : visited){
        if(!x) return false;
    }
    return true;
}

class UnionFind{
public:
    vector<int> parent;
    vector<int> rank;

    UnionFind(int n){
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        for(int i = 0; i <= n; i++){
            parent[i] = i;
        }
    }

    int find(int x){
        if(parent[x] != x){
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void Union(int x, int y){
        int rootX = find(x);
        int rootY = find(y);
        if(rootX != rootY){
            if(rank[rootX] > rank[rootY]){
                parent[rootY] = rootX;
            } else if(rank[rootX] < rank[rootY]){
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

int main(){
    int n , m ;// n个节点，m个边
    cin >> n >> m;

    vector<vector<int>> graph(n + 1);// 邻接表
    vector<bool> visited(n + 1, false);// 访问标记
    vector<int> result;// 结果数组
    UnionFind uf(n + 1);// 并查集

    while(m--){
        int a, b;
        cin >> a >> b;
        // graph[a].push_back(b); // a一定会告诉b
        uf.Union(a, b); // a和b在同一个集合中
    }


    for(int i = 1; i <= n + 1; i++){
        if(find(result.begin(), result.end(), uf.find(i)) == result.end()){
            result.push_back(uf.find(i));
        }
    }

    cout<< result.size() << endl;
    return 0;
}