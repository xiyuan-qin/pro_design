#include<iostream>
#include<vector>
#include<string>

using namespace std;

void process(string& S){
    string s;
    for(int i = 0 ; i < S.size() ; i++){
        if(S[i] == '1'){
            s += '0';
        }else{
            s += '1';
        }
    }
    S += s;
}

int main(){
    int n;
    cin >> n;
    string t;  
    cin >> t;
    
    string s = "01";  
    
    while(s.size() < n){  
        process(s);
    }
    
    s = s.substr(0, n);  
    
    int count = 0;
    for(int i = 0 ; i <= n - t.size(); i++){
        string tem = s.substr(i, t.size());
        if(tem == t){
            count++;
        }
    }
    
    cout << count << endl;
    return 0;
}