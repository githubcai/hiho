#include <cstdio>
#include <cstring>

int num[4], res[4];
int mx = -1;
bool flag[4];

int main(){
    memset(flag, 0, sizeof(flag));
    for(int i = 0; i < 4; ++i) scanf("%d", &num[i]);
    for(int i = 0; i < 4; ++i){
        if(num[i] > 2) continue;
        int temp = num[i] * 10 * 60; 
        flag[i] = true;
        for(int j = 0; j < 4; ++j){
            if(flag[j] || (num[i] == 2 && num[j] >= 4)) continue;
            temp += num[j] * 60;
            flag[j] = true;
            for(int k = 0; k < 4; ++k){
                if(flag[k] || num[k] >= 6) continue;
                temp += num[k] * 10;
                flag[k] = true;
                for(int t = 0; t < 4; ++t){
                    if(flag[t]) continue;
                    temp += num[t];
                    if(mx < temp){
                        mx = temp;
                        res[0] = num[i];
                        res[1] = num[j];
                        res[2] = num[k];
                        res[3] = num[t];
                    }
                    temp -= num[t];
                }
                flag[k] = false;
                temp -= num[k] * 10;
            }
            flag[j] = false;
            temp -= num[j] * 60;
        }
        flag[i] = false;
    }
    if(mx == -1){
        printf("NOT POSSIBLE\n");
    }else{
        printf("%d%d:%d%d\n", res[0], res[1], res[2], res[3]);
    }
    return 0;
}
