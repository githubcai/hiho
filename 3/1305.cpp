#include <cstdio>
#include <algorithm>
using namespace std;

const int MAX = 100001;
struct Point{
    int x, y;
};

Point A[MAX], B[MAX];

bool cmp(const Point &a, const Point &b){
    if(a.x == b.x) return a.y < b.y;
    return a.x < b.x;
}

int trans(Point *num, int length){
    int ret = 0;
    for(int i = 1; i < length; ++i){
        if(num[i].x <= num[ret].y){
            if(num[i].y > num[ret].y) num[ret].y = num[i].y;
        }else{
            ++ret;
            num[ret].x = num[i].x;
            num[ret].y = num[i].y;
        }
    }
    return ret + 1;
}

int main(){
    int N, M;
    scanf("%d%d", &N, &M);
    for(int i = 0; i < N; ++i){
        scanf("%d%d", &A[i].x, &A[i].y);
    }
    for(int i = 0; i < M; ++i){
        scanf("%d%d", &B[i].x, &B[i].y);
    }
    sort(A, A + N, cmp);
    sort(B, B + M, cmp);
    int acnt = trans(A, N), bcnt = trans(B, M);
    int ans = 0, i, j;
    for(i = 0, j = 0; i < acnt && j < bcnt;){
        if(B[j].y <= A[i].x){
            ++j;
            continue;
        }
        if(A[i].y <= B[j].x){
            ans += A[i].y - A[i].x;
            ++i;
            continue;
        }
        if(B[j].x > A[i].x){
            ans += B[j].x - A[i].x;
            if(B[j].y > A[i].y){
                B[j].x = A[i].y;
                ++i;
            }else if(B[j].y == A[i].y){
                ++i, ++j;
            }else{
                A[i].x = B[j].y;
                ++j;
            }
        }else{
            if(B[j].y < A[i].y){
                A[i].x = B[j].y;
                ++j;
            }else if(B[j].y == A[i].y){
                ++i, ++j;
            }else{
                B[j].x = A[i].y;
                ++i;
            }
        }
    }
    while(i < acnt){
        ans += A[i].y - A[i].x;
        ++i;
    }
    printf("%d\n", ans);
    return 0;
}
