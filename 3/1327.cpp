#include <cstdio>
#include <cstring>

const int MAX = 100001;
int num[26];
char input[MAX];

int getMax(){
    int ret = 0;
    for(int i = 0; i < 26; ++i){
        if(num[i] == 0) continue;
        if(ret < num[i]) ret = num[i];
    }
    return ret;
}

int main(){
    scanf("%s", input);
    int slen = strlen(input);
    memset(num, 0, sizeof(num));
    for(int i = 0; i < slen; ++i) num[input[i] - 'a'] += 1;
    int temp = getMax();
    if(temp > (slen + 1) / 2){
        printf("INVALID\n");
    }else{
        int cnt = slen;
        for(int i = 0; i < slen; ++i){
            for(int j = 0; j < 26; ++j){
                if(num[j] == 0 || input[i - 1] == j + 'a') continue;
                --num[j];
                temp = getMax();
                if(temp <= cnt / 2){
                    input[i] = j + 'a';
                    cnt -= 1;
                    break;
                }
                ++num[j];
            }
        }
        input[slen] = '\0';
        printf("%s\n", input);
    }
    return 0;
}
