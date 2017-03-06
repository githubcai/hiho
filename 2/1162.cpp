#include <cstdio>
#include <cstring>

const int MAX = 1 << 7, MOD = 12357;
struct Mat{
    int a[MAX][MAX], size;
    Mat(){
        memset(a, 0, sizeof(a));
        size = 0;
    }
};

int N, K;
Mat input;

void dfs(int x, int y, int row){
    if(row == K){
        input.a[x][y] = 1;
        return;
    }
    dfs((x << 1) + 1, y << 1, row + 1);
    dfs(x << 1, (y << 1) + 1, row + 1);
    if(row + 2 <= K){
        dfs((x << 2) + 3, (y << 2) + 3, row + 2);
    }
}

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
    while(n > 0){
        if(n & 1) ret = multi(ret, m, mod);
        m = multi(m, m, mod);
        n >>= 1;
    }
    return ret;
}

int main(){
    scanf("%d%d", &K, &N);
    input = Mat();
    input.size = 1 << K;
    dfs(0, 0, 0);
    input = quickMulti(input, N, MOD);
    printf("%d\n", input.a[(1 << K) - 1][(1 << K) - 1]);
    return 0;
}
