#include <iostream>
#include <cstring>
#include <string>
#include <map>
using namespace std;

const int MAX = 100001;
struct Edge{
    int to, next, w;
};

Edge edge[MAX], query[MAX];
int ans[MAX], father[MAX], headE[MAX], headQ[MAX], N, M, cntE, cntQ;
bool vis[MAX];

void init(){
    memset(headE, -1, sizeof(headE));
    memset(headQ, -1, sizeof(headQ));
    memset(vis, 0, sizeof(vis));
    cntE = cntQ = 0;
}

void addEdge(int from, int to){
    edge[cntE].to = to;
    edge[cntE].next = headE[from];
    headE[from] = cntE++;
}

void addQuery(int from, int to, int w){
    query[cntQ].to = to;
    query[cntQ].next = headQ[from];
    query[cntQ].w = w;
    headQ[from] = cntQ++;
}

int find(int x){
    if(x == father[x]) return x;
    father[x] = find(father[x]);
    return father[x];
}

void tarjan(int u){
    vis[u] = true;
    father[u] = u;
    for(int i = headE[u]; i != -1; i = edge[i].next){
        int v = edge[i].to;
        tarjan(v);
        father[v] = u;
    }
    for(int i = headQ[u]; i != -1; i = query[i].next){
        int v = query[i].to;
        if(vis[v]){
            ans[query[i].w] = find(v);
        }
    }
}

int main(){
    init();
    map<string, int> ref;
    map<int, string> refR;
    int count = 1;
    cin >> N;
    string name1, name2;
    for(int i = 0; i < N; ++i){
        cin >> name1 >> name2;
        if(ref[name1] == 0){
            refR[count] = name1;
            ref[name1] = count++;
        }
        if(ref[name2] == 0){
            refR[count] = name2;
            ref[name2] = count++;
        }
        addEdge(ref[name1], ref[name2]);
    }
    cin >> M;
    for(int i = 0; i < M; ++i){
        cin >> name1 >> name2;
        addQuery(ref[name1], ref[name2], i);
        addQuery(ref[name2], ref[name1], i);
    }
    tarjan(1);
    for(int i = 0; i < M; ++i){
        cout << refR[ans[i]] << endl;
    }
    return 0;
}
