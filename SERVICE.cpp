//////////////////////////////////////
//           Author : Hasan         //
//              CSE,BUET            //
//////////////////////////////////////

/*
One simple observation makes it O(NL^2) instead of O(NL^3) .
Observation:
We know the last request location from request array. We can use it to optimize
*/
#include <bits/stdc++.h>
#include<unordered_map>
using namespace std;
 
 
 
#define ll long long
#define N 205
#define M 1005
#define pb push_back
#define mp make_pair
#define rep(i,n,m) for(int i = n; i < m; i++)
#define reps(i,n,m) for(int i = n;i >= m; i--)
#define sc scanf
#define pc printf
 
int n,l,cost[N][N],req[M],dp[N][N][M];
 
int go(int loc1,int loc2,int pos){
    if(pos >= n){
        return 0;
    }
 
    int &ret = dp[loc1][loc2][pos];
 
    if(ret != 1e9) return ret;
 
    if(pos == 0){
        if(req[pos] == 1){
           ret = go(2,3,pos+1);
        }
        else if(req[pos] == 2){
           ret = go(1,3,pos+1);
        }
        else if(req[pos] == 3){
           ret = go(1,2,pos+1);
        }
        else{
            int a = min(cost[1][req[pos]] + go(2,3,pos+1),cost[2][req[pos]] + go(1,3,pos+1));
            int b = min(a,cost[3][req[pos]] + go(1,2,pos+1));
            ret = b;
        }
    }
    else{
        int prevLoc = req[pos-1];
        if(req[pos] == prevLoc){
            ret = go(loc1,loc2,pos+1);
        }
        else if(loc1 == req[pos]){
            ret = go(req[pos-1],loc2,pos+1);
        }
        else if(loc2 == req[pos]){
            ret = go(loc1,req[pos-1],pos+1);
        }
        else{
            int a = min(cost[loc1][req[pos]] + go(req[pos-1],loc2,pos+1),cost[loc2][req[pos]] + go(loc1,req[pos-1],pos+1));
            int b = min(a,cost[req[pos-1]][req[pos]] + go(loc1,loc2,pos+1));
            ret = b;
        }
    }
 
 
    return ret;
 
}
 
 
int main()
{
    int cases;
    sc("%d",&cases);
 
    while(cases--){
        rep(i,0,N){
            rep(j,0,N){
                rep(k,0,M){
                    dp[i][j][k] = 1e9;
                }
            }
        }
 
        sc("%d%d",&l,&n);
 
        rep(i,1,l+1){
            rep(j,1,l+1){
                sc("%d",&cost[i][j]);
            }
        }
 
        rep(i,0,n) sc("%d",&req[i]);
 
        int ans = go(1,2,0);
 
        pc("%d\n",ans);
    }
 
 
 
 
 
    return 0;
}
