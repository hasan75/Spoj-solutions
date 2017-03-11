#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef pair<ii,int> iii;


#define N 1005
#define M 250001
#define INF 1000000007
#define PI acos(-1)
#define rep(i,a,b) for(int i = a; i < b; i++)
#define reps(i,a,b) for(int i = a; i >= b; i--)
#define sc scanf
#define pc printf
#define pb push_back
#define F first
#define S second

int n,m;
ii tree[N*4];
int foo[N];
char s[N][N];

void build(int node,int ss,int se)
{
    if(ss == se){
        tree[node] = ii(foo[ss],ss);
        return;
    }
    int mid = (ss + se) / 2;
    int lft = node<<1;
    int rgt = lft|1;

    build(lft,ss,mid);
    build(rgt,mid+1,se);
    if(tree[lft].F < tree[rgt].F){
        tree[node] = tree[lft];
    }
    else{
        tree[node] = tree[rgt];
    }
}

ii query(int node, int ss, int se, int qs, int qe)
{
    if (qs > se || qe < ss)
        return ii(INF,-1);
    if (ss >= qs && se <= qe)
        return tree[node];
    int Left = node<<1;
    int Right =  Left+1;
    int mid = (ss + se) / 2;
    ii p1 = query(Left, ss, mid, qs, qe);
    ii p2 = query(Right, mid + 1, se, qs, qe);
    if(p1.F < p2.F){
        return p1;
    }
    else{
        return p2;
    }
}

int ret(int ss,int se)
{

    //cout << "yessss "<< ss << " " << se << endl;
    if(ss < 0 || se < 0) return 0;
    if(ss >= se){
        return foo[ss];
    }

    ii now = query(1,0,m-1,ss,se);
    //cout << "yes " << now.F << " " << now.S << endl;
    int ans = (se-ss+1)*now.F;
    ans = max(ans,ret(ss,now.S-1));
    ans = max(ans,ret(now.S+1,se));
    return ans;
}

int main()
{
    int t = 0,T;
    sc("%d",&T);

    while(++t <= T){
        memset(foo,0,sizeof(foo));
        sc("%d%d",&n,&m);
        rep(i,0,n){
            rep(j,0,m){
                char ch;
                sc(" %c",&ch);
                s[i][j] = ch;
            }
        }
        int ans = 0;
        rep(i,0,n){

            rep(j,0,m){
                if(s[i][j] == 'F') foo[j]++;
                else foo[j] = 0;
            }

            build(1,0,m-1);
            ans = max(ans,ret(0,m-1));
            //ii an = query(1,0,m-1,1,5);
            //cout << ret(0,m-1) << endl;

        }

        pc("%d\n",ans*3);

    }

	return 0;
}






