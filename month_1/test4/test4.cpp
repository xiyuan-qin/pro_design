#include<iostream>
#include<algorithm>

using namespace std;

int main()
{
    int n , k;
    cin >> n >> k;
    int *color = new int[n];
    for(int i = 0; i < n; i++)
    {
        cin >> color[i];
    }

    int days = 0;
    sort(color, color + n);
    for(int i = 0 ; i < n - 1 ; i++){
        if(color[i] == color[i + 1]){
            color[i] = color[i + 1] = -1;
            i = i + 1;
            days++;
        }
    }
    cout << days << endl;
    return 0;
}
