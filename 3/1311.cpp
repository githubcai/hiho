#include <cstdio>
#include <cstring>

const int MAX = 200, NMAX = MAX / 4;
char cnum[MAX], res[MAX] = {'0', '.'};
int num[NMAX];

int divide(int n){
    int r = 0;
    for(int i = NMAX - 1; i >= 0; --i){
        int temp = num[i] + r * 10000;
        num[i] = temp / n;
        r = temp % n;
    }
    return r;
}

bool check(){
    for(int i = 0; i < NMAX; ++i){
        if(num[i] != 0) return true;
    }
    return false;
}

int main(){
    int T; scanf("%d", &T);
    while(T-- > 0){
        scanf("%s", cnum);
        int slen = strlen(cnum);
        memset(num, 0, sizeof(num));
        int cnt = 0;
        for(int i = slen - 1; i > 1;){
            num[cnt] = 0;
            int temp = 1;
            for(int j = 0; i > 1 && j < 4; ++j){
                num[cnt] += (cnum[i--] - '0') * temp;
                temp *= 10;
            }
            cnt += 1;
        }
        bool flag = true;
        for(int i = 0; i < slen - 2; ++i){
            if(num[0] % 5 != 0){
                flag = false;
                break;
            }
            divide(5);
        }
        if(flag){
            for(int i = 2; i < slen; ++i) res[i] = '0';
            int index = slen - 1;
            while(check()){
                res[index--] += divide(2);
            }
            for(int i = slen - 1; i > 1; --i){
                if(res[i] != '0'){
                    res[i + 1] = '\0';
                    break;
                }
            }
            printf("%s\n", res);
        }else{
            printf("NO\n");
        }
    }
    return 0;
}
