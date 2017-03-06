#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long LL;
const int MAX = 1001;
struct Point{
    LL x, y, r;
};

struct Node{
    int high, low;
};

Point point[MAX];
Node node[MAX];
int W, H, N, father[MAX];

void init(){
    for(int i = 1; i <= N; ++i){
        father[i] = i;
        node[i].low = point[i].y - point[i].r;
        node[i].high = point[i].y + point[i].r;
    }
}

int find(int x){
    if(father[x] == x) return x;
    father[x] = find(father[x]);
    return father[x];
}

void merge(int a, int b){
    int ar = find(a), br = find(b);
    if(ar != br){
        father[ar] = br;
        node[br].high = max(node[br].high, node[ar].high);
        node[br].low = min(node[br].low, node[ar].low);
    }
}

int main(){
    int T; scanf("%d", &T);
    while(T-- > 0){
        scanf("%d%d%d", &W, &H, &N);
        for(int i = 1; i <= N; ++i){
            scanf("%lld%lld%lld", &point[i].x, &point[i].y, &point[i].r);
        }
        init();
        for(int i = 1; i <= N; ++i){
            for(int j = i + 1; j <= N; ++j){
                LL temp = (point[i].x - point[j].x) * (point[i].x - point[j].x) + (point[i].y - point[j].y) * (point[i].y - point[j].y);
                if((point[i].r + point[j].r) * (point[i].r + point[j].r) >= temp) merge(i, j);
            }
        }
        bool flag = true;
        for(int i = 1; i <= N; ++i){
            if(node[i].low <= 0 && node[i].high >= H){
                flag = false;
                break;
            }
        }
        if(flag){
            printf("YES\n");
        }else{
            printf("NO\n");
        }
    }
    return 0;
}
