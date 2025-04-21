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

    void MOVE(string opt) {
        // 保存当前位置
        int old_row = cur_row;
        int old_col = cur_col;
        
        // 执行原有的移动逻辑
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
        
        // 如果处于选中状态，移动会导致退出选中状态
        if (is_select) {
            is_select = false;
        }
        
        // 如果处于粘滞状态，更新结束点
        if (is_sticky && (old_row != cur_row || old_col != cur_col)) {
            sticky_end_row = cur_row;
            sticky_end_col = cur_col;
        }
    }

    void INSERT(string opt) {
        // 如果处于选中状态，先删除选中内容
        if (is_select) {
            deleteSelectedContent();
            is_select = false;
        }
        
        // 如果处于粘滞状态，不执行插入操作
        if (is_sticky) {
            return;
        }
        
        // 执行原有的插入逻辑
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

    void REMOVE(string opt) {
        // 如果处于选中状态，删除选中内容
        if (is_select) {
            deleteSelectedContent();
            is_select = false;
            return;
        }
        
        // 如果处于粘滞状态，不执行删除操作
        if (is_sticky) {
            return;
        }
        
        if (opt == "Del") {
            if (cur_row == row - 1 && cur_col == text[cur_row].size()) {
                return; // 在文件末尾，忽略操作
            }
            
            if (cur_col == text[cur_row].size()) {
                text[cur_row].insert(text[cur_row].end(), text[cur_row + 1].begin(), text[cur_row + 1].end());
                text.erase(text.begin() + cur_row + 1);
                row--;
            } 
            else {
                text[cur_row].erase(text[cur_row].begin() + cur_col);
            }
        }
        else if (opt == "Backspace") {
            if (cur_row == 0 && cur_col == 0) {
                return;
            }
            if (cur_col == 0) {
                cur_col = text[cur_row - 1].size();

                text[cur_row - 1].insert(text[cur_row - 1].end(), text[cur_row].begin(), text[cur_row].end());
                text.erase(text.begin() + cur_row);
                
                row--;
                cur_row--;
                
            }
            else {
                text[cur_row].erase(text[cur_row].begin() + cur_col - 1);
                cur_col--;
            }
        }
    }

    void SHIFT() {
        if (is_sticky) {
            // 关闭粘滞功能
            is_sticky = false;
            
            // 检查光标是否移动
            if (sticky_start_row != cur_row || sticky_start_col != cur_col) {
                // 进入选中状态
                is_select = true;
                sticky_end_row = cur_row;
                sticky_end_col = cur_col;
            }
        } else {
            // 如果已经处于选中状态，只退出选中状态但保留记录点
            if (is_select) {
                is_select = false;
            } else {
                // 启动粘滞功能时，记录当前光标位置
                sticky_start_row = cur_row;
                sticky_start_col = cur_col;
            }
            is_sticky = true;
        }
    }

    // 规范化选中区域，确保start在end之前
    void normalizeSelection() {
        // 确保起点在终点之前（行优先）
        if (sticky_start_row > sticky_end_row || 
            (sticky_start_row == sticky_end_row && sticky_start_col > sticky_end_col)) {
            swap(sticky_start_row, sticky_end_row);
            swap(sticky_start_col, sticky_end_col);
        }
    }

    // 获取选中内容
    string getSelectedContent() {
        normalizeSelection();
        string content;
        
        // 特殊情况：选中内容在同一行
        if (sticky_start_row == sticky_end_row) {
            for (int i = sticky_start_col; i < sticky_end_col; ++i) {
                content.push_back(text[sticky_start_row][i]);
            }
            return content;
        }
        
        // 第一行（从起始点到行尾）
        for (int i = sticky_start_col; i < text[sticky_start_row].size(); ++i) {
            content.push_back(text[sticky_start_row][i]);
        }
        content.push_back(EOL);
        
        // 中间的整行
        for (int i = sticky_start_row + 1; i < sticky_end_row; ++i) {
            for (char ch : text[i]) {
                content.push_back(ch);
            }
            content.push_back(EOL);
        }
        
        // 最后一行（从行首到结束点）
        for (int i = 0; i < sticky_end_col; ++i) {
            content.push_back(text[sticky_end_row][i]);
        }
        
        return content;
    }

    // 删除选中内容
    void deleteSelectedContent() {
        normalizeSelection();
        
        // 将光标移至选中区域起点
        cur_row = sticky_start_row;
        cur_col = sticky_start_col;
        
        // 特殊情况：选中内容在同一行
        if (sticky_start_row == sticky_end_row) {
            text[cur_row].erase(
                text[cur_row].begin() + sticky_start_col,
                text[cur_row].begin() + sticky_end_col
            );
            return;
        }
        
        // 保存起始行中保留的部分
        vector<char> first_line_preserved(
            text[sticky_start_row].begin(),
            text[sticky_start_row].begin() + sticky_start_col
        );
        
        // 保存末尾行中保留的部分
        vector<char> last_line_preserved(
            text[sticky_end_row].begin() + sticky_end_col,
            text[sticky_end_row].end()
        );
        
        // 合并首尾两行的保留部分
        first_line_preserved.insert(
            first_line_preserved.end(),
            last_line_preserved.begin(),
            last_line_preserved.end()
        );
        
        // 删除从起始行到结束行的所有内容
        text.erase(
            text.begin() + sticky_start_row,
            text.begin() + sticky_end_row + 1
        );
        
        // 插入合并后的行
        text.insert(text.begin() + sticky_start_row, first_line_preserved);
        
        // 更新行数
        row = text.size();
    }

    void COPY() {
        // 如果是选中状态，复制选中内容
        if (is_select) {
            clipboard = getSelectedContent();
        } else {
            // 否则复制当前行
            clipboard.clear();
            for (char ch : text[cur_row]) {
                clipboard.push_back(ch);
            }
        }
        // 复制操作不会退出选中状态
    }

};