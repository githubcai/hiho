#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int MAX = 26;
struct Node{
    Node *fail, *next[MAX];
    int count;
    bool flag;
    Node(){
        fail = NULL;
        count = 0;
        flag = false;
        memset(next, 0, sizeof(next));
    }
};

char pstr[100001];
int N;

void insert(Node *root, char *str){
    Node *p = root;
    for(int i = 0; str[i]; ++i){
        int index = str[i] - 'a';
        if(p->next[index] == NULL) p->next[index] = new Node();
        p = p->next[index];
        p->count = i;
    }
    p->flag = true;;
}

void query(Node *root, char *str){
    Node *p = root;
    for(int i = 0; str[i]; ++i){
        int index = str[i] - 'a';
        while(p != NULL && !p->next[index]) p = p->fail;
        p = (p == NULL) ? root : p->next[index];
        Node *temp = p;
        while(temp != root){
            if(temp->flag){
                for(int j = 0; j <= temp->count; ++j){
                    str[i - j] = '*';
                }
                break;
            }
            temp = temp->fail;
        }
    }
}

void buildAC(Node *root){
    queue<Node*> que;
    root->fail = NULL;
    que.push(root);
    while(!que.empty()){
        Node *p, *temp = que.front();
        que.pop();
        for(int i = 0; i < MAX; ++i){
            if(temp->next[i]){
                p = temp->fail;
                while(p){
                    if(p->next[i]){
                        temp->next[i]->fail = p->next[i];
                        break;
                    }
                    p = p->fail;
                }
                if(!p) temp->next[i]->fail = root;
                que.push(temp->next[i]);
            }
        }
    }
}

void del(Node *cur){
    for(int i = 0; i < MAX; ++i){
        if(cur->next[i] != NULL){
            del(cur->next[i]);
        }
    }
    delete cur;
}

int main(){
    scanf("%d", &N);
    Node *root = new Node();
    for(int i = 0; i < N; ++i){
        scanf("%s", pstr);
        insert(root, pstr);
    }
    scanf("%s", pstr);
    buildAC(root);
    query(root, pstr);
    printf("%s\n", pstr);
    del(root);
    return 0;
}
