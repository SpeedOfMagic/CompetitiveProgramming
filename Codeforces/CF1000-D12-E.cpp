/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
//Editorial: http://codeforces.com/blog/entry/60288
#include <bits/stdc++.h>
using namespace std;
template<typename T> using v = vector<T>;
#define int long long
typedef string str;
typedef vector<int> vint;
#define rep(a, l, r) for(int a = (l); a < (r); a++)
#define pb push_back
#define sz(a) ((int) a.size())
const int inf = 4611686018427387903; //2^62 - 1
#if 0  //FileIO
const string fileName = "";
ifstream fin ((fileName == "" ? "input.txt"  : fileName + ".in" ));
ofstream fout((fileName == "" ? "output.txt" : fileName + ".out"));
#define get fin>>
#define put fout<<
#else
#define get cin>>
#define put cout<<
#endif
#define eol put endl
void read() {}     template<typename Arg,typename... Args> void read (Arg& arg,Args&... args){get (arg)     ;read(args...) ;}
void print(){}     template<typename Arg,typename... Args> void print(Arg  arg,Args...  args){put (arg)<<" ";print(args...);}
void debug(){eol;} template<typename Arg,typename... Args> void debug(Arg  arg,Args...  args){put (arg)<<" ";debug(args...);}
int getInt(){int a; get a; return a;}
//code goes here
const int N=3e5+1;
vint g[N];
set<int>g2Rev[N];
bool vis[N];
int col[N];
stack<int>l;
int color=0;
void dfs(int cur,bool todo){
    if(todo){
        col[cur]=color;
        for(int i:g2Rev[cur])if(col[i]==0)dfs(i,todo);
    } else {
        vis[cur]=1;
        for (int i:g[cur]){
            if(!g2Rev[cur].count(i))g2Rev[i].insert(cur);
            if(!vis[i])dfs(i,todo);
        }
        l.push(cur);
    }

}

vint g3[N];
pair<int,int> dfs2(int cur,int p,int d){
    int mx=d,res=cur;
    for(int i:g3[cur]){
        if(i==p)continue;
        pair<int,int>t=dfs2(i,cur,d+1);
        if(t.first>mx){
            mx=t.first;
            res=t.second;
        }
    }
    return {mx,res};
}
void run(){
    int n,m;read(n,m);
    int memV[m],memU[m];
    rep(i,0,m){
        int v,u;
        read(v,u);
        g[v].pb(u);
        g[u].pb(v);
        memV[i]=v;
        memU[i]=u;
    }
    rep(i,0,N)
        vis[i]=0;
    dfs(1,0);
    rep(i,0,N)col[i]=0;
    while(!l.empty()){
        if(col[l.top()]==0){
            color++;
            dfs(l.top(),1);
        }
        l.pop();
    }
    set<int>forbid;
    rep(i,0,m){
        int v=memV[i],u=memU[i];
        if(col[v]==col[u])continue;
        g3[col[v]].pb(col[u]);
        g3[col[u]].pb(col[v]);
    }//g3- конденсация

    int from=dfs2(1,-1,0).second;
    put dfs2(from,-1,0).first;
}

int32_t main() {srand(time(0));ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);put setprecision(15);run();return 0;}