#include <cstdio>
#include <cstring>

const int MAX = 1001, INF = 1 << 30;
char input[MAX];
int num[2][MAX];

int main(){
    int T; scanf("%d", &T);
    while(T-- > 0){
        scanf("%s", input);
        int slen = strlen(input);
        memset(num, 0, sizeof(num));
        int cnt = 0;
        for(int i = 0; i < slen; ++i){
            num[1][i] = cnt;
            if(input[i] == '1') ++cnt;
        }
        cnt = 0;
        for(int i = slen - 1; i >= 0; --i){
            num[0][i] = cnt;
            if(input[i] == '0') ++cnt;
        }
        int ans = INF;
        for(int i = 0; i < slen; ++i){
            int temp = num[0][i] + num[1][i];
            if(ans > temp) ans = temp;
        }
        printf("%d\n", ans);
    }
    return 0;
}
