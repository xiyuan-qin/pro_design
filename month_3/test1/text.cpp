#include<iostream>
#include<vector>
#include<string>
using namespace std;

/**
* 需要设计的：
* //1.光标移动，一个cur指针
* //2.行列数
* //3.规定一个特殊的字符，表示换行
* //4.为了保证光标在行间移动，使用二维vector存储整个文本
* //5.各种commend最好分别写类封装，做成类似接口
* //6.设计一个粘贴板
* //7.设计一个bool值，表示是否开启粘滞功能
* //还有是否是选中状态的bool值
* //8.粘滞功能的起始点和结束点
* //9.copy复制当前行，没有换行符  ｜｜  选中状态下复制选中的内容
*/


class Text {
public:
    vector<string> text; 
    int cur_row, cur_col;
    bool is_select;
    bool is_sticky;
    int sticky_start_row, sticky_start_col;
    int sticky_end_row, sticky_end_col;
    vector<string> clipboard;

    Text() : cur_row(0), cur_col(0), is_select(false), is_sticky(false) {
        text.push_back(""); 
    }

    void MOVE(string opt) {
        if (is_select) is_select = false;

        if (opt == "Home") {
            cur_col = 0;
        } else if (opt == "End") {
            cur_col = text[cur_row].size();
        } else if (opt == "Up") {
            if (cur_row > 0) {
                cur_row--;
                if (cur_col > text[cur_row].size()) {
                    cur_col = text[cur_row].size();
                }
            }
        } else if (opt == "Down") {
            if (cur_row < text.size() - 1) {
                cur_row++;
                if (cur_col > text[cur_row].size()) {
                    cur_col = text[cur_row].size();
                }
            }
        } else if (opt == "Left") {
            if (cur_row == 0 && cur_col == 0) return;
            if (cur_col == 0) {
                cur_row--;
                cur_col = text[cur_row].size();
            } else {
                cur_col--;
            }
        } else if (opt == "Right") {
            if (cur_row == text.size() - 1 && cur_col == text[cur_row].size()) return;
            if (cur_col == text[cur_row].size()) {
                cur_row++;
                cur_col = 0;
            } else {
                cur_col++;
            }
        }
    }

    void INSERT(string opt) {
        if (is_sticky) return;
        if (is_select) {
            deleteSelectedContent();
            is_select = false;
        }

        if (opt == "Char") {
            char ch;
            cin >> ch;
            text[cur_row].insert(cur_col, 1, ch);
            cur_col++;
        } else if (opt == "Enter") {
            string front = text[cur_row].substr(0, cur_col);
            string back = text[cur_row].substr(cur_col);
            text[cur_row] = front;
            text.insert(text.begin() + cur_row + 1, back);
            cur_row++;
            cur_col = 0;
        } else if (opt == "Space") {
            text[cur_row].insert(cur_col, " ");
            cur_col++;
        } else if (opt == "Paste") {
            if (clipboard.empty()) return;
            if (clipboard.size() == 1) {
                text[cur_row].insert(cur_col, clipboard[0]);
                cur_col += clipboard[0].size();
            } else {
                string front = text[cur_row].substr(0, cur_col);
                string back = text[cur_row].substr(cur_col);
                text[cur_row] = front + clipboard[0];
                for (size_t i = 1; i < clipboard.size(); ++i) {
                    text.insert(text.begin() + cur_row + i, clipboard[i]);
                }
                cur_row += clipboard.size() - 1;
                cur_col = clipboard.back().size();
                text[cur_row] += back;
            }
        }
    }

    void REMOVE(string opt) {
        if (is_sticky) return;
        if (is_select) {
            deleteSelectedContent();
            is_select = false;
            return;
        }

        if (text.empty()) return;

        if (opt == "Del") {
            if (cur_row == text.size() - 1 && cur_col == text[cur_row].size()) return;
            if (cur_col == text[cur_row].size()) {
                text[cur_row] += text[cur_row + 1];
                text.erase(text.begin() + cur_row + 1);
            } else {
                text[cur_row].erase(cur_col, 1);
            }
        } else { // Backspace
            if (cur_row == 0 && cur_col == 0) return;
            if (cur_col == 0) {
                int prev_len = text[cur_row - 1].size();
                text[cur_row - 1] += text[cur_row];
                text.erase(text.begin() + cur_row);
                cur_row--;
                cur_col = prev_len;
            } else {
                text[cur_row].erase(cur_col - 1, 1);
                cur_col--;
            }
        }
    }

