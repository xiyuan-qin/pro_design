#include<iostream>
#include<vector>

using namespace std;

long long NUM = 998244353;

int main(){
    int n, m, k;
    cin >> n >> m >> k;

    vector<long long> f(n + 1, 0);
    vector<bool> is_unsafe(n + 1, false);
    
    for(int i = 0; i < m; i++){
        int pos;
        cin >> pos;
        is_unsafe[pos] = true;
    }

    f[0] = 1; // 起点
    
    vector<long long> preSum(n + 2, 0); 
    preSum[1] = f[0]; 
    
    for(int j = 1; j <= n; j++){
        if(!is_unsafe[j]) {
            int start = max(0, j - k);
            f[j] = (preSum[j] - preSum[start] + NUM) % NUM;
        }
     
        preSum[j+1] = (preSum[j] + f[j]) % NUM;
    }

    cout << f[n] << endl;
    return 0;
}