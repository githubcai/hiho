#include <cstdio>
#include <cstring>

typedef long long LL;
const int MAX = 101, SMAX = 100001, MOD = 1000000007;
LL A[MAX], dp[SMAX];

int main(){
    int N, S;
    scanf("%d%d", &N, &S);
    LL sum = 0;
    for(int i = 0; i < N; ++i){
        scanf("%lld", &A[i]);
        sum += A[i];
    }
    sum -= S;
    if(sum < 0 || sum % 2 == 1){
        printf("0\n");
    }else{
        sum /= 2;
        memset(dp, 0, sizeof(0));
        dp[0] = 1;
        for(int i = 0; i < N; ++i){
            for(int j = sum; j >= A[i]; --j){
                dp[j] = (dp[j] + dp[j - A[i]]) % MOD;
            }
        }
        printf("%lld\n", dp[sum]);
    }
    return 0;
}
