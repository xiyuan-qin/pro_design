#include<iostream>
using namespace std;

int sum(int a, int b) {
    return a + b;
}

int main() {
    while(1) {
        int a, b;
        cin >> a >> b;
        if (a == 0 && b == 0) {
            break;
        }
        cout << sum(a, b) << endl;
    }
    return 0;
}   