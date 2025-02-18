#include<iostream>
#include<string>

using namespace std;

int main(){
    string str;
    cin >> str;
    char c = str[0];
    for(int i = 0 ; i < 3 ; i ++){
        if(str[i] != c){
            cout << "Lost" << endl;
            return 0;
        }
    }
    cout << "Won" << endl;
    return 0;   
}
