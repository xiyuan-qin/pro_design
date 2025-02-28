#include<iostream>
#include<vector>

using namespace std;

int main(){
    int n;
    cin>> n;
    vector<int> a(n);
    vector<int>::iterator it;
    vector<int> frequency(n ,0);

    for(int i = 0; i < n; i++){
        cin>> a[i];
        frequency[a[i]]++;
        cout<< frequency[a[i]]<< " ";
    }
    cout<< endl;
    return 0;
   

}