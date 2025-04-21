#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<map>
#include<set>
#include<queue>
#include<stack>

using namespace std;

/**
 * 需要设计的：
 * //1.光标移动，一个cur指针
 * //2.行列数
 * //3.规定一个特殊的字符，表示换行
 * //4.为了保证光标在行间移动，使用二维vector存储整个文本
 * 5.各种commend最好分别写类封装，做成类似接口
 * //6.设计一个粘贴板
 * //7.设计一个bool值，表示是否开启粘滞功能
 * //还有是否是选中状态的bool值
 * //8.粘滞功能的起始点和结束点
 * 9.copy复制当前行，没有换行符  ｜｜  选中状态下复制选中的内容
 */

//换行类的封装
class Move{
public:
};

class Text{
public:
    vector<vector<char>> text;// 存储文本
    int cur_row, cur_col;// 光标位置
    int row, col;// 行列数
    bool is_select;// 是否选中状态
    bool is_sticky;// 是否开启粘滞功能
    int sticky_start_row, sticky_start_col;// 粘滞功能的起始点
    int sticky_end_row, sticky_end_col;// 粘滞功能的结束点
    string clipboard;// 粘贴板
    char EOL = '\n';// 换行符

    Text() : cur_row(0), cur_col(0), is_select(false), is_sticky(false) {
    }


public:

    void MOVE(string opt){
        if(opt == "UP"){
            if(cur_row > 0){
                if(text[cur_row - 1].size() < text[cur_row].size()){
                    cur_col = text[cur_row - 1].size();
                }
                else{
                    cur_row--;
                } 
            }
        }else if(opt == "DOWN"){
            if(cur_row < row - 1){
                if(text[cur_row + 1].size() < text[cur_row].size()){
                    cur_col = text[cur_row + 1].size();
                }
                else{
                    cur_row++;
                }
            }
        }else if(opt == "LEFT"){
            if(!(cur_col == 0 && cur_row == 0)){
                if(cur_col == 0){
                    cur_row--;
                    cur_col = text[cur_row].size();
                }
                else{
                    cur_col--;
                }
            }
        }else if(opt == "RIGHT"){
            if(!(cur_col == text[cur_row].size() && cur_row == row - 1)){
                if(cur_col == text[cur_row].size()){
                    cur_row++;
                    cur_col = 0;
                }
                else{
                    cur_col++;
                }
            }
        }else if(opt == "HOME"){
            cur_col = 0;
            cur_row = 0;
        }else if(opt == "END"){
            cur_col = col;
            cur_row = row - 1;
        }
    }

    void INSERT(string opt){
        if(opt == "Char"){
            char ch;
            cin >> ch;
            text[cur_row].insert(text[cur_row].begin() + cur_col, ch);
            cur_col++;
        }else if(opt == "Enter"){
            // 创建新行，包含当前行光标后面的所有内容
            vector<char> new_line;
            if(cur_col < text[cur_row].size()) {
                // 将当前行光标位置后面的内容复制到新行
                new_line.assign(text[cur_row].begin() + cur_col, text[cur_row].end());
                // 从当前行删除已移动到新行的内容
                text[cur_row].erase(text[cur_row].begin() + cur_col, text[cur_row].end());
            }
            
            // 在当前行后面插入新行
            text.insert(text.begin() + cur_row + 1, new_line);
            row++;
            cur_row++;
            cur_col = 0;
        }
    }

};