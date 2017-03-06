#include <cstdio>
#include <cstring>

const int MAX = 3;
int maze[MAX][MAX], temp[MAX][MAX], res[MAX][MAX], cnt = 0;
bool flag[10];

void dfs(int n){
    if(cnt > 2) return;
    if(n == 9){
        if(temp[0][0] + temp[0][1] + temp[0][2] == 15 &&
            temp[1][0] + temp[1][1] + temp[1][2] == 15 &&
            temp[2][0] + temp[2][1] + temp[2][2] == 15 &&
            temp[0][0] + temp[1][0] + temp[2][0] == 15 &&
            temp[0][1] + temp[1][1] + temp[2][1] == 15 &&
            temp[0][2] + temp[1][2] + temp[2][2] == 15 &&
            temp[0][0] + temp[1][1] + temp[2][2] == 15 &&
            temp[0][2] + temp[1][1] + temp[2][0] == 15){
            ++cnt;
            memcpy(res, temp, sizeof(temp));
        }
        return;
    }
    int x = n / 3, y = n % 3;
    if(maze[x][y] != 0){
        temp[x][y] = maze[x][y];
        dfs(n + 1);
    }else{
        for(int i = 1; i <= 9; ++i){
            if(flag[i]) continue;
            flag[i] = true;
            temp[x][y] = i;
            dfs(n + 1);
            flag[i] = false;
        }
    }
}

int main(){
    memset(flag, 0, sizeof(flag));
    for(int i = 0; i < MAX; ++i){
        for(int j = 0; j < MAX; ++j){
            scanf("%d", &maze[i][j]);
            flag[maze[i][j]] = true;
        }
    }
    maze[1][1] = 5;
    flag[5] = true;
    cnt = 0;
    dfs(0);
    if(cnt >= 2){
        printf("Too Many\n");
    }else{
        for(int i = 0; i < 3; ++i){
            printf("%d", res[i][0]);
            for(int j = 1; j < 3; ++j){
                printf(" %d", res[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}
