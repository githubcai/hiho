#include <cstdio>
#include <cmath>

double a, b, c, d, e;

double cal(double x){
    return (x - d) * (x - d) + (a * x * x + b * x + c - e) * (a * x * x + b * x + c - e);
}

int main(){
    scanf("%lf%lf%lf%lf%lf", &a, &b, &c, &d, &e);
    double left = -200, right = 200;
    while(right - left >= 1e-5){
        double mid1 = (left + right) / 2;
        double mid2 = (right + mid1) / 2;
        double ret1 = cal(mid1), ret2 = cal(mid2);
        if(ret1 >= ret2){
            left = mid1;
        }else{
            right = mid2;
        }
    }
    printf("%.3lf\n", sqrt(cal(left)));
    return 0;
}
