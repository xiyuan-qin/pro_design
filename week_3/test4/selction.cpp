#include<iostream>
#include<vector>

using namespace std;

bool isPrime(int n)
{
    if(n==1) return false;
    if (n==2) return true;
	for(int i=2 ; i * i <= n; i++)
	    if (n % i == 0) return false;
	return true; 
}

void generateCombination(const vector<int>& nums, vector<int>& current, int start, 
    int k, vector<vector<int>>& result) {
    if (current.size() == k) {
        result.push_back(current);
        return;
    }

    for (int i = start; i < nums.size(); i++) {
        current.push_back(nums[i]);
        generateCombination(nums, current, i + 1, k, result);
        current.pop_back();
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

    int count = 0;
    for(vector<int> combination : result){
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