#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
#include <set>
#include <cmath>
#include <algorithm>

using namespace std;
#define MAXN 500005
typedef long long int ll64;
typedef unsigned long long int ll65;
const ll65 INFT = (1e9) + 1;

typedef struct ope{
    ll65 s, m, r;
}ope;
typedef struct stree{
    typedef struct node{
        struct node *ch[2], *pre;
        ll65 tmseg, size, num, sums;
    }node;
    node buf[MAXN*2], *root, *nil;
    int bufsize;
    node *getnode(ll65 tmseg, node* fa){
        node *p = NULL;
        if (bufsize<MAXN*2){ p = buf + bufsize++; }
        else{ p = (node*)malloc(sizeof(node)); }
        p->ch[0] = p->ch[1] = nil;
        p->tmseg = p->sums = tmseg;
        p->pre = fa;
        p->size = p->num = 1;
        return p;
    }
    inline int update(node *x){
        if(x->num<0) x->num=0;
        x->size=x->ch[0]->size+x->ch[1]->size+x->num;
        x->sums=x->ch[0]->sums+x->ch[1]->sums+x->num*x->tmseg;
        return 0;
    }
    int init(){
        bufsize =0;
        nil = getnode(0, NULL);
        nil->ch[0] = nil->ch[1] = NULL;
        nil->size = nil->num = 0;
        root = getnode(0, nil);
        root->ch[1] = getnode(INFT, root);
        update(root);
        return 0;
    }
    int rotateto(node *x, int to){
        node *xf = x->pre;
        xf->ch[to ^ 1] = x->ch[to];
        xf->ch[to ^ 1]->pre = xf;
        x->pre = xf->pre;
        if (xf->pre->ch[0] == xf) x->pre->ch[0] = x;
        else x->pre->ch[1] = x;
        xf->pre = x; x->ch[to] = xf;
        update(xf);
        if(xf==root) root=x;
        return 0;
    }
    int splay(node *x, node *fa){
        while (x->pre != fa){
            if (x->pre->pre == fa){
                if (x->pre->ch[0] == x) rotateto(x, 1);
                else rotateto(x, 0);
            }
            else{
                if (x->pre->pre->ch[0] == x->pre){
                    if (x->pre->ch[0] == x){ rotateto(x->pre, 1); rotateto(x, 1); }
                    else { rotateto(x, 0); rotateto(x, 1); }
                }
                else{
                    if (x->pre->ch[0] == x){ rotateto(x, 1); rotateto(x, 0); }
                    else { rotateto(x->pre, 0); rotateto(x, 0); }
                }
            }
        }
        update(x);
        return 0;
    }
    int select(ll65 value,ll65 &size1,ll65 &size2){
        node *p = root,*q=NULL;
        while (p != nil){
            if (p->tmseg == value) break;
            else if (p->tmseg > value) { q = p; p = p->ch[0]; }
            else { q = p; p = p->ch[1]; }
        }
        if (p == nil){
            splay(q, nil);
            if (q->tmseg < value){
                p=root->ch[1];
                while(p->ch[0]!=nil){p=p->ch[0];}
                splay(p, nil);
            }
        }else{
            splay(p, nil);
        }
        size1 = root->ch[0]->sums;
        size2 = root->size - root->ch[0]->size - 1;
        return 0;
    }
    int insert(ll65 value){
        node *p = root, *q = NULL;
        if(value==0) return 0;
        while (p != nil){
            if (p->tmseg == value) break;
            else if (p->tmseg > value){ q = p; p = p->ch[0]; }
            else { q = p; p = p->ch[1]; }
        }
        if (p != nil){
            p->num += 1;
            p->size += 1;
            p->sums += value;
            splay(p, nil);
        }
        else{
            p = getnode(value, q);
            if (value<q->tmseg) q->ch[0] = p;
            else q->ch[1] = p;
            splay(p, nil);
        }
        return 0;
    }
    int remove(ll65 value){
        node *p = root, *q = NULL;
        if(value==0)return 0;
        while (p != nil){
            if (p->tmseg == value) break;
            else if (p->tmseg > value) { q = p; p = p->ch[0]; }
            else { q = p; p = p->ch[1]; }
        }
        if (p != nil){
            p->num -= 1;
            p->size -= 1;
            p->sums -= value;
            splay(p, nil);
        }
        return 0;
    }
}stree;

