#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAX = 100001;
struct Node{
    int t, sta;
};

Node node[2 * MAX];

bool cmp(const Node &a, const Node &b){
    return a.t < b.t;
}

int main(){
    int N; scanf("%d", &N);
    for(int i = 0; i < N; ++i){
        int x, y;
        scanf("%d%d", &x, &y);
        node[i * 2].t = x;
        node[i * 2].sta = 1;
        node[i * 2 + 1].t = y - 1;
        node[i * 2 + 1].sta = -1;
    }
    sort(node, node + 2 * N, cmp);
    int ans = -1, temp = 0;;
    for(int i = 0; i < 2 * N; ++i){
        temp += node[i].sta;
        if(ans < temp) ans = temp;
    }
    printf("%d\n", ans);
    return 0;
}
