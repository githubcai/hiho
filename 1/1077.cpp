#include <cstdio>
#include <algorithm>
using namespace std;

#define LSON l, m, rt << 1
#define RSON m + 1, r, rt << 1 | 1
const int MAX = 1000001;
int minNum[MAX << 2];

void pushUp(int rt){
    minNum[rt] = min(minNum[rt << 1], minNum[rt << 1 | 1]);
}

void build(int l, int r, int rt){
    int m = (l + r) >> 1;
    if(l == r){
        scanf("%d", &minNum[rt]);
        return;
    }
    build(LSON);
    build(RSON);
    pushUp(rt);
}

void update(int p, int num, int l, int r, int rt){
    int m = (l + r) >> 1;
    if(l == r){
        minNum[rt] = num;
        return;
    }
    if(p <= m){
        update(p, num, LSON);
    }else{
        update(p, num, RSON);
    }
    pushUp(rt);
}

int query(int L, int R, int l, int r, int rt){
    int m = (l + r) >> 1, ret = 1 << 30;
    if(L <= l && r <= R){
        return minNum[rt];
    }
    if(L <= m) ret = min(ret, query(L, R, LSON));
    if(m < R) ret = min(ret, query(L, R, RSON));
    return ret;
}

int main(){
    int N, M;
    scanf("%d", &N);
    build(1, N, 1);
    scanf("%d", &M);
    int oper, a, b;
    for(int i = 0; i < M; ++i){
        scanf("%d%d%d", &oper, &a, &b);
        if(oper == 0){
            printf("%d\n", query(a, b, 1, N, 1));
        }else{
            update(a, b, 1, N, 1);
        }
    }
    return 0;
}
