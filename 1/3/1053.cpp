#include <cstdio>
#include <algorithm>
using namespace std;

const int MAX = 100001;
struct Node{
    int x, y;
};

struct Seg{
    int l, r, n;
};

int N, R;
Node node[MAX];
Seg seg[MAX];

bool cmp(const Node &a, const Node &b){
    return a.x < b.x;
}

bool judge(int mid){
    int num = seg[0].n, index = 0;
    for(int i = 0; i < N; ++i){
        if(seg[index].r < node[i].x) return false;
        if(seg[index].l <= node[i].x){
            num -= mid;
            while(num <= 0){
                ++index;
                if(index == N) return true;
                if(seg[index].l > node[i].x) break;
                num += seg[index].n;
            }
            if(num < 0) num = seg[index].n;
        }
    }
    return false;
}

int main(){
    int T, mx; scanf("%d", &T);
    while(T-- > 0){
        scanf("%d%d", &N, &R);
        mx = -1;
        for(int i = 0; i < N; ++i){
            scanf("%d%d", &node[i].x, &node[i].y);
            mx = max(mx, node[i].y);
        }
        sort(node, node + N, cmp);
        for(int i = 0; i < N; ++i){
            seg[i].l = node[i].x - R;
            seg[i].r = node[i].x + R;
            seg[i].n = node[i].y;
        }
        int left = 1, right = mx, ans = -1;
        while(right >= left){
            int mid = (left + right) / 2;
            if(judge(mid)){
                right = mid - 1;
                ans = mid;
            }else{
                left = mid + 1;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
