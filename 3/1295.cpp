#include <cstdio>
#include <cstring>

const int MAX = 1000001;
int N, cnt, prime[MAX];
bool flag[MAX];

void init(){
    for(int i = 2; i <= N; ++i) flag[i] = true;
    cnt = 0;
}

void getPrime(){
    for(int i = 2; i <= N; ++i){
        if(flag[i]) prime[cnt++] = i;
        for(int j = 0; j < cnt; ++j){
            if(prime[j] * i > N) break;
            flag[prime[j] * i] = false;
            if(i % prime[j] == 0) break;
        }
    }
}

int main(){
    scanf("%d", &N);
    init();
    getPrime();
    printf("%d\n", cnt);
    return 0;
}
