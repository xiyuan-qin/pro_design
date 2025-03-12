#include<iostream>
#include<vector>
#include<algorithm>
#include<iomanip> 
using namespace std;

int main(){
    int n , k;
    cin >> n >> k;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    double ans = 0;

    double l = 0.0 , r = *max_element(a.begin(), a.end());

    while(r - l > 1e-8){
        double mid = (l + r) / 2;
        int temp = 0;
        for(int i = 0 ; i < a.size() ; i++ ){
            temp += (int)(a[i] / mid); 
        }
        if(temp >= k){
            ans = mid;
            l = mid;
        }else{  
            r = mid;
        }
    }

    cout << fixed << setprecision(6) << ans << endl; 
    return 0;
}