#include<iostream>
#include<string>
#include<vector>
#include<cstring>

using namespace std;

int main(){
    string s;
    cin >> s;
    int n = s.size();
    int f[n][n];

    memset(f, 0x80, sizeof(f));

    for(int i = 1; i < n; i++){
        f[i][i - 1] = 0;
    }
    for(int i = 0; i < n; i++){
        f[i][i] = 1;
        for(int j = i - 1 ; ~j; j--){
            f[j][i] = max(f[j + 1][i], f[j][i - 1]);
            if(s[i] == s[j]){
                f[j][i] = max(f[j][i], f[j + 1][i - 1] + 2);
            }
        }
    }

    cout << f[0][n - 1] << endl;
    return 0;
}