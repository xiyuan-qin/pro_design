#include <iostream>
#include <sstream>
using namespace std;

int main() {
    string line;
    while (getline(cin, line)) {  
        stringstream ss(line);
        int num, sum = 0;
        while (ss >> num) {  
            sum += num;
        }
        cout << sum << endl;  
    }
    return 0;
}
