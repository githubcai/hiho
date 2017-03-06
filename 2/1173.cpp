#include <cstdio>

int getSG(int x){
    if(x == 0) return 0;
    if(x % 4 == 0) return x - 1;
    if(x % 4 == 3) return x + 1;
    return x;
}

int main(){
    int N; scanf("%d", &N);
    int ans = 0;
    for(int i = 0; i < N; ++i){
        int temp; scanf("%d", &temp);
        ans ^= getSG(temp);
    }
    if(ans == 0){
        printf("Bob\n");
    }else{
        printf("Alice\n");
    }
    return 0;
}
