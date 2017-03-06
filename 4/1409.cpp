#include <cstdio>
#include <algorithm>
using namespace std;

const int MAX = 100001;
int a[MAX], b[MAX];

int main(){
    int N; scanf("%d", &N);
    for(int i = 0; i < N; ++i){
        scanf("%d", &a[i]);
        b[i] = a[i];
    }
    sort(b, b + N);
    bool isFirst = true;
    int st, ed;
    for(int i = 0; i < N; ++i){
        if(a[i] != b[i]){
            if(isFirst){
                isFirst = false;
                st = i;
            }else{
                ed = i;
            }
        }
    }
    printf("%d\n", ed - st + 1);
    return 0;
}
