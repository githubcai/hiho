#include <cstdio>
#include <cstring>

const int MAX = 102;
char input[MAX], str[MAX];

int getRes(int slen){
    int cnt = 1;
    for(int i = 1; i < slen; ++i){
        if(str[i - 1] == str[i]){
            str[i - 1] = 0;
            cnt += 1;
            continue;
        }
        if(cnt > 1){
            str[i - 1] = 0;
            cnt = 1;
        }
    }
    if(cnt > 1){
        str[slen - 1] = 0;
    }
    cnt = 0;
    for(int i = 0; i < slen; ++i){
        if(str[i] != 0){
            str[cnt++] = str[i];
        }
    }
    if(cnt == slen){
        return slen;
    }else{
        return getRes(cnt);
    }
}

int main(){
    int T; scanf("%d", &T);
    while(T-- > 0){
        scanf("%s", input);
        int slen = strlen(input), ans = MAX;
        for(int k = 0; k < 3; ++k){
            for(int i = 0; i <= slen; ++i){
                if(i < slen && str[i] == 'A' + k) continue;
                for(int j = 0; j < i; ++j){
                    str[j] = input[j];
                }
                str[i] = 'A' + k;
                for(int j = i + 1; j <= slen; ++j){
                    str[j] = input[j - 1];
                }
                int ret = getRes(slen + 1);
                if(ans > ret) ans = ret;
            }
        }
        printf("%d\n", slen + 1 - ans);
    }
    return 0;
}
