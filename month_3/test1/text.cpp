#include<iostream>
#include<vector>
#include<string>


using namespace std;


int n;
int cur_row, cur_col;
int sticky_start_row, sticky_start_col;
vector<string> text(1);
bool is_select = false;
bool is_sticky = false;
vector<string> clipboard;	
int sel_start_row, sel_start_col, sel_end_row, sel_end_col;


void deleteSelectedContent()
{
    is_select = false;
    if (sticky_start_row == cur_row)
    {
        text[cur_row].erase(sel_start_col, sel_end_col - sel_start_col);
        cur_col = sel_start_col;
    }
    else
    {
        text[sel_start_row] = text[sel_start_row].substr(0, sel_start_col);
        string tem = text[sel_end_row].substr(sel_end_col);
        text.erase(text.begin() + sel_end_row);

        for (int i = sel_start_row + 1; i < sel_end_row; ++i)
        {
            text.erase(text.begin() + sel_start_row + 1);
        }
        text[sel_start_row] = text[sel_start_row] + tem;

        cur_row = sel_start_row; cur_col = sel_start_col;
    }
}


void MOVE()
{
    if (is_select) { is_select = false; }
    string comd;
    cin >> comd;
    if (comd == "Home")
    {
        cur_col = 0;
    }
    else if (comd == "End")
    {
        cur_col = text[cur_row].size();
    }
    else if (comd == "Up")
    {
        if (cur_row == 0) return;
        cur_row--;
        if (text[cur_row].size() < cur_col)
        {
            cur_col = text[cur_row].size();
        }

    }
    else if (comd == "Down")
    {
        if (cur_row == text.size() - 1) return;
        cur_row++;
        if (text[cur_row].size() < cur_col)
        {
            cur_col = text[cur_row].size();
        }
    }
    else if (comd == "Left")
    {
        if (cur_row == 0 && cur_col == 0) return;

        if (cur_col == 0)
        {
            cur_row--;
            cur_col = text[cur_row].size();
            return;
        }
        cur_col--;
    }
    else if(comd=="Right")
    {
        if (cur_row == text.size() - 1 && cur_col == text[cur_row].size()) return;

        if (cur_col == text[cur_row].size())
        {
            cur_row++;
            cur_col = 0;
            return;
        }
        cur_col++;
    }

}

void INSERT()
{
    if (is_select) { deleteSelectedContent(); }

    string comd;
    cin >> comd;
    if (comd == "Char")
    {
        string c;
        cin >> c;
        text[cur_row].insert(cur_col, c);

        cur_col++;
    }
    else if (comd == "Enter")
    {
        string a = text[cur_row].substr(0, cur_col);
        string b = text[cur_row].substr(cur_col);
        text[cur_row] = a;
        text.insert(text.begin() + cur_row + 1, b);
        cur_col = 0; cur_row++;
    }
    else if (comd == "Space")
    {
        text[cur_row].insert(cur_col, " ");
        cur_col++;
    }
    else if (comd == "Paste")
    {
        if (clipboard.size() == 0) return;
        if (clipboard.size() == 1)
        {
            text[cur_row].insert(cur_col, clipboard[0]);

            cur_col += clipboard[0].size();
        }
        else if (clipboard.size() == 2)
        {
            string a = text[cur_row].substr(0, cur_col) + clipboard[0];
            string b = clipboard[1] + text[cur_row].substr(cur_col);
            text[cur_row] = a;
            text.insert(text.begin() + cur_row + 1, b);

            cur_row++; cur_col = clipboard[1].size();
        }
        else
        {
            string a = text[cur_row].substr(0, cur_col) + clipboard[0];
            string b = clipboard[clipboard.size()-1] + text[cur_row].substr(cur_col);
            text[cur_row] = a;
            text.insert(text.begin() + cur_row + 1, b);

            for (int i = 1; i < clipboard.size() - 1; ++i)
            {
                text.insert(text.begin() + cur_row + i, clipboard[i]);
            }

            cur_row += clipboard.size() - 1; 
            cur_col = clipboard[clipboard.size() - 1].size();
        }
    }
}

void REMOVE()
{
    if (is_select) { deleteSelectedContent(); return; }
    string comd;
    cin >> comd;
    if (comd == "Del")
    {
        if (cur_row == text.size() - 1 && cur_col == text[cur_row].size()) return;
        else if (cur_col == text[cur_row].size())
        {
            text[cur_row] = text[cur_row] + text[cur_row + 1];
            text.erase(text.begin() + cur_row + 1, text.begin() + cur_row + 2);

            return;
        }
        text[cur_row].erase(cur_col, 1);
    }
    else
    {
        if (cur_row == 0 && cur_col == 0) return;
        else if (cur_col == 0)
        {
            text[cur_row] = text[cur_row - 1] + text[cur_row];
            cur_col = text[cur_row - 1].size();
            text.erase(text.begin() + cur_row - 1, text.begin() + cur_row);
            cur_row--;
            return;
        }
        text[cur_row].erase(cur_col - 1, 1);
        cur_col--;
    }
}


