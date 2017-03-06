#include <cstdio>

const int MAX = 1000001;
int num[MAX], tNum[MAX];

int main(){
    int N; scanf("%d", &N);
    for(int i = 0; i < N; ++i) scanf("%d", &num[i]);
    int pos = -1;
    for(int i = 0; i < N; ++i){
        if(pos == -1){
            tNum[++pos] = num[i];
        }else{
            if(tNum[pos] % 2 == num[i] % 2){
                tNum[++pos] = num[i];
            }else{
                --pos;
            }
        }
    }
    printf("%d\n", pos + 1);
    return 0;
}
