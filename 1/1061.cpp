#include <cstdio>

const int MAX = 10 * (1 << 20) + 1;
char str[MAX];
int N;

bool check(){
    int count, slen;
    bool flag = true;
    for(int i = 0; i < N;){
        if(flag){
            count = 1;
            slen = 1;
            for(++i; i < N && str[i] == str[i - 1]; ++i) ++slen;
        }
        while(i < N){
            if(str[i] != str[i - 1] + 1){
                flag = true;
                break;
            }
            int tlen = 1;
            for(++i; i < N && str[i] == str[i - 1]; ++i) ++tlen;
            if(tlen < slen){
                slen = tlen;
                count = 2;
                flag = false;
                break;
            }else if(tlen > slen){
                if(count == 2) return true;
                slen = tlen;
                count = 1;
                flag = false;
                break;
            }
            ++count;
            if(count == 3) return true;
        }
    }
    return false;
}

int main(){
    int T; scanf("%d", &T);
    while(T-- > 0){
        scanf("%d%s", &N, str);
        if(check()){
            printf("YES\n");
        }else{
            printf("NO\n");
        }
    }
    return 0;
}
