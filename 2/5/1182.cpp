#include <cstdio>
#include <cstring>

const int NMAX = 1 << 14, MMAX = (1 << 15) + 10;
struct Edge{
    int to, next, flag;
};

Edge edge[MMAX];
int N, head[NMAX], cnt, path[MMAX], pcnt;
bool vis[MMAX];

void init(){
    memset(head, -1, sizeof(head));
    memset(vis, 0, sizeof(vis));
    pcnt = cnt = 0;
}

void addEdge(int from, int to, int flag){
    edge[cnt].to = to;
    edge[cnt].next = head[from];
    edge[cnt].flag = flag;
    head[from] = cnt++;
}

void dfs(int u){
    for(int i = head[u]; i != -1; i = edge[i].next){
        int v = edge[i].to, flag = edge[i].flag;
        if(!vis[flag]){
            vis[flag] = true;
            dfs(v);
        }
    }
    path[pcnt++] = u;
}

int main(){
    scanf("%d", &N);
    init();
    int lmt = 1 << N;
    for(int i = 0; i < lmt; ++i){
        int from = (i >> 1), to = i & ((1 << (N - 1)) - 1);
        addEdge(from, to, i);
    }
    dfs(0);
    for(int i = 0; i < pcnt - 1; ++i){
        printf("%d", path[i] & 1);
    }
    printf("\n");
    return 0;
}
