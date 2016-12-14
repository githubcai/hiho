#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int NMAX = 100001, MMAX = 500001, MOD = 142857;
struct Edge{
    int to, next;
};

Edge edge[MMAX];
int cnt, head[NMAX], indegree[NMAX], virus[NMAX];
int N, M, K;

void init(){
    memset(indegree, 0, sizeof(indegree));
    memset(head, -1, sizeof(head));
    memset(virus, 0, sizeof(virus));
    cnt = 0;
}

void addEdge(int from, int to){
    edge[cnt].to = to;
    edge[cnt].next = head[from];
    head[from] = cnt++;
}

int topoSort(){
    queue<int> que;
    for(int i = 1; i <= N; ++i){
        if(indegree[i] == 0) que.push(i);
    }
    int ret = 0;
    while(!que.empty()){
        int now = que.front();
        que.pop();
        ret = (ret + virus[now]) % MOD;
        for(int i = head[now]; i != -1; i = edge[i].next){
            int v = edge[i].to;
            virus[v] = (virus[v] + virus[now]) % MOD;
            indegree[v] -= 1;
            if(indegree[v] == 0) que.push(v);
        }
    }
    return ret;
}

int main(){
    scanf("%d%d%d", &N, &M, &K);
    init();
    for(int i = 0; i < K; ++i){
        int a; scanf("%d", &a);
        virus[a] += 1;
    }
    for(int i = 0; i < M; ++i){
        int a, b; scanf("%d%d", &a, &b);
        addEdge(a, b);
        indegree[b] += 1;
    }
    printf("%d\n", topoSort());
    return 0;
}
