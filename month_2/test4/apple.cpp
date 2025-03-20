#include<iostream>
#include<vector>
#include<map>
#include<algorithm>

using namespace std;

int sumBefore(vector<int>& num , int index){
    int sum = 0;
    for(int i = 0; i <= index; i++){
        sum += num[i];
    }
    return sum;
}

int sumAfter(vector<int>& num , int index){
    int sum = 0;
    for(int i = index + 1; i < num.size(); i++){
        sum += num[i];
    }
    return sum;
}

int main(){
    int nums;
    cin >> nums;
    vector<int> num(nums);

    for(int i = 0; i < nums; i++){
        cin >> num[i];
    }

    int total = 0;
    for(int i = 0; i < nums; i++){
        total += num[i];
    }

    int result = 0;
    int leftSum = 0;

    for(int i = 0; i < nums - 1; i++){
        leftSum += num[i];
        int rightSum = total - leftSum;
        if(leftSum == rightSum){
            result++;
        }
    }
    cout << result << endl;
    return 0;
}