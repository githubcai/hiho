#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define LSON l, m, rt << 1
#define RSON m + 1, r, rt << 1 | 1
const int MAX = 500001;

struct Node{
    int mx, mn;
};

Node node[MAX << 2];
int ind[MAX];

void pushUp(int rt){
    node[rt].mx = max(node[rt << 1].mx, node[rt << 1 | 1].mx);
    node[rt].mn = min(node[rt << 1].mn, node[rt << 1 | 1].mn);
}

void update(int p, int v, int l, int r, int rt){
    if(l == r){
        node[rt].mx = node[rt].mn = v;
        return;
    }
    int m = (l + r) >> 1;
    if(p <= m){
        update(p, v, LSON);
    }else{
        update(p, v, RSON);
    }
    pushUp(rt);
}

int queryMX(int L, int R, int l, int r, int rt){
    int ret = -1, m = (l + r) >> 1;
    if(L <= l && r <= R){
        return node[rt].mx;
    }
    if(L <= m) ret = max(ret, queryMX(L, R, LSON));
    if(m < R) ret = max(ret, queryMX(L, R, RSON));
    return ret;
}

int queryMN(int L, int R, int l, int r, int rt){
    int ret = 100000001, m = (l + r) >> 1;
    if(L <= l && r <= R){
        return node[rt].mn;
    }
    if(L <= m) ret = min(ret, queryMN(L, R, LSON));
    if(m < R) ret = min(ret, queryMN(L, R, RSON));
    return ret;
}

int find(int l, int r, int v){
    int left = l, right = r;
    while(left <= right){
        int mid = (left + right) / 2;
        if(ind[mid] == v) return mid;
        if(ind[mid] > v){
            right = mid - 1;
        }else{
            left = mid + 1;
        }
    }
    return right;
}

int main(){
    int N; scanf("%d", &N);
    char comd[2];
    int cnt = 1, left = 1, right = 1;
    for(int i = 0; i < N; ++i){
        scanf("%s", comd);
        if(comd[0] == 'P'){
            int a, b; scanf("%d%d", &a, &b);
            right = cnt;
            ind[cnt] = a;
            update(cnt, b, 1, N, 1);
            ++cnt;
        }else if(comd[0] == 'Q'){
            int res[3];
            res[0] = queryMX(left, right, 1, N, 1);
            res[1] = queryMN(left, right, 1, N, 1);
            res[2] = queryMX(right, right, 1, N, 1);
            printf("%d %d %d\n", res[0], res[1], res[2]);
        }else{
            int a; scanf("%d", &a);
            a = find(left, right, a);
            left = a + 1;
        }
    }
    return 0;
}
