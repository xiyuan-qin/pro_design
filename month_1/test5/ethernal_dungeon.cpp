#include<iostream>

using namespace std;

/**
 * 强化射击：每第7次
 * 存在多次强化射击的可能
 * 在第一轮就解决，怪物的总血量必须是：9（6次普攻后一次强化）
 * 第二轮：9+6+3=18（上一次打掉的总血量+这一次打掉的）
 * 同时还要保证必须经过强化射击之后全部第一次变为0，即要注意强化射击如果没有打掉，所有怪物的血量都不能为0
 * 所以判断时必须保证：在第n次强化射击完美通关时，每只怪物的血量都要 >= n
 * 
 */

int main(){
    int levels;
    cin >> levels;
    int monsters[levels][3];

    for(int i = 0; i < levels; i++){
        for(int j = 0; j < 3; j++){
            cin >> monsters[i][j];//第i层第j个怪物的血量
        }
    }

    for(int i = 0; i < levels; i++){//打第i层的怪物
        int sum = 0;
        for(int j = 0; j < 3; j++){//计算第i层的怪物总血量
            sum += monsters[i][j];
        }
        if(sum % 9 != 0){//如果总血量不能被9整除，那么这一层的怪物是无法通关的
            cout << "NO" << endl;
            continue;//进入下一层打怪
        }
        
        int times = sum / 9;//需要强化射击的次数
        bool flag = true;
        for(int j = 0; j < 3; j++){
            if(monsters[i][j] < times){//如果第j个怪物的血量小于需要强化射击的次数，那么这一层的怪物是无法通关的
                cout << "NO" << endl;
                flag = false;
                break;
            }
        }
        if(!flag){
            continue;
        }
        else cout << "YES" << endl;
        
    }
    return 0;

}