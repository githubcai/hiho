#include <cstring>
#include <cstdio>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

const int MAX = 1000000, NMAX = 100005, MOD = 142857;
struct Edge{
    int to, next;
};

Edge edges[MAX];
int head[NMAX], cnt, N, M, indegree[NMAX];
unordered_map<int, vector<int>> iRef, oRef;

void addEdge(int from, int to){
    Edge e = {to, head[from]};
    edges[cnt] = e;
    head[from] = cnt++;
}

void init(){
    memset(head, -1, sizeof(head));
    memset(indegree, 0, sizeof(indegree));
    cnt = 0;
    iRef.clear();
    oRef.clear();
    scanf("%d%d", &N, &M);
    for(int i = 0; i < M; ++i){
        int temp; scanf("%d", &temp);
        oRef[0].push_back(temp);
    }
    for(int i = 1; i <= N; ++i){
        int temp; scanf("%d", &temp);
        iRef[temp].push_back(i);
        scanf("%d", &temp);
        for(int j = 0; j < temp; ++j){
            int t; scanf("%d", &t);
            oRef[i].push_back(t);
        }
    }
    queue<int> que;
    que.push(0);
    while(!que.empty()){
        int now = que.front();
        que.pop();
        vector<int> temp = oRef[now];
        for(int i = 0; i < temp.size(); ++i){
            auto iter = iRef.find(temp[i]);
            if(iter != iRef.end()){
                for(int j = 0; j < (iter->second).size(); ++j){
                    addEdge(now, (iter->second)[j]);
                    indegree[(iter->second)[j]] += 1;
                    que.push((iter->second)[j]);
                }
            }
        }
    }
}

int main(){
    int T; scanf("%d", &T);
    while(T-- > 0){
        init();
        vector<int> ans(N + 1, 0);
        queue<int> que;
        que.push(0);
        while(!que.empty()){
            int now = que.front();
            que.pop();
            for(int i = head[now]; i != -1; i = edges[i].next){
                int v = edges[i].to;
                indegree[v] -= 1;
                ans[v] = (ans[v] + 1) % MOD;
                if(indegree[v] == 0) que.push(v);
            }
        }
        printf("%d", ans[1]);
        for(int i = 2; i <= N; ++i){
            printf(" %d", ans[i]);
        }
        printf("\n");
    }
    return 0;
}
