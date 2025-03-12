#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

int main(){
    int  n ;long long K;
    cin >> n >> K;
    vector<long long > num(n);
    
    for(long long  i = 0; i < n; i++){
        cin >> num[i];
    }
    sort(num.begin(), num.end());

    long  frequency = 0;  
    int i = 0;

    while(i < n - 1){
        if(num[i] != -1 && num[i + 1] != -1 && abs(num[i] - num[i + 1]) <= K){
            frequency++;
            num[i] = -1;
            i++;
        }
        else{
            i++;
        }
    }
    
    cout << frequency << endl;
    return 0;

}