void SHIFT()
{
    if (is_sticky)
    {
        if (sticky_start_col != cur_col || sticky_start_row != cur_row)
        {
            sel_end_col = sticky_start_col; sel_end_row = sticky_start_row; sel_start_col = cur_col; sel_start_row = cur_row;

            if (sel_end_row < sel_start_row)
            { 
                swap(sel_end_row, sel_start_row); swap(sel_end_col, sel_start_col);
            }
            else if (sel_end_row == sel_start_row && sel_end_col < sel_start_col) { swap(sel_end_col, sel_start_col); }
            is_select = true;
        }
        is_sticky = false;
    }
    else
    {
        if (is_select)
        {
            is_select = false;

        }
        else 
        {
            sticky_start_col = cur_col; sticky_start_row = cur_row;
        }
        is_sticky = true;
    }

}


void FIND()
{
    string word;
    cin >> word;
    int coun = 0;
    if(is_select)
    {
        if (sel_start_row != sel_end_row)
        {
            for (int i = sel_start_col; i + word.size() <= text[sel_start_row].size(); i++)
            {
                string tem = text[sel_start_row].substr(i, word.size());
                if (tem == word) coun++;
            }
            for (int i = 0; i + word.size() <= sel_end_col; ++i)
            {
                string tem = text[sel_end_row].substr(i, word.size());
                if (tem == word) coun++;
            }
            for (int i = sel_start_row + 1; i < sel_end_row; ++i)
            {
                for (int j = 0; j + word.size() <= text[i].size(); ++j)
                {
                    string tem = text[i].substr(j, word.size());
                    if (tem == word) coun++;
                }
            }
        }
        else
        {
            for (int i = sel_start_col; i + word.size() <= sel_end_col; ++i)
            {
                string tem = text[sel_start_row].substr(i, word.size());
                if (tem == word) coun++;
            }
        }
    }
    else
    {
        for (int i = 0; i <= text.size() - 1; ++i)
        {
            for (int j = 0; j + word.size() <= text[i].size(); ++j)
            {
                string tem = text[i].substr(j, word.size());
                if (tem == word) coun++;
            }
        }
    }
    cout << coun << endl;

}

void COUNT()
{
    int res_c=0;
    if (is_select)
    {
        if (sel_end_row != sel_start_row)
        {
            for (int i = sel_start_row + 1; i < sel_end_row; ++i)
            {
                for (int j = 0; j < text[i].size(); ++j)
                {
                    if (text[i][j] != ' ') res_c++;
                }
            }
            for (int i = sel_start_col; i < text[sel_start_row].size(); ++i)
            {
                if (text[sel_start_row][i] != ' ') res_c++;
            }
            for (int i = 0; i < sel_end_col; ++i)
            {
                if(text[sel_end_row][i]!=' ') res_c++;
            }
        }
        else
        {
            for (int i = sel_start_col; i < sel_end_col; ++i)
            {
                if (text[sel_start_row][i] != ' ') res_c++;
            }
        }
    }
    else
    {
        for (int i = 0; i < text.size(); ++i)
        {
            for (int j = 0; j < text[i].size(); ++j)
            {
                if (text[i][j] != ' ') res_c++;
            }
        }
    }
    cout << res_c << endl;
}

void COPY()
{
    if (is_select)
    {
        clipboard.clear();
        if (sel_end_row == sel_start_row)
        {
            string tem = text[sel_start_row].substr(sel_start_col, sel_end_col - sel_start_col);
            clipboard.push_back(tem);
        }
        else
        {
            string a = text[sel_start_row].substr(sel_start_col);
            clipboard.push_back(a);
            for (int i = sel_start_row + 1; i < sel_end_row; ++i)
            {
                clipboard.push_back(text[i]);
            }
            string b = text[sel_end_row].substr(0, sel_end_col);
            clipboard.push_back(b);
        }
    }
    else if(text[cur_row].size()!=0)
    {
        clipboard.clear();
        clipboard.push_back(text[cur_row]);
    }
}


void PRINT()
{
    for (int i = 0; i != text.size(); ++i)
    {
        cout << text[i] << endl;
    }

}

int main()
{
    FILE* outfp;
    cin >> n;
    
    for (int i = 0; i < n+50; ++i)
    {
        string op;
        cin >> op;
        if (op == "MOVE") MOVE();
        else if (op == "INSERT") INSERT();
        else if (op == "REMOVE") REMOVE();
        else if (op == "SHIFT") SHIFT();
        else if (op == "FIND") FIND();
        else if (op == "COUNT") COUNT();
        else if (op == "COPY") COPY();
        else if (op == "PRINT") PRINT();
        
    }
    
    return 0;
}