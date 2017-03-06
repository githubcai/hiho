#include <cstdio>

const int MAX = 100001;
int cnt, node[MAX];

void push(int v){
    node[++cnt] = v;
    int fa = cnt / 2, child = cnt;
    while(fa > 0 && node[child] > node[fa]){
        int temp = node[child];
        node[child] = node[fa];
        node[fa] = temp;
        child = fa;
        fa /= 2;
    }
}

int pop(){
    int ret = node[1], index = 1;
    node[index] = node[cnt--];
    int left = (index << 1), right = (index << 1 | 1);
    while(left <= cnt){
        int mx = node[left];
        bool flag = true;
        if(right <= cnt && node[right] > mx){
            flag = false;
            mx= node[right];
        }
        if(node[index] >= mx) break;
        if(flag){
            node[left] = node[index];
            node[index] = mx;
            index = left;
        }else{
            node[right] = node[index];
            node[index] = mx;
            index = right;
        }
        left = (index << 1), right = (index << 1 | 1);
    }
    return ret;
}

int main(){
    int N; scanf("%d", &N);
    char op[2]; int num;
    cnt = 0;
    for(int i = 0; i < N; ++i){
        scanf("%s%d", op, &num);
        if(op[0] == 'A'){
            push(num);
        }else{
            printf("%d\n", pop());
        }
    }
    return 0;
}
