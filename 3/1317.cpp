#include <cstdio>

const int NMAX = 101, MMAX = 101, MAX = NMAX * MMAX;

struct DLX{
    int n, m, size;
    int U[MAX], D[MAX], R[MAX], L[MAX], Row[MAX], Col[MAX];
    int H[NMAX];
    int S[MMAX];

    void init(int _n, int _m){
        n = _n, m = _m;
        for(int i = 0; i <= m; ++i){
            S[i] = 0;
            U[i] = D[i] = i;
            L[i] = i - 1;
            R[i] = i + 1;
        }
        R[m] = 0, L[0] = m;
        size = m;
        for(int i = 1; i <= n; ++i) H[i] = -1;
    }

    void link(int r, int c){
        ++S[Col[++size] = c];
        Row[size] = r;
        D[size] = c;
        U[size] = U[c];
        U[D[size]] = size;
        D[U[size]] = size;
        if(H[r] < 0){
            H[r] = L[size] = R[size] = size;
        }else{
            R[size] = H[r];
            L[size] = L[H[r]];
            L[R[size]] = size;
            R[L[size]] = size;
        }
    }

    void remove(int c){
        L[R[c]] = L[c];
        R[L[c]] = R[c];
        for(int i = D[c]; i != c; i = D[i]){
            for(int j = R[i]; j != i; j = R[j]){
               U[D[j]] = U[j];
               D[U[j]] = D[j];
               --S[Col[j]];
            }
        }
    }

    void resume(int c){
        for(int i = U[c]; i != c; i = U[i]){
            for(int j = L[i]; j != i; j = L[j]){
                ++S[Col[U[D[j]] = D[U[j]] = j]];
            }
        }
        L[R[c]] = R[L[c]] = c;
    }

    bool dance(int d){
        if(R[0] == 0) return true;
        int c = R[0];
        for(int i = R[0]; i != 0; i = R[i]){
            if(S[i] < S[c]) c = i;
        }
        remove(c);
        for(int i = D[c]; i != c; i = D[i]){
            for(int j = R[i]; j != i; j = R[j]) remove(Col[j]);
            if(dance(d + 1)) return true;
            for(int j = L[i]; j != i; j = L[j]) resume(Col[j]);
        }
        resume(c);
        return false;
    }
};

int main(){
    int T; scanf("%d", &T);
    DLX dlx;
    while(T-- > 0){
        int n, m; scanf("%d%d", &n, &m);
        dlx.init(n, m);
        for(int i = 1; i <= n; ++i){
            for(int j = 1; j <= m; ++j){
                int temp; scanf("%d", &temp);
                if(temp == 1) dlx.link(i, j);
            }
        }
        if(dlx.dance(0)){
            printf("Yes\n");
        }else{
            printf("No\n");
        }
    }
    return 0;
}
