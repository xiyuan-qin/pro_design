#include<iostream>
using namespace std;

int g1(int x){
    int a[11]{};
    int i = 0;
    while(x % 10 != 0){
        a[i] = x % 10;
        x /= 10;
        i++;
    }
}