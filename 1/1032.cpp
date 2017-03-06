#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAX = 1000005;
char str[MAX], pstr[2 * MAX];
int slen, p[2 * MAX];

void init(){
    slen = strlen(str);
    pstr[0] = '$';
    for(int i = 0; i <= slen; ++i){
        pstr[i * 2 + 1] = '#';
        pstr[i * 2 + 2] = str[i];
    }
    slen = slen * 2 + 2;
}

void manacher(){
    int mx = 0, id;
    for(int i = 1; i < slen; ++i){
        if(mx > i){
            p[i] = min(p[2 * id - i], mx - i);
        }else{
            p[i] = 1;
        }
        for(; pstr[i + p[i]] == pstr[i - p[i]]; ++p[i]);
        if(i + p[i] > mx){
            mx = i + p[i];
            id = i;
        }
    }
}

int main(){
    int N; scanf("%d", &N);
    while(N-- > 0){
        scanf("%s", str);
        init();
        manacher();
        int ans = -1;
        for(int i = 0; i < slen; ++i){
            if(ans < p[i]) ans = p[i];
        }
        printf("%d\n", ans - 1);
    }
    return 0;
}
