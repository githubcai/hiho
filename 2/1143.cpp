#include <cstdio>
#include <cstring>

typedef long long LL;
const int MAX = 2, MOD = 19999997;
struct Mat{
    LL a[MAX][MAX], size;
    Mat(){
        memset(a, 0, sizeof(a));
        size = 0;
    }
};

Mat multi(const Mat &m1, const Mat &m2, int mod){
    Mat ret = Mat();
    ret.size = m1.size;
    for(int i = 0; i < m1.size; ++i){
        for(int j = 0; j < m2.size; ++j){
            if(m1.a[i][j]){
                for(int k = 0; k < m1.size; ++k){
                    ret.a[i][k] = (ret.a[i][k] + m1.a[i][j] * m2.a[j][k]) % mod;
                }
            }
        }
    }
    return ret;
}

Mat quickMulti(Mat m, int n, int mod){
    Mat ret = Mat();
    ret.size = m.size;
    for(int i = 0; i < ret.size; ++i) ret.a[i][i] = 1;
    while(n){
        if(n & 1) ret = multi(ret, m, mod);
        m = multi(m, m, mod);
        n >>= 1;
    }
    return ret;
}

int main(){
    int N; scanf("%d", &N);
    if(N == 1){
        printf("%d\n", 1);
    }else{
        Mat input = Mat();
        input.size = 2;
        input.a[0][0] = input.a[0][1] = input.a[1][0] = 1;
        input = quickMulti(input, N - 1, MOD);
        printf("%lld\n", (input.a[0][0] + input.a[0][1]) % MOD);
    }
    return 0;
}
