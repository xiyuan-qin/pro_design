#include <iostream>
#include <vector>
using namespace std;

vector<vector<long long>> matrix_multiply(const vector<vector<long long>>& A, 
                                          const vector<vector<long long>>& B, 
                                          long long p) {
    int rows_A = A.size();
    int cols_A = A[0].size();
    int cols_B = B[0].size();
    
    vector<vector<long long>> C(rows_A, vector<long long>(cols_B, 0));
    
    for (int i = 0; i < rows_A; i++) {
        for (int j = 0; j < cols_B; j++) {
            for (int k = 0; k < cols_A; k++) {
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % p;
            }
        }
    }
    
    return C;
}

vector<vector<long long>> matrix_power(vector<vector<long long>> A, long long n, long long p) {
    int size = A.size();
    vector<vector<long long>> result(size, vector<long long>(size, 0));
    
    for (int i = 0; i < size; i++) {
        result[i][i] = 1;
    }
    
    while (n > 0) {
        if (n & 1) {
            result = matrix_multiply(result, A, p);
        }
        A = matrix_multiply(A, A, p);
        n >>= 1;
    }
    
    return result;
}

long long fibonacci(long long n, long long p) {
    if (n <= 0) return 0;
    if (n == 1 || n == 2) return 1;
    
    vector<vector<long long>> base = {{1, 1}, {1, 0}};
    
    vector<vector<long long>> result = matrix_power(base, n - 1, p);
    
    return result[0][0];
}

int main() {
    int T;
    cin >> T;
    
    while (T--) {
        long long n, p;
        cin >> n >> p;
        
        cout << fibonacci(n, p) << endl;
    }
    
    return 0;
}
