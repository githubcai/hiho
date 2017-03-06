#include <cstdio>
#include <cstring>

const int NMAX = 1001, MMAX = 5001;
struct Edge{
    int to, next;
};

Edge edge[2 * MMAX];
int N, M, cnt, head[NMAX], link[NMAX];
bool vis[NMAX];

void init(){
    memset(head, -1, sizeof(head));
    cnt = 0;
}

void addEdge(int from, int to){
    edge[cnt].to = to;
    edge[cnt].next = head[from];
    head[from] = cnt++;
}

bool findPath(int u){
    for(int i = head[u]; i != -1; i = edge[i].next){
        int v = edge[i].to;
        if(!vis[v]){
            vis[v] = true;
            if(link[v] == -1 || findPath(link[v])){
                link[v] = u;
                return true;
            }
        }
    }
    return false;
}

int hungary(){
    int ret = 0;
    memset(link, -1, sizeof(link));
    for(int i = 1; i <= N; ++i){
        memset(vis, 0, sizeof(vis));
        if(findPath(i)) ++ret;
    }
    return ret;
}

int main(){
    scanf("%d%d", &N, &M);
    init();
    for(int i = 0; i < M; ++i){
        int a, b; scanf("%d%d", &a, &b);
        addEdge(a, b);
        addEdge(b, a);
    }
    printf("%d\n", hungary() / 2);
    return 0;
}
