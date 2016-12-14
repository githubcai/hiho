#include <cstdio>
#include <cstring>

const int MAX = 101, INF = 1 << 29;
int dist[MAX][MAX], N, M;

int main(){
    memset(dist, 0, sizeof(dist));
    scanf("%d%d", &N, &M);
    for(int i = 1; i <= N; ++i){
        for(int j = i + 1; j <= N; ++j){
            dist[i][j] = dist[j][i] = INF;
        }
    }
    for(int i = 0; i < M; ++i){
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        if(dist[a][b] > c){
            dist[a][b] = dist[b][a] = c;
        }
    }
    for(int k = 1; k <= N; ++k){
        for(int i = 1; i <= N; ++i){
            for(int j = 1; j <= N; ++j){
                if(dist[i][j] > dist[i][k] + dist[k][j]){
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    for(int i = 1; i <= N; ++i){
        printf("%d", dist[i][1]);
        for(int j = 2; j <= N; ++j){
            printf(" %d", dist[i][j]);
        }
        printf("\n");
    }
    return 0;
}
