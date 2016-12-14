#include <cstdio>
#include <cstring>

const int MAX = 201;
int maze[MAX][MAX], res[MAX][MAX], N, M;
int dir[24][2] = {
    {-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
    {0, 1}, {1, -1}, {1, 0}, {1, 1},
    {-2, -2}, {-2, -1}, {-2, 0}, {-2, 1},
    {-2, 2}, {-1, -2}, {-1, 2}, {0, -2},
    {0, 2}, {1, -2}, {1, 2}, {2, -2},
    {2, -1}, {2, 0}, {2, 1}, {2, 2},
};

bool check(int x, int y){
    if(x >= 0 && x < N && y >= 0 && y < M) return true;
    return false;
}

int calUnknow(int x, int y){
    int cnt = 0;
    for(int i = 0; i < 8; ++i){
        int tx = x + dir[i][0], ty = y + dir[i][1];
        if(check(tx, ty) && maze[tx][ty] == -1) ++cnt;
    }
    return cnt;
}

void rule1(int x, int y){
    for(int i = 0; i < 8; ++i){
        int tx = x + dir[i][0], ty = y + dir[i][1];
        if(check(tx, ty) && maze[tx][ty] == -1) res[tx][ty] = -2;
    }
}

void rule2(int x, int y){
    if(maze[x][y] == calUnknow(x, y)){
        for(int i = 0; i < 8; ++i){
            int tx = x + dir[i][0], ty = y + dir[i][1];
            if(check(tx, ty) && maze[tx][ty] == -1) res[tx][ty] = -3;
        }
    }
}

bool isAdjacent(int x1, int y1, int x2, int y2){
    if(x1 - x2 > 1 || x1 - x2 < -1 || y1 - y2 > 1 || y1 - y2 < -1) return false;
    return true;
}

bool checkRef(int x1, int y1, int x2, int y2){
    for(int i = 0; i < 8; ++i){
        int tx = x2 + dir[i][0], ty = y2 + dir[i][1];
        if(check(tx, ty) && maze[tx][ty] == -1 && !isAdjacent(x1, y1, tx, ty)) return false;
    }
    return true;
}

void proc(int x1, int y1, int x2, int y2){
    for(int i = 0; i < 8; ++i){
        int tx = x1 + dir[i][0], ty = y1 + dir[i][1];
        if(check(tx, ty) && maze[tx][ty] == -1 && !isAdjacent(tx, ty, x2, y2)) res[tx][ty] = -3;
    }
}

void rule3(int x, int y){
    for(int i = 0; i < 24; ++i){
        int tx = x + dir[i][0], ty = y + dir[i][1];
        if(check(tx, ty) && maze[tx][ty] >= 0 && checkRef(x, y, tx, ty) && (maze[x][y] - maze[tx][ty] == calUnknow(x, y) - calUnknow(tx, ty))){
            proc(x, y, tx, ty);
        }
    }
}

int main(){
    int T; scanf("%d", &T);
    while(T-- > 0){
        scanf("%d%d", &N, &M);
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < M; ++j){
                scanf("%d", &maze[i][j]);
            }
        }
        memset(res, -1, sizeof(res));
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < M; ++j){
                if(maze[i][j] == 0){
                    rule1(i, j);
                }else if(maze[i][j] > 0){
                    rule2(i, j);
                    rule3(i, j);
                }
            }
        }
        int mine = 0, noMine = 0;
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < M; ++j){
                if(res[i][j] == -2){
                    ++noMine;
                }else if(res[i][j] == -3){
                    ++mine;
                }
            }
        }
        printf("%d %d\n", mine, noMine);
    }
    return 0;
}
