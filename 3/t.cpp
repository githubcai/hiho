#include<cstdio>
#include<cmath>
#include<cstring>
#define inf 1000000007
using namespace std;
int ch[200005][2],size[200005],val[200005],fa[200005],cnt,rt,n;
inline void pushup(int rt)
{
	size[rt]=size[ch[rt][0]]+size[ch[rt][1]]+1;
}
void rotate(int x,int &k)
{
	int y=fa[x],z=fa[y],kind;
	if(ch[y][0]==x)kind=1;else kind=0;
	if(y==k)k=x;
	else
	{
		if(ch[z][0]==y)ch[z][0]=x;else ch[z][1]=x;
	}
	ch[y][kind^1]=ch[x][kind];fa[ch[x][kind]]=y;
	ch[x][kind]=y;fa[y]=x;fa[x]=z;
	pushup(x);pushup(y);
}
void splay(int x,int &k)
{
	while(x!=k)
	{
		int y=fa[x],z=fa[y];
		if(y!=k)
		{
			if((ch[y][0]==x)^(ch[z][0]==y))rotate(x,k);
			else rotate(y,k);
		}
		rotate(x,k);
	}
}
void ins(int &k,int x,int last)
{
	if(k==0)
	{
		k=++cnt;val[k]=x;fa[k]=last;size[k]=1;splay(k,rt);return;
	}
	if(x<val[k])ins(ch[k][0],x,k);
	else ins(ch[k][1],x,k);
}
int pre,sub;
void findpre(int k,int x)
{
	if(!k)return;
	if(x==val[k])
	{
		pre=k;return;
	}
	if(val[k]<=x)pre=k,findpre(ch[k][1],x);
	if(val[k]>x)findpre(ch[k][0],x);
}
void findsub(int k,int x)
{
	if(!k)return;
	if(x==val[k])
	{
		sub=k;return;
	}
	if(val[k]>=x)sub=k,findsub(ch[k][0],x);
	if(val[k]<x)findsub(ch[k][1],x);
}
void del(int a,int b)
{
	findpre(rt,a-1);findsub(rt,b+1);
	int x=pre,y=sub;
	splay(x,rt);splay(y,ch[x][1]);
	int z=ch[y][0];fa[z]=0;size[z]=0;ch[y][0]=0;val[z]=0;
}
int main()
{
	scanf("%d",&n);ins(rt,-inf,0);ins(rt,inf,0);
	while(n--)
	{
		char opt[10];scanf("%s",opt);int x,y;
		if(opt[0]=='I')
		{
			scanf("%d",&x);ins(rt,x,0);
		}
		if(opt[0]=='Q')
		{
			scanf("%d",&x);findpre(rt,x);printf("%d\n",val[pre]);
		}
		if(opt[0]=='D')
		{
			scanf("%d%d",&x,&y);del(x,y);
		}
	}
	return 0;
}
