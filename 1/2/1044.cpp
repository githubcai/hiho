#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int SMAX = (1 << 10), NMAX = 1001;
int lmt, N, M, Q, dp[NMAX][SMAX], w[NMAX];
bool flag[SMAX];

void init(){
    lmt = (1 << M);
    memset(flag, 0, sizeof(bool) * lmt);
    for(int i = 0; i < lmt; ++i){
        int temp = i, cnt = 0;
        while(temp > 0){
            if(temp & 1) ++cnt;
            temp >>= 1;
        }
        if(cnt <= Q) flag[i] = true;
    }
}

int cal(){
    memset(dp, 0, sizeof(dp));
    for(int i = 1; i <= N; ++i){
        for(int j = 0; j < lmt; ++j){
            int st1 = ((j >> 1) | (1 << (M - 1))), st2 = (j >> 1);
            if(flag[st1]) dp[i][st1] = max(dp[i][st1], dp[i - 1][j] + w[i]);
            if(flag[st2]) dp[i][st2] = max(dp[i][st2], dp[i - 1][j]);
        }
    }
    int ret = 0;
    for(int i = 0; i < lmt; ++i){
        ret = max(ret, dp[N][i]);
    }
    return ret;
}

int main(){
    scanf("%d%d%d", &N, &M, &Q);
    init();
    for(int i = 1; i <= N; ++i){
        scanf("%d", &w[i]);
    }
    printf("%d\n", cal());
    return 0;
}
