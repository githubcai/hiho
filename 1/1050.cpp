#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAX = 100001;
struct Edge{
    int to, next;
};

Edge edge[2 * MAX];
int head[MAX], cnt, N, first[MAX], second[MAX], res;

int init(){
    memset(head, -1, sizeof(head));
    memset(first, 0, sizeof(first));
    memset(second, 0, sizeof(second));
    cnt = res = 0;
}

void addEdge(int from, int to){
    Edge e = {to, head[from]};
    edge[cnt] = e;
    head[from] = cnt++;
}

void dfs(int u, int fa){
    for(int i = head[u]; i != -1; i = edge[i].next){
        int v = edge[i].to;
        if(v != fa){
            dfs(v, u);
            int temp = first[v] + 1;
            if(temp > first[u]) swap(first[u], temp);
            if(temp > second[u]) swap(second[u], temp);
        }
    }
    int temp = first[u] + second[u];
    if(temp > res) res = temp;
}

int main(){
    init();
    scanf("%d", &N);
    for(int i = 1; i < N; ++i){
        int a, b;
        scanf("%d%d", &a, &b);
        addEdge(a, b);
        addEdge(b, a);
    }
    dfs(1, -1);
    printf("%d\n", res);
    return 0;
}
