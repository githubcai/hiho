#include <cstdio>
#include <cstring>

const int MAX = 5000001, INF = 1 << 30;
int prime[MAX], phi[MAX], cnt;
bool flag[MAX];

void init(){
    for(int i = 0; i < MAX; ++i) flag[i] = true;
    cnt = 0;
}

void EulerFunction(){
    for(int i = 2; i < MAX; ++i){
        if(flag[i]){
            prime[cnt++] = i;
            phi[i] = i - 1;
        }
        for(int j = 0; j < cnt; ++j){
            if(i * prime[j] >= MAX) break;
            flag[i * prime[j]] = false;
            if(i % prime[j] == 0){
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }else{
                phi[i * prime[j]] = phi[i] * (prime[j] - 1);
            }
        }
    }
}

int main(){
    init();
    EulerFunction();
    int L, R;
    scanf("%d%d", &L, &R);
    int mn = INF, ans;
    for(int i = L; i <= R; ++i){
        if(mn > phi[i]){
            mn = phi[i];
            ans = i;
        }
    }
    printf("%d\n", ans);
    return 0;
}
