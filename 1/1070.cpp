#include <cstdio>

const int MAX = 10001, INF = 0x7fffffff;
int w[MAX];

int main(){
    int N, M; scanf("%d", &N);
    for(int i = 1; i <= N; ++i){
        scanf("%d", &w[i]);
    }
    scanf("%d", &M);
    for(int i = 0; i < M; ++i){
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        if(a == 0){
            int ans = INF;
            for(int i = b; i <= c; ++i){
                ans = (ans < w[i] ? ans : w[i]);
            }
            printf("%d\n", ans);
        }else{
            w[b] = c;
        }
    }
    return 0;
}
