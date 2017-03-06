#include <iostream>
#include <string>
#include <map>
using namespace std;

const int MAX = 201;
int indegree[MAX] = {0}, outdegree[MAX] = {0};
string local[MAX];

int main(){
    int N; cin >> N;
    string st, ed;
    int cnt = 1;
    map<string, int> ref;
    for(int i = 0; i < N; ++i){
        cin >> st >> ed;
        if(ref[st] == 0){
            local[cnt] = st;
            ref[st] = cnt++;
        }
        if(ref[ed] == 0){
            local[cnt] = ed;
            ref[ed] = cnt++;
        }
        ++indegree[ref[ed]];
        ++outdegree[ref[st]];
    }
    int sres, eres;
    for(int i = 1; i < cnt; ++i){
        if(outdegree[i] - indegree[i] == 1) sres = i;
        if(indegree[i] - outdegree[i] == 1) eres = i;
    }
    cout << local[sres] << " " << local[eres] << endl;
    return 0;
}
