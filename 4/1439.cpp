#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAX = 105, INF = 1 << 30;
struct Edge{
    int to, next;
};

Edge edge[MAX];
int head[MAX], cnt, N;
bool preRes[MAX];
char nodes[MAX];

void init(){
    memset(head, -1, sizeof(head));
    cnt = 0;
}

void addEdge(int from, int to){
    Edge e = {to, head[from]};
    edge[cnt] = e;
    head[from] = cnt++;
}

void pre(int u){
    if(head[u] == -1){
        preRes[u] = (nodes[u] == 'T') ? true : false;
        return;
    }
    if(nodes[u] == 'A'){
        preRes[u] = true;
    }else{
        preRes[u] = false;
    }
    for(int i = head[u]; i != -1; i = edge[i].next){
        int v = edge[i].to;
        pre(v);
        if(nodes[u] == 'A'){
            preRes[u] &= preRes[v];
        }else{
            preRes[u] |= preRes[v];
        }
    }
}

int dfs(int u){
    if(head[u] == -1) return -1;
    bool af = true, of = false;
    for(int i = head[u]; i != -1; i = edge[i].next){
        int v = edge[i].to;
        af &= preRes[v], of |= preRes[v];
    }
    int ret = 0;
    if(!af && of) return 1;
    if((nodes[u] == 'O' && af && of) || (nodes[u] == 'A' && !af && !of)) ret = 1;
    int temp = INF;
    for(int i = head[u]; i != -1; i = edge[i].next){
        int v = edge[i].to;
        int t = dfs(v);
        if(t != -1) temp = min(temp, t);
    }
    if(temp == INF) return -1;
    return ret + temp;
}

int main(){
    char input[6];
    int from;
    while(scanf("%d", &N) != EOF){
        init();
        for(int i = 1; i <= N; ++i){
            scanf("%d%s", &from, input);
            addEdge(from, i);
            nodes[i] = input[0];
        }
        pre(1);
        printf("%d\n", dfs(1));
    }
    return 0;
}
