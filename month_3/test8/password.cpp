#include<iostream>
#include<unordered_set>

using namespace std;

unordered_set<char> Upper = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
unordered_set<char> Lower = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
unordered_set<char> Digit = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};


int whatItIs(char c){
    if(Upper.count(c)){
        return 1;
    }else if(Lower.count(c)){
        return 0;
    }else if(Digit.count(c)){
        return 2;
    }
}

int main(){
    string password;
    cin >> password;

    if(password.size() < 6){
        cout << 0 << endl;
        return 0;
    }
    int power = 1;

    for(int i = 1; i < password.size(); i++){
        if(whatItIs(password[i]) == whatItIs(password[i - 1])){
            continue;
        }
        else{
            power++;
        }
    }
    cout << power << endl;
    return 0;

}