#include <cstdio>
#include <cstring>

const int MAX = 100001;
int num[MAX], mnum[MAX], N;
long long sum;

void merge(int left, int mid, int right){
    int i = left, j = mid + 1, cnt = 0, count = 0;
    while(i <= mid && j <= right){
        if(num[i] <= num[j]){
            mnum[cnt++] = num[i++];
            sum += count;
        }else{
            mnum[cnt++] = num[j++];
            ++count;
        }
    }
    while(i <= mid){
        mnum[cnt++] = num[i++];
        sum += count;
    }
    while(j <= right) mnum[cnt++] = num[j++];
    for(i = left, j = 0; i <= right; ++i, ++j){
        num[i] = mnum[j];
    }
}

void run(int left, int right){
    if(left < right){
        int mid = (left + right) / 2;
        run(left, mid);
        run(mid + 1, right);
        merge(left, mid, right);
    }
}

int main(){
    scanf("%d", &N);
    for(int i = 0; i < N; ++i){
        scanf("%d", &num[i]);
    }
    sum = 0;
    run(0, N - 1);
    printf("%lld\n", sum);
    return 0;
}
