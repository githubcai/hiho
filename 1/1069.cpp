#include <iostream>
#include <string>
#include <cstring>
#include <unordered_map>
#include <cmath>
#include <algorithm>
using namespace std;

const int MAX = 100001;
struct Edge{
    int to, next;
};

Edge edge[MAX];
int head[MAX], cnt, total;
int depth[2 * MAX], trace[2 * MAX], first[MAX];
int N, M, minNum[MAX][20];

void init(){
    memset(head, -1, sizeof(head));
    memset(first, -1, sizeof(first));
    total = cnt = 0;
}

void addEdge(int from, int to){
    edge[cnt].to = to;
    edge[cnt].next = head[from];
    head[from] = cnt++;
}

void dfs(int u, int dept){
    if(first[u] == -1) first[u] = total;
    depth[total] = dept;
    trace[total++] = u;
    for(int i = head[u]; i != -1; i = edge[i].next){
        int v = edge[i].to;
        dfs(v, dept + 1);
        depth[total] = dept;
        trace[total++] = u;
    }
}

void RMQ(int num){
    for(int j = 1; j < 20; ++j){
        for(int i = 0; i < num; ++i){
            if(i + (1 << j) - 1 < num){
                minNum[i][j] = min(minNum[i][j - 1], minNum[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
}

int main(){
    unordered_map<string, int> ref;
    unordered_map<int, string> refR;
    cin >> N;
    string name1, name2;
    init();
    for(int i = 0; i < N; ++i){
        cin >> name1 >> name2;
        if(ref.find(name1) == ref.end()){
            refR[cnt] = name1;
            ref[name1] = cnt++;
        }
        if(ref.find(name2) == ref.end()){
            refR[cnt] = name2;
            ref[name2] = cnt++;
        }
        addEdge(ref[name1], ref[name2]);
    }
    dfs(0, 0);
    for(int i = 0; i < total; ++i) minNum[i][0] = depth[i];
    RMQ(total);
    cin >> M;
    for(int i = 0; i < M; ++i){
        cin >> name1 >> name2;
        int st, ed, t, t1 = first[ref[name1]], t2 = first[ref[name2]];
        if(t1 >= t2){
            st = t2, ed = t1;
            t = (int)(log(t1 - t2 + 1) / log(2.0));
        }else{
            st = t1, ed = t2;
            t = (int)(log(t2 - t1 + 1) / log(2.0));
        }
        int mn = min(minNum[st][t], minNum[ed - (1 << t) + 1][t]);
        for(int i = st; i <= ed; ++i){
            if(mn == depth[i]){
                cout << refR[trace[i]] << endl;
                break;
            }
        }
    }
    return 0;
}
