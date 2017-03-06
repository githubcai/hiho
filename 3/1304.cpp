#include <cstdio>
#include <cstring>

int num[4], nowNumber[4];
bool vis[4];
char opType[6] = {'+', '-', '*', '/', '_', '|'}, ops[3];

double cal(double num1, char oper, double num2){
    double ans;
    switch(oper){
        case '+': ans = num1 + num2; break;
        case '-': ans = num1 - num2; break;
        case '*': ans = num1 * num2; break;
        case '/': ans = num1 / num2; break;
        case '_': ans = num2 - num1; break;
        case '|': ans = num2 / num1; break;
    }
    return ans;
}

double calType1(){
    double ans = nowNumber[0];
    for(int i = 1; i < 4; ++i){
        ans = cal(ans, ops[i - 1], nowNumber[i]);
    }
    return ans;
}

double calType2(){
    double ans1 = cal(nowNumber[0], ops[0], nowNumber[1]), ans2 = cal(nowNumber[2], ops[2], nowNumber[3]);
    return cal(ans1, ops[1], ans2);
}

bool makeOperation(int depth){
    if(depth >= 3){
        double temp = calType1() - 24;
        if(temp <= 1e-9 && temp >= -1e-9) return true;
        temp = calType2() - 24;
        if(temp <= 1e-9 && temp >= -1e-9) return true;
        return false;
    }
    for(int i = 0; i < 6; ++i){
        ops[depth] = opType[i];
        if(makeOperation(depth + 1)) return true;
    }
    return false;
}

bool makeNumber(int depth){
    if(depth >= 4) return makeOperation(0);
    for(int i = 0; i < 4; ++i){
        if(!vis[i]){
            nowNumber[depth] = num[i];
            vis[i] = true;
            if(makeNumber(depth + 1)) return true;
            vis[i] = false;
        }
    }
    return false;
}

int main(){
    int T; scanf("%d", &T);
    while(T-- > 0){
        for(int i = 0; i < 4; ++i) scanf("%d", &num[i]);
        memset(vis, 0, sizeof(vis));
        if(makeNumber(0)){
            printf("Yes\n");
        }else{
            printf("No\n");
        }
    }
    return 0;
}
