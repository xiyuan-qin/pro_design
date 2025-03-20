#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>

using namespace std;

long long sumOfFirst(long long k){
    return k * (k + 1) / 2;
}

int main(){
    int n;
    cin >> n;

    long long total = 0;
    long long result = LLONG_MAX;

    vector<int> timesOfSkills(n);

    for(int i = 0; i < n; i++){
        cin >> timesOfSkills[i];
        total += timesOfSkills[i];
    }
    
    vector<long long> prefixSum(n, 0);
    prefixSum[0] = timesOfSkills[0];
    for(int i = 1; i < n; i++){
        prefixSum[i] = prefixSum[i-1] + timesOfSkills[i];
    }

    for(int i = 0; i < n-1; i++){ 
        long long beforeDrug = sumOfFirst(prefixSum[i]);
        long long afterDrug = sumOfFirst(total - prefixSum[i]);
        result = min(result, beforeDrug + afterDrug);
    }

    cout << result << endl;

    return 0;
}