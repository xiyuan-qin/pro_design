#include<iostream>
using namespace std;

int main(){
    int n ;
    cin>>n;
    int *a = new int[n]();
    int *b = new int[n]();
    for(int i = 0 ; i < n ; i++){
        cin >> a[i];
    }
    for(int i = 0 ; i < n ; i++){
        cin >> b[i];
    }
    
    int result = 0;

    for(int i = 0 ; i < n ; i++){
        result += a[i] * b[i];
    }

    if(result == 0){
        cout << "Yes" << endl;
    }
    else{
        cout << "No" << endl;
    }
    return 0;
}