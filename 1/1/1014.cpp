#include <cstdio>
#include <cstdlib>

const int MAX = 26;
struct Trie{
    int num;
    Trie *next[MAX];
};

Trie *root;

void init(){
    root = (Trie*)malloc(sizeof(Trie));
    for(int i = 0; i < MAX; ++i){
        root->next[i] = NULL;
    }
    root->num = 0;
}

void insert(char *word){
    Trie *temp = root;
    ++root->num;
    while(*word != '\0'){
        if(temp->next[*word - 'a'] == NULL){
            Trie *cur = (Trie*)malloc(sizeof(Trie));
            for(int i = 0; i < MAX; ++i){
                cur->next[i] = NULL;
            }
            cur->num = 0;
            temp->next[*word - 'a'] = cur;
        }
        temp = temp->next[*word - 'a'];
        ++temp->num;
        ++word;
    }
}

int search(char *word){
    Trie *temp = root;
    for(int i = 0; word[i] != '\0'; ++i){
        if(temp == NULL || temp->next[word[i] - 'a'] == NULL) return 0;
        temp = temp->next[word[i] - 'a'];
    }
    return temp->num;
}

void del(Trie *cur){
    for(int i = 0; i < MAX; ++i){
        if(cur->next[i] != NULL){
            del(cur->next[i]);
        }
    }
    free(cur);
}

int main(){
    int n; char word[11];
    init();
    scanf("%d", &n);
    for(int i = 0; i < n; ++i){
        scanf("%s", word);
        insert(word);
    }
    scanf("%d", &n);
    for(int i = 0; i < n; ++i){
        scanf("%s", word);
        printf("%d\n", search(word));
    }
    del(root);
    return 0;
}
