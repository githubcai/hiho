#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

const int MAX = 100010;

struct Treap{
    int key, weight, size, son[2];
    void set(int _key, int _weight, int _size){
        key = _key;
        weight = _weight;
        size = _size;
        son[0] = son[1] = 0;
    }
};

Treap treap[MAX];
int cnt = 1, root = 0;    //节点从1开始编号

void rot(int &x, int p){
    int y = treap[x].son[!p];
    treap[x].size = treap[x].size - treap[y].size + treap[treap[y].son[p]].size;
    treap[x].son[!p] = treap[y].son[p];
    treap[y].size = treap[y].size - treap[treap[y].son[p]].size + treap[x].size;
    treap[y].son[p] = x;
    x = y;
}

void ins(int key, int &x){
    if(x == 0){
        treap[x = cnt++].set(key, rand(), 1);
    }else{
        treap[x].size += 1;
        int p = (key < treap[x].key);
        ins(key, treap[x].son[!p]);
        if(treap[x].weight < treap[treap[x].son[!p]].weight) rot(x, p);
    }
}

void del(int key, int &x){
    if(treap[x].key == key){
        if(treap[x].son[0] && treap[x].son[1]){
            int p = (treap[treap[x].son[0]].weight > treap[treap[x].son[1]].weight);
            rot(x, p);
            del(key, treap[x].son[p]);
        }else{
            if(treap[x].son[0]){
                x = treap[x].son[0];
            }else{
                x = treap[x].son[1];
            }
        }
    }else{
        --treap[x].size;
        int p = (key < treap[x].key);
        del(key, treap[x].son[!p]);
    }
}

int find(int &x, int p){    //找出第p小的节点的编号
    if(p == treap[treap[x].son[0]].size + 1) return x;
    if(p > treap[treap[x].son[0]].size + 1){
        find(treap[x].son[1], p - treap[treap[x].son[0]].size - 1);
    }else{
        find(treap[x].son[0], p);
    }
}

int findNoLarger(int key, int &x){  //找出值小于等于key的节点个数
    if(x == 0) return 0;
    if(treap[x].key <= key){
        return treap[treap[x].son[0]].size + 1 + findNoLarger(key, treap[x].son[1]);
    }else{
        return findNoLarger(key, treap[x].son[0]);
    }
}

int findNum(int key, int &x){
    if(treap[x].key > key){
        if(treap[x].son[0]) return findNum(key, treap[x].son[0]);
    }else if(treap[x].key == key){
        return key;
    }else{
        if(treap[x].son[1]){
            int temp = findNum(key, treap[x].son[1]);
            if(temp != -1 && temp <= key){
                return temp;
            }else{
                return treap[x].key;
            }
        }else{
            return treap[x].key;
        }
    }
    return -1;
}

int main(){
    srand(time(NULL));
    int N, k; scanf("%d", &N);
    char oper[2];
    while(N-- > 0){
        scanf("%s%d", oper, &k);
        if(oper[0] == 'I'){
            ins(k, root);
        }else{
            printf("%d\n", findNum(k, root));    
        }
    }
    return 0;
}
