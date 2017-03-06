#include <cstdio>

typedef long long LL;
const int MAX = 1000;
struct Point{
    LL x, y;
};

LL m[MAX], r[MAX];
int N;

LL gcd(LL A, LL B){
    if(A % B == 0) return B;
    return gcd(B, A % B);
}

Point exgcd(LL A, LL B){
    Point p;
    if(A % B == 0){
        p.x = 0, p.y = 1;
        return p;
    }
    Point temp = exgcd(B, A % B);
    p.x = temp.y;
    p.y = temp.x - (A / B) * temp.y;
    return p;
}

LL solve(){
    LL M = m[0], R = r[0];
    for(int i = 1; i < N; ++i){
        LL d = gcd(M, m[i]);
        LL c = r[i] - R;
        if(c % d != 0) return -1;
        Point p = exgcd(M / d, m[i] / d);
        p.x = (c / d * p.x) % (m[i] / d);
        R = R + p.x * M;
        M = M / d * m[i];
        R %= M;
    }
    if(R < 0) R += M;
    return R;
}

int main(){
    scanf("%d", &N);
    for(int i = 0; i < N; ++i){
        scanf("%lld%lld", &m[i], &r[i]);
    }
    LL ret = solve();
    printf("%lld\n", ret);
    return 0;
}
