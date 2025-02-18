#include<iostream>
#include<iomanip>
using namespace std;

int main(){
    int a , b;
    cin >> a >> b;

    int c = a -b ;
    double result = (double)c / a;
    cout <<fixed<< setprecision(3) << result*100 << endl;
    return 0;
}