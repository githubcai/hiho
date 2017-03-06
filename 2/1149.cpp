#include <cstdio>
#include <cstring>

const int MAX = 1001, MOD = 100007;
int dp[MAX][MAX];
char str[MAX];

int main(){
    int T; scanf("%d", &T);
    for(int t = 1; t <= T; ++t){
        scanf("%s", str);
        memset(dp, 0, sizeof(dp));
        int slen = strlen(str);
        for(int i = 0; i < slen; ++i) dp[i][i] = 1;
        for(int i = slen - 1; i >= 0; --i){
            for(int j = i + 1; j < slen; ++j){
                if(str[i] != str[j]){
                    dp[i][j] = ((dp[i + 1][j] + dp[i][j - 1] - dp[i + 1][j - 1]) % MOD + MOD) % MOD;
                }else{
                    dp[i][j] = (dp[i + 1][j] + dp[i][j - 1] + 1) % MOD;
                }
            }
        }
        printf("Case #%d: %d\n", t, dp[0][slen - 1]);
    }
    return 0;
}
