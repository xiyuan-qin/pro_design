#include<iostream>
#include<vector>

using namespace std;

int main(){
    vector<int> status;
    int n;
    int prev = 1;// 上一次得分至少为1
    while(cin>>n){
        if(n != 0){
            status.push_back(n);
        }
        else{
            status.push_back(n);// 把最后一个0压进去
            break;
        }
    }

    int score = 0;
    vector<int>::iterator it = status.begin();
    for(it = status.begin(); *it != 0 ; it++){
        if(*it == 1){
            score += 1;
            prev = 1;
        }
        else{//在跳到了中心的情况下
            if(it == status.begin() || prev == 1){
                score += 2;
                prev = 2;
            }
            else{
                score += 2 + prev;
                prev += 2;
            }
        }
    }
    cout<< score << endl;
    return 0;
}