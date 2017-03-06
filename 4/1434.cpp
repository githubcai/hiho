#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>
using namespace std;

const int MAX = 101;
string file[MAX];

bool cmp(const string &a, const string &b){
    string atemps, atempn, btemps, btempn;
    for(int i = 0; i < a.size(); ++i){
        if(a[i] >= '0' && a[i] <= '9'){
            atempn += a[i];
        }else{
            atemps += a[i];
        }
    }
    for(int i = 0; i < b.size(); ++i){
        if(b[i] >= '0' && b[i] <= '9'){
            btempn += b[i];
        }else{
            btemps += b[i];
        }
    }
    if(atemps == btemps){
        stringstream ss; int at, bt;
        ss << atempn; ss >> at;
        ss.clear();
        ss << btempn; ss >> bt;
        return at < bt;
    }else{
        return atemps < btemps;
    }
}

int main(){
    int N; cin >> N;
    for(int i = 0; i < N; ++i){
        cin >> file[i];
    }
    sort(file, file + N, cmp);
    for(int i = 0; i < N; ++i){
        cout << file[i] << endl;
    }
    return 0;
}
