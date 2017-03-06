#include <cstdio>
#include <cmath>

const int MAX = 50001;
const double PI = acos(-1.0);
struct Point{
    double x, y;
};

Point p[MAX];

double distance(const Point &p1, const Point &p2){
    double r = 6000000;
    double x1 = p1.x * PI / 180;
    double x2 = p2.x * PI / 180;
    double y1 = p1.y * PI / 180;
    double y2 = p2.y * PI / 180;
    return r * acos(cos(x1 - x2) * cos(y1 - y2));
}

int main(){
    int N, M;
    scanf("%d%d", &N, &M);
    for(int i = 0; i < N; ++i){
        scanf("%lf%lf", &p[i].x, &p[i].y);
    }
    for(int i = 0; i < M; ++i){
        int ans = 0;
        Point temp;
        scanf("%lf%lf", &temp.x, &temp.y);
        for(int i = 0; i < N; ++i){
            if(500 - distance(temp, p[i]) >= 1e-12) ++ans;
        }
        printf("%d\n", ans);
    }
    return 0;
}
