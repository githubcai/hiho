#include <cstdio>
#include <cstdlib>
#include <ctime>

typedef unsigned long long LL;
const int TIMES = 100;

LL multi(LL a, LL b, LL mod){
    LL ans = 0;
    a %= mod;
    while(b > 0){
        if(b & 1) ans = (ans + a) % mod;
        b >>= 1;
        a = (a + a) % mod;
    }
    return ans;
}

LL quickMulti(LL a, LL n, LL mod){
    LL ans = 1;
    a %= mod;
    while(n > 0){
        if(n & 1) ans = multi(ans, a, mod);
        n >>= 1;
        a = multi(a, a, mod);
    }
    return ans;
}

bool MillerRabin(LL n){
    if(n == 2) return true;
    if(n < 2 || (n & 1) == 0) return false;
    
    LL m = n - 1;
    int k = 0;
    while((m & 1) == 0){
        ++k;
        m >>= 1;
    }
    for(int i = 0; i < TIMES; ++i){
        srand(time(NULL));
        LL a = rand() % (n - 2) + 2;
        LL x = quickMulti(a, m, n);
        for(int j = 0; j < k; ++j){
            LL y = multi(x, x, n);
            if(y == 1 && x != 1 && x != n - 1) return false;
            x = y;
        }
        if(x != 1) return false;
    }
    return true;
}

int main(){
    int T; scanf("%d", &T);
    while(T-- > 0){
        LL n; scanf("%llu", &n);
        if(MillerRabin(n)){
            printf("Yes\n");
        }else{
            printf("No\n");
        }
    }
    return 0;
}
