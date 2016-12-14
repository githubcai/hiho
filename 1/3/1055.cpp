#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAX = 101;
struct Edge{
    int to, next;
};

Edge edge[2 * MAX];
int val[MAX], head[MAX], cnt, N, M, dp[MAX][MAX];

void addEdge(int from, int to){
    Edge e = {to, head[from]};
    edge[cnt] = e;
    head[from] = cnt++;
}

void dfs(int u, int fa){
    dp[u][1] = val[u];
    for(int i = head[u]; i != -1; i = edge[i].next){
        int v = edge[i].to;
        if(v == fa) continue;
        dfs(v, u);
        for(int j = M; j >= 2; --j){
            for(int k = 1; k < j; ++k){
                dp[u][j] = max(dp[u][j], dp[u][j - k] + dp[v][k]);
            }
        }
    }
}

int main(){
    memset(head, -1, sizeof(head));
    cnt = 0;
    scanf("%d%d", &N, &M);
    for(int i = 1; i <= N; ++i){
        scanf("%d", &val[i]);
    }
    for(int i = 1; i < N; ++i){
        int a, b;
        scanf("%d%d", &a, &b);
        addEdge(a, b);
        addEdge(b, a);
    }
    memset(dp, 0, sizeof(dp));
    dfs(1, -1);
    printf("%d\n", dp[1][M]);
    return 0;
}
