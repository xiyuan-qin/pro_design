#include<iostream>
#include<cmath>

using namespace std;

int fangcha(int *a , int n , int avg){
    int result = 0;
    for(int i = 0 ; i < n ; i++){
        result += (a[i] - avg) * (a[i] - avg);
    }
    return result;
}

int main(){
    int n;
    cin >> n;
    int *a = new int[n]();
    int avg_min = 0;
    for(int i = 0 ; i < n ; i++){
        cin >> a[i];
        avg_min += a[i];
    }
    
    avg_min = avg_min / n;
    int avg_max = avg_min + 1;

    int result_min = fangcha(a , n , avg_min);
    int result_max = fangcha(a , n , avg_max);

    cout << min(result_min , result_max) << endl;

    return 0;

}


