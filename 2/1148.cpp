#include <string>
#include <unordered_map>
#include <cstdio>
using namespace std;

int getNum(int year){
    return year / 4 - year / 100 + year / 400;
}

bool judge(int year){
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

int main(){
    unordered_map<string, int> ref = {
        {"January", 1}, {"February", 2}, {"March", 3},
        {"April", 4}, {"May", 5}, {"June", 6},
        {"July", 7}, {"August", 8}, {"September", 9},
        {"October", 10}, {"November", 11}, {"December", 12}
    };
    char month[2][15];
    int day[2], year[2], mon[2], T;
    scanf("%d", &T);
    for(int i = 1; i <= T; ++i){
        scanf("%s %d, %d", month[0], &day[0], &year[0]);
        scanf("%s %d, %d", month[1], &day[1], &year[1]);
        mon[0] = ref[string(month[0])];
        mon[1] = ref[string(month[1])];
        
        int ans = 0;
        if(year[1] > year[0]){
            ans = getNum(year[1] - 1) - getNum(year[0] - 1);
            if(judge(year[0]) && mon[0] > 2) ans -= 1;
            if(judge(year[1]) && (mon[1] > 2 || (mon[1] == 2 && day[1] == 29))) ans += 1;
        }else if(year[0] == year[1]){
            if(judge(year[0]) && mon[1] >= mon[0] && mon[0] <= 2 && (mon[1] > 2 || (mon[1] == 2 && day[1] == 29))) ans = 1;
        }
        printf("Case #%d: %d\n", i, ans);
    }
    return 0;
}
