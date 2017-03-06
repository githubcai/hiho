#include <queue>
#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>
using namespace std;

const int NMAX = 100001;
struct Edge{
    int to, next, w;
};

struct Node{
    int x, y, ind;
};

Edge edges[4 * NMAX];
int head[NMAX], dist[NMAX], cnt, N;
Node nodes[NMAX];
bool vis[NMAX];

void init(){
    cnt = 0;
    memset(head, -1, sizeof(head));
}

void addEdge(int from, int to, int w){
    Edge e = {to, head[from], w};
    edges[cnt] = e;
    head[from] = cnt++;
}

bool cmpX(const Node &a, const Node &b){
    if(a.x == b.x) a.y < b.y;
    return a.x < b.x;
}

bool cmpY(const Node &a, const Node &b){
    if(a.y == b.y) a.x < b.x;
    return a.y < b.y;
}

void spfa(int st){
    for(int i = 0; i < N; ++i) dist[i] = INT_MAX;
    memset(vis, 0, sizeof(vis));
    queue<int> que;
    que.push(st);
    vis[st] = true;
    dist[st] = 0;
    while(!que.empty()){
        int now = que.front();
        que.pop();
        vis[now] = false;
        for(int i = head[now]; i != -1; i = edges[i].next){
            int v = edges[i].to;
            int temp = dist[now] + edges[i].w;
            if(temp < dist[v]){
                dist[v] = temp;
                if(!vis[v]){
                    vis[v] = true;
                    que.push(v);
                }
            }
        }
    }
}

int main(){
    scanf("%d", &N);
    for(int i = 0; i < N; ++i){
        scanf("%d%d", &nodes[i].x, &nodes[i].y);
        nodes[i].ind = i;
    }
    init();
    sort(nodes, nodes + N, cmpX);
    for(int i = 1; i < N; ++i){
        int ti = i - 1;
        while(i < N && nodes[i].x == nodes[ti].x){
            addEdge(nodes[i].ind, nodes[ti].ind, 0);
            addEdge(nodes[ti].ind, nodes[i].ind, 0);
            i += 1;
        }
        if(i < N){
            addEdge(nodes[i].ind, nodes[ti].ind, nodes[i].x - nodes[ti].x);
            addEdge(nodes[ti].ind, nodes[i].ind, nodes[i].x - nodes[ti].x);
        }
    }
    sort(nodes, nodes + N, cmpY);
    for(int i = 1; i < N; ++i){
        int ti = i - 1;
        while(i < N && nodes[i].y == nodes[ti].y){
            addEdge(nodes[i].ind, nodes[ti].ind, 0);
            addEdge(nodes[ti].ind, nodes[i].ind, 0);
            i += 1;
        }
        if(i < N){
            addEdge(nodes[i].ind, nodes[ti].ind, nodes[i].y - nodes[ti].y);
            addEdge(nodes[ti].ind, nodes[i].ind, nodes[i].y - nodes[ti].y);
        }
    }
    spfa(0);
    printf("%d\n", dist[N - 1]);
    return 0;
}
