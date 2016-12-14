#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAX = 100;
int maze[MAX][MAX], n, dp[MAX];

int main(){
    scanf("%d", &n);
    for(int i = 0; i < n; ++i){
        for(int j = 0; j <= i; ++j){
            scanf("%d", &maze[i][j]);
        }
    }
    memset(dp, 0, sizeof(dp));
    dp[0] = maze[0][0];
    for(int i = 1; i < n; ++i){
        for(int j = i; j > 0; --j){
            dp[j] = max(dp[j], dp[j - 1]) + maze[i][j];
        }
        dp[0] += maze[i][0];
    }
    int ans = 0;
    for(int i = 0; i < n; ++i){
        if(ans < dp[i]) ans = dp[i];
    }
    printf("%d\n", ans);
    return 0;
}
