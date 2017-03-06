#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const int MAX = 1000001;
int minSum[MAX][20];

void RMQ(int num){
    for(int j = 1; j < 20; ++j){
        for(int i = 0; i < num; ++i){
            if(i + (1 << j) - 1 < num){
                minSum[i][j] = min(minSum[i][j - 1], minSum[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
}

int main(){
    int num; scanf("%d", &num);
    for(int i = 0; i < num; ++i){
        scanf("%d", &minSum[i][0]);
    }
    RMQ(num);
    scanf("%d", &num);
    int st, ed;
    while(num-- > 0){
        scanf("%d%d", &st, &ed);
        int t = (int)(log(ed - st + 1) / log(2.0));
        int res = min(minSum[st - 1][t], minSum[ed - (1 << t)][t]);
        printf("%d\n", res);
    }
    return 0;
}
