#include <cstdio>
#include <cmath>

const int MAX = 100000;
int N, M, K;
double dis[MAX];

int main(){
    while(scanf("%d%d%d", &N, &M, &K) != EOF){
        for(int i = 0; i < N; ++i){
            scanf("%lf", &dis[i]);
        }
        double left = 0, right = M;
        while(right - left > 1e-3){
            double mid = (left + right) / 2;
            int temp = K;
            for(int i = 1; i < N; ++i){
                int t = ceil((dis[i] - dis[i - 1]) / mid) - 1;
                temp -= t;
                if(temp < 0) break;
            }
            if(temp >= 0){
                right = mid;
            }else{
                left = mid;
            }
        }
        printf("%0.1lf\n", left);
    }
    return 0;
}
