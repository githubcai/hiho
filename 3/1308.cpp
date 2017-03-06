#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int MAX = 1 << 18;
struct Point{
    int x, y;
};

struct Node{
    int st, step;
};

bool vis[MAX];
int dir[8][2] = {
    {-2, -1}, {-1, -2}, {1, -2}, {2, -1},
    {-2, 1}, {-1, 2}, {1, 2}, {2, 1}
};

bool check(int st){
    if((st & 0x3f) == ((st >> 6) & 0x3f) && (st & 0x3f) == ((st >> 12) & 0x3f)) return true;
    return false;
}

int bfs(int st){
    queue<Node> que;
    memset(vis, 0, sizeof(vis));
    Node now, next;
    now.st = st, now.step = 0;
    vis[st] = true;
    que.push(now);
    while(!que.empty()){
        now = que.front();
        que.pop();
        if(check(now.st)) return now.step;
        Point pnow[3];
        for(int i = 2; i >= 0; --i){
            int temp = (now.st & 0x3f);
            pnow[i].x = (temp >> 3);
            pnow[i].y = (temp & 7);
            now.st >>= 6;
        }
        next.step = now.step + 1;
        for(int i = 0; i < 3; ++i){
            int tx = pnow[i].x, ty = pnow[i].y;
            for(int j = 0; j < 8; ++j){
                pnow[i].x = tx + dir[j][0], pnow[i].y = ty + dir[j][1];
                if(pnow[i].x >= 0 && pnow[i].x < 8 && pnow[i].y >= 0 && pnow[i].y < 8){
                    next.st = 0;
                    for(int k = 0; k < 3; ++k){
                        next.st = (next.st << 3) | pnow[k].x;
                        next.st = (next.st << 3) | pnow[k].y;
                    }
                    if(!vis[next.st]){
                        vis[next.st] = true;
                        que.push(next);
                    }
                }
            }
            pnow[i].x = tx, pnow[i].y = ty;
        }
    }
    return -1;
}


int main(){
    int T; scanf("%d", &T);
    while(T-- > 0){
        int st = 0; char temp[3];
        for(int i = 0; i < 3; ++i){
            scanf("%s", temp);
            st = (st << 3) | (temp[0] - 'A');
            st = (st << 3) | (temp[1] - '1');
        }
        printf("%d\n", bfs(st));
    }
    return 0;
}
