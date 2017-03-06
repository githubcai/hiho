#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int CAPACITY = 20;
struct Point{
    int x, y;
};

Point p;
int r;

struct Boundary{
    int left, right, top, bottom;
    
    void set(int _left, int _right, int _bottom, int _top){
        left = _left;
        right = _right;
        bottom = _bottom;
        top = _top;
    }
    
    bool check(const Point &p) const{
        if(p.x < left || p.x > right || p.y < bottom || p.y > top) return false;
        return true;
    }

    bool intersect(const Boundary &bound) const{
        int mxLeft = max(left, bound.left);
        int mxBottom = max(bottom, bound.bottom);
        int mnRight = min(right, bound.right);
        int mnTop = min(top, bound.top);
        if(mxLeft > mnRight || mxBottom > mnTop) return false;
        return true;
    }
};

struct Node{
    Boundary boundary;
    Point points[CAPACITY];
    int plen;
    Node *next[4];
    bool isDivide;

    Node(const Boundary &_boundary){
        memset(next, 0 , sizeof(next));
        plen = 0;
        isDivide = false;
        boundary = _boundary;
    }

    void divide(){
        isDivide = true;
        int xmid = (boundary.left + boundary.right) / 2;
        int ymid = (boundary.top + boundary.bottom) / 2;
        Boundary bound[4];
        bound[0].set(boundary.left, xmid, ymid + 1, boundary.top);
        bound[1].set(xmid + 1, boundary.right, ymid + 1, boundary.top);
        bound[2].set(boundary.left, xmid, boundary.bottom, ymid);
        bound[3].set(xmid + 1, boundary.right, boundary.bottom, ymid);
        for(int i = 0; i < 4; ++i){
             next[i] = new Node(bound[i]);
        }
    }
};

void insert(Node *node, const Point &p){
    if(!node->boundary.check(p)) return;
    if(node->plen < CAPACITY){
        node->points[node->plen++] = p;
    }else{
        if(!node->isDivide) node->divide();
        for(int i = 0; i < 4; ++i){
            insert(node->next[i], p);
        }
    }
}

int query(Node *node, const Boundary &range){
    int ret = 0;
    if(!node->boundary.intersect(range)) return ret;
    for(int i = 0; i < node->plen; ++i){
        int temp = (p.x - node->points[i].x) * (p.x - node->points[i].x) + 
            (p.y - node->points[i].y) * (p.y - node->points[i].y);
        if(temp <= r * r) ++ret;
    }
    if(node->isDivide){
        for(int i = 0; i < 4; ++i){
            ret += query(node->next[i], range);
        }
    }
    return ret;
}

int main(){
    int N, M;
    Boundary bound;
    bound.set(0, 30000, 0, 30000);
    Node *root = new Node(bound);
    scanf("%d%d", &N, &M);
    for(int i = 0; i < N; ++i){
        scanf("%d%d", &p.x, &p.y);
        insert(root, p);
    }
    for(int i = 0; i < M; ++i){
        scanf("%d%d%d", &p.x, &p.y, &r);
        bound.left = p.x - r;
        bound.right = p.x + r;
        bound.bottom = p.y - r;
        bound.top = p.y + r;
        printf("%d\n", query(root, bound));
    }
    return 0;
}
