#include<iostream>
#include<vector>
#include<climits> 
#include<cmath> 
#include<algorithm> 

using namespace std;

int main(){
    int n;
    cin >> n;
    if (n <= 0) {
        cout << 0 << endl;
        return 0;
    }
     if (n == 1) {
        cout << 0 << endl; 
    }


    vector<vector<int>> matrix(3, vector<int>(n));
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matrix[i][j];
        }
    }


    vector<long long> dp(3, 0); 


    for (int col = 1; col < n; col++) {
    
        vector<long long> new_dp(3, -1); 

        for (int curr_row = 0; curr_row < 3; curr_row++) {
            long long min_cost_for_curr = -1; 

            for (int prev_row = 0; prev_row < 3; prev_row++) {
                long long diff = abs((long long)matrix[curr_row][col] - matrix[prev_row][col-1]);
                long long current_path_cost = dp[prev_row] + diff;

                if (min_cost_for_curr == -1 || current_path_cost < min_cost_for_curr) {
                     min_cost_for_curr = current_path_cost;
                }
            }
             new_dp[curr_row] = min_cost_for_curr;
        }
        dp = new_dp;
    }

    long long result = -1;
    for(int i=0; i<3; ++i){
        if(result == -1 || dp[i] < result){
            result = dp[i];
        }
    }

    cout << result << endl;

    return 0;
}