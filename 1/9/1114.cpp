#include <cstdio>
#include <queue>
using namespace std;

const int MAX = 100001;
int N, maze[MAX] = {0}, res[2][MAX] = {0};

int main(){
    int T; scanf("%d", &T);
    while(T-- > 0){
        scanf("%d", &N);
        for(int i = 1; i <= N; ++i){
            scanf("%d", &maze[i]);
        }
        for(int k = 0; k < 2; ++k){
            res[k][1] = k;
            for(int i = 2; i <= N; ++i){
                res[k][i] = maze[i - 1] - res[k][i - 1] - res[k][i - 2];
                if(res[k][i] > 1 || res[k][i] < 0){
                    res[k][1] = -1;
                        break;
                }
            }
            if(res[k][N] + res[k][N - 1] != maze[N]) res[k][1] = -1;
        }
        
        queue<int> q1, q2;
        if(res[0][1] == -1){
            for(int i = 1; i <= N; ++i){
                if(res[1][i] == 0){
                    q2.push(i);
                }else{
                    q1.push(i);
                }
            }
        }else if(res[1][1] == -1){
            for(int i = 1; i <= N; ++i){
                if(res[0][i] == 0){
                    q2.push(i);
                }else{
                    q1.push(i);
                }
            }       
        }else if(res[0][1] != -1 && res[1][1] != -1){
            for(int i = 1; i <= N; ++i){
                if(res[0][i] == res[1][i] && res[0][i] == 0){
                    q2.push(i);
                }else if(res[0][i] == res[1][i] && res[0][i] == 1){
                    q1.push(i);
                }
            }       
        }
        printf("%lu", q1.size());
        while(!q1.empty()){
            int t = q1.front();
            q1.pop();
            printf(" %d", t);
        }
        printf("\n");
        
        printf("%lu", q2.size());
        while(!q2.empty()){
            int t = q2.front();
            q2.pop();
            printf(" %d", t);
        }
        printf("\n");
    }
    return 0;
}
