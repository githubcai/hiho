#include <cstdio>
#include <bitset>
using namespace std;

const int MAX = 101;
struct Edge{
    int to, next;
};

bitset<MAX> reach[MAX];
Edge edge[2 * MAX];
int num, cnt, head[MAX], must[MAX], N, M;
bool flag, vis[MAX];

void init(){
    for(int i = 1; i <= N; ++i){
        reach[i].reset();
        head[i] = -1;
        vis[i] = false;
    }
    num = cnt = 0;
    flag = false;
}

void addEdge(int from, int to){
    Edge e = {to, head[from]};
    edge[cnt] = e;
    head[from] = cnt++;
}

void pre(int u, int fa){
    for(int i = head[u]; i != -1; i = edge[i].next){
        int v = edge[i].to;
        if(v != fa){
            pre(v, u);
            reach[u] |= reach[v];
        }
    }
    reach[u][u] = 1;
}

void dfs(int u, int fa){
    if(flag) return;
    if(u == must[num]) ++num;
    if(num == M){
        flag = true;
        return;
    }
    while(num < M){
        int temp = num;
        for(int i = head[u]; i != -1; i = edge[i].next){
            int v = edge[i].to;
            if(!vis[v] && reach[v][must[num]] && v != fa){
                vis[v] = true;
                dfs(v, u);
            }
        }
        if(temp == num) break;
    }
}

int main(){
    int T; scanf("%d", &T);
    while(T-- > 0){
        scanf("%d", &N);
        init();
        for(int i = 1; i < N; ++i){
            int a, b;
            scanf("%d%d", &a, &b);
            addEdge(a, b);
            addEdge(b, a);
        }
        pre(1, -1);
        scanf("%d", &M);
        for(int i = 0; i < M; ++i){
            scanf("%d", &must[i]);
        }
        dfs(1, -1);
        if(flag){
            printf("YES\n");
        }else{
            printf("NO\n");
        }
    }
    return 0;
}
