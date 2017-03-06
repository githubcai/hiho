#include <cstdio>
#include <cstring>

const int NMAX = 750, MMAX = 330, MAX = NMAX * MMAX;

struct DLX{
    int n, m, size;
    int U[MAX], D[MAX], R[MAX], L[MAX], Row[MAX], Col[MAX];
    int H[NMAX];
    int S[MMAX];
    int ansd, ans[NMAX];

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
        if(R[0] == 0){
            ansd = d;
            return true;
        }
        int c = R[0];
        for(int i = R[0]; i != 0; i = R[i]){
            if(S[i] < S[c]) c = i;
        }
        remove(c);
        for(int i = D[c]; i != c; i = D[i]){
            ans[d] = Row[i];
            for(int j = R[i]; j != i; j = R[j]) remove(Col[j]);
            if(dance(d + 1)) return true;
            for(int j = L[i]; j != i; j = L[j]) resume(Col[j]);
        }
        resume(c);
        return false;
    }
};

DLX dlx;

void setNode(int r, int x, int y, int k){
    int t = (x / 3) * 3 + (y / 3);
    dlx.link(r, 162 + 9 * t + k);
    dlx.link(r, 9 * x + k);
    dlx.link(r, 81 + 9 * y + k);
    dlx.link(r, 244 + 9 * x + y);
}

int main(){
    int T, maze[9][9];
    scanf("%d", &T);
    while(T-- > 0){
        for(int i = 0; i < 9; ++i){
            for(int j = 0; j < 9; ++j){
                scanf("%d", &maze[i][j]);
            }
        }
        dlx.init(729, 324);
        int r = 1;
        for(int i = 0; i < 9; ++i){
            for(int j = 0; j < 9; ++j){
                if(maze[i][j] != 0){
                    setNode(r, i, j, maze[i][j]);
                    r += 1;
                }else{
                    for(int k = 1; k < 10; ++k){
                        setNode(r, i, j, k);
                        r += 1;
                    }
                }
            }
        }
        memset(maze, 0, sizeof(maze));
        dlx.dance(0);
        int x, y, k;
        for(int i = 0; i < dlx.ansd; ++i){
            int temp = dlx.Col[dlx.L[dlx.H[dlx.ans[i]]]] - 244;
            x = temp / 9;
            y = temp % 9;
            temp = dlx.Col[dlx.H[dlx.ans[i]]];
            k = (temp - 1) % 9 + 1;
            maze[x][y] = k;
        }

        for(int i = 0; i < 9; ++i){
            printf("%d", maze[i][0]);
            for(int j = 1; j < 9; ++j){
                printf(" %d", maze[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}
