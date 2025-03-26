#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
using namespace std;

#define ll long long
const ll inf = 1e18;

struct FileNode {
    bool isDir;            // 是否为目录
    ll ld, lr;             // 目录配额、后代配额
    ll sd, sr;             // 目录已用配额、后代已用配额
    map<string, FileNode*> children; // 子一级文件、目录
    ll fileSize;           // 文件大小
    
    FileNode() {           // 构造函数
        isDir = true;
        ld = lr = inf;
        sd = sr = 0;
        fileSize = 0;
    }
};

FileNode root;

// 根据路径分割文件名
vector<string> split(string &path) {
    stringstream ss(path);
    string part;
    vector<string> res;
    while (getline(ss, part, '/')) {
        res.push_back(part);
    }
    return res;
}

// 查找路径上的所有文件/目录
vector<FileNode*> findFile(vector<string> &fileNames) {
    vector<FileNode*> res;
    res.push_back(&root);
    for (int i = 1; i < fileNames.size(); ++i) {
        if (res.back()->isDir == false) break;  // 该文件非目录，无法进行操作
        if (res.back()->children.count(fileNames[i]) == 0) break;  // 目录下未找到指定文件/目录
        res.push_back(res.back()->children[fileNames[i]]);  // 找到了指定文件/目录，加入res
    }
    return res;
}

// 创建文件
bool create() {
    string path;
    ll fileSize;
    cin >> path >> fileSize;
    
    vector<string> fileNames = split(path);
    vector<FileNode*> filePtrs = findFile(fileNames);
    
    ll inc;
    if (fileNames.size() == filePtrs.size()) {  // 文件已存在
        if (filePtrs.back()->isDir) {
            return false;  // 是目录文件，创建失败
        } else {
            inc = fileSize - filePtrs.back()->fileSize;  // 替换文件，计算增量
        }
    } else {  // 需要创建目录或文件
        if (!filePtrs.back()->isDir) {
            return false;  // 中间路径有非目录，创建失败
        }
        inc = fileSize;  // 新建文件，增量为文件大小
    }
    
    // 检查配额限制
    // 后代配额检查
    for (int i = 0; i < filePtrs.size(); ++i) {
        if (filePtrs[i]->sr + inc > filePtrs[i]->lr) {
            return false;  // 配额检查失败
        }
    }
    
    // 目录配额检查
    int i = fileNames.size() - 2;
    if (i < filePtrs.size() && filePtrs[i]->sd + inc > filePtrs[i]->ld) {
        return false;  // 配额检查失败
    }
    
    // 补齐路径
    for (int i = filePtrs.size(); i < fileNames.size(); ++i) {
        FileNode* newNode = new FileNode();
        filePtrs.back()->children[fileNames[i]] = newNode;
        filePtrs.push_back(newNode);
    }
    
    // 创建文件基本信息写入
    filePtrs.back()->isDir = false;
    filePtrs.back()->fileSize = fileSize;
    
    // 修改祖先的后代已用配额
    for (auto &node : filePtrs) {
        node->sr += inc;
    }
    
    // 修改父亲的目录已用配额
    if (filePtrs.size() > 1) {
        filePtrs[filePtrs.size() - 2]->sd += inc;
    }
    
    return true;
}

// 移除文件
bool remove() {
    string path;
    cin >> path;
    
    vector<string> fileNames = split(path);
    vector<FileNode*> filePtrs = findFile(fileNames);
    
    if (filePtrs.size() != fileNames.size()) {
        return true;  // 文件不存在，视为成功
    }
    
    if (filePtrs.back()->isDir) {  // 目录文件
        // 对路径上的祖先后代已用配额减去该目录的所有后代已用配额
        for (auto &node : filePtrs) {
            node->sr -= filePtrs.back()->sr;
        }
    } else {  // 普通文件
        // 对路径上的祖先后代已用配额减去该文件大小
        for (auto &node : filePtrs) {
            node->sr -= filePtrs.back()->fileSize;
        }
        // 父亲的目录已用配额减去文件大小
        filePtrs[filePtrs.size() - 2]->sd -= filePtrs.back()->fileSize;
    }
    
    // 移除文件
    FileNode* nodeToDelete = filePtrs.back();
    filePtrs[filePtrs.size() - 2]->children.erase(fileNames.back());
    delete nodeToDelete;
    
    return true;
}

// 设置配额
bool quota() {
    string path;
    ll ld, lr;
    cin >> path >> ld >> lr;
    
    // 若配额值为0，表示不限制
    ld = (ld == 0) ? inf : ld;
    lr = (lr == 0) ? inf : lr;
    
    vector<string> fileNames = split(path);
    vector<FileNode*> filePtrs = findFile(fileNames);
    
    if (filePtrs.size() != fileNames.size()) {
        return false;  // 目录不存在
    }
    
    if (!filePtrs.back()->isDir) {
        return false;  // 不是目录文件
    }
    
    // 判断修改后目录的sd、sr是否超出新配额
    if (filePtrs.back()->sd > ld || filePtrs.back()->sr > lr) {
        return false;
    }
    
    // 完成配额修改
    filePtrs.back()->ld = ld;
    filePtrs.back()->lr = lr;
    
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    
    while (n--) {
        char op;
        cin >> op;
        bool res;
        
        switch (op) {
            case 'C': res = create(); break;
            case 'R': res = remove(); break;
            case 'Q': res = quota(); break;
        }
        
        if (res) cout << "Y\n";
        else cout << "N\n";
    }
    
    return 0;
}
