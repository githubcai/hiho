#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAX = 2101;
char strA[MAX], strB[MAX];
int dp[MAX][MAX], pdp[MAX][MAX];

void pre(int lenA, int lenB){
    memset(pdp, 0, sizeof(pdp));
    for(int i = 1; i <= lenA; ++i){
        for(int j = 1; j <= lenB; ++j){
            if(strA[i - 1] == strB[j - 1]){
                pdp[i][j] = pdp[i - 1][j - 1] + 1;
            }
        }
    }
}

int main(){
    scanf("%s%s", strA, strB);
    int lenA = strlen(strA), lenB = strlen(strB);
    pre(lenA, lenB);
    memset(dp, 0, sizeof(dp));
    for(int i = 1; i <= lenA; ++i){
        for(int j = 1; j <= lenB; ++j){
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            if(pdp[i][j] >= 3){
                for(int k = 3; k <= pdp[i][j]; ++k){
                    dp[i][j] = max(dp[i][j], dp[i - k][j - k] + k);
                }
            }
        }
    }
    printf("%d\n", dp[lenA][lenB]);
    return 0;
}
