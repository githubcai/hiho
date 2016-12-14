#include <cstdio>
#include <algorithm>
using namespace std;

const int MAX = 1000001;
long long num[MAX];

int main(){
    int N, K;
    scanf("%d%d", &N, &K);
    for(int i = 0; i < N; ++i){
        scanf("%lld", &num[i]);
    }
    if(K > N){
        printf("-1\n");
    }else{
        sort(num, num + N);
        printf("%lld\n", num[K - 1]);
    }
    return 0;
}
