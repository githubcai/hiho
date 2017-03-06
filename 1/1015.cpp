#include <cstdio>
#include <cstring>

const int NMAX = 1000001, MMAX = 10001;
char str[NMAX], pat[MMAX];
int next[MMAX];

void getNext(int plen){
    next[0] = 0;
    for(int i = 1, j = 0; i < plen; ++i){
        while(j > 0 && pat[i] != pat[j]) j = next[j - 1];
        if(pat[i] == pat[j]) ++j;
        next[i] = j;
    }
}

int kmp(){
    int nlen = strlen(str), plen = strlen(pat), ret = 0;
    getNext(plen);
    for(int i = 0, j = 0; i < nlen; ++i){
        while(j > 0 && pat[j] != str[i]) j = next[j - 1];
        if(str[i] == pat[j]) ++j;
        if(j == plen) ++ret;
    }
    return ret;
}

int main(){
    int N;
    scanf("%d", &N);
    for(int i = 0; i < N; ++i){
        scanf("%s%s", pat, str);
        printf("%d\n", kmp());
    }
    return 0;
}
