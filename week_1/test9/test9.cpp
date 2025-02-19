#include<iostream>
using namespace std;

int sum(int a, int b) {
    return a + b;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        cout << sum(a, b) << endl;
    }
    return 0;
}   