typedef struct stree1{
    typedef struct node{
        struct node *pre, *ch[2];
        ll65 tm;
    }node;
    node buf[MAXN*4], *root, *nil;
    int bufsize;
    node *getnode(ll65 value, node *fa){
        node *p = NULL;
        if (bufsize<MAXN*4) p = buf + bufsize++;
        else p = (node*)malloc(sizeof(node));
        p->pre = fa; p->tm = value;
        p->ch[0] = p->ch[1] = nil;
        return p;
    }
    int init(){
        bufsize = 0;
        nil = NULL;
        nil = getnode(0, NULL);
        nil->ch[0] = nil->ch[1] = NULL;
        nil->tm = 0;
        root = getnode(0, nil);
        root->ch[1] = getnode(INFT, root);
        return 0;
    }
    int rotateto(node *x, int to){
        node *xf = x->pre;
        xf->ch[to ^ 1] = x->ch[to];
        xf->ch[to ^ 1]->pre = xf;
        x->pre = xf->pre;
        if (xf->pre->ch[0] == xf) x->pre->ch[0] = x;
        else x->pre->ch[1] = x;
        xf->pre = x; x->ch[to] = xf;
        if(xf==root) root=x;
        return 0;
    }
    int splay(node *x, node *fa){
        while (x->pre != fa){
            if (x->pre->pre == fa){
                if (x->pre->ch[0] == x) rotateto(x, 1);
                else rotateto(x, 0);
            }
            else{
                if (x->pre->pre->ch[0] == x->pre){
                    if (x->pre->ch[0] == x){ rotateto(x->pre, 1); rotateto(x, 1); }
                    else { rotateto(x, 0); rotateto(x, 1); }
                }
                else{
                    if (x->pre->ch[0] == x){ rotateto(x, 1); rotateto(x, 0); }
                    else { rotateto(x->pre, 0); rotateto(x, 0); }
                }
            }
        }
        return 0;
    }
    int insert(ll65 tm, ll65 &a, ll65 &b, ll65 &c){
        node *p = root, *q = NULL;
        if(tm==0) return 0;
        while (p != nil){
            if (p->tm == tm) break;
            else if (p->tm > tm){ q = p; p = p->ch[0]; }
            else { q = p; p = p->ch[1]; }
        }
        if (p == nil){
            p=getnode(tm,q);
            if(tm > q->tm){
                q->ch[1]=p;
            }else q->ch[0]=p;
            splay(p, nil); b=tm;
            p=root->ch[0]; while(p->ch[1]!=nil) p=p->ch[1];
            a=p->tm;
            p=root->ch[1]; while(p->ch[0]!=nil) p=p->ch[0];
            c=p->tm;
            return 1;
        }
        else return 0;
        return 0;
    }
    int remove(ll65 tm, ll65 &a, ll65 &b, ll65 &c){
        node *p = root, *q = NULL;
        if(tm==0) return 0;
        while (p != nil){
            if (p->tm == tm) break;
            else if (p->tm > tm){ q = p; p = p->ch[0]; }
            else { q = p; p = p->ch[1]; }
        }
        if (p != nil){
            splay(p, nil);
            node *p1 = p->ch[0];
            while (p1->ch[1] != nil) p1 = p1->ch[1];
            node *p2 = p->ch[1];
            while (p2->ch[0] != nil) p2 = p2->ch[0];
            splay(p1, nil); splay(p2, root);
            a = p1->tm; b = tm; c = p2->tm;
            p2->ch[0] = nil;
            return 1;
        }
        else return 0;
        return 0;
    }
    int getmin(){
        node *p = root, *q = root;
        while (p->ch[0]!=nil){
            p = p->ch[0];
        }
        if(p->ch[1]==nil){
            q=p->pre;
        }else{
            q=p->ch[1];
            while(q->ch[0]!=nil) q=q->ch[0];
        }
        return q->tm;
    }
}stree1;

vector<ll65> stm[MAXN], etm[MAXN];
ope op[MAXN],opr[MAXN];

