#include<iostream>
#include<cctype>
#include<string>

using namespace std;

int main(){
    string str;
    cin >> str;

    for(int i = 0 ; i < str.size() ; i++){
       if((i + 1) % 2 == 0){// 偶数位置
            if(islower(str[i])){
                cout<< "No" << endl;
                return 0;
            }    
       }
       else{// 奇数位置
            if(isupper(str[i])){
                cout<< "No" << endl;
                return 0;
            }
       }
    }
    
    cout << "Yes" << endl;
    
    return 0;
}