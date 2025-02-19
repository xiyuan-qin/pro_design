#include<iostream>
#include<iomanip>
#include<cmath>

using namespace std;

int main(){
    int a, b , H, M;
    cin >> a >> b >> H >> M;
    H = H % 12;
    double angle_minute = 6.0 * M;
    double angle_hour = 30.0 * H + 0.5 * M;

    //计算两个角度之间的差值

    double angle = abs(angle_hour - angle_minute);
    if(angle > 180){
        angle = 360 - angle;
    }
    double res = sqrt(a * a + b * b - 2 * a * b * cos(angle * M_PI / 180));
    cout<<fixed<<setprecision(10)<<res<<endl;
    return 0;
}
