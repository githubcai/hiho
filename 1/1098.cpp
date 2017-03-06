#include <cstdio>
#include <algorithm>
using namespace std;

const int NMAX = 100001, MMAX = 1000001;
struct Edge{
    int from, to, w;
};

Edge edge[MMAX];
int father[NMAX], N, M;

bool cmp(const Edge &a, const Edge &b){
    return a.w < b.w;
}

int find(int x){
    if(x == father[x]) return x;
    father[x] = find(father[x]);
    return father[x];
}

void kruscal(){
    for(int i = 1; i <= N; ++i){
        father[i] = i;
    }
    int result = 0;
    for(int i = 0; i < M; ++i){
        int ar = find(edge[i].from), br = find(edge[i].to);
        if(ar != br){
            result += edge[i].w;
            father[ar] = br;
        }
    }
    printf("%d\n", result);
}

int main(){
    scanf("%d%d", &N, &M);
    for(int i = 0; i < M; ++i){
        scanf("%d%d%d", &edge[i].from, &edge[i].to, &edge[i].w);
    }
    sort(edge, edge + M, cmp);
    kruscal();
    return 0;
}
