#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int NMAX = 500, MMAX = 100001;
int N, M, need[NMAX], val[NMAX], dp[MMAX];

int main(){
    scanf("%d%d", &N, &M);
    for(int i = 0; i < N; ++i){
        scanf("%d%d", &need[i], &val[i]);
    }
    memset(dp, 0, sizeof(dp));
    for(int i = 0; i < N; ++i){
        for(int j = need[i]; j <= M; ++j){
            dp[j] = max(dp[j], dp[j - need[i]] + val[i]);
        }
    }
    int ans = 0;
    for(int i = 1; i <= M; ++i){
        if(ans < dp[i]) ans = dp[i];
    }
    printf("%d\n", ans);
    return 0;
}
