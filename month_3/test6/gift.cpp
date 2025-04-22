#include<iostream>
#include<vector>
#include<unordered_set>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> a(n);
    
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    
    unordered_set<int> seen;
    int prefixLength = 0;
    
    // 从右向左扫描
    for(int i = n-1; i >= 0; --i) {
        if(seen.count(a[i])) {
            prefixLength = i + 1;
            break;
        }
        seen.insert(a[i]);
    }
    
    cout << prefixLength << endl;
    return 0;
}