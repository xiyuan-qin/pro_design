#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main(){
    int num_of_persons, end_num;
    cin >> num_of_persons >> end_num;

    vector<int> claps(num_of_persons, 0);

    for(int i = 1; i <= end_num; i++){
        if(i % 7 == 0 || to_string(i).find('7') != string::npos){
            claps[(i-1) % num_of_persons]++;
        }
    }
    
    for(int i = 0; i < num_of_persons; i++){
        cout << claps[i] << " ";
    }
    cout << endl;
    
    return 0;
}