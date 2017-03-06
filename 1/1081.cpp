#include <cstdio>
#include <cstring>

const int MAX = 1001, INF = 0x7ffffff;
int maze[MAX][MAX], dist[MAX], verNum, M, S, T;
bool vis[MAX];

void Dijkstra(int v){
    memset(vis, 0, sizeof(vis));
    for(int i = 1; i <= verNum; ++i){
        dist[i] = maze[v][i];
    }
    vis[v] = true;
    for(int i = 1; i < verNum; ++i){
        int tMin = INF, mark;
        for(int j = 1; j <= verNum; ++j){
            if(!vis[j] && dist[j] < tMin){
                mark = j;
                tMin = dist[j];
            }
        }
        vis[mark] = true;
        for(int j = 1; j <= verNum; ++j){
            if(!vis[j] && dist[j] > dist[mark] + maze[mark][j]){
                dist[j] = dist[mark] + maze[mark][j];
            }
        }
    }
}

int main(){
    scanf("%d%d%d%d", &verNum, &M, &S, &T);
    memset(maze, 0, sizeof(maze));
    for(int i = 1; i <= verNum; ++i){
        for(int j = i + 1; j <= verNum; ++j){
            maze[i][j] = maze[j][i] = INF;
        }
    }
    for(int i = 0; i < M; ++i){
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        if(maze[a][b] > c){
            maze[a][b] = maze[b][a] = c;
        }
    }
    Dijkstra(S);
    printf("%d\n", dist[T]);
    return 0;
}
