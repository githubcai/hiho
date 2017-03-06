#include <cstdio>

struct Node{
    int x, y;

    bool operator==(const Node &a) const{
        return x == a.x && y == a.y;
    }
};

Node nodes[8];

bool check(){
    int cnt = 8;
    for(int i = 0; i < 8; ++i){
        for(int j = i + 1; j < 8; ++j){
            if(nodes[i] == nodes[j]) --cnt;
        }
    }
    if(cnt == 4) return true;
    return false;
}

bool checkRect(){
    int cnt1 = 0, cnt2 = 0;
    for(int i = 1; i < 4; ++i){
        if((nodes[0].x - nodes[1].x) * (nodes[2 * i].x - nodes[2 * i + 1].x) == -(nodes[2 * i].y - nodes[2 * i + 1].y) * (nodes[0].y - nodes[1].y)){
            cnt1 += 1;
            continue;
        }
        if((nodes[0].x - nodes[1].x) * (nodes[2 * i].y - nodes[2 * i + 1].y) == (nodes[2 * i].x - nodes[2 * i + 1].x) * (nodes[0].y - nodes[1].y)){
            cnt2 += 1;
            continue;
        }
    }
    if(cnt1 == 2 && cnt2 == 1) return true;
    return false;
}

int main(){
    int T; scanf("%d", &T);
    while(T-- > 0){
        for(int i = 0; i < 8; ++i){
            scanf("%d%d", &nodes[i].x, &nodes[i].y);
        }
        if(check() && checkRect()){
            printf("YES\n");
        }else{
            printf("NO\n");
        }
    }
    return 0;
}
