#include <cstdio>
#include <cstring>

const int MAX = 26;
struct Node{
    int num;
    Node *next[MAX];
    Node(){
        num = 0;
        memset(next, 0, sizeof(next));
    }
};

Node *root;

void insert(char *word){
    Node *temp = root;
    root->num += 1;
    while(*word != '\0'){
        if(temp->next[*word - 'a'] == NULL){
            Node *cur = new Node();
            temp->next[*word - 'a'] = cur;
        }
        temp = temp->next[*word - 'a'];
        word += 1;
        temp->num += 1;
    }
}

int search(char *word){
    Node *temp = root;
    while(*word != '\0'){
        if(temp == NULL || temp->next[*word - 'a'] == NULL) return 0;
        temp = temp->next[*word - 'a'];
        word += 1;
    }
    return temp->num;
}

void del(Node *cur){
    if(cur == NULL) return;
    for(int i = 0; i < MAX; ++i) del(cur->next[i]);
    delete cur;
}

int main(){
    int N; scanf("%d", &N);
    root = new Node();
    char word[11];
    for(int i = 0; i < N; ++i){
        scanf("%s", word);
        insert(word);
    }
    scanf("%d", &N);
    for(int i = 0; i < N; ++i){
        scanf("%s", word);
        printf("%d\n", search(word));
    }
    del(root);
    return 0;
}
