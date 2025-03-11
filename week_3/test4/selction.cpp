#include<iostream>
#include<vector>

using namespace std;

bool isPrime(int n)//计算是否为素数
{
    if(n==1) return false;
    if (n==2) return true;
	for(int i=2 ; i * i <= n; i++)
	    if (n % i == 0) return false;
	return true; 
}

void generateCombination(const vector<int>& nums, vector<int>& current, int start, 
    int k, vector<vector<int>>& result) {

    if (current.size() == k) {// 够了，存进result
        result.push_back(current);
        return;
    }

    for (int i = start; i < nums.size(); i++) {
        current.push_back(nums[i]);//先存一个元素
        generateCombination(nums, current, i + 1, k, result);//在下一个位置产生对应的排列
        current.pop_back();//拿掉，下一个循环插入下一个元素
    }
}

int main(){
    int n , k;
    cin>> n >> k;
    vector<int> num(n, 0);
    for(int i = 0; i < n; i++){
        cin>> num[i];
    }
    
    vector<int> current;
    vector<vector<int>> result;
    generateCombination(num, current, 0, k, result);

    int count = 0;//素数的个数
    for(vector<int> combination : result){//遍历所有的组合
        int sum = 0;
        for(int i = 0; i < k; i++){
            sum += combination[i];
        }
        if(isPrime(sum)){
            count++;
        }
    }
    cout<< count << endl;
    return 0;
    
}