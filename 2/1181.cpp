#include <cstdio>
#include <cstring>

const int NMAX = 1001, MMAX = 5005;
struct Edge{
    int to, next, flag;
};

Edge edge[2 * MMAX];
int head[NMAX], degree[NMAX], path[MMAX], cnt, N, M, pcnt;
bool vis[MMAX];

void init(){
    memset(head, -1, sizeof(head));
    memset(vis, 0, sizeof(vis));
    memset(degree, 0, sizeof(degree));
    cnt = pcnt = 0;
}

void addEdge(int from, int to, int flag){
    edge[cnt].flag = flag;
    edge[cnt].to = to;
    edge[cnt].next = head[from];
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
    scanf("%d%d", &N, &M);
    init();
    for(int i = 0; i < M; ++i){
        int a, b;
        scanf("%d%d", &a, &b);
        addEdge(a, b, i);
        addEdge(b, a, i);
        ++degree[a], ++degree[b];
    }
    int start = 1;
    for(int i = 1; i <= N; ++i){
        if(degree[i] % 2 == 1){
            start = i;
            break;
        }
    }
    dfs(start);
    printf("%d", path[0]);
    for(int i = 1; i < pcnt; ++i){
        printf(" %d", path[i]);
    }
    printf("\n");
    return 0;
}
