#include <cstdio>
#include <map>
using namespace std;

typedef long long LL;
const int MAX = 100001;
LL A[MAX], P[MAX], S[MAX];

int main(){
    int N, M;
    scanf("%d%d", &N, &M);
    for(int i = 0; i < M; ++i){
        scanf("%lld", &A[i]);
    }
    for(int i = 0; i < M; ++i){
        scanf("%lld", &P[i]);
    }
    for(int i = 0; i < M; ++i){
        scanf("%lld", &S[i]);
    }
    map<LL, LL> store;
    for(int i = 0; i < M; ++i){
        LL a = A[i] / S[i], b = A[i] % S[i];
        LL ta = P[i] * S[i], tb = P[i] * b;
        store[ta] += a;
        store[tb] += 1;
    }
    LL ans = 0;
    for(auto iter = store.rbegin(); iter != store.rend(); ++iter){
        if(N > iter->second){
            ans += iter->second * iter->first;
            N -= iter->second;
        }else{
            ans += N * iter->first;
            break;
        }
    }
    printf("%lld\n", ans);
    return 0;
}
