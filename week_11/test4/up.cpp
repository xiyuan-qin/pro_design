#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);

    int n;
    cin >> n;

    if (n == 0) {
        cout << 0 << endl;
        return 0;
    }

    vector<int> tails;
    int num;

    for (int i = 0; i < n; ++i) {
        cin >> num;

        auto it = lower_bound(tails.begin(), tails.end(), num);

        if (it == tails.end()) {
            tails.push_back(num);
        } else {
            *it = num;
        }
    }

    cout << tails.size() << endl;

    return 0;
}
