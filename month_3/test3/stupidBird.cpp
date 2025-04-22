#include<iostream>
#include<vector>
#include<string>

using namespace std;

/**
 * 如果本轮最终跳票总人数或投除 ycs 以外其他人出局的总人数二者中任意一项大于等于投 ycs 出局的人数，ycs 本轮不会出局，反之则 ycs 一定出局。
 * 也就是说 ycs 本轮出局的条件是：
 * 1.本轮最终跳票总人数 < 投 ycs 出局的人数 && 
 * 2.投除 ycs 以外其他人出局的总人数 < 投 ycs 出局的人数
 * 如果一定出局，输出“Bingo”
 * 不出局，输出“gugugu...”
 */


int main(){
    int x , y , z;
    cin >> x >> y >> z; //x:本轮打算投他出局的人数
                        //y:本轮目前投除 ycs 以外的其他某个人出局的人数
                        //z:本轮目前打算选择跳过投票的人数。

    if(z < x && y < x){
        cout << "Bingo" << endl;
    }else{  
        cout << "gugugu..." << endl;
    }
    return 0;
}       