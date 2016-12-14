#include <cstdio>

#define LSON l, m, rt << 1
#define RSON m + 1, r, rt << 1 | 1
const int MAX = 100001;
struct Node{
    int sum, lazy;
};

Node nodes[MAX << 2];

void pushUp(int rt){
    nodes[rt].sum = nodes[rt << 1].sum + nodes[rt << 1 | 1].sum;
}

void pushDown(int rt, int m){
    if(nodes[rt].lazy){
        nodes[rt << 1].lazy = nodes[rt << 1 | 1].lazy = nodes[rt].lazy;
        nodes[rt << 1].sum = (m - (m >> 1)) * nodes[rt].lazy;
        nodes[rt << 1 | 1].sum = (m >> 1) * nodes[rt].lazy;
        nodes[rt].lazy = 0;
    }
}

void build(int l, int r, int rt){
    int m = (l + r) >> 1;
    nodes[rt].lazy = 0;
    if(l == r){
        scanf("%d", &nodes[rt].sum);
        return;
    }
    build(LSON);
    build(RSON);
    pushUp(rt);
}

void update(int L, int R, int num, int l, int r, int rt){
    int m = (l + r) >> 1;
    if(L <= l && r <= R){
        nodes[rt].sum = (r - l + 1) * num;
        nodes[rt].lazy = num;
        return;
    }
    pushDown(rt, r - l + 1);
    if(L <= m) update(L, R, num, LSON);
    if(m < R) update(L, R, num, RSON);
    pushUp(rt);
}

int query(int L, int R, int l, int r, int rt){
    int ret = 0, m = (l + r) >> 1;
    if(L <= l && r <= R){
        return nodes[rt].sum;
    }
    pushDown(rt, r - l + 1);
    if(L <= m) ret += query(L, R, LSON);
    if(m < R) ret += query(L, R, RSON);
    return ret;
}

int main(){
    int N, M;
    scanf("%d", &N);
    build(1, N, 1);
    scanf("%d", &M);
    for(int i = 0; i < M; ++i){
        int oper; scanf("%d", &oper);
        if(oper == 0){
            int l, r;
            scanf("%d%d", &l, &r);
            printf("%d\n", query(l, r, 1, N, 1));
        }else{
            int l, r, n;
            scanf("%d%d%d", &l, &r, &n);
            update(l, r, n, 1, N, 1);
        }
    }
    return 0;
}
