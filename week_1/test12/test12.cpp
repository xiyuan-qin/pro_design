#include<iostream>
using namespace std;

int main(){
    int n;
    while(cin>>n){
        int a ;
        if (n == 0){
            break;
        }
        int result = 0;
        for (int i = 0; i < n; i++){
            cin >> a;
            result += a;
        }
        cout << result << endl;
    }
    return 0;
}