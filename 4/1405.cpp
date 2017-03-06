#include <cstdio>

const int MAX = 101, INF = 1 << 30;
int A[MAX], res[MAX], cnt = 0;

void preOrder(int left, int right){
    if(left <= right){
        int mid, temp = INF;
        for(int i = left; i <= right; ++i){
            if(temp > A[i]){
                temp = A[i];
                mid = i;
            }
        }
        res[cnt++] = temp;
        preOrder(left, mid - 1);
        preOrder(mid + 1, right);
    }
}

int main(){
    int N; scanf("%d", &N);
    for(int i = 0; i < N; ++i){
        scanf("%d", &A[i]);
    }
    preOrder(0, N - 1);
    printf("%d", res[0]);
    for(int i = 1; i < cnt; ++i) printf(" %d", res[i]);
    printf("\n");
    return 0;
}
