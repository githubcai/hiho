#include <iostream>
#include <string>
#include <set>
#include <map>
using namespace std;

int main(){
    string S; cin >> S;
    map<string, set<int>> store;
    for(int i = 0; i < S.size(); ++i){
        for(int j = 1; i + j <= S.size(); ++j){
            string temp = S.substr(i, j);
            set<int> tm = store[temp];
            tm.insert(i + j);
            store[temp] = tm;
        }
    }
    int N; cin >> N;
    while(N-- > 0){
        string str; cin >> str;
        set<int> temp = store[str];
        string l = str, s = str;
        for(auto iter = store.begin(); iter != store.end(); ++iter){
            if(iter->second == temp){
                if(l.size() < iter->first.size()) l = iter->first;
                if(s.size() > iter->first.size()) s = iter->first;
            }
        }
        cout << s << " " << l;
        for(auto iter = temp.begin(); iter != temp.end(); ++iter){
            cout << " " << *iter;
        }
        cout << endl;
    }
    return 0;
}
