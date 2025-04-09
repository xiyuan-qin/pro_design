#include<iostream>
#include<vector>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> price(n);
    for(int i = 0; i < n; i++){
        cin >> price[i];
    }

    vector<int> nextDay(n);

    for(int i = 0; i < n; i++){
        if(i == 0){
            nextDay[i] = (price[i] + price[i + 1]) / 2 ;
        }
        else if(i == n - 1){
            nextDay[i] = (price[i] + price[i - 1]) / 2 ;
        }
        else{
            nextDay[i] = (price[i] + price[i - 1] + price[i + 1]) / 3 ;
        }
    }

    for(auto x : nextDay){
        cout << x << " ";
    }
    cout << endl;

    return 0;
}