#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAX = 201, INF = 1 << 30;
int dp[MAX][MAX], N;

void init(){
    memset(dp, 0, sizeof(dp));
    for(int i = 1; i <= N; ++i){
        for(int j = i + 1; j <= N; ++j){
            dp[i][j] = dp[j][i] = INF;
        }
    }
}

int main(){
    scanf("%d", &N);
    init();
    for(int i = 1; i < N; ++i){
        for(int j = 1; j < N; ++j){
            if(i + j > N) continue;
            dp[j][i + j] = min(dp[j][i + j], dp[j + 1][i + j] + j);
            dp[j][i + j] = min(dp[j][i + j], dp[j][i + j - 1] + i + j);
            for(int k = j + 1; k < i + j; ++k){
                dp[j][i + j] = min(dp[j][i + j], k + max(dp[j][k - 1], dp[k + 1][i + j]));
            }
        }
    }
    printf("%d\n", dp[1][N]);
    return 0;
}
