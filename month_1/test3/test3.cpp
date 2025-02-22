#include<iostream>
#include<string>

using namespace std;

int light[] = {0, 0, 0};

int main()
{
    int n , result = 0;
    string str;

    cin >> n >> str;

    for(int i = 0 ; i < str.size(); i++){
        if(str[i] == 'R')
            light[0]++;
        else if(str[i] == 'G')
            light[1]++;
        else
            light[2]++;
    }

    while(light[0] > 0 && light[1] > 0 && light[2] > 0){
        light[0]--;
        light[1]--;
        light[2]--;
        result++;
    }


    cout<< result << endl;
    return 0;
}
