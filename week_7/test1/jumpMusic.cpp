#include<iostream>
#include<string>
#include<vector>
#include<map>

using namespace std;

enum yuanyin {a , e , i , o , u };

int main(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    
    int result = 0;
    int start = 0;
    for (int i = 0; i < n; i++){
        if(s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u'){
            if(i + 1 - start > result){
                result = i + 1 - start;
            }
        }
        else{
            start = i + 1;
        }
       
    }

    cout << result << endl;
    return 0;
}