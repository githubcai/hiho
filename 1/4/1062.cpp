#include <iostream>
#include <string>
#include <map>
#include <set>
using namespace std;

int main(){
    int N; cin >> N;
    string name1, name2;
    map<string, string> ref;
    for(int i = 0; i < N; ++i){
        cin >> name1 >> name2;
        ref[name2] = name1;
    }
    cin >> N;
    for(int i = 0; i < N; ++i){
        cin >> name1 >> name2;
        set<string> store;
        while(true){
            store.insert(name1);
            auto iter = ref.find(name1);
            if(iter == ref.end()) break;
            name1 = ref[name1];
        }
        bool flag = false;
        while(true){
            auto iters = store.find(name2);
            if(iters != store.end()){
                flag = true;
                break;
            }
            auto iterm = ref.find(name2);
            if(iterm == ref.end()) break;
            name2 = ref[name2];
        }
        if(flag){
            cout << name2 << endl;
        }else{
            cout << "-1" << endl;
        }
    }
    return 0;
}
