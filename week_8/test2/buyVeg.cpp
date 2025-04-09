#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main(){
    int n;
    cin >> n;

    vector<pair<int, int>> timeOfH(n);
    vector<pair<int, int>> timeOfW(n);

    for(int i = 0; i < n; i++){
        cin >> timeOfH[i].first >> timeOfH[i].second;
    }

    for(int i = 0; i < n; i++){
        cin >> timeOfW[i].first >> timeOfW[i].second;
    }

    int tot_time = 0;
    int h_index = 0, w_index = 0;

    while(h_index < n && w_index < n){
        // 找出两个当前时间段的重叠部分
        int start = max(timeOfH[h_index].first, timeOfW[w_index].first);
        int end = min(timeOfH[h_index].second, timeOfW[w_index].second);
        
        // 如果有重叠，累加重叠时间
        if(start < end){
            tot_time += (end - start);
        }
        
        // 移动结束时间较早的指针
        if(timeOfH[h_index].second < timeOfW[w_index].second){
            h_index++;
        }
        else{
            w_index++;
        }
    }

    cout << tot_time << endl;
    return 0;
}