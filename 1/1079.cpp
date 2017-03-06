#include <cstdio>
#include <set>
#include <algorithm>
using namespace std;

#define LSON l, m, rt << 1
#define RSON m + 1, r, rt << 1 | 1

const int MAX = 100001;
struct Node{
    int lazy, flag;
};

struct Poster{
    int l, r;
};

Node nodes[MAX << 2];
Poster posters[MAX];
int N, L, cnt, xseg[2 * MAX];
set<int> result;

void build(int l, int r, int rt){
    nodes[rt].lazy = -1;
    nodes[rt].flag = -1;
    if(l == r) return;
    int m = (l + r) / 2;
    build(LSON);
    build(RSON);
}

void pushDown(int rt){
    if(nodes[rt].lazy != -1){
        int left = (rt << 1), right = (rt << 1 | 1);
        nodes[left].flag = nodes[right].flag = nodes[rt].lazy;
        nodes[left].lazy = nodes[right].lazy = nodes[rt].lazy;
        nodes[rt].lazy = -1;
    }
}

void update(int L, int R, int v, int l, int r, int rt){
    if(L <= l && r <= R){
        nodes[rt].flag = v;
        nodes[rt].lazy = v;
        return;
    }
    pushDown(rt);
    int m = (l + r) / 2;
    if(m >= L) update(L, R, v, LSON);
    if(m < R) update(L, R, v, RSON);
}

void query(int l, int r, int rt){
    if(l == r){
        if(nodes[rt].flag != -1) result.insert(nodes[rt].flag);
        return;
    }
    if(nodes[rt].lazy != -1){
        result.insert(nodes[rt].flag);
        return;
    }
    int m = (l + r) / 2;
    query(LSON);
    query(RSON);
}

int find(int v){
    int left = 0, right = cnt;
    while(true){
        int mid = (left + right) / 2;
        if(xseg[mid] == v) return mid;
        if(xseg[mid] > v){
            right = mid - 1;
        }else{
            left = mid + 1;
        }
    }
    return -1;
}

int main(){
    scanf("%d%d", &N, &L);
    int temp = 0;
    for(int i = 0; i < N; ++i){
        scanf("%d%d", &posters[i].l, &posters[i].r);
        xseg[temp++] = posters[i].l;
        xseg[temp++] = posters[i].r;
    }
    sort(xseg, xseg + temp);
    cnt = 0;
    for(int i = 1; i < temp; ++i){
        if(xseg[cnt] != xseg[i]){
            xseg[++cnt] = xseg[i];
        }
    }
    build(1, cnt, 1);
    for(int i = 0; i < N; ++i){
        int L = find(posters[i].l), R = find(posters[i].r);
        update(L + 1, R, i, 1, cnt, 1);
    }
    query(1, cnt, 1);
    printf("%lu\n", result.size());
    return 0;
}
