#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main(){
    int n , k;
    cin >> n >> k;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    int ans = 0;

    int  l = 0 , r = *min_element(a.begin(), a.end());

    

    while(l <= r){
        int mid = (l + r) / 2;
        int temp = 0;
        for(int i = 0 ; i < a.size() ; i++ ){
            temp += a[i] / mid;
        }
        if(temp >= k){
            ans = mid;
            l = mid + 1;
        }else{  
            r = mid - 1;
        }

    }

    cout << ans << endl;
    return 0;

}