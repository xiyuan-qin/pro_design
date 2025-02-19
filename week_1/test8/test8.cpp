#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

int g1(int x){
    string numStr = to_string(x);
    sort(numStr.begin(), numStr.end(), greater<char>());
    return stoi(numStr);
}

int g2(int x){
    string numStr = to_string(x);
    sort(numStr.begin(), numStr.end());
    return stoi(numStr);
}

int f(int x){
    return g1(x) - g2(x);
}


int main(){
    int n , k;
    cin>>n>>k;

   for(int i = 0 ; i < k ; i++){
        n = f(n);
    }

    cout<<n<<endl;

    return 0;
}