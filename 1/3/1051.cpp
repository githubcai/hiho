#include <cstdio>
#include <algorithm>
using namespace std;

const int MAX = 101;
int day[MAX] = {0}, N, M;

int main(){
    int T; scanf("%d", &T);
    while(T-- > 0){
        scanf("%d%d", &N, &M);
        for(int i = 1; i <= N; ++i){
            scanf("%d", &day[i]);
        }
        day[N + 1] = 101;
        if(N <= M){
            printf("100\n");
        }else{
            int res = 0;
            for(int i = M; i <= N; ++i){
                res = max(res, day[i + 1] - day[i - M] - 1);
            }
            printf("%d\n", res);
        }
    }
    return 0;
}
