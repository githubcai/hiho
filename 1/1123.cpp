#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long LL;
const int MAX = 100001;
struct Node{
    LL x, y;
};

Node node1[MAX], node2[MAX];

bool cmp(const Node &a, const Node &b){
    return a.x < b.x;
}

int main(){
    int T; scanf("%d", &T);
    while(T-- > 0){
        int n, m;
        scanf("%d%d", &n, &m);
        for(int i = 0; i < n; ++i) scanf("%lld%lld", &node1[i].x, &node1[i].y);
        for(int i = 0; i < m; ++i) scanf("%lld%lld", &node2[i].x, &node2[i].y);
        sort(node1, node1 + n, cmp);
        sort(node2, node2 + m, cmp);
        LL sum = 0, temp = 0;
        int j = 0;
        for(int i = 0; i < n; ++i){
            for(; j < m; ++j){
                if(node1[i].x > node2[j].x){
                    temp += node2[j].y;
                }else{
                    break;
                }
            }
            sum += node1[i].y * temp;
        }
        printf("%lld\n", sum);
    }
    return 0;
}
