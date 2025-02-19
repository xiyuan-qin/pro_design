#include<iostream>
using namespace std;

int main(){
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        int m ;
        int a = 0;
        cin>>m;
        int result = 0;
        for (int i = 0; i < m; i++){
            cin >> a;
            result += a;
        }
        cout << result << endl;
    }
    return 0;
}