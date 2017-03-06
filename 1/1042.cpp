#include <cstdio>
#include <algorithm>
using namespace std;

int n, m, L;
int l, r, t, b;

int runHorse(int pl, int pr, int pt, int pb){
    int ll = max(pl, l);
    int rr = min(pr, r);
    int tt = max(pt, t);
    int bb = min(pb, b);

    if(ll >= rr || tt >= bb){
        return (pr - pl) * (pb - pt);
    }
    int inside = 0;
    if(l > pl && l < pr && t > pt && t < pb) ++inside;
    if(l > pl && l < pr && b > pt && b < pb) ++inside;
    if(r > pl && r < pr && t > pt && t < pb) ++inside;
    if(r > pl && r < pr && b > pt && b < pb) ++inside;
    if(inside == 1 || inside == 4){
        return (pr - pl) * (pb - pt) - (rr - ll) * (bb - tt);
    }
    return 0;
}

int main(){
    scanf("%d%d%d", &n, &m, &L);
    scanf("%d%d%d%d", &l, &r, &t, &b);

    int res = 0;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            int w = 1;
            int h = (L - 2 * w) / 2;
            while(h > 0){
                res = max(res, runHorse(j, min(m, j + w), i, min(n, i + h)));
                ++w;
                h = (L - 2 * w) / 2;
            }
        }
    }
    printf("%d\n", res);
    return 0;
}
