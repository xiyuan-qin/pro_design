#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

class Product {
public:
    int price;
    string cata;
    int num;
public:
    Product(int num, int price, string name) : num(num), price(price), cata(name) {}
    Product() : num(-1), price(0), cata("") {}
};

int main() {
    int n;
    cin >> n;
    Product bullon[n];

    for (int i = 0; i < n; i++) {
        int price;
        string str;
        cin >> price >> str;
        bullon[i] = Product(i + 1, price, str);
    }

    // 价格相同时按编号升序排序
    sort(bullon, bullon + n, [](const Product& a, const Product& b) {
        if (a.price != b.price) {
            return a.price < b.price;
        } else {
            return a.num < b.num;
        }
    });

    for (int i = 0; i < n; i++) {
        int qiqiu[10] = {0};
        for (char c : bullon[i].cata) {
            qiqiu[c - '0']++;
        }
        if (qiqiu[0] >= 2 && qiqiu[5] >= 1 && qiqiu[1] >= 1) {
            cout << bullon[i].num << endl;
            return 0;
        }
    }

    cout << 0 << endl;
    return 0;
}
