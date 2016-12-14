#include <cstdio>

const int MAX = 1001, INF = 1 << 29;
int N, maze[MAX][MAX];

void prim(){
    int dist[N], a[N];
    for(int i = 0; i < N; ++i){
        a[i] = i;
        dist[i] = maze[0][i];
    }
    int result = 0, mark = 0;
    for(int i = 0; i < N - 1; ++i){
        int tMin = INF;
        for(int j = i + 1; j < N; ++j){
            if(maze[a[i]][a[j]] < dist[a[j]]){
                dist[a[j]] = maze[a[i]][a[j]];
            }
            if(tMin > dist[a[j]]){
                tMin = dist[a[j]];
                mark = j;
            }
        }
        result += tMin;
        int t = a[mark];
        a[mark] = a[i + 1];
        a[i + 1] = t;
    }
    printf("%d\n", result);
}

int main(){
    scanf("%d", &N);
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            scanf("%d", &maze[i][j]);
        }
    }
    prim();
    return 0;
}
