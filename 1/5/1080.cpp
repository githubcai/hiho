#include <cstdio>

#define LSON l, m, rt << 1
#define RSON m + 1, r, rt << 1 | 1
const int MAX = 100001;
struct Node{
    int sum, lazy0, lazy1;
};

Node nodes[MAX << 2];

void pushUp(int rt){
    nodes[rt].sum = nodes[rt << 1].sum + nodes[rt << 1 | 1].sum;
}

void pushDown(int l, int r, int rt){
    int m = (l + r) / 2;
    if(nodes[rt].lazy1 != 0){
        nodes[rt << 1].lazy0 = nodes[rt << 1 | 1].lazy0 = 0;
        nodes[rt << 1].lazy1 = nodes[rt << 1 | 1].lazy1 = nodes[rt].lazy1;
        nodes[rt << 1].sum = (m - l + 1) * nodes[rt].lazy1;
        nodes[rt << 1 | 1].sum = (r - m) * nodes[rt].lazy1;
        nodes[rt].lazy1 = 0;
    }
    if(nodes[rt].lazy0 != 0){
        nodes[rt << 1].lazy0 += nodes[rt].lazy0;
        nodes[rt << 1 | 1].lazy0 += nodes[rt].lazy0;
        nodes[rt << 1].sum += (m - l + 1) * nodes[rt].lazy0;
        nodes[rt << 1 | 1].sum += (r - m) * nodes[rt].lazy0;
        nodes[rt].lazy0 = 0;
    }
}

void build(int l, int r, int rt){
    nodes[rt].lazy0 = nodes[rt].lazy1 = 0;
    if(l == r){
        scanf("%d", &nodes[rt].sum);
        return;
    }
    int m = (l + r) / 2;
    build(LSON);
    build(RSON);
    pushUp(rt);
}

void update0(int L, int R, int v, int l, int r, int rt){
    if(L <= l && r <= R){
        nodes[rt].sum += (r - l + 1) * v;
        nodes[rt].lazy0 += v;
        return;
    }
    pushDown(l, r, rt);
    int m = (l + r) / 2;
    if(m >= L) update0(L, R, v, LSON);
    if(m < R) update0(L, R, v, RSON);
    pushUp(rt);
}

void update1(int L, int R, int v, int l, int r, int rt){
    if(L <= l && r <= R){
        nodes[rt].lazy0 = 0;
        nodes[rt].sum = (r - l + 1) * v;
        nodes[rt].lazy1 = v;
        return;
    }
    pushDown(l, r, rt);
    int m = (l + r) / 2;
    if(m >= L) update1(L, R, v, LSON);
    if(m < R) update1(L, R, v, RSON);
    pushUp(rt);
}

int main(){
    int N, M;
    scanf("%d%d", &N, &M);
    build(0, N, 1);
    int a, b, c, d;
    for(int i = 0; i < M; ++i){
        scanf("%d%d%d%d", &a, &b, &c, &d);
        if(a == 0){
            update0(b, c, d, 0, N, 1);
        }else{
            update1(b, c, d, 0, N, 1);
        }
        printf("%d\n", nodes[1].sum);
    }
    return 0;
}
