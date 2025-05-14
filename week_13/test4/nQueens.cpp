#include<iostream>
#include<vector>
#include<cstring>

using namespace std;

int N, K;
typedef long long ll;

bool hasConflict(int row1, int row2) {
    if ((row1 & row2) != 0) return true; 
    
    if ((row1 << 1) & row2) return true; 
    if ((row1 >> 1) & row2) return true; 
    
    return false;
}

bool isValidRow(int state) {
    int prevBit = 0;
    for (int i = 0; i < N; i++) {
        int curBit = (state >> i) & 1;
        if (curBit && prevBit) return false; 
        prevBit = curBit;
    }
    return true;
}

int countBits(int state) {
    int cnt = 0;
    while (state) {
        cnt += state & 1;
        state >>= 1;
    }
    return cnt;
}

vector<int> generateValidStates() {
    vector<int> validStates;
    int maxState = 1 << N;
    for (int state = 0; state < maxState; state++) {
        if (isValidRow(state)) {
            validStates.push_back(state);
        }
    }
    return validStates;
}

int main() {
    cin >> N >> K;
    
    vector<int> validStates = generateValidStates();
    int stateSize = validStates.size();

    vector<vector<vector<ll>>> dp(N+1, vector<vector<ll>>(stateSize, vector<ll>(K+1, 0)));

    for (int j = 0; j < stateSize; j++) {
        int kingsInState = countBits(validStates[j]);
        if (kingsInState <= K) {
            dp[1][j][kingsInState] = 1;
        }
    }

    for (int i = 2; i <= N; i++) { 
        for (int j = 0; j < stateSize; j++) { 
            int curState = validStates[j];
            int kingsInCurRow = countBits(curState);
            
            for (int prev = 0; prev < stateSize; prev++) {
                int prevState = validStates[prev];

                if (!hasConflict(curState, prevState)) {
                    for (int k = 0; k + kingsInCurRow <= K; k++) {
                        dp[i][j][k + kingsInCurRow] += dp[i-1][prev][k];
                    }
                }
            }
        }
    }
    
    ll result = 0;
    for (int j = 0; j < stateSize; j++) {
        result += dp[N][j][K];
    }
    
    cout << result << endl;
    
    return 0;
}