#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAX = 2000010;
char s[MAX], str[MAX];
int p[MAX], n;

void init(){
    n = strlen(s);
    str[0] = '$', str[1] = '#';
    for(int i = 0; i < n; ++i){
        str[i * 2 + 2] = s[i];
        str[i * 2 + 3] = '#';
    }
    n = n * 2 + 2;
    str[n] = 0;
}

void manacher(){
    int mx = 0, id;
    for(int i = 1; i < n; ++i){
        if(mx > i){
            p[i] = min(p[2 * id - i], p[id] + id - i);
        }else{
            p[i] = 1;
        }
        for(; str[i + p[i]] == str[i - p[i]]; ++p[i]);
        if(p[i] + i > mx){
            mx = p[i] + i;
            id = i;
        }
    }
}

int main(){
    int N; scanf("%d", &N);
    for(int i = 0; i < N; ++i){
        scanf("%s", s);
        init();
        manacher();
        int ans = 0;
        for(int i = 1; i < n; ++i){
            if(ans < p[i]) ans = p[i];
        }
        printf("%d\n", ans - 1);
    }
    return 0;
}
