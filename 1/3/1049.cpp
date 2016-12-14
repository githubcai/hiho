#include <cstdio>
#include <cstring>

const int MAX = 27;

void postOrder(char *pre, char *middle, int slen){
    if(slen == 1){
        printf("%c", pre[0]);
        return;
    }
    int temp = 0;
    while(middle[temp] != pre[0]) ++temp;
    if(temp > 0) postOrder(pre + 1, middle, temp);
    if(slen - temp - 1 > 0) postOrder(pre + temp + 1, middle + temp + 1, slen - temp - 1);
    printf("%c", pre[0]);
}

int main(){
    char pre[MAX], middle[MAX];
    scanf("%s%s", pre, middle);
    int slen = strlen(pre);
    postOrder(pre, middle, slen);
    printf("\n");
    return 0;
}
