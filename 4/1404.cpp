#include <cstdio>

const int MAX = 15;
char maze[MAX][MAX + 1];
int dir[4][2] = {{0, 1}, {1, -1}, {1, 0}, {1, 1}};

bool check(int x, int y){
    if(x >= 0 && x < MAX && y >= 0 && y < MAX) return true;
    return false;
}

int main(){
    int T; scanf("%d", &T);
    while(T-- > 0){
        for(int i = 0; i < MAX; ++i){
            scanf("%s", maze[i]);
        }
        bool white = false, black = false, flag = false;
        for(int i = 0; i < MAX && !flag; ++i){
            for(int j = 0; j < MAX && !flag; ++j){
                if(maze[i][j] == '.') continue;
                for(int k = 0; k < 4 && !flag; ++k){
                    int x = i - dir[k][0], y = j - dir[k][1];
                    if(check(x, y) && maze[i][j] == maze[x][y]) continue;
                    x = i + dir[k][0], y = j + dir[k][1];
                    int cnt = 1;
                    while(check(x, y) && maze[i][j] == maze[x][y] && cnt < 5){
                        x += dir[k][0], y += dir[k][1];
                        cnt += 1;
                    }
                    if(cnt == 5){
                        if(maze[i][j] == 'B'){
                            black = true;
                        }else{
                            white = true;
                        }
                    }
                    if(white && black) flag = true;
                }
            }
        }
        if(flag){
            printf("Both\n");
        }else if(white){
            printf("White\n");
        }else if(black){
            printf("Black\n");
        }else{
            printf("None\n");
        }
    }
    return 0;
}