    void SHIFT() {
        if (is_sticky) {
            is_sticky = false;
            if (sticky_start_row != cur_row || sticky_start_col != cur_col) {
                sticky_end_row = cur_row;
                sticky_end_col = cur_col;
                if (sticky_start_row > sticky_end_row || (sticky_start_row == sticky_end_row && sticky_start_col > sticky_end_col)) {
                    swap(sticky_start_row, sticky_end_row);
                    swap(sticky_start_col, sticky_end_col);
                }
                is_select = true;
            }
        } else {
            if (!is_select) {
                sticky_start_row = cur_row;
                sticky_start_col = cur_col;
            }
            is_sticky = true;
            is_select = false;
        }
    }

    void deleteSelectedContent() {
        if (sticky_start_row == sticky_end_row) {
            text[sticky_start_row].erase(sticky_start_col, sticky_end_col - sticky_start_col);
        } else {
            string back = text[sticky_end_row].substr(sticky_end_col);
            text[sticky_start_row] = text[sticky_start_row].substr(0, sticky_start_col) + back;
            text.erase(text.begin() + sticky_start_row + 1, text.begin() + sticky_end_row + 1);
        }
        cur_row = sticky_start_row;
        cur_col = sticky_start_col;
        is_select = false;
    }

    void COPY() {
        clipboard.clear();
        if (is_select) {
            if (sticky_start_row == sticky_end_row) {
                clipboard.push_back(text[sticky_start_row].substr(sticky_start_col, sticky_end_col - sticky_start_col));
            } else {
                clipboard.push_back(text[sticky_start_row].substr(sticky_start_col));
                for (int i = sticky_start_row + 1; i < sticky_end_row; ++i) {
                    clipboard.push_back(text[i]);
                }
                clipboard.push_back(text[sticky_end_row].substr(0, sticky_end_col));
            }
        } else if (!text[cur_row].empty()) {
            clipboard.push_back(text[cur_row]);
        }
    }

    void FIND(string word) {
        int count = 0;
        if (is_select) {
            if (sticky_start_row == sticky_end_row) {
                string selected = text[sticky_start_row].substr(sticky_start_col, sticky_end_col - sticky_start_col);
                size_t pos = 0;
                while ((pos = selected.find(word, pos)) != string::npos) {
                    count++;
                    pos += word.size();
                }
            } else {
                string first = text[sticky_start_row].substr(sticky_start_col);
                size_t pos = 0;
                while ((pos = first.find(word, pos)) != string::npos) {
                    count++;
                    pos += word.size();
                }
                for (int i = sticky_start_row + 1; i < sticky_end_row; ++i) {
                    pos = 0;
                    while ((pos = text[i].find(word, pos)) != string::npos) {
                        count++;
                        pos += word.size();
                    }
                }
                string last = text[sticky_end_row].substr(0, sticky_end_col);
                pos = 0;
                while ((pos = last.find(word, pos)) != string::npos) {
                    count++;
                    pos += word.size();
                }
            }
        } else {
            for (const string& line : text) {
                size_t pos = 0;
                while ((pos = line.find(word, pos)) != string::npos) {
                    count++;
                    pos += word.size();
                }
            }
        }
        cout << count << endl;
    }

    void COUNT() {
        int count = 0;
        if (is_select) {
            if (sticky_start_row == sticky_end_row) {
                string selected = text[sticky_start_row].substr(sticky_start_col, sticky_end_col - sticky_start_col);
                for (char c : selected) {
                    if (c != ' ') count++;
                }
            } else {
                string first = text[sticky_start_row].substr(sticky_start_col);
                for (char c : first) {
                    if (c != ' ') count++;
                }
                for (int i = sticky_start_row + 1; i < sticky_end_row; ++i) {
                    for (char c : text[i]) {
                        if (c != ' ') count++;
                    }
                }
                string last = text[sticky_end_row].substr(0, sticky_end_col);
                for (char c : last) {
                    if (c != ' ') count++;
                }
            }
        } else {
            for (const string& line : text) {
                for (char c : line) {
                    if (c != ' ') count++;
                }
            }
        }
        cout << count << endl;
    }

    void PRINT() {
        for (const string& line : text) {
            cout << line << endl;
        }
    }
};

int main() {
    int n;
    cin >> n;
    Text text;
    string cmd, opt;
    for (int i = 0; i < n; ++i) {
        cin >> cmd;
        if (cmd == "MOVE") {
            cin >> opt;
            text.MOVE(opt);
        } else if (cmd == "INSERT") {
            cin >> opt;
            text.INSERT(opt);
        } else if (cmd == "REMOVE") {
            cin >> opt;
            text.REMOVE(opt);
        } else if (cmd == "SHIFT") {
            text.SHIFT();
        } else if (cmd == "COPY") {
            text.COPY();
        } else if (cmd == "FIND") {
            string word;
            cin >> word;
            text.FIND(word);
        } else if (cmd == "COUNT") {
            text.COUNT();
        } else if (cmd == "PRINT") {
            text.PRINT();
        }
    }
}