#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef pair<ii,int> iii;


#define N 10000005
#define M 40005
#define INF 10000003
#define PI acos(-1)
#define rep(i,a,b) for(int i = a; i < b; i++)
#define reps(i,a,b) for(int i = a; i >= b; i--)
#define sc scanf
#define pc printf
#define pb push_back
#define F first
#define S second

int n,t,l[M],r[M],con[N];
bool tree[M*4],lazy[M*4];
set<int>st;

void update(int node,int a,int b,int aa,int bb)
{   int lft = node<<1;
    int rgt = lft|1;
    if(lazy[node]){
        tree[node] = 1;
        if(a != b){
            lazy[lft] = lazy[node];
            lazy[rgt] = lazy[node];
        }
        lazy[node] = 0;
    }

    if(a > b || a > bb || b < aa) return;

    if(a >= aa && b <= bb){
        tree[node] = 1;
        if(a != b){
            lazy[lft] = 1;
            lazy[rgt] = 1;
        }
        lazy[node] = 0;
        return;
    }
    int mid = (a + b)>>1;
    update(lft,a,mid,aa,bb);
    update(rgt,mid+1,b,aa,bb);
    tree[node] = (tree[lft]&tree[rgt]);
}

int ret(int node,int a,int b,int aa,int bb)
{
    //if(a > b || a > bb || b < aa) return 0;
    int lft = node<<1;
    int rgt = lft|1;
    if(lazy[node] ){
        tree[node] = 1;
        if(a != b){
            lazy[lft] = lazy[node];
            lazy[rgt] = lazy[node];
        }
        lazy[node] = 0;
    }


    if(a >= aa && b <= bb){
        return tree[node];
    }
    if(a > bb || b < aa) return 1;
    int mid = (a + b)>>1;
    bool q1 = ret(lft,a,mid,aa,bb);
    bool q2 = ret(rgt,mid+1,b,aa,bb);
    return (q1&q2);
}

int main()
{
    sc("%d",&t);
    while(t--){
        st.clear();
        sc("%d",&n);
        rep(i,0,4*M){
            lazy[i] = 0;
            tree[i] = 0;
        }
        rep(i,0,n){
            sc("%d%d",&l[i],&r[i]);
            st.insert(l[i]);
            st.insert(r[i]);
        }
        int in = 0;
        set<int>::iterator it;
        for(it = st.begin(); it != st.end(); it++){
            con[(*it)] = ++in;
        }
        int cnt = 0;
        reps(i,n-1,0){
            int u = l[i],v = r[i];
            bool is = ret(1,1,in,con[u],con[v]);
            if(is == 0){
                update(1,1,in,con[u],con[v]);
                cnt++;
            }
        }
        pc("%d\n",cnt);
    }

	return 0;
}






