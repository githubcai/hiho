#include <cstdio>
#include <algorithm>
using namespace std;

const int  MAX = 100010;
int wa[MAX], wb[MAX], wv[MAX], ws[MAX];
int rk[MAX], height[MAX];
int N, input[MAX], sa[MAX];

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
        for(i = 0; i < n; ++i) if(sa[i] >= j) y[p++] = sa[i] - j;
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

bool judge(int mid){
    for(int i = 1; i <= N;){
        int mn = sa[i - 1], mx = sa[i - 1];
        while(i <= N && height[i++] >= mid){
            mn = min(mn, sa[i - 1]);
            mx = max(mx, sa[i - 1]);
        }
        if(mx - mn >= mid) return true;
    }
    return false;
}

int main(){
    scanf("%d", &N);
    for(int i = 0; i < N; ++i){
        scanf("%d", &input[i]);
    }
    input[N] = 0;
    da(input, sa, N + 1, 1001);
    calHeight(input, sa, N);
    int left = 0, right = N, ans;
    while(right >= left){
        int mid = (left + right) / 2;
        if(judge(mid)){
            ans = mid;
            left = mid + 1;
        }else{
            right = mid - 1;
        }
    }
    printf("%d\n", ans);
    return 0;
}
