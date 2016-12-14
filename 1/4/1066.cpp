#include <string>
#include <iostream>
#include <map>
using namespace std;

const int MAX = 100001;
int N, father[MAX];;

void init(){
    for(int i = 1; i <= N; ++i){
        father[i] = i;
    }
}

int find(int x){
    if(x == father[x]) return x;
    father[x] = find(father[x]);
    return father[x];
}

void merge(int a, int b){
    int ar = find(a), br = find(b);
    if(ar != br) father[ar] = br;
}

int main(){
    cin >> N;
    init();
    int cnt = 1, oper;
    map<string, int> store;
    string p1, p2;
    for(int i = 0; i < N; ++i){
        cin >> oper >> p1 >> p2;
        if(store[p1] == 0) store[p1] = cnt++;
        if(store[p2] == 0) store[p2] = cnt++;
        if(oper == 1){
            if(find(store[p1]) == find(store[p2])){
                cout << "yes" << endl;
            }else{
                cout << "no" << endl;
            }
        }else{
            merge(store[p1], store[p2]);
        }
    }
    return 0;
}
