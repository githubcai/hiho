#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int NMAX = 100001, MMAX = 500001;
struct Edge{
    int to, next;
};

Edge edge[MMAX];
int head[NMAX], cnt, indegree[NMAX], N, M;

void init(){
    memset(indegree, 0, sizeof(indegree));
    memset(head, -1, sizeof(head));
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
            indegree[v] -= 1;
            if(indegree[v] == 0) que.push(v);
        }
    }
    for(int i = 1; i <= N; ++i){
        if(indegree[i] != 0) return false;
    }
    return true;
}

int main(){
    int T; scanf("%d", &T);
    while(T-- > 0){
        init();
        scanf("%d%d", &N, &M);
        for(int i = 0; i < M; ++i){
            int a, b; scanf("%d%d", &a, &b);
            addEdge(a, b);
            indegree[b] += 1;
        }
        if(topoSort()){
            printf("Correct\n");
        }else{
            printf("Wrong\n");
        }
    }
    return 0;
}
