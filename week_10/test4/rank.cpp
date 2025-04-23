#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>

using namespace std;

class BIT {
private:
    vector<int> tree;
public:
    BIT(int n) : tree(n + 1, 0) {}
    
    void update(int i, int val) {
        while (i < tree.size()) {
            tree[i] += val;
            i += (i & -i);
        }
    }
    
    int query(int i) {
        int sum = 0;
        while (i > 0) {
            sum += tree[i];
            i -= (i & -i);
        }
        return sum;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr); 
    
    int n;
    cin >> n;
    
    struct Program {
        int time, memory, index;
    };
    vector<Program> programs(n);
    
    for (int i = 0; i < n; i++) {
        cin >> programs[i].time >> programs[i].memory;
        programs[i].index = i;
    }
    

    sort(programs.begin(), programs.end(), [](const Program& a, const Program& b) {
        if (a.time != b.time)
            return a.time < b.time;
        return a.memory < b.memory;
    });
    
    vector<int> memory;
    memory.reserve(n);
    for (const auto& p : programs) {
        memory.push_back(p.memory);
    }
    
    sort(memory.begin(), memory.end());
    memory.erase(unique(memory.begin(), memory.end()), memory.end());
    
    unordered_map<int, int> mem_to_idx;
    for (int i = 0; i < memory.size(); i++) {
        mem_to_idx[memory[i]] = i + 1;
    }
    
    vector<int> score(n);
    BIT bit(memory.size());
    
    for (int i = 0; i < n; i++) {
        int pos = mem_to_idx[programs[i].memory];
        int dominated = bit.query(pos);
        score[programs[i].index] = dominated;
        bit.update(pos, 1);
    }
    
    vector<int> counts(n, 0);
    for (int i = 0; i < n; i++) {
        counts[score[i]]++;
    }
    
    for (int i = 0; i < n; i++) {
        cout << counts[i] << '\n'; 
    }
    
    return 0;
}