int oprcmp(const ope &a,const ope &b){
    if(a.m == b.m) return a.r<b.r;
    return a.m<b.m;
}
int main(){
    ll65 i, j, k;
    ll65 n, m, l, r, t;
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    scanf("%llu", &n);
    for (i = 1; i <= n; i++){
        scanf("%llu %llu %llu", &op[i].s, &op[i].m, &op[i].r);
    }
    scanf("%llu", &m);
    i=0; k=1;j=1;
    int flag0=0;
    scanf("%llu %llu %llu", &opr[i].s, &opr[i].m, &opr[i].r);
    int tst=0,ted=0;
    for (i =1; i<m; i++){
        scanf("%llu %llu %llu", &opr[j].s, &opr[j].m, &opr[j].r);
        if(opr[j].s != opr[j-1].s){
            if(ted>tst){
                sort(opr+tst,opr+ted+1,oprcmp);
                int ii,jj=tst;
                for( ii =tst+1;ii<=ted;ii++){
                    if(opr[ii].m<= opr[jj].r+1){
                        opr[jj].r=max(opr[jj].r,opr[ii].r);
                    }else{ ++jj;  opr[jj]=opr[ii];  }
                }
                ++jj; opr[jj]=opr[j];
                tst=ted=jj;  j=jj+1;
            }else{
                tst=ted=j;
                j++;
            }
        }else{
            ted=j;
            j++;
        }
    }
    if(ted>tst){
        sort(opr+tst,opr+ted+1,oprcmp);
        int ii ,jj=tst;
        for( ii =tst+1;ii<=ted;ii++){
            if(opr[ii].m<= opr[jj].r+1){
                opr[jj].r=max(opr[jj].r,opr[ii].r);
            }else{
                ++jj;
                opr[jj]=opr[ii];
            }
        }
        ted=jj;
    }
    for(i=0;i<=ted;i++){
        stm[opr[i].m].push_back(opr[i].s);
        etm[opr[i].r].push_back(opr[i].s);
    }

    stree *t1 = new stree;
    stree1*t2 = new stree1;
    t1->init(); t2->init();
    ll65 a, b, c;
    ll65 ans = 0;
    int ret=0,tmpcnt=0;
    for (i = 1; i <= n; i++){
        for (j = 0; j<stm[i].size(); j++){
            if(stm[i][j]==0)flag0=1;
            tmpcnt++;
            ret=t2->insert(stm[i][j], a, b, c);
            //cout<<"insert : "<<a<<" "<<b<<" "<<c<<endl;
            if(ret==1){
                //cout<<a<<" "<<b<<" "<<c<<endl;
                if (c != INFT){
                    t1->remove(c - a);
                    t1->insert(c - b);
                }
                t1->insert(b - a);
            }
        }
        //cout<<t1->root->sums<<endl;
        if(tmpcnt>0)
        if(op[i].m>0){
            if(op[i].r>0){
                ll65 mint = t2->getmin();
                if(flag0==1)mint=0;
                ll65 size1, size2;
                ll65 tmp=(op[i].m + op[i].r - 1) / op[i].r;
                t1->select(tmp, size1, size2);
                if (mint < tmp){
                    size1 -= mint;
                }else size2--;
                ans += size1*op[i].r + size2*op[i].m;

                tmp=(op[i].m - op[i].s + op[i].r - 1) / op[i].r;
                if (mint < tmp){
                    ans += mint*op[i].r + op[i].s;
                }
                else
                    ans += op[i].m;
            }else{
                ans+=op[i].s;
            }
        }
        //cout<<"id = "<<i<<" : ans="<<ans<<endl;
        for (j = 0; j < etm[i].size(); j++){
            if(etm[i][j]==0) flag0=0;
            tmpcnt--;
            int ret=t2->remove(etm[i][j],a,b,c);
            //cout<<"remove : "<<a<<" "<<b<<" "<<c<<endl;
            if(ret){
                t1->remove(b - a);
                if (c != INFT){
                    t1->remove(c - b);
                    t1->insert(c - a);
                }
            }
        }
    }
    printf("%llu\n", ans);
    return 0;
}
