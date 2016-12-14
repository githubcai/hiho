#include <cstdio>
#include <cstring>

const int MAX = 10;
int filter[MAX][MAX], trace[MAX], cnt, N;
bool vis[MAX], know[MAX][MAX];

void dfs(int count){
    if(count >= 4){
        int temp = 0;
        for(int i = 0; i < count - 1; ++i){
            if(know[trace[i]][trace[i + 1]]) ++temp;
        }
        if(temp == N) ++cnt;
    }
    for(int i = 1; i <= 9; ++i){
        if(!vis[i] && vis[filter[i][trace[count - 1]]]){
            vis[i] = true;
            trace[count] = i;
            dfs(count + 1);
            vis[i] = false;
        }
    }
}

int main(){
    memset(filter, 0, sizeof(filter));
    filter[1][3] = filter[3][1] = 2;
    filter[4][6] = filter[6][4] = 5;
    filter[7][9] = filter[9][7] = 8;
    filter[1][7] = filter[7][1] = 4;
    filter[2][8] = filter[8][2] = 5;
    filter[3][9] = filter[9][3] = 6;
    filter[1][9] = filter[9][1] = 5;
    filter[3][7] = filter[7][3] = 5;

    int T; scanf("%d", &T);
    while(T-- > 0){
        memset(know, 0, sizeof(know));
        scanf("%d", &N);
        for(int i = 0; i < N; ++i){
            int a, b;
            scanf("%d%d", &a, &b);
            know[a][b] = know[b][a] = true;
        }

        memset(vis, 0, sizeof(vis));
        vis[0] = true;
        cnt = 0;
        dfs(0);
        printf("%d\n", cnt);
    }
    return 0;
}
