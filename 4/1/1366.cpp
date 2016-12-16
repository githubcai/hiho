#include <iostream>
#include <string>
#include <algorithm>
#include <set>
using namespace std;

int main(){
    int N; cin >> N;
    string str;
    set<string> store;
    int result = 0;
    for(int i = 0; i < N; ++i){
        cin >> str;
        string temp = str;
        reverse(str.begin(), str.end());
        auto iter = store.find(str);
        if(iter != store.end()){
            ++result;
        }else{
            store.insert(temp);
        }
    }
    cout << result << endl;
    return 0;
}
