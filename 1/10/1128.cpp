#include <cstdio>

int main(){
    int N, K;
    scanf("%d%d", &N, &K);
    long long num;
    int cnt = 1;
    bool flag = false;
    for(int i = 0; i < N; ++i){
        scanf("%lld", &num);
        if(K > num) cnt++;
        if(K == num) flag = true;
    }
    if(flag){
        printf("%d\n", cnt);
    }else{
        printf("-1\n");
    }
    return 0;
}
