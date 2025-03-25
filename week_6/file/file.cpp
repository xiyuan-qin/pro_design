#include<iostream>
#include<map>
#include<vector>
#include<string>
#include<sstream>

using namespace std;

class File{
public:
    bool isDir;

    long long LD , LR;// 给定配额
    int SD , SR;// 实际配额

    map<string, File> children;// 节点之后的孩子

    long long fileSize;

    File(){
        LD = LR = 1e9;
        SD = SR = 0;
        fileSize = 0;
        isDir = true;
    }

}root;

vector<string> nameList;
vector<File*> nodeList;

bool create(){
    int fileSize;
    cin >> fileSize;

    int inc = fileSize;

    auto lastNode = nodeList.back();

    if(nameList.size() == nodeList.size()){
        if(lastNode->isDir){
            return false;
        }
        inc = fileSize - lastNode->fileSize;
    }
    else{
        if(!lastNode->isDir){
            return false;
        }
    }

    for(int i = 0 ; i < nodeList.size(); i++){
        if(nodeList[i]->SR + inc > nodeList[i]->LR){
            return false;
        }

        if(i == nodeList.size() - 2){
            if(nodeList[i]->SD + inc > nodeList[i]->LD){
                return false;
            }
        }
    }
    for(int i = nodeList.size(); i < nameList.size(); i--){
       nodeList.push_back(&nodeList.back()->children[nameList[i]]);
    }
    change_quota(inc);

    nodeList.back()->fileSize = fileSize;
    nodeList.back()->isDir = false;
    return true;
        
}

void change_quota(int inc, bool isFile = true){
    for(int i = 0; i < nodeList.size(); i++){
        nodeList[i]->SR += inc;
        if(i == nodeList.size() - 2 && isFile){
            nodeList[i]->SD += inc;
        }
    }
}

void upd_path(){
    nameList.clear();
    nodeList.clear();

    string path;
    cin >> path;

    string cur;

    stringstream ss(path);
    while(getline(ss, cur, '/')){
        nameList.push_back(cur);
    }

    File *f = &root;
    nodeList.push_back(f);

    for(int i = 1; i < nameList.size(); i++){

        string &cur_name = nameList[i];
        if(!f->isDir || f->children.count(cur_name) == 0){
            break;
        }

        f = &f->children[cur_name];
        nodeList.push_back(f);
    }

}

bool remove(){
    if(nameList.size() != nodeList.size() ){
        return true;
    }

    auto lastNode = nodeList.back();
    if(lastNode->isDir){
        change_quota(-lastNode->SR, false);
    }
    else{
        change_quota(-lastNode->fileSize);
    }

    nodeList[nodeList.size() - 2]->children.erase(nameList.back());
    return true;
}


bool quota(){//修改
    int LD, LR;
    cin >> LD >> LR;

    if(LD == 0) LD = 1e9;

    if(LR == 0) LR = 1e9;

    if(nameList.size() != nodeList.size()){
        return false;
    }

    auto lastNode = nodeList.back();


    if(!lastNode->isDir) return false;

    if(lastNode->SD > LD || lastNode->SR > LR) return false;

    lastNode->LD = LD;
    lastNode->LR = LR;

    return true;
}

int main(){
    int n ;
    cin >> n;
    while(n--){
        char op;
        cin >> op;
        bool is_success = false;

        upd_path();

        if(op == 'C') is_success = create();
        if(op == 'R') is_success = remove();
        if(op == 'Q') is_success = quota();

        if(is_success) cout << "Y" << endl;
        else cout << "N" << endl;
    }
}