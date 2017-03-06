#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int MAX = 100001;
struct Edge{
    int to, next;
};

Edge edge[MAX];
int head[MAX], cnt, indegree[MAX];
int N, M;

void init(){
    memset(head, -1, sizeof(head));
    memset(indegree, 0, sizeof(indegree));
    cnt = 0;
}

void addEdge(int from, int to){
    edge[cnt].to = to;
    edge[cnt].next = head[from];
    head[from] = cnt++;
}

bool topoSort(){
    queue<int> que;
    for(int i = 1; i <= N; ++i){
        if(indegree[i] == 0) que.push(i);
    }
    while(!que.empty()){
        int now = que.front();
        que.pop();
        for(int i = head[now]; i != -1; i = edge[i].next){
            int v = edge[i].to;
            --indegree[v];
            if(indegree[v] == 0) que.push(v);
        }
    }
    for(int i = 1; i <= N; ++i){
        if(indegree[i] != 0) return true;
    }
    return false;
}

int main(){
    int T; scanf("%d", &T);
    while(T-- > 0){
        init();
        scanf("%d%d", &N, &M);
        for(int i = 0; i < M; ++i){
            int u, v;
            scanf("%d%d", &u, &v);
            addEdge(u, v);
            ++indegree[v];
        }
        if(topoSort()){
            printf("YES\n");
        }else{
            printf("NO\n");
        }
    }
    return 0;
}
