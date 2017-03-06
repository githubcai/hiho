#include <cstdio>
#include <queue>
using namespace std;

typedef long long LL;
const int MAX = 100001;
LL num[MAX], N, Q;

bool check(int mid){
    priority_queue<LL> que;
    LL ret = 0, cnt = 1;
    for(int i = 0; i < N; ++i){
        que.push(num[i]);
        if(que.size() == mid){
            LL now = que.top();
            que.pop();
            ret += now * cnt;
            ++cnt;
        }
        if(ret > Q) return false;
    }
    while(!que.empty()){
        LL now = que.top();
        que.pop();
        ret += now * cnt;
        ++cnt;
        if(ret > Q) return false;
    }
    return true;
}

int main(){
    scanf("%lld%lld", &N, &Q);
    for(int i = 0; i < N; ++i) scanf("%lld", &num[i]);
    int ans = -1, left = 1, right = N;
    while(left <= right){
        int mid = (left + right) / 2;
        if(check(mid)){
            ans = mid;
            right = mid - 1;
        }else{
            left = mid + 1;
        }
    }
    printf("%d\n", ans);
    return 0;
}
