#include <cstdio>

int main(){
    int N; scanf("%d\n", &N);
    int ans = 0;
    for(int i = 1; i <= N; ++i){
        char c; scanf("%c", &c);
        if(c == 'H') ans ^= i;
    }
    if(ans == 0){
        printf("Bob\n");
    }else{
        printf("Alice\n");
    }
    return 0;
}
