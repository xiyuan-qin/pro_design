#include<iostream>
#include<vector>

using namespace std;

// 计算棋子数
int solve(vector<vector<char>>& board, vector<bool>& rowUsed, vector<bool>& colUsed, 
          int n, int k/*棋子数量*/, int pos/*从0到n*n */, int count) {// pos = row * n + col
    // 已经放置k个棋子，找到一个
    if(count == k) {
        return 1;
    }   
    
    // 已考虑完所有位置但没放够k个
    if(pos == n * n) {
        return 0;
    }
    
    int row = pos / n;
    int col = pos % n;
    int solutions = 0;
    
    // 不在当前位置放棋子
    solutions += solve(board, rowUsed, colUsed, n, k, pos + 1, count);
    
    // 在当前位置放棋子
    if(board[row][col] == '#' && !rowUsed[row] && !colUsed[col]) {
        rowUsed[row] = true;
        colUsed[col] = true;
        solutions += solve(board, rowUsed, colUsed, n, k, pos + 1, count + 1);
        rowUsed[row] = false;
        colUsed[col] = false;
    }
    
    return solutions;
}

int main(){
    vector<vector<char>> chessBoard;
    int n, k;
    while(cin >> n >> k){
        if(n == -1 && k == -1){
            break;
        }
        chessBoard.resize(n, vector<char>(n));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                cin >> chessBoard[i][j];
            }
        }
        
        //已被占用的行和列
        vector<bool> rowUsed(n, false);
        vector<bool> colUsed(n, false);
        
        
        int count = solve(chessBoard, rowUsed, colUsed, n, k, 0, 0);
        cout << count << endl;
    }
    return 0;
}