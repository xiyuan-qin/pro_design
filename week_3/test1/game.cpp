#include<iostream>
#include<vector>

using namespace std;

int main(){
    int n , k;
    cin>> n >> k;
    int num = n;
    vector<int> exsit(n, 0);//0 表示还存在游戏中
    int count = 0;
    int index = 0;
    while(true){
        if(exsit[index] == 1){
            index = (index + 1) % num;
            continue;
        }
        count++;
        if(count % k == 0 || count % 10 == k){
            exsit[index] = 1;// 1 表示已经退出游戏
            n--;
        }
        if(n == 1){
            break;
        }
        index = (index + 1) % num;//  表示第index个人进行游戏
    }
    for(int i = 0; i < exsit.size(); i++){
        if(exsit[i] == 0){
            cout<< i + 1 << endl;
            break;
        }
    }
    return 0;
}