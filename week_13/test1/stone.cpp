#include<iostream>
#include<vector>
#include<climits>  

using namespace std;

int main(){
    int n;
    cin >> n;

    vector<int> a(2 * n);

    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    for(int i = n + 1; i < 2 * n; i++){
        a[i] = a[i - n];
    }
    for(int i = 1; i < 2 * n; i++){
        a[i] += a[i - 1];
    }

    vector<vector<int>> f(2*n, vector<int>(2*n, 1e9)), g(2*n, vector<int>(2*n, -1e9));
    for(int r = 1; r < 2 * n; r++){
        f[r][r] = g[r][r] = 0;
        for(int l = r - 1; l ; l--){
            for(int i = l; i < r; i++){
                f[l][r] = min(f[l][r], f[l][i] + f[i + 1][r] + a[r] - a[l - 1]);
                g[l][r] = max(g[l][r], g[l][i] + g[i + 1][r] + a[r] - a[l - 1]);
            }
        }
    }

    int ans[2] = {INT_MAX, INT_MIN};
    for(int i = 1; i <= n; i++){
        ans[0] = min(ans[0], f[i][i + n - 1]);
        ans[1] = max(ans[1], g[i][i + n - 1]);
    }
    cout << ans[0] << endl; 
    cout << ans[1] << endl;
    return 0;
}