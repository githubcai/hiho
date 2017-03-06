#include <cstdio>
#include <cstring>

const int MAX = 1000005;
int n = 0;
int maxlen[2 * MAX], minlen[2 * MAX], trans[2 * MAX][26], slink[2 * MAX];

int newState(int _maxlen, int _minlen, int* _trans, int _slink){
        maxlen[n] = _maxlen;
        minlen[n] = _minlen;
        for(int i = 0; i < 26; i++){
            if(_trans == NULL){
                trans[n][i] = -1;
            }else{
                trans[n][i] = _trans[i];
            }
        }
        slink[n] = _slink;
        return n++;
}

int addChar(int u, char ch){
        int c = ch - 'a';
        int z = newState(maxlen[u] + 1, -1, NULL, -1);
        int v = u;
        while(v != -1 && trans[v][c] == -1){
            trans[v][c] = z;
            v = slink[v];
        }
        if(v == -1){ //最简单的情况，suffix-path(u->S)上都没有对应字符ch的转移
            minlen[z] = 1;
            slink[z] = 0;
            return z;
        }
        int x = trans[v][c];
        if(maxlen[v] + 1 == maxlen[x]){ //较简单的情况，不用拆分x
            minlen[z] = maxlen[x] + 1;
            slink[z] = x;
            return z;
        }
        int y = newState(maxlen[v] + 1, -1, trans[x], slink[x]); //最复杂的情况，拆分x
        slink[y] = slink[x];
        minlen[x] = maxlen[y] + 1;
        slink[x] = y;
        minlen[z] = maxlen[y] + 1;
        slink[z] = y;
        int w = v;
        while(w != -1 && trans[w][c] == x){
            trans[w][c] = y;
            w = slink[w];
        }
        minlen[y] = maxlen[slink[y]] + 1;
        return z;
}

int main(){
    char str[MAX];
    int slen, u = newState(0, 0, NULL, -1);
    scanf("%s", str);
    slen = strlen(str);
    for(int i = 0; i < slen; ++i){
        u = addChar(u, str[i]);
    }
    long long ans = 0;
    for(int i = 1; i < n; ++i){
        ans += maxlen[i] - minlen[i] + 1;
    }
    printf("%lld\n", ans);
    return 0;
}
