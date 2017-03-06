#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

const int MAX = 51, NMAX = 1300;
struct Node{
    int x, y;
};

char maze[MAX][MAX];
int N, M, cnt, area[NMAX];
vector<int> store[NMAX];
bool vis[MAX][MAX];
int dir[4][2] = {
    {0, 1}, {0, -1}, {1, 0}, {-1, 0}
};

void dfs(int x, int y){
    for(int i = 0; i < 4; ++i){
        int tx = x + dir[i][0], ty = y + dir[i][1];
        if(tx >= 0 && tx < N && ty >= 0 && ty < M && !vis[tx][ty]){
            vis[tx][ty] = true;
            if(maze[tx][ty] == '#'){
                store[cnt].push_back(tx * M + ty);
                area[cnt] += 1;
                dfs(tx, ty);
            }
        }
    }
}

int main(){
    scanf("%d%d", &N, &M);
    for(int i = 0; i < N; ++i) scanf("%s", maze[i]);
    cnt = 0;
    for(int i = 0; i < NMAX; ++i) store[i].clear();
    memset(area, 0, sizeof(area));
    memset(vis, 0, sizeof(vis));
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < M; ++j){
            if(!vis[i][j]){
                vis[i][j] = true;
                if(maze[i][j] == '#'){
                    store[cnt].push_back(i * M + j);
                    area[cnt] += 1;
                    dfs(i, j);
                    ++cnt;
                }
            }
        }
    }
    int A = cnt, B, C;
    set<int> tSet;
    for(int i = 0; i < cnt; ++i) tSet.insert(area[i]);
    B = tSet.size();
    for(int i = 0; i < cnt; ++i) sort(store[i].begin(), store[i].end());
    bool flag[cnt];
    memset(flag, 0, sizeof(flag));
    C = 0;
    for(int i = 0; i < cnt; ++i){
        if(flag[i]) continue;
        flag[i] = true;
        for(int j = i + 1; j < cnt; ++j){
            if(store[i].size() == store[j].size()){
                int temp = 1;
                int sub = store[i][0] - store[j][0];
                while(temp < store[i].size()){
                    if(store[i][temp] - store[j][temp] != sub) break;
                    ++temp;
                }
                if(temp == store[i].size()) flag[j] = true;
            }
        }
        ++C;
    }
    printf("%d %d %d\n", A, B, C);
    return 0;
}
