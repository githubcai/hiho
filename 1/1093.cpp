#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int NMAX = 100001, MMAX = 1000001, INF = 0x7ffffff;
struct Edge{
    int to, next, w;
};

Edge edge[MMAX];
int head[NMAX], cnt, dist[NMAX];
bool vis[NMAX];
int N, M, S, T;

void init(){
    memset(head, -1, sizeof(head));
    cnt = 0;
}

void addEdge(int from, int to, int w){
    edge[cnt].to = to;
    edge[cnt].w = w;
    edge[cnt].next = head[from];
    head[from] = cnt++;
}

void spfa(int s){
    queue<int> que;
    for(int i = 1; i <= N; ++i) dist[i] = INF;
    memset(vis, 0, sizeof(vis));
    que.push(s);
    dist[s] = 0;
    vis[s] = true;
    while(!que.empty()){
        int u = que.front();
        que.pop();
        vis[u] = false;
        for(int i = head[u]; i != -1; i = edge[i].next){
            int v= edge[i].to;
            if(dist[v] > dist[u] + edge[i].w){
                dist[v] = dist[u] + edge[i].w;
                if(!vis[v]){
                    vis[v] = true;
                    que.push(v);
                }
            }
        }
    }
}

int main(){
    init();
    scanf("%d%d%d%d", &N, &M, &S, &T);
    for(int i = 0; i < M; ++i){
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        addEdge(a, b, c);
        addEdge(b, a, c);
    }
    spfa(S);
    printf("%d\n", dist[T]);
    return 0;
}
