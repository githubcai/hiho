#include <cstdio>

typedef long long LL;

struct Point{
    LL x, y;
};

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

int main(){
    LL s1, s2, v1, v2, m;
    scanf("%lld%lld%lld%lld%lld", &s1, &s2, &v1, &v2, &m);
    LL A = v1 - v2, B = m, C = s2 - s1;
    while(A < 0) A += B;
    LL temp = gcd(A, B);
    if(C % temp != 0){
        printf("-1\n");
    }else{
        A /= temp;
        B /= temp;
        C /= temp;
        
        Point p = exgcd(A, B);
        p.x = (p.x * C) % B;
        while(p.x < 0) p.x += B;
        printf("%lld\n", p.x);
    }
    return 0;
}
