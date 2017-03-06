#include <cstdio>

int Josephus(int n, int k){
    if(n == 1) return 0;
    int ret = 0;
    if(n < k){
        for(int i = 2; i <= n; ++i) ret = (ret + k) % i;
        return ret;
    }
    ret = Josephus(n - n / k, k);
    if(ret < (n % k)){
        ret = ret - n % k + n;
    }else{
        ret = ret - n % k + (ret - n % k) / (k - 1);
    }
    return ret;
}

int main(){
    int T; scanf("%d", &T);
    while(T-- > 0){
        int N, K;
        scanf("%d%d", &N, &K);
        printf("%d\n", Josephus(N, K));
    }
    return 0;
}
