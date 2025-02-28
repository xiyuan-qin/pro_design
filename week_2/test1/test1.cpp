#include<iostream>
#include<vector>
using namespace std;

int main(){
    int n;
    cin>> n;
    vector<int> a(n);
    vector<int>::iterator it;
    vector<int>::iterator it2;

    int res = 0;
    for(it = a.begin(); it != a.end(); it++){
        cin>> *it;
    }
    for(it = a.begin(); it != a.end(); it++){
        for(it2 = it + 1; it2 != a.end(); it2++){
            if(*it - *it2 == 1 || *it - *it2 == -1){
                res++;
            }
        }
    }
    cout<< res<< endl;
    return 0;

}