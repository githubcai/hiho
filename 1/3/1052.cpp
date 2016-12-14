#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAX = 1001;
char str[MAX], dir[5] = "ATCG";
int K;

int main(){
    int T; scanf("%d", &T);
    while(T-- > 0){
        scanf("%s%d", str, &K);
        int slen = strlen(str);
        int rep = slen - K, ans = 0;
        for(int i = 0; i < rep; ++i){
            int count[4] = {0};
            for(int j = i; j < slen; j += rep){
                for(int k = 0; k < 4; ++k){
                    if(str[j] == dir[k]) ++count[k];
                }
            }
            int sum = 0, mx = -1;
            for(int j = 0; j < 4; ++j){
                sum += count[j];
                mx = max(mx, count[j]);
            }
            ans += sum - mx;
        }
        printf("%d\n", ans);
    }
    return 0;
}
