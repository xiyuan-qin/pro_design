#include<iostream>
#include<algorithm>
#include<vector>
#include<map>

using namespace std;

bool checkUp(vector<vector<int>>& matrix, int i, int j) {
    if(i == 0) return true; // 第一行一定是最高的
    return matrix[i][j] > matrix[i - 1][j];
}

bool checkDown(vector<vector<int>>& matrix, int i, int j) {
    if(i == matrix[0].size() - 1) return true; // 最后一行一定是最高的
    return matrix[i][j] > matrix[i + 1][j];
}

bool checkLeft(vector<vector<int>>& matrix, int i, int j) {
    if(j == 0) return true; // 第一列一定是最高的
    return matrix[i][j] > matrix[i][j - 1];
}

bool checkRight(vector<vector<int>>& matrix, int i, int j) {
    if(j == matrix.size() - 1) return true; // 最后一列一定是最高的
    return matrix[i][j] > matrix[i][j + 1];
}

bool checkHighest(vector<vector<int>>& matrix, int i, int j) {
    return checkUp(matrix, i, j) && checkDown(matrix, i, j) && checkLeft(matrix, i, j) && checkRight(matrix, i, j);
}

int main(){
    int rows , cols;
    cin >> rows >> cols;

    vector<vector<int>> matrix(rows, vector<int>(cols));
    map<int, pair<int, int>> highest;

    int highestCount = 0;

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cin >> matrix[i][j];
        }
    }

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(checkHighest(matrix, i, j)){
                highestCount++;
            }
        }
    }

    cout << highestCount << endl;
    return 0;
}