#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int NMAX = 100001, MMAX = 1000001;
struct Edge{
    int to, w, next;
};

struct Node{
    int v, w;
    friend bool operator<(const Node &a, const Node &b){
        return a.w > b.w;
    }
};

int head[NMAX], cnt, N, M;
Edge edge[MMAX];
bool vis[NMAX];

void init(){
    memset(head, -1, sizeof(head));
    memset(vis, 0, sizeof(vis));
    cnt = 0;
}

void addEdge(int from, int to, int w){
    edge[cnt].to = to;
    edge[cnt].w = w;
    edge[cnt].next = head[from];
    head[from] = cnt++;
}

void prim(){
    priority_queue<Node> que;
    Node now, next;
    int ret = 0;
    now.v = 1, now.w = 0;
    que.push(now);
    while(!que.empty()){
        now = que.top();
        que.pop();
        if(vis[now.v]) continue;
        ret += now.w;
        vis[now.v] = true;
        for(int i = head[now.v]; i != -1; i = edge[i].next){
            int v = edge[i].to;
            if(!vis[v]){
                next.v = v, next.w = edge[i].w;
                que.push(next);
            }
        }
    }
    printf("%d\n", ret);
}

int main(){
    init();
    scanf("%d%d", &N, &M);
    for(int i = 0; i < M; ++i){
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        addEdge(a, b, c);
        addEdge(b, a, c);
    }
    prim();
    return 0;
}
