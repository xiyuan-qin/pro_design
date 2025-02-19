#include <iostream>
using namespace std;

int main() {
    string a, b;
    while (cin >> a >> b) {  
        int num1 = stoi(a, nullptr, 16);  
        int num2 = stoi(b, nullptr, 16);
        cout << num1 + num2 << endl;  
    }
    return 0;
}
