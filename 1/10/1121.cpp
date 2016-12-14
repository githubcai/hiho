#include <cstdio>
#include <cstring>

const int NMAX = 10001, MMAX = 40001;
struct Edge{
    int to, next;
};

Edge edge[2 * MMAX];
int N, M, cnt, head[NMAX], vis[NMAX];

void init(){
    cnt = 0;
    memset(head, -1, sizeof(head));
    memset(vis, -1, sizeof(vis));
}

void addEdge(int from, int to){
    edge[cnt].to = to;
    edge[cnt].next = head[from];
    head[from] = cnt++;
}

bool dfs(int u, int color){
    vis[u] = color;
    for(int i = head[u]; i != -1; i = edge[i].next){
        int v = edge[i].to;
        if(vis[v] == -1){
            if(!dfs(v, color ^ 1)) return false;
        }else{
            if((vis[u] ^ vis[v]) == 0) return false;
        }
    }
    return true;
}

int main(){
    int T; scanf("%d", &T);
    while(T-- > 0){
        scanf("%d%d", &N, &M);
        init();
        for(int i = 0; i < M; ++i){
            int a, b;
            scanf("%d%d", &a, &b);
            addEdge(a, b);
            addEdge(b, a);
        }
        bool flag = true;
        for(int i = 1; i <= N && flag; ++i){
            if(vis[i] == -1){
                if(!dfs(i, 1)) flag = false;
            }
        }
        if(flag){
            printf("Correct\n");
        }else{
            printf("Wrong\n");
        }
    }
    return 0;
}
