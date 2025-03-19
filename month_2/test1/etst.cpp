#include <iostream>
#include <deque>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <climits> 

using namespace std;

class Window {
public:
    int likeness;   
    long long chatCount;  
    bool isTop;   

    Window(int l) : likeness(l), chatCount(0), isTop(false) {}
};

class ChatSystem {
private:
    deque<Window*> windows;                    // 窗口队列
    unordered_map<int, Window*> likenessMap;   // 喜爱度到窗口的映射

   
    Window* getTopWindow() {
        if (windows.empty()) return nullptr;
        
        // 检查是否有窗口置顶
        for (auto window : windows) {
            if (window->isTop) {
                return window;
            }
        }
        
        // 没有置顶窗口，返回队首
        return windows.front();
    }

public:
    ChatSystem() {}

    ~ChatSystem() {
        for (auto window : windows) {
            delete window;
        }
        windows.clear();
        likenessMap.clear();
    }

  
    string add(int likeness) {
        if (likenessMap.find(likeness) != likenessMap.end()) {
            return "same likeness";
        }

        Window* window = new Window(likeness);
        windows.push_back(window);
        likenessMap[likeness] = window;
        return "success";
    }

    string close(int likeness) {
        auto it = likenessMap.find(likeness);
        if (it == likenessMap.end()) {
            return "invalid likeness";
        }

        Window* window = it->second;
        long long chatCount = window->chatCount;

        // 从队列中删除
        auto iter = find(windows.begin(), windows.end(), window);
        if (iter != windows.end()) {
            windows.erase(iter);
        }
        
        likenessMap.erase(likeness);
        delete window;
        return "close " + to_string(likeness) + " with " + to_string(chatCount);
    }
    string chat(long long count) {
        Window* top = getTopWindow();
        if (!top) {
            return "empty";
        }
        top->chatCount += count;
        return "success";
    }

    string rotate(int x) {
        if (x < 1 || x > windows.size()) {
            return "out of range";
        }
        
        if (x > 1) {  // x=1时不需要任何操作
            Window* window = windows[x-1];
            windows.erase(windows.begin() + (x-1));
            windows.push_front(window);
        }

        return "success";
    }


    string prior() {
        if (windows.empty()) {
            return "empty";
        }

        // 找到最高喜爱度的窗口
        int maxLikeness = INT_MIN;
        Window* maxWindow = nullptr;
        
        for (auto window : windows) {
            if (window->likeness > maxLikeness) {
                maxLikeness = window->likeness;
                maxWindow = window;
            }
        }

        // 如果最高喜爱度的窗口不在队首，则移动它
        if (maxWindow != windows.front()) {
            auto iter = find(windows.begin(), windows.end(), maxWindow);
            windows.erase(iter);
            windows.push_front(maxWindow);
        }

        return "success";
    }

    string choose(int likeness) {
        auto it = likenessMap.find(likeness);
        if (it == likenessMap.end()) {
            return "invalid likeness";
        }

        Window* window = it->second;
        
        // 如果不在队首，则移动到队首
        if (window != windows.front()) {
            auto iter = find(windows.begin(), windows.end(), window);
            windows.erase(iter);
            windows.push_front(window);
        }

        return "success";
    }

    string top(int likeness) {
        auto it = likenessMap.find(likeness);
        if (it == likenessMap.end()) {
            return "invalid likeness";
        }

        // 取消所有窗口的置顶状态
        for (auto window : windows) {
            window->isTop = false;
        }

        // 设置新的置顶
        it->second->isTop = true;
        return "success";
    }


    string untop() {
        bool found = false;
        
        // 寻找置顶窗口并取消置顶
        for (auto window : windows) {
            if (window->isTop) {
                window->isTop = false;
                found = true;
                break;
            }
        }
        
        if (!found) {
            return "no such person";
        }
        
        return "success";
    }

    vector<string> sayBye() {
        vector<string> messages;
        
        // 首先检查是否有置顶窗口，如果有且聊过天则先处理它
        for (auto it = windows.begin(); it != windows.end(); ++it) {
            if ((*it)->isTop && (*it)->chatCount > 0) {
                messages.push_back("Bye " + to_string((*it)->likeness) + ": " + to_string((*it)->chatCount));
                break;
            }
        }
        
        // 然后处理其他窗口
        while (!windows.empty()) {
            Window* window = windows.front();
            int likeness = window->likeness;
            long long chatCount = window->chatCount;
            
            if (!window->isTop && chatCount > 0) {
                messages.push_back("Bye " + to_string(likeness) + ": " + to_string(chatCount));
            }
            
            //移除
            windows.pop_front();
            likenessMap.erase(likeness);
            delete window;
        }
        
        return messages;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while (T--) {
        int n;
        cin >> n;
        
        ChatSystem system;
        int opId = 1;
        
        for (int i = 0; i < n; i++) {
            string op;
            cin >> op;
            
            // 处理可能的\r字符
            op.erase(remove(op.begin(), op.end(), '\r'), op.end());
            
            if (op == "Add") {
                int likeness;
                cin >> likeness;
                cout << "OpId #" << opId++ << ": " << system.add(likeness) << "." << endl;
            }
            else if (op == "Close") {
                int likeness;
                cin >> likeness;
                cout << "OpId #" << opId++ << ": " << system.close(likeness) << "." << endl;
            }
            else if (op == "Chat") {
                long long count;
                cin >> count;
                cout << "OpId #" << opId++ << ": " << system.chat(count) << "." << endl;
            }
            else if (op == "Rotate") {
                int x;
                cin >> x;
                cout << "OpId #" << opId++ << ": " << system.rotate(x) << "." << endl;
            }
            else if (op == "Prior") {
                cout << "OpId #" << opId++ << ": " << system.prior() << "." << endl;
            }
            else if (op == "Choose") {
                int likeness;
                cin >> likeness;
                cout << "OpId #" << opId++ << ": " << system.choose(likeness) << "." << endl;
            }
            else if (op == "Top") {
                int likeness;
                cin >> likeness;
                cout << "OpId #" << opId++ << ": " << system.top(likeness) << "." << endl;
            }
            else if (op == "Untop") {
                cout << "OpId #" << opId++ << ": " << system.untop() << "." << endl;
            }
        }
       
        vector<string> byeMessages = system.sayBye();
        for (const auto& msg : byeMessages) {
            cout << "OpId #" << opId++ << ": " << msg << "." << endl;
        }
    }
    
    return 0;
}
