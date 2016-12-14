#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int NMAX = 501, MMAX = 100001;
int dp[MMAX], N, M, need[NMAX], value[NMAX];

int main(){
    scanf("%d%d", &N, &M);
    for(int i = 0; i < N; ++i){
        scanf("%d%d", &need[i], &value[i]);
    }
    memset(dp, 0, sizeof(MMAX));
    for(int i = 0; i < N; ++i){
        for(int j = M; j >= need[i]; --j){
            dp[j] = max(dp[j], dp[j - need[i]] + value[i]);
        }
    }
    int ans = 0;
    for(int i = 1; i < M; ++i){
        if(ans < dp[i]) ans = dp[i];
    }
    printf("%d\n", ans);
    return 0;
}
