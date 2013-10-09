#include<cstdio>
#include<cstring>
#include<vector>
#include<iostream>
#include<algorithm>

using namespace std;

const int MAXN=55;     //最大结点个数

int n,m;

class edge
{
public:
    int from,to,f;

};

bool cmpe(edge a,edge b)
{
    return a.f<b.f;
}

class MyAns
{
public:
    vector<int> v;
};
bool cmp(MyAns a,MyAns b)
{
    int sa=a.v.size();
    int sb=b.v.size();
    if(sa!=sb)
        return sa<sb;

    int size=min(sa,sb);

    for(int i=0;i<size;i++)
    {
        if(a.v[i]!=b.v[i])
            return a.v[i]<b.v[i];
    }
    return sa<sb;

}

vector<MyAns> ans;          //答案
vector<edge> adj[MAXN];  //邻接表
//int flag[MAXN];         //1 -> AND    2 ->OR

int st;

void addedge(int x,int y,int f)
{
//    printf("%d  ->  %d\n",x,y);
    edge e;
    e.from=x;e.to=y;
    e.f=f;
    adj[x].push_back(e);
}

void dfs(int cur,MyAns curans)
{
    int flag=0;

    for(int i=0;i<curans.v.size();i++)
    {
        if(cur==curans.v[i])
        {
            flag=1;
            break;
        }
    }

    int size=adj[cur].size();
    curans.v.push_back(cur);

    if(flag==1)
    {
        ans.push_back(curans);
        return;
    }

    int num=0;

    for(int i=0;i<size;i++)
    {
        num++;
        dfs(adj[cur][i].to,curans);
    }

    if(num==0)
    {
        ans.push_back(curans);
    }
}

void solve()
{
    for(int i=1;i<=n;i++)
    {
        if(adj[i].size()>0)
            sort(adj[i].begin(),adj[i].end(),cmpe);
    }

    MyAns curans;

    dfs(st,curans);
    int cnt=ans.size();
    int tmp=0;
    int vis[MAXN];
    memset(vis,0,sizeof(vis));

    for(int i=0;i<cnt;i++)
    {
        int size=ans[i].v.size();

        bool flag=false;
        for(int j=0;j<size-1;j++)
        {
            int f=0;
            for(int k=0;k<cnt;k++)
                if(i!=k)
            {
                int s=ans[j].v.size();
                for(int l=0;l<s-1;l++)
                    if(ans[i].v[j]==ans[k].v[l] && ans[i].v[j+1]==ans[k].v[l+1])
                    {
                        f=1;
                        break;
                    }
            }
            if(f==0)
            {
                flag=true;
                break;
            }
        }
        if(!flag)
        {
            vis[i]=1;
            tmp--;
        }
    }

    printf("CC=%d\n",cnt+tmp);

    sort(ans.begin(),ans.end(),cmp);

    for(int i=0;i<cnt;i++)
    {
        if(vis[i])  continue;
        int size=ans[i].v.size();
        printf("%d",ans[i].v[0]);
        for(int j=1;j<size;j++)
            printf(",%d",ans[i].v[j]);
        puts("");
    }

}

int main()
{

//    freopen("in.txt","r",stdin);

    cin>>st;
    n=m=0;

    char line[1111];

    while(scanf("%s",line)==1)
    {
        int x,y;char str[111];
        if(line[0]=='E')    break;
        sscanf(line,"%d->%d,%s",&x,&y,str);
        n=max(n,x);
        n=max(n,y);

        int f;
        if(str[0]=='F')
            f=0;
        else if(str[0]=='T')
            f=1;
        else
            f=-1;

        addedge(x,y,f);

    }

    solve();

    return 0;
}
