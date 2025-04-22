#include<iostream>
#include<vector>

using namespace std;

/**
 * 每一场战斗，勇士需要消耗 max(y−x,0) 生命值打倒敌人
 * x为勇士在本场战斗开始前的战力值
 * y为敌人的战力值
 * 战斗后勇士的战力值变为 max(x,y)，为0则勇士死亡
 */

int main(){
    int n;
    cin >> n; 
    vector<long long> enemies(n);

    long long hp, power; 
    cin >> hp >> power;
    for(int i = 0; i < n; ++i) {
        cin >> enemies[i];
    }
    for(int i = 0; i < n; i++){
        long long damage = max(enemies[i] - power, 0LL);
        hp -= damage;
        if(hp <= 0){
            cout << "NO" << endl << i << endl;
            return 0;
        }
        power = max(power, enemies[i]);
    }
    cout << "YES" << endl << hp << endl;
    return 0;
}