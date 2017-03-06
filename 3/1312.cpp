#include <cstdio>
#include <cmath>
#include <cstring>
#include <queue>
using namespace std;

const int ST = 46233, MAX = 362881, fac[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320};
struct Node{
    int st, f;
    friend bool operator<(const Node &a, const Node &b){
        return a.f > b.f;
    }
};

int num[9], ntemp[9], step[MAX]; // step为每个状态对应的最少步数,当第一次遇到一个新状态时,它的步数不一定是最小的
int dir[4][2] = {
    {-1, 0}, {0, 1}, {1, 0}, {0, -1}
};

int canto(int *nm){
    int st = 0;
    for(int i = 0; i < 9; ++i){
        int cnt = 0;
        for(int j = i + 1; j < 9; ++j){
            if(num[j] <= num[i]) ++cnt;
        }
        st += cnt * fac[8 - i];
    }
    return st;
}

void uncanto(int st){
    bool vis[9];
    memset(vis, 0, sizeof(vis));
    for(int i = 0; i < 9; ++i){
        int temp = st / fac[8 - i];
        st %= fac[8 - i];
        int cnt = 0;
        for(int j = 0; j < 9; ++j){
            if(!vis[j]){
                if(temp == cnt){
                    ntemp[i] = j;
                    vis[j] = true;
                    break;
                }
                cnt += 1;
            }
        }
    }
}

int getH(int *nm){
    int ret = 0;
    for(int i = 0; i < 9; ++i){
        if(nm[i] == 0) continue;
        int temp = nm[i];
        int x = i / 3, y = i % 3, tx = (temp - 1) / 3, ty = (temp - 1) % 3;
        ret += abs(x - tx) + abs(y - ty);
    }
    return ret;
}

int bfs(){
    priority_queue<Node> que;
    Node now, next;
    memset(step, -1, sizeof(step));
    now.st = canto(num);
    now.f = getH(num);
    step[now.st] = 0;
    que.push(now);
    while(!que.empty()){
        now = que.top();
        que.pop();
        if(now.st == ST) return step[now.st];
        uncanto(now.st);
        int maze[3][3], x, y;
        for(int i = 0; i < 9; ++i){
            int tx = i / 3, ty = i % 3;
            maze[tx][ty] = ntemp[i];
            if(ntemp[i] == 0) x = tx, y = ty;
        }
        for(int i = 0; i < 4; ++i){
            int tx = x + dir[i][0], ty = y + dir[i][1];
            if(tx >= 0 && tx < 3 && ty >= 0 && ty < 3){
                maze[x][y] = maze[tx][ty];
                maze[tx][ty] = 0;
                for(int j = 0; j < 3; ++j){
                    for(int k = 0; k < 3; ++k){
                        num[j * 3 + k] = maze[j][k];
                    }
                }
                next.st = canto(num);
                if(step[next.st] == -1 || step[next.st] > step[now.st] + 1){
                    step[next.st] = step[now.st] + 1;
                    next.f = step[next.st] + getH(num);
                    que.push(next);
                }
                maze[tx][ty] = maze[x][y];
                maze[x][y] = 0;
            }
        }
    }
    return -1;
}

bool check(){
    int ret = 0;
    for(int i = 0; i < 9; ++i){
        if(num[i] == 0) continue;
        for(int j = i + 1; j < 9; ++j){
            if(num[j] > 0 && num[i] > num[j]) ++ret;
        }
    }
    return ret % 2 == 0;
}

int main(){
    int T; scanf("%d", &T);
    while(T-- > 0){
        for(int i = 0; i < 9; ++i){
            scanf("%d", &num[i]);
        }
        if(check()){
            printf("%d\n", bfs());
        }else{
            printf("No Solution!\n");
        }
    }
    return 0;
}
