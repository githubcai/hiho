#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const int MAX = 100010;
int wa[MAX], wb[MAX], wv[MAX], ws[MAX];
int rk[MAX], height[MAX];
int N, sa[MAX], input[MAX];

bool cmp(int *r, int a, int b, int l){
    return r[a] == r[b] && r[a + l] == r[b + l];
}

void da(int *r, int *sa, int n, int m){
    int i, j, p, *x = wa, *y = wb, *t;
    for(i = 0; i < m; ++i) ws[i] = 0;
    for(i = 0; i < n; ++i) ++ws[x[i] = r[i]];
    for(i = 1; i < m; ++i) ws[i] += ws[i - 1];
    for(i = n - 1; i >= 0; --i) sa[--ws[x[i]]] = i;
    for(j = 1, p = 1; p < n; j *= 2, m = p){
        for(p = 0, i = n - j; i < n; ++i) y[p++] = i;
        for(i = 0; i < n; ++i) if(sa[i] > j) y[p++] = sa[i] - j;
        for(i = 0; i < n; ++i) wv[i] = x[y[i]];
        for(i = 0; i < m; ++i) ws[i] = 0;
        for(i = 0; i < n; ++i) ++ws[wv[i]];
        for(i = 1; i < m; ++i) ws[i] += ws[i - 1];
        for(i = n - 1; i >= 0; --i) sa[--ws[wv[i]]] = y[i];
        for(t = x, x = y, y = t, p = 1, x[sa[0]] = 0, i = 1; i < n; ++i){
            x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p++;
        }
    }
}

void calHeight(int *r, int *sa, int n){
    int i, j, k = 0;
    for(i = 1; i <= n; ++i) rk[sa[i]] = i;
    for(i = 0; i < n; height[rk[i++]] = k){
        for(k ? k-- : 0, j = sa[rk[i] - 1]; r[i + k] == r[j + k]; ++k);
    }
}

int minSum[MAX][20];
void RMQ(int num){
    for(int j = 1; j < 20; ++j){
        for(int i = 1; i <= num; ++i){
            if(i + (1 << j) - 1 <= num){
                minSum[i][j] = min(minSum[i][j - 1], minSum[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
}

int lcp(int a, int b){
    int st = rk[a], ed = rk[b];
    if(st > ed){
        int t = st;
        st = ed;
        ed = t;
    }
    st += 1;
    int t = (int)(log(ed - st + 1) / log(2.0));
    return min(minSum[st][t], minSum[ed - (1 << t) + 1][t]);
}

int main(){
    char str[MAX];
    scanf("%s", str);
    int slen = strlen(str);
    for(int i = 0; i <= slen; ++i){
        input[i] = str[i];
    }
    da(input, sa, slen + 1, 128);
    calHeight(input, sa, slen);
    for(int i = 1; i <= slen; ++i){
        minSum[i][0] = height[i];
    }
    RMQ(slen);
    int ans = -1;
    for(int L = 1; L <= slen; ++L){
        for(int i = 1; i + L <= slen; i += L){
            int R = lcp(i, i + L);
            ans = max(ans, R / L + 1);
            if(i >= L - R % L){
                ans = max(ans, lcp(i - L + R % L, i + R % L) / L + 1);
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
