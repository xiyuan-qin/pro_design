#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main(){
    int num_of_buckets, m;
    cin>> num_of_buckets>> m;
    vector<vector<int>> buckets(num_of_buckets);


    for(int i = 0; i < m; i++){// 有m行数据
        int bucket_num, value;
        cin>> value >> bucket_num;
        buckets[bucket_num - 1].push_back(value);
    }

    for(int i = 0; i < num_of_buckets; i++){
        sort(buckets[i].begin(), buckets[i].end());
        for(int j = 0; j < buckets[i].size(); j++){
            cout<< buckets[i][j]<< " ";
        }
        cout<< endl;
    }
    return 0;


}