#include <cstdio>

const int MAX = 200001, INF = 1 << 30;
struct Tree{
    int key, fa, son[2];
    void set(int _key, int _size, int _fa){
        key = _key;
        fa = _fa;
        son[0] = son[1] = 0;
    }
};

int cnt = 1, rt = 0;
Tree T[MAX];

void rotate(int x, int p){
    int y = T[x].fa;
    T[y].son[!p] = T[x].son[p];
    T[T[x].son[p]].fa = y;
    T[x].fa = T[y].fa;
    if(T[x].fa) T[T[x].fa].son[T[T[x].fa].son[1] == y] = x;
    T[x].son[p] = y;
    T[y].fa = x;
}

void splay(int x, int to){
    while(T[x].fa != to){
        if(T[T[x].fa].fa == to){
            rotate(x, T[T[x].fa].son[0] == x);
        }else{
            int y = T[x].fa, z = T[y].fa;
            int p = (T[z].son[0] == y);
            if(T[y].son[p] == x){
                rotate(x, !p); rotate(x, p);
            }else{
                rotate(y, p); rotate(x, p);
            }
        }
    }
    if(to == 0) rt = x;
}

int find(int key){
    int x = rt;
    while(x && T[x].key != key) x = T[x].son[key > T[x].key];
    if(x) splay(x, 0);
    return x;
}

int prev(){
    int x = T[rt].son[0];
    if(!x) return 0;
    while(T[x].son[1]) x = T[x].son[1];
    splay(x, 0);
    return x;
}

int succ(){
    int x = T[rt].son[1];
    if(!x) return 0;
    while(T[x].son[0]) x = T[x].son[0];
    splay(x, 0);
    return x;
}

void insert(int key){
    if(!rt){
        T[rt = cnt++].set(key, 1, 0);
    }else{
        int x = rt, y = 0;
        while(x){
            y = x;
            x = T[x].son[key > T[x].key];
        }
        T[x = cnt++].set(key, 1, y);
        T[y].son[key > T[y].key] = x;
        splay(x, 0);
    }
}

void del(int l, int r){
    if(!find(l)) insert(l);
    int p = prev();
    if(!find(r)) insert(r);
    int q = succ();
    if(!p && !q){
        rt = 0;
        return;
    }
    if(!p){
        T[rt].son[0] = 0;
        return;
    }
    if(!q){
        splay(p, 0);
        T[rt].son[1] = 0;
        return;
    }
    splay(p, q);
    T[p].son[1] = 0;
}

void delKey(int key){
    int x = find(key);
    if(!x) return;
    int y = T[x].son[0];
    while(T[y].son[1]) y = T[y].son[1];
    int z = T[x].son[1];
    while(T[z].son[0]) z = T[z].son[0];
    if(!y && !z){
        rt = 0;
        return;
    }
    if(!y){
        splay(z, 0);
        T[z].son[0] = 0;
        return;
    }
    if(!z){
        splay(y, 0);
        T[y].son[1] = 0;
        return;
    }
    splay(y, 0);
    splay(z, y);
    T[z].son[0] = 0;
}

int findNum(int key){
    int x = find(key);
    if(x){
        return T[x].key;
    }else{
        insert(key);
        int x = prev();
        delKey(key);
        return T[x].key;
    }
}

int main(){
    int n; scanf("%d", &n);
    char oper[2];
    insert(-INF);
    insert(INF);
    while(n-- > 0){
        scanf("%s", oper);
        if(oper[0] == 'I'){
            int k; scanf("%d", &k);
            insert(k);
        }else if(oper[0] == 'Q'){
            int k; scanf("%d", &k);
            printf("%d\n", findNum(k));
        }else{
            int a, b; scanf("%d%d", &a, &b);
            del(a, b);
        }
    }
    return 0;
}
