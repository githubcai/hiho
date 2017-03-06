#include <cstdio>
#include <cstring>

const int SMAX = 1 << 5, MOD = 1000000007;
int dp[2][SMAX], N, M, lmt;
bool flag[SMAX];

void check(){
    lmt = (1 << M);
    memset(flag, 0, sizeof(bool) * lmt);
    memset(dp[0], 0, sizeof(dp[0]));
    for(int i = 0; i < lmt; ++i){
        int temp = i;
        bool tflag = true;
        while(temp > 0){
            if(temp & 1){
                temp >>= 1;
                if((temp & 1) == 0){
                    tflag = false;
                    break;
                }
            }
            temp >>= 1;
        }
        if(tflag){
            flag[i] = true;
            dp[0][i] = 1;
        }
    }
}

int cal(){
    int index = 0;
    for(int i = 1; i < N; ++i){
        index ^= 1;
        memset(dp[index], 0, sizeof(dp[index]));
        for(int j = 0; j < lmt; ++j){
            for(int k = 0; k < lmt; ++k){
                if((j | k) == (lmt - 1) && flag[j & k]){
                    dp[index][j] = (dp[index][j] + dp[index ^ 1][k]) % MOD;
                }
            }
        }
    }
    return dp[index][lmt - 1];
}

int main(){
    scanf("%d%d", &N, &M);
    check();
    printf("%d\n", cal());
    return 0;
}
