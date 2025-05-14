#include<iostream>
#include<vector>
#include<string>

using namespace std;

int main(){
    string s;
    cin >> s;
    int n = s.length();

    s = " " + s; 

    vector<vector<int>> f(n + 2, vector<int>(n + 2, 1e9));
    for(int r = 1; r <= n; r++){
        f[r][r] = 1;
        f[r + 1][r] = 0;

        for(int l = r - 1; l ; l--){
            if(s[l] == '(' && s[r] == ')' || s[l] == '[' && s[r] == ']'){
                f[l][r] = min(f[l][r], f[l + 1][r - 1]);
            }
            for(int i = l; i < r; i++){
                f[l][r] = min(f[l][r], f[l][i] + f[i + 1][r]);
            }
        }
    }

    cout << f[1][n] << endl;
    return 0;
}