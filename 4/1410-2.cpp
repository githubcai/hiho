#include <cstdio>

typedef long long LL;

int main(){
    LL N; scanf("%lld", &N);
    LL cnt = 0, ans = 0;
    while(N > 0){
        if(N & 1 == 1){
            ++cnt;
        }else{
            if(cnt > 1){
                ans += 1;
                cnt = 1;
            }else if(cnt == 1){
                ans += 1;
                cnt = 0;
            }
        }
        N >>= 1;
    }
    if(cnt > 1){
        ans += 2;
    }else if(cnt == 1){
        ans += 1;
    }
    printf("%lld\n", ans);
    return 0;
}
