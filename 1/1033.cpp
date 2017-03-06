#include <cstdio>
#include <cstring>

typedef long long LL;
const int MOD = 1000000007;
struct Node{
    LL s, n;
};

Node dp[19][20][400];
int bits[18];
LL base[19];

Node dfs(int len, int dig, bool begin_zero, bool limit, int sum){
    Node t = {0, 0};
    if(!limit && dp[len][dig + (begin_zero ? 0 : 10)][sum + 200].n != -1){
        return dp[len][dig + (begin_zero ? 0 : 10)][sum + 200];
    }
    if(len == 0){
        if(dig != sum) return t;
        t.n = 1, t.s = sum;
        return t;
    }
    int end = (limit ? bits[len - 1] : 9);
    int newsum = dig - sum;
    Node temp;
    for(int j = 0; j < end + 1; ++j){
        if(begin_zero){
            temp = dfs(len - 1, j, j == 0, limit && (j == end), sum);
        }else{
            temp = dfs(len - 1, j, false, limit && (j == end), newsum);
        }
        t.n += temp.n;
        t.s = ((t.s + temp.s) % MOD + ((temp.n * dig) % MOD * base[len]) % MOD) % MOD;
    }
    if(!limit) dp[len][dig + (begin_zero ? 0 : 10)][sum + 200] = t;
    return t;
}

LL solve(LL n, LL s){
    if(n <= 0) return 0;
    memset(bits, 0, sizeof(bits));
    int l = 0;
    while(n){
        bits[l++] = n % 10;
        n /= 10;
    }
    return dfs(l, 0, true, true, s).s;
}

int main(){
    LL l, r, s;
    Node t = {0, -1};
    for(int i = 0; i < 19; ++i){
        for(int j = 0; j < 20; ++j){
            for(int k = 0; k < 400; ++k){
                dp[i][j][k] = t;
            }
        }
    }
    base[0] = 1;
    for(int i = 1; i < 19; ++i){
        base[i] = base[i - 1] * 10 % MOD;
    }
    scanf("%lld%lld%lld", &l, &r, &s);
    printf("%lld\n", (solve(r, s) - solve(l - 1, s) + MOD) % MOD);
    return 0;
}
