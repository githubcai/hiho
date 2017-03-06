#include <cstdio>
#include <cstring>

const int MAX = 10001;
int father[MAX], N, M, degree[MAX];

void init(){
    for(int i = 0; i <= N; ++i) father[i] = i;
    memset(degree, 0, sizeof(degree));
}

int find(int x){
    if(x == father[x]) return x;
    father[x] = find(father[x]);
    return father[x];
}

void merge(int a, int b){
    int ar = find(a), br = find(b);
    if(ar != br) father[ar] = br;
}

bool check(){
    int root = find(1), odd = 0;
    for(int i = 1; i <= N; ++i){
        if(root != find(i)) return false;
        if(degree[i] % 2 == 1) ++odd;
    }
    if(odd == 1 || odd >2) return false;
    return true;
}

int main(){
    scanf("%d%d", &N, &M);
    init();
    for(int i = 0; i < M; ++i){
        int a, b;
        scanf("%d%d", &a, &b);
        ++degree[a], ++degree[b];
        merge(a, b);
    }
    if(check()){
        printf("Full\n");
    }else{
        printf("Part\n");
    }
    return 0;
}
