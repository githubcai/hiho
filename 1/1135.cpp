#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

const int MAX = 20001;
char str[MAX];
int target[3], num[3];

int main(){
    scanf("%d%d%d%s", &target[0], &target[1], &target[2], str);
    sort(target, target + 3);
    int slen = strlen(str), ans = -1, cnt = 0, r = 0, y = 0, b = 0;
    for(int i = 0; i < slen; ++i){
        cnt += 1;
        if(ans < cnt) ans = cnt;
        switch(str[i]){
            case 'R': r += 1; break;
            case 'Y': y += 1; break;
            case 'B': b += 1; break;
        }
        num[0] = abs(r - y), num[1] = abs(r - b), num[2] = abs(y - b);
        sort(num, num + 3);
        if(num[0] == target[0] && num[1] == target[1] && num[2] == target[2]) cnt = r = y = b = 0;
    }
    printf("%d\n", ans);
    return 0;
}
