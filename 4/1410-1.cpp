#include <cstdio>

typedef long long LL;
LL table[9] = {0, 1, 1, 2, 1, 2, 2, 2, 1};

LL cal(LL num){
    if(num < 9) return table[num];
    LL left, right = 1;
    while(right < num) right <<= 1;
    if(right == num) return 1;
    left = right / 2;
    LL temp = (left + right) / 2;
    if(num > temp){
        num = 2 * temp - num;
    }
    return cal(num - left) + 1;
}

int main(){
    LL N; scanf("%lld", &N);
    printf("%lld\n", cal(N));
    return 0;
}
