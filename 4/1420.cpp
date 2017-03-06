#include <iostream>
#include <string>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <algorithm>

const int MAX = 30;
int a[MAX], b[MAX], res[2 * MAX + 2];
std::string input;

void trans(int *inp){
    int ret = 0, cnt = 0;
    std::string str;
    for(int i = input.size() - 1; i >= 0; --i){
        str += input[i]; ++cnt;
        if(cnt == 4){
            std::stringstream ss;
            std::reverse(str.begin(), str.end());
            ss << str;
            ss >> inp[ret++];
            str = "";
            cnt = 0;
        }
    }
    if(cnt != 0){
        std::stringstream ss;
        std::reverse(str.begin(), str.end());
        ss << str;
        ss >> inp[ret++];
    }
}

void multi(){
    memset(res, 0, sizeof(res));
    for(int i = 0; i < MAX; ++i){
        int c = 0;
        for(int j = 0; j < MAX; ++j){
            int temp = a[i] * b[j] + res[i + j] + c;
            c = temp / 10000;
            res[i + j] = temp % 10000;
        }
    }
}

int main(){
    std::cin >> input;
    trans(a);
    std::cin >> input;
    trans(b);
    multi();
    int ed;
    for(ed = 2 * MAX + 1; ed > 0; --ed){
        if(res[ed] > 0) break;
    }
    printf("%d", res[ed--]);
    while(ed >= 0){
        printf("%04d", res[ed--]);
    }
    printf("\n");
}
