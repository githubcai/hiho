#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <map>
#include <algorithm>
using namespace std;

const int MAX = 100001;
int N, M;
struct Edge{
    int to, next;
};

Edge edge[MAX];
int head[MAX], cnt, total;
int depth[2 * MAX], trace[2 * MAX], first[MAX];
int minNum[MAX][20];

void init(){
    cnt = 0;
    total = 1;
    memset(head, -1, sizeof(head));
    memset(first, -1, sizeof(first));
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
        for(int i = 1; i <= num; ++i){
            if(i + (1 << j) - 1 <= num){
                minNum[i][j] = min(minNum[i][j - 1], minNum[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
}

int main(){
    init();
    cin >> N;
    map<string, int> ref;
    map<int, string> refR;
    string name1, name2;
    int count = 1;
    for(int i = 0; i < N; ++i){
        cin >> name1 >> name2;
        if(ref[name1] == 0){
            refR[count] = name1;
            ref[name1] = count++;
        }
        if(ref[name2] == 0){
            refR[count] = name2;
            ref[name2] = count++;
        }
        addEdge(ref[name1], ref[name2]);
    }
    dfs(1, 1);
    for(int i = 1; i <= total; ++i){
        minNum[i][0] = depth[i];
    }
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
