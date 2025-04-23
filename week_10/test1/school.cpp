#include<iostream>
#include<vector>

using namespace std;

int red , yellow , green;

int main(){
    cin >> red >> yellow >> green;
    int n;
    cin >> n;
    vector<pair<int, int >> a(n);

    for(int i = 0; i < n; i++){
        cin >> a[i].first >> a[i].second;
    }

    int ans = 0;
    for(int i = 0; i < n; i++){
        int opt = a[i].first;
        int time = a[i].second;
        switch (opt)
        {
        case 0:
            ans += time;
            break;
        case 1:
            ans += time;
            break;
        case 2:
            ans += time;
            ans += red;
            break;
        case 3:
            break;
        default:
            break;
        }
    }

    cout << ans << endl;
    return 0;
}