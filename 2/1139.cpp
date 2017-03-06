#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int NMAX = 10001, MMAX = 100001;
struct Edge{
    int to, w, next;
};

struct Node{
    int v, count;
};

Edge edge[2 * MMAX];
int head[NMAX], cnt, N, M, K, T;
bool vis[NMAX];

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

bool judge(int mid){
    queue<Node> que;
    memset(vis, 0, sizeof(vis));
    Node now = {1, 0}, next;
    que.push(now);
    vis[1] = true;
    while(!que.empty()){
        Node now = que.front();
        que.pop();
        if(now.count >= K) continue;
        for(int i = head[now.v]; i != -1; i = edge[i].next){
            int v = edge[i].to;
            if(!vis[v] && edge[i].w <= mid){
                if(v == T) return true;
                vis[v] = true;
                next.v = v, next.count = now.count + 1;
                que.push(next);
            }
        }
    }
    return false;
}

int main(){
    scanf("%d%d%d%d", &N, &M, &K, &T);
    init();
    int ans, left = 1, right = -1;
    for(int i = 0; i < M; ++i){
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        addEdge(a, b, c);
        addEdge(b, a, c);
        if(c > right) right = c;
    }
    while(left <= right){
        int mid = (left + right) / 2;
        if(judge(mid)){
            ans = mid;
            right = mid - 1;
        }else{
            left = mid + 1;
        }
    }
    printf("%d\n", ans);
    return 0;
}
