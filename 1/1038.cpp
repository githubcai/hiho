#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int NMAX = 501, MMAX = 100001;
struct Node{
    int need, value;
};

Node nodes[NMAX];
int N, M, dp[MMAX];

int main(){
    scanf("%d%d", &N, &M);
    for(int i = 0; i < N; ++i){
        scanf("%d%d", &nodes[i].need, &nodes[i].value);
    }
    memset(dp, 0, sizeof(dp));
    for(int i = 0; i < N; ++i){
        for(int j = M; j >= nodes[i].need; --j){
            dp[j] = max(dp[j], dp[j - nodes[i].need] + nodes[i].value);
        }
    }
    printf("%d\n", dp[M]);
    return 0;
}
