#include <cstdio>

typedef long long LL;
LL A[32][2] = {0};

int main(){
    int N; scanf("%d", &N);
    for(int i = 0; i < N; ++i){
        int a; scanf("%d", &a);
        for(int i = 0; i < 32; ++i){
            A[i][(a >> i) & 1] += 1;
        }
    }
    LL ans = 0;
    for(int i = 0; i < 32; ++i){
        ans += A[i][0] * A[i][1];
    }
    printf("%lld\n", ans);
    return 0;
}
