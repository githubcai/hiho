#include <cstdio>

int main(){
    int N; scanf("%d", &N);
    int ans = 0;
    for(int i = 0; i < N; ++i){
        int temp; scanf("%d", &temp);
        ans ^= temp;
    }
    if(ans == 0){
        printf("Bob\n");
    }else{
        printf("Alice\n");
    }
    return 0;
}
