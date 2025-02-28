#include<iostream>
#include<vector>
#include<set>
#include<algorithm>
#include<string>

using namespace std;

int main(){
    set<string> s;
    int m;
    cin>> m;
    for(int i = 0; i < m; i++){
        int opt; string word;
        cin>> opt;
        switch(opt){
            case 1:
                cin>> word;
                if(s.find(word) != s.end()){
                    cout<< "found"<< endl;
                }else{
                    cout<< "write"<< endl;
                    s.insert(word);
                }
                break;
            case 2:
                cin>> word;
                if(s.find(word) != s.end()){
                    cout<< "erased"<< endl;
                    s.erase(word);
                }else{
                    cout<< "not found"<< endl;
                }
                break;
            case 3:
                set<string>::iterator it;
                for(it = s.begin(); it != s.end(); it++){
                    cout<< *it<< " ";
                }
                cout<< endl;
                break;
        }
    }
    return 0;
}